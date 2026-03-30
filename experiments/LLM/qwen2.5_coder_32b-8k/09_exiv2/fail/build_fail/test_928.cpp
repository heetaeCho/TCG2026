#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_928 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockExifData;

};



TEST_F(CanonMakerNoteTest_928, TagListPreIReturnsConstant_928) {

    const auto& tagList = CanonMakerNote::tagListPreI();

    EXPECT_TRUE(tagList != nullptr);

}



TEST_F(CanonMakerNoteTest_928, PrintFiFileNumber_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printFiFileNumber(os, mockValue, &mockExifData);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintFocalLength_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printFocalLength(os, mockValue, &mockExifData);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, Print0x0008_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, Print0x000a_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, Print0x000c_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::print0x000c(os, mockValue, &mockExifData);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintCs0x0002_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintCsLensType_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printCsLensType(os, mockValue, &mockExifData);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintCsLens_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintLe0x0000_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0001_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0002_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0003_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0009_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x000c_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x000d_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x000e_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x000e(os, mockValue, &mockExifData);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0013_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0015_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0016_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0017_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintSi0x0018_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}



TEST_F(CanonMakerNoteTest_928, PrintFiFocusDistance_ReturnsStream_928) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

}
