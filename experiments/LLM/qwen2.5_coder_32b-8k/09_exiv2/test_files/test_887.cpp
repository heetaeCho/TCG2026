#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/olympusmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class OlympusMakerNoteTest_887 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockExifData;

};



TEST_F(OlympusMakerNoteTest_887, print0x0200_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0200(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0204_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0204(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x1015_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x1015(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0201_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0201(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0209_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0209(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, printEq0x0301_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::printEq0x0301(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, printCs0x0301_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::printCs0x0301(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x050f_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x050f(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0527_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0527(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0529_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0529(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x1209_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x1209(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0305_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0305(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, print0x0308_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::print0x0308(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, printGeneric_NominalCase_887) {

    std::ostringstream os;

    OlympusMakerNote::printGeneric(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_887, tagListCs_ReturnsNonEmptyArray_887) {

    const TagInfo* tags = OlympusMakerNote::tagListCs();

    EXPECT_NE(tags, nullptr);

}
