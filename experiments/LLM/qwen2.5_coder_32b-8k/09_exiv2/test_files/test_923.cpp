#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest, TagListFcd1_ReturnsConstant_923) {

    const auto& tagList = CanonMakerNote::tagListFcd1();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(CanonMakerNoteTest, PrintFiFileNumber_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintFocalLength_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, Print0x0008_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, Print0x000A_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, Print0x000C_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintCs0x0002_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintCsLensType_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintCsLens_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintLe0x0000_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0001_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0002_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0003_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0009_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x000C_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x000D_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x000E_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0013_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0015_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0016_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0017_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintSi0x0018_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest, PrintFiFocusDistance_NormalOperation_923) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}
