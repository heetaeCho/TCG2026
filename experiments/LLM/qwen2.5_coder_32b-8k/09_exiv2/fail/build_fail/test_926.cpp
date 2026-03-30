#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Ref;



class CanonMakerNoteTest_926 : public ::testing::Test {

protected:

    std::ostringstream oss;

    MockValue mockValue; // Assuming Value is a class and we need to mock it

    MockExifData mockMetadata; // Assuming ExifData is a class and we need to mock it



    CanonMakerNoteTest_926() {}

    ~CanonMakerNoteTest_926() override {}



    void SetUp() override {

        oss.str("");

        oss.clear();

    }



    void TearDown() override {}

};



TEST_F(CanonMakerNoteTest_926, TagListFlReturnsConstant_926) {

    auto tagList = CanonMakerNote::tagListFl();

    EXPECT_TRUE(tagList != nullptr); // Assuming tagInfoFl_ is a non-null pointer

}



TEST_F(CanonMakerNoteTest_926, PrintFiFileNumberNormalOperation_926) {

    CanonMakerNote::printFiFileNumber(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintFocalLengthNormalOperation_926) {

    CanonMakerNote::printFocalLength(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, Print0x0008NormalOperation_926) {

    CanonMakerNote::print0x0008(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, Print0x000ANormalOperation_926) {

    CanonMakerNote::print0x000a(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, Print0x000CNormalOperation_926) {

    CanonMakerNote::print0x000c(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintCs0x0002NormalOperation_926) {

    CanonMakerNote::printCs0x0002(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintCsLensTypeNormalOperation_926) {

    CanonMakerNote::printCsLensType(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintCsLensNormalOperation_926) {

    CanonMakerNote::printCsLens(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintLe0x0000NormalOperation_926) {

    CanonMakerNote::printLe0x0000(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0001NormalOperation_926) {

    CanonMakerNote::printSi0x0001(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0002NormalOperation_926) {

    CanonMakerNote::printSi0x0002(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0003NormalOperation_926) {

    CanonMakerNote::printSi0x0003(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0009NormalOperation_926) {

    CanonMakerNote::printSi0x0009(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x000CNormalOperation_926) {

    CanonMakerNote::printSi0x000c(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x000DNormalOperation_926) {

    CanonMakerNote::printSi0x000d(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x000ENormalOperation_926) {

    CanonMakerNote::printSi0x000e(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0013NormalOperation_926) {

    CanonMakerNote::printSi0x0013(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0015NormalOperation_926) {

    CanonMakerNote::printSi0x0015(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0016NormalOperation_926) {

    CanonMakerNote::printSi0x0016(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0017NormalOperation_926) {

    CanonMakerNote::printSi0x0017(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintSi0x0018NormalOperation_926) {

    CanonMakerNote::printSi0x0018(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}



TEST_F(CanonMakerNoteTest_926, PrintFiFocusDistanceNormalOperation_926) {

    CanonMakerNote::printFiFocusDistance(oss, mockValue, nullptr);

    EXPECT_FALSE(oss.str().empty()); // Assuming the function outputs something

}
