#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "canonmn_int.hpp"



using namespace ::testing;

using namespace Exiv2::Internal;



class CanonMakerNoteTest_937 : public Test {

protected:

    std::ostringstream os;

    Value mockValue;

    const ExifData* mockMetadata = nullptr;

};



TEST_F(CanonMakerNoteTest_937, tagListFilReturnsConstant_937) {

    auto result = CanonMakerNote::tagListFil();

    EXPECT_NE(result, nullptr);

}



TEST_F(CanonMakerNoteTest_937, printFiFileNumberNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printFocalLengthNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, print0x0008NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, print0x000aNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, print0x000cNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printCs0x0002NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printCsLensTypeNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printCsLensNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printLe0x0000NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0001NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0002NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0003NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0009NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x000cNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x000dNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x000eNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0013NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0015NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0016NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0017NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printSi0x0018NormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_937, printFiFocusDistanceNormalOperation_937) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());

}
