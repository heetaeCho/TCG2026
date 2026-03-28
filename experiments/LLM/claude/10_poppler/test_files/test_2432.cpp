static bool annots_display_decide_cb(Annot *annot, void *user_data) {
    auto flags = (PopplerRenderAnnotsFlags)GPOINTER_TO_UINT(user_data);
    Annot::AnnotSubtype type = annot->getType();
    int typeMask = 1 << MAX(0, (((int)type) - 1));
    return (flags & typeMask) != 0;
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"

// We need access to the static function. Since it's static in the .cc file,
// we include it to get access for testing purposes.
// First, include glib dependencies
#include <glib.h>
#include <glib-object.h>

// Forward declare the enum used
// PopplerRenderAnnotsFlags is a flags enum where each annotation subtype 
// corresponds to a bit position

// Include the poppler-page header to get type definitions
extern "C" {
#include "poppler-page.h"
}

// Since annots_display_decide_cb is static, we test through the public API
// that uses it, or we replicate the test by including the source.
// For unit testing a static function, we include the source file.
// This is a common pattern for testing static/file-local functions.

// We define a test-accessible wrapper by including the implementation
namespace test_annots_display {
#define static  // temporarily remove static qualifier
#include "poppler-page.cc"
#undef static
}

class AnnotsDisplayDecideCbTest_2432 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper: create a mock-like Annot that returns a specific subtype
// Since Annot has getType() as a public method, we need a real or mock Annot.
// We'll use GMock to mock the Annot class.

class MockAnnot : public Annot {
public:
    // We can't easily construct Annot without PDFDoc, so we mock getType
    MOCK_CONST_METHOD0(getType, AnnotSubtype());
};

// Test: Type 1 (Text) with matching flag returns true
TEST_F(AnnotsDisplayDecideCbTest_2432, Type1WithMatchingFlagReturnsTrue_2432) {
    // AnnotSubtype starts at 1 for typeText
    // typeMask = 1 << (1 - 1) = 1 << 0 = 1
    // flags should have bit 0 set
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return(Annot::typeText));
    
    unsigned int flags = 1; // bit 0
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_TRUE(result);
}

// Test: Type 1 with non-matching flag returns false
TEST_F(AnnotsDisplayDecideCbTest_2432, Type1WithNonMatchingFlagReturnsFalse_2432) {
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return(Annot::typeText));
    
    unsigned int flags = 2; // bit 1 only
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_FALSE(result);
}

// Test: Type 2 with matching flag returns true
TEST_F(AnnotsDisplayDecideCbTest_2432, Type2WithMatchingFlagReturnsTrue_2432) {
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return(Annot::typeLink));
    
    unsigned int flags = 1 << 1; // bit 1
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_TRUE(result);
}

// Test: All flags set, any type returns true
TEST_F(AnnotsDisplayDecideCbTest_2432, AllFlagsSetAnyTypeReturnsTrue_2432) {
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return(Annot::typeHighlight));
    
    unsigned int flags = 0xFFFFFFFF;
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_TRUE(result);
}

// Test: No flags set, any type returns false
TEST_F(AnnotsDisplayDecideCbTest_2432, NoFlagsSetAnyTypeReturnsFalse_2432) {
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return(Annot::typeHighlight));
    
    unsigned int flags = 0;
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_FALSE(result);
}

// Test: Multiple flags set, type matches one of them
TEST_F(AnnotsDisplayDecideCbTest_2432, MultipleFlagsTypeMatchesOne_2432) {
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return(Annot::typeFreeText));
    
    // typeFreeText is subtype 3, so typeMask = 1 << 2 = 4
    unsigned int flags = 0x05; // bits 0 and 2 set
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_TRUE(result);
}

// Test: Boundary - subtype value of 0 (if it exists) uses MAX(0, -1) = 0
TEST_F(AnnotsDisplayDecideCbTest_2432, SubtypeZeroUsesShiftZero_2432) {
    MockAnnot annot;
    // typeUnknown is typically 0
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return((Annot::AnnotSubtype)0));
    
    // typeMask = 1 << MAX(0, 0 - 1) = 1 << MAX(0, -1) = 1 << 0 = 1
    unsigned int flags = 1; // bit 0
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_TRUE(result);
}

// Test: Subtype 0 with no bit 0 returns false
TEST_F(AnnotsDisplayDecideCbTest_2432, SubtypeZeroNoBit0ReturnsFalse_2432) {
    MockAnnot annot;
    EXPECT_CALL(annot, getType()).WillOnce(::testing::Return((Annot::AnnotSubtype)0));
    
    unsigned int flags = 2; // only bit 1
    void *user_data = GUINT_TO_POINTER(flags);
    
    bool result = test_annots_display::annots_display_decide_cb(&annot, user_data);
    EXPECT_FALSE(result);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
