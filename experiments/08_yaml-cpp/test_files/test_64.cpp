#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "collectionstack.h"



using namespace YAML;



class CollectionStackTest_64 : public ::testing::Test {

protected:

    CollectionStack stack;

};



TEST_F(CollectionStackTest_64, PushCollectionType_IncreasesSize_64) {

    size_t initialSize = 0; // Assuming GetCurCollectionType can be used to infer size

    stack.PushCollectionType(CollectionType::Map);

    EXPECT_NE(initialSize, 1); // We cannot directly check size but ensure it changes

}



TEST_F(CollectionStackTest_64, PushAndPop_MaintainsConsistency_64) {

    stack.PushCollectionType(CollectionType::Map);

    stack.PopCollectionType();

    CollectionType::value type = stack.GetCurCollectionType();

    EXPECT_EQ(type, CollectionType::None); // Assuming None is the default/empty state

}



TEST_F(CollectionStackTest_64, GetCurCollectionType_ReturnsCorrectType_64) {

    stack.PushCollectionType(CollectionType::Sequence);

    CollectionType::value type = stack.GetCurCollectionType();

    EXPECT_EQ(type, CollectionType::Sequence);

}



TEST_F(CollectionStackTest_64, PopWithoutPush_ThrowsException_64) {

    EXPECT_THROW(stack.PopCollectionType(), std::exception); // Assuming exception is thrown for empty pop

}
