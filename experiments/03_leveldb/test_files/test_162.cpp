#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/status.h"

#include "leveldb/options.h"

#include "db/filename.h"

#include "db/table_cache.h"

#include "util/testharness.h"



using namespace leveldb;



class VersionSetTest_162 : public ::testing::Test {

protected:

    Env* env_;

    Options options_;

    TableCache* table_cache_;

    InternalKeyComparator icmp_;

    VersionSet* version_set_;



    virtual void SetUp() override {

        env_ = Env::Default();

        options_.env = env_;

        table_cache_ = new TableCache(dbname_, &options_, 10);

        icmp_ = InternalKeyComparator(BytewiseComparator());

        version_set_ = new VersionSet(dbname_, &options_, table_cache_, &icmp_);

    }



    virtual void TearDown() override {

        delete version_set_;

        delete table_cache_;

    }



private:

    std::string dbname_ = test::TmpDir() + "/leveldb_versionset_test";

};



TEST_F(VersionSetTest_162, LogAndApply_NormalOperation_162) {

    VersionEdit edit;

    port::Mutex mu;

    Status status = version_set_->LogAndApply(&edit, &mu);

    EXPECT_TRUE(status.ok());

}



TEST_F(VersionSetTest_162, NumLevelFiles_BoundaryConditions_162) {

    int num_files = version_set_->NumLevelFiles(0);

    EXPECT_GE(num_files, 0); // At least zero files

}



TEST_F(VersionSetTest_162, NumLevelBytes_BoundaryConditions_162) {

    int64_t num_bytes = version_set_->NumLevelBytes(0);

    EXPECT_GE(num_bytes, 0); // Bytes cannot be negative

}



TEST_F(VersionSetTest_162, LastSequence_NormalOperation_162) {

    uint64_t sequence = version_set_->LastSequence();

    EXPECT_EQ(sequence, 0); // Initially the last sequence should be zero

}



TEST_F(VersionSetTest_162, SetLastSequence_NormalOperation_162) {

    version_set_->SetLastSequence(10);

    EXPECT_EQ(version_set_->LastSequence(), 10);

}



TEST_F(VersionSetTest_162, ManifestFileNumber_BoundaryConditions_162) {

    uint64_t manifest_file_number = version_set_->ManifestFileNumber();

    EXPECT_GE(manifest_file_number, 0); // Manifest file number cannot be negative

}



TEST_F(VersionSetTest_162, NewFileNumber_NormalOperation_162) {

    uint64_t new_file_number = version_set_->NewFileNumber();

    EXPECT_GT(new_file_number, 0); // File numbers should start from at least 1

}



TEST_F(VersionSetTest_162, Recover_NormalOperation_162) {

    bool save_manifest;

    Status status = version_set_->Recover(&save_manifest);

    EXPECT_TRUE(status.ok());

}



TEST_F(VersionSetTest_162, PickCompaction_NormalOperation_162) {

    Compaction* compaction = version_set_->PickCompaction();

    // Since there are no files in the levels initially, it should return nullptr

    EXPECT_EQ(compaction, nullptr);

}



TEST_F(VersionSetTest_162, CompactRange_NormalOperation_162) {

    InternalKey begin;

    InternalKey end;

    Compaction* compaction = version_set_->CompactRange(0, &begin, &end);

    // Since there are no files in the levels initially, it should return nullptr

    EXPECT_EQ(compaction, nullptr);

}
