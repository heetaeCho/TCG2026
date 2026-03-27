// File: re2_compile_to_prog_test_327.cc

#include <gtest/gtest.h>
#include <cstdint>
#include <limits>

// Include the public interface only.
#include "re2/regexp.h"

namespace re2 {

// Forward declarations to avoid depending on internal definitions.
class Prog;
class Compiler;

// ---- Test seam to observe calls into the external collaborator ----
// We provide a definition for Compiler::Compile with the exact signature.
// This replaces the real implementation at link-time *for tests only*,
// letting us observe the call and control the return value without
// re-implementing any Regexp logic.

static Regexp*      g_last_re            = nullptr;
static bool         g_last_reversed      = true;      // will detect false forwarding
static int64_t      g_last_max_mem       = -1;
static Prog*        g_return_prog        = reinterpret_cast<Prog*>(0xDEADBEEF);

Prog* Compiler::Compile(Regexp* re, bool reversed, int64_t max_mem) {
  g_last_re       = re;
  g_last_reversed = reversed;
  g_last_max_mem  = max_mem;
  return g_return_prog;
}

}  // namespace re2

namespace {

using namespace re2;

class CompileToProgTest_327 : public ::testing::Test {
 protected:
  void SetUp() override {
    // Reset seam-observed values before each test.
    g_last_re       = nullptr;
    g_last_reversed = true;
    g_last_max_mem  = -1;
    g_return_prog   = reinterpret_cast<Prog*>(0xDEADBEEF);
  }

  // Helper to parse a simple pattern into a Regexp* using only the public API.
  Regexp* ParseSimple(const char* pat) {
    // Use zero flags; status can be null per public signature.
    return Regexp::Parse(pat, static_cast<Regexp::ParseFlags>(0), /*status=*/nullptr);
  }
};

// --- Tests ---

// Verifies that Regexp::CompileToProg forwards `this`, `reversed=false`, and `max_mem`
// to Compiler::Compile, and returns exactly what Compiler::Compile returns.
TEST_F(CompileToProgTest_327, ForwardsArgumentsAndReturnsCompilerResult_327) {
  Regexp* re = ParseSimple("a");
  ASSERT_NE(re, nullptr) << "Regexp::Parse returned null";

  const int64_t kMem = 12345;
  Prog* ret = re->CompileToProg(kMem);

  // Returned value should be exactly what our seam returns.
  EXPECT_EQ(ret, g_return_prog);

  // Interaction verification: the collaborator saw correct args.
  EXPECT_EQ(g_last_re, re);
  EXPECT_FALSE(g_last_reversed) << "CompileToProg must call Compiler::Compile with reversed=false";
  EXPECT_EQ(g_last_max_mem, kMem);

  re->Decref();  // clean up via public API
}

// If the external collaborator returns nullptr, CompileToProg should surface it unchanged.
TEST_F(CompileToProgTest_327, PropagatesNullWhenCompilerReturnsNull_327) {
  Regexp* re = ParseSimple("b");
  ASSERT_NE(re, nullptr);

  g_return_prog = nullptr;  // seam-controlled collaborator result

  Prog* ret = re->CompileToProg(0);
  EXPECT_EQ(ret, nullptr);

  // Still ensure the call was made with reversed=false and the provided max_mem.
  EXPECT_EQ(g_last_re, re);
  EXPECT_FALSE(g_last_reversed);
  EXPECT_EQ(g_last_max_mem, 0);

  re->Decref();
}

// Boundary: very large max_mem should be forwarded without truncation.
TEST_F(CompileToProgTest_327, ForwardsMaxInt64Boundary_327) {
  Regexp* re = ParseSimple("[0-9]+");
  ASSERT_NE(re, nullptr);

  const int64_t kMax = std::numeric_limits<int64_t>::max();
  Prog* ret = re->CompileToProg(kMax);
  (void)ret;  // we only care that call happens & args forwarded

  EXPECT_EQ(g_last_re, re);
  EXPECT_FALSE(g_last_reversed);
  EXPECT_EQ(g_last_max_mem, kMax);

  re->Decref();
}

// Sanity: the call should bind to the specific receiver ("this").
// Using two different Regexp instances should record the last one used.
TEST_F(CompileToProgTest_327, UsesCallingInstanceAsThis_327) {
  Regexp* re1 = ParseSimple("x");
  Regexp* re2 = ParseSimple("y");
  ASSERT_NE(re1, nullptr);
  ASSERT_NE(re2, nullptr);

  // First call from re1
  g_last_re = nullptr;
  (void)re1->CompileToProg(1);
  EXPECT_EQ(g_last_re, re1);

  // Second call from re2
  g_last_re = nullptr;
  (void)re2->CompileToProg(2);
  EXPECT_EQ(g_last_re, re2);
  EXPECT_FALSE(g_last_reversed);
  EXPECT_EQ(g_last_max_mem, 2);

  re1->Decref();
  re2->Decref();
}

}  // namespace
