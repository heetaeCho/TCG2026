#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/memtable.h"



namespace leveldb {



class MemTableIteratorTest_360 : public ::testing::Test {

protected:

    class MockMemTable : public MemTable {

    public:

        MOCK_METHOD(void, SeekToLast, (), (override));

    };



    MockMemTable mock_table;

    MemTableIterator iterator;



    MemTableIteratorTest_360() : iterator(&mock_table) {}

};



TEST_F(MemTableIteratorTest_360, SeekToLast_CallsUnderlyingSeekToLast_360) {

    EXPECT_CALL(mock_table, SeekToLast());

    iterator.SeekToLast();

}



// Assuming there are other methods and behaviors to test, here are some additional examples:



TEST_F(MemTableIteratorTest_360, Valid_ReturnsFalse_WhenNoElements_360) {

    // This is a boundary condition where the iterator is at an invalid state

    EXPECT_CALL(mock_table, SeekToLast());

    iterator.SeekToLast();

    EXPECT_FALSE(iterator.Valid());

}



TEST_F(MemTableIteratorTest_360, Status_ReturnsOk_AfterSeekToLast_360) {

    // Assuming status should be OK after a successful operation

    EXPECT_CALL(mock_table, SeekToLast());

    iterator.SeekToLast();

    EXPECT_EQ(iterator.status().ok(), true);

}



// Exceptional or error cases (if observable through the interface)

TEST_F(MemTableIteratorTest_360, Status_ReturnsError_WhenSeekFails_360) {

    // Assuming there's a way to simulate a failure in SeekToLast

    EXPECT_CALL(mock_table, SeekToLast()).WillOnce(testing::Invoke([&]() {

        // Simulate some error condition

        mock_table.SetStatus(Status::IOError("Simulated error"));

    }));

    iterator.SeekToLast();

    EXPECT_EQ(iterator.status().ok(), false);

}



}  // namespace leveldb
