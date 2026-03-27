#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "sigmamn_int.cpp"  // Assuming the class definition is in this file



using namespace Exiv2::Internal;

using ::testing::HasSubstr;



class SigmaMakerNoteTest_1725 : public ::testing::Test {

protected:

    SigmaMakerNote sigmaMakerNote_;

};



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_NormalOperation_1725) {

    std::ostringstream os;

    Exiv2::Value value("Key: Value");

    const ExifData* exifData = nullptr;  // Not used in the function



    sigmaMakerNote_.printStripLabel(os, value, exifData);



    EXPECT_EQ(os.str(), "Value");

}



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_BoundaryCondition_EmptyString_1725) {

    std::ostringstream os;

    Exiv2::Value value("");

    const ExifData* exifData = nullptr;



    sigmaMakerNote_.printStripLabel(os, value, exifData);



    EXPECT_EQ(os.str(), "");

}



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_BoundaryCondition_NoColon_1725) {

    std::ostringstream os;

    Exiv2::Value value("NoColonHere");

    const ExifData* exifData = nullptr;



    sigmaMakerNote_.printStripLabel(os, value, exifData);



    EXPECT_EQ(os.str(), "NoColonHere");

}



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_BoundaryCondition_ColonOnly_1725) {

    std::ostringstream os;

    Exiv2::Value value(":");

    const ExifData* exifData = nullptr;



    sigmaMakerNote_.printStripLabel(os, value, exifData);



    EXPECT_EQ(os.str(), "");

}



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_BoundaryCondition_ColonWithSpace_1725) {

    std::ostringstream os;

    Exiv2::Value value(": Value");

    const ExifData* exifData = nullptr;



    sigmaMakerNote_.printStripLabel(os, value, exifData);



    EXPECT_EQ(os.str(), "Value");

}



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_BoundaryCondition_MultipleColons_1725) {

    std::ostringstream os;

    Exiv2::Value value("Key1: Key2: Value");

    const ExifData* exifData = nullptr;



    sigmaMakerNote_.printStripLabel(os, value, exifData);



    EXPECT_EQ(os.str(), "Key2: Value");

}



TEST_F(SigmaMakerNoteTest_1725, PrintStripLabel_ExceptionalCase_NullValue_1725) {

    std::ostringstream os;

    Exiv2::Value* nullValuePtr = nullptr;  // This will cause a segmentation fault if not handled

    const ExifData* exifData = nullptr;



    // Assuming the Value object is properly constructed and passed, we simulate an invalid state

    try {

        sigmaMakerNote_.printStripLabel(os, *nullValuePtr, exifData);

        FAIL() << "Expected an exception or error handling";

    } catch (const std::exception& e) {

        SUCCEED();  // Expected behavior if the function handles null gracefully

    }

}
