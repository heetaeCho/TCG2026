#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.cpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Nikon3MakerNote nikonMakerNote;

    std::ostringstream oss;

    Value mockValue;

};



TEST_F(Nikon3MakerNoteTest_478, PrintAperture_NormalOperation_478) {

    unsigned char apertureValue = 24; // Example value corresponding to F/1.0

    mockValue.typeId_ = unsignedByte;

    mockValue.size_ = 1;

    mockValue.pData_ = &apertureValue;



    nikonMakerNote.printAperture(oss, mockValue, nullptr);

    EXPECT_EQ("F1.0", oss.str());

}



TEST_F(Nikon3MakerNoteTest_478, PrintAperture_ZeroValue_478) {

    unsigned char apertureValue = 0;

    mockValue.typeId_ = unsignedByte;

    mockValue.size_ = 1;

    mockValue.pData_ = &apertureValue;



    nikonMakerNote.printAperture(oss, mockValue, nullptr);

    EXPECT_EQ("n/a", oss.str());

}



TEST_F(Nikon3MakerNoteTest_478, PrintAperture_InvalidCount_478) {

    unsigned char apertureValue = 24;

    mockValue.typeId_ = unsignedByte;

    mockValue.size_ = 2; // Invalid count

    mockValue.pData_ = &apertureValue;



    nikonMakerNote.printAperture(oss, mockValue, nullptr);

    EXPECT_EQ("(0)", oss.str());

}



TEST_F(Nikon3MakerNoteTest_478, PrintAperture_InvalidType_478) {

    unsigned char apertureValue = 24;

    mockValue.typeId_ = shortType; // Invalid type

    mockValue.size_ = 1;

    mockValue.pData_ = &apertureValue;



    nikonMakerNote.printAperture(oss, mockValue, nullptr);

    EXPECT_EQ("(0)", oss.str());

}



TEST_F(Nikon3MakerNoteTest_478, PrintAperture_BoundaryCondition_478) {

    unsigned char apertureValueMax = 255; // Maximum possible value

    mockValue.typeId_ = unsignedByte;

    mockValue.size_ = 1;

    mockValue.pData_ = &apertureValueMax;



    nikonMakerNote.printAperture(oss, mockValue, nullptr);

    EXPECT_EQ("F707.4", oss.str());

}



TEST_F(Nikon3MakerNoteTest_478, PrintAperture_BoundaryConditionMin_478) {

    unsigned char apertureValueMin = 1; // Minimum non-zero value

    mockValue.typeId_ = unsignedByte;

    mockValue.size_ = 1;

    mockValue.pData_ = &apertureValueMin;



    nikonMakerNote.printAperture(oss, mockValue, nullptr);

    EXPECT_EQ("F0.9", oss.str());

}
