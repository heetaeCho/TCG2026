#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/filter_policy.h"

#include "db/dbformat.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class MockFilterPolicy : public FilterPolicy {

public:

    MOCK_CONST_METHOD0(Name, const char*());

    MOCK_CONST_METHOD3(CreateFilter, void(const Slice*, int, std::string*));

    MOCK_CONST_METHOD2(KeyMayMatch, bool(const Slice&, const Slice&));

};



class InternalFilterPolicyTest_192 : public ::testing::Test {

protected:

    MockFilterPolicy mock_filter_policy;

    InternalFilterPolicy internal_filter_policy;



    InternalFilterPolicyTest_192() : internal_filter_policy(&mock_filter_policy) {}

};



TEST_F(InternalFilterPolicyTest_192, Name_ReturnsUserPolicyName_192) {

    const char* expected_name = "MockFilterPolicy";

    EXPECT_CALL(mock_filter_policy, Name()).WillOnce(Return(expected_name));



    const char* actual_name = internal_filter_policy.Name();

    EXPECT_STREQ(actual_name, expected_name);

}



TEST_F(InternalFilterPolicyTest_192, CreateFilter_DelegatesToUserPolicy_192) {

    const Slice keys[1] = {Slice("key")};

    int n = 1;

    std::string dst;



    EXPECT_CALL(mock_filter_policy, CreateFilter(keys, n, &dst));



    internal_filter_policy.CreateFilter(keys, n, &dst);

}



TEST_F(InternalFilterPolicyTest_192, KeyMayMatch_DelegatesToUserPolicy_192) {

    Slice key("key");

    Slice filter("filter");

    bool expected_result = true;



    EXPECT_CALL(mock_filter_policy, KeyMayMatch(key, filter)).WillOnce(Return(expected_result));



    bool actual_result = internal_filter_policy.KeyMayMatch(key, filter);

    EXPECT_EQ(actual_result, expected_result);

}
