#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "table/block.cc"

#include "leveldb/slice.h"



using namespace leveldb;



class MockComparator : public Comparator {

public:

    MOCK_CONST_METHOD2(Compare, int(const Slice& a, const Slice& b));

};



class IterTest_413 : public ::testing::Test {

protected:

    MockComparator mock_comparator_;

    char data_[1024];

    uint32_t restarts_ = 0;

    uint32_t num_restarts_ = 0;



    std::unique_ptr<Block::Iter> iter_;



    void SetUp() override {

        iter_.reset(new Block::Iter(&mock_comparator_, data_, restarts_, num_restarts_));

    }

};



TEST_F(IterTest_413, SeekToFirstInitializesIterator_413) {

    iter_->SeekToFirst();

    EXPECT_FALSE(iter_->Valid());

}



TEST_F(IterTest_413, SeekToLastInitializesIterator_413) {

    iter_->SeekToLast();

    EXPECT_FALSE(iter_->Valid());

}



TEST_F(IterTest_413, SeekWithEmptyDataDoesNotCrash_413) {

    Slice target("nonexistent");

    iter_->Seek(target);

    EXPECT_FALSE(iter_->Valid());

}



TEST_F(IterTest_413, SeekCallsCompareCorrectly_413) {

    Slice target("key");

    EXPECT_CALL(mock_comparator_, Compare(::testing::An<const Slice&>(), ::testing::Eq(target)))

        .WillOnce(::testing::Return(-1))

        .WillOnce(::testing::Return(1));



    iter_->Seek(target);

    iter_->Seek(target);

}



TEST_F(IterTest_413, SeekToRestartPointSetsCorrectIndex_413) {

    Slice target("key");

    EXPECT_CALL(mock_comparator_, Compare(::testing::An<const Slice&>(), ::testing::Eq(target)))

        .WillOnce(::testing::Return(-1));



    iter_->Seek(target);

    // Since we cannot access internal state, this is the best we can verify.

}



TEST_F(IterTest_413, SeekWithInvalidDataHandlesCorruption_413) {

    Slice target("key");

    EXPECT_CALL(mock_comparator_, Compare(::testing::An<const Slice&>(), ::testing::Eq(target)))

        .WillOnce(::testing::Return(-1));



    iter_->Seek(target);

    // Assuming CorruptionError sets status to an error state.

    EXPECT_TRUE(!iter_->status().ok());

}



TEST_F(IterTest_413, SeekWithExactMatchFindsKey_413) {

    Slice target("key");

    EXPECT_CALL(mock_comparator_, Compare(::testing::An<const Slice&>(), ::testing::Eq(target)))

        .WillOnce(::testing::Return(0));



    iter_->Seek(target);

    EXPECT_TRUE(iter_->Valid());

}



TEST_F(IterTest_413, SeekWithNonExactMatchFindsNextKey_413) {

    Slice target("key");

    EXPECT_CALL(mock_comparator_, Compare(::testing::An<const Slice&>(), ::testing::Eq(target)))

        .WillOnce(::testing::Return(-1))

        .WillOnce(::testing::Return(0));



    iter_->Seek(target);

    EXPECT_TRUE(iter_->Valid());

}



TEST_F(IterTest_413, SeekWithNoMatchingKeyDoesNotSetIterator_413) {

    Slice target("key");

    EXPECT_CALL(mock_comparator_, Compare(::testing::An<const Slice&>(), ::testing::Eq(target)))

        .WillRepeatedly(::testing::Return(-1));



    iter_->Seek(target);

    EXPECT_FALSE(iter_->Valid());

}
