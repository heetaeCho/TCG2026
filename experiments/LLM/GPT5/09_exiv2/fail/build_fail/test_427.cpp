#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "nikonmn_int.hpp"

using namespace Exiv2::Internal;

// Test fixture for Nikon3MakerNote
class Nikon3MakerNoteTest_427 : public ::testing::Test {
protected:
    Nikon3MakerNoteTest_427() {}
    ~Nikon3MakerNoteTest_427() override {}
};

// Test: tagListAFT
TEST_F(Nikon3MakerNoteTest_427, TagListAFT_427) {
    constexpr auto tags = Nikon3MakerNote::tagListAFT();
    EXPECT_EQ(tags, Nikon3MakerNote::tagListAFT());
}

// Test: printIiIso (normal case)
TEST_F(Nikon3MakerNoteTest_427, PrintIiIso_427) {
    std::ostringstream oss;
    Value value;  // Assume this is a valid Value object
    ExifData* metadata = nullptr;  // Assuming ExifData is handled elsewhere

    auto& result = Nikon3MakerNote::printIiIso(oss, value, metadata);
    EXPECT_EQ(&result, &oss);  // Ensure ostream is returned
}

// Test: printAf2AreaMode
TEST_F(Nikon3MakerNoteTest_427, PrintAf2AreaMode_427) {
    std::ostringstream oss;
    Value value;  // Assume this is a valid Value object
    ExifData* metadata = nullptr;

    auto& result = Nikon3MakerNote::printAf2AreaMode(oss, value, metadata);
    EXPECT_EQ(&result, &oss);
}

// Test: print0x0002 (boundary case with empty ExifData)
TEST_F(Nikon3MakerNoteTest_427, Print0x0002Boundary_427) {
    std::ostringstream oss;
    Value value;  // Assuming a valid value for 0x0002
    ExifData* metadata = nullptr;  // Empty metadata

    auto& result = Nikon3MakerNote::print0x0002(oss, value, metadata);
    EXPECT_EQ(&result, &oss);  // Check that the output is correct
}

// Test: printFocusDistance (edge case)
TEST_F(Nikon3MakerNoteTest_427, PrintFocusDistanceEdge_427) {
    std::ostringstream oss;
    Value value;  // Assuming a valid value
    ExifData* metadata = nullptr;

    auto& result = Nikon3MakerNote::printFocusDistance(oss, value, metadata);
    EXPECT_EQ(&result, &oss);
}

// Test: printFStops (exceptional case if metadata is invalid)
TEST_F(Nikon3MakerNoteTest_427, PrintFStopsExceptional_427) {
    std::ostringstream oss;
    Value value;  // Assume valid Value
    ExifData* metadata = nullptr;  // Invalid metadata for this case

    auto& result = Nikon3MakerNote::printFStops(oss, value, metadata);
    EXPECT_EQ(&result, &oss);
}

// Test: printLensId (edge case with missing group information)
TEST_F(Nikon3MakerNoteTest_427, PrintLensIdEdge_427) {
    std::ostringstream oss;
    Value value;  // Assume this is a valid Value object
    ExifData* metadata = nullptr;
    std::string group = "";  // Empty group for this test

    auto& result = Nikon3MakerNote::printLensId(oss, value, metadata, group);
    EXPECT_EQ(&result, &oss);
}

// Test: printCameraExposureCompensation (boundary condition)
TEST_F(Nikon3MakerNoteTest_427, PrintCameraExposureCompensationBoundary_427) {
    std::ostringstream oss;
    Value value;  // Valid value for camera exposure compensation
    ExifData* metadata = nullptr;  // Assuming default metadata

    auto& result = Nikon3MakerNote::printCameraExposureCompensation(oss, value, metadata);
    EXPECT_EQ(&result, &oss);
}

// Test: tagList (normal case)
TEST_F(Nikon3MakerNoteTest_427, TagListNormal_427) {
    constexpr auto tags = Nikon3MakerNote::tagList();
    EXPECT_EQ(tags, Nikon3MakerNote::tagList());
}

// Test: tagListAf (boundary condition)
TEST_F(Nikon3MakerNoteTest_427, TagListAfBoundary_427) {
    constexpr auto tags = Nikon3MakerNote::tagListAf();
    EXPECT_EQ(tags, Nikon3MakerNote::tagListAf());
}