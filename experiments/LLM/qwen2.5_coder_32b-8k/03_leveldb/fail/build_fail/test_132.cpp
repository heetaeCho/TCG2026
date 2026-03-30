#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/comparator.h"

#include "db/version_edit.h"



using namespace leveldb;

using ::testing::Return;



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice&, const Slice&));

    MOCK_METHOD0(Name, const char*());

    MOCK_METHOD2(FindShortestSeparator, void(std::string*, const Slice&));

    MOCK_METHOD1(FindShortSuccessor, void(std::string*));

};



class AfterFileTest_132 : public ::testing::Test {

protected:

    MockComparator mock_comparator;

    FileMetaData file_meta_data;

    Slice user_key;



    void SetUp() override {

        // Setup any common state or configurations for tests here.

        file_meta_data.smallest = InternalKey(Slice("smallest_key"), 100, ValueType::kTypeValue);

        file_meta_data.largest = InternalKey(Slice("largest_key"), 200, ValueType::kTypeValue);

    }

};



TEST_F(AfterFileTest_132, NormalOperation_UserKeySmallerThanSmallest_132) {

    EXPECT_CALL(mock_comparator, Compare(user_key, file_meta_data.smallest.user_key()))

        .WillOnce(Return(-1));



    bool result = AfterFile(&mock_comparator, &user_key, &file_meta_data);

    EXPECT_FALSE(result);

}



TEST_F(AfterFileTest_132, NormalOperation_UserKeyLargerThanLargest_132) {

    EXPECT_CALL(mock_comparator, Compare(user_key, file_meta_data.largest.user_key()))

        .WillOnce(Return(1));



    bool result = AfterFile(&mock_comparator, &user_key, &file_meta_data);

    EXPECT_TRUE(result);

}



TEST_F(AfterFileTest_132, NormalOperation_UserKeyBetweenSmallestAndLargest_132) {

    EXPECT_CALL(mock_comparator, Compare(user_key, file_meta_data.largest.user_key()))

        .WillOnce(Return(-1));

    EXPECT_CALL(mock_comparator, Compare(user_key, file_meta_data.smallest.user_key()))

        .WillOnce(Return(1));



    bool result = AfterFile(&mock_comparator, &user_key, &file_meta_data);

    EXPECT_FALSE(result);

}



TEST_F(AfterFileTest_132, BoundaryCondition_UserKeyEqualsSmallest_132) {

    user_key = file_meta_data.smallest.user_key();

    EXPECT_CALL(mock_comparator, Compare(user_key, file_meta_data.smallest.user_key()))

        .WillOnce(Return(0));



    bool result = AfterFile(&mock_comparator, &user_key, &file_meta_data);

    EXPECT_FALSE(result);

}



TEST_F(AfterFileTest_132, BoundaryCondition_UserKeyEqualsLargest_132) {

    user_key = file_meta_data.largest.user_key();

    EXPECT_CALL(mock_comparator, Compare(user_key, file_meta_data.largest.user_key()))

        .WillOnce(Return(0));



    bool result = AfterFile(&mock_comparator, &user_key, &file_meta_data);

    EXPECT_TRUE(result);

}



TEST_F(AfterFileTest_132, ExceptionalCase_UserKeyNullptr_132) {

    Slice* null_user_key = nullptr;



    bool result = AfterFile(&mock_comparator, null_user_key, &file_meta_data);

    EXPECT_FALSE(result);

}
