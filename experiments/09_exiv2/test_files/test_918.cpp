#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class CanonMakerNoteTest_918 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest_918, TagListMc_ReturnsConstant_918) {

    const auto& tags = CanonMakerNote::tagListMc();

    EXPECT_TRUE(tags != nullptr);

}



TEST_F(CanonMakerNoteTest_918, PrintFiFileNumber_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintFocalLength_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, Print0x0008_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, Print0x000a_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, Print0x000c_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintCs0x0002_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintCsLensType_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintCsLens_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintLe0x0000_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0001_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0002_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0003_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0009_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x000c_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x000d_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x000e_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0013_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0015_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0016_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0017_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintSi0x0018_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_918, PrintFiFocusDistance_NormalOperation_918) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_FALSE(os.str().empty());

}
