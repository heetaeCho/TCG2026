#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "leveldb/slice.h"



using namespace leveldb;



class MockVersionSet : public VersionSet {

public:

    MockVersionSet(const std::string &dbname, const Options *options, TableCache *table_cache, const InternalKeyComparator *cmp)

        : VersionSet(dbname, options, table_cache, cmp) {}



    MOCK_CONST_METHOD1(MaxGrandParentOverlapBytes, int64_t(const Options&));

};



class CompactionTest_182 : public ::testing::Test {

protected:

    void SetUp() override {

        options = new Options();

        icmp = new InternalKeyComparator(options->comparator);

        version_set = new MockVersionSet("testdb", options, nullptr, icmp);

        compaction = new Compaction(options, 0);

        compaction->input_version_ = new Version(version_set);



        // Set up grandparents with some metadata

        FileMetaData* meta1 = new FileMetaData();

        meta1->largest.Encode().data() = "key3";

        meta1->file_size = 100;

        compaction->grandparents_.insert(meta1);

    }



    void TearDown() override {

        delete options;

        delete icmp;

        delete version_set;

        delete compaction;

    }



    Options* options;

    InternalKeyComparator* icmp;

    MockVersionSet* version_set;

    Compaction* compaction;

};



TEST_F(CompactionTest_182, ShouldStopBefore_NormalOperation_182) {

    Slice key("key2");

    EXPECT_CALL(*version_set, MaxGrandParentOverlapBytes(::testing::_)).WillOnce(::testing::Return(50));

    bool result = compaction->ShouldStopBefore(key);

    EXPECT_FALSE(result);

}



TEST_F(CompactionTest_182, ShouldStopBefore_BoundaryCondition_182) {

    Slice key("key4");

    EXPECT_CALL(*version_set, MaxGrandParentOverlapBytes(::testing::_)).WillOnce(::testing::Return(50));

    bool result = compaction->ShouldStopBefore(key);

    EXPECT_TRUE(result);

}



TEST_F(CompactionTest_182, ShouldStopBefore_ExceptionalCase_182) {

    Slice key("key3");

    EXPECT_CALL(*version_set, MaxGrandParentOverlapBytes(::testing::_)).WillOnce(::testing::Return(0));

    bool result = compaction->ShouldStopBefore(key);

    EXPECT_TRUE(result);

}



TEST_F(CompactionTest_182, ShouldStopBefore_MaxOverlap_182) {

    Slice key("key3");

    EXPECT_CALL(*version_set, MaxGrandParentOverlapBytes(::testing::_)).WillOnce(::testing::Return(100));

    compaction->seen_key_ = true;

    bool result = compaction->ShouldStopBefore(key);

    EXPECT_TRUE(result);

}



TEST_F(CompactionTest_182, ShouldStopBefore_NoOverlap_182) {

    Slice key("key1");

    EXPECT_CALL(*version_set, MaxGrandParentOverlapBytes(::testing::_)).WillOnce(::testing::Return(50));

    bool result = compaction->ShouldStopBefore(key);

    EXPECT_FALSE(result);

}
