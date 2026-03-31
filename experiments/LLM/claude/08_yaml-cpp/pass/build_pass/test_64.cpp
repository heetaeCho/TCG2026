#include <gtest/gtest.h>
#include "collectionstack.h"
#include "yaml-cpp/yaml.h"

namespace YAML {

class CollectionStackTest_64 : public ::testing::Test {
 protected:
  CollectionStack stack_;
};

// Test that a freshly constructed CollectionStack returns NoCollection
TEST_F(CollectionStackTest_64, DefaultCollectionTypeIsNoCollection_64) {
  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
}

// Test pushing a BlockMap type and retrieving it
TEST_F(CollectionStackTest_64, PushBlockMapAndGet_64) {
  stack_.PushCollectionType(CollectionType::BlockMap);
  EXPECT_EQ(CollectionType::BlockMap, stack_.GetCurCollectionType());
}

// Test pushing a BlockSeq type and retrieving it
TEST_F(CollectionStackTest_64, PushBlockSeqAndGet_64) {
  stack_.PushCollectionType(CollectionType::BlockSeq);
  EXPECT_EQ(CollectionType::BlockSeq, stack_.GetCurCollectionType());
}

// Test pushing a FlowMap type and retrieving it
TEST_F(CollectionStackTest_64, PushFlowMapAndGet_64) {
  stack_.PushCollectionType(CollectionType::FlowMap);
  EXPECT_EQ(CollectionType::FlowMap, stack_.GetCurCollectionType());
}

// Test pushing a FlowSeq type and retrieving it
TEST_F(CollectionStackTest_64, PushFlowSeqAndGet_64) {
  stack_.PushCollectionType(CollectionType::FlowSeq);
  EXPECT_EQ(CollectionType::FlowSeq, stack_.GetCurCollectionType());
}

// Test pushing multiple types returns the most recently pushed type
TEST_F(CollectionStackTest_64, PushMultipleReturnsTop_64) {
  stack_.PushCollectionType(CollectionType::BlockMap);
  stack_.PushCollectionType(CollectionType::FlowSeq);
  EXPECT_EQ(CollectionType::FlowSeq, stack_.GetCurCollectionType());
}

// Test that popping reveals the previous type
TEST_F(CollectionStackTest_64, PopRevealsUnderlyingType_64) {
  stack_.PushCollectionType(CollectionType::BlockMap);
  stack_.PushCollectionType(CollectionType::FlowSeq);
  stack_.PopCollectionType(CollectionType::FlowSeq);
  EXPECT_EQ(CollectionType::BlockMap, stack_.GetCurCollectionType());
}

// Test push and pop returns to NoCollection
TEST_F(CollectionStackTest_64, PushAndPopReturnsToNoCollection_64) {
  stack_.PushCollectionType(CollectionType::BlockSeq);
  stack_.PopCollectionType(CollectionType::BlockSeq);
  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
}

// Test pushing multiple and popping all returns to NoCollection
TEST_F(CollectionStackTest_64, PushMultiplePopAllReturnsToNoCollection_64) {
  stack_.PushCollectionType(CollectionType::BlockMap);
  stack_.PushCollectionType(CollectionType::FlowMap);
  stack_.PushCollectionType(CollectionType::BlockSeq);
  stack_.PopCollectionType(CollectionType::BlockSeq);
  stack_.PopCollectionType(CollectionType::FlowMap);
  stack_.PopCollectionType(CollectionType::BlockMap);
  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
}

// Test LIFO ordering with multiple pushes and pops
TEST_F(CollectionStackTest_64, LIFOOrderingIsRespected_64) {
  stack_.PushCollectionType(CollectionType::BlockMap);
  stack_.PushCollectionType(CollectionType::BlockSeq);
  stack_.PushCollectionType(CollectionType::FlowMap);

  EXPECT_EQ(CollectionType::FlowMap, stack_.GetCurCollectionType());
  stack_.PopCollectionType(CollectionType::FlowMap);

  EXPECT_EQ(CollectionType::BlockSeq, stack_.GetCurCollectionType());
  stack_.PopCollectionType(CollectionType::BlockSeq);

  EXPECT_EQ(CollectionType::BlockMap, stack_.GetCurCollectionType());
  stack_.PopCollectionType(CollectionType::BlockMap);

  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
}

// Test pushing the same type multiple times
TEST_F(CollectionStackTest_64, PushSameTypeMultipleTimes_64) {
  stack_.PushCollectionType(CollectionType::BlockMap);
  stack_.PushCollectionType(CollectionType::BlockMap);
  stack_.PushCollectionType(CollectionType::BlockMap);

  EXPECT_EQ(CollectionType::BlockMap, stack_.GetCurCollectionType());
  stack_.PopCollectionType(CollectionType::BlockMap);
  EXPECT_EQ(CollectionType::BlockMap, stack_.GetCurCollectionType());
  stack_.PopCollectionType(CollectionType::BlockMap);
  EXPECT_EQ(CollectionType::BlockMap, stack_.GetCurCollectionType());
  stack_.PopCollectionType(CollectionType::BlockMap);
  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
}

// Test GetCurCollectionType is idempotent (doesn't modify state)
TEST_F(CollectionStackTest_64, GetCurCollectionTypeIsIdempotent_64) {
  stack_.PushCollectionType(CollectionType::FlowSeq);
  EXPECT_EQ(CollectionType::FlowSeq, stack_.GetCurCollectionType());
  EXPECT_EQ(CollectionType::FlowSeq, stack_.GetCurCollectionType());
  EXPECT_EQ(CollectionType::FlowSeq, stack_.GetCurCollectionType());
}

// Test NoCollection type on empty stack is stable across multiple calls
TEST_F(CollectionStackTest_64, EmptyStackReturnsNoCollectionConsistently_64) {
  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
  EXPECT_EQ(CollectionType::NoCollection, stack_.GetCurCollectionType());
}

}  // namespace YAML
