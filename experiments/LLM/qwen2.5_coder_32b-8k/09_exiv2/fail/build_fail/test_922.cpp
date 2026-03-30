#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "canonmn_int.hpp"

#include <sstream>



using namespace Exiv2::Internal;



class CanonMakerNoteTest_922 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(CanonMakerNoteTest_922, TagListFcd2_ReturnsConstantValue_922) {

    auto result = CanonMakerNote::tagListFcd2();

    EXPECT_NE(result, nullptr);

}



TEST_F(CanonMakerNoteTest_922, PrintFiFileNumber_ValidInput_OutputStreamModified_922) {

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed

    ExifData mockMetadata; // Assuming ExifData is a type that can be default constructed



    auto& result = CanonMakerNote::printFiFileNumber(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os); // Check if the same stream is returned

    EXPECT_FALSE(os.str().empty()); // Check if the output stream is modified

}



TEST_F(CanonMakerNoteTest_922, PrintFocalLength_ValidInput_OutputStreamModified_922) {

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed

    ExifData mockMetadata; // Assuming ExifData is a type that can be default constructed



    auto& result = CanonMakerNote::printFocalLength(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os); // Check if the same stream is returned

    EXPECT_FALSE(os.str().empty()); // Check if the output stream is modified

}



TEST_F(CanonMakerNoteTest_922, Print0x0008_ValidInput_OutputStreamModified_922) {

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed



    auto& result = CanonMakerNote::print0x0008(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os); // Check if the same stream is returned

    EXPECT_FALSE(os.str().empty()); // Check if the output stream is modified

}



TEST_F(CanonMakerNoteTest_922, PrintCsLensType_ValidInput_OutputStreamModified_922) {

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed

    ExifData mockMetadata; // Assuming ExifData is a type that can be default constructed



    auto& result = CanonMakerNote::printCsLensType(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os); // Check if the same stream is returned

    EXPECT_FALSE(os.str().empty()); // Check if the output stream is modified

}



TEST_F(CanonMakerNoteTest_922, PrintSi0x000e_ValidInput_OutputStreamModified_922) {

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed

    ExifData mockMetadata; // Assuming ExifData is a type that can be default constructed



    auto& result = CanonMakerNote::printSi0x000e(os, mockValue, &mockMetadata);

    EXPECT_EQ(&result, &os); // Check if the same stream is returned

    EXPECT_FALSE(os.str().empty()); // Check if the output stream is modified

}



TEST_F(CanonMakerNoteTest_922, PrintFiFocusDistance_ValidInput_OutputStreamModified_922) {

    std::ostringstream os;

    Value mockValue; // Assuming Value is a type that can be default constructed



    auto& result = CanonMakerNote::printFiFocusDistance(os, mockValue, nullptr);

    EXPECT_EQ(&result, &os); // Check if the same stream is returned

    EXPECT_FALSE(os.str().empty()); // Check if the output stream is modified

}
