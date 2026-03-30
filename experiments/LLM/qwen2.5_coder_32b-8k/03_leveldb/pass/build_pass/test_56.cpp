#include <gtest/gtest.h>

#include "db/dbformat.h"

#include "leveldb/slice.h"



namespace leveldb {



class ParseInternalKeyTest_56 : public ::testing::Test {

protected:

    ParsedInternalKey result;

};



TEST_F(ParseInternalKeyTest_56, NormalOperationWithValidInput_56) {

    Slice internal_key("user_key_data", 13);

    uint8_t type = kTypeValue;

    SequenceNumber sequence = 12345;

    

    // Append the sequence number and type to form a valid internal key

    char buffer[21];

    memcpy(buffer, "user_key_data", 13);

    EncodeFixed64(buffer + 13, (sequence << 8) | type);

    Slice full_internal_key(buffer, sizeof(buffer));



    EXPECT_TRUE(ParseInternalKey(full_internal_key, &result));

    EXPECT_EQ(result.user_key.ToString(), "user_key_data");

    EXPECT_EQ(result.sequence, sequence);

    EXPECT_EQ(result.type, static_cast<ValueType>(type));

}



TEST_F(ParseInternalKeyTest_56, BoundaryConditionWithMinimalValidInput_56) {

    Slice internal_key("u", 1);

    uint8_t type = kTypeValue;

    SequenceNumber sequence = 0;

    

    // Append the sequence number and type to form a valid internal key

    char buffer[9];

    memcpy(buffer, "u", 1);

    EncodeFixed64(buffer + 1, (sequence << 8) | type);

    Slice full_internal_key(buffer, sizeof(buffer));



    EXPECT_TRUE(ParseInternalKey(full_internal_key, &result));

    EXPECT_EQ(result.user_key.ToString(), "u");

    EXPECT_EQ(result.sequence, sequence);

    EXPECT_EQ(result.type, static_cast<ValueType>(type));

}



TEST_F(ParseInternalKeyTest_56, BoundaryConditionWithMaximalSequenceNumber_56) {

    Slice internal_key("user_key_data", 13);

    uint8_t type = kTypeValue;

    SequenceNumber sequence = std::numeric_limits<SequenceNumber>::max();

    

    // Append the sequence number and type to form a valid internal key

    char buffer[21];

    memcpy(buffer, "user_key_data", 13);

    EncodeFixed64(buffer + 13, (sequence << 8) | type);

    Slice full_internal_key(buffer, sizeof(buffer));



    EXPECT_TRUE(ParseInternalKey(full_internal_key, &result));

    EXPECT_EQ(result.user_key.ToString(), "user_key_data");

    EXPECT_EQ(result.sequence, sequence);

    EXPECT_EQ(result.type, static_cast<ValueType>(type));

}



TEST_F(ParseInternalKeyTest_56, ExceptionalCaseWithTooShortInput_56) {

    Slice internal_key("short", 5);

    

    EXPECT_FALSE(ParseInternalKey(internal_key, &result));

}



TEST_F(ParseInternalKeyTest_56, ExceptionalCaseWithInvalidType_56) {

    Slice internal_key("user_key_data", 13);

    uint8_t type = 2; // Invalid type

    SequenceNumber sequence = 0;

    

    // Append the sequence number and type to form a valid internal key

    char buffer[21];

    memcpy(buffer, "user_key_data", 13);

    EncodeFixed64(buffer + 13, (sequence << 8) | type);

    Slice full_internal_key(buffer, sizeof(buffer));



    EXPECT_FALSE(ParseInternalKey(full_internal_key, &result));

}



} // namespace leveldb
