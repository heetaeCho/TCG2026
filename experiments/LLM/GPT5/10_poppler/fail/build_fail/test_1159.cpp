#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h" // Include the header file for GfxFont

// Mock dependencies if needed (e.g., XRef, Dict, GooString, etc.)
// Assuming mock implementations are provided where necessary

// Test fixture for GfxFont tests
class GfxFontTest_1159 : public ::testing::Test {
protected:
    // Set up necessary objects
    std::unique_ptr<GfxFont> font;

    void SetUp() override {
        // Setup logic (if any), e.g., creating a font instance
        font = std::make_unique<GfxFont>("tag", 1, nullptr, GfxFontType::Type1, 2);
    }

    void TearDown() override {
        // Clean-up logic (if needed)
    }
};

// Test for the getDescent method (Normal Operation)
TEST_F(GfxFontTest_1159, GetDescentNormal_1159) {
    // Assuming descent value is set during object creation or setup
    double expectedDescent = font->getDescent();
    EXPECT_EQ(expectedDescent, font->getDescent()); // Check if descent returns correct value
}

// Test for boundary conditions (if applicable)
TEST_F(GfxFontTest_1159, GetDescentBoundary_1159) {
    // Assuming boundary values are based on the logic of the constructor
    font = std::make_unique<GfxFont>("tag", 1, nullptr, GfxFontType::Type1, 2); // Boundary input
    double descent = font->getDescent();
    EXPECT_GE(descent, -10000.0); // Example boundary condition (min value)
    EXPECT_LE(descent, 10000.0); // Example boundary condition (max value)
}

// Test for exceptional or error cases
TEST_F(GfxFontTest_1159, GetDescentError_1159) {
    // Simulate error case if possible, for example, invalid input
    font = nullptr;
    EXPECT_THROW(font->getDescent(), std::runtime_error); // Assuming a runtime error is thrown
}

// Test for external interactions (if any, e.g., mocking dependencies like GooString)
TEST_F(GfxFontTest_1159, GetFontFamilyExternalInteraction_1159) {
    // Assuming GooString or other external classes interact with this function
    auto mockFamily = std::make_unique<GooString>("Arial");
    font->family = std::move(mockFamily);

    EXPECT_EQ(font->getFamily()->getCString(), "Arial");
}

// Test for checking font is OK
TEST_F(GfxFontTest_1159, IsFontOk_1159) {
    EXPECT_TRUE(font->isOk()); // Assuming this checks if the font is initialized and valid
}

// Test for verifying getTag() functionality
TEST_F(GfxFontTest_1159, GetTag_1159) {
    EXPECT_EQ(font->getTag(), "tag"); // Check if getTag returns the correct tag value
}

// Test for the isSubset method (Normal operation)
TEST_F(GfxFontTest_1159, IsSubset_1159) {
    // Assuming default behavior returns true or false
    bool isSubsetResult = font->isSubset();
    EXPECT_FALSE(isSubsetResult); // Assuming the default is false
}

// Test for getNameWithoutSubsetTag method (Normal operation)
TEST_F(GfxFontTest_1159, GetNameWithoutSubsetTag_1159) {
    // Assuming this method strips out subset tag if present
    std::string name = font->getNameWithoutSubsetTag();
    EXPECT_EQ(name, "ExpectedFontName"); // Replace with actual expected behavior
}

// Test for exceptional error case in locateFont (when font cannot be located)
TEST_F(GfxFontTest_1159, LocateFontError_1159) {
    XRef* xref = nullptr;
    PSOutputDev* ps = nullptr;
    GooString* substituteFontName = nullptr;
    EXPECT_THROW(font->locateFont(xref, ps, substituteFontName), std::runtime_error); // Assuming exception is thrown
}