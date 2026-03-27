// File: ./TestProjects/yaml-cpp/test/ptr_vector_test_70.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <string>
#include <type_traits>
#include <utility>

#include "ptr_vector.h"  // ./TestProjects/yaml-cpp/src/ptr_vector.h

namespace {

struct Widget70 {
  int value{};
  std::string name;
  explicit Widget70(int v = 0, std::string n = {}) : value(v), name(std::move(n)) {}
};

using Vec70 = YAML::ptr_vector<Widget70>;

}  // namespace

// Compile-time interface/semantic checks (observable at type level).
TEST(PtrVectorTest_70, TypeTraits_CopyDisabledMoveEnabled_70) {
  static_assert(!std::is_copy_constructible_v<Vec70>, "ptr_vector should be non-copyable");
  static_assert(!std::is_copy_assignable_v<Vec70>, "ptr_vector should be non-copy-assignable");
  static_assert(std::is_move_constructible_v<Vec70>, "ptr_vector should be move-constructible");
  static_assert(std::is_move_assignable_v<Vec70>, "ptr_vector should be move-assignable");
  SUCCEED();
}

TEST(PtrVectorTest_70, DefaultConstructedIsEmpty_70) {
  Vec70 v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(PtrVectorTest_70, PushBackIncreasesSizeAndNotEmpty_70) {
  Vec70 v;
  v.push_back(std::make_unique<Widget70>(1, "a"));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 1u);

  v.push_back(std::make_unique<Widget70>(2, "b"));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 2u);
}

TEST(PtrVectorTest_70, OperatorIndexReturnsReferenceToStoredObject_70) {
  Vec70 v;
  v.push_back(std::make_unique<Widget70>(10, "x"));
  v.push_back(std::make_unique<Widget70>(20, "y"));

  Widget70& w0 = v[0];
  Widget70& w1 = v[1];

  EXPECT_EQ(w0.value, 10);
  EXPECT_EQ(w0.name, "x");
  EXPECT_EQ(w1.value, 20);
  EXPECT_EQ(w1.name, "y");

  // Must be references to distinct elements.
  EXPECT_NE(&w0, &w1);
}

TEST(PtrVectorTest_70, OperatorIndexAllowsMutationThroughReference_70) {
  Vec70 v;
  v.push_back(std::make_unique<Widget70>(5, "before"));

  v[0].value = 99;
  v[0].name = "after";

  EXPECT_EQ(v[0].value, 99);
  EXPECT_EQ(v[0].name, "after");
}

TEST(PtrVectorTest_70, BackReturnsLastElement_70) {
  Vec70 v;
  v.push_back(std::make_unique<Widget70>(1, "first"));
  v.push_back(std::make_unique<Widget70>(2, "second"));
  v.push_back(std::make_unique<Widget70>(3, "third"));

  Widget70& b = v.back();
  EXPECT_EQ(b.value, 3);
  EXPECT_EQ(b.name, "third");

  // If we mutate back(), the change should be visible when indexing last element.
  b.value = 777;
  EXPECT_EQ(v[2].value, 777);
}

TEST(PtrVectorTest_70, ClearEmptiesVectorAndResetsSize_70) {
  Vec70 v;
  v.push_back(std::make_unique<Widget70>(1, "a"));
  v.push_back(std::make_unique<Widget70>(2, "b"));
  ASSERT_EQ(v.size(), 2u);
  ASSERT_FALSE(v.empty());

  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);

  // Clearing an already-empty vector should still be safe and keep it empty.
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST(PtrVectorTest_70, MoveConstructTransfersContents_70) {
  Vec70 src;
  src.push_back(std::make_unique<Widget70>(11, "one"));
  src.push_back(std::make_unique<Widget70>(22, "two"));
  ASSERT_EQ(src.size(), 2u);

  Vec70 dst(std::move(src));

  EXPECT_EQ(dst.size(), 2u);
  EXPECT_FALSE(dst.empty());
  EXPECT_EQ(dst[0].value, 11);
  EXPECT_EQ(dst[0].name, "one");
  EXPECT_EQ(dst[1].value, 22);
  EXPECT_EQ(dst[1].name, "two");

  // The moved-from object should remain in a valid, usable state; at minimum, it
  // should support clear()/empty()/size() without crashing.
  EXPECT_NO_THROW(src.clear());
  EXPECT_TRUE(src.empty());
  EXPECT_EQ(src.size(), 0u);
}

TEST(PtrVectorTest_70, MoveAssignTransfersContentsAndOverwritesDestination_70) {
  Vec70 a;
  a.push_back(std::make_unique<Widget70>(1, "a1"));
  a.push_back(std::make_unique<Widget70>(2, "a2"));

  Vec70 b;
  b.push_back(std::make_unique<Widget70>(9, "b1"));
  ASSERT_EQ(b.size(), 1u);

  b = std::move(a);

  EXPECT_EQ(b.size(), 2u);
  EXPECT_EQ(b[0].value, 1);
  EXPECT_EQ(b[0].name, "a1");
  EXPECT_EQ(b[1].value, 2);
  EXPECT_EQ(b[1].name, "a2");

  // Moved-from should still be valid and clearable.
  EXPECT_NO_THROW(a.clear());
  EXPECT_TRUE(a.empty());
  EXPECT_EQ(a.size(), 0u);
}

// Boundary/“error” cases (observable via interface).
// We cannot assume whether operator[] checks bounds or not; instead we verify
// safe behavior in a controlled way using death tests only when supported.
// If the implementation uses unchecked operator[], out-of-range is UB and this
// test may be unreliable; therefore we keep it guarded and non-fatal.
#ifdef GTEST_HAS_DEATH_TEST
TEST(PtrVectorDeathTest_70, OperatorIndexOutOfRangeMayDie_70) {
  Vec70 v;
  v.push_back(std::make_unique<Widget70>(1, "x"));

  // If ptr_vector uses std::vector::at or asserts internally, this may terminate.
  // If it is unchecked, accessing out of range is undefined; this death test is
  // provided as a best-effort "exceptional" coverage and is skipped on platforms
  // where it can't be made reliable.
#if !defined(NDEBUG)
  EXPECT_DEATH(
      {
        // Volatile index to discourage compile-time optimization.
        volatile std::size_t idx = 999;
        (void)v[idx];
      },
      ".*");
#else
  GTEST_SKIP() << "Skipping death test in release builds (NDEBUG).";
#endif
}
#endif
