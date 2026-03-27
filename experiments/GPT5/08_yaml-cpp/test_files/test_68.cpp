// File: ptr_vector_test_68.cpp

#include <gtest/gtest.h>

#include <memory>
#include <type_traits>
#include <utility>

#include "TestProjects/yaml-cpp/src/ptr_vector.h"

namespace {

struct Widget {
  explicit Widget(int v) : value(v) {}
  int value;
};

using YAML::ptr_vector;

class PtrVectorTest_68 : public ::testing::Test {};

TEST_F(PtrVectorTest_68, DefaultConstructedIsEmpty_68) {
  ptr_vector<Widget> v;

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST_F(PtrVectorTest_68, PushBackMakesNonEmptyAndIncreasesSize_68) {
  ptr_vector<Widget> v;

  v.push_back(std::make_unique<Widget>(10));

  EXPECT_FALSE(v.empty());
  EXPECT_EQ(v.size(), 1u);
  EXPECT_EQ(v.back().value, 10);
  EXPECT_EQ(v[0].value, 10);
}

TEST_F(PtrVectorTest_68, PushBackMultiplePreservesOrderAndBack_68) {
  ptr_vector<Widget> v;

  v.push_back(std::make_unique<Widget>(1));
  v.push_back(std::make_unique<Widget>(2));
  v.push_back(std::make_unique<Widget>(3));

  EXPECT_EQ(v.size(), 3u);
  EXPECT_FALSE(v.empty());

  EXPECT_EQ(v[0].value, 1);
  EXPECT_EQ(v[1].value, 2);
  EXPECT_EQ(v[2].value, 3);
  EXPECT_EQ(v.back().value, 3);
}

TEST_F(PtrVectorTest_68, OperatorIndexReturnsMutableReference_68) {
  ptr_vector<Widget> v;
  v.push_back(std::make_unique<Widget>(7));

  v[0].value = 42;

  EXPECT_EQ(v[0].value, 42);
  EXPECT_EQ(v.back().value, 42);
}

TEST_F(PtrVectorTest_68, ClearEmptiesVector_68) {
  ptr_vector<Widget> v;
  v.push_back(std::make_unique<Widget>(1));
  v.push_back(std::make_unique<Widget>(2));

  ASSERT_FALSE(v.empty());
  ASSERT_EQ(v.size(), 2u);

  v.clear();

  EXPECT_TRUE(v.empty());
  EXPECT_EQ(v.size(), 0u);
}

TEST_F(PtrVectorTest_68, MoveConstructionTransfersElementsToDestination_68) {
  ptr_vector<Widget> src;
  src.push_back(std::make_unique<Widget>(5));
  src.push_back(std::make_unique<Widget>(6));

  ptr_vector<Widget> dst(std::move(src));

  EXPECT_EQ(dst.size(), 2u);
  EXPECT_FALSE(dst.empty());
  EXPECT_EQ(dst[0].value, 5);
  EXPECT_EQ(dst[1].value, 6);
  EXPECT_EQ(dst.back().value, 6);

  // Moved-from object must remain valid; verify it can be used again.
  src.push_back(std::make_unique<Widget>(99));
  EXPECT_EQ(src.size(), 1u);
  EXPECT_EQ(src[0].value, 99);
}

TEST_F(PtrVectorTest_68, MoveAssignmentReplacesDestinationContents_68) {
  ptr_vector<Widget> src;
  src.push_back(std::make_unique<Widget>(11));
  src.push_back(std::make_unique<Widget>(22));

  ptr_vector<Widget> dst;
  dst.push_back(std::make_unique<Widget>(1));  // pre-existing content

  dst = std::move(src);

  EXPECT_EQ(dst.size(), 2u);
  EXPECT_FALSE(dst.empty());
  EXPECT_EQ(dst[0].value, 11);
  EXPECT_EQ(dst[1].value, 22);
  EXPECT_EQ(dst.back().value, 22);

  // Moved-from object must remain valid; verify it can be used again.
  src.push_back(std::make_unique<Widget>(123));
  EXPECT_EQ(src.size(), 1u);
  EXPECT_EQ(src.back().value, 123);
}

TEST_F(PtrVectorTest_68, CopyOperationsAreDeletedAndMoveIsSupported_68) {
  using V = ptr_vector<Widget>;

  EXPECT_FALSE((std::is_copy_constructible<V>::value));
  EXPECT_FALSE((std::is_copy_assignable<V>::value));

  EXPECT_TRUE((std::is_move_constructible<V>::value));
  EXPECT_TRUE((std::is_move_assignable<V>::value));
}

}  // namespace
