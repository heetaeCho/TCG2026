#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;

using ::testing::_;



class CanonMakerNoteTest_910 : public ::testing::Test {

protected:

    void SetUp() override {

        metadata = new ExifData();

    }



    void TearDown() override {

        delete metadata;

    }



    Value dummyValue;  // Assuming Value has a default constructor

    ExifData* metadata;

};



TEST_F(CanonMakerNoteTest_910, TagListSi_ReturnsConstantReference_910) {

    auto& tagList = CanonMakerNote::tagListSi();

    EXPECT_EQ(&tagList, &CanonMakerNote::tagListSi());

}



TEST_F(CanonMakerNoteTest_910, PrintFiFileNumber_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printFiFileNumber(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintFocalLength_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printFocalLength(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, Print0x0008_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::print0x0008(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, Print0x000a_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::print0x000a(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, Print0x000c_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::print0x000c(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintCs0x0002_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printCs0x0002(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintCsLensType_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printCsLensType(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintCsLens_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printCsLens(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintLe0x0000_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printLe0x0000(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0001_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0001(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0002_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0002(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0003_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0003(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0009_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0009(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x000c_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x000c(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x000d_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x000d(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x000e_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x000e(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0013_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0013(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0015_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0015(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0016_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0016(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0017_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0017(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintSi0x0018_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printSi0x0018(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(CanonMakerNoteTest_910, PrintFiFocusDistance_NonEmptyOutput_910) {

    std::ostringstream oss;

    CanonMakerNote::printFiFocusDistance(oss, dummyValue, metadata);

    EXPECT_FALSE(oss.str().empty());

}
