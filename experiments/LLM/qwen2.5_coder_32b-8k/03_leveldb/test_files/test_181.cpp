#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "db/version_set.h"

#include "leveldb/comparator.h"



using namespace leveldb;

using ::testing::Return;



class MockComparator : public Comparator {

public:

    MOCK_METHOD2(Compare, int(const Slice& a, const Slice& b));

    MOCK_METHOD0(Name, const char*());

};



class CompactionTest_181 : public ::testing::Test {

protected:

    MockComparator mock_comparator;

    InternalKeyComparator icmp(&mock_comparator);

    Version version(nullptr);

    Compaction compaction(nullptr, 3); // Assuming level 3 for testing



    void SetUp() override {

        compaction.input_version_ = &version;

        version.files_[5].push_back(new FileMetaData());

        version.files_[5].back()->smallest.user_key().data_ = "key1";

        version.files_[5].back()->largest.user_key().data_ = "key2";

    }



    void TearDown() override {

        for (int lvl = 0; lvl < config::kNumLevels; lvl++) {

            for (auto file : version.files_[lvl]) {

                delete file;

            }

        }

    }

};



TEST_F(CompactionTest_181, IsBaseLevelForKey_OutsideRange_181) {

    Slice user_key("key0");

    EXPECT_CALL(mock_comparator, Compare(user_key, testing::_))

        .WillOnce(Return(-1)); // key0 < key1



    ASSERT_TRUE(compaction.IsBaseLevelForKey(user_key));

}



TEST_F(CompactionTest_181, IsBaseLevelForKey_InsideRange_181) {

    Slice user_key("key1.5");

    EXPECT_CALL(mock_comparator, Compare(testing::_, testing::_))

        .WillOnce(Return(-1)) // key1 < key1.5

        .WillOnce(Return(1));  // key1.5 > key2



    ASSERT_FALSE(compaction.IsBaseLevelForKey(user_key));

}



TEST_F(CompactionTest_181, IsBaseLevelForKey_BoundaryConditionLowerBound_181) {

    Slice user_key("key1");

    EXPECT_CALL(mock_comparator, Compare(testing::_, testing::_))

        .WillOnce(Return(0)) // key1 == key1

        .WillOnce(Return(-1)); // key1 < key2



    ASSERT_TRUE(compaction.IsBaseLevelForKey(user_key));

}



TEST_F(CompactionTest_181, IsBaseLevelForKey_BoundaryConditionUpperBound_181) {

    Slice user_key("key2");

    EXPECT_CALL(mock_comparator, Compare(testing::_, testing::_))

        .WillOnce(Return(-1)) // key1 < key2

        .WillOnce(Return(0));  // key2 == key2



    ASSERT_TRUE(compaction.IsBaseLevelForKey(user_key));

}



TEST_F(CompactionTest_181, IsBaseLevelForKey_NoFilesInNextLevels_181) {

    Slice user_key("key3");

    version.files_[5].clear(); // Remove files in level 5

    EXPECT_CALL(mock_comparator, Compare(testing::_, testing::_)).Times(0);



    ASSERT_TRUE(compaction.IsBaseLevelForKey(user_key));

}



TEST_F(CompactionTest_181, IsBaseLevelForKey_MultipleFilesInNextLevels_181) {

    version.files_[5].push_back(new FileMetaData());

    version.files_[5].back()->smallest.user_key().data_ = "key3";

    version.files_[5].back()->largest.user_key().data_ = "key4";



    Slice user_key("key2.5");

    EXPECT_CALL(mock_comparator, Compare(testing::_, testing::_))

        .WillOnce(Return(1))  // key2 < key2.5

        .WillOnce(Return(-1)); // key2.5 < key3



    ASSERT_TRUE(compaction.IsBaseLevelForKey(user_key));

}
