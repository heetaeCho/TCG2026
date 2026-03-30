#include <gtest/gtest.h>

#include "db/version_edit.h"



using namespace leveldb;



class VersionEditTest_338 : public ::testing::Test {

protected:

    VersionEdit* version_edit_;



    void SetUp() override {

        version_edit_ = new VersionEdit();

    }



    void TearDown() override {

        delete version_edit_;

    }

};



TEST_F(VersionEditTest_338, ClearResetsComparatorName_338) {

    Slice comparator_name("test_comparator");

    version_edit_->SetComparatorName(comparator_name);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("comparator"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsLogNumber_338) {

    uint64_t log_number = 123;

    version_edit_->SetLogNumber(log_number);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("log number"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsPrevLogNumber_338) {

    uint64_t prev_log_number = 456;

    version_edit_->SetPrevLogNumber(prev_log_number);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("prev log number"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsNextFileNumber_338) {

    uint64_t next_file_number = 789;

    version_edit_->SetNextFile(next_file_number);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("next file number"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsLastSequence_338) {

    SequenceNumber last_sequence = 101112;

    version_edit_->SetLastSequence(last_sequence);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("last sequence"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsCompactPointers_338) {

    InternalKey key("test_key");

    version_edit_->SetCompactPointer(0, key);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("compact pointers"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsDeletedFiles_338) {

    version_edit_->RemoveFile(1, 123456);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("deleted files"), std::string::npos);

}



TEST_F(VersionEditTest_338, ClearResetsNewFiles_338) {

    InternalKey smallest("smallest_key");

    InternalKey largest("largest_key");

    version_edit_->AddFile(1, 654321, 1024, smallest, largest);

    version_edit_->Clear();

    EXPECT_EQ(version_edit_->DebugString().find("new files"), std::string::npos);

}
