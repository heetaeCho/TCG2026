// File: ./TestProjects/yaml-cpp/test/ptr_vector_test_67.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "ptr_vector.h"

namespace {

struct Item_67 {
  explicit Item_67(int v) : value(v) {}
  int value;
};

class PtrVectorTest_67 : public ::testing::Test {
 protected:
  using Vec = YAML::ptr_vector<Item_67>;
};

TEST_F(PtrVectorTest_67, DefaultConstructedIsEmpty_67) {
  Vec v;
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());
}

TEST_F(PtrVectorTest_67, PushBackIncreasesSizeAndStoresValues_67) {
  Vec v;

  v.push_back(std::make_unique<Item_67>(1));
  EXPECT_EQ(v.size(), 1u);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v[0].value, 1);

  v.push_back(std::make_unique<Item_67>(2));
  EXPECT_EQ(v.size(), 2u);
  EXPECT_EQ(v[0].value, 1);
  EXPECT_EQ(v[1].value, 2);
}

TEST_F(PtrVectorTest_67, OperatorIndexReturnsMutableReference_67) {
  Vec v;
  v.push_back(std::make_unique<Item_67>(10));
  v.push_back(std::make_unique<Item_67>(20));

  Item_67& ref = v[0];
  ref.value = 111;

  EXPECT_EQ(v[0].value, 111);
  EXPECT_EQ(v[1].value, 20);
}

TEST_F(PtrVectorTest_67, BackReturnsLastElement_67) {
  Vec v;
  v.push_back(std::make_unique<Item_67>(7));
  v.push_back(std::make_unique<Item_67>(9));

  EXPECT_EQ(v.back().value, 9);

  v.back().value = 123;
  EXPECT_EQ(v[1].value, 123);
}

TEST_F(PtrVectorTest_67, ClearRemovesAllElementsAndAllowsReuse_67) {
  Vec v;
  v.push_back(std::make_unique<Item_67>(1));
  v.push_back(std::make_unique<Item_67>(2));
  ASSERT_EQ(v.size(), 2u);
  ASSERT_FALSE(v.empty());

  v.clear();
  EXPECT_EQ(v.size(), 0u);
  EXPECT_TRUE(v.empty());

  // Reuse after clear
  v.push_back(std::make_unique<Item_67>(42));
  EXPECT_EQ(v.size(), 1u);
  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v[0].value, 42);
}

TEST_F(PtrVectorTest_67, PushBackConsumesUniquePtr_67) {
  Vec v;

  auto p = std::make_unique<Item_67>(5);
  Item_67* raw = p.get();
  ASSERT_NE(raw, nullptr);

  v.push_back(std::move(p));

  EXPECT_EQ(p.get(), nullptr);         // observable move-from effect on caller unique_ptr
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(&v[0], raw);               // same object now owned by the container
  EXPECT_EQ(v[0].value, 5);
}

TEST_F(PtrVectorTest_67, MoveConstructorTransfersElements_67) {
  Vec src;
  src.push_back(std::make_unique<Item_67>(1));
  src.push_back(std::make_unique<Item_67>(2));

  Vec dst(std::move(src));

  EXPECT_EQ(dst.size(), 2u);
  EXPECT_FALSE(dst.empty());
  EXPECT_EQ(dst[0].value, 1);
  EXPECT_EQ(dst[1].value, 2);

  // Moved-from object must remain valid; we only check operations are callable.
  src.clear();
  EXPECT_TRUE(src.empty());
}

TEST_F(PtrVectorTest_67, MoveAssignmentTransfersElements_67) {
  Vec a;
  a.push_back(std::make_unique<Item_67>(10));
  a.push_back(std::make_unique<Item_67>(20));

  Vec b;
  b.push_back(std::make_unique<Item_67>(99));

  b = std::move(a);

  EXPECT_EQ(b.size(), 2u);
  EXPECT_EQ(b[0].value, 10);
  EXPECT_EQ(b[1].value, 20);

  // Moved-from object must remain valid; we only check operations are callable.
  a.clear();
  EXPECT_TRUE(a.empty());
}

TEST_F(PtrVectorTest_67, CopyOperationsAreDeleted_67) {
  using Vec = YAML::ptr_vector<Item_67>;

  EXPECT_FALSE((std::is_copy_constructible_v<Vec>));
  EXPECT_FALSE((std::is_copy_assignable_v<Vec>));

  EXPECT_TRUE((std::is_move_constructible_v<Vec>));
  EXPECT_TRUE((std::is_move_assignable_v<Vec>));
}

}  // namespace
