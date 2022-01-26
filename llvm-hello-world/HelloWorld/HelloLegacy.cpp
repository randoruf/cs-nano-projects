#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"


using namespace llvm;
// the "static" keyword to file in C, which means the anonymous namespace is only visible to the current file. 
namespace {

// This method implements what the pass does
void visitor(Function &F) {
    errs() << "(llvm-tutor) Hello from: "<< F.getName() << "\n";
    errs() << "(llvm-tutor)   number of arguments: " << F.arg_size() << "\n";
}
//-----------------------------------------------------------------------------
// Legacy PM Implementation
//----------------------------------------------------------------------------
struct HelloWorld : public FunctionPass{
    static char ID; // the ID address used by LLVM to identify a pass (so the intilization value does not matter)
    HelloWorld() : FunctionPass(ID) {} 
    // the default behavior of an FunctionPass 
    virtual bool runOnFunction(Function &F) override{
        errs() << ">>>> The Legacy PM <<<<\n"; 
        visitor(F); 
        return false; // this is an Analysis Pass, to return false as we don't modify the IR unit. 
    }
}; 

} // namespace (without ; )

//-----------------------------------------------------------------------------
// Legacy PM Registration
//----------------------------------------------------------------------------
// The address of this variable is used to uniquely identify the pass. The actual value doesn't matter.
char HelloWorld::ID = 0; 
// This is the core interface for pass plugins. It guarantees that 'opt' will
// recognize LegacyHelloWorld when added to the pass pipeline on the command
// line, i.e.  via '--legacy-hello-world'
RegisterPass<HelloWorld> 
    X("hello-legacy", "Hello World Pass (Legacy)", 
    true,  // This pass doesn't modify the CFG => true
    false  // This pass is not a pure analysis pass(since it actually doing nothing and printing) => false
); 
 
