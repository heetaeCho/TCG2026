#include <gtest/gtest.h>

#include "./TestProjects/poppler/splash/SplashTypes.h"



// Assuming SplashColor and SplashColorConstPtr are defined elsewhere

typedef unsigned char SplashColorComponent;

typedef const SplashColorComponent* SplashColorConstPtr;

#define SPOT_NCOMPS 4



class SplashColorEqualityTest : public ::testing::Test {

protected:

    static constexpr int COLOR_SIZE = SPOT_NCOMPS + 4;

    SplashColorComponent color1[COLOR_SIZE];

    SplashColorComponent color2[COLOR_SIZE];



    void SetUp() override {

        // Initialize colors to default values

        for (int i = 0; i < COLOR_SIZE; ++i) {

            color1[i] = static_cast<SplashColorComponent>(i);

            color2[i] = static_cast<SplashColorComponent>(i);

        }

    }



    void SetDifferentColors() {

        // Modify one component to make colors different

        color2[0] = 255;

    }

};



TEST_F(SplashColorEqualityTest_1048, ColorsEqualWhenIdentical_1048) {

    EXPECT_TRUE(splashColorEqual(color1, color2));

}



TEST_F(SplashColorEqualityTest_1048, ColorsNotEqualWhenDifferent_1048) {

    SetDifferentColors();

    EXPECT_FALSE(splashColorEqual(color1, color2));

}



TEST_F(SplashColorEqualityTest_1048, BoundaryConditionAllZero_1048) {

    for (int i = 0; i < COLOR_SIZE; ++i) {

        color1[i] = 0;

        color2[i] = 0;

    }

    EXPECT_TRUE(splashColorEqual(color1, color2));

}



TEST_F(SplashColorEqualityTest_1048, BoundaryConditionAllMaxValue_1048) {

    for (int i = 0; i < COLOR_SIZE; ++i) {

        color1[i] = 255;

        color2[i] = 255;

    }

    EXPECT_TRUE(splashColorEqual(color1, color2));

}



TEST_F(SplashColorEqualityTest_1048, BoundaryConditionOneDifferentComponent_1048) {

    for (int i = 0; i < COLOR_SIZE - 1; ++i) {

        color1[i] = 0;

        color2[i] = 0;

    }

    color1[COLOR_SIZE - 1] = 1;

    color2[COLOR_SIZE - 1] = 2;

    EXPECT_FALSE(splashColorEqual(color1, color2));

}



TEST_F(SplashColorEqualityTest_1048, BoundaryConditionFirstComponentDifferent_1048) {

    color1[0] = 0;

    color2[0] = 1;

    for (int i = 1; i < COLOR_SIZE; ++i) {

        color1[i] = 0;

        color2[i] = 0;

    }

    EXPECT_FALSE(splashColorEqual(color1, color2));

}



TEST_F(SplashColorEqualityTest_1048, BoundaryConditionLastComponentDifferent_1048) {

    color1[COLOR_SIZE - 1] = 0;

    color2[COLOR_SIZE - 1] = 1;

    for (int i = 0; i < COLOR_SIZE - 1; ++i) {

        color1[i] = 0;

        color2[i] = 0;

    }

    EXPECT_FALSE(splashColorEqual(color1, color2));

}
