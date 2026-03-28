#include <gtest/gtest.h>

#include "splash/SplashTypes.h"



class SplashTypesTest_1043 : public ::testing::Test {

protected:

    // Any necessary setup or teardown can go here.

};



TEST_F(SplashTypesTest_1043, NormalOperation_1043) {

    unsigned char color[] = {50};

    EXPECT_EQ(splashDeviceN8C(color), 50);

}



TEST_F(SplashTypesTest_1043, BoundaryConditionMinimum_1043) {

    unsigned char color[] = {0};

    EXPECT_EQ(splashDeviceN8C(color), 0);

}



TEST_F(SplashTypesTest_1043, BoundaryConditionMaximum_1043) {

    unsigned char color[] = {255};

    EXPECT_EQ(splashDeviceN8C(color), 255);

}

```


