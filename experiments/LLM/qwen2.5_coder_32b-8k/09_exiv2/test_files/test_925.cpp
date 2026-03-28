#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class CanonMakerNoteTest_925 : public ::testing::Test {

protected:

    Value mockValue;

    ExifData mockMetadata;

};



TEST_F(CanonMakerNoteTest_925, tagListCbi_ReturnsTagInfoCbi_925) {

    const auto& tags = CanonMakerNote::tagListCbi();

    EXPECT_EQ(tags, CanonMakerNote::tagInfoCbi_);

}



TEST_F(CanonMakerNoteTest_925, printFiFileNumber_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printFocalLength_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, print0x0008_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, print0x000a_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::print0x000a(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, print0x000c_ValidExifData_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::print0x000c(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printCs0x0002_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printCs0x0002(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printCsLensType_ValidMetadata_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printCsLens_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printCsLens(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printLe0x0000_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printLe0x0000(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0001_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0001(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0002_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0002(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0003_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0003(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0009_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0009(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x000c_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x000c(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x000d_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x000d(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x000e_ValidMetadata_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0013_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0013(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0015_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0015(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0016_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0016(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0017_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0017(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printSi0x0018_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printSi0x0018(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}



TEST_F(CanonMakerNoteTest_925, printFiFocusDistance_ValidValue_ReturnsStreamWithContent_925) {

    std::ostringstream os;

    const auto& result = CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os);

    EXPECT_FALSE(os.str().empty());

}
