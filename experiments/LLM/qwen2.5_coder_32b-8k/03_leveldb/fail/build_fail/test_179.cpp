#include <gtest/gtest.h>

#include "db/version_set.h"

#include <gmock/gmock.h>



using namespace leveldb;



class MockVersion : public Version {

public:

    MOCK_METHOD1(NumFiles, int(int level)) const;

};



class CompactionTest_179 : public ::testing::Test {

protected:

    void SetUp() override {

        options = new Options();

        input_version = new MockVersion();

        compaction = new Compaction(options, 0);

        compaction->input_version_ = input_version;

    }



    void TearDown() override {

        delete compaction;

        delete input_version;

        delete options;

    }



    Options* options;

    MockVersion* input_version;

    Compaction* compaction;

};



TEST_F(CompactionTest_179, IsTrivialMove_NormalOperation_NoOverlap_179) {

    EXPECT_CALL(*input_version, NumFiles(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*input_version, NumFiles(1)).WillOnce(::testing::Return(0));



    compaction->grandparents_.clear(); // Ensure no grandparents

    bool result = compaction->IsTrivialMove();

    

    EXPECT_TRUE(result);

}



TEST_F(CompactionTest_179, IsTrivialMove_NormalOperation_WithOverlapWithinLimit_179) {

    EXPECT_CALL(*input_version, NumFiles(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*input_version, NumFiles(1)).WillOnce(::testing::Return(0));



    FileMetaData* grandparent_file = new FileMetaData();

    compaction->grandparents_.push_back(grandparent_file);

    compaction->input_version_->vset_ = new VersionSet("dbname", options, nullptr, nullptr);

    compaction->input_version_->vset_->options_->max_grandparent_overlap_bytes = 1024;



    bool result = compaction->IsTrivialMove();



    EXPECT_TRUE(result);



    delete grandparent_file;

    delete compaction->input_version_->vset_;

}



TEST_F(CompactionTest_179, IsTrivialMove_NormalOperation_WithOverlapExceedingLimit_179) {

    EXPECT_CALL(*input_version, NumFiles(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*input_version, NumFiles(1)).WillOnce(::testing::Return(0));



    FileMetaData* grandparent_file = new FileMetaData();

    compaction->grandparents_.push_back(grandparent_file);

    compaction->input_version_->vset_ = new VersionSet("dbname", options, nullptr, nullptr);

    compaction->input_version_->vset_->options_->max_grandparent_overlap_bytes = 1;



    bool result = compaction->IsTrivialMove();



    EXPECT_FALSE(result);



    delete grandparent_file;

    delete compaction->input_version_->vset_;

}



TEST_F(CompactionTest_179, IsTrivialMove_BoundaryCondition_SingleInputFile_NoGrandparents_179) {

    EXPECT_CALL(*input_version, NumFiles(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*input_version, NumFiles(1)).WillOnce(::testing::Return(0));



    compaction->grandparents_.clear(); // Ensure no grandparents



    bool result = compaction->IsTrivialMove();



    EXPECT_TRUE(result);

}



TEST_F(CompactionTest_179, IsTrivialMove_BoundaryCondition_MultipleInputFiles_NoGrandparents_179) {

    EXPECT_CALL(*input_version, NumFiles(0)).WillOnce(::testing::Return(2));

    EXPECT_CALL(*input_version, NumFiles(1)).WillOnce(::testing::Return(0));



    compaction->grandparents_.clear(); // Ensure no grandparents



    bool result = compaction->IsTrivialMove();



    EXPECT_FALSE(result);

}



TEST_F(CompactionTest_179, IsTrivialMove_BoundaryCondition_SingleInputFile_MultipleGrandparents_179) {

    EXPECT_CALL(*input_version, NumFiles(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*input_version, NumFiles(1)).WillOnce(::testing::Return(0));



    FileMetaData* grandparent_file = new FileMetaData();

    compaction->grandparents_.push_back(grandparent_file);

    compaction->input_version_->vset_ = new VersionSet("dbname", options, nullptr, nullptr);

    compaction->input_version_->vset_->options_->max_grandparent_overlap_bytes = 1024;



    bool result = compaction->IsTrivialMove();



    EXPECT_TRUE(result);



    delete grandparent_file;

    delete compaction->input_version_->vset_;

}
