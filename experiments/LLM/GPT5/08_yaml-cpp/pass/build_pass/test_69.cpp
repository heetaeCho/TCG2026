// File: ptr_vector_test_69.cpp
#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <type_traits>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"

namespace {

struct IntBox {
  explicit IntBox(int v) : value(v) {}
  int value;
};

using YAML::ptr_vector;

class PtrVectorTest_69 : public ::testing::Test {};

TEST_F(PtrVectorTest_69, TypeTraits_CopyIsDeleted_MoveIsEnabled_69) {
  static_assert(!std::is_copy_constructible_v<ptr_vector<IntBox>>,
                "ptr_vector should not be copy constructible");
  static_assert(!std::is_copy_assignable_v<ptr_vector<IntBox>>,
                "ptr_vector should not be copy assignable");

  static_assert(std::is_move_constructible_v<ptr_vector<IntBox>>,
                "ptr_vector should be move constructible");
  static_assert(std::is_move_assignable_v<ptr_vector<IntBox>>,
                "ptr_vector should be move assignable");
}

TEST_F(PtrVectorTest_69, DefaultConstructed_IsEmptyAndSizeZero_69) {
  ptr_vector<IntBox> v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(0));
}

TEST_F(PtrVectorTest_69, PushBack_MakesVectorNonEmptyAndIncrementsSize_69) {
  ptr_vector<IntBox> v;

  v.push_back(std::make_unique<IntBox>(1));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(1));

  v.push_back(std::make_unique<IntBox>(2));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(2));
}

TEST_F(PtrVectorTest_69, PushBack_PreservesElementOrder_OperatorIndexReturnsElements_69) {
  ptr_vector<IntBox> v;

  v.push_back(std::make_unique<IntBox>(10));
  v.push_back(std::make_unique<IntBox>(20));
  v.push_back(std::make_unique<IntBox>(30));

  EXPECT_EQ(v.size(), static_cast<std::size_t>(3));

  EXPECT_EQ(v[0].value, 10);
  EXPECT_EQ(v[1].value, 20);
  EXPECT_EQ(v[2].value, 30);
}

TEST_F(PtrVectorTest_69, Back_ReturnsLastElement_69) {
  ptr_vector<IntBox> v;

  v.push_back(std::make_unique<IntBox>(7));
  EXPECT_EQ(v.back().value, 7);

  v.push_back(std::make_unique<IntBox>(9));
  EXPECT_EQ(v.back().value, 9);
}

TEST_F(PtrVectorTest_69, Clear_RemovesAllElementsAndResetsSize_69) {
  ptr_vector<IntBox> v;

  v.push_back(std::make_unique<IntBox>(1));
  v.push_back(std::make_unique<IntBox>(2));
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), static_cast<std::size_t>(2));

  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(0));

  // Ensure it remains usable after clear.
  v.push_back(std::make_unique<IntBox>(3));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(1));
  EXPECT_EQ(v.back().value, 3);
}

TEST_F(PtrVectorTest_69, MoveConstruction_TransfersContents_69) {
  ptr_vector<IntBox> src;
  src.push_back(std::make_unique<IntBox>(11));
  src.push_back(std::make_unique<IntBox>(22));
  ASSERT_EQ(src.size(), static_cast<std::size_t>(2));

  ptr_vector<IntBox> dst(std::move(src));

  EXPECT_EQ(dst.size(), static_cast<std::size_t>(2));
  EXPECT_EQ(dst[0].value, 11);
  EXPECT_EQ(dst[1].value, 22);
  EXPECT_EQ(dst.back().value, 22);

  // Moved-from object should still be in a valid state for further operations.
  src.clear();
  src.push_back(std::make_unique<IntBox>(33));
  EXPECT_EQ(src.size(), static_cast<std::size_t>(1));
  EXPECT_EQ(src.back().value, 33);
}

TEST_F(PtrVectorTest_69, MoveAssignment_TransfersContentsAndOverwritesDestination_69) {
  ptr_vector<IntBox> src;
  src.push_back(std::make_unique<IntBox>(1));
  src.push_back(std::make_unique<IntBox>(2));

  ptr_vector<IntBox> dst;
  dst.push_back(std::make_unique<IntBox>(99));
  ASSERT_EQ(dst.size(), static_cast<std::size_t>(1));

  dst = std::move(src);

  EXPECT_EQ(dst.size(), static_cast<std::size_t>(2));
  EXPECT_EQ(dst[0].value, 1);
  EXPECT_EQ(dst[1].value, 2);

  // Moved-from object should still be usable.
  src.clear();
  EXPECT_TRUE(src.empty());
  src.push_back(std::make_unique<IntBox>(5));
  EXPECT_EQ(src.size(), static_cast<std::size_t>(1));
  EXPECT_EQ(src.back().value, 5);
}

TEST_F(PtrVectorTest_69, PushBack_AllowsMovingUniquePtrLvalue_69) {
  ptr_vector<IntBox> v;

  auto p = std::make_unique<IntBox>(123);
  IntBox* raw = p.get();

  v.push_back(std::move(p));

  EXPECT_EQ(v.size(), static_cast<std::size_t>(1));
  EXPECT_EQ(v.back().value, 123);
  // The unique_ptr should have been moved from.
  EXPECT_EQ(p.get(), nullptr);
  // And the stored object should be the same one that was moved.
  EXPECT_EQ(&v.back(), raw);
}

TEST_F(PtrVectorTest_69, PushBack_NullUniquePtr_IncreasesSizeAndKeepsContainerUsable_69) {
  ptr_vector<IntBox> v;

  std::unique_ptr<IntBox> nullp;
  v.push_back(std::move(nullp));

  EXPECT_EQ(v.size(), static_cast<std::size_t>(1));
  EXPECT_FALSE(v.empty());

  // Don't dereference element 0 (it may be null). Just ensure container remains usable.
  v.push_back(std::make_unique<IntBox>(77));
  EXPECT_EQ(v.size(), static_cast<std::size_t>(2));
  EXPECT_EQ(v.back().value, 77);
}

}  // namespace
