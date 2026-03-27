#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/dbformat.h"



using namespace leveldb;



class InternalKeyTest_53 : public ::testing::Test {

protected:

    InternalKey key;

};



TEST_F(InternalKeyTest_53, SetFrom_NormalOperation_53) {

    ParsedInternalKey parsed_key(Slice("user_key"), 123, kTypeValue);

    key.SetFrom(parsed_key);



    EXPECT_EQ(key.user_key().ToString(), "user_key");

}



TEST_F(InternalKeyTest_53, Clear_ResetsState_53) {

    ParsedInternalKey parsed_key(Slice("user_key"), 123, kTypeValue);

    key.SetFrom(parsed_key);

    key.Clear();



    EXPECT_EQ(key.user_key().ToString(), "");

}



TEST_F(InternalKeyTest_53, DecodeFrom_ValidInput_ReturnsTrue_53) {

    std::string encoded = "encoded_data";

    Slice slice(encoded);

    bool result = key.DecodeFrom(slice);



    EXPECT_TRUE(result);

}



TEST_F(InternalKeyTest_53, DecodeFrom_InvalidInput_ReturnsFalse_53) {

    std::string invalid_encoded = "invalid";

    Slice slice(invalid_encoded);

    bool result = key.DecodeFrom(slice);



    EXPECT_FALSE(result);

}



TEST_F(InternalKeyTest_53, Encode_ReturnsNonEmptyString_53) {

    ParsedInternalKey parsed_key(Slice("user_key"), 123, kTypeValue);

    key.SetFrom(parsed_key);



    Slice encoded = key.Encode();

    EXPECT_FALSE(encoded.empty());

}



TEST_F(InternalKeyTest_53, DebugString_ReturnsNonEmptyString_53) {

    ParsedInternalKey parsed_key(Slice("user_key"), 123, kTypeValue);

    key.SetFrom(parsed_key);



    std::string debug_string = key.DebugString();

    EXPECT_FALSE(debug_string.empty());

}



TEST_F(InternalKeyTest_53, UserKey_AfterSetFrom_ReturnsCorrectUserKey_53) {

    ParsedInternalKey parsed_key(Slice("user_key"), 123, kTypeValue);

    key.SetFrom(parsed_key);



    Slice user_key_slice = key.user_key();

    EXPECT_EQ(user_key_slice.ToString(), "user_key");

}



TEST_F(InternalKeyTest_53, UserKey_AfterClear_ReturnsEmptySlice_53) {

    ParsedInternalKey parsed_key(Slice("user_key"), 123, kTypeValue);

    key.SetFrom(parsed_key);

    key.Clear();



    Slice user_key_slice = key.user_key();

    EXPECT_TRUE(user_key_slice.empty());

}
