#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <ostream>
#include "sonymn_int.hpp"  // Include the header of the class to be tested

namespace Exiv2 {
namespace Internal {

class SonyMakerNoteTest_274 : public ::testing::Test {
protected:
    // Setup and teardown for each test case (if needed)
    void SetUp() override {
        // Code for setup (if necessary)
    }

    void TearDown() override {
        // Code for cleanup (if necessary)
    }
};

TEST_F(SonyMakerNoteTest_274, PrintWhiteBalanceFineTune_274) {
    std::ostream os(nullptr);
    Value value;  // Assuming Value is some object you can create
    ExifData* metadata = nullptr;

    // Test normal operation (verify behavior with valid inputs)
    EXPECT_NO_THROW({
        SonyMakerNote::printWhiteBalanceFineTune(os, value, metadata);
    });

    // Verify interactions with std::ostream if needed
}

TEST_F(SonyMakerNoteTest_274, PrintMultiBurstMode_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation (verify behavior with valid inputs)
    EXPECT_NO_THROW({
        SonyMakerNote::printMultiBurstMode(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintAutoHDRStd_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printAutoHDRStd(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintFocusMode2_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printFocusMode2(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintWBShiftABGM_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printWBShiftABGM(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintAFMode_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printAFMode(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintFocusMode3_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printFocusMode3(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintHighISONoiseReduction2_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printHighISONoiseReduction2(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc1CameraTemperature_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printSonyMisc1CameraTemperature(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintSony2FpFocusMode_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printSony2FpFocusMode(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc2bLensZoomPosition_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printSonyMisc2bLensZoomPosition(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cSequenceNumber_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printSonyMisc3cSequenceNumber(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, PrintSonyMisc3cModelReleaseYear_274) {
    std::ostream os(nullptr);
    Value value;
    ExifData* metadata = nullptr;

    // Test normal operation
    EXPECT_NO_THROW({
        SonyMakerNote::printSonyMisc3cModelReleaseYear(os, value, metadata);
    });
}

TEST_F(SonyMakerNoteTest_274, TagList_274) {
    // Boundary test for tagList method
    auto tags = SonyMakerNote::tagList();
    EXPECT_FALSE(tags.empty());  // Assuming tagList should return non-empty result
}

}  // namespace Internal
}  // namespace Exiv2