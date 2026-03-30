#include "gtest/gtest.h"

#include "db/version_set.h"

#include <vector>

#include <set>



using namespace leveldb;



class LevelFileNumIteratorTest : public ::testing::Test {

protected:

    InternalKeyComparator icmp_;

    std::vector<FileMetaData*> file_meta_data_vec_;

    FileMetaData* file_meta_data_1;

    FileMetaData* file_meta_data_2;

    LevelFileNumIterator* iterator_;



    void SetUp() override {

        file_meta_data_1 = new FileMetaData();

        file_meta_data_2 = new FileMetaData();

        

        file_meta_data_1->number = 1;

        file_meta_data_1->file_size = 1024;

        file_meta_data_2->number = 2;

        file_meta_data_2->file_size = 2048;



        file_meta_data_vec_.push_back(file_meta_data_1);

        file_meta_data_vec_.push_back(file_meta_data_2);



        iterator_ = new LevelFileNumIterator(icmp_, &file_meta_data_vec_);

    }



    void TearDown() override {

        delete iterator_;

        delete file_meta_data_1;

        delete file_meta_data_2;

    }

};



TEST_F(LevelFileNumIteratorTest_142, ValidReturnsTrueWhenIndexIsValid_142) {

    iterator_->SeekToFirst();

    EXPECT_TRUE(iterator_->Valid());

}



TEST_F(LevelFileNumIteratorTest_142, ValidReturnsFalseWhenIndexIsInvalid_142) {

    iterator_->index_ = file_meta_data_vec_.size();

    EXPECT_FALSE(iterator_->Valid());

}



TEST_F(LevelFileNumIteratorTest_142, SeekToFirstSetsIndexToZero_142) {

    iterator_->SeekToFirst();

    EXPECT_EQ(0U, iterator_->index_);

}



TEST_F(LevelFileNumIteratorTest_142, SeekToLastSetsIndexToLastElement_142) {

    iterator_->SeekToLast();

    EXPECT_EQ(file_meta_data_vec_.size() - 1U, iterator_->index_);

}



TEST_F(LevelFileNumIteratorTest_142, NextIncrementsIndex_142) {

    iterator_->SeekToFirst();

    iterator_->Next();

    EXPECT_EQ(1U, iterator_->index_);

}



TEST_F(LevelFileNumIteratorTest_142, PrevDecrementsIndex_142) {

    iterator_->SeekToLast();

    iterator_->Prev();

    EXPECT_EQ(file_meta_data_vec_.size() - 2U, iterator_->index_);

}



TEST_F(LevelFileNumIteratorTest_142, ValueReturnsEncodedValue_142) {

    iterator_->SeekToFirst();

    Slice value = iterator_->value();

    uint64_t number;

    uint64_t file_size;

    memcpy(&number, value.data(), sizeof(number));

    memcpy(&file_size, value.data() + 8, sizeof(file_size));



    EXPECT_EQ(1U, number);

    EXPECT_EQ(1024U, file_size);

}



TEST_F(LevelFileNumIteratorTest_142, StatusReturnsOK_142) {

    EXPECT_TRUE(iterator_->status().ok());

}
