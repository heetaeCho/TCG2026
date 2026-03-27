#include <gtest/gtest.h>

#include "olympusmn_int.hpp"

#include <sstream>

#include <memory>



using namespace Exiv2::Internal;



class OlympusMakerNoteTest_893 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue; // Assuming Value is a defined type in the actual implementation

    ExifData mockExifData; // Assuming ExifData is a defined type in the actual implementation

};



TEST_F(OlympusMakerNoteTest_893, TagListFe_ReturnsValidPointer_893) {

    const TagInfo* tagList = OlympusMakerNote::tagListFe();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(OlympusMakerNoteTest_893, Print0x0200_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0200(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0204_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0204(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x1015_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x1015(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0201_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0201(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0209_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0209(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, PrintEq0x0301_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::printEq0x0301(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, PrintCs0x0301_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::printCs0x0301(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x050f_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x050f(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0527_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0527(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0529_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0529(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x1209_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x1209(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0305_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0305(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, Print0x0308_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::print0x0308(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}



TEST_F(OlympusMakerNoteTest_893, PrintGeneric_NormalOperation_893) {

    std::ostream& result = OlympusMakerNote::printGeneric(oss, mockValue, &mockExifData);

    EXPECT_EQ(&result, &oss); // Check if the same stream is returned

}
