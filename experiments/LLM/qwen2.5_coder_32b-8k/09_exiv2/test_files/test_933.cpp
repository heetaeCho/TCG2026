#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_933 : public ::testing::Test {

protected:

    std::ostringstream os;

    Value mockValue;  // Mock Value object, assuming it's default constructible

    const ExifData* mockMetadata = nullptr;  // Assuming ExifData is pointer type and can be null for these tests

};



TEST_F(CanonMakerNoteTest_933, tagListLiOp_ReturnsConstantPointer_933) {

    auto result = CanonMakerNote::tagListLiOp();

    EXPECT_NE(result, nullptr);

}



TEST_F(CanonMakerNoteTest_933, printFiFileNumber_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printFiFileNumber(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printFocalLength_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printFocalLength(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, print0x0008_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::print0x0008(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, print0x000a_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::print0x000a(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, print0x000c_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::print0x000c(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printCs0x0002_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printCs0x0002(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printCsLensType_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printCsLensType(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printCsLens_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printCsLens(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printLe0x0000_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printLe0x0000(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0001_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0001(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0002_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0002(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0003_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0003(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0009_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0009(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x000c_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000c(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x000d_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000d(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x000e_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x000e(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0013_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0013(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0015_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0015(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0016_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0016(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0017_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0017(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printSi0x0018_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printSi0x0018(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}



TEST_F(CanonMakerNoteTest_933, printFiFocusDistance_NormalOperation_933) {

    std::ostringstream os;

    CanonMakerNote::printFiFocusDistance(os, mockValue, mockMetadata);

    EXPECT_FALSE(os.str().empty());  // Assuming some output is generated

}
