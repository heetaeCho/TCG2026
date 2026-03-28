#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_939 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;

    ExifData mockExifData;

};



TEST_F(CanonMakerNoteTest_939, TagListAfC_ReturnsExpectedTagInfo_939) {

    auto tagList = CanonMakerNote::tagListAfC();

    EXPECT_NE(tagList, nullptr);

}



TEST_F(CanonMakerNoteTest_939, PrintFiFileNumber_NormalOperation_939) {

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintFocalLength_NormalOperation_939) {

    CanonMakerNote::printFocalLength(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, Print0x0008_NormalOperation_939) {

    CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, Print0x000a_NormalOperation_939) {

    CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, Print0x000c_NormalOperation_939) {

    CanonMakerNote::print0x000c(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintCs0x0002_NormalOperation_939) {

    CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintCsLensType_NormalOperation_939) {

    CanonMakerNote::printCsLensType(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintCsLens_NormalOperation_939) {

    CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintLe0x0000_NormalOperation_939) {

    CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0001_NormalOperation_939) {

    CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0002_NormalOperation_939) {

    CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0003_NormalOperation_939) {

    CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0009_NormalOperation_939) {

    CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x000c_NormalOperation_939) {

    CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x000d_NormalOperation_939) {

    CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x000e_NormalOperation_939) {

    CanonMakerNote::printSi0x000e(os, mockValue, &mockExifData);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0013_NormalOperation_939) {

    CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0015_NormalOperation_939) {

    CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0016_NormalOperation_939) {

    CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0017_NormalOperation_939) {

    CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintSi0x0018_NormalOperation_939) {

    CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_939, PrintFiFocusDistance_NormalOperation_939) {

    CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}
