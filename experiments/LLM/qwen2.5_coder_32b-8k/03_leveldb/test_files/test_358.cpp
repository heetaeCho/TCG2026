#include <gtest/gtest.h>

#include "leveldb/memtable.h"

#include "leveldb/slice.h"



using namespace leveldb;



class MockIterator {

public:

    MOCK_METHOD1(Seek, void(const Slice& k));

};



class MemTableIteratorTest_358 : public ::testing::Test {

protected:

    std::unique_ptr<MockIterator> mock_iter_;

    MemTable* mock_table_;

    MemTableIterator* memtable_iterator_;



    void SetUp() override {

        mock_iter_ = std::make_unique<MockIterator>();

        mock_table_ = nullptr; // Since we treat the implementation as a black box, we don't need to instantiate this.

        memtable_iterator_ = new MemTableIterator(mock_table_);

    }



    void TearDown() override {

        delete memtable_iterator_;

    }

};



TEST_F(MemTableIteratorTest_358, SeekCallsInternalSeek_358) {

    Slice key("test_key");

    EXPECT_CALL(*mock_iter_, Seek(EncodeKey(&memtable_iterator_->tmp_, key))).Times(1);

    memtable_iterator_->Seek(key);

}



TEST_F(MemTableIteratorTest_358, SeekWithEmptySliceDoesNotCrash_358) {

    Slice empty_key;

    EXPECT_CALL(*mock_iter_, Seek(EncodeKey(&memtable_iterator_->tmp_, empty_key))).Times(1);

    memtable_iterator_->Seek(empty_key);

}



TEST_F(MemTableIteratorTest_358, SeekBoundaryConditions_358) {

    Slice max_key(std::string(256, '\xFF'));

    EXPECT_CALL(*mock_iter_, Seek(EncodeKey(&memtable_iterator_->tmp_, max_key))).Times(1);

    memtable_iterator_->Seek(max_key);



    Slice min_key;

    EXPECT_CALL(*mock_iter_, Seek(EncodeKey(&memtable_iterator_->tmp_, min_key))).Times(1);

    memtable_iterator_->Seek(min_key);

}



TEST_F(MemTableIteratorTest_358, NormalOperation_SeekTwice_358) {

    Slice key1("key1");

    Slice key2("key2");



    EXPECT_CALL(*mock_iter_, Seek(EncodeKey(&memtable_iterator_->tmp_, key1))).Times(1);

    memtable_iterator_->Seek(key1);



    EXPECT_CALL(*mock_iter_, Seek(EncodeKey(&memtable_iterator_->tmp_, key2))).Times(1);

    memtable_iterator_->Seek(key2);

}
