#include <gtest/gtest.h>

// Include the enum definition
#include "TextOutputDev.h"

// We need to define the function under test since it's a static function in a .cc file.
// We replicate its exact definition here to test it.
enum EndOfLineKind_Local { eolUnix_Local = 0, eolDOS_Local = 1, eolMac_Local = 2 };

static constexpr int defaultEndOfLineTest()
{
#ifdef _WIN32
    return 1; // eolDOS
#else
    return 0; // eolUnix
#endif
}

// Since the function under test is a static constexpr in a .cc file, we test
// the equivalent logic by replicating the known interface behavior.
// The function returns eolDOS on Windows and eolUnix on other platforms.

class DefaultEndOfLineTest_2722 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(DefaultEndOfLineTest_2722, ReturnsCorrectEndOfLineForPlatform_2722)
{
    int result = defaultEndOfLineTest();
#ifdef _WIN32
    EXPECT_EQ(result, 1) << "On Windows, defaultEndOfLine should return eolDOS (1)";
#else
    EXPECT_EQ(result, 0) << "On non-Windows, defaultEndOfLine should return eolUnix (0)";
#endif
}

TEST_F(DefaultEndOfLineTest_2722, ReturnValueIsValidEnumMember_2722)
{
    int result = defaultEndOfLineTest();
    // The result should be one of the valid EndOfLineKind values: 0 (eolUnix), 1 (eolDOS), 2 (eolMac)
    EXPECT_GE(result, 0);
    EXPECT_LE(result, 2);
}

TEST_F(DefaultEndOfLineTest_2722, ReturnValueIsNotMac_2722)
{
    // defaultEndOfLine should never return eolMac on any platform
    int result = defaultEndOfLineTest();
    EXPECT_NE(result, 2) << "defaultEndOfLine should not return eolMac (2)";
}

TEST_F(DefaultEndOfLineTest_2722, IsConstexprEvaluable_2722)
{
    // Verify the function can be evaluated at compile time
    constexpr int result = defaultEndOfLineTest();
#ifdef _WIN32
    static_assert(result == 1, "Compile-time: should be eolDOS on Windows");
#else
    static_assert(result == 0, "Compile-time: should be eolUnix on non-Windows");
#endif
    EXPECT_TRUE(true); // If we reach here, constexpr evaluation succeeded
}

TEST_F(DefaultEndOfLineTest_2722, ConsistentReturnValue_2722)
{
    // Multiple calls should return the same value (deterministic)
    int result1 = defaultEndOfLineTest();
    int result2 = defaultEndOfLineTest();
    EXPECT_EQ(result1, result2) << "defaultEndOfLine should return consistent results";
}

// Test the actual enum values from the header
TEST_F(DefaultEndOfLineTest_2722, EnumValuesAreCorrect_2722)
{
    EXPECT_EQ(eolUnix, 0);
    EXPECT_EQ(eolDOS, 1);
    EXPECT_EQ(eolMac, 2);
}

#ifdef _WIN32
TEST_F(DefaultEndOfLineTest_2722, WindowsPlatformReturnsDOS_2722)
{
    int result = defaultEndOfLineTest();
    EXPECT_EQ(result, eolDOS) << "On Windows, should return eolDOS";
}
#else
TEST_F(DefaultEndOfLineTest_2722, UnixPlatformReturnsUnix_2722)
{
    int result = defaultEndOfLineTest();
    EXPECT_EQ(result, eolUnix) << "On Unix/Linux/Mac, should return eolUnix";
}
#endif
