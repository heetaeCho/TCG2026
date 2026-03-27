#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "sonymn_int.cpp"



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class SonyMakerNoteTest_1601 : public ::testing::Test {

protected:

    SonyMakerNote sonyMakerNote;

};



TEST_F(SonyMakerNoteTest_1601, PrintExposureStandardAdjustment_NormalOperation_1601) {

    Value value;

    value.makeArray(signedRational);

    value.rational(0).first = 3;

    value.rational(0).second = 2;



    std::ostringstream os;

    sonyMakerNote.printExposureStandardAdjustment(os, value, nullptr);



    EXPECT_EQ("1.5", os.str());

}



TEST_F(SonyMakerNoteTest_1601, PrintExposureStandardAdjustment_ValueCountNotOne_1601) {

    Value value;

    value.makeArray(signedRational);

    value.rational(0).first = 3;

    value.rational(0).second = 2;

    value.rational(1).first = 4;

    value.rational(1).second = 3;



    std::ostringstream os;

    sonyMakerNote.printExposureStandardAdjustment(os, value, nullptr);



    EXPECT_THAT(os.str(), HasSubstr("(3/2 4/3)"));

}



TEST_F(SonyMakerNoteTest_1601, PrintExposureStandardAdjustment_ValueTypeNotSignedRational_1601) {

    Value value;

    value.makeArray(longText);

    value.readString() = "Sample Text";



    std::ostringstream os;

    sonyMakerNote.printExposureStandardAdjustment(os, value, nullptr);



    EXPECT_THAT(os.str(), HasSubstr("(Sample Text)"));

}



TEST_F(SonyMakerNoteTest_1601, PrintExposureStandardAdjustment_ValueZeroDenominator_1601) {

    Value value;

    value.makeArray(signedRational);

    value.rational(0).first = 3;

    value.rational(0).second = 0;



    std::ostringstream os;

    sonyMakerNote.printExposureStandardAdjustment(os, value, nullptr);



    EXPECT_EQ("inf", os.str()); // Assuming the division by zero results in infinity representation

}
