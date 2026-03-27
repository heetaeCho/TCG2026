#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.hpp"

#include <chrono>



using namespace Catch::Benchmark::Detail;



class EnvironmentEstimateTest_909 : public ::testing::Test {

protected:

    using Clock = std::chrono::high_resolution_clock;

};



TEST_F(EnvironmentEstimateTest_909, NormalOperation_ReturnsValidEnvironmentEstimate_909) {

    auto estimate = estimate_clock_resolution<Clock>(10);

    EXPECT_GE(estimate.duration.count(), 0);

}



TEST_F(EnvironmentEstimateTest_909, BoundaryCondition_ZeroIterations_ThrowsOrHandlesGracefully_909) {

    // Assuming the function handles zero iterations gracefully

    auto estimate = estimate_clock_resolution<Clock>(0);

    EXPECT_GE(estimate.duration.count(), 0);

}



TEST_F(EnvironmentEstimateTest_909, BoundaryCondition_NegativeIterations_ThrowsOrHandlesGracefully_909) {

    // Assuming the function handles negative iterations gracefully

    auto estimate = estimate_clock_resolution<Clock>(-1);

    EXPECT_GE(estimate.duration.count(), 0);

}

```


