#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Annot.h"



using namespace testing;



class AnnotPathTest_736 : public ::testing::Test {

protected:

    AnnotPath path;

};



TEST_F(AnnotPathTest_736, GetCoordsLength_ReturnsZeroForDefaultConstructor_736) {

    EXPECT_EQ(path.getCoordsLength(), 0);

}



TEST_F(AnnotPathTest_736, GetCoordsLength_ReturnsCorrectSize_AfterInitializationWithVector_736) {

    std::vector<AnnotCoord> coords = {AnnotCoord(), AnnotCoord()};

    AnnotPath path(coords);

    EXPECT_EQ(path.getCoordsLength(), 2);

}



TEST_F(AnnotPathTest_736, GetCoordsLength_ReturnsCorrectSize_AfterInitializationWithRvalueVector_736) {

    std::vector<AnnotCoord> coords = {AnnotCoord(), AnnotCoord()};

    AnnotPath path(std::move(coords));

    EXPECT_EQ(path.getCoordsLength(), 2);

}



TEST_F(AnnotPathTest_736, GetCoordsLength_ReturnsZero_AfterInitializationWithRvalueInt_736) {

    AnnotPath path(int{0});

    EXPECT_EQ(path.getCoordsLength(), 0);

}



// Assuming getX and getY are observable and should be tested for boundary conditions

TEST_F(AnnotPathTest_736, GetX_ThrowsException_ForInvalidIndex_736) {

    EXPECT_THROW(path.getX(-1), std::out_of_range);

}



TEST_F(AnnotPathTest_736, GetY_ThrowsException_ForInvalidIndex_736) {

    EXPECT_THROW(path.getY(-1), std::out_of_range);

}



// Assuming valid index access should not throw and return some value

TEST_F(AnnotPathTest_736, GetX_ReturnsValidValue_ForValidIndex_736) {

    AnnotCoord coord;

    std::vector<AnnotCoord> coords = {coord};

    AnnotPath path(coords);

    EXPECT_NO_THROW(path.getX(0));

}



TEST_F(AnnotPathTest_736, GetY_ReturnsValidValue_ForValidIndex_736) {

    AnnotCoord coord;

    std::vector<AnnotCoord> coords = {coord};

    AnnotPath path(coords);

    EXPECT_NO_THROW(path.getY(0));

}
