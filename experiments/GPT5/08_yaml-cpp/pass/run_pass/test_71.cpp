// File: ./TestProjects/yaml-cpp/test/ptr_vector_back_test_71.cpp

#include <gtest/gtest.h>

#include <memory>
#include <utility>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"

namespace {

struct Box {
  int v;
};

class PtrVectorTest_71 : public ::testing::Test {};

TEST_F(PtrVectorTest_71, BackReturnsLastElementAfterMultiplePushBacks_71) {
  YAML::ptr_vector<Box> v;

  auto a = std::make_unique<Box>();
  a->v = 10;
  v.push_back(std::move(a));

  auto b = std::make_unique<Box>();
  b->v = 20;
  v.push_back(std::move(b));

  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), 2u);
  EXPECT_EQ(v.back().v, 20);
  EXPECT_EQ(v[0].v, 10);
  EXPECT_EQ(v[1].v, 20);
}

TEST_F(PtrVectorTest_71, BackReturnsMutableReferenceToLastElement_71) {
  YAML::ptr_vector<Box> v;

  auto a = std::make_unique<Box>();
  a->v = 1;
  v.push_back(std::move(a));

  auto b = std::make_unique<Box>();
  b->v = 2;
  v.push_back(std::move(b));

  ASSERT_EQ(v.size(), 2u);

  Box& last = v.back();
  last.v = 99;

  EXPECT_EQ(v.back().v, 99);
  EXPECT_EQ(v[1].v, 99);
  EXPECT_EQ(v[0].v, 1);
}

TEST_F(PtrVectorTest_71, BackWorksWithSingleElement_71) {
  YAML::ptr_vector<int> v;

  auto p = std::make_unique<int>(123);
  v.push_back(std::move(p));

  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v.back(), 123);

  v.back() = 456;
  EXPECT_EQ(v.back(), 456);
  EXPECT_EQ(v[0], 456);
}

TEST_F(PtrVectorTest_71, ClearEmptiesContainerAndAllowsReuse_71) {
  YAML::ptr_vector<int> v;

  v.push_back(std::make_unique<int>(1));
  v.push_back(std::make_unique<int>(2));
  ASSERT_EQ(v.size(), 2u);

  v.clear();

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);

  // Reuse after clear
  v.push_back(std::make_unique<int>(7));
  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), 1u);
  EXPECT_EQ(v.back(), 7);
}

TEST_F(PtrVectorTest_71, MoveConstructionPreservesBackElement_71) {
  YAML::ptr_vector<int> src;
  src.push_back(std::make_unique<int>(5));
  src.push_back(std::make_unique<int>(6));
  ASSERT_EQ(src.size(), 2u);

  YAML::ptr_vector<int> dst(std::move(src));

  ASSERT_FALSE(dst.empty());
  ASSERT_EQ(dst.size(), 2u);
  EXPECT_EQ(dst.back(), 6);

  // Moved-from object must remain valid; clear() should be safe to call.
  src.clear();
  EXPECT_TRUE(src.empty());
}

TEST_F(PtrVectorTest_71, MoveAssignmentPreservesBackElement_71) {
  YAML::ptr_vector<int> a;
  a.push_back(std::make_unique<int>(1));
  a.push_back(std::make_unique<int>(2));

  YAML::ptr_vector<int> b;
  b.push_back(std::make_unique<int>(9));

  b = std::move(a);

  ASSERT_FALSE(b.empty());
  ASSERT_EQ(b.size(), 2u);
  EXPECT_EQ(b.back(), 2);

  // Moved-from object must remain valid; clear() should be safe to call.
  a.clear();
  EXPECT_TRUE(a.empty());
}

}  // namespace
