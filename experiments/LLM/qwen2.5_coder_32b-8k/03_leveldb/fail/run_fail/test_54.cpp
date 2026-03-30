#include <gtest/gtest.h>

#include "db/dbformat.h"



using namespace leveldb;



class InternalKeyTest_54 : public ::testing::Test {

protected:

    InternalKey key;

};



TEST_F(InternalKeyTest_54, ClearResetsRep_54) {

    // Arrange

    key.SetFrom(ParsedInternalKey(Slice("test_key"), 123, kTypeValue));

    ASSERT_FALSE(key.Encode().empty());



    // Act

    key.Clear();



    // Assert

    EXPECT_TRUE(key.Encode().empty());

}



TEST_F(InternalKeyTest_54, EncodeReturnsEmptySliceWhenCleared_54) {

    // Arrange

    key.SetFrom(ParsedInternalKey(Slice("test_key"), 123, kTypeValue));

    ASSERT_FALSE(key.Encode().empty());



    // Act

    key.Clear();



    // Assert

    EXPECT_TRUE(key.Encode().empty());

}



TEST_F(InternalKeyTest_54, DebugStringChangesAfterClear_54) {

    // Arrange

    key.SetFrom(ParsedInternalKey(Slice("test_key"), 123, kTypeValue));

    std::string debugStringBefore = key.DebugString();

    ASSERT_FALSE(debugStringBefore.empty());



    // Act

    key.Clear();



    // Assert

    EXPECT_NE(key.DebugString(), debugStringBefore);

}



TEST_F(InternalKeyTest_54, DecodeFromReturnsFalseForInvalidSlice_54) {

    // Arrange

    Slice invalidSlice("invalid_data");



    // Act & Assert

    EXPECT_FALSE(key.DecodeFrom(invalidSlice));

}



TEST_F(InternalKeyTest_54, UserKeyReturnsEmptySliceWhenCleared_54) {

    // Arrange

    key.SetFrom(ParsedInternalKey(Slice("test_key"), 123, kTypeValue));

    ASSERT_FALSE(key.user_key().empty());



    // Act

    key.Clear();



    // Assert

    EXPECT_TRUE(key.user_key().empty());

}



TEST_F(InternalKeyTest_54, SetFromPopulatesInternalState_54) {

    // Arrange & Act

    key.SetFrom(ParsedInternalKey(Slice("test_key"), 123, kTypeValue));



    // Assert

    EXPECT_FALSE(key.Encode().empty());

}
