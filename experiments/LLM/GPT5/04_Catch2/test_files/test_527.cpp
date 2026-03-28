// JsonUtils_indent_tests_527.cpp
#include <gtest/gtest.h>
#include <sstream>
#include <cstdint>

// Minimal declaration matching the provided interface
namespace Catch {
struct JsonUtils {
    static void indent(std::ostream& os, std::uint64_t level);
    // appendCommaNewline is declared in the header but not tested here,
    // because there is no observable behavior provided/implemented.
};
} // namespace Catch

using Catch::JsonUtils;

class JsonUtilsTest_527 : public ::testing::Test {
protected:
    std::ostringstream os;
};

// Normal operation: level = 0 should not write anything
TEST_F(JsonUtilsTest_527, IndentZero_NoOutput_527) {
    JsonUtils::indent(os, 0);
    EXPECT_EQ(os.str(), "");
}

// Normal operation: small positive level writes exactly that many spaces
TEST_F(JsonUtilsTest_527, IndentThree_WritesThreeSpaces_527) {
    JsonUtils::indent(os, 3);
    EXPECT_EQ(os.str(), "   ");
    // Also verify all characters are spaces
    for (char c : os.str()) {
        EXPECT_EQ(c, ' ');
    }
}

// Boundary-ish: ensure it appends and does not clobber existing content
TEST_F(JsonUtilsTest_527, IndentAppends_ToExistingContent_527) {
    os << "X";
    JsonUtils::indent(os, 4);
    EXPECT_EQ(os.str(), "X    ");
}

// Larger count (but reasonable for a unit test): verify length and contents
TEST_F(JsonUtilsTest_527, IndentLarge_WritesCorrectCount_527) {
    constexpr std::uint64_t kLevel = 100;
    JsonUtils::indent(os, kLevel);
    const std::string out = os.str();
    EXPECT_EQ(out.size(), static_cast<size_t>(kLevel));
    // Spot-check a few positions to ensure they are spaces
    ASSERT_FALSE(out.empty());
    EXPECT_EQ(out.front(), ' ');
    EXPECT_EQ(out.back(), ' ');
    EXPECT_EQ(out[kLevel / 2], ' ');
}

// Idempotence of output type: ensure only spaces are written (no newlines/tabs)
TEST_F(JsonUtilsTest_527, IndentOnlySpaces_NoOtherChars_527) {
    JsonUtils::indent(os, 10);
    const std::string out = os.str();
    for (char c : out) {
        EXPECT_EQ(c, ' ');
    }
}
