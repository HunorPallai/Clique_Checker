package hu.elte.inf.graph.clique;

import static hu.elte.inf.graph.clique.MatrixLoadKernel.NUM_ROWS;

import java.util.ArrayList;
import java.util.List;
import java.util.Collections;
import java.util.stream.Collectors;

import com.maxeler.maxcompiler.v2.kernelcompiler.Kernel;
import com.maxeler.maxcompiler.v2.kernelcompiler.KernelBase;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEType;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.base.DFEVar;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVector;
import com.maxeler.maxcompiler.v2.kernelcompiler.types.composite.DFEVectorType;
import com.maxeler.maxcompiler.v2.kernelcompiler.stdlib.Bitops;
import com.maxeler.maxcompiler.v2.kernelcompiler.Optimization;
import com.maxeler.maxcompiler.v2.utils.MathUtils;

import com.maxeler.maxeleros.resourceestimation.KernelEstimatorVisitor;
import com.maxeler.maxeleros.managercompiler.graph.nodes.KernelGraphVisitor;
import com.maxeler.photon.resource_annotation.ResourceComponent;
import com.maxeler.photon.graph_passes.maxdc_gen.OptionallyInlinedLogicNode;
import com.maxeler.photon.core.PhotonDesignData;
import com.maxeler.photon.core.VarTyped;
import com.maxeler.photon.maxcompilersim.CodeBlockRoot;
import com.maxeler.photon.maxcompilersim.Expression;
import com.maxeler.photon.maxcompilersim.SimCodeType;
import com.maxeler.photon.maxcompilersim.COutput;
import com.maxeler.photon.maxcompilersim.ExpInput;
import com.maxeler.photon.maxcompilersim.CodeContext;
import com.maxeler.photon.core.Node;
import com.maxeler.photon.core.Var;
import com.maxeler.photon.types.HWType;
import com.maxeler.photon.core.PhotonException;
import com.maxeler.photon.nodes.NodeConstant;
import com.maxeler.photon.nodes.ConstantFold;
import com.maxeler.maxdc.resource_usage.EntityResourceUsage;
import com.maxeler.maxdc.Entity;
import com.maxeler.maxdc.Signal;
import com.maxeler.maxdc.Reg;
import com.maxeler.maxdc.LogicSource;
import com.maxeler.maxdc.EntityStructural;
import com.maxeler.maxdc.portable.KeepHierarchy;
import com.maxeler.utils.Bits;

import java.util.Map;
import java.util.Set;
import java.util.EnumSet;
import java.lang.reflect.Field;


public class Utility {
	public static final DFEType UINT64 = Kernel.dfeUInt(64);
	public static final DFEType UINT32 = Kernel.dfeUInt(32);
	public static final DFEType UINT6 = Kernel.dfeUInt(6);
	public static final DFEType BOOL = Kernel.dfeBool();
	public static final DFEVectorType<DFEVar> ADJ_MATRIX_TYPE = 
			new DFEVectorType<DFEVar>(UINT64, NUM_ROWS);
	
	public static class Pair<A, B> {
        private A first;
        private B second;
    
        public Pair(A first, B second) {
            super();
            this.first = first;
            this.second = second;
        }
    
        public int hashCode() {
            int hashFirst = first != null ? first.hashCode() : 0;
            int hashSecond = second != null ? second.hashCode() : 0;
    
            return (hashFirst + hashSecond) * hashSecond + hashFirst;
        }
    
        public boolean equals(Object other) {
            if (other instanceof Pair<?, ?>) {
                Pair<?, ?> otherPair = (Pair<?, ?>) other;
                return 
                ((  this.first == otherPair.first ||
                    ( this.first != null && otherPair.first != null &&
                      this.first.equals(otherPair.first))) &&
                 (  this.second == otherPair.second ||
                    ( this.second != null && otherPair.second != null &&
                      this.second.equals(otherPair.second))) );
            }
    
            return false;
        }
    
        public String toString()
        { 
               return "(" + first + ", " + second + ")"; 
        }
    
        public A getFirst() {
            return first;
        }
    
        public void setFirst(A first) {
            this.first = first;
        }
    
        public B getSecond() {
            return second;
        }
    
        public void setSecond(B second) {
            this.second = second;
        }
    }
	
	public static class NodeKeep extends Node implements OptionallyInlinedLogicNode, ConstantFold
    {
        public NodeKeep(final PhotonDesignData photonDesignData, final String[] array) {
            super(photonDesignData, array);
            this.addInput("a");
            this.addOutput("result");            
        }

        @Override
        public Optimization.PipelinedOps getNodeType() {
            return Optimization.PipelinedOps.MISC;
        }

        @Override
        public VarTyped<NodeKeep> connectOutput(final String s) {
            return this._connectOutput(this, s);
        }
        
        @Override
        protected void assignOutputTypes() {
            final InputDesc inputDesc = this.getInputDesc("a");
            final HWType hwType = inputDesc.getSrcType();
            this.setOutputDesc("result", hwType, this.isResultRegistered() ? 1 : 0);
        }

        @Override
        public Set<ControlSignal> getControlSignals() {
            if (!this.isResultRegistered()) return Collections.emptySet();
            if (this.getOutputDesc("result").getVar().getResetValue() != null) {
                return EnumSet.of(ControlSignal.CLOCK, ControlSignal.CLOCK_ENABLE, ControlSignal.RESET);
            }
            return EnumSet.of(ControlSignal.CLOCK, ControlSignal.CLOCK_ENABLE);
        }
        
        @Override
        public Entity make() {
            throw new PhotonException("make() not implemented", new Object[0]);
        }
        
        @Override
        public void makeSimCode(final CodeContext codeContext) {
            final ExpInput expInput = codeContext.getInputVar("a");
            final COutput cOutput = codeContext.getOutputVar("result");
            final HWType hwType = cOutput.getType().getHWType();
            Expression expression = expInput;
            if (!expInput.getType().isSoftwareType() && !expInput.getType().getHWType().equals(hwType)) {
                expression = expInput.cast(new SimCodeType(hwType));
            }
            final Bits bits = this.getOutputDesc("result").getVar().getResetValue();
            if (bits != null) {
                final CodeBlockRoot codeBlockRoot = codeContext.getResetBlock();
                codeBlockRoot.output(cOutput, codeBlockRoot.constant(bits, cOutput.getType()));
            }
            final CodeBlockRoot codeBlockRoot2 = codeContext.getExecuteBlock();
            codeBlockRoot2.output(cOutput, codeBlockRoot2.eval(expression));
        }
        
        @Override
        protected EntityResourceUsage getEstimatedResourceCount() {
            final int totalBits = this.getInputDesc("a").getType().getTotalBits();
            return new EntityResourceUsage(totalBits, this.isResultRegistered() ? totalBits : 0, 0, 0);
        }
        
        private boolean isResultRegistered() {
            return this.getOperatorSupplier().getSquashFactor(Optimization.PipelinedOps.MISC) == 0.0;
        }
        
        @Override
        public boolean canResetOutput(final OutputDesc outputDesc) {
            return outputDesc == this.getOutputDesc("result") && this.isResultRegistered();
        }
        
        @Override
        public Map<String, LogicSource> makeInlineLogic(final Map<String, LogicSource> map, final EntityStructural entityStructural) {
            Signal signal = entityStructural.signal(map.get("a"));  
            LogicSource logicSource = null;
            if (this.isResultRegistered()) {
                final Reg reg = entityStructural.reg(signal);
                reg.setKeepSynthesis(); //Vivado KEEP
                //reg.setKeepImplementation(); //Vivado DONT_TOUCH prevents LUTNMs!
                final Bits bits = this.getOutputDesc("result").getVar().getResetValue();
                if (bits != null) {
                    reg.setResetValue(entityStructural.constant(bits));
                }
                logicSource = reg;
            } else {
                signal.setKeepSynthesis(); //Vivado KEEP
                //signal.setKeepImplementation(); //Vivado DONT_TOUCH prevents LUTNMs!
                logicSource = signal;
            }
            entityStructural.setKeepHierarchy(KeepHierarchy.FALSE);
            return Collections.singletonMap("result", logicSource);
        }
        
        @Override
        public String getUserSignature() {
            return "PhotonKeep_" + this.getInputDesc("a").getType().getTotalBits() + ((this.getOperatorSupplier().getSquashFactor(this.getNodeType()) == 0.0) ? "pipe" : "nopipe");
        }
        
        @Override
        public void visitKernelGraph(final KernelGraphVisitor kernelGraphVisitor) {
            kernelGraphVisitor.visitKernelGraph(this);
        }
        
        @Override
        public <R extends Enum<R> & ResourceComponent> void visitKernelUsageEstimation(final KernelEstimatorVisitor<R> kernelEstimatorVisitor) {
            kernelEstimatorVisitor.visit(this);
        }
       
        @Override
        public NodeConstant foldOperation() {
            final NodeConstant nodeConstant = this.tryReplaceByConstant();
            if (nodeConstant != null) {
                return nodeConstant;
            }
            final ConstantInput constantInput = this.findSingleConstantInput();
            if (constantInput == null) {
                return null;
            }
            final Bits bits = constantInput.node.getValueAsBits(constantInput.type);
            if (bits.isAllZeros()) {
                return this.replaceWithConstant(bits);
            }
            return null;
        }
               
        @Override
        public String toString() {
            return "KEEP";
        }
        
        protected NodeConstant tryReplaceByConstant() {
            final NodeConstant nodeConstant = this.getInputAsConstant("a");
            if (nodeConstant == null) {
                return null;
            }
            return this.replaceWithConstant(nodeConstant.getValueAsBits(this.getInputDesc("a").getType()));
        }        
        protected ConstantInput findSingleConstantInput() {
            String s = "a";
            NodeConstant nodeConstant = this.getInputAsConstant("a");
            HWType hwType = this.getInputDesc("a").getType();
            if (nodeConstant == null) {
                return null;
            }
            return new ConstantInput(s, nodeConstant, hwType);
        }
        protected NodeConstant replaceWithConstant(final Bits bits) {
            return this.replaceWithConstant("result", bits);
        }

        protected static class ConstantInput
        {
            public final String input;
            public final NodeConstant node;
            public final HWType type;
            
            public ConstantInput(final String input, final NodeConstant node, final HWType type) {
                this.input = input;
                this.node = node;
                this.type = type;
            }
        }        
    }
	
	public static DFEVar setKeep(DFEVar var, boolean keepEnabled)
    {
        if (keepEnabled) {
            NodeKeep node = new NodeKeep(var.getOwner().getPhotonDesignData(), var.getOwner().getPhotonDesignData().getGroupPath());
            try {
                Field f = var.getClass().getDeclaredField("m_imp");
                f.setAccessible(true);
                node.connectInput("a", (Var)f.get(var));
            } catch (NoSuchFieldException|IllegalAccessException e) { }
            return new DFEVar(var.getOwner(), node.connectOutput("result"));
        } else {
            return var;
        }
    }
	
	public static Pair<DFEVar, DFEVar> leading0count(DFEVar var, KernelBase<?> base, boolean oldMethod, boolean keep, boolean altMethod)
    {
        int size = var.getType().getTotalBits();
        //construct 8-bit LZC
        if (oldMethod) keep = true;
        List<DFEVar> LP3s = new ArrayList<>(), LP2s = new ArrayList<>(), LP1_ints = new ArrayList<>();
        List<DFEVar> LP1s = new ArrayList<>(), LP4s = new ArrayList<>();
        base.optimization.pushNoPipelining();
        for (int i = size; i > 0; i -= 8) {
            int curSize = Math.min(i, 8);
            DFEVar x = var.slice(Math.max(0, i-8), curSize);
            if (size <= 8 || oldMethod || altMethod || (LP4s.size() & 1) == 0 || curSize < 7)
                LP3s.add(curSize <= 2 ? null : setKeep((curSize >= 4 ? x.slice(curSize-4, 4) : x) === 0, keep));
            LP2s.add(curSize <= 1 ? null :
                setKeep((curSize <= 4 ? x.slice(curSize-2, 2) === 0 :
                x.slice(curSize-2, 2) === 0 &
                    (x.slice(curSize-4, 2) !== 0 | (curSize >= 6 ? x.slice(curSize-6, 2) === 0 : ~x.get(curSize-5)))), keep));
            if (size > 8 && !oldMethod && !altMethod && ((LP1_ints.size() & 1) != 0) && curSize >= 7) {
                LP1_ints.add(setKeep(
                    ~var.get(i+1) & (var.get(i) | ~x.get(curSize-1) & (x.get(curSize-2) | ~x.get(curSize-3))), keep)); // & x.get(curSize-4)
            } else {
                LP1_ints.add(setKeep(
                    curSize > 6 && (size <= 8 || oldMethod || altMethod) ? ~x.get(curSize-1) & (x.get(curSize-2) | ~x.get(curSize-3) & (x.get(curSize-4) | ~x.get(curSize-5) & x.get(curSize-6))) :
                    curSize >= 5 ? ~x.get(curSize-1) & (x.get(curSize-2) | ~x.get(curSize-3) & (x.get(curSize-4) | ~x.get(curSize-5))) :
                    curSize >= 3 ? ~x.get(curSize-1) & (x.get(curSize-2) | ~x.get(curSize-3)) :
                    ~x.get(curSize-1), keep));
            }
            if (size <= 8 || oldMethod) {
                LP4s.add(curSize <= 4 ? null :
                    setKeep(curSize <= 6 ? x === 0 :
                    LP3s.get(LP3s.size()-1) & LP2s.get(LP2s.size()-1) & ~LP1_ints.get(LP1_ints.size()-1) & (curSize <= 7 ? ~x.get(curSize-7) : x.slice(curSize-8, 2) === 0), size > 8 && keep));
                LP1s.add(curSize <= 6 ? LP1_ints.get(LP1_ints.size()-1) :
                    setKeep(LP1_ints.get(LP1_ints.size()-1) | LP3s.get(LP3s.size()-1) & LP2s.get(LP2s.size()-1) & ~x.get(curSize-7), size > 8 && keep));
                if (size <= 8) {
                    base.optimization.popNoPipelining();
                    return new Pair<DFEVar, DFEVar>(base.optimization.limitFanout(
                        size <= 1 ? LP1s.get(0).reinterpret(KernelBase.dfeBool()) :
                        size <= 2 ? LP2s.get(0).reinterpret(KernelBase.dfeBool()) :
                        size <= 4 ? LP3s.get(0).reinterpret(KernelBase.dfeBool()) : LP4s.get(0).reinterpret(KernelBase.dfeBool()), 32),
                        size <= 1 ? null : base.optimization.limitFanout(
                        size <= 2 ? LP1s.get(0).reinterpret(KernelBase.dfeBool()) :
                        size <= 4 ? LP2s.get(0).cat(LP1s.get(0)).reinterpret(KernelBase.dfeUInt(2)) :
                        LP3s.get(0).cat(LP2s.get(0)).cat(LP1s.get(0)).reinterpret(KernelBase.dfeUInt(3)), 32));
                }
            } else {
                if (!altMethod && (LP4s.size() & 1) != 0 && curSize >= 7) { //low part of intermediate requires shifted calculation or Z0s requires 7 bits
                    LP4s.add(setKeep(var.slice(i, 2).cat(x.slice(curSize-3, 3)) === 0, keep));
                    LP1s.add(x.slice(0, curSize-3));
                    LP3s.add(LP4s.get(LP4s.size()-1) & ~x.get(curSize-4));
                } else {
                    LP4s.add(setKeep((curSize >= 6 ? x.slice(curSize-6, 6) : x) === 0, keep));
                    LP1s.add(curSize <= 6 ? null : curSize <= 7 ? x.get(curSize-7) : x.slice(curSize-8, 2));
                }
            }
        }
        List<DFEVar> V = new ArrayList<>(), Z0s = new ArrayList<>(), Z1s = new ArrayList<>(), Z2s = new ArrayList<>(), Z3s = new ArrayList<>();
        for (int i = 0; i < LP4s.size(); i += 2) {
            DFEVar VH;
            if (oldMethod) {
                if (size <= 16) keep = false;
                VH = LP4s.get(i) == null ? (LP3s.get(i) == null ? (LP2s.get(i) == null ? LP1s.get(i).reinterpret(KernelBase.dfeBool()) : LP2s.get(i)) : LP3s.get(i)) : LP4s.get(i);
                V.add(i+1==LP4s.size() ? VH : setKeep(VH & (LP4s.get(i+1) == null ? (LP3s.get(i+1) == null ? (LP2s.get(i+1) == null ? LP1s.get(i+1) : LP2s.get(i+1)) : LP3s.get(i+1)) : LP4s.get(i+1)), keep));
                Z0s.add(setKeep(VH ? (i+1==LP1s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : LP1s.get(i+1).reinterpret(KernelBase.dfeBool())) : LP1s.get(i).reinterpret(KernelBase.dfeBool()), keep));
                Z1s.add(setKeep(VH ? (i+1==LP2s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : (LP2s.get(i+1) == null ? LP1s.get(i+1) : LP2s.get(i+1)).reinterpret(KernelBase.dfeBool())) : (LP2s.get(i) == null ? LP1s.get(i) : LP2s.get(i)).reinterpret(KernelBase.dfeBool()), keep));
                Z2s.add(setKeep(VH ? (i+1==LP3s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : (LP3s.get(i+1) == null ? (LP2s.get(i+1) == null ? LP1s.get(i+1) : LP2s.get(i+1)) : LP3s.get(i+1)).reinterpret(KernelBase.dfeBool())) : (LP3s.get(i) == null ? (LP2s.get(i) == null ? LP1s.get(i) : LP2s.get(i)) : LP3s.get(i)).reinterpret(KernelBase.dfeBool()), keep));
            } else {
                VH = LP1s.get(i) == null ? LP4s.get(i) : LP4s.get(i) & LP1s.get(i) === 0;
                boolean defaultLogic = i+1==LP4s.size() || LP1s.get(i+1) == null || LP1s.get(i+1).getType().getTotalBits() < 3;
                if (defaultLogic) {
                    if (size <= 16) keep = false;
                    V.add(i+1==LP4s.size() ? VH : setKeep(LP4s.get(i) & LP4s.get(i+1) & (LP1s.get(i+1) == null ? LP1s.get(i) : LP1s.get(i).cat(LP1s.get(i+1))) === 0, keep));
                    if (size <= 14) Z0s.add(setKeep(VH ? (i+1==LP4s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : (LP1s.get(i+1) == null ? LP1_ints.get(i+1) : LP1_ints.get(i+1) | LP4s.get(i+1)).reinterpret(KernelBase.dfeBool())) : (LP1s.get(i) == null ? LP1_ints.get(i) : LP1_ints.get(i) & ~LP4s.get(i) | LP4s.get(i) & ~LP1s.get(i).get(LP1s.get(i).getType().getTotalBits()-1)).reinterpret(KernelBase.dfeBool()), keep));
                    else Z0s.add(setKeep(VH ? (i+1==LP4s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : (LP1s.get(i+1) == null ? LP1_ints.get(i+1) : LP1_ints.get(i+1) | LP4s.get(i+1) & ~LP1s.get(i+1).get(LP1s.get(i+1).getType().getTotalBits()-1)).reinterpret(KernelBase.dfeBool())) : (LP1s.get(i) == null ? LP1_ints.get(i) : LP1_ints.get(i) & ~LP4s.get(i) | LP4s.get(i) & ~LP1s.get(i).get(LP1s.get(i).getType().getTotalBits()-1)).reinterpret(KernelBase.dfeBool()), keep));
                } else {
                    DFEVar allZero = setKeep(LP1s.get(i+1) === 0, keep);
                    int l = LP1s.get(i+1).getType().getTotalBits();
                    DFEVar parity = setKeep(LP1s.get(i+1).get(l-1) | ~LP1s.get(i+1).get(l-2) & (LP1s.get(i+1).get(l-3) | ~LP1s.get(i+1).get(l-4)), keep);
                    if (size <= 16) keep = false;
                    V.add(i+1==LP4s.size() ? VH : setKeep(LP1s.get(i+1) == null ? LP4s.get(i) & LP4s.get(i+1) : LP4s.get(i) & LP4s.get(i+1) & allZero, keep));
                    Z0s.add(setKeep((LP4s.get(i) ? (LP4s.get(i+1) ? parity : LP1_ints.get(i+1)) : LP1_ints.get(i)).reinterpret(KernelBase.dfeBool()), keep));
                }
                Z1s.add(setKeep(VH ? (i+1==LP4s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : (LP2s.get(i+1) == null ? LP1_ints.get(i+1).reinterpret(KernelBase.dfeBool()) : LP2s.get(i+1))) :
                    (LP2s.get(i) == null ? LP1_ints.get(i).reinterpret(KernelBase.dfeBool()) : LP2s.get(i)), keep));
                Z2s.add(setKeep(VH ? (i+1==LP4s.size() ? base.constant.var(KernelBase.dfeBool(), 1) : (LP3s.get(i+1) == null ? (LP2s.get(i+1) == null ? LP1_ints.get(i+1).reinterpret(KernelBase.dfeBool()) : LP2s.get(i+1)) : LP3s.get(i+1))) :
                    (LP3s.get(i) == null ? (LP2s.get(i) == null ? LP1_ints.get(i).reinterpret(KernelBase.dfeBool()) : LP2s.get(i)) : LP3s.get(i)), keep));
                if (LP1s.get(i) != null) VH = setKeep(VH, keep);
            }
            Z3s.add(VH);
        }
        List<List<DFEVar>> Zs = new ArrayList<>();
        int total = MathUtils.ceilLog2(size);
        for (int c = 0; c < total-4; c++) {
            if (c == total-4-1) keep = false;
            Zs.add(new ArrayList<>());
            for (int i = 0; i < V.size(); i++) {
                Z0s.set(i, setKeep(V.get(i) ? (i+1==V.size() ? base.constant.var(KernelBase.dfeBool(), 1) : Z0s.get(i+1)) : Z0s.get(i), keep));
                Z1s.set(i, setKeep(V.get(i) ? (i+1==V.size() ? base.constant.var(KernelBase.dfeBool(), 1) : Z1s.get(i+1)) : Z1s.get(i), keep));
                Z2s.set(i, setKeep(V.get(i) ? (i+1==V.size() ? base.constant.var(KernelBase.dfeBool(), 1) : Z2s.get(i+1)) : Z2s.get(i), keep));
                Z3s.set(i, setKeep(V.get(i) ? (i+1==V.size() ? base.constant.var(KernelBase.dfeBool(), 1) : Z3s.get(i+1)) : Z3s.get(i), keep));
                for (int j = 0; j < c; j++) {
                    Zs.get(j).set(i, setKeep(V.get(i) ? (i+1==V.size() ? base.constant.var(KernelBase.dfeBool(), 1) : Zs.get(j).get(i+1)) : Zs.get(j).get(i), keep));
                }
                Zs.get(c).add(V.get(i));
                V.set(i, i+1==V.size() ? V.get(i) : setKeep(V.get(i) & V.get(i+1), keep));
                if (i+1!=V.size()) { V.remove(i+1); Z0s.remove(i+1); Z1s.remove(i+1); Z2s.remove(i+1); Z3s.remove(i+1);
                    for (int j = 0; j < c; j++) { Zs.get(j).remove(i+1); }
                }
            }
        }
        base.optimization.popNoPipelining();
        return new Pair<DFEVar, DFEVar>(base.optimization.limitFanout(V.get(0), 32),
            base.optimization.limitFanout(
                (Zs.size() != 0 ? Bitops.catLsbToMsb(Zs.stream().map(x -> x.get(0)).collect(Collectors.toList())).cat(
                    Z3s.get(0)) : Z3s.get(0)).cat(Z2s.get(0)).cat(Z1s.get(0)).cat(Z0s.get(0)).reinterpret(KernelBase.dfeUInt(total)), 32));
    }
	
	public static DFEVar trailingZeroCount(DFEVar value, Kernel kernel) {
		//return leading0count(Bitops.bitreverse(value), kernel, false, false, true).second;
		return ctz64(value, kernel);
	}
	
	public static DFEVar barrelShifter(DFEVar value, DFEVar shift, boolean isLeft, KernelBase<?> base)
    {
        final int muxPipeliningLimit = 3;
        value = base.optimization.pipeline(value);
        //LUT6 allows 4:1 MUX, LUT6_2 allows 2-bit 2:1 MUX
        int tot = shift.getType().getTotalBits();
        for (int i = 0; i < tot; i+=2) {
            if (i % (muxPipeliningLimit * 2) == (muxPipeliningLimit * 2 - 2) || i+2 >= tot) base.optimization.pushNoPipelining();
            if (i == tot-1) {
                value = base.control.mux(shift.get(i), value, isLeft ? value << (1<<i) : value >> (1<<i)); //1+2=LUT3 or 1+2+1+2=LUT6_2
            } else {
                value = base.control.mux(shift.slice(i, 2), value, isLeft ? value << (1<<i) : value >> (1<<i),
                    isLeft ? value << (1<<(i+1)) : value >> (1<<(i+1)), isLeft ? value << ((1<<i)+(1<<(i+1))) : value >> ((1<<i)+(1<<(i+1)))); //2+4=LUT6
            }
            if (i % (muxPipeliningLimit * 2) == (muxPipeliningLimit * 2 - 2) || i+2 >= tot) base.optimization.popNoPipelining();
        }
        return value;
    }
	
	public static DFEVar nextGospersSubset(DFEVar subset, Kernel kernel) {
		DFEVar c = subset & (~subset + 1);
		DFEVar r = subset + c;
		DFEVar diff = (subset ^ r) >> 2;
		DFEVar shiftAmount = trailingZeroCount(c, kernel);
		DFEVar divByC = barrelShifter(diff, shiftAmount, false, kernel);
		return divByC | r;
	}
	
	public static DFEVar ctz64(DFEVar value, Kernel kernel) {
		DFEVar lowest1Bit = value & (~value + 1);
		DFEVar result = kernel.constant.var(UINT6, 0);
		for (int i = 0; i < 64; ++i) {
			DFEVar isBitSet = lowest1Bit.slice(i, 1).cast(BOOL);
			DFEVar pos = kernel.constant.var(UINT6, i);
			result = result | (isBitSet === 1 ? pos : kernel.constant.var(UINT6, 0));
		}
		
		return result;
	}
	
	public static DFEVar lookupRow(DFEVector<DFEVar> rows, DFEVar index, Kernel kernel) {
		DFEVar result = rows[0];
		
		for (int i = 1; i < 64; ++i) {
			result = (index === kernel.constant.var(UINT6, i)) ? rows[i] : result;
		}
		
		return result;
	}
}
