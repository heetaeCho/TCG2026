#include <gtest/gtest.h>

#include "db/version_set.h"

#include "db/compaction.h"



namespace leveldb {



class VersionSetTest_173 : public ::testing::Test {

protected:

    struct MockEnv {};

    struct MockOptions {};

    struct MockTableCache {};

    struct MockInternalKeyComparator {};



    MockEnv env_;

    MockOptions options_;

    MockTableCache table_cache_;

    MockInternalKeyComparator icmp_;



    VersionSet version_set_{"test_db", &options_, &table_cache_, &icmp_};



    void SetUp() override {

        // Initialize necessary setup for tests

        version_set_.current_ = new Version(&version_set_);

    }



    void TearDown() override {

        // Cleanup after each test

        delete version_set_.current_;

    }

};



TEST_F(VersionSetTest_173, PickCompaction_NoCompactionNeeded_173) {

    version_set_.current_->compaction_score_ = 0;

    version_set_.current_->file_to_compact_ = nullptr;



    Compaction* compaction = version_set_.PickCompaction();

    EXPECT_EQ(compaction, nullptr);

}



TEST_F(VersionSetTest_173, PickCompaction_SizeBasedCompaction_173) {

    version_set_.current_->compaction_score_ = 2;

    version_set_.current_->file_to_compact_ = nullptr;



    FileMetaData file_meta_data;

    version_set_.current_->files_[0].push_back(&file_meta_data);



    Compaction* compaction = version_set_.PickCompaction();

    EXPECT_NE(compaction, nullptr);

    EXPECT_EQ(compaction->level(), 0);

    delete compaction;

}



TEST_F(VersionSetTest_173, PickCompaction_SeekBasedCompaction_173) {

    FileMetaData file_meta_data;

    version_set_.current_->file_to_compact_ = &file_meta_data;

    version_set_.current_->file_to_compact_level_ = 1;



    Compaction* compaction = version_set_.PickCompaction();

    EXPECT_NE(compaction, nullptr);

    EXPECT_EQ(compaction->level(), 1);

    delete compaction;

}



TEST_F(VersionSetTest_173, PickCompaction_LevelBoundaryCondition_173) {

    version_set_.current_->compaction_score_ = 2;

    version_set_.current_->file_to_compact_ = nullptr;



    FileMetaData file_meta_data;

    version_set_.current_->files_[6].push_back(&file_meta_data);



    Compaction* compaction = version_set_.PickCompaction();

    EXPECT_NE(compaction, nullptr);

    EXPECT_EQ(compaction->level(), 5); // The level should not exceed the maximum allowed level

    delete compaction;

}



TEST_F(VersionSetTest_173, PickCompaction_FileMetaDataEmpty_173) {

    version_set_.current_->compaction_score_ = 2;

    version_set_.current_->file_to_compact_ = nullptr;



    Compaction* compaction = version_set_.PickCompaction();

    EXPECT_EQ(compaction, nullptr);

}



} // namespace leveldb
