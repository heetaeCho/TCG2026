#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/slice.h"



using namespace leveldb;



class VersionTest_154 : public ::testing::Test {

protected:

    VersionSet vset_;

    Version* version_;



    VersionTest_154() 

        : vset_("testdb", nullptr, nullptr, nullptr),

          version_(new Version(&vset_)) {}



    ~VersionTest_154() override {

        delete version_;

    }

};



TEST_F(VersionTest_154, PickLevelForMemTableOutput_NormalOperation_154) {

    Slice smallest_user_key("a");

    Slice largest_user_key("z");



    int level = version_->PickLevelForMemTableOutput(smallest_user_key, largest_user_key);

    EXPECT_GE(level, 0);

    EXPECT_LT(level, config::kNumLevels);

}



TEST_F(VersionTest_154, PickLevelForMemTableOutput_BoundaryConditions_EmptyKeys_154) {

    Slice smallest_user_key("");

    Slice largest_user_key("");



    int level = version_->PickLevelForMemTableOutput(smallest_user_key, largest_user_key);

    EXPECT_GE(level, 0);

    EXPECT_LT(level, config::kNumLevels);

}



TEST_F(VersionTest_154, PickLevelForMemTableOutput_BoundaryConditions_SingleCharKeys_154) {

    Slice smallest_user_key("a");

    Slice largest_user_key("a");



    int level = version_->PickLevelForMemTableOutput(smallest_user_key, largest_user_key);

    EXPECT_GE(level, 0);

    EXPECT_LT(level, config::kNumLevels);

}



TEST_F(VersionTest_154, PickLevelForMemTableOutput_ExceptionalCase_NoOverlapInLevel0_154) {

    Slice smallest_user_key("a");

    Slice largest_user_key("z");



    // Assuming no overlap in Level 0 for this test case

    EXPECT_CALL(*version_, OverlapInLevel(0, &smallest_user_key, &largest_user_key))

        .WillOnce(::testing::Return(false));



    int level = version_->PickLevelForMemTableOutput(smallest_user_key, largest_user_key);

    EXPECT_GE(level, 1); // Since there's no overlap in Level 0, it should move to a higher level

}



TEST_F(VersionTest_154, PickLevelForMemTableOutput_ExceptionalCase_NoOverlapInHigherLevels_154) {

    Slice smallest_user_key("a");

    Slice largest_user_key("z");



    // Assuming no overlap in any levels for this test case

    EXPECT_CALL(*version_, OverlapInLevel(::testing::_, &smallest_user_key, &largest_user_key))

        .WillRepeatedly(::testing::Return(false));



    int level = version_->PickLevelForMemTableOutput(smallest_user_key, largest_user_key);

    EXPECT_EQ(level, config::kMaxMemCompactLevel); // Should stop at kMaxMemCompactLevel

}



TEST_F(VersionTest_154, PickLevelForMemTableOutput_ExceptionalCase_MaxGrandParentOverlapBytesExceeded_154) {

    Slice smallest_user_key("a");

    Slice largest_user_key("z");



    // Assuming no overlap in Level 0 for this test case

    EXPECT_CALL(*version_, OverlapInLevel(0, &smallest_user_key, &largest_user_key))

        .WillOnce(::testing::Return(false));



    // Assuming no overlap in Level 1 and MaxGrandParentOverlapBytes exceeded in Level 2

    std::vector<FileMetaData*> overlaps;

    EXPECT_CALL(*version_, OverlapInLevel(1, &smallest_user_key, &largest_user_key))

        .WillOnce(::testing::Return(false));



    InternalKey start(smallest_user_key, kMaxSequenceNumber, kValueTypeForSeek);

    InternalKey limit(largest_user_key, 0, static_cast<ValueType>(0));

    EXPECT_CALL(*version_, GetOverlappingInputs(3, &start, &limit, &overlaps))

        .WillOnce(::testing::Return());



    EXPECT_CALL(*version_, TotalFileSize(&overlaps))

        .WillOnce(::testing::Return(version_->MaxGrandParentOverlapBytes(vset_.options_) + 1));



    int level = version_->PickLevelForMemTableOutput(smallest_user_key, largest_user_key);

    EXPECT_EQ(level, 2); // Should stop at Level 2 due to MaxGrandParentOverlapBytes exceeded

}
