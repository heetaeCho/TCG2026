#include <gtest/gtest.h>



// Since dblToByte is a static inline function, we can directly call it in our tests.

unsigned char dblToByte(double x) { return static_cast<unsigned char>(x * 255.0); }



class DblToByteTest_390 : public ::testing::Test {

protected:

    // You can set up any common state here if needed

};



TEST_F(DblToByteTest_390, NormalOperation_390) {

    EXPECT_EQ(dblToByte(0.5), 127);

    EXPECT_EQ(dblToByte(0.0), 0);

    EXPECT_EQ(dblToByte(1.0), 255);

}



TEST_F(DblToByteTest_390, BoundaryConditions_390) {

    EXPECT_EQ(dblToByte(-0.1), 0); // Expect clamping to 0

    EXPECT_EQ(dblToByte(1.1), 255); // Expect clamping to 255

}



TEST_F(DblToByteTest_390, EdgeCases_390) {

    EXPECT_EQ(dblToByte(0.000001), 0); // Very small positive number should round to 0

    EXPECT_EQ(dblToByte(0.999999), 255); // Very close to 1 should round to 255

}



TEST_F(DblToByteTest_390, MaxMinValues_390) {

    EXPECT_EQ(dblToByte(std::numeric_limits<double>::min()), 0);

    EXPECT_EQ(dblToByte(std::numeric_limits<double>::max()), 255);

}
