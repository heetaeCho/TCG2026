// File: ./TestProjects/re2/re2/tests/compiler_shortvisit_test_318.cc

#include "gtest/gtest.h"
#include "re2/compile.h"   // Assumes this exposes re2::Compiler, re2::Regexp (decl), etc.

namespace re2 {

class CompilerShortVisitTest_318 : public ::testing::Test {
protected:
  Compiler c_;
};

// [318] Normal operation: calling ShortVisit should mark the compiler as failed.
TEST_F(CompilerShortVisitTest_318, ShortVisit_SetsFailedFlag_318) {
  // Arrange
  // We can't (and won't) depend on internal Frag structure; pass a default-initialized value.
  Frag any_frag = Frag();  // Treat as opaque.
  Regexp* any_re = nullptr;  // We're not asserting on re; ShortVisit treats impl as black box.

  // Precondition sanity: if there is a public failed() accessor, it should start false.
  // We only assert postcondition (observable) after call.
  // Act
  Frag out = c_.ShortVisit(any_re, any_frag);

  // Assert
  // Observable behavior: the compiler moves into a failed state.
  // (We intentionally do not assert on 'out' structure since it's not part of a stable public contract.)
  EXPECT_TRUE(c_.failed()) << "ShortVisit should set the compiler into a failed state.";
}

// [318] Boundary: nullptr Regexp argument should be handled (no crash) and still mark failed.
TEST_F(CompilerShortVisitTest_318, ShortVisit_NullptrRegexp_SetsFailed_318) {
  Frag any_frag = Frag();

  Frag out = c_.ShortVisit(nullptr, any_frag);

  EXPECT_TRUE(c_.failed());
  (void)out;  // Silence unused warning without asserting internal structure.
}

// [318] Idempotence on failure: multiple calls keep (or leave) the compiler in a failed state.
TEST_F(CompilerShortVisitTest_318, ShortVisit_MultipleCalls_RemainsFailed_318) {
  Frag any_frag = Frag();

  // First call transitions to failed.
  (void)c_.ShortVisit(nullptr, any_frag);
  EXPECT_TRUE(c_.failed()) << "Compiler should be failed after first ShortVisit.";

  // Second call should not "un-fail" the state.
  (void)c_.ShortVisit(nullptr, any_frag);
  EXPECT_TRUE(c_.failed()) << "Compiler should remain failed after subsequent ShortVisit.";
}

}  // namespace re2
