#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/options.h"

#include "leveldb/slice.h"



using namespace leveldb;



class CompactionTest_82 : public ::testing::Test {

protected:

    Options options;

    const int level = 0;

    std::unique_ptr<Compaction> compaction;



    void SetUp() override {

        compaction.reset(new Compaction(&options, level));

    }

};



TEST_F(CompactionTest_82, LevelReturnsCorrectValue_82) {

    EXPECT_EQ(compaction->level(), level);

}



TEST_F(CompactionTest_82, MaxOutputFileSizeReturnsPositiveValue_82) {

    EXPECT_GT(compaction->MaxOutputFileSize(), 0);

}



TEST_F(CompactionTest_82, NumInputFilesReturnsZeroInitially_82) {

    EXPECT_EQ(compaction->num_input_files(0), 0);

    EXPECT_EQ(compaction->num_input_files(1), 0);

}



TEST_F(CompactionTest_82, InputReturnsNullptrForNonexistentFile_82) {

    EXPECT_EQ(compaction->input(0, 0), nullptr);

    EXPECT_EQ(compaction->input(1, 0), nullptr);

}



TEST_F(CompactionTest_82, IsTrivialMoveInitiallyFalse_82) {

    EXPECT_FALSE(compaction->IsTrivialMove());

}



TEST_F(CompactionTest_82, AddInputDeletionsDoesNotThrow_82) {

    VersionEdit edit;

    EXPECT_NO_THROW(compaction->AddInputDeletions(&edit));

}



TEST_F(CompactionTest_82, IsBaseLevelForKeyInitiallyFalse_82) {

    Slice user_key("test_key");

    EXPECT_FALSE(compaction->IsBaseLevelForKey(user_key));

}



TEST_F(CompactionTest_82, ShouldStopBeforeInitiallyFalse_82) {

    Slice internal_key("test_internal_key");

    EXPECT_FALSE(compaction->ShouldStopBefore(internal_key));

}



TEST_F(CompactionTest_82, ReleaseInputsDoesNotThrow_82) {

    EXPECT_NO_THROW(compaction->ReleaseInputs());

}
