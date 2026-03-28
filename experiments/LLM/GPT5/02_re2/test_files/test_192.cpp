// File: pcre_find_and_consume_functor_test.cc

#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include <string>
#include "TestProjects/re2/util/pcre.h"      // re2::PCRE, re2::PCRE::Arg, re2::PCRE::FindAndConsumeFunctor
#include "absl/strings/string_view.h"

using ::testing::Eq;
using ::testing::Ne;
using ::testing::Gt;

namespace re2 {

class FindAndConsumeFunctorTest_192 : public ::testing::Test {
 protected:
  // Helper to build a vector of default Args (we do not rely on internal parsing).
  static void FillDefaultArgs(PCRE::Arg* out, size_t n) {
    for (size_t i = 0; i < n; ++i) out[i] = PCRE::Arg();
  }
};

// Normal operation: when the pattern matches, operator() should return true
// and advance the input by the consumed length (observable via input mutation).
TEST_F(FindAndConsumeFunctorTest_192, MatchAdvancesInputAndReturnsTrue_192) {
  // Arrange
  // Choose a very simple pattern that should match a non-empty prefix in common PCRE syntax.
  // We do not assume implementation details; we only verify observable effects.
  PCRE pattern("(\\w+)");
  absl::string_view input_sv = "abc123_xyz";
  std::string backing = std::string(input_sv);  // we need a stable buffer for string_view
  absl::string_view input(backing);

  PCRE::FindAndConsumeFunctor functor;

  // Provide 16 default Args (we don't depend on capture parsing).
  PCRE::Arg a[16];
  FillDefaultArgs(a, 16);

  // Act
  const bool ok = functor(&input, pattern,
                          a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                          a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);

  // Assert: On success, input must be advanced (strictly smaller) and return true.
  EXPECT_TRUE(ok);
  EXPECT_LT(input.size(), backing.size());          // consumed > 0
  // Since the pattern is UNANCHORED internally, the first token "abc123" should be consumed
  // if the implementation consumes matched prefix. We only assert that the result starts
  // somewhere after the beginning. A strong-but-still-black-box check is that the remaining
  // view equals the suffix after the first run of word chars.
  // "abc123_xyz" => expected remainder "_xyz".
  // If the implementation differs but still advances, the first EXPECT_LT above still holds.
  EXPECT_THAT(std::string(input), Eq(std::string("_xyz")));
}

// No match case: when the pattern does not match anywhere, operator() should return false
// and must NOT mutate input.
TEST_F(FindAndConsumeFunctorTest_192, NoMatchKeepsInputAndReturnsFalse_192) {
  // Arrange
  PCRE pattern("ZZZ");   // unlikely to be found in the input below
  std::string backing = "abc123_xyz";
  absl::string_view input(backing);

  PCRE::FindAndConsumeFunctor functor;

  PCRE::Arg a[16];
  FillDefaultArgs(a, 16);

  // Act
  absl::string_view before = input;
  const bool ok = functor(&input, pattern,
                          a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                          a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);

  // Assert
  EXPECT_FALSE(ok);
  EXPECT_EQ(input.data(), before.data());  // start pointer unchanged
  EXPECT_EQ(input.size(), before.size());  // length unchanged
  EXPECT_THAT(std::string(input), Eq(backing));
}

// Boundary-style usage: pass the maximum number of Arg parameters (16) and
// verify that a successful match still advances input (no crash / misuse of args array).
TEST_F(FindAndConsumeFunctorTest_192, HandlesMaximumArgsWithoutFailing_192) {
  // Arrange
  PCRE pattern("(abc)");   // simple literal to keep expectations reasonable
  std::string backing = "abc_tail";
  absl::string_view input(backing);

  PCRE::FindAndConsumeFunctor functor;

  // Provide 16 Args explicitly, with mixed default-constructed values.
  PCRE::Arg a0, a1, a2, a3, a4, a5, a6, a7, a8, a9, a10, a11, a12, a13, a14, a15;

  // Act
  const bool ok = functor(&input, pattern,
                          a0, a1, a2, a3, a4, a5, a6, a7,
                          a8, a9, a10, a11, a12, a13, a14, a15);

  // Assert: should succeed and advance (observable effect only).
  EXPECT_TRUE(ok);
  EXPECT_THAT(input.size(), Lt(backing.size()));
  // If the engine consumed "abc", the remainder should start with "_tail".
  EXPECT_THAT(std::string(input), Eq(std::string("_tail")));
}

// Regression-style behavior check: If the pattern can match an empty string,
// verify that the observable contract still holds: return value indicates success,
// and input is advanced by exactly the consumed amount (which may be zero).
TEST_F(FindAndConsumeFunctorTest_192, EmptyMatchDoesNotAdvanceInput_IfConsumedZero_192) {
  // Arrange
  PCRE pattern(".*");  // commonly can match empty at the first position
  std::string backing = "data";
  absl::string_view input(backing);

  PCRE::FindAndConsumeFunctor functor;

  PCRE::Arg a[16];
  FillDefaultArgs(a, 16);

  // Act
  const bool ok = functor(&input, pattern,
                          a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7],
                          a[8], a[9], a[10], a[11], a[12], a[13], a[14], a[15]);

  // Assert
  // We only assert what is observable: success boolean, and that input is either unchanged
  // (if consumed==0) or shortened (if implementation consumes the maximal match).
  EXPECT_TRUE(ok);
  // Accept either unchanged or shortened input; both are valid observable outcomes
  // depending on how consumed is defined internally. We ensure it never grows.
  EXPECT_LE(input.size(), backing.size());
}

}  // namespace re2
