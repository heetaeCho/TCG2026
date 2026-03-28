// File: prog_compile_set_test_331.cc

#include <gtest/gtest.h>
#include <cstdint>

//
// Minimal forward declarations to avoid depending on internal details.
// We only declare the types and the exact function signature we interact with.
//
namespace re2 {

class RE2 {
public:
  // Values themselves are irrelevant for black-box testing;
  // we just need a well-typed enum to pass through.
  enum Anchor { UNANCHORED = 0, ANCHOR_START = 1, ANCHOR_BOTH = 2 };
};

class Regexp;       // opaque to tests
class Prog;         // opaque to tests

// Dependency seam: declaration matches the production signature.
class Compiler {
public:
  static Prog* CompileSet(Regexp* re, RE2::Anchor anchor, int64_t max_mem);
};

// SUT method we are testing lives on Prog. We don't re-implement Prog;
// we just need the member function declaration to compile calls in tests.
class Prog {
public:
  Prog* CompileSet(Regexp* re, RE2::Anchor anchor, int64_t max_mem);
};

} // namespace re2

//
// ---- Test Double for the dependency: Compiler::CompileSet ----
// We define a replacement with the same signature to capture calls
// and control the return value. This does NOT simulate internal logic;
// it only records the interaction.
//
namespace re2 {
namespace test_double_331 {

static Regexp*        g_last_re             = nullptr;
static RE2::Anchor    g_last_anchor         = RE2::UNANCHORED;
static int64_t        g_last_max_mem        = 0;
static int            g_call_count          = 0;
static Prog*          g_return_prog         = nullptr;

static void Reset() {
  g_last_re      = nullptr;
  g_last_anchor  = RE2::UNANCHORED;
  g_last_max_mem = 0;
  g_call_count   = 0;
  g_return_prog  = nullptr;
}

} // namespace test_double_331

// Replacement definition for the dependency under test.
// This captures parameters and returns a pre-set pointer.
Prog* Compiler::CompileSet(Regexp* re, RE2::Anchor anchor, int64_t max_mem) {
  using namespace test_double_331;
  g_last_re      = re;
  g_last_anchor  = anchor;
  g_last_max_mem = max_mem;
  ++g_call_count;
  return g_return_prog;
}

} // namespace re2

//
// ------------------------------ Tests ------------------------------
// IMPORTANT: We never touch internal state of Prog. We only:
//  - Call Prog::CompileSet()
//  - Verify that Compiler::CompileSet() was invoked with the same arguments
//  - Verify that the return pointer from Compiler::CompileSet() is forwarded
//
// NOTE: Since Prog is opaque, we don't construct a real instance.
//       The wrapper does not use 'this', so we safely call it on a
//       dummy pointer to the opaque type (no dereference).
//

using re2::RE2;
using re2::Regexp;
using re2::Prog;

class Prog_CompileSet_Test_331 : public ::testing::Test {
protected:
  void SetUp() override {
    re2::test_double_331::Reset();
  }

  // Helper to invoke SUT with a dummy 'this' pointer.
  Prog* CallCompileSet(Regexp* re, RE2::Anchor anchor, int64_t max_mem) {
    // Create a dummy 'this' pointer; the wrapper shouldn't touch it.
    Prog* dummy_this = reinterpret_cast<Prog*>(0x1);
    return dummy_this->CompileSet(re, anchor, max_mem);
  }
};

// Verifies that Prog::CompileSet forwards all parameters exactly as-is.
TEST_F(Prog_CompileSet_Test_331, ForwardsParameters_331) {
  Regexp* re_in = reinterpret_cast<Regexp*>(0xABC);
  RE2::Anchor anchor_in = RE2::ANCHOR_START;
  int64_t max_mem_in = 123456789LL;

  (void)CallCompileSet(re_in, anchor_in, max_mem_in);

  using namespace re2::test_double_331;
  EXPECT_EQ(g_call_count, 1);
  EXPECT_EQ(g_last_re, re_in);
  EXPECT_EQ(g_last_anchor, anchor_in);
  EXPECT_EQ(g_last_max_mem, max_mem_in);
}

// Verifies that the return value from Compiler::CompileSet is forwarded unchanged.
TEST_F(Prog_CompileSet_Test_331, ReturnsDependencyResult_331) {
  // Arrange the dependency to return a specific pointer.
  Prog* expected = reinterpret_cast<Prog*>(0xDEADBEEF);
  re2::test_double_331::g_return_prog = expected;

  Regexp* any_re = reinterpret_cast<Regexp*>(0x1);
  Prog* got = CallCompileSet(any_re, RE2::UNANCHORED, /*max_mem=*/0);

  EXPECT_EQ(got, expected);
}

// Verifies that nullptr return from the dependency is forwarded verbatim.
TEST_F(Prog_CompileSet_Test_331, ForwardsNullReturn_331) {
  re2::test_double_331::g_return_prog = nullptr;

  Regexp* any_re = reinterpret_cast<Regexp*>(0x2);
  Prog* got = CallCompileSet(any_re, RE2::ANCHOR_BOTH, /*max_mem=*/-1);

  EXPECT_EQ(got, nullptr);
}

// Smoke: different anchor values flow through unchanged.
// (Catches accidental hard-coding or enum mishandling.)
TEST_F(Prog_CompileSet_Test_331, AnchorValuesArePassedThrough_331) {
  Regexp* any_re = reinterpret_cast<Regexp*>(0x3);

  // Case 1: UNANCHORED
  re2::test_double_331::Reset();
  (void)CallCompileSet(any_re, RE2::UNANCHORED, 10);
  EXPECT_EQ(re2::test_double_331::g_last_anchor, RE2::UNANCHORED);

  // Case 2: ANCHOR_START
  re2::test_double_331::Reset();
  (void)CallCompileSet(any_re, RE2::ANCHOR_START, 20);
  EXPECT_EQ(re2::test_double_331::g_last_anchor, RE2::ANCHOR_START);

  // Case 3: ANCHOR_BOTH
  re2::test_double_331::Reset();
  (void)CallCompileSet(any_re, RE2::ANCHOR_BOTH, 30);
  EXPECT_EQ(re2::test_double_331::g_last_anchor, RE2::ANCHOR_BOTH);
}
