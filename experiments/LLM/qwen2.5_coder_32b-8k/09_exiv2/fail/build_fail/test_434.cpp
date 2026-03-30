#include <gtest/gtest.h>

#include <gmock/gmock-matchers.h>

#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

#include <sstream>

#include <memory>



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class Nikon3MakerNoteTest_434 : public ::testing::Test {

protected:

    Nikon3MakerNoteTest_434() {}



    std::ostringstream oss;

    Value mockValue; // Assuming Value is some type that can be default constructed

    ExifData mockMetadata; // Assuming ExifData is some type that can be default constructed



    void TearDown() override {

        oss.str("");

        oss.clear();

    }

};



TEST_F(Nikon3MakerNoteTest_434, TagListFl7_ReturnsConstexprArray_434) {

    auto result = Nikon3MakerNote::tagListFl7();

    EXPECT_TRUE(result != nullptr);

}



TEST_F(Nikon3MakerNoteTest_434, PrintIiIso_NormalOperation_434) {

    Nikon3MakerNote::printIiIso(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, Print0x0002_NormalOperation_434) {

    Nikon3MakerNote::print0x0002(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintAf2AreaMode_NormalOperation_434) {

    Nikon3MakerNote::printAf2AreaMode(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, Print0x0089_NormalOperationWithMetadata_434) {

    Nikon3MakerNote::print0x0089(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintLensId_NormalOperationWithGroup_434) {

    Nikon3MakerNote::printLensId(oss, mockValue, &mockMetadata, "SampleGroup");

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintAperture_NormalOperation_434) {

    Nikon3MakerNote::printAperture(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintFocal_NormalOperation_434) {

    Nikon3MakerNote::printFocal(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintFocusDistance_NormalOperation_434) {

    Nikon3MakerNote::printFocusDistance(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintAfPointsInFocus_NormalOperationWithMetadata_434) {

    Nikon3MakerNote::printAfPointsInFocus(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData1Fl7_NormalOperationWithMetadata_434) {

    Nikon3MakerNote::printExternalFlashData1Fl7(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintFlashGroupAControlData_NormalOperationWithMetadata_434) {

    Nikon3MakerNote::printFlashGroupAControlData(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintExternalFlashData3_NormalOperationWithMetadata_434) {

    Nikon3MakerNote::printExternalFlashData3(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}



TEST_F(Nikon3MakerNoteTest_434, PrintTimeZone_NormalOperation_434) {

    Nikon3MakerNote::printTimeZone(oss, mockValue, &mockMetadata);

    EXPECT_FALSE(oss.str().empty()); // Assuming it prints something

}
