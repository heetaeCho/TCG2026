#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/comparator.h"



namespace leveldb {



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice& a, const Slice& b));

    MOCK_METHOD0(Name, const char*());

    MOCK_METHOD2(FindShortestSeparator, void(std::string* start, const Slice& limit));

    MOCK_METHOD1(FindShortSuccessor, void(std::string* key));

};



class VersionTest_155 : public ::testing::Test {

protected:

    MockComparator mock_comparator;

    InternalKeyComparator icmp{&mock_comparator};

    VersionSet vset{"dummy_dbname", nullptr, nullptr, &icmp};

    Version version{&vset};



    void SetUp() override {

        // Initialize FileMetaData objects for testing

        file1.smallest = InternalKey{"key1_start", 0, kTypeValue};

        file1.largest = InternalKey{"key1_end", 0, kTypeValue};

        file2.smallest = InternalKey{"key2_start", 0, kTypeValue};

        file2.largest = InternalKey{"key2_end", 0, kTypeValue};

        file3.smallest = InternalKey{"key3_start", 0, kTypeValue};

        file3.largest = InternalKey{"key3_end", 0, kTypeValue};



        version.files_[0].insert(&file1);

        version.files_[0].insert(&file2);

        version.files_[0].insert(&file3);

    }



    FileMetaData file1;

    FileMetaData file2;

    FileMetaData file3;

};



TEST_F(VersionTest_155, GetOverlappingInputs_NoOverlap_155) {

    InternalKey begin{"key0_end", 0, kTypeValue};

    InternalKey end{"key4_start", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    version.GetOverlappingInputs(0, &begin, &end, &inputs);



    EXPECT_TRUE(inputs.empty());

}



TEST_F(VersionTest_155, GetOverlappingInputs_PartialOverlap_155) {

    InternalKey begin{"key1_start", 0, kTypeValue};

    InternalKey end{"key2_mid", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(testing::Return(-1))

                                              .WillOnce(testing::Return(1));



    version.GetOverlappingInputs(0, &begin, &end, &inputs);



    ASSERT_EQ(inputs.size(), 1);

    EXPECT_EQ(inputs[0], &file1);

}



TEST_F(VersionTest_155, GetOverlappingInputs_FullOverlap_155) {

    InternalKey begin{"key1_start", 0, kTypeValue};

    InternalKey end{"key3_end", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(testing::Return(-1))

                                              .WillOnce(testing::Return(1))

                                              .WillOnce(testing::Return(-1));



    version.GetOverlappingInputs(0, &begin, &end, &inputs);



    ASSERT_EQ(inputs.size(), 3);

    EXPECT_EQ(inputs[0], &file1);

    EXPECT_EQ(inputs[1], &file2);

    EXPECT_EQ(inputs[2], &file3);

}



TEST_F(VersionTest_155, GetOverlappingInputs_NoBegin_155) {

    InternalKey end{"key2_mid", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(testing::Return(-1));



    version.GetOverlappingInputs(0, nullptr, &end, &inputs);



    ASSERT_EQ(inputs.size(), 1);

    EXPECT_EQ(inputs[0], &file1);

}



TEST_F(VersionTest_155, GetOverlappingInputs_NoEnd_155) {

    InternalKey begin{"key2_start", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(testing::Return(-1));



    version.GetOverlappingInputs(0, &begin, nullptr, &inputs);



    ASSERT_EQ(inputs.size(), 3);

    EXPECT_EQ(inputs[0], &file2);

    EXPECT_EQ(inputs[1], &file3);

}



TEST_F(VersionTest_155, GetOverlappingInputs_LevelBoundary_155) {

    InternalKey begin{"key1_start", 0, kTypeValue};

    InternalKey end{"key3_end", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    EXPECT_CALL(mock_comparator, Compare(_, _)).WillOnce(testing::Return(-1))

                                              .WillOnce(testing::Return(1))

                                              .WillOnce(testing::Return(-1));



    version.GetOverlappingInputs(config::kNumLevels - 1, &begin, &end, &inputs);



    EXPECT_TRUE(inputs.empty());

}



TEST_F(VersionTest_155, GetOverlappingInputs_EmptyRange_155) {

    InternalKey begin{"key2_mid", 0, kTypeValue};

    InternalKey end{"key2_mid", 0, kTypeValue};

    std::vector<FileMetaData*> inputs;



    version.GetOverlappingInputs(0, &begin, &end, &inputs);



    EXPECT_TRUE(inputs.empty());

}



} // namespace leveldb
