#pragma once

#include <ostream>

struct PassTestFileInput;
struct NoFailTestFileInput;

void PrintTo(PassTestFileInput const& output, std::ostream* os);
void PrintTo(NoFailTestFileInput const& output, std::ostream* os);

namespace ccg {
class CompilerOutput;

void PrintTo(CompilerOutput const& output, std::ostream* os);
}
