#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/slice.h"



using namespace leveldb;



class CompactionTest_79 : public ::testing::Test {

protected:

    const Options options;

    Compaction* compaction;



    void SetUp() override {

        compaction = new Compaction(&options, 1);

    }



    void TearDown() override {

        delete compaction;

    }

};



TEST_F(CompactionTest_79, LevelReturnsCorrectValue_79) {

    EXPECT_EQ(compaction->level(), 1);

}



TEST_F(CompactionTest_79, MaxOutputFileSizeReturnsPositiveValue_79) {

    EXPECT_GT(compaction->MaxOutputFileSize(), 0u);

}



TEST_F(CompactionTest_79, NumInputFilesInitiallyZero_79) {

    EXPECT_EQ(compaction->num_input_files(0), 0);

    EXPECT_EQ(compaction->num_input_files(1), 0);

}



TEST_F(CompactionTest_79, IsTrivialMoveInitiallyFalse_79) {

    EXPECT_FALSE(compaction->IsTrivialMove());

}



TEST_F(CompactionTest_79, AddInputDeletionsDoesNotThrow_79) {

    VersionEdit edit;

    EXPECT_NO_THROW(compaction->AddInputDeletions(&edit));

}



TEST_F(CompactionTest_79, IsBaseLevelForKeyWithEmptyKey_79) {

    Slice empty_key("", 0);

    EXPECT_FALSE(compaction->IsBaseLevelForKey(empty_key));

}



TEST_F(CompactionTest_79, ShouldStopBeforeWithEmptyKey_79) {

    Slice empty_key("", 0);

    EXPECT_FALSE(compaction->ShouldStopBefore(empty_key));

}



TEST_F(CompactionTest_79, ReleaseInputsDoesNotThrow_79) {

    EXPECT_NO_THROW(compaction->ReleaseInputs());

}
