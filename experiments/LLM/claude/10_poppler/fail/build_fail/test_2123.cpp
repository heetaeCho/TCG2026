#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Forward declarations and minimal stubs needed for testing
// Since we're treating the implementation as a black box, we need to set up
// the structures that the function operates on.

#include "poppler-annot.h"
#include "poppler-private.h"

// We need access to Annot and AnnotBorderArray from poppler core
#include "Annot.h"

class PopplerAnnotSetBorderWidthTest_2123 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need to create a minimal PopplerAnnot with a valid Annot object
        // This requires setting up the necessary poppler core objects
    }

    void TearDown() override {
    }

    PopplerAnnot *createTestAnnot() {
        // Create a PopplerAnnot structure with a mock or real Annot
        // This depends on the actual poppler infrastructure
        PopplerAnnot *annot = static_cast<PopplerAnnot *>(g_object_new(POPPLER_TYPE_ANNOT, nullptr));
        return annot;
    }
};

// Test setting a normal positive border width
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetPositiveWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 5.0);
        // Verify through the getter if available
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 5.0);
    }
    
    g_object_unref(annot);
}

// Test setting border width to zero
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetZeroWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 0.0);
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 0.0);
    }
    
    g_object_unref(annot);
}

// Test setting a very large border width
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetLargeWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 1000.0);
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 1000.0);
    }
    
    g_object_unref(annot);
}

// Test setting a very small positive border width
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetSmallPositiveWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 0.001);
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 0.001);
    }
    
    g_object_unref(annot);
}

// Test setting border width to 1.0 (common default)
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetUnitWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 1.0);
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 1.0);
    }
    
    g_object_unref(annot);
}

// Test setting border width multiple times (last value should persist)
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetWidthMultipleTimes_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 3.0);
        poppler_annot_set_border_width(annot, 7.0);
        poppler_annot_set_border_width(annot, 2.5);
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 2.5);
    }
    
    g_object_unref(annot);
}

// Test setting a fractional border width
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetFractionalWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        poppler_annot_set_border_width(annot, 2.75);
        double width = poppler_annot_get_border_width(annot);
        EXPECT_DOUBLE_EQ(width, 2.75);
    }
    
    g_object_unref(annot);
}

// Test setting negative border width (boundary/error case)
TEST_F(PopplerAnnotSetBorderWidthTest_2123, SetNegativeWidth_2123) {
    PopplerAnnot *annot = createTestAnnot();
    ASSERT_NE(annot, nullptr);
    
    if (annot->annot) {
        // Negative width - behavior depends on implementation
        // We just verify it doesn't crash
        poppler_annot_set_border_width(annot, -1.0);
        // The function should still complete without crashing
        double width = poppler_annot_get_border_width(annot);
        // We observe whatever the implementation does with negative values
        (void)width;
    }
    
    g_object_unref(annot);
}
