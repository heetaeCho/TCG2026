// TEST_ID: 23
// File: MemPoolTTraceTests_23.cpp

#include <gtest/gtest.h>

#include <string>

#include "TestProjects/tinyxml2/tinyxml2.h"

namespace {

template <size_t N>
using PoolT = tinyxml2::MemPoolT<N>;

class MemPoolTTraceTest_23 : public ::testing::Test {
protected:
    PoolT<16> pool;
};

TEST_F(MemPoolTTraceTest_23, TracePrintsNameAndKeyTokens_23) {
    const char* name = "MyPool";

    testing::internal::CaptureStdout();
    pool.Trace(name);
    const std::string out = testing::internal::GetCapturedStdout();

    // Don't assume numeric values; just validate format-ish and that the name is included.
    EXPECT_NE(out.find("Mempool "), std::string::npos);
    EXPECT_NE(out.find(name), std::string::npos);
    EXPECT_NE(out.find("watermark="), std::string::npos);
    EXPECT_NE(out.find(" current="), std::string::npos);
    EXPECT_NE(out.find(" size="), std::string::npos);
    EXPECT_NE(out.find(" nAlloc="), std::string::npos);
    EXPECT_NE(out.find(" blocks="), std::string::npos);
}

TEST_F(MemPoolTTraceTest_23, TraceAcceptsEmptyName_23) {
    const char* name = "";

    testing::internal::CaptureStdout();
    pool.Trace(name);
    const std::string out = testing::internal::GetCapturedStdout();

    EXPECT_NE(out.find("Mempool "), std::string::npos);
    // Empty name: we only assert that output is produced and has expected tokens.
    EXPECT_NE(out.find("watermark="), std::string::npos);
}

TEST_F(MemPoolTTraceTest_23, TraceDoesNotChangeObservableCounters_23) {
    const size_t itemSizeBefore = pool.ItemSize();
    const size_t currentBefore = pool.CurrentAllocs();
    const size_t untrackedBefore = pool.Untracked();

    testing::internal::CaptureStdout();
    pool.Trace("NoSideEffects");
    (void)testing::internal::GetCapturedStdout();

    EXPECT_EQ(pool.ItemSize(), itemSizeBefore);
    EXPECT_EQ(pool.CurrentAllocs(), currentBefore);
    EXPECT_EQ(pool.Untracked(), untrackedBefore);
}

TEST_F(MemPoolTTraceTest_23, TraceWorksAfterAllocAndFreeWithoutChangingCounts_23) {
    void* p = pool.Alloc();
    const size_t currentAfterAlloc = pool.CurrentAllocs();
    const size_t untrackedAfterAlloc = pool.Untracked();

    testing::internal::CaptureStdout();
    pool.Trace("AfterAlloc");
    const std::string out1 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out1.find("AfterAlloc"), std::string::npos);

    // Trace should not alter observable counters.
    EXPECT_EQ(pool.CurrentAllocs(), currentAfterAlloc);
    EXPECT_EQ(pool.Untracked(), untrackedAfterAlloc);

    // Free only if Alloc returned something usable.
    if (p) {
        pool.Free(p);
    }

    const size_t currentAfterFree = pool.CurrentAllocs();
    const size_t untrackedAfterFree = pool.Untracked();

    testing::internal::CaptureStdout();
    pool.Trace("AfterFree");
    const std::string out2 = testing::internal::GetCapturedStdout();
    EXPECT_NE(out2.find("AfterFree"), std::string::npos);

    EXPECT_EQ(pool.CurrentAllocs(), currentAfterFree);
    EXPECT_EQ(pool.Untracked(), untrackedAfterFree);
}

}  // namespace
