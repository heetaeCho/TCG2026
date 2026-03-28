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



class InternalKeyComparatorTest_188 : public ::testing::Test {

protected:

    MockComparator mock_user_comparator;

    InternalKeyComparator internal_key_comparator{&mock_user_comparator};

};



TEST_F(InternalKeyComparatorTest_188, Name_ReturnsCorrectName_188) {

    EXPECT_STREQ(internal_key_comparator.Name(), "leveldb.InternalKeyComparator");

}



TEST_F(InternalKeyComparatorTest_188, Compare_DelegatesToUserComparator_188) {

    const Slice a("key1");

    const Slice b("key2");

    EXPECT_CALL(mock_user_comparator, Compare(a, b)).WillOnce(::testing::Return(-1));

    EXPECT_EQ(internal_key_comparator.Compare(a, b), -1);

}



TEST_F(InternalKeyComparatorTest_188, FindShortestSeparator_DelegatesToUserComparator_188) {

    std::string start("start");

    const Slice limit("limit");

    EXPECT_CALL(mock_user_comparator, FindShortestSeparator(&start, limit));

    internal_key_comparator.FindShortestSeparator(&start, limit);

}



TEST_F(InternalKeyComparatorTest_188, FindShortSuccessor_DelegatesToUserComparator_188) {

    std::string key("key");

    EXPECT_CALL(mock_user_comparator, FindShortSuccessor(&key));

    internal_key_comparator.FindShortSuccessor(&key);

}



TEST_F(InternalKeyComparatorTest_188, UserComparator_ReturnsCorrectInstance_188) {

    EXPECT_EQ(&internal_key_comparator.user_comparator(), &mock_user_comparator);

}



}  // namespace leveldb
