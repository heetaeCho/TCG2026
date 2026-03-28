// BufStream_test_203.cpp
#include <gtest/gtest.h>

#include "Stream.h"

// The TEST_ID is 203

namespace {

class BufStreamTest_203 : public ::testing::Test {};

TEST_F(BufStreamTest_203, GetKindReturnsWeird_WithTypicalBufSize_203)
{
    // Use the (int, int) constructor to avoid relying on other collaborators.
    BufStream s(/*strA=*/0, /*bufSizeA=*/16384);
    EXPECT_EQ(s.getKind(), strWeird);
}

TEST_F(BufStreamTest_203, GetKindReturnsWeird_WithSmallBufSize_203)
{
    BufStream s(/*strA=*/0, /*bufSizeA=*/1);
    EXPECT_EQ(s.getKind(), strWeird);
}

TEST_F(BufStreamTest_203, GetKindReturnsWeird_WithZeroBufSizeBoundary_203)
{
    // Boundary condition: zero buffer size.
    BufStream s(/*strA=*/0, /*bufSizeA=*/0);
    EXPECT_EQ(s.getKind(), strWeird);
}

TEST_F(BufStreamTest_203, GetKindCallableOnConstObject_203)
{
    BufStream s(/*strA=*/0, /*bufSizeA=*/1024);
    const BufStream& cs = s;
    EXPECT_EQ(cs.getKind(), strWeird);
}

} // namespace