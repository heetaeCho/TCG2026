// TEST_ID: 21
#include <gtest/gtest.h>

#include <string>

#include "./TestProjects/poppler/goo/GooString.h"

// The provided partial interface shows:
//   class GooString { public: std::string &toNonConstStr() { return *this; } };
// We treat it as a black box and only verify observable behavior via the returned reference.

namespace {

class GooStringTest_21 : public ::testing::Test {};

TEST_F(GooStringTest_21, ReturnsLvalueReferenceToStdString_21) {
  GooString s("hello");
  std::string& ref = s.toNonConstStr();

  // Must be an lvalue ref (compile-time) and should expose the same contents.
  static_assert(std::is_lvalue_reference_v<decltype(ref)>, "Expected lvalue reference");
  EXPECT_EQ(ref, "hello");
}

TEST_F(GooStringTest_21, ReturnedReferenceAllowsMutationAndPersists_21) {
  GooString s("abc");

  std::string& ref = s.toNonConstStr();
  ref += "def";

  // If the returned reference aliases the underlying string, subsequent calls should see the change.
  EXPECT_EQ(s.toNonConstStr(), "abcdef");
}

TEST_F(GooStringTest_21, MultipleCallsReturnSameAliasingReference_21) {
  GooString s("x");

  std::string& r1 = s.toNonConstStr();
  std::string& r2 = s.toNonConstStr();

  // Observable aliasing: changing through one reference should be visible through the other.
  r1.push_back('y');
  EXPECT_EQ(r2, "xy");

  // Also check they are the same object (address comparison is an observable property of references).
  EXPECT_EQ(&r1, &r2);
}

TEST_F(GooStringTest_21, WorksOnEmptyStringBoundary_21) {
  GooString s("");

  std::string& ref = s.toNonConstStr();
  EXPECT_TRUE(ref.empty());

  // Boundary: mutate from empty.
  ref.push_back('a');
  EXPECT_EQ(s.toNonConstStr(), "a");
}

TEST_F(GooStringTest_21, NoThrowForTypicalUsage_21) {
  GooString s("safe");
  EXPECT_NO_THROW({
    std::string& ref = s.toNonConstStr();
    ref.append("!");
  });
  EXPECT_EQ(s.toNonConstStr(), "safe!");
}

}  // namespace