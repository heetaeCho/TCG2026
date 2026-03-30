#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"



namespace leveldb {



class MockInternalKeyComparator : public InternalKeyComparator {

public:

    MOCK_CONST_METHOD1(Compare, int(const Slice&, const Slice&));

};



class LevelFileNumIteratorTest_137 : public ::testing::Test {

protected:

    void SetUp() override {

        flist = std::make_shared<std::vector<FileMetaData*>>();

        icmp = new MockInternalKeyComparator();

        iterator = new LevelFileNumIterator(*icmp, flist.get());

    }



    void TearDown() override {

        delete iterator;

        delete icmp;

    }



    MockInternalKeyComparator* icmp;

    std::shared_ptr<std::vector<FileMetaData*>> flist;

    LevelFileNumIterator* iterator;

};



TEST_F(LevelFileNumIteratorTest_137, SeekToFirstOnEmptyList_137) {

    iterator->SeekToFirst();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(LevelFileNumIteratorTest_137, SeekToFirstOnNonEmptyList_137) {

    flist->push_back(new FileMetaData());

    iterator->SeekToFirst();

    EXPECT_TRUE(iterator->Valid());

}



TEST_F(LevelFileNumIteratorTest_137, ValidAfterSeekToFirst_137) {

    flist->push_back(new FileMetaData());

    flist->push_back(new FileMetaData());

    iterator->SeekToFirst();

    EXPECT_TRUE(iterator->Valid());

    iterator->Next();

    EXPECT_TRUE(iterator->Valid());

    iterator->Next();

    EXPECT_FALSE(iterator->Valid());

}



TEST_F(LevelFileNumIteratorTest_137, KeyAndValueAccessors_137) {

    flist->push_back(new FileMetaData());

    iterator->SeekToFirst();

    EXPECT_NO_THROW(iterator->key());

    EXPECT_NO_THROW(iterator->value());

}



TEST_F(LevelFileNumIteratorTest_137, StatusAccessor_137) {

    iterator->SeekToFirst();

    EXPECT_EQ(Status::OK(), iterator->status());

}



}  // namespace leveldb
