#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "db/memtable.cc"  // Assuming MemTableIterator is included here



using namespace leveldb;



class MockMemTable : public MemTable {

public:

    MOCK_METHOD(void, Add, (const Slice& key, const Slice& value), (override));

};



class MemTableIteratorTest_365 : public ::testing::Test {

protected:

    std::unique_ptr<MockMemTable> mock_memtable;

    std::unique_ptr<MemTableIterator> iterator;



    void SetUp() override {

        mock_memtable = std::make_unique<MockMemTable>();

        iterator = std::make_unique<MemTableIterator>(mock_memtable.get());

    }

};



TEST_F(MemTableIteratorTest_365, StatusIsOK_365) {

    EXPECT_EQ(iterator->status(), Status::OK());

}



TEST_F(MemTableIteratorTest_365, ValidInitiallyReturnsFalse_365) {

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_365, SeekToFirstOnEmptyMemTable_365) {

    iterator->SeekToFirst();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_365, SeekToLastOnEmptyMemTable_365) {

    iterator->SeekToLast();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_365, NextOnEmptyMemTable_365) {

    iterator->Next();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_365, PrevOnEmptyMemTable_365) {

    iterator->Prev();

    EXPECT_FALSE(iterator->Valid());

}



// Assuming MemTable::Add can be used to populate the memtable

TEST_F(MemTableIteratorTest_365, SeekToFirstFindsFirstElement_365) {

    mock_memtable->Add(Slice("key1"), Slice("value1"));

    mock_memtable->Add(Slice("key2"), Slice("value2"));



    iterator->SeekToFirst();

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key1");

}



TEST_F(MemTableIteratorTest_365, SeekToLastFindsLastElement_365) {

    mock_memtable->Add(Slice("key1"), Slice("value1"));

    mock_memtable->Add(Slice("key2"), Slice("value2"));



    iterator->SeekToLast();

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key2");

}



TEST_F(MemTableIteratorTest_365, NextTraversesInOrder_365) {

    mock_memtable->Add(Slice("key1"), Slice("value1"));

    mock_memtable->Add(Slice("key2"), Slice("value2"));



    iterator->SeekToFirst();

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key1");



    iterator->Next();

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key2");



    iterator->Next();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_365, PrevTraversesInReverseOrder_365) {

    mock_memtable->Add(Slice("key1"), Slice("value1"));

    mock_memtable->Add(Slice("key2"), Slice("value2"));



    iterator->SeekToLast();

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key2");



    iterator->Prev();

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key1");



    iterator->Prev();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(MemTableIteratorTest_365, SeekFindsExactMatch_365) {

    mock_memtable->Add(Slice("key1"), Slice("value1"));

    mock_memtable->Add(Slice("key2"), Slice("value2"));



    iterator->Seek(Slice("key1"));

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key1");



    iterator->Seek(Slice("key2"));

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key2");

}



TEST_F(MemTableIteratorTest_365, SeekFindsNextKeyIfExactMatchNotFound_365) {

    mock_memtable->Add(Slice("key1"), Slice("value1"));

    mock_memtable->Add(Slice("key3"), Slice("value3"));



    iterator->Seek(Slice("key2"));

    EXPECT_TRUE(iterator->Valid());

    EXPECT_EQ(iterator->key().ToString(), "key3");

}
