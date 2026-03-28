#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/c.cc"

#include "leveldb/slice.h"



using namespace leveldb;

using ::testing::Return;



class MockFilterPolicy : public FilterPolicy {

public:

    MOCK_CONST_METHOD0(Name, const char*());

    MOCK_METHOD3(CreateFilter, void(const Slice* keys, int n, std::string* dst));

    MOCK_CONST_METHOD2(KeyMayMatch, bool(const Slice& key, const Slice& filter));

};



class leveldb_filterpolicy_tTest : public ::testing::Test {

protected:

    leveldb_filterpolicy_t filter_policy;

    MockFilterPolicy mock_filter_policy;



    void SetUp() override {

        filter_policy.key_match_ = [](void* state, const char* key_data, size_t key_size,

                                      const char* filter_data, size_t filter_size) -> uint8_t {

            auto policy = static_cast<MockFilterPolicy*>(state);

            Slice key(key_data, key_size);

            Slice filter(filter_data, filter_size);

            return policy->KeyMayMatch(key, filter);

        };

    }

};



TEST_F(leveldb_filterpolicy_tTest, KeyMayMatch_ReturnsTrue_217) {

    const char* key_data = "test_key";

    const char* filter_data = "test_filter";

    Slice key(key_data);

    Slice filter(filter_data);



    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(true));

    ASSERT_TRUE(filter_policy.KeyMayMatch(key, filter));

}



TEST_F(leveldb_filterpolicy_tTest, KeyMayMatch_ReturnsFalse_217) {

    const char* key_data = "test_key";

    const char* filter_data = "test_filter";

    Slice key(key_data);

    Slice filter(filter_data);



    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(false));

    ASSERT_FALSE(filter_policy.KeyMayMatch(key, filter));

}



TEST_F(leveldb_filterpolicy_tTest, KeyMayMatch_EmptyKey_217) {

    const char* key_data = "";

    const char* filter_data = "test_filter";

    Slice key(key_data);

    Slice filter(filter_data);



    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(true));

    ASSERT_TRUE(filter_policy.KeyMayMatch(key, filter));

}



TEST_F(leveldb_filterpolicy_tTest, KeyMayMatch_EmptyFilter_217) {

    const char* key_data = "test_key";

    const char* filter_data = "";

    Slice key(key_data);

    Slice filter(filter_data);



    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(true));

    ASSERT_TRUE(filter_policy.KeyMayMatch(key, filter));

}



TEST_F(leveldb_filterpolicy_tTest, KeyMayMatch_BothEmpty_217) {

    const char* key_data = "";

    const char* filter_data = "";

    Slice key(key_data);

    Slice filter(filter_data);



    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(true));

    ASSERT_TRUE(filter_policy.KeyMayMatch(key, filter));

}
