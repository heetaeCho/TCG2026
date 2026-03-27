#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/dbformat.h"



using namespace leveldb;



class InternalKeyComparatorTest : public ::testing::Test {

protected:

    Comparator* mock_user_comparator;

    InternalKeyComparator comparator;



    InternalKeyComparatorTest() 

        : mock_user_comparator(new MockComparator()), 

          comparator(mock_user_comparator) {}



    ~InternalKeyComparatorTest() {

        delete mock_user_comparator;

    }



    class MockComparator : public Comparator {

    public:

        MOCK_METHOD(const char*, Name, (), (const override));

        MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const override));

        MOCK_METHOD(void, FindShortestSeparator, (std::string* start, const Slice& limit), (override));

        MOCK_METHOD(void, FindShortSuccessor, (std::string* key), (override));

    };

};



TEST_F(InternalKeyComparatorTest_55, CompareDifferentUserKeys_55) {

    InternalKey a(Slice("key1"), 100, kTypeValue);

    InternalKey b(Slice("key2"), 100, kTypeValue);



    EXPECT_CALL(*mock_user_comparator, Compare(_, _))

        .WillOnce(::testing::Return(-1));



    int result = comparator.Compare(a, b);

    EXPECT_EQ(result, -1);

}



TEST_F(InternalKeyComparatorTest_55, CompareSameUserKeysDifferentSequenceNumbers_55) {

    InternalKey a(Slice("key"), 100, kTypeValue);

    InternalKey b(Slice("key"), 200, kTypeValue);



    EXPECT_CALL(*mock_user_comparator, Compare(_, _))

        .WillOnce(::testing::Return(0));



    int result = comparator.Compare(a, b);

    EXPECT_EQ(result, -1);

}



TEST_F(InternalKeyComparatorTest_55, CompareSameUserKeysSameSequenceNumbersDifferentTypes_55) {

    InternalKey a(Slice("key"), 100, kTypeValue);

    InternalKey b(Slice("key"), 100, kTypeDeletion);



    EXPECT_CALL(*mock_user_comparator, Compare(_, _))

        .WillOnce(::testing::Return(0));



    int result = comparator.Compare(a, b);

    EXPECT_EQ(result, -1);

}



TEST_F(InternalKeyComparatorTest_55, NameReturnsCorrectName_55) {

    EXPECT_CALL(*mock_user_comparator, Name())

        .WillOnce(::testing::Return("MockComparator"));



    const char* name = comparator.Name();

    EXPECT_STREQ(name, "leveldb.InternalKeyComparator:MockComparator");

}



TEST_F(InternalKeyComparatorTest_55, FindShortestSeparatorDelegatesToUserComparator_55) {

    std::string start;

    Slice limit;



    EXPECT_CALL(*mock_user_comparator, FindShortestSeparator(&start, limit))

        .Times(1);



    comparator.FindShortestSeparator(&start, limit);

}



TEST_F(InternalKeyComparatorTest_55, FindShortSuccessorDelegatesToUserComparator_55) {

    std::string key;



    EXPECT_CALL(*mock_user_comparator, FindShortSuccessor(&key))

        .Times(1);



    comparator.FindShortSuccessor(&key);

}
