#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "db/version_set.h"

#include "leveldb/status.h"



using namespace leveldb;

using ::testing::Return;



class VersionSetTest_143 : public ::testing::Test {

protected:

    InternalKeyComparator icmp_;

    std::vector<FileMetaData*> file_metadata_list_;

    LevelFileNumIterator* iterator_;



    void SetUp() override {

        iterator_ = new LevelFileNumIterator(icmp_, &file_metadata_list_);

    }



    void TearDown() override {

        delete iterator_;

    }

};



TEST_F(VersionSetTest_143, StatusInitiallyOk_143) {

    EXPECT_EQ(iterator_->status().ok(), true);

}



TEST_F(VersionSetTest_143, ValidReturnsFalseForEmptyList_143) {

    EXPECT_EQ(iterator_->Valid(), false);

}



TEST_F(VersionSetTest_143, SeekToFirstDoesNothingOnEmptyList_143) {

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->Valid(), false);

}



TEST_F(VersionSetTest_143, SeekToLastDoesNothingOnEmptyList_143) {

    iterator_->SeekToLast();

    EXPECT_EQ(iterator_->Valid(), false);

}



TEST_F(VersionSetTest_143, NextDoesNothingOnEmptyList_143) {

    iterator_->Next();

    EXPECT_EQ(iterator_->Valid(), false);

}



TEST_F(VersionSetTest_143, PrevDoesNothingOnEmptyList_143) {

    iterator_->Prev();

    EXPECT_EQ(iterator_->Valid(), false);

}



TEST_F(VersionSetTest_143, KeyThrowsWhenInvalid_143) {

    EXPECT_THROW(iterator_->key(), std::exception);

}



TEST_F(VersionSetTest_143, ValueThrowsWhenInvalid_143) {

    EXPECT_THROW(iterator_->value(), std::exception);

}



TEST_F(VersionSetTest_143, ValidReturnsTrueForNonEmptyList_143) {

    file_metadata_list_.push_back(new FileMetaData());

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->Valid(), true);

    delete file_metadata_list_[0];

}



TEST_F(VersionSetTest_143, SeekToFirstSetsIteratorToStart_143) {

    file_metadata_list_.push_back(new FileMetaData());

    file_metadata_list_.push_back(new FileMetaData());

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->Valid(), true);

    delete file_metadata_list_[0];

    delete file_metadata_list_[1];

}



TEST_F(VersionSetTest_143, SeekToLastSetsIteratorToEnd_143) {

    file_metadata_list_.push_back(new FileMetaData());

    file_metadata_list_.push_back(new FileMetaData());

    iterator_->SeekToLast();

    EXPECT_EQ(iterator_->Valid(), true);

    delete file_metadata_list_[0];

    delete file_metadata_list_[1];

}



TEST_F(VersionSetTest_143, NextMovesIteratorForward_143) {

    file_metadata_list_.push_back(new FileMetaData());

    file_metadata_list_.push_back(new FileMetaData());

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->Valid(), true);

    iterator_->Next();

    EXPECT_EQ(iterator_->Valid(), true);

    delete file_metadata_list_[0];

    delete file_metadata_list_[1];

}



TEST_F(VersionSetTest_143, PrevMovesIteratorBackward_143) {

    file_metadata_list_.push_back(new FileMetaData());

    file_metadata_list_.push_back(new FileMetaData());

    iterator_->SeekToLast();

    EXPECT_EQ(iterator_->Valid(), true);

    iterator_->Prev();

    EXPECT_EQ(iterator_->Valid(), true);

    delete file_metadata_list_[0];

    delete file_metadata_list_[1];

}
