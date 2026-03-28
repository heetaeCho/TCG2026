#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "collectionstack.h"



using namespace YAML;



class CollectionStackTest_63 : public ::testing::Test {

protected:

    CollectionStack collectionStack;

};



TEST_F(CollectionStackTest_63, GetCurCollectionType_EmptyStack_ReturnsNoCollection_63) {

    EXPECT_EQ(collectionStack.GetCurCollectionType(), CollectionType::NoCollection);

}



TEST_F(CollectionStackTest_63, PushCollectionTypeAndGetCurCollectionType_NormalOperation_63) {

    collectionStack.PushCollectionType(CollectionType::Sequence);

    EXPECT_EQ(collectionStack.GetCurCollectionType(), CollectionType::Sequence);

}



TEST_F(CollectionStackTest_63, PushAndPopCollectionType_NormalOperation_63) {

    collectionStack.PushCollectionType(CollectionType::Map);

    collectionStack.PopCollectionType();

    EXPECT_EQ(collectionStack.GetCurCollectionType(), CollectionType::NoCollection);

}



TEST_F(CollectionStackTest_63, PushMultipleTypesAndGetCurCollectionType_ReturnsTopType_63) {

    collectionStack.PushCollectionType(CollectionType::Sequence);

    collectionStack.PushCollectionType(CollectionType::Map);

    EXPECT_EQ(collectionStack.GetCurCollectionType(), CollectionType::Map);

}



TEST_F(CollectionStackTest_63, PopCollectionType_EmptyStack_NoError_63) {

    collectionStack.PopCollectionType(); // Should not cause any issues

    EXPECT_EQ(collectionStack.GetCurCollectionType(), CollectionType::NoCollection);

}
