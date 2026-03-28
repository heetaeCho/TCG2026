#include <gtest/gtest.h>

#include "TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class Nikon3MakerNoteTest_433 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value value;

    const ExifData* metadata = nullptr;

};



TEST_F(Nikon3MakerNoteTest_433, TagListFl6ReturnsConstantValue_433) {

    auto result = Nikon3MakerNote::tagListFl6();

    EXPECT_NE(result, nullptr);

}



TEST_F(Nikon3MakerNoteTest_433, Print0x0002NormalOperation_433) {

    os.str("");

    Nikon3MakerNote::print0x0002(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintAf2AreaModeNormalOperation_433) {

    os.str("");

    Nikon3MakerNote::printAf2AreaMode(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, Print0x0089WithMetadata_433) {

    os.str("");

    Nikon3MakerNote::print0x0089(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintLensIdWithGroup_433) {

    os.str("");

    std::string group = "SampleGroup";

    Nikon3MakerNote::printLensId(os, value, metadata, group);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintFocusDistanceNormalOperation_433) {

    os.str("");

    Nikon3MakerNote::printFocusDistance(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintApertureNormalOperation_433) {

    os.str("");

    Nikon3MakerNote::printAperture(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintFocalNormalOperation_433) {

    os.str("");

    Nikon3MakerNote::printFocal(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintFStopsNormalOperation_433) {

    os.str("");

    Nikon3MakerNote::printFStops(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(Nikon3MakerNoteTest_433, PrintExitPupilPositionNormalOperation_433) {

    os.str("");

    Nikon3MakerNote::printExitPupilPosition(os, value, metadata);

    EXPECT_FALSE(os.str().empty());

}
