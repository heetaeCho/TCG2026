#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include <sstream>

#include "nikonmn_int.hpp"



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(Nikon3MakerNoteTest, TagListPc_ReturnsExpected_421) {

    const auto& tagList = Nikon3MakerNote::tagListPc();

    EXPECT_TRUE(tagList != nullptr);

}



TEST_F(Nikon3MakerNoteTest, PrintIiIso_NormalOperation_421) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAf2AreaMode_MetadataNullptr_421) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintLensId_GroupEmptyString_421) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, mockValue, &mockMetadata, "");

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintAfPointsInFocus_MetadataNullptr_421) {

    std::ostringstream os;

    Nikon3MakerNote::printAfPointsInFocus(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintExternalFlashData1Fl6_MetadataNullptr_421) {

    std::ostringstream os;

    Nikon3MakerNote::printExternalFlashData1Fl6(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest, PrintFocusDistanceLd4_NormalOperation_421) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
