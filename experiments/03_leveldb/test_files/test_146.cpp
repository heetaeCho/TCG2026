#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "leveldb/dbformat.h"

#include "leveldb/comparator.h"



namespace leveldb {

    class MockComparator : public Comparator {

    public:

        MOCK_METHOD2(Compare, int(const Slice& a, const Slice& b));

        MOCK_CONST_METHOD0(Name, const char*());

        MOCK_METHOD2(FindShortestSeparator, void(std::string* start, const Slice& limit));

        MOCK_METHOD1(FindShortSuccessor, void(std::string* key));

    };



    class SaveValueTest : public ::testing::Test {

    protected:

        MockComparator mock_cmp;

        Saver saver;

        std::string value;



        SaveValueTest() : saver{kNotFound, &mock_cmp, &value} {}

    };



    TEST_F(SaveValueTest, NormalOperation_UserKeyMatch_ValueTypeValue_146) {

        Slice ikey("user_key\0seq\0type", 20); // Mocked internal key

        Slice v("value_data", 10);

        EXPECT_CALL(mock_cmp, Compare(_, _)).WillOnce(::testing::Return(0));

        SaveValue(&saver, ikey, v);

        EXPECT_EQ(saver.state, kFound);

        EXPECT_EQ(value, "value_data");

    }



    TEST_F(SaveValueTest, NormalOperation_UserKeyMatch_ValueTypeDeletion_146) {

        Slice ikey("user_key\0seq\0type", 20); // Mocked internal key

        Slice v;

        EXPECT_CALL(mock_cmp, Compare(_, _)).WillOnce(::testing::Return(0));

        SaveValue(&saver, ikey, v);

        EXPECT_EQ(saver.state, kDeleted);

    }



    TEST_F(SaveValueTest, UserKeyMismatch_146) {

        Slice ikey("different_user_key\0seq\0type", 28); // Mocked internal key

        Slice v("value_data", 10);

        EXPECT_CALL(mock_cmp, Compare(_, _)).WillOnce(::testing::Return(1));

        SaveValue(&saver, ikey, v);

        EXPECT_EQ(saver.state, kNotFound);

    }



    TEST_F(SaveValueTest, ParseInternalKeyFailure_146) {

        Slice ikey("invalid_ikey", 12); // Invalid internal key

        Slice v("value_data", 10);

        SaveValue(&saver, ikey, v);

        EXPECT_EQ(saver.state, kCorrupt);

    }



    TEST_F(SaveValueTest, BoundaryCondition_EmptySlices_146) {

        Slice ikey;

        Slice v;

        SaveValue(&saver, ikey, v);

        EXPECT_EQ(saver.state, kCorrupt);

    }

}
