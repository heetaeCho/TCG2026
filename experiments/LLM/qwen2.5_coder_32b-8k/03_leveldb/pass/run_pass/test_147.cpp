#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_edit.h"



namespace leveldb {



class FileMetaDataComparator {

public:

    bool operator()(FileMetaData* a, FileMetaData* b) const {

        return a->number > b->number;

    }

};



using FileSet = std::set<FileMetaData*, FileMetaDataComparator>;



class VersionSetTest_147 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup any common state before tests (if needed).

    }



    void TearDown() override {

        // Cleanup any common state after tests (if needed).

        for (auto file : file_set_) {

            delete file;

        }

        file_set_.clear();

    }



    FileSet file_set_;

};



TEST_F(VersionSetTest_147, InsertFileMetaData_147) {

    FileMetaData* meta = new FileMetaData();

    meta->number = 10;

    file_set_.insert(meta);

    EXPECT_EQ(file_set_.size(), 1);

}



TEST_F(VersionSetTest_147, InsertMultipleFiles_147) {

    FileMetaData* meta1 = new FileMetaData();

    meta1->number = 10;

    FileMetaData* meta2 = new FileMetaData();

    meta2->number = 20;



    file_set_.insert(meta1);

    file_set_.insert(meta2);



    EXPECT_EQ(file_set_.size(), 2);

}



TEST_F(VersionSetTest_147, InsertDuplicateFileNumber_147) {

    FileMetaData* meta1 = new FileMetaData();

    meta1->number = 10;

    FileMetaData* meta2 = new FileMetaData();

    meta2->number = 10;



    file_set_.insert(meta1);

    file_set_.insert(meta2);



    EXPECT_EQ(file_set_.size(), 1); // Should not insert duplicate

}



TEST_F(VersionSetTest_147, InsertFilesNewestFirst_147) {

    FileMetaData* meta1 = new FileMetaData();

    meta1->number = 10;

    FileMetaData* meta2 = new FileMetaData();

    meta2->number = 20;



    file_set_.insert(meta1);

    file_set_.insert(meta2);



    auto it = file_set_.begin();

    EXPECT_EQ((*it)->number, 20); // Newest first

}



TEST_F(VersionSetTest_147, EraseFileMetaData_147) {

    FileMetaData* meta = new FileMetaData();

    meta->number = 10;

    file_set_.insert(meta);



    file_set_.erase(meta);

    EXPECT_EQ(file_set_.size(), 0);

}



TEST_F(VersionSetTest_147, EraseNonExistingFile_147) {

    FileMetaData* meta = new FileMetaData();

    meta->number = 10;

    file_set_.insert(meta);



    FileMetaData* meta2 = new FileMetaData();

    meta2->number = 20;



    file_set_.erase(meta2);

    EXPECT_EQ(file_set_.size(), 1); // Should not change size

}



TEST_F(VersionSetTest_147, BoundaryCondition_EmptyFileSet_147) {

    EXPECT_EQ(file_set_.size(), 0);

}



} // namespace leveldb
