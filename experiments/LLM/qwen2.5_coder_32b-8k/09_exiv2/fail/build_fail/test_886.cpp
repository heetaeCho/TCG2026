#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "olympusmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class OlympusMakerNoteTest_886 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(OlympusMakerNoteTest_886, Print0x0200_NormalOperation_886) {

    OlympusMakerNote::print0x0200(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0204_NormalOperation_886) {

    OlympusMakerNote::print0x0204(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x1015_NormalOperation_886) {

    OlympusMakerNote::print0x1015(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0201_NormalOperation_886) {

    OlympusMakerNote::print0x0201(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0209_NormalOperation_886) {

    OlympusMakerNote::print0x0209(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, PrintEq0x0301_NormalOperation_886) {

    OlympusMakerNote::printEq0x0301(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, PrintCs0x0301_NormalOperation_886) {

    OlympusMakerNote::printCs0x0301(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x050f_NormalOperation_886) {

    OlympusMakerNote::print0x050f(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0527_NormalOperation_886) {

    OlympusMakerNote::print0x0527(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0529_NormalOperation_886) {

    OlympusMakerNote::print0x0529(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x1209_NormalOperation_886) {

    OlympusMakerNote::print0x1209(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0305_NormalOperation_886) {

    OlympusMakerNote::print0x0305(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, Print0x0308_NormalOperation_886) {

    OlympusMakerNote::print0x0308(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, PrintGeneric_NormalOperation_886) {

    OlympusMakerNote::printGeneric(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_886, TagList_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagList();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListCs_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListCs();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListEq_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListEq();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListRd_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListRd();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListRd2_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListRd2();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListIp_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListIp();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListFi_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListFi();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListFe_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListFe();

    EXPECT_NE(tags, nullptr);

}



TEST_F(OlympusMakerNoteTest_886, TagListRi_ReturnsNonNull_886) {

    const auto& tags = OlympusMakerNote::tagListRi();

    EXPECT_NE(tags, nullptr);

}
