#include <gtest/gtest.h>

#include "db/version_set.cc"



using namespace leveldb;



class LevelFileNumIteratorTest_138 : public ::testing::Test {

protected:

    void SetUp() override {

        FileMetaData* file_meta_data = new FileMetaData();

        flist.push_back(file_meta_data);

        iterator = std::make_unique<LevelFileNumIterator>(InternalKeyComparator(BytewiseComparator()), &flist);

    }



    void TearDown() override {

        for (auto& file : flist) {

            delete file;

        }

        flist.clear();

    }



    std::vector<FileMetaData*> flist;

    std::unique_ptr<LevelFileNumIterator> iterator;

};



TEST_F(LevelFileNumIteratorTest_138, SeekToLastOnNonEmptySet_138) {

    iterator->SeekToLast();

    EXPECT_EQ(iterator->index_, 0);

}



TEST_F(LevelFileNumIteratorTest_138, SeekToLastOnEmptySet_138) {

    flist.clear();

    iterator = std::make_unique<LevelFileNumIterator>(InternalKeyComparator(BytewiseComparator()), &flist);

    iterator->SeekToLast();

    EXPECT_EQ(iterator->index_, 0);

}



TEST_F(LevelFileNumIteratorTest_138, ValidAfterSeekToLastOnNonEmptySet_138) {

    iterator->SeekToLast();

    EXPECT_TRUE(iterator->Valid());

}



TEST_F(LevelFileNumIteratorTest_138, InvalidAfterSeekToLastOnEmptySet_138) {

    flist.clear();

    iterator = std::make_unique<LevelFileNumIterator>(InternalKeyComparator(BytewiseComparator()), &flist);

    iterator->SeekToLast();

    EXPECT_FALSE(iterator->Valid());

}
