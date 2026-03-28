#include <gtest/gtest.h>

#include "db/version_set.h"



namespace leveldb {



class VersionSetTest_78 : public ::testing::Test {

protected:

    Options options;

    TableCache table_cache{nullptr};

    InternalKeyComparator icmp;

    std::string dbname = "test_db";

    VersionSet version_set{dbname, &options, &table_cache, &icmp};



    // Helper to set compaction_score_ and file_to_compact_

    void SetCompactionScoreAndFileToCompact(double score, FileMetaData* file) {

        auto current_version = version_set.current();

        if (current_version) {

            current_version->compaction_score_ = score;

            current_version->file_to_compact_ = file;

        }

    }

};



TEST_F(VersionSetTest_78, NeedsCompaction_ReturnsFalseWhenNoConditionsMet_78) {

    SetCompactionScoreAndFileToCompact(0.5, nullptr);

    EXPECT_FALSE(version_set.NeedsCompaction());

}



TEST_F(VersionSetTest_78, NeedsCompaction_ReturnsTrueWhenCompactionScoreIsHigh_78) {

    SetCompactionScoreAndFileToCompact(1.5, nullptr);

    EXPECT_TRUE(version_set.NeedsCompaction());

}



TEST_F(VersionSetTest_78, NeedsCompaction_ReturnsTrueWhenFileToCompactIsNotNull_78) {

    FileMetaData file_meta_data;

    SetCompactionScoreAndFileToCompact(0.5, &file_meta_data);

    EXPECT_TRUE(version_set.NeedsCompaction());

}



TEST_F(VersionSetTest_78, NeedsCompaction_ReturnsTrueWhenBothConditionsAreMet_78) {

    FileMetaData file_meta_data;

    SetCompactionScoreAndFileToCompact(1.5, &file_meta_data);

    EXPECT_TRUE(version_set.NeedsCompaction());

}



}  // namespace leveldb
