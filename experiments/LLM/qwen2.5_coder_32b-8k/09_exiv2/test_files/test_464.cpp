#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest_464 : public ::testing::Test {

protected:

    Nikon3MakerNote nikon3MakerNote;

    std::ostringstream os;

};



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_NormalOperation_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 4);

    value.rationals()[0] = {100, 1};

    value.rationals()[1] = {100, 1};

    value.rationals()[2] = {8, 1};

    value.rationals()[3] = {8, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "100mm F8.00");

}



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_DifferentFocalLengths_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 4);

    value.rationals()[0] = {50, 1};

    value.rationals()[1] = {70, 1};

    value.rationals()[2] = {8, 1};

    value.rationals()[3] = {8, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "50-70mm F8.00");

}



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_DifferentApertures_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 4);

    value.rationals()[0] = {100, 1};

    value.rationals()[1] = {100, 1};

    value.rationals()[2] = {8, 1};

    value.rationals()[3] = {16, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "100mm F8.00-16.00");

}



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_ZeroDenominatorInFocalLength_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 4);

    value.rationals()[0] = {100, 1};

    value.rationals()[1] = {100, 0}; // Zero denominator

    value.rationals()[2] = {8, 1};

    value.rationals()[3] = {8, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "(100/1 100/0 8/1 8/1)");

}



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_ZeroDenominatorInAperture_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 4);

    value.rationals()[0] = {100, 1};

    value.rationals()[1] = {100, 1};

    value.rationals()[2] = {8, 0}; // Zero denominator

    value.rationals()[3] = {8, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "(100/1 100/1 8/0 8/1)");

}



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_ValueSizeLessThanFour_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 2);

    value.rationals()[0] = {100, 1};

    value.rationals()[1] = {100, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "(100/1 100/1)");

}



TEST_F(Nikon3MakerNoteTest_464, PutIncreasesCount_ValueSizeGreaterThanFour_464) {

    Exiv2::Value value;

    value.makeArray(Exiv2::rational, 5);

    value.rationals()[0] = {100, 1};

    value.rationals()[1] = {100, 1};

    value.rationals()[2] = {8, 1};

    value.rationals()[3] = {8, 1};

    value.rationals()[4] = {16, 1};



    nikon3MakerNote.print0x0084(os, value, nullptr);



    EXPECT_EQ(os.str(), "100mm F8.00");

}
