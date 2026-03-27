#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



namespace Exiv2 {

    class Value {};

    struct ExifData {};

}



using namespace ::testing;

using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_440 : public Test {

protected:

    std::ostringstream os;

    Exiv2::Value value;

    const Exiv2::ExifData* metadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest_440, TagListCb1_ReturnsConstantReference_440) {

    auto& tagList = Nikon3MakerNote::tagListCb1();

    EXPECT_TRUE(&tagList == &Nikon3MakerNote::tagInfoCb1_);

}



TEST_F(Nikon3MakerNoteTest_440, PrintIiIso_NormalOperation_440) {

    os.str("");

    Nikon3MakerNote::printIiIso(os, value, metadata);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output

}



TEST_F(Nikon3MakerNoteTest_440, PrintAf2AreaMode_MetadataNullptr_440) {

    os.str("");

    Nikon3MakerNote::printAf2AreaMode(os, value, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output even if metadata is null

}



TEST_F(Nikon3MakerNoteTest_440, PrintLensId_MetadataNullptr_440) {

    os.str("");

    Nikon3MakerNote::printLensId(os, value, nullptr, "group");

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output even if metadata is null

}



TEST_F(Nikon3MakerNoteTest_440, PrintAperture_NormalOperation_440) {

    os.str("");

    Nikon3MakerNote::printAperture(os, value, metadata);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output

}



TEST_F(Nikon3MakerNoteTest_440, PrintFocal_Ld4_NormalOperation_440) {

    os.str("");

    Nikon3MakerNote::printFocalLd4(os, value, metadata);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output

}



TEST_F(Nikon3MakerNoteTest_440, PrintFocusDistance_Ld4_MetadataNullptr_440) {

    os.str("");

    Nikon3MakerNote::printFocusDistanceLd4(os, value, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output even if metadata is null

}



TEST_F(Nikon3MakerNoteTest_440, PrintFlashGroupAControlData_MetadataNullptr_440) {

    os.str("");

    Nikon3MakerNote::printFlashGroupAControlData(os, value, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output even if metadata is null

}



TEST_F(Nikon3MakerNoteTest_440, PrintExternalFlashData1Fl6_MetadataNullptr_440) {

    os.str("");

    Nikon3MakerNote::printExternalFlashData1Fl6(os, value, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output even if metadata is null

}



TEST_F(Nikon3MakerNoteTest_440, PrintPictureControl_MetadataNullptr_440) {

    os.str("");

    Nikon3MakerNote::printPictureControl(os, value, nullptr);

    EXPECT_FALSE(os.str().empty()); // Assuming print functions produce some output even if metadata is null

}
