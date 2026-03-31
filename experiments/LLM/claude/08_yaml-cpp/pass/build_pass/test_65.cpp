#include "gtest/gtest.h"
#include "collectionstack.h"

namespace YAML {

class CollectionStackTest_65 : public ::testing::Test {
protected:
    CollectionStack stack;
};

// Test that a newly created CollectionStack has a default collection type
TEST_F(CollectionStackTest_65, DefaultCollectionType_65) {
    // A freshly created stack should have some default collection type
    // We can observe this through GetCurCollectionType
    CollectionType::value defaultType = stack.GetCurCollectionType();
    // Just verify it doesn't crash and returns a valid value
    (void)defaultType;
}

// Test pushing a BlockMap type and retrieving it
TEST_F(CollectionStackTest_65, PushBlockMapAndGet_65) {
    stack.PushCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
}

// Test pushing a BlockSeq type and retrieving it
TEST_F(CollectionStackTest_65, PushBlockSeqAndGet_65) {
    stack.PushCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(CollectionType::BlockSeq, stack.GetCurCollectionType());
}

// Test pushing a FlowMap type and retrieving it
TEST_F(CollectionStackTest_65, PushFlowMapAndGet_65) {
    stack.PushCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
}

// Test pushing a FlowSeq type and retrieving it
TEST_F(CollectionStackTest_65, PushFlowSeqAndGet_65) {
    stack.PushCollectionType(CollectionType::FlowSeq);
    EXPECT_EQ(CollectionType::FlowSeq, stack.GetCurCollectionType());
}

// Test pushing a NoCollection type and retrieving it
TEST_F(CollectionStackTest_65, PushNoCollectionAndGet_65) {
    stack.PushCollectionType(CollectionType::NoCollection);
    EXPECT_EQ(CollectionType::NoCollection, stack.GetCurCollectionType());
}

// Test pop returns to previous collection type
TEST_F(CollectionStackTest_65, PopReturnsToPreviousType_65) {
    CollectionType::value initialType = stack.GetCurCollectionType();
    
    stack.PushCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(initialType, stack.GetCurCollectionType());
}

// Test multiple push and pop operations (LIFO behavior)
TEST_F(CollectionStackTest_65, MultiplePushPopLIFO_65) {
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::FlowSeq);
    stack.PushCollectionType(CollectionType::BlockSeq);
    
    EXPECT_EQ(CollectionType::BlockSeq, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(CollectionType::FlowSeq, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::FlowSeq);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::BlockMap);
}

// Test pushing the same type multiple times
TEST_F(CollectionStackTest_65, PushSameTypeMultipleTimes_65) {
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::BlockMap);
    
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::BlockMap);
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    
    stack.PopCollectionType(CollectionType::BlockMap);
}

// Test push then immediate pop leaves stack in original state
TEST_F(CollectionStackTest_65, PushThenPopRestoresState_65) {
    CollectionType::value before = stack.GetCurCollectionType();
    
    stack.PushCollectionType(CollectionType::FlowMap);
    stack.PopCollectionType(CollectionType::FlowMap);
    
    EXPECT_EQ(before, stack.GetCurCollectionType());
}

// Test alternating push and pop operations
TEST_F(CollectionStackTest_65, AlternatingPushPop_65) {
    CollectionType::value initialType = stack.GetCurCollectionType();
    
    stack.PushCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(CollectionType::BlockSeq, stack.GetCurCollectionType());
    stack.PopCollectionType(CollectionType::BlockSeq);
    EXPECT_EQ(initialType, stack.GetCurCollectionType());
    
    stack.PushCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
    stack.PopCollectionType(CollectionType::FlowMap);
    EXPECT_EQ(initialType, stack.GetCurCollectionType());
}

// Test deep nesting of collection types
TEST_F(CollectionStackTest_65, DeepNesting_65) {
    const int depth = 100;
    for (int i = 0; i < depth; ++i) {
        stack.PushCollectionType(CollectionType::BlockMap);
    }
    
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    
    for (int i = 0; i < depth; ++i) {
        EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
        stack.PopCollectionType(CollectionType::BlockMap);
    }
}

// Test that GetCurCollectionType is consistent without modification
TEST_F(CollectionStackTest_65, GetCurCollectionTypeConsistent_65) {
    stack.PushCollectionType(CollectionType::FlowSeq);
    
    CollectionType::value first = stack.GetCurCollectionType();
    CollectionType::value second = stack.GetCurCollectionType();
    
    EXPECT_EQ(first, second);
}

// Test interleaved different types
TEST_F(CollectionStackTest_65, InterleavedDifferentTypes_65) {
    stack.PushCollectionType(CollectionType::BlockMap);
    stack.PushCollectionType(CollectionType::FlowSeq);
    stack.PushCollectionType(CollectionType::BlockSeq);
    stack.PushCollectionType(CollectionType::FlowMap);
    
    EXPECT_EQ(CollectionType::FlowMap, stack.GetCurCollectionType());
    stack.PopCollectionType(CollectionType::FlowMap);
    
    EXPECT_EQ(CollectionType::BlockSeq, stack.GetCurCollectionType());
    stack.PopCollectionType(CollectionType::BlockSeq);
    
    EXPECT_EQ(CollectionType::FlowSeq, stack.GetCurCollectionType());
    stack.PopCollectionType(CollectionType::FlowSeq);
    
    EXPECT_EQ(CollectionType::BlockMap, stack.GetCurCollectionType());
    stack.PopCollectionType(CollectionType::BlockMap);
}

}  // namespace YAML
