#include <gtest/gtest.h>

#include "Annot.h"



// Test fixture for AnnotCoord class tests.

class AnnotCoordTest_734 : public ::testing::Test {

protected:

    // Initialize any common objects or states here if necessary.

};



// Test to verify normal operation of getX() method with default constructor.

TEST_F(AnnotCoordTest_734, GetX_DefaultConstructor_734) {

    AnnotCoord coord;

    EXPECT_EQ(coord.getX(), 0.0);

}



// Test to verify normal operation of getX() method with parameterized constructor.

TEST_F(AnnotCoordTest_734, GetX_ParameterizedConstructor_734) {

    AnnotCoord coord(5.0, 10.0);

    EXPECT_EQ(coord.getX(), 5.0);

}



// Test to verify boundary condition of getX() method with large positive value.

TEST_F(AnnotCoordTest_734, GetX_LargePositiveValue_734) {

    AnnotCoord coord(1e9, 2e9);

    EXPECT_EQ(coord.getX(), 1e9);

}



// Test to verify boundary condition of getX() method with large negative value.

TEST_F(AnnotCoordTest_734, GetX_LargeNegativeValue_734) {

    AnnotCoord coord(-1e9, -2e9);

    EXPECT_EQ(coord.getX(), -1e9);

}



// Test to verify boundary condition of getX() method with zero value.

TEST_F(AnnotCoordTest_734, GetX_ZeroValue_734) {

    AnnotCoord coord(0.0, 0.0);

    EXPECT_EQ(coord.getX(), 0.0);

}
