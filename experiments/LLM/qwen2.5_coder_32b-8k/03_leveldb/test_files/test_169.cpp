#include <gtest/gtest.h>

#include "db/version_set.h"

#include <set>



using namespace leveldb;



class VersionSetTest_169 : public ::testing::Test {

protected:

    VersionSetTest_169() {

        options = new Options();

        table_cache = new TableCache(options, 10);

        icmp = new InternalKeyComparator(BytewiseComparator());

        version_set = new VersionSet("/tmp/testdb", options, table_cache, icmp);

    }



    ~VersionSetTest_169() {

        delete version_set;

        delete icmp;

        delete table_cache;

        delete options;

    }



    Options* options;

    TableCache* table_cache;

    InternalKeyComparator* icmp;

    VersionSet* version_set;

};



TEST_F(VersionSetTest_169, AddLiveFiles_NoFiles_169) {

    std::set<uint64_t> live_files;

    version_set->AddLiveFiles(&live_files);

    EXPECT_TRUE(live_files.empty());

}



TEST_F(VersionSetTest_169, AddLiveFiles_SingleFile_169) {

    FileMetaData* file = new FileMetaData();

    file->number = 1;



    Version* version = new Version(version_set);

    version->files_[0].push_back(file);



    version_set->dummy_versions_.next_->next_ = version;

    version->prev_ = &version_set->dummy_versions_;

    version_set->dummy_versions_.next_->next_->next_ = &version_set->dummy_versions_;



    std::set<uint64_t> live_files;

    version_set->AddLiveFiles(&live_files);

    EXPECT_EQ(live_files.size(), 1);

    EXPECT_TRUE(live_files.find(1) != live_files.end());



    // Cleanup

    delete file;

}



TEST_F(VersionSetTest_169, AddLiveFiles_MultipleLevelsMultipleFiles_169) {

    FileMetaData* file1 = new FileMetaData();

    file1->number = 1;

    FileMetaData* file2 = new FileMetaData();

    file2->number = 2;



    Version* version = new Version(version_set);

    version->files_[0].push_back(file1);

    version->files_[1].push_back(file2);



    version_set->dummy_versions_.next_->next_ = version;

    version->prev_ = &version_set->dummy_versions_;

    version_set->dummy_versions_.next_->next_->next_ = &version_set->dummy_versions_;



    std::set<uint64_t> live_files;

    version_set->AddLiveFiles(&live_files);

    EXPECT_EQ(live_files.size(), 2);

    EXPECT_TRUE(live_files.find(1) != live_files.end());

    EXPECT_TRUE(live_files.find(2) != live_files.end());



    // Cleanup

    delete file1;

    delete file2;

}



TEST_F(VersionSetTest_169, AddLiveFiles_DuplicateFileNumbers_169) {

    FileMetaData* file1 = new FileMetaData();

    file1->number = 1;

    FileMetaData* file2 = new FileMetaData();

    file2->number = 1;



    Version* version = new Version(version_set);

    version->files_[0].push_back(file1);

    version->files_[1].push_back(file2);



    version_set->dummy_versions_.next_->next_ = version;

    version->prev_ = &version_set->dummy_versions_;

    version_set->dummy_versions_.next_->next_->next_ = &version_set->dummy_versions_;



    std::set<uint64_t> live_files;

    version_set->AddLiveFiles(&live_files);

    EXPECT_EQ(live_files.size(), 1);

    EXPECT_TRUE(live_files.find(1) != live_files.end());



    // Cleanup

    delete file1;

    delete file2;

}
