#include <gtest/gtest.h>
#include "collectionstack.h"

namespace YAML {

class CollectionStackTest_63 : public ::testing::Test {
protected:
    CollectionStack stack;
};

// Test that a newly constructed CollectionStack returns NoCollection
TEST_F(CollectionStackTest_63, DefaultReturnsNoCollection_63) {
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
}

// Test pushing a BlockMap type and retrieving it
TEST_F(CollectionStackTest_63, PushBlockMapReturnsCurrent_63) {
    stack.PushCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
}

// Test pushing a BlockSeq type and retrieving it
TEST_F(CollectionStackTest_63, PushBlockSeqReturnsCurrent_63) {
    stack.PushCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(CollectionType::BlockSeq, stack.GetCurCollectionType());
}

// Test pushing a FlowMap type and retrieving it
TEST_F(CollectionStackTest_63, PushFlowMapReturnsCurrent_63) {
    stack.PushCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
}

// Test pushing a FlowSeq type and retrieving it
TEST_F(CollectionStackTest_63, PushFlowSeqReturnsCurrent_63) {
    stack.PushCollectionType(CollectionType::FlowSeq);
    EXPECT_EQ(CollectionType::FlowSeq, stack.GetCurCollectionType());
}

// Test that after pop, the previous collection type is restored
TEST_F(CollectionStackTest_63, PopRestoresPreviousType_63) {
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::FlowSeq);
    EXPECT_EQ(CollectionType::FlowSeq, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::FlowSeq);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
}

// Test that after popping all elements, NoCollection is returned
TEST_F(CollectionStackTest_63, PopAllReturnsNoCollection_63) {
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
}

// Test multiple pushes and pops in sequence (LIFO behavior)
TEST_F(CollectionStackTest_63, MultiplePushPopLIFO_63) {
    stack.PushCollectionType(CollectionType::BlockSeq);
    stack.PushCollectionType(CollectionType::FlowMap);
    stack.PushCollectionType(CollectionType::FlowSeq);

    EXPECT_EQ(CollectionType::FlowSeq, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::FlowSeq);
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(CollectionType::BlockSeq, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
}

// Test pushing the same type multiple times
TEST_F(CollectionStackTest_63, PushSameTypeMultipleTimes_63) {
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::BlockMap);

    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());

    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
}

// Test GetCurCollectionType is const and can be called multiple times without side effects
TEST_F(CollectionStackTest_63, GetCurCollectionTypeIsIdempotent_63) {
    stack.PushCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
}

// Test that calling GetCurCollectionType on empty stack multiple times is safe
TEST_F(CollectionStackTest_63, EmptyStackMultipleGetCalls_63) {
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
}

// Test push after pop returns to correct state
TEST_F(CollectionStackTest_63, PushAfterPopWorks_63) {
    stack.PushCollectionType(CollectionType::BlockSeq);
    stack.PopCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());

    stack.PushCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
}

}  // namespace YAML
