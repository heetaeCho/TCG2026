#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

#include "poppler/Unicode.h"
#include "goo/GooString.h"
#include "poppler/UnicodeMap.h"
#include "poppler/GlobalParams.h"

// We need access to the static function - include the .cc file
// or declare it extern. Since it's static, we include the source.
// However, this may cause linking issues. An alternative approach:
// We replicate the declaration and link against the object.
// For testing a static function, we include the source file.

// Forward declare the helper functions used by reorderText
// We need to include the actual source to get the static function
#include "poppler/TextOutputDev.cc"

class ReorderTextTest_1903 : public ::testing::Test {
protected:
    void SetUp() override {
        // Initialize globalParams if needed
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
        // Get a Latin1 or ASCII UnicodeMap
        uMap = globalParams->getTextEncoding();
        if (!uMap) {
            // Try to parse a known encoding
            uMap = UnicodeMap::parse("Latin1");
        }
    }

    std::shared_ptr<UnicodeMap> uMap;
};

// Test with empty input (len = 0)
TEST_F(ReorderTextTest_1903, EmptyInput_1903) {
    Unicode text[] = { 'A' };
    GooString s;
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 0, uMap.get(), true, &s, u);
    EXPECT_EQ(nCols, 0);
}

// Test with null GooString and null Unicode output
TEST_F(ReorderTextTest_1903, NullOutputs_1903) {
    Unicode text[] = { 'H', 'e', 'l', 'l', 'o' };
    
    int nCols = reorderText(text, 5, uMap.get(), true, nullptr, nullptr);
    EXPECT_EQ(nCols, 5);
}

// Test primaryLR with only LTR characters
TEST_F(ReorderTextTest_1903, PrimaryLR_AllLTR_1903) {
    Unicode text[] = { 'A', 'B', 'C', 'D' };
    GooString s;
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 4, uMap.get(), true, &s, u);
    EXPECT_EQ(nCols, 4);
    EXPECT_EQ(u[0], 'A');
    EXPECT_EQ(u[1], 'B');
    EXPECT_EQ(u[2], 'C');
    EXPECT_EQ(u[3], 'D');
}

// Test primaryLR with only numeric characters
TEST_F(ReorderTextTest_1903, PrimaryLR_NumericChars_1903) {
    Unicode text[] = { '1', '2', '3' };
    GooString s;
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 3, uMap.get(), true, &s, u);
    EXPECT_EQ(nCols, 3);
    EXPECT_EQ(u[0], '1');
    EXPECT_EQ(u[1], '2');
    EXPECT_EQ(u[2], '3');
}

// Test primaryLR with RTL (Arabic) characters
TEST_F(ReorderTextTest_1903, PrimaryLR_WithRTL_1903) {
    // Arabic characters are RTL: U+0627 (Alef), U+0628 (Ba), U+0629 (Ta Marbuta)
    Unicode text[] = { 'A', 'B', 0x0627, 0x0628, 0x0629, 'C', 'D' };
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 7, uMap.get(), true, nullptr, u);
    EXPECT_EQ(nCols, 7);
    // LTR chars should be in order
    EXPECT_EQ(u[0], 'A');
    EXPECT_EQ(u[1], 'B');
    // RTL chars should be reversed
    EXPECT_EQ(u[2], 0x0629);
    EXPECT_EQ(u[3], 0x0628);
    EXPECT_EQ(u[4], 0x0627);
    // Back to LTR
    EXPECT_EQ(u[5], 'C');
    EXPECT_EQ(u[6], 'D');
}

// Test primaryRL (right-to-left primary direction) with only RTL characters
TEST_F(ReorderTextTest_1903, PrimaryRL_AllRTL_1903) {
    Unicode text[] = { 0x0627, 0x0628, 0x0629 };
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 3, uMap.get(), false, nullptr, u);
    EXPECT_EQ(nCols, 3);
    // In RTL primary, RTL chars appear in reverse order (right-to-left reading)
    EXPECT_EQ(u[0], 0x0629);
    EXPECT_EQ(u[1], 0x0628);
    EXPECT_EQ(u[2], 0x0627);
}

// Test primaryRL with embedded LTR characters
TEST_F(ReorderTextTest_1903, PrimaryRL_WithLTR_1903) {
    Unicode text[] = { 0x0627, 0x0628, 'A', 'B', 0x0629 };
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 5, uMap.get(), false, nullptr, u);
    EXPECT_EQ(nCols, 5);
    // RTL primary: starts from end, RTL chars reversed, LTR embedded in order
    EXPECT_EQ(u[0], 0x0629);
    // LTR run should be in forward order
    EXPECT_EQ(u[1], 'A');
    EXPECT_EQ(u[2], 'B');
    EXPECT_EQ(u[3], 0x0628);
    EXPECT_EQ(u[4], 0x0627);
}

// Test single character LTR
TEST_F(ReorderTextTest_1903, SingleCharLTR_1903) {
    Unicode text[] = { 'X' };
    GooString s;
    Unicode u[5] = {};
    
    int nCols = reorderText(text, 1, uMap.get(), true, &s, u);
    EXPECT_EQ(nCols, 1);
    EXPECT_EQ(u[0], 'X');
}

// Test single character RTL in LTR primary
TEST_F(ReorderTextTest_1903, SingleRTLCharInLTR_1903) {
    Unicode text[] = { 0x0627 };  // Arabic Alef
    Unicode u[5] = {};
    
    int nCols = reorderText(text, 1, uMap.get(), true, nullptr, u);
    EXPECT_EQ(nCols, 1);
    EXPECT_EQ(u[0], 0x0627);
}

// Test single character RTL in RTL primary
TEST_F(ReorderTextTest_1903, SingleRTLCharInRTL_1903) {
    Unicode text[] = { 0x0627 };
    Unicode u[5] = {};
    
    int nCols = reorderText(text, 1, uMap.get(), false, nullptr, u);
    EXPECT_EQ(nCols, 1);
    EXPECT_EQ(u[0], 0x0627);
}

// Test with GooString output in LTR mode
TEST_F(ReorderTextTest_1903, GooStringOutput_LTR_1903) {
    Unicode text[] = { 'H', 'i' };
    GooString s;
    
    int nCols = reorderText(text, 2, uMap.get(), true, &s, nullptr);
    EXPECT_EQ(nCols, 2);
    EXPECT_GT(s.toStr().size(), 0u);
}

// Test with GooString output in RTL mode
TEST_F(ReorderTextTest_1903, GooStringOutput_RTL_1903) {
    Unicode text[] = { 0x0627, 0x0628 };
    GooString s;
    
    int nCols = reorderText(text, 2, uMap.get(), false, &s, nullptr);
    EXPECT_EQ(nCols, 2);
    // Should have content plus RLE and POPDF markers
    EXPECT_GT(s.toStr().size(), 0u);
}

// Test with null Unicode output buffer but valid GooString
TEST_F(ReorderTextTest_1903, NullUnicodeBuffer_1903) {
    Unicode text[] = { 'A', 'B', 'C' };
    GooString s;
    
    int nCols = reorderText(text, 3, uMap.get(), true, &s, nullptr);
    EXPECT_EQ(nCols, 3);
}

// Test primaryLR with alternating LTR and RTL
TEST_F(ReorderTextTest_1903, AlternatingLTRRTL_1903) {
    Unicode text[] = { 'A', 0x0627, 'B', 0x0628, 'C' };
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 5, uMap.get(), true, nullptr, u);
    EXPECT_EQ(nCols, 5);
    // First LTR char
    EXPECT_EQ(u[0], 'A');
}

// Test with numbers embedded in RTL text (LTR primary)
TEST_F(ReorderTextTest_1903, NumbersInRTL_LTRPrimary_1903) {
    Unicode text[] = { 0x0627, '1', '2', 0x0628 };
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 4, uMap.get(), true, nullptr, u);
    EXPECT_EQ(nCols, 4);
}

// Test return value matches expected column count for mixed text
TEST_F(ReorderTextTest_1903, ReturnValueMatchesLength_1903) {
    Unicode text[] = { 'A', 'B', 0x0627, 0x0628, 'C' };
    
    int nCols = reorderText(text, 5, uMap.get(), true, nullptr, nullptr);
    EXPECT_EQ(nCols, 5);
}

// Test return value for RTL primary
TEST_F(ReorderTextTest_1903, ReturnValueRTLPrimary_1903) {
    Unicode text[] = { 0x0627, 0x0628, 'A', 'B', 0x0629 };
    
    int nCols = reorderText(text, 5, uMap.get(), false, nullptr, nullptr);
    EXPECT_EQ(nCols, 5);
}

// Test with all spaces (neutral characters) in LTR primary
TEST_F(ReorderTextTest_1903, AllSpaces_LTR_1903) {
    Unicode text[] = { ' ', ' ', ' ' };
    Unicode u[10] = {};
    
    int nCols = reorderText(text, 3, uMap.get(), true, nullptr, u);
    EXPECT_EQ(nCols, 3);
    EXPECT_EQ(u[0], ' ');
    EXPECT_EQ(u[1], ' ');
    EXPECT_EQ(u[2], ' ');
}

// Test empty with RTL primary
TEST_F(ReorderTextTest_1903, EmptyInput_RTL_1903) {
    Unicode text[] = { 'A' };
    
    int nCols = reorderText(text, 0, uMap.get(), false, nullptr, nullptr);
    EXPECT_EQ(nCols, 0);
}
