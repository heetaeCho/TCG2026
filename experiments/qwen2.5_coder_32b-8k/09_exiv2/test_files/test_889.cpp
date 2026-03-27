#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "olympusmn_int.hpp"

#include <sstream>



using namespace ::testing;

using namespace Exiv2::Internal;



class OlympusMakerNoteTest_889 : public Test {

protected:

    std::ostringstream oss_;

    Value dummyValue_;

    const ExifData* dummyExifData_ = nullptr;

};



TEST_F(OlympusMakerNoteTest_889, TagListRdReturnsValidPointer_889) {

    const auto& tagList = OlympusMakerNote::tagListRd();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0200_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0200(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0204_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0204(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x1015_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x1015(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0201_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0201(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0209_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0209(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, PrintEq0x0301_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::printEq0x0301(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, PrintCs0x0301_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::printCs0x0301(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x050f_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x050f(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0527_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0527(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0529_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0529(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x1209_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x1209(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0305_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0305(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, Print0x0308_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::print0x0308(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}



TEST_F(OlympusMakerNoteTest_889, PrintGeneric_ReturnsSameStreamReference_889) {

    std::ostream& result = OlympusMakerNote::printGeneric(oss_, dummyValue_, dummyExifData_);

    EXPECT_EQ(&result, &oss_);

}
