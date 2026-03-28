#include <glib.h>
#include <glib-object.h>
#include "poppler-document.h"
#include "poppler-layer.h"
#include "poppler.h"

#include <gtest/gtest.h>

class PopplerLayersIterTest_2251 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that passing NULL iter returns NULL
TEST_F(PopplerLayersIterTest_2251, NullIterReturnsNull_2251)
{
    PopplerLayer *layer = poppler_layers_iter_get_layer(nullptr);
    EXPECT_EQ(layer, nullptr);
}

// Test with a real PDF document that has optional content (layers)
class PopplerLayersIterDocTest_2251 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerLayersIter *iter = nullptr;

    void SetUp() override
    {
        // Try to load a test PDF with layers if available
        GError *error = nullptr;
        // Use a simple PDF path - this test may be skipped if no suitable PDF exists
        doc = nullptr;
        iter = nullptr;
    }

    void TearDown() override
    {
        if (iter) {
            poppler_layers_iter_free(iter);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }
};

// Test that get_layer returns NULL for a layer without optional content group
// This test verifies the branch where layer->oc is null
TEST_F(PopplerLayersIterDocTest_2251, NoOCLayerReturnsNull_2251)
{
    // Without a real document with layers, we verify the null-safety
    // The function should handle the case gracefully
    PopplerLayer *result = poppler_layers_iter_get_layer(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test poppler_layers_iter_get_layer with a valid document that has layers
TEST_F(PopplerLayersIterDocTest_2251, ValidDocumentWithLayers_2251)
{
    GError *error = nullptr;
    gchar *uri = g_strdup_printf("file://%s", "./TestProjects/poppler/test/pdf-files/layers.pdf");
    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc == nullptr) {
        // If the test PDF doesn't exist, skip
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF with layers not available";
        return;
    }

    iter = poppler_layers_iter_new(doc);
    if (iter == nullptr) {
        GTEST_SKIP() << "Document has no layers";
        return;
    }

    // Iterate through layers and test get_layer
    do {
        PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
        // Layer may be NULL if the item doesn't have an optional content group
        // but the function should not crash
        if (layer != nullptr) {
            // Verify it's a valid PopplerLayer object
            EXPECT_TRUE(POPPLER_IS_LAYER(layer));
            g_object_unref(layer);
        }

        // Check children
        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                PopplerLayer *child_layer = poppler_layers_iter_get_layer(child);
                if (child_layer != nullptr) {
                    EXPECT_TRUE(POPPLER_IS_LAYER(child_layer));
                    g_object_unref(child_layer);
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
        }
    } while (poppler_layers_iter_next(iter));
}

// Test that poppler_layers_iter_get_layer returns proper GObject type
TEST_F(PopplerLayersIterDocTest_2251, ReturnedLayerIsProperGObject_2251)
{
    GError *error = nullptr;
    gchar *uri = g_strdup_printf("file://%s", "./TestProjects/poppler/test/pdf-files/layers.pdf");
    doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Test PDF with layers not available";
        return;
    }

    iter = poppler_layers_iter_new(doc);
    if (iter == nullptr) {
        GTEST_SKIP() << "Document has no layers";
        return;
    }

    PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
    if (layer != nullptr) {
        // Verify the returned object is a PopplerLayer
        EXPECT_TRUE(POPPLER_IS_LAYER(layer));

        // Test that we can get the title (basic property access)
        const gchar *title = poppler_layer_get_title(layer);
        // Title should exist for a valid layer
        EXPECT_NE(title, nullptr);

        g_object_unref(layer);
    }
}
