#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "db/table_cache.h"

#include "db/dbformat.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;

using ::testing::ElementsAre;



class MockTableCache : public TableCache {

public:

    MOCK_METHOD4(NewIterator, Iterator*(const ReadOptions&, uint64_t, uint64_t, Table**));

};



class VersionSetTest_168 : public ::testing::Test {

protected:

    void SetUp() override {

        Options options;

        env = Env::Default();

        dbname = "testdb";

        icmp = new InternalKeyComparator(BytewiseComparator());

        table_cache = new MockTableCache(dbname, options, 10);

        version_set = new VersionSet(dbname, &options, table_cache, icmp);

    }



    void TearDown() override {

        delete version_set;

        delete table_cache;

        delete icmp;

    }



    Env* env;

    std::string dbname;

    InternalKeyComparator* icmp;

    MockTableCache* table_cache;

    VersionSet* version_set;

};



TEST_F(VersionSetTest_168, ApproximateOffsetOf_EmptyVersionSet_168) {

    Version empty_version(version_set);

    InternalKey ikey("test_key", 0, kValueTypeForSeek);

    EXPECT_EQ(version_set->ApproximateOffsetOf(&empty_version, ikey), 0U);

}



TEST_F(VersionSetTest_168, ApproximateOffsetOf_SingleFileWithinRange_168) {

    Version version(version_set);



    FileMetaData* file = new FileMetaData();

    file->smallest = InternalKey("a", 0, kValueTypeForSeek);

    file->largest = InternalKey("z", 0, kValueTypeForSeek);

    file->file_size = 1024;

    file->number = 1;



    version.files_[0].push_back(file);



    InternalKey ikey("m", 0, kValueTypeForSeek);

    EXPECT_EQ(version_set->ApproximateOffsetOf(&version, ikey), 0U);



    delete file;

}



TEST_F(VersionSetTest_168, ApproximateOffsetOf_SingleFileOutsideRange_LargerThanLargest_168) {

    Version version(version_set);



    FileMetaData* file = new FileMetaData();

    file->smallest = InternalKey("a", 0, kValueTypeForSeek);

    file->largest = InternalKey("z", 0, kValueTypeForSeek);

    file->file_size = 1024;

    file->number = 1;



    version.files_[0].push_back(file);



    InternalKey ikey("zz", 0, kValueTypeForSeek);

    EXPECT_EQ(version_set->ApproximateOffsetOf(&version, ikey), 1024U);



    delete file;

}



TEST_F(VersionSetTest_168, ApproximateOffsetOf_SingleFileOutsideRange_SmallerThanSmallest_168) {

    Version version(version_set);



    FileMetaData* file = new FileMetaData();

    file->smallest = InternalKey("a", 0, kValueTypeForSeek);

    file->largest = InternalKey("z", 0, kValueTypeForSeek);

    file->file_size = 1024;

    file->number = 1;



    version.files_[0].push_back(file);



    InternalKey ikey("aa", 0, kValueTypeForSeek);

    EXPECT_EQ(version_set->ApproximateOffsetOf(&version, ikey), 0U);



    delete file;

}



TEST_F(VersionSetTest_168, ApproximateOffsetOf_MultipleFiles_168) {

    Version version(version_set);



    FileMetaData* file1 = new FileMetaData();

    file1->smallest = InternalKey("a", 0, kValueTypeForSeek);

    file1->largest = InternalKey("m", 0, kValueTypeForSeek);

    file1->file_size = 512;

    file1->number = 1;



    FileMetaData* file2 = new FileMetaData();

    file2->smallest = InternalKey("n", 0, kValueTypeForSeek);

    file2->largest = InternalKey("z", 0, kValueTypeForSeek);

    file2->file_size = 512;

    file2->number = 2;



    version.files_[0].push_back(file1);

    version.files_[0].push_back(file2);



    InternalKey ikey("o", 0, kValueTypeForSeek);

    EXPECT_EQ(version_set->ApproximateOffsetOf(&version, ikey), 512U);



    delete file1;

    delete file2;

}



TEST_F(VersionSetTest_168, ApproximateOffsetOf_TableCacheInteraction_168) {

    Version version(version_set);



    FileMetaData* file = new FileMetaData();

    file->smallest = InternalKey("a", 0, kValueTypeForSeek);

    file->largest = InternalKey("z", 0, kValueTypeForSeek);

    file->file_size = 1024;

    file->number = 1;



    version.files_[0].push_back(file);



    Table* tableptr = nullptr;

    Iterator* iter = new MockIterator();

    EXPECT_CALL(*table_cache, NewIterator(_, 1, 1024, _))

        .WillOnce(DoAll(SetArgReferee<3>(tableptr), Return(iter)));



    InternalKey ikey("m", 0, kValueTypeForSeek);

    EXPECT_EQ(version_set->ApproximateOffsetOf(&version, ikey), 0U);



    delete file;

    delete iter;

}
