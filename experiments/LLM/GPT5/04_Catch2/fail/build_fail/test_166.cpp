// File: match_not_of_generic_test_166.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/matchers/catch_matchers_templated.hpp"

using ::testing::_;
using ::testing::Eq;
using ::testing::Return;

namespace Detail = Catch::Matchers::Detail;

// --- Test doubles (external collaborators to be mocked) ---

// For int arguments
struct MockIntMatcher {
  MOCK_METHOD(bool, match, (const int&), (const));
};

// For std::string arguments
struct MockStringMatcher {
  MOCK_METHOD(bool, match, (const std::string&), (const));
};

// For a user-defined type to verify template acceptance
struct Widget {
  int value{};
  bool operator==(const Widget& other) const { return value == other.value; }
};

struct MockWidgetMatcher {
  MOCK_METHOD(bool, match, (const Widget&), (const));
};

// --- Tests ---

// Normal operation: when inner matcher returns true, NOT-of should return false.
TEST(MatchNotOfGenericTest_166, TrueIsNegatedToFalse_166) {
  MockIntMatcher inner;
  EXPECT_CALL(inner, match(Eq(42)))
      .Times(1)
      .WillOnce(Return(true));

  Detail::MatchNotOfGeneric<MockIntMatcher> uut(inner);
  EXPECT_FALSE(uut.match(42));
}

// Normal operation: when inner matcher returns false, NOT-of should return true.
TEST(MatchNotOfGenericTest_166, FalseIsNegatedToTrue_166) {
  MockIntMatcher inner;
  EXPECT_CALL(inner, match(Eq(-7)))
      .Times(1)
      .WillOnce(Return(false));

  Detail::MatchNotOfGeneric<MockIntMatcher> uut(inner);
  EXPECT_TRUE(uut.match(-7));
}

// Interaction verification: underlying match() is invoked exactly once with the forwarded argument.
TEST(MatchNotOfGenericTest_166, CallsUnderlyingExactlyOnce_166) {
  MockIntMatcher inner;
  EXPECT_CALL(inner, match(Eq(7)))
      .Times(1)
      .WillOnce(Return(false));  // value doesn't matter for this test; we check call count and param

  Detail::MatchNotOfGeneric<MockIntMatcher> uut(inner);
  // Should call inner.match(7) once
  (void)uut.match(7);
}

// Type-generic behavior: works with std::string and respects const-correctness.
TEST(MatchNotOfGenericTest_166, AcceptsConstAndRvalueArgs_String_166) {
  MockStringMatcher inner;
  const std::string lvalue = "hello";
  EXPECT_CALL(inner, match(Eq(lvalue)))
      .WillOnce(Return(true));   // NOT-of -> false
  EXPECT_CALL(inner, match(Eq(std::string("world"))))
      .WillOnce(Return(false));  // NOT-of -> true

  const Detail::MatchNotOfGeneric<MockStringMatcher> uut(inner); // verify match() is const
  EXPECT_FALSE(uut.match(lvalue));            // const lvalue
  EXPECT_TRUE(uut.match(std::string("world"))); // rvalue
}

// Type-generic behavior: works with a user-defined type (no assumptions on internals).
TEST(MatchNotOfGenericTest_166, AcceptsUserDefinedType_166) {
  MockWidgetMatcher inner;
  Widget w{123};
  EXPECT_CALL(inner, match(Eq(w))).WillOnce(Return(true)); // NOT-of -> false

  Detail::MatchNotOfGeneric<MockWidgetMatcher> uut(inner);
  EXPECT_FALSE(uut.match(w));
}

// Boundary-ish API properties we can check without peeking inside:
// - Deleted copy-ctor and defaulted move-ctor (from the provided interface snippet).
// These are compile-time properties; static_asserts live inside a test TU.
TEST(MatchNotOfGenericTest_166, TypeTraits_MoveConstructible_NotCopyConstructible_166) {
  using NotInt = Detail::MatchNotOfGeneric<MockIntMatcher>;
  static_assert(std::is_move_constructible<NotInt>::value, "Should be move-constructible");
  static_assert(!std::is_copy_constructible<NotInt>::value, "Copy-ctor should be deleted");
}
