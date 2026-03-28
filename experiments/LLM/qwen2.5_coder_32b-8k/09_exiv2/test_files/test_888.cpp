#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "olympusmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class OlympusMakerNoteTest_888 : public ::testing::Test {

protected:

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(OlympusMakerNoteTest_888, Print0x0200_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0200(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0204_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0204(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x1015_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x1015(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0201_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0201(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0209_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0209(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, PrintEq0x0301_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::printEq0x0301(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, PrintCs0x0301_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::printCs0x0301(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x050f_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x050f(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0527_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0527(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0529_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0529(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x1209_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x1209(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0305_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0305(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, Print0x0308_NormalOperation_888) {

    std::ostringstream os;

    OlympusMakerNote::print0x0308(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_888, TagListEq_ReturnsConstant_888) {

    const auto& tagList = OlympusMakerNote::tagListEq();

    EXPECT_TRUE(tagList != nullptr);

}
