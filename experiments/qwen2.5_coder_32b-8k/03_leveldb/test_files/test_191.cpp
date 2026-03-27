#include <gtest/gtest.h>

#include "db/dbformat.h"

#include "leveldb/comparator.h"

#include "leveldb/slice.h"



namespace leveldb {



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice& a, const Slice& b));

    MOCK_METHOD1(Name, const char*());

    MOCK_METHOD2(FindShortestSeparator, void(std::string* start, const Slice& limit));

    MOCK_METHOD1(FindShortSuccessor, void(std::string* key));

};



class InternalKeyComparatorTest : public ::testing::Test {

protected:

    MockComparator mock_comparator;

    InternalKeyComparator internal_key_comparator{&mock_comparator};

};



TEST_F(InternalKeyComparatorTest_191, FindShortSuccessor_NormalOperation_191) {

    std::string key = "user_key";

    std::string expected_successor = "user_key\x00\x00\x00\x00\x00\x00\x00\xff";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mock_comparator, FindShortSuccessor(&key));



    internal_key_comparator.FindShortSuccessor(&key);



    ASSERT_EQ(key, expected_successor);

}



TEST_F(InternalKeyComparatorTest_191, FindShortSuccessor_UserKeyUnchanged_191) {

    std::string key = "user_key";

    std::string unchanged_key = key;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(0));



    internal_key_comparator.FindShortSuccessor(&key);



    ASSERT_EQ(key, unchanged_key);

}



TEST_F(InternalKeyComparatorTest_191, FindShortSuccessor_EmptyString_191) {

    std::string key = "";

    std::string expected_successor = "\x00\x00\x00\x00\x00\x00\x00\xff";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mock_comparator, FindShortSuccessor(&key));



    internal_key_comparator.FindShortSuccessor(&key);



    ASSERT_EQ(key, expected_successor);

}



TEST_F(InternalKeyComparatorTest_191, FindShortSuccessor_ShorterSuccessor_191) {

    std::string key = "user_key";

    std::string shorter_successor = "user";

    std::string expected_successor = "user\x00\x00\x00\x00\x00\x00\x00\xff";



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(-1));

    EXPECT_CALL(mock_comparator, FindShortSuccessor(&key))

        .WillOnce([shorter_successor](std::string* key) { *key = shorter_successor; });



    internal_key_comparator.FindShortSuccessor(&key);



    ASSERT_EQ(key, expected_successor);

}



TEST_F(InternalKeyComparatorTest_191, FindShortSuccessor_ExceptionalCase_191) {

    std::string key = "user_key";

    std::string unchanged_key = key;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(::testing::Return(1));



    internal_key_comparator.FindShortSuccessor(&key);



    ASSERT_EQ(key, unchanged_key);

}



}  // namespace leveldb
