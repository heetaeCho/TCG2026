#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-document.h"
#include "poppler-page.h"
}

class PopplerAnnotCircleTest_2115 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL returns NULL (g_return_val_if_fail should handle this)
TEST_F(PopplerAnnotCircleTest_2115, GetInteriorColorWithNullReturnsNull_2115)
{
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    // We need to suppress the GLib warning for this test
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");
    PopplerColor *color = poppler_annot_circle_get_interior_color(NULL);
    g_test_assert_expected_messages();
    EXPECT_EQ(color, nullptr);
}

// Test that passing an invalid (non-PopplerAnnotCircle) object returns NULL
TEST_F(PopplerAnnotCircleTest_2115, GetInteriorColorWithInvalidAnnotTypeReturnsNull_2115)
{
    // Create a different type of annotation object if possible, or use a generic GObject
    // A plain GObject is not a PopplerAnnotCircle, so the type check should fail
    GObject *not_a_circle = (GObject *)g_object_new(G_TYPE_OBJECT, NULL);
    
    g_test_expect_message("GLib-GObject", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_ANNOT_CIRCLE*");
    PopplerColor *color = poppler_annot_circle_get_interior_color((PopplerAnnotCircle *)not_a_circle);
    g_test_assert_expected_messages();
    
    EXPECT_EQ(color, nullptr);
    
    g_object_unref(not_a_circle);
}

// Test with a valid PopplerAnnotCircle created from a PDF that has a circle annotation
// This test creates a circle annotation via the poppler API if available
TEST_F(PopplerAnnotCircleTest_2115, GetInteriorColorWithValidCircleAnnot_2115)
{
    // Create a PopplerAnnotCircle using the API
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerAnnot *annot = poppler_annot_circle_new(NULL, &rect);
    
    if (annot != nullptr) {
        EXPECT_TRUE(POPPLER_IS_ANNOT_CIRCLE(annot));
        
        // Get interior color - for a newly created circle annot, it may be NULL
        // (no interior color set by default)
        PopplerColor *color = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
        
        // The result depends on the default state; it could be NULL if no interior color is set
        // We simply verify the call doesn't crash and returns a valid or NULL pointer
        if (color != nullptr) {
            g_free(color);
        }
        
        g_object_unref(annot);
    }
}

// Test that setting and getting interior color works consistently
TEST_F(PopplerAnnotCircleTest_2115, SetAndGetInteriorColorConsistency_2115)
{
    PopplerRectangle rect;
    rect.x1 = 10.0;
    rect.y1 = 10.0;
    rect.x2 = 100.0;
    rect.y2 = 100.0;

    PopplerAnnot *annot = poppler_annot_circle_new(NULL, &rect);
    
    if (annot != nullptr) {
        PopplerColor color_to_set;
        color_to_set.red = 65535;
        color_to_set.green = 0;
        color_to_set.blue = 32768;
        
        poppler_annot_circle_set_interior_color(POPPLER_ANNOT_CIRCLE(annot), &color_to_set);
        
        PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
        
        ASSERT_NE(retrieved_color, nullptr);
        EXPECT_EQ(retrieved_color->red, 65535);
        EXPECT_EQ(retrieved_color->green, 0);
        EXPECT_EQ(retrieved_color->blue, 32768);
        
        g_free(retrieved_color);
        g_object_unref(annot);
    }
}

// Test clearing interior color (setting to NULL) and then getting it
TEST_F(PopplerAnnotCircleTest_2115, SetNullInteriorColorAndGet_2115)
{
    PopplerRectangle rect;
    rect.x1 = 0.0;
    rect.y1 = 0.0;
    rect.x2 = 50.0;
    rect.y2 = 50.0;

    PopplerAnnot *annot = poppler_annot_circle_new(NULL, &rect);
    
    if (annot != nullptr) {
        // Set interior color to NULL (clear it)
        poppler_annot_circle_set_interior_color(POPPLER_ANNOT_CIRCLE(annot), NULL);
        
        PopplerColor *color = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
        
        // After clearing, should return NULL
        EXPECT_EQ(color, nullptr);
        
        if (color != nullptr) {
            g_free(color);
        }
        
        g_object_unref(annot);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
