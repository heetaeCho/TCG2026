#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"



using namespace Exiv2::Internal;



class CanonMakerNoteTest_915 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value mockValue; // Assuming Value is some type that can be default-constructed

    const ExifData* mockMetadata = nullptr; // Assuming ExifData is a pointer type

};



TEST_F(CanonMakerNoteTest_915, tagListFi_ReturnsValidTagInfo_915) {

    auto tagInfo = CanonMakerNote::tagListFi();

    EXPECT_NE(tagInfo, nullptr);

}



TEST_F(CanonMakerNoteTest_915, printFiFileNumber_ValidOutput_915) {

    CanonMakerNote::printFiFileNumber(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printFocalLength_ValidOutput_915) {

    CanonMakerNote::printFocalLength(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, print0x0008_ValidOutput_915) {

    CanonMakerNote::print0x0008(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, print0x000a_ValidOutput_915) {

    CanonMakerNote::print0x000a(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, print0x000c_ValidOutput_915) {

    CanonMakerNote::print0x000c(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printCs0x0002_ValidOutput_915) {

    CanonMakerNote::printCs0x0002(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printCsLensType_ValidOutput_915) {

    CanonMakerNote::printCsLensType(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printCsLens_ValidOutput_915) {

    CanonMakerNote::printCsLens(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printLe0x0000_ValidOutput_915) {

    CanonMakerNote::printLe0x0000(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0001_ValidOutput_915) {

    CanonMakerNote::printSi0x0001(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0002_ValidOutput_915) {

    CanonMakerNote::printSi0x0002(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0003_ValidOutput_915) {

    CanonMakerNote::printSi0x0003(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0009_ValidOutput_915) {

    CanonMakerNote::printSi0x0009(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x000c_ValidOutput_915) {

    CanonMakerNote::printSi0x000c(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x000d_ValidOutput_915) {

    CanonMakerNote::printSi0x000d(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x000e_ValidOutput_915) {

    CanonMakerNote::printSi0x000e(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0013_ValidOutput_915) {

    CanonMakerNote::printSi0x0013(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0015_ValidOutput_915) {

    CanonMakerNote::printSi0x0015(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0016_ValidOutput_915) {

    CanonMakerNote::printSi0x0016(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0017_ValidOutput_915) {

    CanonMakerNote::printSi0x0017(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printSi0x0018_ValidOutput_915) {

    CanonMakerNote::printSi0x0018(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_915, printFiFocusDistance_ValidOutput_915) {

    CanonMakerNote::printFiFocusDistance(oss, mockValue, mockMetadata);

    EXPECT_FALSE(oss.str().empty());

}
