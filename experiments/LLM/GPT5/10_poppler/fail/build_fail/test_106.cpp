// Object_getRefGen_test_106.cpp
#include <gtest/gtest.h>

#include <climits>
#include <type_traits>
#include <utility>

#include "poppler/Object.h"

namespace {

class ObjectGetRefGenTest_106 : public ::testing::Test {};

// Helper: create a ref Object if the concrete header supports it.
// If not supported, tests will GTEST_SKIP (still compiling cleanly).
static Object MakeRefObjectOrSkip_106(int num, int gen) {
  // Common Poppler patterns across versions: construct from Ref or from (num, gen).
  if constexpr (std::is_constructible_v<Ref, int, int>) {
    if constexpr (std::is_constructible_v<Object, Ref>) {
      Ref r{num, gen};
      return Object(r);
    }
  }
  if constexpr (std::is_constructible_v<Object, int, int>) {
    return Object(num, gen);
  }

  // If neither is available, we can't produce an objRef through the public API shown.
  GTEST_SKIP() << "Cannot construct an objRef Object with the available public constructors in this build.";
#if defined(__GNUC__) || defined(__clang__)
  __builtin_unreachable();
#else
  return Object();  // Unreached, but keeps compilers happy.
#endif
}

TEST_F(ObjectGetRefGenTest_106, ReturnsGenerationForRefObject_106) {
  Object obj = MakeRefObjectOrSkip_106(123, 7);
  ASSERT_TRUE(obj.isRef());
  EXPECT_EQ(obj.getRefGen(), 7);
}

TEST_F(ObjectGetRefGenTest_106, ReturnsZeroGenerationWhenGenIsZero_106) {
  Object obj = MakeRefObjectOrSkip_106(1, 0);
  ASSERT_TRUE(obj.isRef());
  EXPECT_EQ(obj.getRefGen(), 0);
}

TEST_F(ObjectGetRefGenTest_106, ReturnsLargeGenerationValue_106) {
  Object obj = MakeRefObjectOrSkip_106(1, INT_MAX);
  ASSERT_TRUE(obj.isRef());
  EXPECT_EQ(obj.getRefGen(), INT_MAX);
}

TEST_F(ObjectGetRefGenTest_106, MovePreservesGeneration_106) {
  Object original = MakeRefObjectOrSkip_106(55, 42);
  ASSERT_TRUE(original.isRef());

  Object moved(std::move(original));
  ASSERT_TRUE(moved.isRef());
  EXPECT_EQ(moved.getRefGen(), 42);
}

TEST_F(ObjectGetRefGenTest_106, MoveAssignmentPreservesGeneration_106) {
  Object src = MakeRefObjectOrSkip_106(77, 9);
  ASSERT_TRUE(src.isRef());

  Object dst; // non-ref default
  dst = std::move(src);

  ASSERT_TRUE(dst.isRef());
  EXPECT_EQ(dst.getRefGen(), 9);
}

#if GTEST_HAS_DEATH_TEST
// getRefGen() is guarded by OBJECT_TYPE_CHECK(objRef). In many Poppler builds this
// is an assert/abort in debug builds. We only run death expectations when assertions
// are likely enabled to keep the suite portable.
#ifndef NDEBUG
TEST_F(ObjectGetRefGenTest_106, DiesWhenCalledOnNonRefObject_106) {
  Object nonRef(123); // objInt
  ASSERT_FALSE(nonRef.isRef());

  EXPECT_DEATH(
      {
        (void)nonRef.getRefGen();
      },
      "");
}
#endif  // !NDEBUG
#endif  // GTEST_HAS_DEATH_TEST

} // namespace