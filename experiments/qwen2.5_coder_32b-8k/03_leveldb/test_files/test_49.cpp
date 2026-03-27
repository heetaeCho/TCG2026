#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/dbformat.h"



namespace leveldb {



class MockComparator : public Comparator {

public:

    MOCK_METHOD(const char*, Name, (), (const override));

    MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const override));

    MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit), (override));

    MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (override));

};



class InternalKeyComparatorTest : public ::testing::Test {

protected:

    MockComparator mock_user_comparator;

    InternalKeyComparator internal_key_comparator{&mock_user_comparator};

};



TEST_F(InternalKeyComparatorTest_49, UserComparatorReturnsProvidedComparator_49) {

    EXPECT_EQ(&mock_user_comparator, internal_key_comparator.user_comparator());

}



TEST_F(InternalKeyComparatorTest_49, NameDelegatesToUserComparator_49) {

    const char* expected_name = "test_name";

    EXPECT_CALL(mock_user_comparator, Name()).WillOnce(::testing::Return(expected_name));

    EXPECT_EQ(expected_name, internal_key_comparator.Name());

}



TEST_F(InternalKeyComparatorTest_49, CompareDelegatesToUserComparatorForSlices_49) {

    Slice a("a");

    Slice b("b");

    int expected_result = 1;

    EXPECT_CALL(mock_user_comparator, Compare(a, b)).WillOnce(::testing::Return(expected_result));

    EXPECT_EQ(expected_result, internal_key_comparator.Compare(a, b));

}



TEST_F(InternalKeyComparatorTest_49, FindShortestSeparatorDelegatesToUserComparator_49) {

    std::string start("start");

    Slice limit("limit");

    EXPECT_CALL(mock_user_comparator, FindShortestSeparator(&start, limit)).Times(1);

    internal_key_comparator.FindShortestSeparator(&start, limit);

}



TEST_F(InternalKeyComparatorTest_49, FindShortSuccessorDelegatesToUserComparator_49) {

    std::string key("key");

    EXPECT_CALL(mock_user_comparator, FindShortSuccessor(&key)).Times(1);

    internal_key_comparator.FindShortSuccessor(&key);

}



}  // namespace leveldb
