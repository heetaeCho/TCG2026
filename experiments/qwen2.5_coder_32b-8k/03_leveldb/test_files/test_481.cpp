#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/options.h"

#include "db/dbformat.h"

#include "db/table_cache.h"



using namespace leveldb;



class VersionSetTest_481 : public ::testing::Test {

protected:

    Options options_;

    Env* env_;

    TableCache* table_cache_;

    InternalKeyComparator icmp_;



    void SetUp() override {

        env_ = options_.env;

        table_cache_ = new TableCache("/tmp", options_, 10);

        icmp_ = InternalKeyComparator(options_.comparator);

    }



    void TearDown() override {

        delete table_cache_;

    }

};



TEST_F(VersionSetTest_481, ConstructorInitializesMembersCorrectly_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    EXPECT_EQ(version_set.ManifestFileNumber(), 0);

    EXPECT_EQ(version_set.LastSequence(), 0);

}



TEST_F(VersionSetTest_481, NumLevelFilesReturnsZeroForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    for (int level = 0; level < 7; ++level) {

        EXPECT_EQ(version_set.NumLevelFiles(level), 0);

    }

}



TEST_F(VersionSetTest_481, NumLevelBytesReturnsZeroForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    for (int level = 0; level < 7; ++level) {

        EXPECT_EQ(version_set.NumLevelBytes(level), 0);

    }

}



TEST_F(VersionSetTest_481, MarkFileNumberUsedIncreasesNextFileNumber_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    uint64_t initial_file_number = version_set.NewFileNumber();

    version_set.MarkFileNumberUsed(initial_file_number);

    EXPECT_EQ(version_set.NewFileNumber(), initial_file_number + 2);

}



TEST_F(VersionSetTest_481, ReuseFileNumberSetsNextFileNumberProperly_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    uint64_t file_number = 10;

    version_set.ReuseFileNumber(file_number);

    EXPECT_EQ(version_set.NewFileNumber(), file_number + 2);

}



TEST_F(VersionSetTest_481, LogAndApplyChangesLastSequence_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    port::Mutex mu;

    uint64_t initial_sequence = version_set.LastSequence();

    VersionEdit edit;

    edit.SetLogNumber(1);

    Status s = version_set.LogAndApply(&edit, &mu);

    EXPECT_TRUE(s.ok());

    EXPECT_GT(version_set.LastSequence(), initial_sequence);

}



TEST_F(VersionSetTest_481, RecoverDoesNotThrowOnNewDirectory_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    bool save_manifest = false;

    Status s = version_set.Recover(&save_manifest);

    EXPECT_TRUE(s.ok());

}



TEST_F(VersionSetTest_481, PickCompactionReturnsNullptrForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    Compaction* compaction = version_set.PickCompaction();

    EXPECT_EQ(compaction, nullptr);

}



TEST_F(VersionSetTest_481, CompactRangeReturnsNullptrForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    InternalKey begin("begin");

    InternalKey end("end");

    Compaction* compaction = version_set.CompactRange(0, &begin, &end);

    EXPECT_EQ(compaction, nullptr);

}



TEST_F(VersionSetTest_481, NeedsCompactionReturnsFalseForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    bool needs_compaction = version_set.NeedsCompaction();

    EXPECT_FALSE(needs_compaction);

}



TEST_F(VersionSetTest_481, LogNumberAndPrevLogNumberAreInitialized_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    EXPECT_EQ(version_set.LogNumber(), 0);

    EXPECT_EQ(version_set.PrevLogNumber(), 0);

}



TEST_F(VersionSetTest_481, LevelSummaryDoesNotCrashForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    char buffer[1024];

    LevelSummaryStorage scratch(buffer, sizeof(buffer));

    const char* summary = version_set.LevelSummary(&scratch);

    EXPECT_TRUE(summary != nullptr);

}



TEST_F(VersionSetTest_481, ApproximateOffsetOfReturnsZeroForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    InternalKey key("key");

    int64_t offset = version_set.ApproximateOffsetOf(version_set.current(), key);

    EXPECT_EQ(offset, 0);

}



TEST_F(VersionSetTest_481, AddLiveFilesDoesNotCrashForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    std::set<uint64_t> live_files;

    version_set.AddLiveFiles(&live_files);

    EXPECT_TRUE(true); // If it doesn't crash, the test passes

}



TEST_F(VersionSetTest_481, MaxNextLevelOverlappingBytesReturnsZeroForNewInstance_481) {

    VersionSet version_set("/tmp", &options_, table_cache_, &icmp_);

    int64_t overlapping_bytes = version_set.MaxNextLevelOverlappingBytes();

    EXPECT_EQ(overlapping_bytes, 0);

}
