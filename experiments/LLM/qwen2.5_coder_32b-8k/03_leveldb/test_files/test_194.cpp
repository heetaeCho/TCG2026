#include <gtest/gtest.h>

#include "leveldb/dbformat.h"

#include "leveldb/slice.h"



using namespace leveldb;



class MockFilterPolicy : public FilterPolicy {

public:

    MOCK_METHOD(const char*, Name, (), (const override));

    MOCK_METHOD(void, CreateFilter, (const Slice* keys, int n, std::string* dst), (const override));

    MOCK_METHOD(bool, KeyMayMatch, (const Slice& key, const Slice& filter), (const override));

};



class InternalFilterPolicyTest_194 : public ::testing::Test {

protected:

    MockFilterPolicy mock_user_policy;

    InternalFilterPolicy internal_filter_policy;



    InternalFilterPolicyTest_194() : internal_filter_policy(&mock_user_policy) {}

};



TEST_F(InternalFilterPolicyTest_194, KeyMayMatch_DelegatesToUserPolicy_NormalOperation_194) {

    Slice key("test_key");

    Slice filter("test_filter");

    EXPECT_CALL(mock_user_policy, KeyMayMatch(ExtractUserKey(key), filter)).WillOnce(::testing::Return(true));

    EXPECT_TRUE(internal_filter_policy.KeyMayMatch(key, filter));

}



TEST_F(InternalFilterPolicyTest_194, KeyMayMatch_DelegatesToUserPolicy_EmptyKey_194) {

    Slice key("");

    Slice filter("test_filter");

    EXPECT_CALL(mock_user_policy, KeyMayMatch(ExtractUserKey(key), filter)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(internal_filter_policy.KeyMayMatch(key, filter));

}



TEST_F(InternalFilterPolicyTest_194, KeyMayMatch_DelegatesToUserPolicy_EmptyFilter_194) {

    Slice key("test_key");

    Slice filter("");

    EXPECT_CALL(mock_user_policy, KeyMayMatch(ExtractUserKey(key), filter)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(internal_filter_policy.KeyMayMatch(key, filter));

}



TEST_F(InternalFilterPolicyTest_194, KeyMayMatch_DelegatesToUserPolicy_ReturnsFalse_194) {

    Slice key("test_key");

    Slice filter("test_filter");

    EXPECT_CALL(mock_user_policy, KeyMayMatch(ExtractUserKey(key), filter)).WillOnce(::testing::Return(false));

    EXPECT_FALSE(internal_filter_policy.KeyMayMatch(key, filter));

}
