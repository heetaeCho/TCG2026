// File: ./TestProjects/yaml-cpp/test/ptr_vector_test_66.cpp

#include <gtest/gtest.h>

#include <cstddef>
#include <memory>
#include <type_traits>
#include <utility>

#include "ptr_vector.h"

namespace {

struct Item {
  explicit Item(int v) : value(v) {}
  int value;
};

using Vec = YAML::ptr_vector<Item>;

class PtrVectorTest_66 : public ::testing::Test {};

TEST_F(PtrVectorTest_66, DefaultConstructedIsEmpty_66) {
  Vec v;
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(0));
}

TEST_F(PtrVectorTest_66, PushBackMakesNonEmptyAndIncreasesSize_66) {
  Vec v;

  v.push_back(std::make_unique<Item>(10));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(1));

  v.push_back(std::make_unique<Item>(20));
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(2));
}

TEST_F(PtrVectorTest_66, OperatorIndexReturnsReferenceToStoredObject_66) {
  Vec v;

  auto p0 = std::make_unique<Item>(123);
  Item* raw0 = p0.get();
  v.push_back(std::move(p0));

  ASSERT_EQ(v.size(), static_cast<std::size_t>(1));
  EXPECT_EQ(&v[0], raw0);
  EXPECT_EQ(v[0].value, 123);

  v[0].value = 456;
  EXPECT_EQ(v[0].value, 456);
}

TEST_F(PtrVectorTest_66, BackReturnsLastElement_66) {
  Vec v;

  auto p0 = std::make_unique<Item>(1);
  Item* raw0 = p0.get();
  v.push_back(std::move(p0));

  EXPECT_EQ(&v.back(), raw0);
  EXPECT_EQ(v.back().value, 1);

  auto p1 = std::make_unique<Item>(2);
  Item* raw1 = p1.get();
  v.push_back(std::move(p1));

  EXPECT_EQ(&v.back(), raw1);
  EXPECT_EQ(v.back().value, 2);
}

TEST_F(PtrVectorTest_66, ClearEmptiesVectorAfterElementsAdded_66) {
  Vec v;

  v.push_back(std::make_unique<Item>(1));
  v.push_back(std::make_unique<Item>(2));
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), static_cast<std::size_t>(2));

  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(0));
}

TEST_F(PtrVectorTest_66, ClearOnEmptyIsSafeAndKeepsEmpty_66) {
  Vec v;
  ASSERT_TRUE(v.empty());

  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(0));

  // Call twice to exercise idempotence through the public interface.
  v.clear();
  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), static_cast<std::size_t>(0));
}

TEST_F(PtrVectorTest_66, MoveConstructorPreservesElementsInDestination_66) {
  Vec src;
  src.push_back(std::make_unique<Item>(7));
  src.push_back(std::make_unique<Item>(8));

  // Capture observable identities/values before move.
  Item* first_addr = &src[0];
  Item* second_addr = &src[1];

  Vec dst(std::move(src));

  EXPECT_EQ(dst.size(), static_cast<std::size_t>(2));
  EXPECT_EQ(&dst[0], first_addr);
  EXPECT_EQ(&dst[1], second_addr);
  EXPECT_EQ(dst[0].value, 7);
  EXPECT_EQ(dst[1].value, 8);

  // Moved-from object must remain valid; we only require it supports clear/empty/size.
  src.clear();
  EXPECT_TRUE(src.empty());
  EXPECT_EQ(src.size(), static_cast<std::size_t>(0));
}

TEST_F(PtrVectorTest_66, MoveAssignmentPreservesElementsInDestination_66) {
  Vec src;
  src.push_back(std::make_unique<Item>(11));
  src.push_back(std::make_unique<Item>(22));

  Item* a0 = &src[0];
  Item* a1 = &src[1];

  Vec dst;
  dst.push_back(std::make_unique<Item>(999));  // ensure destination had prior contents

  dst = std::move(src);

  EXPECT_EQ(dst.size(), static_cast<std::size_t>(2));
  EXPECT_EQ(&dst[0], a0);
  EXPECT_EQ(&dst[1], a1);
  EXPECT_EQ(dst[0].value, 11);
  EXPECT_EQ(dst[1].value, 22);

  // Moved-from remains valid; only require it supports clear/empty/size.
  src.clear();
  EXPECT_TRUE(src.empty());
  EXPECT_EQ(src.size(), static_cast<std::size_t>(0));
}

TEST_F(PtrVectorTest_66, CopyOperationsAreDeleted_66) {
  EXPECT_FALSE((std::is_copy_constructible_v<Vec>));
  EXPECT_FALSE((std::is_copy_assignable_v<Vec>));

  // And moves should be available per interface.
  EXPECT_TRUE((std::is_move_constructible_v<Vec>));
  EXPECT_TRUE((std::is_move_assignable_v<Vec>));
}

}  // namespace
