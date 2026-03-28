// File: pcre_consume_functor_test.cc
#include <gtest/gtest.h>
#include "re2/util/pcre.h"

using re2::PCRE;

namespace {

// Helper to provide 16 default Arg objects (we cannot rely on no_more_args sentinel)
struct SixteenArgs {
  PCRE::Arg a0, a1, a2, a3, a4, a5, a6, a7,
            a8, a9, a10, a11, a12, a13, a14, a15;
};

}  // namespace

// Normal operation: when a prefix matches, input is advanced by the matched length.
TEST(PCRE_ConsumeFunctorTest_191, ConsumesOnPrefixMatch_191) {
  PCRE pattern(std::string("abc"));   // treat as black box
  PCRE::ConsumeFunctor functor;
  SixteenArgs args;

  absl::string_view input("abcdef");
  absl::string_view original = input;

  const bool ok = functor(&input, pattern,
                          args.a0, args.a1, args.a2, args.a3, args.a4, args.a5, args.a6, args.a7,
                          args.a8, args.a9, args.a10, args.a11, args.a12, args.a13, args.a14, args.a15);

  EXPECT_TRUE(ok);
  // Observable effect: input was advanced by the consumed prefix.
  // We can't inspect 'consumed', but the new input should equal the suffix after "abc".
  EXPECT_EQ(input, absl::string_view("def"));
  // And length must be shorter than the original.
  EXPECT_LT(input.size(), original.size());
}

// Failure leaves input unchanged.
TEST(PCRE_ConsumeFunctorTest_191, NoConsumeOnNoMatch_191) {
  PCRE pattern(std::string("xyz"));
  PCRE::ConsumeFunctor functor;
  SixteenArgs args;

  absl::string_view input("abcdef");
  absl::string_view before = input;

  const bool ok = functor(&input, pattern,
                          args.a0, args.a1, args.a2, args.a3, args.a4, args.a5, args.a6, args.a7,
                          args.a8, args.a9, args.a10, args.a11, args.a12, args.a13, args.a14, args.a15);

  EXPECT_FALSE(ok);
  // Observable effect: input remains unchanged on failure.
  EXPECT_EQ(input, before);
}

// Anchoring behavior: operator() uses ANCHOR_START internally.
// A pattern that would match only after the first character should not consume.
TEST(PCRE_ConsumeFunctorTest_191, AnchoredAtStart_NoMiddleMatch_191) {
  PCRE pattern(std::string("bc"));  // would match at position 1 if unanchored
  PCRE::ConsumeFunctor functor;
  SixteenArgs args;

  absl::string_view input("abcdef");
  absl::string_view before = input;

  const bool ok = functor(&input, pattern,
                          args.a0, args.a1, args.a2, args.a3, args.a4, args.a5, args.a6, args.a7,
                          args.a8, args.a9, args.a10, args.a11, args.a12, args.a13, args.a14, args.a15);

  EXPECT_FALSE(ok);
  EXPECT_EQ(input, before);  // no consumption because match is not at start
}

// Boundary-ish case: ensure consumption length equals full matched prefix, even with groups.
// (We do not assert group contents; just that successful match consumes exactly the prefix.)
TEST(PCRE_ConsumeFunctorTest_191, ConsumesEntireMatchedPrefix_WithGroups_191) {
  PCRE pattern(std::string("(ab)(cd)"));
  PCRE::ConsumeFunctor functor;
  SixteenArgs args;

  absl::string_view input("abcdZ");
  const bool ok = functor(&input, pattern,
                          args.a0, args.a1, args.a2, args.a3, args.a4, args.a5, args.a6, args.a7,
                          args.a8, args.a9, args.a10, args.a11, args.a12, args.a13, args.a14, args.a15);

  EXPECT_TRUE(ok);
  // After matching "abcd" at the start, the remaining input should be "Z".
  EXPECT_EQ(input, absl::string_view("Z"));
}

// Stress the call shape: providing all 16 Arg parameters should still behave correctly.
TEST(PCRE_ConsumeFunctorTest_191, AcceptsSixteenArgs_AndConsumes_191) {
  PCRE pattern(std::string("hello"));
  PCRE::ConsumeFunctor functor;
  SixteenArgs args;  // 16 args passed; we don't rely on sentinel visibility.

  absl::string_view input("hello world");
  const bool ok = functor(&input, pattern,
                          args.a0, args.a1, args.a2, args.a3, args.a4, args.a5, args.a6, args.a7,
                          args.a8, args.a9, args.a10, args.a11, args.a12, args.a13, args.a14, args.a15);

  EXPECT_TRUE(ok);
  EXPECT_EQ(input, absl::string_view(" world"));
}

