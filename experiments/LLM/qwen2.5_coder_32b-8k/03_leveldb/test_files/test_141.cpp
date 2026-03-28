#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "db/dbformat.h"



using namespace leveldb;

using ::testing::Return;

using ::testing::_;



class VersionTest_141 : public ::testing::Test {

protected:

    std::vector<FileMetaData*> file_list_;

    InternalKeyComparator icmp_;

    LevelFileNumIterator* iterator_;



    void SetUp() override {

        iterator_ = new LevelFileNumIterator(icmp_, &file_list_);

    }



    void TearDown() override {

        delete iterator_;

        for (auto& file : file_list_) {

            delete file;

        }

        file_list_.clear();

    }

};



TEST_F(VersionTest_141, Valid_ReturnsFalseWhenEmpty_141) {

    EXPECT_FALSE(iterator_->Valid());

}



TEST_F(VersionTest_141, SeekToFirst_SetsIndexToZeroWhenNotEmpty_141) {

    file_list_.push_back(new FileMetaData());

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->index_, 0);

}



TEST_F(VersionTest_141, SeekToLast_SetsIndexToLastElementWhenNotEmpty_141) {

    file_list_.push_back(new FileMetaData());

    file_list_.push_back(new FileMetaData());

    iterator_->SeekToLast();

    EXPECT_EQ(iterator_->index_, 1);

}



TEST_F(VersionTest_141, Next_IncrementsIndex_141) {

    file_list_.push_back(new FileMetaData());

    file_list_.push_back(new FileMetaData());

    iterator_->SeekToFirst();

    iterator_->Next();

    EXPECT_EQ(iterator_->index_, 1);

}



TEST_F(VersionTest_141, Prev_DecrementsIndex_141) {

    file_list_.push_back(new FileMetaData());

    file_list_.push_back(new FileMetaData());

    iterator_->SeekToLast();

    iterator_->Prev();

    EXPECT_EQ(iterator_->index_, 0);

}



TEST_F(VersionTest_141, Key_ReturnsLargestEncodeWhenValid_141) {

    auto* meta = new FileMetaData();

    meta->largest.SetFrom(ParsedInternalKey(Slice("test_key"), 123, kTypeValue));

    file_list_.push_back(meta);

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->key().ToString(), "test_key\x00\x00\x00\x00\x00\x00\x00{");

}



TEST_F(VersionTest_141, Status_ReturnsOkWhenValid_141) {

    file_list_.push_back(new FileMetaData());

    iterator_->SeekToFirst();

    EXPECT_EQ(iterator_->status().ok(), true);

}
