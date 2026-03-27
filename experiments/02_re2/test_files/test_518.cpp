#include <gtest/gtest.h>



namespace re2 {



// Test fixture for UnHex function

class UnHexTest : public ::testing::Test {

protected:

    // No setup or teardown needed for this simple function

};



// Test normal operation with valid hex digits

TEST_F(UnHexTest_518, ValidHexDigits_518) {

    EXPECT_EQ(0, UnHex('0'));

    EXPECT_EQ(9, UnHex('9'));

    EXPECT_EQ(10, UnHex('A'));

    EXPECT_EQ(15, UnHex('F'));

    EXPECT_EQ(10, UnHex('a'));

    EXPECT_EQ(15, UnHex('f'));

}



// Test boundary conditions with the smallest and largest valid hex digits

TEST_F(UnHexTest_518, BoundaryHexDigits_518) {

    EXPECT_EQ(0, UnHex('0'));

    EXPECT_EQ(15, UnHex('F'));

    EXPECT_EQ(15, UnHex('f'));

}



// Test exceptional or error cases with invalid hex digits

TEST_F(UnHexTest_518, InvalidHexDigits_518) {

    // Note: Since ABSL_LOG(DFATAL) is used in the implementation, this will cause a fatal log message.

    // In a real-world scenario, we would need to handle or suppress this log message for testing purposes.

    EXPECT_EQ(0, UnHex('G')); // Invalid uppercase hex digit

    EXPECT_EQ(0, UnHex('g')); // Invalid lowercase hex digit

    EXPECT_EQ(0, UnHex('-')); // Invalid symbol

    EXPECT_EQ(0, UnHex(' ')); // Space character

}



}  // namespace re2
