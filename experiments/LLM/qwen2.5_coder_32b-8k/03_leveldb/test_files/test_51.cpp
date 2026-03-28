#include <gtest/gtest.h>

#include "db/dbformat.h"



using namespace leveldb;



class InternalKeyTest_51 : public ::testing::Test {

protected:

    Slice default_slice;

    SequenceNumber sequence_number = 12345;

    ValueType value_type = kTypeValue;



    void SetUp() override {

        std::string data("test_key");

        default_slice = Slice(data);

    }

};



TEST_F(InternalKeyTest_51, EncodeReturnsNonEmptySlice_51) {

    InternalKey internal_key(default_slice, sequence_number, value_type);

    Slice encoded = internal_key.Encode();

    EXPECT_FALSE(encoded.empty());

}



TEST_F(InternalKeyTest_51, DefaultConstructorInitializesRepEmpty_51) {

    InternalKey internal_key;

    EXPECT_TRUE(internal_key.Encode().empty());

}



TEST_F(InternalKeyTest_51, SetFromUpdatesRep_51) {

    InternalKey internal_key;

    ParsedInternalKey parsed_key = {"test_user_key", sequence_number, value_type};

    internal_key.SetFrom(parsed_key);

    Slice encoded = internal_key.Encode();

    EXPECT_FALSE(encoded.empty());

}



TEST_F(InternalKeyTest_51, ClearResetsRep_51) {

    InternalKey internal_key(default_slice, sequence_number, value_type);

    internal_key.Clear();

    EXPECT_TRUE(internal_key.Encode().empty());

}



TEST_F(InternalKeyTest_51, UserKeyReturnsCorrectSlice_51) {

    InternalKey internal_key(default_slice, sequence_number, value_type);

    EXPECT_EQ(default_slice.ToString(), internal_key.user_key().ToString());

}



TEST_F(InternalKeyTest_51, DecodeFromSetsRep_51) {

    std::string data("test_encoded_key");

    Slice encoded_slice(data);

    InternalKey internal_key;

    bool success = internal_key.DecodeFrom(encoded_slice);

    EXPECT_TRUE(success);

    EXPECT_FALSE(internal_key.Encode().empty());

}



TEST_F(InternalKeyTest_51, DecodeFromInvalidSliceReturnsFalse_51) {

    std::string data("invalid");

    Slice encoded_slice(data);

    InternalKey internal_key;

    bool success = internal_key.DecodeFrom(encoded_slice);

    EXPECT_FALSE(success);

}



TEST_F(InternalKeyTest_51, DebugStringProvidesNonEmptyOutput_51) {

    InternalKey internal_key(default_slice, sequence_number, value_type);

    std::string debug_string = internal_key.DebugString();

    EXPECT_FALSE(debug_string.empty());

}
