#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/slice.h"



using namespace leveldb;



class CompactionTest_81 : public ::testing::Test {

protected:

    Options options;

    int level = 0;

    std::unique_ptr<Compaction> compaction;



    void SetUp() override {

        compaction = std::make_unique<Compaction>(&options, level);

    }

};



TEST_F(CompactionTest_81, NumInputFiles_ZeroInputs_81) {

    EXPECT_EQ(compaction->num_input_files(0), 0);

}



TEST_F(CompactionTest_81, NumInputFiles_NonZeroInputs_81) {

    // Assuming we have a way to add inputs, which is not provided in the interface.

    // This test case assumes that inputs can be added externally for testing purposes.

    // For now, we will mock the behavior by directly setting the input vector size.

    compaction->inputs_[0].push_back(new FileMetaData());

    compaction->inputs_[1].push_back(new FileMetaData());

    EXPECT_EQ(compaction->num_input_files(0), 1);

    EXPECT_EQ(compaction->num_input_files(1), 1);

}



TEST_F(CompactionTest_81, NumInputFiles_OutOfBounds_81) {

    // Test for out-of-bounds access

    EXPECT_THROW({ compaction->num_input_files(-1); }, std::exception);

    EXPECT_THROW({ compaction->num_input_files(2); }, std::exception);

}



TEST_F(CompactionTest_81, Level_ReturnsCorrectLevel_81) {

    EXPECT_EQ(compaction->level(), level);

}



TEST_F(CompactionTest_81, TrivialMove_DefaultState_81) {

    // Assuming IsTrivialMove returns false by default

    EXPECT_FALSE(compaction->IsTrivialMove());

}



TEST_F(CompactionTest_81, MaxOutputFileSize_ReturnsExpectedValue_81) {

    uint64_t expected_size = MaxFileSizeForLevel(&options, level);

    EXPECT_EQ(compaction->MaxOutputFileSize(), expected_size);

}
