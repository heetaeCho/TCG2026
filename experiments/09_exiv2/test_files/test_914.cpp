#include <gtest/gtest.h>

#include "canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class CanonMakerNoteTest_914 : public ::testing::Test {

protected:

    std::ostringstream oss;

    Value dummyValue;

    ExifData* pExifData = nullptr;

};



TEST_F(CanonMakerNoteTest_914, TagListTiReturnsConstant_914) {

    const auto& tagList = CanonMakerNote::tagListTi();

    EXPECT_EQ(&tagList, &CanonMakerNote::tagInfoTi_);

}



TEST_F(CanonMakerNoteTest_914, PrintFiFileNumberNormalOperation_914) {

    CanonMakerNote::printFiFileNumber(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintFocalLengthNormalOperation_914) {

    CanonMakerNote::printFocalLength(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, Print0x0008NormalOperation_914) {

    CanonMakerNote::print0x0008(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, Print0x000ANormalOperation_914) {

    CanonMakerNote::print0x000a(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, Print0x000CNormalOperation_914) {

    CanonMakerNote::print0x000c(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintCs0x0002NormalOperation_914) {

    CanonMakerNote::printCs0x0002(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintCsLensTypeNormalOperation_914) {

    CanonMakerNote::printCsLensType(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintCsLensNormalOperation_914) {

    CanonMakerNote::printCsLens(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintLe0x0000NormalOperation_914) {

    CanonMakerNote::printLe0x0000(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0001NormalOperation_914) {

    CanonMakerNote::printSi0x0001(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0002NormalOperation_914) {

    CanonMakerNote::printSi0x0002(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0003NormalOperation_914) {

    CanonMakerNote::printSi0x0003(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0009NormalOperation_914) {

    CanonMakerNote::printSi0x0009(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x000CNormalOperation_914) {

    CanonMakerNote::printSi0x000c(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x000DNormalOperation_914) {

    CanonMakerNote::printSi0x000d(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x000ENormalOperation_914) {

    CanonMakerNote::printSi0x000e(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0013NormalOperation_914) {

    CanonMakerNote::printSi0x0013(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0015NormalOperation_914) {

    CanonMakerNote::printSi0x0015(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0016NormalOperation_914) {

    CanonMakerNote::printSi0x0016(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0017NormalOperation_914) {

    CanonMakerNote::printSi0x0017(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintSi0x0018NormalOperation_914) {

    CanonMakerNote::printSi0x0018(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_914, PrintFiFocusDistanceNormalOperation_914) {

    CanonMakerNote::printFiFocusDistance(oss, dummyValue, pExifData);

    EXPECT_FALSE(oss.str().empty());

}
