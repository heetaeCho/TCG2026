#include <gtest/gtest.h>



// Assuming GfxColorComp is defined somewhere and it's typically a float between 0 and 1.

// For this example, let's assume GfxColorComp is a typedef for float.



TEST(colToShortTest_394, NormalOperation_394) {

    EXPECT_EQ(colToShort(0.0f), 0);

    EXPECT_EQ(colToShort(1.0f), 65535);

    EXPECT_EQ(colToShort(0.5f), 32768);

}



TEST(colToShortTest_394, BoundaryConditions_394) {

    EXPECT_EQ(colToShort(0.0f), 0);

    EXPECT_EQ(colToShort(1.0f), 65535);

    EXPECT_EQ(colToShort(-0.1f), 0); // Assuming clamping behavior

    EXPECT_EQ(colToShort(1.1f), 65535); // Assuming clamping behavior

}



TEST(colToShortTest_394, ExceptionalCases_394) {

    // Since colToShort is a simple cast and there are no exceptional cases observable through this function,

    // we can assume that it will not throw exceptions or have undefined behavior for valid float inputs.

    EXPECT_NO_THROW(colToShort(0.5f));

}
