#include <gtest/gtest.h>

#include "./TestProjects/yaml-cpp/src/contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



TEST_F(NearestTowardZeroPolicyTest_369, ShorterInterval_ReturnsDefaultConstructedInterval_369) {

    // Arrange

    using SignedSignificandBits = int;

    

    // Act

    auto result = nearest_toward_zero::shorter_interval<SignedSignificandBits>(0);



    // Assert

    EXPECT_TRUE(result.empty());

}



TEST_F(NearestTowardZeroPolicyTest_369, ShorterInterval_HandlesPositiveValue_Correctly_369) {

    // Arrange

    using SignedSignificandBits = int;

    

    // Act

    auto result = nearest_toward_zero::shorter_interval<SignedSignificandBits>(1);



    // Assert

    EXPECT_TRUE(result.empty());

}



TEST_F(NearestTowardZeroPolicyTest_369, ShorterInterval_HandlesNegativeValue_Correctly_369) {

    // Arrange

    using SignedSignificandBits = int;

    

    // Act

    auto result = nearest_toward_zero::shorter_interval<SignedSignificandBits>(-1);



    // Assert

    EXPECT_TRUE(result.empty());

}



TEST_F(NearestTowardZeroPolicyTest_369, ShorterInterval_HandlesBoundaryValue_Correctly_369) {

    // Arrange

    using SignedSignificandBits = int;

    

    // Act

    auto result = nearest_toward_zero::shorter_interval<SignedSignificandBits>(std::numeric_limits<SignedSignificandBits>::max());



    // Assert

    EXPECT_TRUE(result.empty());

}



TEST_F(NearestTowardZeroPolicyTest_369, ShorterInterval_HandlesMinimumValue_Correctly_369) {

    // Arrange

    using SignedSignificandBits = int;

    

    // Act

    auto result = nearest_toward_zero::shorter_interval<SignedSignificandBits>(std::numeric_limits<SignedSignificandBits>::min());



    // Assert

    EXPECT_TRUE(result.empty());

}

```


