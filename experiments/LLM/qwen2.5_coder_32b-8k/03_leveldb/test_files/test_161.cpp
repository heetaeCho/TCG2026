#include <gtest/gtest.h>

#include "db/version_set.h"



using namespace leveldb;



class VersionSetBuilderTest : public ::testing::Test {

protected:

    VersionSet* vset_;

    Version* base_version_;

    Builder* builder_;



    void SetUp() override {

        Options options;

        TableCache table_cache(nullptr, 10);

        InternalKeyComparator icmp(options.comparator);

        vset_ = new VersionSet("dbname", &options, &table_cache, &icmp);

        base_version_ = new Version(vset_);

        builder_ = new Builder(vset_, base_version_);

    }



    void TearDown() override {

        delete builder_;

        delete base_version_;

        delete vset_;

    }

};



TEST_F(VersionSetBuilderTest_NormalOperation_161, MaybeAddFile_AddsFileToLevel_161) {

    Version version(vset_);

    FileMetaData file;

    builder_->MaybeAddFile(&version, 1, &file);



    EXPECT_EQ(version.files_[1].size(), 1);

    EXPECT_EQ(version.files_[1][0], &file);

}



TEST_F(VersionSetBuilderTest_BoundaryConditions_161, MaybeAddFile_AddsToFileLevelZero_161) {

    Version version(vset_);

    FileMetaData file;

    builder_->MaybeAddFile(&version, 0, &file);



    EXPECT_EQ(version.files_[0].size(), 1);

    EXPECT_EQ(version.files_[0][0], &file);

}



TEST_F(VersionSetBuilderTest_BoundaryConditions_161, MaybeAddFile_AddsToFileLevelSix_161) {

    Version version(vset_);

    FileMetaData file;

    builder_->MaybeAddFile(&version, 6, &file);



    EXPECT_EQ(version.files_[6].size(), 1);

    EXPECT_EQ(version.files_[6][0], &file);

}



TEST_F(VersionSetBuilderTest_ErrorCases_161, MaybeAddFile_IgnoresDeletedFiles_161) {

    Version version(vset_);

    FileMetaData file;

    file.number = 42;

    builder_->levels_[1].deleted_files.insert(file.number);



    builder_->MaybeAddFile(&version, 1, &file);



    EXPECT_EQ(version.files_[1].size(), 0);

}



TEST_F(VersionSetBuilderTest_NormalOperation_161, MaybeAddFile_IncrementsRefsCount_161) {

    Version version(vset_);

    FileMetaData file;

    builder_->MaybeAddFile(&version, 1, &file);



    EXPECT_EQ(file.refs, 1);

}
