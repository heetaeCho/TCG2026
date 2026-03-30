#include <gtest/gtest.h>

#include "db/version_edit.h"



using namespace leveldb;



class VersionEditTest_68 : public ::testing::Test {

protected:

    VersionEdit* version_edit_;



    void SetUp() override {

        version_edit_ = new VersionEdit();

    }



    void TearDown() override {

        delete version_edit_;

    }

};



TEST_F(VersionEditTest_68, RemoveFile_AddsToFileSet_68) {

    int level = 0;

    uint64_t file = 100;



    version_edit_->RemoveFile(level, file);

    const auto& deleted_files = version_edit_->deleted_files_;



    EXPECT_EQ(deleted_files.size(), 1);

    EXPECT_TRUE(deleted_files.find(std::make_pair(level, file)) != deleted_files.end());

}



TEST_F(VersionEditTest_68, RemoveFile_MultipleFiles_68) {

    int level1 = 0;

    uint64_t file1 = 100;

    int level2 = 1;

    uint64_t file2 = 200;



    version_edit_->RemoveFile(level1, file1);

    version_edit_->RemoveFile(level2, file2);



    const auto& deleted_files = version_edit_->deleted_files_;

    EXPECT_EQ(deleted_files.size(), 2);

    EXPECT_TRUE(deleted_files.find(std::make_pair(level1, file1)) != deleted_files.end());

    EXPECT_TRUE(deleted_files.find(std::make_pair(level2, file2)) != deleted_files.end());

}



TEST_F(VersionEditTest_68, RemoveFile_SameFileMultipleTimes_68) {

    int level = 0;

    uint64_t file = 100;



    version_edit_->RemoveFile(level, file);

    version_edit_->RemoveFile(level, file);



    const auto& deleted_files = version_edit_->deleted_files_;

    EXPECT_EQ(deleted_files.size(), 1); // Set should not allow duplicates

    EXPECT_TRUE(deleted_files.find(std::make_pair(level, file)) != deleted_files.end());

}



TEST_F(VersionEditTest_68, RemoveFile_NegativeLevel_68) {

    int level = -1;

    uint64_t file = 100;



    version_edit_->RemoveFile(level, file);

    const auto& deleted_files = version_edit_->deleted_files_;



    EXPECT_EQ(deleted_files.size(), 1);

    EXPECT_TRUE(deleted_files.find(std::make_pair(level, file)) != deleted_files.end());

}



TEST_F(VersionEditTest_68, RemoveFile_ZeroLevel_68) {

    int level = 0;

    uint64_t file = 0;



    version_edit_->RemoveFile(level, file);

    const auto& deleted_files = version_edit_->deleted_files_;



    EXPECT_EQ(deleted_files.size(), 1);

    EXPECT_TRUE(deleted_files.find(std::make_pair(level, file)) != deleted_files.end());

}
