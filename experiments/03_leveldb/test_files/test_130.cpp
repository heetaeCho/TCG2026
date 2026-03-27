#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_edit.h"

#include "db/version_set.cc"  // Including the implementation file for TotalFileSize



namespace leveldb {



class VersionSetTest_130 : public ::testing::Test {

protected:

    std::vector<FileMetaData*> files;

};



TEST_F(VersionSetTest_130, TotalFileSize_EmptyVector_ReturnsZero_130) {

    EXPECT_EQ(TotalFileSize(files), 0);

}



TEST_F(VersionSetTest_130, TotalFileSize_SingleFile_ReturnsFileSize_130) {

    FileMetaData* file = new FileMetaData();

    file->file_size = 1024;

    files.push_back(file);



    EXPECT_EQ(TotalFileSize(files), 1024);



    delete file;  // Clean up allocated memory

}



TEST_F(VersionSetTest_130, TotalFileSize_MultipleFiles_ReturnsSumOfFileSizes_130) {

    FileMetaData* file1 = new FileMetaData();

    file1->file_size = 512;

    files.push_back(file1);



    FileMetaData* file2 = new FileMetaData();

    file2->file_size = 2048;

    files.push_back(file2);



    EXPECT_EQ(TotalFileSize(files), 2560);



    delete file1;  // Clean up allocated memory

    delete file2;  // Clean up allocated memory

}



TEST_F(VersionSetTest_130, TotalFileSize_MaxFileSize_ReturnsMaxValue_130) {

    FileMetaData* file = new FileMetaData();

    file->file_size = std::numeric_limits<int64_t>::max();

    files.push_back(file);



    EXPECT_EQ(TotalFileSize(files), std::numeric_limits<int64_t>::max());



    delete file;  // Clean up allocated memory

}



TEST_F(VersionSetTest_130, TotalFileSize_LargeFiles_SumWithinInt64Range_130) {

    FileMetaData* file1 = new FileMetaData();

    file1->file_size = std::numeric_limits<int64_t>::max() / 2;

    files.push_back(file1);



    FileMetaData* file2 = new FileMetaData();

    file2->file_size = std::numeric_limits<int64_t>::max() / 2 - 1;

    files.push_back(file2);



    EXPECT_EQ(TotalFileSize(files), std::numeric_limits<int64_t>::max() - 1);



    delete file1;  // Clean up allocated memory

    delete file2;  // Clean up allocated memory

}



TEST_F(VersionSetTest_130, TotalFileSize_LargeFiles_SumExceedsInt64Range_ReturnsNegativeValue_130) {

    FileMetaData* file1 = new FileMetaData();

    file1->file_size = std::numeric_limits<int64_t>::max();

    files.push_back(file1);



    FileMetaData* file2 = new FileMetaData();

    file2->file_size = 1;

    files.push_back(file2);



    // Since the sum exceeds int64_t, we expect a negative value due to overflow

    EXPECT_LT(TotalFileSize(files), 0);



    delete file1;  // Clean up allocated memory

    delete file2;  // Clean up allocated memory

}



}  // namespace leveldb
