#include <gtest/gtest.h>



// The function to be tested

static inline unsigned char colToByte(GfxColorComp x) { return (unsigned char)(((x << 8) - x + 0x8000) >> 16); }



// Define a test fixture if needed. In this case, it's not strictly necessary.

class ColToByteTest : public ::testing::Test {

protected:

    // Any setup or teardown code can go here

};



TEST_F(ColToByteTest_393, NormalOperation_393) {

    EXPECT_EQ(colToByte(0.0f), 0);

    EXPECT_EQ(colToByte(1.0f), 255);

    EXPECT_EQ(colToByte(0.5f), 128);

}



TEST_F(ColToByteTest_393, BoundaryConditions_393) {

    EXPECT_EQ(colToByte(-0.1f), 0);   // Below the lower bound

    EXPECT_EQ(colToByte(1.1f), 255);  // Above the upper bound

}



TEST_F(ColToByteTest_393, EdgeCases_393) {

    EXPECT_EQ(colToByte(0.0f), 0);

    EXPECT_EQ(colToByte(1.0f), 255);

    EXPECT_EQ(colToByte(0.3333f), 85); // Approximation to nearest byte

    EXPECT_EQ(colToByte(0.6667f), 170); // Approximation to nearest byte

}

```


