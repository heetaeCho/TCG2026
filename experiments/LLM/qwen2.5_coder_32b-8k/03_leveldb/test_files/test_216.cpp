#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/c.cc"

#include "leveldb/slice.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockFilterPolicy : public leveldb_filterpolicy_t {

public:

    MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst) const, (override));

    MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter) const, (override));

};



class FilterPolicyTest_216 : public ::testing::Test {

protected:

    MockFilterPolicy mock_filter_policy;

};



TEST_F(FilterPolicyTest_216, CreateFilter_NormalOperation_216) {

    std::string result;

    Slice keys[] = {Slice("key1"), Slice("key2")};

    EXPECT_CALL(mock_filter_policy, CreateFilter(keys, 2, &result)).Times(1);

    mock_filter_policy.CreateFilter(keys, 2, &result);

}



TEST_F(FilterPolicyTest_216, CreateFilter_BoundaryZeroKeys_216) {

    std::string result;

    Slice keys[] = {};

    EXPECT_CALL(mock_filter_policy, CreateFilter(keys, 0, &result)).Times(1);

    mock_filter_policy.CreateFilter(keys, 0, &result);

}



TEST_F(FilterPolicyTest_216, KeyMayMatch_NormalOperation_216) {

    Slice key("key");

    Slice filter("filter");

    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(true));

    bool result = mock_filter_policy.KeyMayMatch(key, filter);

    EXPECT_TRUE(result);

}



TEST_F(FilterPolicyTest_216, KeyMayMatch_KeyNotMatching_216) {

    Slice key("key");

    Slice filter("filter");

    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(false));

    bool result = mock_filter_policy.KeyMayMatch(key, filter);

    EXPECT_FALSE(result);

}
