#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/status.h"



namespace leveldb {



class CompactionTest_183 : public ::testing::Test {

protected:

    Compaction* compaction_;

    Version* mock_input_version_;



    void SetUp() override {

        mock_input_version_ = new Version(nullptr);

        compaction_ = new Compaction(nullptr, 0);

        compaction_->input_version_ = mock_input_version_;

    }



    void TearDown() override {

        delete compaction_;

        mock_input_version_->Unref();

    }

};



TEST_F(CompactionTest_183, ReleaseInputs_ResetsInputVersionPointer_183) {

    compaction_->ReleaseInputs();

    EXPECT_EQ(compaction_->input_version_, nullptr);

}



TEST_F(CompactionTest_183, ReleaseInputs_UnrefsInputVersion_183) {

    EXPECT_CALL(*mock_input_version_, Unref())

        .Times(1);



    compaction_->ReleaseInputs();

}



TEST_F(CompactionTest_183, ReleaseInputs_NoOpIfInputVersionIsNull_183) {

    compaction_->input_version_ = nullptr;

    EXPECT_NO_FATAL_FAILURE(compaction_->ReleaseInputs());

}



TEST_F(CompactionTest_183, Level_ReturnsCorrectLevel_183) {

    EXPECT_EQ(compaction_->level(), 0);

}



TEST_F(CompactionTest_183, Edit_ReturnsValidVersionEditPointer_183) {

    EXPECT_NE(compaction_->edit(), nullptr);

}



TEST_F(CompactionTest_183, NumInputFiles_ReturnsZeroInitially_183) {

    EXPECT_EQ(compaction_->num_input_files(0), 0);

    EXPECT_EQ(compaction_->num_input_files(1), 0);

}



TEST_F(CompactionTest_183, Input_ReturnsNullForNonexistentFile_183) {

    EXPECT_EQ(compaction_->input(0, 0), nullptr);

    EXPECT_EQ(compaction_->input(1, 0), nullptr);

}



TEST_F(CompactionTest_183, MaxOutputFileSize_ReturnsPositiveValue_183) {

    EXPECT_GT(compaction_->MaxOutputFileSize(), 0);

}



} // namespace leveldb
