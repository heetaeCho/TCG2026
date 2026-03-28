#include <gtest/gtest.h>

#include "db/version_set.h"

#include "db/file_metadata.h"



using namespace leveldb;



class VersionSetTest_158 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize any necessary objects or variables here if needed

    }



    void TearDown() override {

        // Clean up any resources if needed

    }

};



TEST_F(VersionSetTest_158, BuilderDestructorDeletesAddedFiles_158) {

    VersionSet vset;

    Version base_version(&vset);

    VersionSet::Builder builder(&vset, &base_version);



    FileMetaData* file = new FileMetaData();

    file->refs = 1; // Increment ref count to ensure it gets deleted



    builder.MaybeAddFile(nullptr, 0, file);



    EXPECT_EQ(1, file->refs); // Check that the file was added correctly



    // Destructor should be called here and we expect file to be deleted

}



TEST_F(VersionSetTest_158, BuilderDestructorHandlesMultipleFiles_158) {

    VersionSet vset;

    Version base_version(&vset);

    VersionSet::Builder builder(&vset, &base_version);



    FileMetaData* file1 = new FileMetaData();

    FileMetaData* file2 = new FileMetaData();



    file1->refs = 1; // Increment ref count to ensure it gets deleted

    file2->refs = 1; // Increment ref count to ensure it gets deleted



    builder.MaybeAddFile(nullptr, 0, file1);

    builder.MaybeAddFile(nullptr, 1, file2);



    EXPECT_EQ(1, file1->refs); // Check that the files were added correctly

    EXPECT_EQ(1, file2->refs); // Check that the files were added correctly



    // Destructor should be called here and we expect both files to be deleted

}



TEST_F(VersionSetTest_158, BuilderDestructorHandlesZeroRefs_158) {

    VersionSet vset;

    Version base_version(&vset);

    VersionSet::Builder builder(&vset, &base_version);



    FileMetaData* file = new FileMetaData();

    // No need to increment ref count



    builder.MaybeAddFile(nullptr, 0, file);



    EXPECT_EQ(0, file->refs); // Check that the file was added correctly



    // Destructor should be called here and we expect file not to be deleted

}



TEST_F(VersionSetTest_158, BuilderDestructorHandlesMultipleLevels_158) {

    VersionSet vset;

    Version base_version(&vset);

    VersionSet::Builder builder(&vset, &base_version);



    FileMetaData* file1 = new FileMetaData();

    FileMetaData* file2 = new FileMetaData();



    file1->refs = 1; // Increment ref count to ensure it gets deleted

    file2->refs = 1; // Increment ref count to ensure it gets deleted



    builder.MaybeAddFile(nullptr, 0, file1);

    builder.MaybeAddFile(nullptr, config::kNumLevels - 1, file2);



    EXPECT_EQ(1, file1->refs); // Check that the files were added correctly

    EXPECT_EQ(1, file2->refs); // Check that the files were added correctly



    // Destructor should be called here and we expect both files to be deleted

}



TEST_F(VersionSetTest_158, BuilderDestructorHandlesMaxLevel_158) {

    VersionSet vset;

    Version base_version(&vset);

    VersionSet::Builder builder(&vset, &base_version);



    FileMetaData* file = new FileMetaData();

    file->refs = 1; // Increment ref count to ensure it gets deleted



    builder.MaybeAddFile(nullptr, config::kNumLevels - 1, file);



    EXPECT_EQ(1, file->refs); // Check that the file was added correctly



    // Destructor should be called here and we expect file to be deleted

}



TEST_F(VersionSetTest_158, BuilderDestructorHandlesMinLevel_158) {

    VersionSet vset;

    Version base_version(&vset);

    VersionSet::Builder builder(&vset, &base_version);



    FileMetaData* file = new FileMetaData();

    file->refs = 1; // Increment ref count to ensure it gets deleted



    builder.MaybeAddFile(nullptr, 0, file);



    EXPECT_EQ(1, file->refs); // Check that the file was added correctly



    // Destructor should be called here and we expect file to be deleted

}
