// File: table/blockhandle_test_388.cc
#include <gtest/gtest.h>
#include "table/format.h"  // Provides leveldb::BlockHandle

using leveldb::BlockHandle;

class BlockHandleTest_388 : public ::testing::Test {
protected:
    BlockHandle bh_;
};

// Normal operation: setting and then reading back an arbitrary offset.
TEST_F(BlockHandleTest_388, SetOffsetReturnsSameValue_388) {
    const uint64_t kValue = 123456789ull;
    bh_.set_offset(kValue);
    EXPECT_EQ(kValue, bh_.offset());
}

// Boundary condition: offset set to zero.
TEST_F(BlockHandleTest_388, SetOffsetZero_388) {
    const uint64_t kZero = 0ull;
    bh_.set_offset(kZero);
    EXPECT_EQ(kZero, bh_.offset());
}

// Boundary condition: offset set to max uint64.
TEST_F(BlockHandleTest_388, SetOffsetMaxUint64_388) {
    const uint64_t kMax = std::numeric_limits<uint64_t>::max();
    bh_.set_offset(kMax);
    EXPECT_EQ(kMax, bh_.offset());
}

// Behavioral check: multiple updates—latest set value should be observed.
TEST_F(BlockHandleTest_388, SetOffsetMultipleUpdatesLastWins_388) {
    bh_.set_offset(10ull);
    bh_.set_offset(20ull);
    bh_.set_offset(30ull);
    EXPECT_EQ(30ull, bh_.offset());
}
