// File: test_strpair_transferto_155.cpp

#include <gtest/gtest.h>

#include "tinyxml2.h"

namespace {

class StrPairTransferToTest_155 : public ::testing::Test {
protected:
    tinyxml2::StrPair src_;
    tinyxml2::StrPair dst_;
};

TEST_F(StrPairTransferToTest_155, TransferToMovesStringAndEmptiesSource_155) {
    src_.SetStr("hello", 0);
    ASSERT_FALSE(src_.Empty());

    ASSERT_TRUE(dst_.Empty());

    src_.TransferTo(&dst_);

    // Destination should now represent the source string.
    EXPECT_STREQ(dst_.GetStr(), "hello");
    EXPECT_FALSE(dst_.Empty());

    // Source should be emptied after transfer.
    EXPECT_TRUE(src_.Empty());
}

TEST_F(StrPairTransferToTest_155, TransferToOnSelfIsNoOp_155) {
    src_.SetStr("self", 0);
    ASSERT_FALSE(src_.Empty());

    const char* before = src_.GetStr();
    ASSERT_NE(before, nullptr);

    src_.TransferTo(&src_);

    // Should remain valid and unchanged.
    EXPECT_FALSE(src_.Empty());
    EXPECT_STREQ(src_.GetStr(), "self");

    // Pointer stability is not guaranteed by interface, so don't require it.
}

TEST_F(StrPairTransferToTest_155, TransferToFromEmptyLeavesDestinationEmpty_155) {
    ASSERT_TRUE(src_.Empty());
    ASSERT_TRUE(dst_.Empty());

    src_.TransferTo(&dst_);

    EXPECT_TRUE(src_.Empty());
    EXPECT_TRUE(dst_.Empty());
}

TEST_F(StrPairTransferToTest_155, TransferToAfterDestinationResetSucceeds_155) {
    src_.SetStr("moved", 0);
    ASSERT_FALSE(src_.Empty());

    // Make destination non-empty, then reset to satisfy preconditions.
    dst_.SetStr("will be reset", 0);
    ASSERT_FALSE(dst_.Empty());
    dst_.Reset();
    ASSERT_TRUE(dst_.Empty());

    src_.TransferTo(&dst_);

    EXPECT_STREQ(dst_.GetStr(), "moved");
    EXPECT_FALSE(dst_.Empty());
    EXPECT_TRUE(src_.Empty());
}

#ifndef NDEBUG
TEST_F(StrPairTransferToTest_155, TransferToWithNullDestinationDies_155) {
    src_.SetStr("x", 0);
    ASSERT_DEATH({ src_.TransferTo(nullptr); }, ".*");
}

TEST_F(StrPairTransferToTest_155, TransferToWithNonEmptyDestinationDies_155) {
    src_.SetStr("src", 0);
    dst_.SetStr("dst-not-empty", 0);

    // TransferTo requires destination to be in a default/empty state.
    ASSERT_DEATH({ src_.TransferTo(&dst_); }, ".*");
}
#endif

}  // namespace
