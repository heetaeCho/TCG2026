#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cmath>
#include <iostream>

namespace Exiv2 { namespace Internal {

// Mocking the ExifData type as it is passed as a parameter in the function.
class MockExifData {};

class Nikon3MakerNoteTest : public ::testing::Test {
protected:
    Nikon3MakerNote makerNote;
};

// TEST_ID is 459
TEST_F(Nikon3MakerNoteTest, printIiIso_NormalValue_459) {
    // Normal test case for printIiIso
    std::ostringstream oss;
    Value value(10);  // Example value
    ExifData exifData;  // Not used in the function, but needed as a parameter

    makerNote.printIiIso(oss, value, &exifData);

    EXPECT_EQ(oss.str(), "200");  // Expected value based on the formula
}

// TEST_ID is 460
TEST_F(Nikon3MakerNoteTest, printIiIso_LowestValue_460) {
    // Test case for lowest possible value
    std::ostringstream oss;
    Value value(-10);  // A value well below 0
    ExifData exifData;

    makerNote.printIiIso(oss, value, &exifData);

    EXPECT_EQ(oss.str(), "6");  // Expected value based on the formula for low value
}

// TEST_ID is 461
TEST_F(Nikon3MakerNoteTest, printIiIso_HighestValue_461) {
    // Test case for the highest possible value
    std::ostringstream oss;
    Value value(1000);  // A very high value
    ExifData exifData;

    makerNote.printIiIso(oss, value, &exifData);

    // Expected value is based on the formula 100.0 * exp2((value / 12.0) - 5)
    // Let's calculate it manually: 100.0 * exp2((1000 / 12.0) - 5)
    double expected = std::lround(100.0 * std::exp2((1000 / 12.0) - 5));
    EXPECT_EQ(oss.str(), std::to_string(expected));  // Expected value should match
}

// TEST_ID is 462
TEST_F(Nikon3MakerNoteTest, printIiIso_ZeroValue_462) {
    // Test case for value = 0
    std::ostringstream oss;
    Value value(0);  // Value at zero
    ExifData exifData;

    makerNote.printIiIso(oss, value, &exifData);

    EXPECT_EQ(oss.str(), "32");  // Expected value based on the formula for value = 0
}

// TEST_ID is 463
TEST_F(Nikon3MakerNoteTest, printIiIso_InvalidValueType_463) {
    // Test case for invalid value type (non-integral value for example)
    std::ostringstream oss;
    Value value("string");  // Invalid value type
    ExifData exifData;

    try {
        makerNote.printIiIso(oss, value, &exifData);
        FAIL() << "Expected std::invalid_argument exception";
    } catch (const std::invalid_argument& e) {
        EXPECT_STREQ(e.what(), "Invalid value type for printIiIso");
    } catch (...) {
        FAIL() << "Expected std::invalid_argument exception";
    }
}

} }