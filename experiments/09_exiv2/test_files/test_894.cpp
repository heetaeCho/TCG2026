#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/olympusmn_int.hpp"



using namespace Exiv2::Internal;

using testing::_;



class OlympusMakerNoteTest_894 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(OlympusMakerNoteTest_894, Print0x0200_NormalOperation_894) {

    OlympusMakerNote::print0x0200(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0204_NormalOperation_894) {

    OlympusMakerNote::print0x0204(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x1015_NormalOperation_894) {

    OlympusMakerNote::print0x1015(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0201_NormalOperation_894) {

    OlympusMakerNote::print0x0201(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0209_NormalOperation_894) {

    OlympusMakerNote::print0x0209(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, PrintEq0x0301_NormalOperation_894) {

    OlympusMakerNote::printEq0x0301(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, PrintCs0x0301_NormalOperation_894) {

    OlympusMakerNote::printCs0x0301(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x050f_NormalOperation_894) {

    OlympusMakerNote::print0x050f(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0527_NormalOperation_894) {

    OlympusMakerNote::print0x0527(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0529_NormalOperation_894) {

    OlympusMakerNote::print0x0529(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x1209_NormalOperation_894) {

    OlympusMakerNote::print0x1209(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0305_NormalOperation_894) {

    OlympusMakerNote::print0x0305(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, Print0x0308_NormalOperation_894) {

    OlympusMakerNote::print0x0308(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(OlympusMakerNoteTest_894, TagListRi_ReturnsNonEmptyArray_894) {

    const auto& tagList = OlympusMakerNote::tagListRi();

    EXPECT_GT(tagList.size(), 0);

}
