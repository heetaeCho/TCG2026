#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/dbformat.h"

#include <string>



using namespace leveldb;



class AppendInternalKeyTest_185 : public ::testing::Test {

protected:

    std::string result;

    ParsedInternalKey key;

};



TEST_F(AppendInternalKeyTest_185, NormalOperation_185) {

    Slice user_key("testkey");

    SequenceNumber sequence = 10;

    ValueType type = kTypeValue;

    key = ParsedInternalKey(user_key, sequence, type);



    AppendInternalKey(&result, key);

    

    EXPECT_EQ(result.size(), user_key.size() + sizeof(uint64_t));

    EXPECT_TRUE(result.starts_with(user_key.ToString()));

}



TEST_F(AppendInternalKeyTest_185, EmptyUserKey_185) {

    Slice user_key;

    SequenceNumber sequence = 0;

    ValueType type = kTypeDeletion;

    key = ParsedInternalKey(user_key, sequence, type);



    AppendInternalKey(&result, key);

    

    EXPECT_EQ(result.size(), sizeof(uint64_t));

}



TEST_F(AppendInternalKeyTest_185, LargeSequenceNumber_185) {

    Slice user_key("testkey");

    SequenceNumber sequence = UINT64_MAX;

    ValueType type = kTypeValue;

    key = ParsedInternalKey(user_key, sequence, type);



    AppendInternalKey(&result, key);

    

    EXPECT_EQ(result.size(), user_key.size() + sizeof(uint64_t));

}



TEST_F(AppendInternalKeyTest_185, DifferentValueType_185) {

    Slice user_key("testkey");

    SequenceNumber sequence = 10;

    ValueType type = kTypeDeletion;

    key = ParsedInternalKey(user_key, sequence, type);



    AppendInternalKey(&result, key);

    

    EXPECT_EQ(result.size(), user_key.size() + sizeof(uint64_t));

}



TEST_F(AppendInternalKeyTest_185, MultipleAppends_185) {

    Slice user_key1("key1");

    SequenceNumber sequence1 = 10;

    ValueType type1 = kTypeValue;

    ParsedInternalKey key1(user_key1, sequence1, type1);



    Slice user_key2("key2");

    SequenceNumber sequence2 = 20;

    ValueType type2 = kTypeDeletion;

    ParsedInternalKey key2(user_key2, sequence2, type2);



    AppendInternalKey(&result, key1);

    AppendInternalKey(&result, key2);

    

    EXPECT_EQ(result.size(), (user_key1.size() + sizeof(uint64_t)) + (user_key2.size() + sizeof(uint64_t)));

}
