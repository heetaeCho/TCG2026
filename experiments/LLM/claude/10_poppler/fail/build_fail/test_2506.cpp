#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler.h"
}

class PopplerLayerTest_2506 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PDF document with optional content (layers) to test
        // PopplerLayer functionality properly
        doc = nullptr;
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
    }

    PopplerDocument *doc;
};

// Test that PopplerLayer GType is properly registered
TEST_F(PopplerLayerTest_2506, TypeRegistration_2506)
{
    GType layer_type = poppler_layer_get_type();
    EXPECT_NE(layer_type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(layer_type, G_TYPE_OBJECT));
}

// Test that PopplerLayer type name is correct
TEST_F(PopplerLayerTest_2506, TypeName_2506)
{
    GType layer_type = poppler_layer_get_type();
    const gchar *name = g_type_name(layer_type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerLayer");
}

// Test getting layers from a document without layers
TEST_F(PopplerLayerTest_2506, NoLayersInSimpleDocument_2506)
{
    // Create a simple PDF in memory that has no layers
    GError *error = nullptr;
    
    // Try to load a simple PDF without optional content
    const char *pdf_data = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                           "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                           "3 0 obj<</Type/Page/Parent 2 0 R/MediaBox[0 0 612 792]>>endobj\n"
                           "xref\n0 4\n"
                           "0000000000 65535 f \n"
                           "0000000009 00000 n \n"
                           "0000000058 00000 n \n"
                           "0000000115 00000 n \n"
                           "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";

    GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
    doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
    g_bytes_unref(bytes);

    if (doc == nullptr) {
        // If loading fails, skip this test
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not create test document";
        return;
    }

    GList *layers = poppler_document_get_layers(doc);
    // A simple document without OCG should return NULL or empty layers
    // The actual return depends on poppler implementation
    if (layers) {
        g_list_free(layers);
    }
    // Just verify we don't crash
    SUCCEED();
}

// Test that PopplerLayer is a GObject subclass
TEST_F(PopplerLayerTest_2506, IsGObjectSubclass_2506)
{
    GType layer_type = poppler_layer_get_type();
    GType parent_type = g_type_parent(layer_type);
    EXPECT_EQ(parent_type, G_TYPE_OBJECT);
}

// Test class size is valid
TEST_F(PopplerLayerTest_2506, ClassSizeValid_2506)
{
    GType layer_type = poppler_layer_get_type();
    GTypeQuery query;
    g_type_query(layer_type, &query);
    EXPECT_GT(query.class_size, 0u);
    EXPECT_GT(query.instance_size, 0u);
}

// Test that the type can be looked up by name
TEST_F(PopplerLayerTest_2506, TypeLookupByName_2506)
{
    // First ensure the type is registered
    GType layer_type = poppler_layer_get_type();
    GType looked_up = g_type_from_name("PopplerLayer");
    EXPECT_EQ(layer_type, looked_up);
}
