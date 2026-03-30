// File: parse_state_finishregexp_test_482.cc

#include <gtest/gtest.h>

// The project headers as provided.
#include "re2/regexp.h"
// We include the .cc so the nested type (ParseState) and its method are visible.
// This keeps us from re-implementing anything while letting us call the real code.
#include "re2/parse.cc"

namespace re2 {

// Test suite for Regexp::ParseState::FinishRegexp
// NOTE: We never access private/internal state (like op_, down_, etc.).
// We only rely on observable inputs/outputs via the public or exposed fields
// that are part of the provided interface surface for this kata.

TEST(ParseStateFinishRegexpTest_482, ReturnsNullForNullInput_482) {
  Regexp::ParseState ps;  // Treat as black box; FinishRegexp doesn't depend on internal state for this case.
  Regexp* out = ps.FinishRegexp(nullptr);
  EXPECT_EQ(out, nullptr);
}

TEST(ParseStateFinishRegexpTest_482, ReturnsSamePointerWhenNonNull_482) {
  Regexp::ParseState ps;

  // Construct a minimal Regexp instance without assuming any internal logic.
  // We avoid touching private fields and only use publicly exposed members from the provided headers.
  Regexp re{};
  re.cc_ = nullptr;
  re.ccb_ = nullptr;

  Regexp* out = ps.FinishRegexp(&re);

  // Observables:
  // - Should return the same pointer when input is non-null.
  // - With no pending builder (ccb_ == nullptr), no externally visible changes to cc_/ccb_.
  EXPECT_EQ(out, &re);
  EXPECT_EQ(re.cc_, nullptr);
  EXPECT_EQ(re.ccb_, nullptr);
}

TEST(ParseStateFinishRegexpTest_482, LeavesBuilderUntouchedWhenNotACharClass_482) {
  Regexp::ParseState ps;

  // Set up a Regexp that holds a CharClassBuilder pointer.
  // We do NOT (and cannot) set internal opcode; we only assert behavior that
  // is observable without depending on private state.
  Regexp re{};
  auto* builder = new CharClassBuilder();
  re.cc_ = nullptr;
  re.ccb_ = builder;

  Regexp* out = ps.FinishRegexp(&re);

  // Observable expectations that do not rely on internal op_:
  // If the implementation decides not to consume the builder (e.g., not a char class),
  // it must at least preserve inputs and still return the same pointer.
  EXPECT_EQ(out, &re);
  EXPECT_EQ(re.ccb_, builder);  // Still owned here if not consumed by FinishRegexp.
  EXPECT_EQ(re.cc_, nullptr);

  // Clean up in test to avoid leaking the test-allocated builder.
  delete builder;
}

}  // namespace re2
