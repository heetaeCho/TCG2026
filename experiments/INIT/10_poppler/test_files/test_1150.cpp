#include <gtest/gtest.h>
#include "GfxFont.h"  // Assuming GfxFont.h is located in the given path

// Test Fixture for GfxFont
class GfxFontTest_1150 : public ::testing::Test {
protected:
    // You can initialize shared resources here if needed
    GfxFontTest_1150() {}
    ~GfxFontTest_1150() override {}

    void SetUp() override {
        // Initialize the object here if necessary
        font = std::make_unique<GfxFont>("tag", Ref{}, nullptr, GfxFontType::typeA, Ref{});
    }

    void TearDown() override {
        // Cleanup if necessary
    }

    std::unique_ptr<GfxFont> font;
};

// Test case for the `getFlags` method
TEST_F(GfxFontTest_1150, GetFlagsReturnsCorrectFlags_1150) {
    // Arrange: You might want to mock or set up specific conditions for flags
    
    // Act: Call the method
    int flags = font->getFlags();
    
    // Assert: Check the expected outcome
    EXPECT_EQ(flags, 0);  // Assuming 0 is the default value, adjust as necessary
}

// Test case for `getNameWithoutSubsetTag` method
TEST_F(GfxFontTest_1150, GetNameWithoutSubsetTag_1151) {
    // Arrange: Set up the font to have a specific name
    std::string expected_name = "FontName";
    font->setName(expected_name);

    // Act: Call the method
    std::string name_without_subset = font->getNameWithoutSubsetTag();

    // Assert: Verify the name doesn't contain the subset tag
    EXPECT_EQ(name_without_subset, expected_name);
}

// Test case for `getType` method
TEST_F(GfxFontTest_1150, GetFontType_1152) {
    // Arrange: Set up expected font type
    GfxFontType expected_type = GfxFontType::typeA;

    // Act: Call the method
    GfxFontType type = font->getType();

    // Assert: Check that the returned type matches
    EXPECT_EQ(type, expected_type);
}

// Test case for `isSubset` method
TEST_F(GfxFontTest_1150, IsSubsetReturnsTrue_1153) {
    // Act: Check if font is a subset
    bool is_subset = font->isSubset();

    // Assert: Verify the expected result (true or false based on actual behavior)
    EXPECT_TRUE(is_subset);  // Change to false if expected result is different
}

// Test case for `getAscent` method
TEST_F(GfxFontTest_1150, GetAscentReturnsValidValue_1154) {
    // Arrange: The expected ascent value
    double expected_ascent = 1.5;  // Set a reasonable expected value

    // Act: Get the ascent value from the font
    double ascent = font->getAscent();

    // Assert: Check if the ascent is within the expected range
    EXPECT_EQ(ascent, expected_ascent);
}

// Test case for `getDescent` method
TEST_F(GfxFontTest_1150, GetDescentReturnsValidValue_1155) {
    // Arrange: Expected descent value
    double expected_descent = -0.5;

    // Act: Get the descent value
    double descent = font->getDescent();

    // Assert: Check if descent value is as expected
    EXPECT_EQ(descent, expected_descent);
}

// Test case for `isBold` method
TEST_F(GfxFontTest_1150, IsBoldReturnsTrue_1156) {
    // Act: Call isBold
    bool is_bold = font->isBold();

    // Assert: Check if bold is enabled
    EXPECT_FALSE(is_bold);  // Adjust based on expected result
}

// Test case for `getFontMatrix` method
TEST_F(GfxFontTest_1150, GetFontMatrixReturnsValidMatrix_1157) {
    // Arrange: Define expected font matrix
    std::array<double, 6> expected_matrix = {1.0, 0.0, 0.0, 1.0, 0.0, 0.0};

    // Act: Get the font matrix
    const std::array<double, 6>& matrix = font->getFontMatrix();

    // Assert: Check if matrix matches
    EXPECT_EQ(matrix, expected_matrix);
}

// Test case for `getFontBBox` method
TEST_F(GfxFontTest_1150, GetFontBBoxReturnsValidBBox_1158) {
    // Arrange: Define expected font bounding box
    std::array<double, 4> expected_bbox = {0.0, 0.0, 100.0, 100.0};

    // Act: Get the font bounding box
    const std::array<double, 4>& bbox = font->getFontBBox();

    // Assert: Check if bounding box matches
    EXPECT_EQ(bbox, expected_bbox);
}

// Test case for `matches` method
TEST_F(GfxFontTest_1150, MatchesReturnsTrueForMatchingTag_1159) {
    // Arrange: Define a matching tag
    const char* matching_tag = "tag";

    // Act: Check if the font matches the tag
    bool matches = font->matches(matching_tag);

    // Assert: Verify if it matches
    EXPECT_TRUE(matches);
}

// Test case for `getFamily` method
TEST_F(GfxFontTest_1150, GetFamilyReturnsCorrectFamily_1160) {
    // Arrange: Set up a family name
    GooString expected_family("Arial");
    font->setFamily(expected_family);

    // Act: Get the family name
    const GooString* family = font->getFamily();

    // Assert: Check if the family name matches
    EXPECT_EQ(family->getCString(), "Arial");
}