#include "llvm/Support/CommandLine.h" // For cl::xxx.
#include "llvm/Support/Debug.h"       // For dbgs().

using namespace llvm;

extern int fctWithUB(int a);

static cl::opt<int> InputNumber(cl::Positional, cl::desc("<input IR file>"),
                                cl::init(12));

int main(int argc, char **argv) {
  cl::ParseCommandLineOptions(argc, argv, "CH10 UB sanitizer\n");

  int Result = fctWithUB(InputNumber);
  dbgs() << "fctWithUB(" << InputNumber << ") == " << Result << '\n';

  return 0;
}
