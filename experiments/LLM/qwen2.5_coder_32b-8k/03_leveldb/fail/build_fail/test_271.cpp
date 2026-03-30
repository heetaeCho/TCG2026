#include <gtest/gtest.h>

#include "leveldb/c.h"

#include "leveldb/slice.h"



class FilterPolicyTest_271 : public ::testing::Test {

protected:

    void SetUp() override {

        filter_policy = leveldb_filterpolicy_create_bloom(10);

    }



    void TearDown() override {

        leveldb_filterpolicy_destroy(filter_policy);

    }



    leveldb_filterpolicy_t* filter_policy;

};



TEST_F(FilterPolicyTest_271, Name_ReturnsCorrectName_271) {

    const char* name = filter_policy->Name();

    EXPECT_STREQ(name, "leveldb.BuiltinBloomFilter");

}



TEST_F(FilterPolicyTest_271, CreateFilter_EmptyKeys_NoOutput_271) {

    std::string dst;

    leveldb::Slice keys[0];

    filter_policy->CreateFilter(keys, 0, &dst);

    EXPECT_TRUE(dst.empty());

}



TEST_F(FilterPolicyTest_271, CreateFilter_SingleKey_ValidOutput_271) {

    std::string dst;

    const char* key_data = "test_key";

    leveldb::Slice keys[] = {leveldb::Slice(key_data)};

    filter_policy->CreateFilter(keys, 1, &dst);

    EXPECT_FALSE(dst.empty());

}



TEST_F(FilterPolicyTest_271, KeyMayMatch_EmptyKeyAndFilter_ReturnsFalse_271) {

    leveldb::Slice key;

    leveldb::Slice filter;

    bool result = filter_policy->KeyMayMatch(key, filter);

    EXPECT_FALSE(result);

}



TEST_F(FilterPolicyTest_271, KeyMayMatch_ValidKeyAndMatchingFilter_ReturnsTrue_271) {

    std::string dst;

    const char* key_data = "test_key";

    leveldb::Slice keys[] = {leveldb::Slice(key_data)};

    filter_policy->CreateFilter(keys, 1, &dst);



    leveldb::Slice key(key_data);

    leveldb::Slice filter(dst);

    bool result = filter_policy->KeyMayMatch(key, filter);

    EXPECT_TRUE(result);

}



TEST_F(FilterPolicyTest_271, KeyMayMatch_ValidKeyAndNonMatchingFilter_ReturnsFalse_271) {

    std::string dst;

    const char* key_data = "test_key";

    leveldb::Slice keys[] = {leveldb::Slice(key_data)};

    filter_policy->CreateFilter(keys, 1, &dst);



    const char* other_key_data = "other_key";

    leveldb::Slice key(other_key_data);

    leveldb::Slice filter(dst);

    bool result = filter_policy->KeyMayMatch(key, filter);

    EXPECT_FALSE(result);

}
