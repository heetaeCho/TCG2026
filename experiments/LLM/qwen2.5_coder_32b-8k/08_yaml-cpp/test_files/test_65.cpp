#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "collectionstack.h"



using namespace YAML;



class CollectionStackTest_65 : public ::testing::Test {

protected:

    CollectionStack collectionStack;

};



TEST_F(CollectionStackTest_65, PushAndPopMatchingType_65) {

    CollectionType::value type = CollectionType::BlockMap;

    collectionStack.PushCollectionType(type);

    EXPECT_NO_THROW(collectionStack.PopCollectionType(type));

}



TEST_F(CollectionStackTest_65, PopWithMismatchingType_65) {

    CollectionType::value pushedType = CollectionType::BlockMap;

    CollectionType::value poppedType = CollectionType::FlowSeq;

    collectionStack.PushCollectionType(pushedType);

    EXPECT_THROW(collectionStack.PopCollectionType(poppedType), std::exception);

}



TEST_F(CollectionStackTest_65, PopEmptyStack_65) {

    CollectionType::value type = CollectionType::BlockMap;

    EXPECT_THROW(collectionStack.PopCollectionType(type), std::exception);

}



TEST_F(CollectionStackTest_65, PushMultipleAndPopAll_65) {

    collectionStack.PushCollectionType(CollectionType::BlockMap);

    collectionStack.PushCollectionType(CollectionType::FlowSeq);

    collectionStack.PushCollectionType(CollectionType::BlockSeq);



    EXPECT_NO_THROW(collectionStack.PopCollectionType(CollectionType::BlockSeq));

    EXPECT_NO_THROW(collectionStack.PopCollectionType(CollectionType::FlowSeq));

    EXPECT_NO_THROW(collectionStack.PopCollectionType(CollectionType::BlockMap));

}



TEST_F(CollectionStackTest_65, PushAndCheckCurrentType_65) {

    CollectionType::value type = CollectionType::BlockMap;

    collectionStack.PushCollectionType(type);

    EXPECT_EQ(collectionStack.GetCurCollectionType(), type);

}
