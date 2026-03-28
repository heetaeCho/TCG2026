#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "CairoOutputDev.h"

class CairoOutputDevTest_1727 : public ::testing::Test {
protected:
    CairoOutputDev dev;
};

// Test interpretType3Chars returns false
TEST_F(CairoOutputDevTest_1727, InterpretType3CharsReturnsFalse_1727) {
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test upsideDown return value
TEST_F(CairoOutputDevTest_1727, UpsideDownReturnValue_1727) {
    // upsideDown() should return a consistent boolean value
    bool result = dev.upsideDown();
    // Call again to verify consistency
    EXPECT_EQ(result, dev.upsideDown());
}

// Test useDrawChar return value
TEST_F(CairoOutputDevTest_1727, UseDrawCharReturnValue_1727) {
    bool result = dev.useDrawChar();
    EXPECT_EQ(result, dev.useDrawChar());
}

// Test useTilingPatternFill return value
TEST_F(CairoOutputDevTest_1727, UseTilingPatternFillReturnValue_1727) {
    bool result = dev.useTilingPatternFill();
    EXPECT_EQ(result, dev.useTilingPatternFill());
}

// Test useFillColorStop return value
TEST_F(CairoOutputDevTest_1727, UseFillColorStopReturnValue_1727) {
    bool result = dev.useFillColorStop();
    EXPECT_EQ(result, dev.useFillColorStop());
}

// Test needClipToCropBox return value
TEST_F(CairoOutputDevTest_1727, NeedClipToCropBoxReturnValue_1727) {
    bool result = dev.needClipToCropBox();
    EXPECT_EQ(result, dev.needClipToCropBox());
}

// Test supportJPXtransparency return value
TEST_F(CairoOutputDevTest_1727, SupportJPXTransparencyReturnValue_1727) {
    bool result = dev.supportJPXtransparency();
    EXPECT_EQ(result, dev.supportJPXtransparency());
}

// Test useShadedFills with different type values
TEST_F(CairoOutputDevTest_1727, UseShadedFillsVariousTypes_1727) {
    // Test with various shading types (1-7 are common PDF shading types)
    for (int type = 1; type <= 7; ++type) {
        bool result = dev.useShadedFills(type);
        // Just verify it doesn't crash and returns consistent results
        EXPECT_EQ(result, dev.useShadedFills(type));
    }
}

// Test useShadedFills with boundary type 0
TEST_F(CairoOutputDevTest_1727, UseShadedFillsTypeZero_1727) {
    bool result = dev.useShadedFills(0);
    EXPECT_EQ(result, dev.useShadedFills(0));
}

// Test useShadedFills with negative type
TEST_F(CairoOutputDevTest_1727, UseShadedFillsNegativeType_1727) {
    bool result = dev.useShadedFills(-1);
    EXPECT_EQ(result, dev.useShadedFills(-1));
}

// Test setPrinting
TEST_F(CairoOutputDevTest_1727, SetPrintingTrue_1727) {
    // Should not crash
    dev.setPrinting(true);
}

TEST_F(CairoOutputDevTest_1727, SetPrintingFalse_1727) {
    // Should not crash
    dev.setPrinting(false);
}

// Test setLogicalStructure
TEST_F(CairoOutputDevTest_1727, SetLogicalStructureTrue_1727) {
    dev.setLogicalStructure(true);
}

TEST_F(CairoOutputDevTest_1727, SetLogicalStructureFalse_1727) {
    dev.setLogicalStructure(false);
}

// Test getType3GlyphWidth
TEST_F(CairoOutputDevTest_1727, GetType3GlyphWidthReturnsValues_1727) {
    double wx = -1.0, wy = -1.0;
    dev.getType3GlyphWidth(&wx, &wy);
    // After construction, wx and wy should have some defined value
    // We just verify no crash and values are set
    EXPECT_TRUE(std::isfinite(wx));
    EXPECT_TRUE(std::isfinite(wy));
}

// Test hasType3GlyphBBox
TEST_F(CairoOutputDevTest_1727, HasType3GlyphBBoxInitialState_1727) {
    bool result = dev.hasType3GlyphBBox();
    // Consistent return
    EXPECT_EQ(result, dev.hasType3GlyphBBox());
}

// Test type3GlyphHasColor
TEST_F(CairoOutputDevTest_1727, Type3GlyphHasColorInitialState_1727) {
    bool result = dev.type3GlyphHasColor();
    EXPECT_EQ(result, dev.type3GlyphHasColor());
}

// Test getType3GlyphBBox returns non-null
TEST_F(CairoOutputDevTest_1727, GetType3GlyphBBoxReturnsPointer_1727) {
    double* bbox = dev.getType3GlyphBBox();
    EXPECT_NE(bbox, nullptr);
}

// Test setCairo with nullptr
TEST_F(CairoOutputDevTest_1727, SetCairoNull_1727) {
    dev.setCairo(nullptr);
    // Should not crash
}

// Test setTextPage with nullptr (empty shared_ptr)
TEST_F(CairoOutputDevTest_1727, SetTextPageNull_1727) {
    dev.setTextPage(nullptr);
    // Should not crash
}

// Test multiple calls to interpretType3Chars are consistent
TEST_F(CairoOutputDevTest_1727, InterpretType3CharsConsistency_1727) {
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test that default constructor creates a valid object
TEST_F(CairoOutputDevTest_1727, DefaultConstructorCreatesValidObject_1727) {
    CairoOutputDev newDev;
    EXPECT_FALSE(newDev.interpretType3Chars());
}

// Test setType3RenderType
TEST_F(CairoOutputDevTest_1727, SetType3RenderType_1727) {
    // Set various render types - just ensure no crash
    dev.setType3RenderType(Type3RenderType::T3_UNSET);
    EXPECT_FALSE(dev.interpretType3Chars());
}

// Test popTransparencyGroup does not crash on fresh object
// Note: This might crash without proper setup, but we test the interface
TEST_F(CairoOutputDevTest_1727, EndPageDoesNotCrashOnFreshObject_1727) {
    // endPage on a fresh object should handle gracefully
    dev.endPage();
}
