#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <iostream>

#include <string>

#include "nikonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

    ExifData* mockMetadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest, TagListVrReturnsConstant_420) {

    auto result = Nikon3MakerNote::tagListVr();

    EXPECT_EQ(result, Nikon3MakerNote::tagInfoVr_);

}



TEST_F(Nikon3MakerNoteTest, PrintIiIsoNormalOperation_420) {

    Nikon3MakerNote::printIiIso(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaModeWithMetadata_420) {

    Nikon3MakerNote::printAf2AreaMode(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensIdWithGroup_420) {

    std::string group = "SampleGroup";

    Nikon3MakerNote::printLensId(os, mockValue, mockMetadata, group);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocusWithMetadata_420) {

    Nikon3MakerNote::printAfPointsInFocus(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFlashGroupAControlDataWithMetadata_420) {

    Nikon3MakerNote::printFlashGroupAControlData(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6WithMetadata_420) {

    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
