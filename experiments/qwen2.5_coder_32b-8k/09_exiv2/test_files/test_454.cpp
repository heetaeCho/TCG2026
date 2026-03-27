#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include <exiv2/value.hpp>

#include <exiv2/exifdata.hpp>

#include "nikonmn_int.cpp"



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon1MakerNoteTest_454 : public ::testing::Test {

protected:

    Nikon1MakerNote nikonMakerNote;

    std::ostringstream os;

};



TEST_F(Nikon1MakerNoteTest_454, Print0x0086_NormalOperation_454) {

    Value value(XmpValueTypes::xmpRational);

    value.rational(0, 1);

    nikonMakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ("0.0x", os.str());

}



TEST_F(Nikon1MakerNoteTest_454, Print0x0086_NotUsed_454) {

    Value value(XmpValueTypes::xmpRational);

    value.rational(0, 2);

    nikonMakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ("Not used", os.str());

}



TEST_F(Nikon1MakerNoteTest_454, Print0x0086_DivisionByZero_454) {

    Value value(XmpValueTypes::xmpRational);

    value.rational(1, 0);

    nikonMakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ("(1/0)", os.str());

}



TEST_F(Nikon1MakerNoteTest_454, Print0x0086_BoundaryCondition_454) {

    Value value(XmpValueTypes::xmpRational);

    value.rational(3, 2);

    nikonMakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ("1.5x", os.str());

}



TEST_F(Nikon1MakerNoteTest_454, Print0x0086_FloatPrecision_454) {

    Value value(XmpValueTypes::xmpRational);

    value.rational(1, 3);

    nikonMakerNote.print0x0086(os, value, nullptr);

    EXPECT_EQ("0.3x", os.str());

}
