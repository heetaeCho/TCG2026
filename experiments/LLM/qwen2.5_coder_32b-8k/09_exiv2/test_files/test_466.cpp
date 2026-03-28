#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_466 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    Value value;

};



TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NotUsed_466) {

    std::ostringstream os;

    value = RationalValue(0, 1); // r == 0

    nikon3MakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ(os.str(), "Not used");

}



TEST_F(Nikon3MakerNoteTest_466, Print0x0086_ZeroDenominator_466) {

    std::ostringstream os;

    value = RationalValue(1, 0); // s == 0

    nikon3MakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ(os.str(), "(1/0)");

}



TEST_F(Nikon3MakerNoteTest_466, Print0x0086_NormalOperation_466) {

    std::ostringstream os;

    value = RationalValue(3, 2); // r == 3, s == 2

    nikon3MakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ(os.str(), "1.5x");

}



TEST_F(Nikon3MakerNoteTest_466, Print0x0086_BoundaryCondition_466) {

    std::ostringstream os;

    value = RationalValue(1, 1); // r == 1, s == 1

    nikon3MakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ(os.str(), "1.0x");

}
