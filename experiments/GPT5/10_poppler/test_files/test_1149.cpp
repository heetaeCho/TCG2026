#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "GfxFont.h"  // Include the actual header file

// Mock class if necessary (e.g., for dependencies)
class MockXRef : public XRef {
    // Mock methods if necessary
};

// Unit test class
class GfxFontTest_1149 : public ::testing::Test {
protected:
    GfxFontTest_1149() {
        // Set up any necessary resources for the tests
    }
};

// Test: getEmbeddedFontName - Normal Operation
TEST_F(GfxFontTest_1149, GetEmbeddedFontName_1149) {
    // Assuming embFontName is a GooString* that is not null
    GooString embFont("EmbeddedFontName");
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setEmbeddedFontName(&embFont);

    const GooString* result = gfxFont->getEmbeddedFontName();
    EXPECT_EQ(result->getString(), "EmbeddedFontName");
}

// Test: getEmbeddedFontName - Null Pointer
TEST_F(GfxFontTest_1149, GetEmbeddedFontName_Null_1149) {
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setEmbeddedFontName(nullptr);

    const GooString* result = gfxFont->getEmbeddedFontName();
    EXPECT_EQ(result, nullptr);
}

// Test: isSubset - Normal Operation
TEST_F(GfxFontTest_1149, IsSubset_1149) {
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    
    EXPECT_FALSE(gfxFont->isSubset());  // Assuming it returns false for this test
}

// Test: isSubset - Boundary Condition
TEST_F(GfxFontTest_1149, IsSubset_Empty_1149) {
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    // Test the scenario when isSubset should be true
    // Here you'd configure the font object accordingly.
    
    EXPECT_TRUE(gfxFont->isSubset());  // Adjust according to expected behavior
}

// Test: getFamily - Normal Operation
TEST_F(GfxFontTest_1149, GetFamily_1149) {
    GooString familyName("FamilyName");
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setFamily(&familyName);

    const GooString* result = gfxFont->getFamily();
    EXPECT_EQ(result->getString(), "FamilyName");
}

// Test: getFamily - Boundary Condition (empty family name)
TEST_F(GfxFontTest_1149, GetFamily_Empty_1149) {
    GooString familyName("");
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setFamily(&familyName);

    const GooString* result = gfxFont->getFamily();
    EXPECT_EQ(result->getString(), "");
}

// Test: isFixedWidth - Normal Operation
TEST_F(GfxFontTest_1149, IsFixedWidth_1149) {
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    
    EXPECT_FALSE(gfxFont->isFixedWidth());  // Assuming default is not fixed width
}

// Test: getFontMatrix - Normal Operation
TEST_F(GfxFontTest_1149, GetFontMatrix_1149) {
    std::array<double, 6> fontMatrix = { 1.0, 0.0, 0.0, 1.0, 0.0, 0.0 };
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setFontMatrix(fontMatrix);

    const std::array<double, 6>& result = gfxFont->getFontMatrix();
    EXPECT_EQ(result[0], 1.0);
    EXPECT_EQ(result[1], 0.0);
}

// Test: readEmbFontFile - Error case
TEST_F(GfxFontTest_1149, ReadEmbFontFile_Error_1149) {
    MockXRef mockXRef;
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    
    // Simulate error in reading embedded font file (assuming the method can return null or empty)
    EXPECT_CALL(mockXRef, readEmbFontFile(::testing::_)).WillOnce(::testing::Return(std::nullopt));
    
    auto result = gfxFont->readEmbFontFile(&mockXRef);
    EXPECT_EQ(result, std::nullopt);  // Assuming the method returns std::nullopt on failure
}

// Test: getAscent - Boundary condition (e.g., negative value)
TEST_F(GfxFontTest_1149, GetAscent_Negative_1149) {
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setAscent(-10.0);

    double result = gfxFont->getAscent();
    EXPECT_EQ(result, -10.0);
}

// Test: getDescent - Boundary condition (e.g., negative value)
TEST_F(GfxFontTest_1149, GetDescent_Negative_1149) {
    std::unique_ptr<GfxFont> gfxFont = std::make_unique<GfxFont>(/* constructor args */);
    gfxFont->setDescent(-5.0);

    double result = gfxFont->getDescent();
    EXPECT_EQ(result, -5.0);
}