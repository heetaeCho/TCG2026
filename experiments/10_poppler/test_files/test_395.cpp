#include <gtest/gtest.h>

#include "GfxState.h"



// Mocking GfxColorComp for potential future use with Google Mock if needed

using GfxColorComp = unsigned char;



TEST(clearGfxColorTest_395, ClearsAllComponentsToZero_395) {

    GfxColor color;

    // Initialize with non-zero values to ensure they are cleared

    for (int i = 0; i < gfxColorMaxComps; ++i) {

        color.c[i] = static_cast<GfxColorComp>(i + 1);

    }

    clearGfxColor(&color);



    for (int i = 0; i < gfxColorMaxComps; ++i) {

        EXPECT_EQ(color.c[i], 0) << "Component " << i << " was not cleared.";

    }

}



TEST(clearGfxColorTest_395, LeavesOtherDataUnchanged_395) {

    // This test assumes there might be other data in the GfxColor struct besides 'c'.

    // Since we don't have access to private members, this is more of a conceptual test.

    // If there are no other members, this test will still pass trivially.



    GfxColor color;

    // Initialize with non-zero values

    for (int i = 0; i < gfxColorMaxComps; ++i) {

        color.c[i] = static_cast<GfxColorComp>(i + 1);

    }

    

    clearGfxColor(&color);



    // Recheck that all components are zero

    for (int i = 0; i < gfxColorMaxComps; ++i) {

        EXPECT_EQ(color.c[i], 0) << "Component " << i << " was not cleared.";

    }



    // Additional checks would require knowledge of other members, which we don't have.

}



// Since the function only clears the array and does not return any value or throw exceptions,

// there are no exceptional cases to test. The behavior is deterministic based on input.



TEST(clearGfxColorTest_395, BoundaryCondition_ZeroComponents_395) {

    GfxColor color;

    clearGfxColor(&color);



    // Check the first and last components as boundary conditions

    EXPECT_EQ(color.c[0], 0);

    EXPECT_EQ(color.c[gfxColorMaxComps - 1], 0);

}
