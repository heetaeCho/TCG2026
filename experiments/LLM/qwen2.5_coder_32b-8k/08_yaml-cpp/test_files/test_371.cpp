#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking dependencies if needed

// None in this case as there are no external collaborators



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



class NearestAwayFromZeroTest_371 : public ::testing::Test {

protected:

    using Policy = nearest_away_from_zero_t;

};



TEST_F(NearestAwayFromZeroTest_371, NormalInterval_ReturnsDefaultConstructedInterval_371) {

    auto result = Policy::normal_interval<int>(0);

    EXPECT_EQ(result, decltype(result){});

}



// Boundary conditions

TEST_F(NearestAwayFromZeroTest_371, NormalInterval_BoundaryConditionPositiveSignificandBits_371) {

    auto result = Policy::normal_interval<int>(std::numeric_limits<int>::max());

    EXPECT_EQ(result, decltype(result){});

}



TEST_F(NearestAwayFromZeroTest_371, NormalInterval_BoundaryConditionNegativeSignificandBits_371) {

    auto result = Policy::normal_interval<int>(std::numeric_limits<int>::min());

    EXPECT_EQ(result, decltype(result){});

}



// Exceptional or error cases

// None in this case as the function is marked noexcept and does not have any parameters that could lead to errors



} } } } }
