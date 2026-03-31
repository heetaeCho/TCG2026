#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <poppler-structure-element.h>

#include <gtest/gtest.h>
#include <cstring>

class PopplerStructureElementGetPaddingTest_2562 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a valid PopplerDocument with tagged structure to get real structure elements.
        // For unit testing purposes, we test the guard conditions and behavior with NULL/invalid inputs.
    }

    void TearDown() override {
    }
};

// Test that passing NULL as the structure element doesn't crash (g_return_if_fail guard)
TEST_F(PopplerStructureElementGetPaddingTest_2562, NullElementDoesNotCrash_2562) {
    gdouble paddings[4] = {-1.0, -1.0, -1.0, -1.0};
    
    // Should safely return without modifying paddings due to g_return_if_fail
    poppler_structure_element_get_padding(nullptr, paddings);
    
    // paddings should remain unchanged since the function should early-return
    EXPECT_DOUBLE_EQ(paddings[0], -1.0);
    EXPECT_DOUBLE_EQ(paddings[1], -1.0);
    EXPECT_DOUBLE_EQ(paddings[2], -1.0);
    EXPECT_DOUBLE_EQ(paddings[3], -1.0);
}

// Test that passing NULL as paddings array doesn't crash (g_return_if_fail guard)
TEST_F(PopplerStructureElementGetPaddingTest_2562, NullPaddingsDoesNotCrash_2562) {
    // Passing NULL for both should not crash
    poppler_structure_element_get_padding(nullptr, nullptr);
}

// Test with a real document if available - loading a tagged PDF
class PopplerStructureElementGetPaddingWithDocTest_2562 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    
    void SetUp() override {
        // Try to create a minimal test scenario
        // In practice, we'd need a tagged PDF file for full integration testing
    }
    
    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that an invalid GObject type is rejected by the type check macro
TEST_F(PopplerStructureElementGetPaddingWithDocTest_2562, InvalidGObjectTypeIsRejected_2562) {
    gdouble paddings[4] = {42.0, 42.0, 42.0, 42.0};
    
    // Create a random GObject that is NOT a PopplerStructureElement
    // The POPPLER_IS_STRUCTURE_ELEMENT check should fail
    GObject *fake_obj = (GObject *)g_object_new(G_TYPE_OBJECT, nullptr);
    
    poppler_structure_element_get_padding((PopplerStructureElement *)fake_obj, paddings);
    
    // paddings should remain unchanged
    EXPECT_DOUBLE_EQ(paddings[0], 42.0);
    EXPECT_DOUBLE_EQ(paddings[1], 42.0);
    EXPECT_DOUBLE_EQ(paddings[2], 42.0);
    EXPECT_DOUBLE_EQ(paddings[3], 42.0);
    
    g_object_unref(fake_obj);
}

// Test boundary: paddings array is allocated but element is null
TEST_F(PopplerStructureElementGetPaddingTest_2562, AllocatedPaddingsWithNullElement_2562) {
    gdouble *paddings = g_new0(gdouble, 4);
    paddings[0] = 99.0;
    paddings[1] = 99.0;
    paddings[2] = 99.0;
    paddings[3] = 99.0;
    
    poppler_structure_element_get_padding(nullptr, paddings);
    
    // Should not have been modified
    EXPECT_DOUBLE_EQ(paddings[0], 99.0);
    EXPECT_DOUBLE_EQ(paddings[1], 99.0);
    EXPECT_DOUBLE_EQ(paddings[2], 99.0);
    EXPECT_DOUBLE_EQ(paddings[3], 99.0);
    
    g_free(paddings);
}
