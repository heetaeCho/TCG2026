#include <gtest/gtest.h>

#include "db/version_set.h"

#include "db/dbformat.h"



namespace leveldb {



class MockVersion : public Version {

public:

    MOCK_METHOD(void, GetOverlappingInputs, (int level, const InternalKey* begin, const InternalKey* end, std::vector<FileMetaData*> * inputs), (override));

};



class VersionSetTest_177 : public ::testing::Test {

protected:

    MockVersion mock_version;

    Options options;

    TableCache table_cache{&options, nullptr};

    InternalKeyComparator icmp;

    VersionSet version_set{"test_db", &options, &table_cache, &icmp};



    void SetUp() override {

        version_set.dummy_versions_.refs_ = 1; // Ensure dummy_versions is properly set up

        version_set.current_ = &mock_version;

    }



    void TearDown() override {

        version_set.current_->Unref();

    }

};



TEST_F(VersionSetTest_177, CompactRange_ReturnsNullptrWhenNoOverlappingInputs_177) {

    const InternalKey* begin = nullptr;

    const InternalKey* end = nullptr;



    EXPECT_CALL(mock_version, GetOverlappingInputs(testing::_, testing::Eq(begin), testing::Eq(end), testing::_))

        .WillOnce(testing::SetArgReferee<3>(std::vector<FileMetaData*>()));



    Compaction* compaction = version_set.CompactRange(0, begin, end);



    EXPECT_EQ(compaction, nullptr);

}



TEST_F(VersionSetTest_177, CompactRange_ReturnsCompactionObjectWhenOverlappingInputsExist_177) {

    const InternalKey* begin = new InternalKey();

    const InternalKey* end = new InternalKey();

    std::vector<FileMetaData*> inputs;

    FileMetaData file_meta_data;



    inputs.push_back(&file_meta_data);



    EXPECT_CALL(mock_version, GetOverlappingInputs(testing::_, testing::Eq(begin), testing::Eq(end), testing::_))

        .WillOnce(testing::SetArgReferee<3>(inputs));



    Compaction* compaction = version_set.CompactRange(0, begin, end);



    EXPECT_NE(compaction, nullptr);

    delete compaction;

    delete begin;

    delete end;

}



TEST_F(VersionSetTest_177, CompactRange_LimitsInputsToWithinFileSizeLimit_177) {

    const InternalKey* begin = new InternalKey();

    const InternalKey* end = new InternalKey();

    std::vector<FileMetaData*> inputs;

    FileMetaData file_meta_data1, file_meta_data2;



    file_meta_data1.file_size = 100 * 1024 * 1024; // 100 MB

    file_meta_data2.file_size = 60 * 1024 * 1024; // 60 MB



    inputs.push_back(&file_meta_data1);

    inputs.push_back(&file_meta_data2);



    EXPECT_CALL(mock_version, GetOverlappingInputs(testing::_, testing::Eq(begin), testing::Eq(end), testing::_))

        .WillOnce(testing::SetArgReferee<3>(inputs));



    Compaction* compaction = version_set.CompactRange(1, begin, end);



    ASSERT_NE(compaction, nullptr);

    EXPECT_EQ(compaction->num_input_files(0), 1); // Only the first file should be included

    delete compaction;

    delete begin;

    delete end;

}



TEST_F(VersionSetTest_177, CompactRange_HandlesBoundaryConditionsForLevelZero_177) {

    const InternalKey* begin = new InternalKey();

    const InternalKey* end = new InternalKey();

    std::vector<FileMetaData*> inputs;

    FileMetaData file_meta_data;



    file_meta_data.file_size = 200 * 1024 * 1024; // 200 MB



    inputs.push_back(&file_meta_data);



    EXPECT_CALL(mock_version, GetOverlappingInputs(testing::_, testing::Eq(begin), testing::Eq(end), testing::_))

        .WillOnce(testing::SetArgReferee<3>(inputs));



    Compaction* compaction = version_set.CompactRange(0, begin, end);



    ASSERT_NE(compaction, nullptr);

    EXPECT_EQ(compaction->num_input_files(0), 1); // All files should be included in level zero

    delete compaction;

    delete begin;

    delete end;

}



TEST_F(VersionSetTest_177, CompactRange_HandlesEdgeCaseWithNoInputs_177) {

    const InternalKey* begin = nullptr;

    const InternalKey* end = nullptr;



    EXPECT_CALL(mock_version, GetOverlappingInputs(testing::_, testing::Eq(begin), testing::Eq(end), testing::_))

        .WillOnce(testing::SetArgReferee<3>(std::vector<FileMetaData*>()));



    Compaction* compaction = version_set.CompactRange(0, begin, end);



    EXPECT_EQ(compaction, nullptr);

}



} // namespace leveldb
