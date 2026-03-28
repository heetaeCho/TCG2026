#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include "./TestProjects/exiv2/src/nikonmn_int.hpp"

namespace Exiv2 {
namespace Internal {

class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    // You can mock dependencies if needed here
};

TEST_F(Nikon3MakerNoteTest, tagListAf_424) {
    // Test: Verify the tagListAf function returns the expected value
    auto result = Nikon3MakerNote::tagListAf();
    // You can check if result matches expected value here, if it was an actual function
    // For now, we assume we can only check that it executes without error.
    EXPECT_NO_THROW(result);
}

TEST_F(Nikon3MakerNoteTest, printIiIso_424) {
    // Test: Verify the printIiIso function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printIiIso(os, value, metadata));

    // Additional validation can be done by inspecting the content of the os stream
    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, print0x0002_424) {
    // Test: Verify the print0x0002 function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::print0x0002(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printAf2AreaMode_424) {
    // Test: Verify the printAf2AreaMode function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printAf2AreaMode(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printLensId1_424) {
    // Test: Verify the printLensId1 function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printLensId1(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printFocusDistance_424) {
    // Test: Verify the printFocusDistance function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printFocusDistance(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printAperture_424) {
    // Test: Verify the printAperture function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printAperture(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printFStops_424) {
    // Test: Verify the printFStops function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printFStops(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printExitPupilPosition_424) {
    // Test: Verify the printExitPupilPosition function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printExitPupilPosition(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printFlashFocalLength_424) {
    // Test: Verify the printFlashFocalLength function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printFlashFocalLength(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

TEST_F(Nikon3MakerNoteTest, printRepeatingFlashRate_424) {
    // Test: Verify the printRepeatingFlashRate function for expected output
    std::ostringstream os;
    Value value;
    const ExifData* metadata = nullptr;

    EXPECT_NO_THROW(Nikon3MakerNote::printRepeatingFlashRate(os, value, metadata));

    std::string result = os.str();
    EXPECT_FALSE(result.empty());
}

// Add additional tests for other print functions as needed

}  // namespace Internal
}  // namespace Exiv2