#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "dragonbox.h"



namespace YAML { namespace jkj { namespace dragonbox { namespace policy { namespace decimal_to_binary_rounding {



using namespace ::testing;



class NearestAwayFromZeroTest_372 : public Test {

protected:

    using Policy = nearest_away_from_zero_t;

};



TEST_F(NearestAwayFromZeroTest_372, ShorterInterval_ReturnsDefaultConstructedInterval_372) {

    // Arrange

    int significandBits = 5; // Example value for testing



    // Act

    auto interval = Policy::shorter_interval(significandBits);



    // Assert

    EXPECT_EQ(interval, decltype(interval){});

}



// Boundary conditions

TEST_F(NearestAwayFromZeroTest_372, ShorterInterval_BoundaryCondition_ZeroSignificandBits_372) {

    // Arrange

    int significandBits = 0;



    // Act

    auto interval = Policy::shorter_interval(significandBits);



    // Assert

    EXPECT_EQ(interval, decltype(interval){});

}



TEST_F(NearestAwayFromZeroTest_372, ShorterInterval_BoundaryCondition_MaxIntSignificandBits_372) {

    // Arrange

    int significandBits = std::numeric_limits<int>::max();



    // Act

    auto interval = Policy::shorter_interval(significandBits);



    // Assert

    EXPECT_EQ(interval, decltype(interval){});

}



TEST_F(NearestAwayFromZeroTest_372, ShorterInterval_BoundaryCondition_MinIntSignificandBits_372) {

    // Arrange

    int significandBits = std::numeric_limits<int>::min();



    // Act

    auto interval = Policy::shorter_interval(significandBits);



    // Assert

    EXPECT_EQ(interval, decltype(interval){});

}



// Exceptional or error cases (if observable through the interface)

// In this case, there are no apparent exceptional or error cases as the function is templated and returns a default-constructed object.



} } } } }
