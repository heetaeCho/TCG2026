#include <gtest/gtest.h>

#include "db/memtable.h"

#include "leveldb/comparator.h"

#include "leveldb/slice.h"



using namespace leveldb;



class MockComparator : public Comparator {

public:

    MOCK_METHOD(const char*, Name, (), (override));

    MOCK_METHOD(int, Compare, (const Slice& a, const Slice& b), (const, override));

};



class MemTableTest_355 : public ::testing::Test {

protected:

    void SetUp() override {

        mock_comparator = std::make_unique<MockComparator>();

        key_comparator = new MemTable::KeyComparator(*mock_comparator);

    }



    void TearDown() override {

        delete key_comparator;

    }



    std::unique_ptr<MockComparator> mock_comparator;

    MemTable::KeyComparator* key_comparator;

};



TEST_F(MemTableTest_355, CompareSameKeys_355) {

    Slice slice1("same_key");

    Slice slice2("same_key");



    EXPECT_CALL(*mock_comparator, Compare(slice1, slice2)).WillOnce(::testing::Return(0));



    int result = (*key_comparator)("same_key", "same_key");

    EXPECT_EQ(result, 0);

}



TEST_F(MemTableTest_355, CompareDifferentKeys_355) {

    Slice slice1("first_key");

    Slice slice2("second_key");



    EXPECT_CALL(*mock_comparator, Compare(slice1, slice2)).WillOnce(::testing::Return(-1));



    int result = (*key_comparator)("first_key", "second_key");

    EXPECT_EQ(result, -1);

}



TEST_F(MemTableTest_355, CompareKeysWithDifferentLengths_355) {

    Slice slice1("short");

    Slice slice2("longer_key");



    EXPECT_CALL(*mock_comparator, Compare(slice1, slice2)).WillOnce(::testing::Return(1));



    int result = (*key_comparator)("short", "longer_key");

    EXPECT_EQ(result, 1);

}



TEST_F(MemTableTest_355, BoundaryCondition_EmptyKeys_355) {

    Slice slice1("");

    Slice slice2("");



    EXPECT_CALL(*mock_comparator, Compare(slice1, slice2)).WillOnce(::testing::Return(0));



    int result = (*key_comparator)("", "");

    EXPECT_EQ(result, 0);

}



TEST_F(MemTableTest_355, BoundaryCondition_EmptyAndNonEmptyKeys_355) {

    Slice slice1("");

    Slice slice2("non_empty");



    EXPECT_CALL(*mock_comparator, Compare(slice1, slice2)).WillOnce(::testing::Return(-1));



    int result = (*key_comparator)("", "non_empty");

    EXPECT_EQ(result, -1);

}



TEST_F(MemTableTest_355, ExceptionalCase_NullKeys_355) {

    // Assuming the implementation handles null pointers gracefully

    Slice slice1(nullptr, 0);

    Slice slice2("non_empty");



    EXPECT_CALL(*mock_comparator, Compare(slice1, slice2)).WillOnce(::testing::Return(-1));



    int result = (*key_comparator)(nullptr, "non_empty");

    EXPECT_EQ(result, -1);

}
