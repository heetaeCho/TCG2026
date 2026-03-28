#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "nikonmn_int.hpp"

#include <sstream>

#include <exiv2/exif.hpp>



using namespace Exiv2;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_430 : public ::testing::Test {

protected:

    Value value;

    ExifData exifData;

};



TEST_F(Nikon3MakerNoteTest_430, tagListFl1_ReturnsConstantTagInfo_430) {

    const auto& tagInfo = Nikon3MakerNote::tagListFl1();

    EXPECT_TRUE(tagInfo != nullptr);

}



TEST_F(Nikon3MakerNoteTest_430, printIiIso_NormalOperation_430) {

    std::ostringstream os;

    Nikon3MakerNote::printIiIso(os, value, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_430, printAf2AreaMode_MetadataNullptr_Behavior_430) {

    std::ostringstream os;

    Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);

    EXPECT_FALSE(os.str().empty());  // Assuming no crash and some default output

}



TEST_F(Nikon3MakerNoteTest_430, printLensId_MetadataNullptr_Behavior_430) {

    std::ostringstream os;

    Nikon3MakerNote::printLensId(os, value, nullptr, "Group");

    EXPECT_FALSE(os.str().empty());  // Assuming no crash and some default output

}



TEST_F(Nikon3MakerNoteTest_430, printFlashFocalLength_NormalOperation_430) {

    std::ostringstream os;

    Nikon3MakerNote::printFlashFocalLength(os, value, &exifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_430, printFocusDistanceLd4_NormalOperation_430) {

    std::ostringstream os;

    Nikon3MakerNote::printFocusDistanceLd4(os, value, &exifData);

    EXPECT_FALSE(os.str().empty());

}
