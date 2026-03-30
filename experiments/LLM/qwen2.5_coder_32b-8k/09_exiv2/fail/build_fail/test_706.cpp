#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/panasonicmn_int.hpp"

#include <sstream>

#include <exif.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class PanasonicMakerNoteTest_706 : public ::testing::Test {

protected:

    PanasonicMakerNote makerNote_;

    std::ostringstream os_;

    Value value_;

    const ExifData* exifData_ = nullptr;

};



TEST_F(PanasonicMakerNoteTest_706, print0x000f_NormalOperation_706) {

    makerNote_.print0x000f(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, print0x0023_NormalOperation_706) {

    makerNote_.print0x0023(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, print0x0029_NormalOperation_706) {

    makerNote_.print0x0029(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, print0x0033_NormalOperation_706) {

    makerNote_.print0x0033(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, print0x0036_NormalOperation_706) {

    makerNote_.print0x0036(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, print0x003c_NormalOperation_706) {

    makerNote_.print0x003c(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, printPressure_NormalOperation_706) {

    makerNote_.printPressure(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, printPanasonicText_NormalOperation_706) {

    makerNote_.printPanasonicText(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, printAccelerometer_NormalOperation_706) {

    makerNote_.printAccelerometer(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, printRollAngle_NormalOperation_706) {

    makerNote_.printRollAngle(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, printPitchAngle_NormalOperation_706) {

    makerNote_.printPitchAngle(os_, value_, exifData_);

    EXPECT_FALSE(os_.str().empty());

}



TEST_F(PanasonicMakerNoteTest_706, tagListRaw_ReturnsTagInfoRaw_706) {

    const auto& tagList = PanasonicMakerNote::tagListRaw();

    EXPECT_TRUE(tagList.size() > 0);

}
