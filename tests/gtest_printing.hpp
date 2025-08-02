#include <ostream>

struct PassTestFileInput;

namespace ccg {
class CompilerOutput;

void PrintTo(CompilerOutput const & output, std::ostream * os);
void PrintTo(PassTestFileInput const & output, std::ostream * os);
}
