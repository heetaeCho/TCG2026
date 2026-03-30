#include <gtest/gtest.h>

#include "leveldb/dbformat.h"

#include "leveldb/comparator.h"

#include "gmock/gmock.h"



using namespace leveldb;

using ::testing::_;

using ::testing::InvokeWithoutArgs;



// Mock class for Comparator

class MockComparator : public Comparator {

public:

    MOCK_CONST_METHOD2(Compare, int(const Slice& a, const Slice& b));

    MOCK_CONST_METHOD1(FindShortestSeparator, void(std::string* start, const Slice& limit));

};



class InternalKeyComparatorTest_190 : public ::testing::Test {

protected:

    MockComparator mock_user_comparator;

    InternalKeyComparator internal_key_comparator{ &mock_user_comparator };



    std::string start_str = "start";

    std::string limit_str = "limit";

    Slice start_slice{ start_str };

    Slice limit_slice{ limit_str };

};



TEST_F(InternalKeyComparatorTest_190, FindShortestSeparator_NormalOperation_190) {

    EXPECT_CALL(mock_user_comparator, Compare(start_slice, _)).WillOnce(Return(-1));

    EXPECT_CALL(mock_user_comparator, FindShortestSeparator(_, limit_slice));



    internal_key_comparator.FindShortestSeparator(&start_str, limit_slice);

}



TEST_F(InternalKeyComparatorTest_190, FindShortestSeparator_StartGreaterThanLimit_190) {

    EXPECT_CALL(mock_user_comparator, Compare(start_slice, _)).WillOnce(Return(1));

    EXPECT_CALL(mock_user_comparator, FindShortestSeparator(_, limit_slice)).Times(0);



    internal_key_comparator.FindShortestSeparator(&start_str, limit_slice);

}



TEST_F(InternalKeyComparatorTest_190, FindShortestSeparator_StartEqualsLimit_190) {

    EXPECT_CALL(mock_user_comparator, Compare(start_slice, _)).WillOnce(Return(0));

    EXPECT_CALL(mock_user_comparator, FindShortestSeparator(_, limit_slice)).Times(0);



    internal_key_comparator.FindShortestSeparator(&start_str, limit_slice);

}



TEST_F(InternalKeyComparatorTest_190, FindShortestSeparator_UserComparatorUpdatesStart_190) {

    std::string tmp = "tmp";

    EXPECT_CALL(mock_user_comparator, Compare(start_slice, _)).WillOnce(Return(-1));

    EXPECT_CALL(mock_user_comparator, FindShortestSeparator(&tmp, limit_slice));



    internal_key_comparator.FindShortestSeparator(&start_str, limit_slice);

}
