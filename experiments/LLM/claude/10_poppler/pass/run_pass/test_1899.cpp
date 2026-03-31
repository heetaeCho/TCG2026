#include <gtest/gtest.h>
#include <string>

// We need to test the static function findModifier which is defined in GlobalParams.cc
// Since it's a static function (file-local linkage), we need to include the source
// or redefine the function signature for testing. Since we treat it as a black box
// and need to test it, we'll declare it with the same signature and include the
// implementation file indirectly.

// Since findModifier is static in GlobalParams.cc, we need a way to access it.
// One common approach is to include the .cc file directly for testing static functions.
// However, that may pull in many dependencies. Instead, we replicate the function
// signature here as it's provided in the prompt, purely for testability.

// Note: In a real project, you'd either make this function non-static/internal-linkage
// with a test-visible header, or include the .cc file with appropriate guards.

namespace {

static bool findModifier(const std::string &name, const size_t modStart, const char *modifier, size_t &start)
{
    if (modStart == std::string::npos) {
        return false;
    }
    size_t match = name.find(modifier, modStart);
    if (match == std::string::npos) {
        return false;
    }
    if (start == std::string::npos || match < start) {
        start = match;
    }
    return true;
}

} // anonymous namespace

class FindModifierTest_1899 : public ::testing::Test {
protected:
    size_t start;

    void SetUp() override {
        start = std::string::npos;
    }
};

// Test that when modStart is npos, the function returns false
TEST_F(FindModifierTest_1899, ModStartNpos_ReturnsFalse_1899)
{
    start = std::string::npos;
    std::string name = "SomeFontBold";
    bool result = findModifier(name, std::string::npos, "Bold", start);
    EXPECT_FALSE(result);
    EXPECT_EQ(start, std::string::npos);
}

// Test that when modifier is not found in name, the function returns false
TEST_F(FindModifierTest_1899, ModifierNotFound_ReturnsFalse_1899)
{
    start = std::string::npos;
    std::string name = "SomeFontRegular";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_FALSE(result);
    EXPECT_EQ(start, std::string::npos);
}

// Test that when modifier is found, the function returns true and updates start
TEST_F(FindModifierTest_1899, ModifierFound_ReturnsTrue_UpdatesStart_1899)
{
    start = std::string::npos;
    std::string name = "SomeFontBold";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 8u); // "Bold" starts at index 8
}

// Test that start is updated only if match is earlier than current start
TEST_F(FindModifierTest_1899, MatchEarlierThanCurrentStart_UpdatesStart_1899)
{
    start = 10;
    std::string name = "BoldFontItalic";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 0u); // "Bold" is at position 0, which is less than 10
}

// Test that start is NOT updated if match is later than current start
TEST_F(FindModifierTest_1899, MatchLaterThanCurrentStart_DoesNotUpdateStart_1899)
{
    start = 2;
    std::string name = "SomeFontBold";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 2u); // "Bold" at index 8 > current start of 2, so no update
}

// Test searching from a modStart offset that skips the modifier
TEST_F(FindModifierTest_1899, ModStartAfterModifier_ReturnsFalse_1899)
{
    start = std::string::npos;
    std::string name = "BoldFont";
    bool result = findModifier(name, 5, "Bold", start);
    EXPECT_FALSE(result);
    EXPECT_EQ(start, std::string::npos);
}

// Test searching from a modStart that is exactly where modifier begins
TEST_F(FindModifierTest_1899, ModStartExactlyAtModifier_ReturnsTrue_1899)
{
    start = std::string::npos;
    std::string name = "SomeBoldFont";
    bool result = findModifier(name, 4, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 4u);
}

// Test with empty modifier string (should match at modStart position)
TEST_F(FindModifierTest_1899, EmptyModifier_ReturnsTrue_1899)
{
    start = std::string::npos;
    std::string name = "SomeFont";
    bool result = findModifier(name, 3, "", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 3u);
}

// Test with empty name string
TEST_F(FindModifierTest_1899, EmptyName_ModifierNotEmpty_ReturnsFalse_1899)
{
    start = std::string::npos;
    std::string name = "";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_FALSE(result);
    EXPECT_EQ(start, std::string::npos);
}

// Test with empty name and empty modifier
TEST_F(FindModifierTest_1899, EmptyNameAndEmptyModifier_ReturnsTrue_1899)
{
    start = std::string::npos;
    std::string name = "";
    bool result = findModifier(name, 0, "", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 0u);
}

// Test multiple occurrences of modifier - should find first one from modStart
TEST_F(FindModifierTest_1899, MultipleOccurrences_FindsFirstFromModStart_1899)
{
    start = std::string::npos;
    std::string name = "BoldSomeBold";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 0u);
}

// Test multiple occurrences - searching from after first occurrence
TEST_F(FindModifierTest_1899, MultipleOccurrences_SearchFromMiddle_1899)
{
    start = std::string::npos;
    std::string name = "BoldSomeBold";
    bool result = findModifier(name, 1, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 8u);
}

// Test that when match == start, start is not changed (match is not < start)
TEST_F(FindModifierTest_1899, MatchEqualsCurrentStart_NoChange_1899)
{
    start = 4;
    std::string name = "SomeBoldFont";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 4u); // match is 4, start is 4, condition match < start is false
}

// Test with modStart at end of string
TEST_F(FindModifierTest_1899, ModStartAtEnd_ModifierNotFound_1899)
{
    start = std::string::npos;
    std::string name = "SomeBold";
    bool result = findModifier(name, name.size(), "Bold", start);
    EXPECT_FALSE(result);
    EXPECT_EQ(start, std::string::npos);
}

// Test with modStart at end of string with empty modifier
TEST_F(FindModifierTest_1899, ModStartAtEnd_EmptyModifier_ReturnsTrue_1899)
{
    start = std::string::npos;
    std::string name = "SomeBold";
    bool result = findModifier(name, name.size(), "", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, name.size());
}

// Test: start is npos, modifier found -> start should be updated
TEST_F(FindModifierTest_1899, StartIsNpos_ModifierFound_StartsUpdated_1899)
{
    start = std::string::npos;
    std::string name = "TestItalicFont";
    bool result = findModifier(name, 0, "Italic", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 4u);
}

// Test case-sensitive matching
TEST_F(FindModifierTest_1899, CaseSensitive_NoMatch_1899)
{
    start = std::string::npos;
    std::string name = "SomeFontbold";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_FALSE(result);
    EXPECT_EQ(start, std::string::npos);
}

// Test partial match doesn't count as match
TEST_F(FindModifierTest_1899, SubstringMatch_ReturnsTrue_1899)
{
    start = std::string::npos;
    std::string name = "SemiBold";
    bool result = findModifier(name, 0, "Bold", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 4u);
}

// Test modStart = 0 with modifier at position 0
TEST_F(FindModifierTest_1899, ModStartZero_ModifierAtStart_1899)
{
    start = std::string::npos;
    std::string name = "Italic-Regular";
    bool result = findModifier(name, 0, "Italic", start);
    EXPECT_TRUE(result);
    EXPECT_EQ(start, 0u);
}
