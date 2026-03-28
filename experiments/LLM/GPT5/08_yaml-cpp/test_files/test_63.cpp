// File: ./TestProjects/yaml-cpp/test/collectionstack_test.cpp

#include <gtest/gtest.h>

#include "collectionstack.h"

namespace {

class CollectionStackTest_63 : public ::testing::Test {
 protected:
  YAML::CollectionStack stack;
};

TEST_F(CollectionStackTest_63, InitiallyReturnsNoCollection_63) {
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::NoCollection);
}

TEST_F(CollectionStackTest_63, GetCurCollectionTypeWorksOnConstObject_63) {
  const YAML::CollectionStack& const_stack = stack;
  EXPECT_EQ(const_stack.GetCurCollectionType(), YAML::CollectionType::NoCollection);
}

TEST_F(CollectionStackTest_63, PushUpdatesCurrentType_63) {
  stack.PushCollectionType(YAML::CollectionType::BlockSeq);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::BlockSeq);

  stack.PushCollectionType(YAML::CollectionType::FlowMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::FlowMap);
}

TEST_F(CollectionStackTest_63, PopRestoresPreviousType_63) {
  stack.PushCollectionType(YAML::CollectionType::BlockSeq);
  stack.PushCollectionType(YAML::CollectionType::FlowMap);

  stack.PopCollectionType(YAML::CollectionType::FlowMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::BlockSeq);

  stack.PopCollectionType(YAML::CollectionType::BlockSeq);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::NoCollection);
}

TEST_F(CollectionStackTest_63, NestedPushPopSequenceMaintainsLIFO_63) {
  stack.PushCollectionType(YAML::CollectionType::BlockMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::BlockMap);

  stack.PushCollectionType(YAML::CollectionType::FlowSeq);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::FlowSeq);

  stack.PushCollectionType(YAML::CollectionType::FlowMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::FlowMap);

  stack.PopCollectionType(YAML::CollectionType::FlowMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::FlowSeq);

  stack.PopCollectionType(YAML::CollectionType::FlowSeq);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::BlockMap);

  stack.PopCollectionType(YAML::CollectionType::BlockMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::NoCollection);
}

TEST_F(CollectionStackTest_63, ManyPushesThenManyPopsEndsAtNoCollection_63) {
  // Boundary-style stress: multiple levels.
  stack.PushCollectionType(YAML::CollectionType::BlockSeq);
  stack.PushCollectionType(YAML::CollectionType::BlockMap);
  stack.PushCollectionType(YAML::CollectionType::FlowSeq);
  stack.PushCollectionType(YAML::CollectionType::FlowMap);

  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::FlowMap);

  stack.PopCollectionType(YAML::CollectionType::FlowMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::FlowSeq);

  stack.PopCollectionType(YAML::CollectionType::FlowSeq);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::BlockMap);

  stack.PopCollectionType(YAML::CollectionType::BlockMap);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::BlockSeq);

  stack.PopCollectionType(YAML::CollectionType::BlockSeq);
  EXPECT_EQ(stack.GetCurCollectionType(), YAML::CollectionType::NoCollection);
}

}  // namespace
