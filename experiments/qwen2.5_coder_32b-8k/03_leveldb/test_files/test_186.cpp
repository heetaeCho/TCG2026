#include <gtest/gtest.h>

#include "db/dbformat.h"

#include "leveldb/slice.h"



using namespace leveldb;



class ParsedInternalKeyTest_186 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any state needed for tests here.

        user_key = Slice("test_user_key");

        sequence_number = 12345;

        value_type = kTypeValue;

        parsed_internal_key = ParsedInternalKey(user_key, sequence_number, value_type);

    }



    Slice user_key;

    SequenceNumber sequence_number;

    ValueType value_type;

    ParsedInternalKey parsed_internal_key;

};



TEST_F(ParsedInternalKeyTest_186, DebugString_NormalOperation_186) {

    std::string expected = "'test_user_key' @ 12345 : 1";

    EXPECT_EQ(parsed_internal_key.DebugString(), expected);

}



TEST_F(ParsedInternalKeyTest_186, DebugString_EmptyUserKey_186) {

    ParsedInternalKey empty_key_parsed_internal_key(Slice(""), sequence_number, value_type);

    std::string expected = "'\\x00' @ 12345 : 1";

    EXPECT_EQ(empty_key_parsed_internal_key.DebugString(), expected);

}



TEST_F(ParsedInternalKeyTest_186, DebugString_MaxSequenceNumber_186) {

    ParsedInternalKey max_seq_parsed_internal_key(user_key, std::numeric_limits<SequenceNumber>::max(), value_type);

    std::string expected = "'test_user_key' @ 18446744073709551615 : 1";

    EXPECT_EQ(max_seq_parsed_internal_key.DebugString(), expected);

}



TEST_F(ParsedInternalKeyTest_186, DebugString_DifferentValueType_186) {

    ParsedInternalKey deletion_key_parsed_internal_key(user_key, sequence_number, kTypeDeletion);

    std::string expected = "'test_user_key' @ 12345 : 0";

    EXPECT_EQ(deletion_key_parsed_internal_key.DebugString(), expected);

}
