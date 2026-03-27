#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/sonymn_int.hpp>

#include <sstream>

#include <memory>



using namespace Exiv2::Internal;

using ::testing::Return;



class SonyMakerNoteTest_1592 : public ::testing::Test {

protected:

    std::unique_ptr<SonyMakerNote> sonyMakerNote_;

    std::ostringstream oss_;



    SonyMakerNoteTest_1592() : sonyMakerNote_(std::make_unique<SonyMakerNote>()) {}

};



TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NormalOperation_APositive_BPositive_1592) {

    Exiv2::Value value;

    value.makeArray(Exiv2::signedLong);

    value[0] = 3;

    value[1] = 4;



    sonyMakerNote_->printWBShiftABGM(oss_, value, nullptr);



    EXPECT_EQ("A/B: B3, G/M: M4", oss_.str());

}



TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NormalOperation_ANegative_BNegative_1592) {

    Exiv2::Value value;

    value.makeArray(Exiv2::signedLong);

    value[0] = -3;

    value[1] = -4;



    sonyMakerNote_->printWBShiftABGM(oss_, value, nullptr);



    EXPECT_EQ("A/B: A3, G/M: G4", oss_.str());

}



TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_NormalOperation_AZero_BZero_1592) {

    Exiv2::Value value;

    value.makeArray(Exiv2::signedLong);

    value[0] = 0;

    value[1] = 0;



    sonyMakerNote_->printWBShiftABGM(oss_, value, nullptr);



    EXPECT_EQ("A/B: 0, G/M: 0", oss_.str());

}



TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_BoundaryCondition_CountNotTwo_1592) {

    Exiv2::Value value;

    value.makeArray(Exiv2::signedLong);

    value[0] = 3;



    sonyMakerNote_->printWBShiftABGM(oss_, value, nullptr);



    EXPECT_EQ("(Xmp.GDepth.Settings.GDepthMap 1 # (3))", oss_.str());

}



TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_BoundaryCondition_TypeNotSignedLong_1592) {

    Exiv2::Value value;

    value.makeArray(Exiv2::unsignedShort);

    value[0] = 3;

    value[1] = 4;



    sonyMakerNote_->printWBShiftABGM(oss_, value, nullptr);



    EXPECT_EQ("(Xmp.GDepth.Settings.GDepthMap 1 # (3 4))", oss_.str());

}



TEST_F(SonyMakerNoteTest_1592, PrintWBShiftABGM_ExceptionalCase_EmptyValue_1592) {

    Exiv2::Value value;



    sonyMakerNote_->printWBShiftABGM(oss_, value, nullptr);



    EXPECT_EQ("()", oss_.str());

}
