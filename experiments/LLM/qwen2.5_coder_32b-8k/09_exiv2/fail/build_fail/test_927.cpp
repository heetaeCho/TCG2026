#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "TestProjects/exiv2/src/canonmn_int.hpp"



using namespace Exiv2::Internal;



class CanonMakerNoteTest_927 : public ::testing::Test {

protected:

    MockValue mockValue;

    MockExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest_927, tagListMo_ReturnsTagInfoMo_927) {

    const TagInfo* result = CanonMakerNote::tagListMo();

    EXPECT_NE(result, nullptr);

}



TEST_F(CanonMakerNoteTest_927, printFiFileNumber_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printFocalLength_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, print0x0008_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, print0x000a_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, print0x000c_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printCs0x0002_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printCsLensType_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printCsLens_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printLe0x0000_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0001_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0002_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0003_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0009_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x000c_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x000d_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x000e_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0013_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0015_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0016_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0017_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printSi0x0018_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_927, printFiFocusDistance_ValidInput_PrintsCorrectly_927) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
