#include <gtest/gtest.h>
#include <string>

// Include the necessary header for KeyLocation enum
#include "CertificateInfo.h"

// Since locationToString is a static function in a .cc file, we need to
// re-declare it here for testing purposes. We include the actual source
// or replicate the declaration. Since we can't include the .cc file directly
// in a normal build, we'll use a workaround.

// We need to make the static function accessible. One approach is to
// include the .cc file directly (which makes its static functions available
// in this translation unit).
#include "pdfsig.cc"

using namespace std;

class LocationToStringTest_2685 : public ::testing::Test {
protected:
    // No setup needed
};

// Test that KeyLocation::Unknown returns an empty string
TEST_F(LocationToStringTest_2685, UnknownReturnsEmptyString_2685)
{
    std::string result = locationToString(KeyLocation::Unknown);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result, std::string{});
}

// Test that KeyLocation::Other returns "(Other)"
TEST_F(LocationToStringTest_2685, OtherReturnsOtherString_2685)
{
    std::string result = locationToString(KeyLocation::Other);
    EXPECT_EQ(result, "(Other)");
}

// Test that KeyLocation::Computer returns "(Computer)"
TEST_F(LocationToStringTest_2685, ComputerReturnsComputerString_2685)
{
    std::string result = locationToString(KeyLocation::Computer);
    EXPECT_EQ(result, "(Computer)");
}

// Test that KeyLocation::HardwareToken returns "(Hardware Token)"
TEST_F(LocationToStringTest_2685, HardwareTokenReturnsHardwareTokenString_2685)
{
    std::string result = locationToString(KeyLocation::HardwareToken);
    EXPECT_EQ(result, "(Hardware Token)");
}

// Test that an invalid/out-of-range enum value returns an empty string
// (falls through the switch to the default return)
TEST_F(LocationToStringTest_2685, InvalidEnumValueReturnsEmptyString_2685)
{
    // Cast an integer that doesn't correspond to any valid enum value
    KeyLocation invalidLocation = static_cast<KeyLocation>(99);
    std::string result = locationToString(invalidLocation);
    EXPECT_TRUE(result.empty());
    EXPECT_EQ(result, std::string{});
}

// Test with another out-of-range negative value
TEST_F(LocationToStringTest_2685, NegativeEnumValueReturnsEmptyString_2685)
{
    KeyLocation invalidLocation = static_cast<KeyLocation>(-1);
    std::string result = locationToString(invalidLocation);
    EXPECT_TRUE(result.empty());
}

// Test that the result for Known values is non-empty
TEST_F(LocationToStringTest_2685, KnownValuesReturnNonEmptyStrings_2685)
{
    EXPECT_FALSE(locationToString(KeyLocation::Other).empty());
    EXPECT_FALSE(locationToString(KeyLocation::Computer).empty());
    EXPECT_FALSE(locationToString(KeyLocation::HardwareToken).empty());
}

// Test that each known enum value produces a distinct string
TEST_F(LocationToStringTest_2685, EachKnownValueProducesDistinctString_2685)
{
    std::string other = locationToString(KeyLocation::Other);
    std::string computer = locationToString(KeyLocation::Computer);
    std::string hardwareToken = locationToString(KeyLocation::HardwareToken);

    EXPECT_NE(other, computer);
    EXPECT_NE(other, hardwareToken);
    EXPECT_NE(computer, hardwareToken);
}

// Boundary: test with enum value just beyond the last valid one (4)
TEST_F(LocationToStringTest_2685, BoundaryValueJustBeyondLastEnum_2685)
{
    KeyLocation boundary = static_cast<KeyLocation>(4);
    std::string result = locationToString(boundary);
    EXPECT_TRUE(result.empty());
}

// Boundary: test with enum value 0 which is Unknown
TEST_F(LocationToStringTest_2685, ZeroValueIsUnknown_2685)
{
    KeyLocation zero = static_cast<KeyLocation>(0);
    std::string result = locationToString(zero);
    EXPECT_TRUE(result.empty());
}
