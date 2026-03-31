#include <gtest/gtest.h>
#include <string>

// Forward declaration matching the interface from the partial code
namespace Exiv2 {
namespace Internal {
std::string indent(size_t i);
}
}

// Test fixture
class ImageIntTest_114 : public ::testing::Test {
protected:
};

// Normal operation tests

TEST_F(ImageIntTest_114, IndentZeroReturnsEmptyString_114) {
    std::string result = Exiv2::Internal::indent(0);
    EXPECT_EQ(result, "");
    EXPECT_EQ(result.size(), 0u);
}

TEST_F(ImageIntTest_114, IndentOneReturnsTwoSpaces_114) {
    std::string result = Exiv2::Internal::indent(1);
    EXPECT_EQ(result, "  ");
    EXPECT_EQ(result.size(), 2u);
}

TEST_F(ImageIntTest_114, IndentTwoReturnsFourSpaces_114) {
    std::string result = Exiv2::Internal::indent(2);
    EXPECT_EQ(result, "    ");
    EXPECT_EQ(result.size(), 4u);
}

TEST_F(ImageIntTest_114, IndentThreeReturnsSixSpaces_114) {
    std::string result = Exiv2::Internal::indent(3);
    EXPECT_EQ(result, "      ");
    EXPECT_EQ(result.size(), 6u);
}

TEST_F(ImageIntTest_114, IndentFiveReturnsTenSpaces_114) {
    std::string result = Exiv2::Internal::indent(5);
    EXPECT_EQ(result, "          ");
    EXPECT_EQ(result.size(), 10u);
}

TEST_F(ImageIntTest_114, IndentTenReturnsTwentySpaces_114) {
    std::string result = Exiv2::Internal::indent(10);
    EXPECT_EQ(result.size(), 20u);
    // Verify all characters are spaces
    for (char c : result) {
        EXPECT_EQ(c, ' ');
    }
}

// Verify the result length is always 2*i
TEST_F(ImageIntTest_114, IndentLengthIsTwiceInput_114) {
    for (size_t i = 0; i < 20; ++i) {
        std::string result = Exiv2::Internal::indent(i);
        EXPECT_EQ(result.size(), 2 * i) << "Failed for i=" << i;
    }
}

// Verify result contains only spaces
TEST_F(ImageIntTest_114, IndentContainsOnlySpaces_114) {
    for (size_t i = 0; i < 15; ++i) {
        std::string result = Exiv2::Internal::indent(i);
        for (size_t j = 0; j < result.size(); ++j) {
            EXPECT_EQ(result[j], ' ') << "Non-space character at position " << j << " for indent(" << i << ")";
        }
    }
}

// Boundary: large value
TEST_F(ImageIntTest_114, IndentLargeValueProducesCorrectLength_114) {
    size_t large = 100;
    std::string result = Exiv2::Internal::indent(large);
    EXPECT_EQ(result.size(), 200u);
    for (char c : result) {
        EXPECT_EQ(c, ' ');
    }
}

// Verify that indent returns a new string each time (no aliasing issues)
TEST_F(ImageIntTest_114, IndentReturnsIndependentStrings_114) {
    std::string a = Exiv2::Internal::indent(3);
    std::string b = Exiv2::Internal::indent(3);
    EXPECT_EQ(a, b);
    // Modifying one should not affect the other
    a[0] = 'x';
    EXPECT_NE(a, b);
}

// Verify that consecutive indent levels differ by exactly 2 spaces
TEST_F(ImageIntTest_114, IndentConsecutiveLevelsDifferByTwoSpaces_114) {
    for (size_t i = 0; i < 10; ++i) {
        std::string current = Exiv2::Internal::indent(i);
        std::string next = Exiv2::Internal::indent(i + 1);
        EXPECT_EQ(next.size() - current.size(), 2u) << "Failed between levels " << i << " and " << (i + 1);
    }
}
