#include <gtest/gtest.h>

#include "db/dbformat.h"

#include "leveldb/slice.h"



namespace leveldb {



class InternalKeyEncodingLengthTest_47 : public ::testing::Test {

protected:

    Slice user_key;

    SequenceNumber sequence;

    ValueType type;

    ParsedInternalKey parsed_key;



    void SetUp() override {

        user_key = Slice("test_user_key");

        sequence = 12345;

        type = kTypeValue;

        parsed_key = ParsedInternalKey(user_key, sequence, type);

    }

};



TEST_F(InternalKeyEncodingLengthTest_47, NormalOperation_47) {

    size_t expected_length = user_key.size() + 8;

    EXPECT_EQ(InternalKeyEncodingLength(parsed_key), expected_length);

}



TEST_F(InternalKeyEncodingLengthTest_47, EmptyUserKey_47) {

    Slice empty_user_key = Slice();

    ParsedInternalKey parsed_empty_key(empty_user_key, sequence, type);

    size_t expected_length = 8; // Only the 8 bytes for sequence and type

    EXPECT_EQ(InternalKeyEncodingLength(parsed_empty_key), expected_length);

}



TEST_F(InternalKeyEncodingLengthTest_47, LargeUserKey_47) {

    std::string large_user_key_str(1024, 'a'); // A very long user key

    Slice large_user_key = Slice(large_user_key_str);

    ParsedInternalKey parsed_large_key(large_user_key, sequence, type);

    size_t expected_length = large_user_key.size() + 8;

    EXPECT_EQ(InternalKeyEncodingLength(parsed_large_key), expected_length);

}



} // namespace leveldb
