#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "db/table_cache.h"

#include "db/compaction.h"



using namespace leveldb;

using ::testing::_;

using ::testing::NiceMock;



class MockTableCache : public TableCache {

public:

    MOCK_METHOD3(NewIterator, Iterator*(const ReadOptions&, uint64_t, uint64_t));

};



class MockCompaction : public Compaction {

public:

    MockCompaction(const Options* options, int level) : Compaction(options, level) {}

    MOCK_CONST_METHOD0(level, int());

    MOCK_CONST_METHOD2(input, FileMetaData*(int, int));

    MOCK_CONST_METHOD1(num_input_files, int(int));

};



class VersionSetTest_172 : public ::testing::Test {

protected:

    void SetUp() override {

        options = new Options();

        table_cache = new NiceMock<MockTableCache>("dbname", *options, 10);

        version_set = new VersionSet("dbname", options, table_cache, &icmp);

        compaction = new MockCompaction(options, 0);

    }



    void TearDown() override {

        delete compaction;

        delete version_set;

        delete table_cache;

        delete options;

    }



    Options* options;

    NiceMock<MockTableCache>* table_cache;

    VersionSet* version_set;

    MockCompaction* compaction;

    InternalKeyComparator icmp;

};



TEST_F(VersionSetTest_172, MakeInputIterator_NoInputs_172) {

    EXPECT_CALL(*compaction, num_input_files(0)).WillOnce(::testing::Return(0));

    EXPECT_CALL(*compaction, num_input_files(1)).WillOnce(::testing::Return(0));



    Iterator* result = version_set->MakeInputIterator(compaction);

    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(VersionSetTest_172, MakeInputIterator_SingleLevelZeroInput_172) {

    FileMetaData file_meta_data;

    file_meta_data.number = 1;

    file_meta_data.file_size = 1024;



    EXPECT_CALL(*compaction, level()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*compaction, num_input_files(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*compaction, input(0, 0)).WillOnce(::testing::Return(&file_meta_data));

    EXPECT_CALL(*table_cache, NewIterator(_, 1, 1024)).WillOnce(::testing::Return(new Iterator()));



    Iterator* result = version_set->MakeInputIterator(compaction);

    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(VersionSetTest_172, MakeInputIterator_MultipleLevelZeroInputs_172) {

    FileMetaData file_meta_data1;

    file_meta_data1.number = 1;

    file_meta_data1.file_size = 1024;



    FileMetaData file_meta_data2;

    file_meta_data2.number = 2;

    file_meta_data2.file_size = 2048;



    EXPECT_CALL(*compaction, level()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*compaction, num_input_files(0)).WillOnce(::testing::Return(2));

    EXPECT_CALL(*compaction, input(0, 0)).WillOnce(::testing::Return(&file_meta_data1));

    EXPECT_CALL(*compaction, input(0, 1)).WillOnce(::testing::Return(&file_meta_data2));

    EXPECT_CALL(*table_cache, NewIterator(_, 1, 1024)).WillOnce(::testing::Return(new Iterator()));

    EXPECT_CALL(*table_cache, NewIterator(_, 2, 2048)).WillOnce(::testing::Return(new Iterator()));



    Iterator* result = version_set->MakeInputIterator(compaction);

    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(VersionSetTest_172, MakeInputIterator_SingleLevelNonZeroInput_172) {

    FileMetaData file_meta_data;

    file_meta_data.number = 3;

    file_meta_data.file_size = 4096;



    EXPECT_CALL(*compaction, level()).WillOnce(::testing::Return(1));

    EXPECT_CALL(*compaction, num_input_files(1)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*compaction, input(1, 0)).WillOnce(::testing::Return(&file_meta_data));



    Iterator* result = version_set->MakeInputIterator(compaction);

    ASSERT_NE(result, nullptr);

    delete result;

}



TEST_F(VersionSetTest_172, MakeInputIterator_MultipleLevelsInputs_172) {

    FileMetaData file_meta_data0;

    file_meta_data0.number = 4;

    file_meta_data0.file_size = 8192;



    FileMetaData file_meta_data1;

    file_meta_data1.number = 5;

    file_meta_data1.file_size = 16384;



    EXPECT_CALL(*compaction, level()).WillOnce(::testing::Return(0));

    EXPECT_CALL(*compaction, num_input_files(0)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*compaction, input(0, 0)).WillOnce(::testing::Return(&file_meta_data0));



    EXPECT_CALL(*compaction, level()).WillRepeatedly(::testing::Return(1)); // Additional call from MakeInputIterator

    EXPECT_CALL(*compaction, num_input_files(1)).WillOnce(::testing::Return(1));

    EXPECT_CALL(*compaction, input(1, 0)).WillOnce(::testing::Return(&file_meta_data1));



    EXPECT_CALL(*table_cache, NewIterator(_, 4, 8192)).WillOnce(::testing::Return(new Iterator()));



    Iterator* result = version_set->MakeInputIterator(compaction);

    ASSERT_NE(result, nullptr);

    delete result;

}
