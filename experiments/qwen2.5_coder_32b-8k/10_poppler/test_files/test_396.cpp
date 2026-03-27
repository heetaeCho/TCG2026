#include <gtest/gtest.h>

#include "GfxState.h"



// Assuming GfxColorComp is a typedef for some numeric type, e.g., float or double.

// For the purpose of these tests, we'll assume it's a float.

typedef float GfxColorComp;



class GfxRGBTest_396 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(GfxRGBTest_396, EqualityOperatorSameValues_396) {

    GfxRGB rgb1 = {0.5f, 0.5f, 0.5f};

    GfxRGB rgb2 = {0.5f, 0.5f, 0.5f};

    EXPECT_TRUE(rgb1 == rgb2);

}



TEST_F(GfxRGBTest_396, EqualityOperatorDifferentValues_396) {

    GfxRGB rgb1 = {0.5f, 0.4f, 0.3f};

    GfxRGB rgb2 = {0.5f, 0.5f, 0.5f};

    EXPECT_FALSE(rgb1 == rgb2);

}



TEST_F(GfxRGBTest_396, EqualityOperatorBoundaryValues_396) {

    GfxRGB rgb1 = {0.0f, 0.0f, 0.0f};

    GfxRGB rgb2 = {1.0f, 1.0f, 1.0f};

    EXPECT_FALSE(rgb1 == rgb2);

}



TEST_F(GfxRGBTest_396, EqualityOperatorMaxValues_396) {

    GfxRGB rgb1 = {1.0f, 1.0f, 1.0f};

    GfxRGB rgb2 = {1.0f, 1.0f, 1.0f};

    EXPECT_TRUE(rgb1 == rgb2);

}



TEST_F(GfxRGBTest_396, EqualityOperatorMinValues_396) {

    GfxRGB rgb1 = {0.0f, 0.0f, 0.0f};

    GfxRGB rgb2 = {0.0f, 0.0f, 0.0f};

    EXPECT_TRUE(rgb1 == rgb2);

}
