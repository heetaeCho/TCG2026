#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/slice.h"



using namespace leveldb;



class CompactionTest_80 : public ::testing::Test {

protected:

    Options options;

    Compaction compaction;



    CompactionTest_80() : compaction(&options, 1) {}

};



TEST_F(CompactionTest_80, EditReturnsValidPointer_80) {

    EXPECT_NE(compaction.edit(), nullptr);

}



TEST_F(CompactionTest_80, LevelReturnsCorrectValue_80) {

    EXPECT_EQ(compaction.level(), 1);

}



TEST_F(CompactionTest_80, IsTrivialMoveInitiallyFalse_80) {

    EXPECT_FALSE(compaction.IsTrivialMove());

}



TEST_F(CompactionTest_80, AddInputDeletionsDoesNotThrow_80) {

    VersionEdit edit;

    EXPECT_NO_THROW(compaction.AddInputDeletions(&edit));

}



TEST_F(CompactionTest_80, IsBaseLevelForKeyInitiallyFalseForEmptyKey_80) {

    Slice empty_key("", 0);

    EXPECT_FALSE(compaction.IsBaseLevelForKey(empty_key));

}



TEST_F(CompactionTest_80, ShouldStopBeforeInitiallyFalseForEmptyKey_80) {

    Slice empty_key("", 0);

    EXPECT_FALSE(compaction.ShouldStopBefore(empty_key));

}



TEST_F(CompactionTest_80, ReleaseInputsDoesNotThrow_80) {

    EXPECT_NO_THROW(compaction.ReleaseInputs());

}



TEST_F(CompactionTest_80, NumInputFilesInitiallyZeroForBothInputs_80) {

    EXPECT_EQ(compaction.num_input_files(0), 0);

    EXPECT_EQ(compaction.num_input_files(1), 0);

}



TEST_F(CompactionTest_80, InputReturnsNullptrForNonexistentFile_80) {

    EXPECT_EQ(compaction.input(0, 0), nullptr);

    EXPECT_EQ(compaction.input(1, 0), nullptr);

}



TEST_F(CompactionTest_80, MaxOutputFileSizeReturnsPositiveValue_80) {

    EXPECT_GT(compaction.MaxOutputFileSize(), 0);

}
