#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "contrib/dragonbox.h"



using namespace YAML::jkj::dragonbox::policy::decimal_to_binary_rounding;



class NearestToOddPolicyTest_360 : public ::testing::Test {

protected:

    using Policy = nearest_to_odd_t;

};



TEST_F(NearestToOddPolicyTest_360, ShorterInterval_ReturnsDefaultConstructedInterval_360) {

    // Arrange

    int testValue = 42; // Example value, as the function is templated and noexcept



    // Act

    auto result = Policy::shorter_interval(testValue);



    // Assert

    EXPECT_EQ(result, interval_type::open{});

}



TEST_F(NearestToOddPolicyTest_360, ShorterInterval_HandlesZero_360) {

    // Arrange

    int testValue = 0;



    // Act

    auto result = Policy::shorter_interval(testValue);



    // Assert

    EXPECT_EQ(result, interval_type::open{});

}



TEST_F(NearestToOddPolicyTest_360, ShorterInterval_HandlesNegativeValue_360) {

    // Arrange

    int testValue = -42;



    // Act

    auto result = Policy::shorter_interval(testValue);



    // Assert

    EXPECT_EQ(result, interval_type::open{});

}



// Assuming there are no exceptional cases for this function as it's marked noexcept and returns a default constructed object.

```


