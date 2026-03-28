#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class CanonMakerNoteTest_916 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed

    const ExifData* mockMetadata = nullptr; // Assuming ExifData is a pointer type

};



TEST_F(CanonMakerNoteTest_916, tagListPr_ReturnsConstexpr_916) {

    auto tagList = CanonMakerNote::tagListPr();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(CanonMakerNoteTest_916, printFiFileNumber_NormalOperation_916) {

    CanonMakerNote::printFiFileNumber(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printFocalLength_NormalOperation_916) {

    CanonMakerNote::printFocalLength(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, print0x0008_NormalOperation_916) {

    CanonMakerNote::print0x0008(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, print0x000a_NormalOperation_916) {

    CanonMakerNote::print0x000a(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, print0x000c_NormalOperation_916) {

    CanonMakerNote::print0x000c(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printCs0x0002_NormalOperation_916) {

    CanonMakerNote::printCs0x0002(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printCsLensType_NormalOperation_916) {

    CanonMakerNote::printCsLensType(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printCsLens_NormalOperation_916) {

    CanonMakerNote::printCsLens(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printLe0x0000_NormalOperation_916) {

    CanonMakerNote::printLe0x0000(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0001_NormalOperation_916) {

    CanonMakerNote::printSi0x0001(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0002_NormalOperation_916) {

    CanonMakerNote::printSi0x0002(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0003_NormalOperation_916) {

    CanonMakerNote::printSi0x0003(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0009_NormalOperation_916) {

    CanonMakerNote::printSi0x0009(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x000c_NormalOperation_916) {

    CanonMakerNote::printSi0x000c(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x000d_NormalOperation_916) {

    CanonMakerNote::printSi0x000d(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x000e_NormalOperation_916) {

    CanonMakerNote::printSi0x000e(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0013_NormalOperation_916) {

    CanonMakerNote::printSi0x0013(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0015_NormalOperation_916) {

    CanonMakerNote::printSi0x0015(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0016_NormalOperation_916) {

    CanonMakerNote::printSi0x0016(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0017_NormalOperation_916) {

    CanonMakerNote::printSi0x0017(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printSi0x0018_NormalOperation_916) {

    CanonMakerNote::printSi0x0018(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_916, printFiFocusDistance_NormalOperation_916) {

    CanonMakerNote::printFiFocusDistance(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
