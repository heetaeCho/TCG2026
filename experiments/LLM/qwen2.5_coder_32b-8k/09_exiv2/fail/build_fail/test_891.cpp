#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "olympusmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



class OlympusMakerNoteTest_891 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(OlympusMakerNoteTest_891, TagListIp_ReturnsConstantReference_891) {

    const auto& tagList = OlympusMakerNote::tagListIp();

    EXPECT_TRUE(&tagList != nullptr);

}



TEST_F(OlympusMakerNoteTest_891, Print0x0200_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0200(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0204_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0204(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x1015_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x1015(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0201_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0201(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0209_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0209(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, PrintEq0x0301_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::printEq0x0301(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, PrintCs0x0301_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::printCs0x0301(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x050f_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x050f(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0527_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0527(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0529_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0529(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x1209_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x1209(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0305_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0305(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_891, Print0x0308_NormalOperation_891) {

    std::ostringstream os;

    OlympusMakerNote::print0x0308(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
