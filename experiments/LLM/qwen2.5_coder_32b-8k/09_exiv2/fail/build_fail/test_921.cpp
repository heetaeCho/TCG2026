#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



using namespace Exiv2::Internal;



class CanonMakerNoteTest_921 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest_921, TagListCoReturnsTagInfo_921) {

    const auto& tagList = CanonMakerNote::tagListCo();

    EXPECT_FALSE(tagList.empty());

}



TEST_F(CanonMakerNoteTest_921, PrintFiFileNumberOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintFocalLengthOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, Print0x0008OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, Print0x000AOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, Print0x000COutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintCs0x0002OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintCsLensTypeOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintCsLensOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintLe0x0000OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0001OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0002OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0003OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0009OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x000COutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x000DOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x000EOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0013OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0015OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0016OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0017OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintSi0x0018OutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_921, PrintFiFocusDistanceOutputCheck_921) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}
