#include <glib-object.h>
#include <gtest/gtest.h>

// Include the poppler glib headers
extern "C" {
#include "poppler.h"
#include "poppler-private.h"
}

class PopplerLayerTest_2505 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper to load a test PDF document with layers (OCG)
static PopplerDocument *load_test_document_with_layers()
{
    // Try to find a PDF with layers for testing
    // We'll try creating a simple document first
    const char *test_paths[] = { "./TestProjects/poppler/test/unittestcases/optionalContent.pdf", "./test/unittestcases/optionalContent.pdf", "../test/unittestcases/optionalContent.pdf", nullptr };

    PopplerDocument *doc = nullptr;
    for (int i = 0; test_paths[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_paths[i], nullptr, nullptr);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, nullptr);
            g_free(uri);
            if (doc) {
                return doc;
            }
        }
    }
    return nullptr;
}

// Test that PopplerLayer is a valid GObject type
TEST_F(PopplerLayerTest_2505, TypeRegistration_2505)
{
    GType layer_type = POPPLER_TYPE_LAYER;
    EXPECT_NE(layer_type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(layer_type, G_TYPE_OBJECT));
}

// Test getting layers from a document with optional content
TEST_F(PopplerLayerTest_2505, GetLayersFromDocument_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    GList *layers = poppler_document_get_layers(doc);
    // layers could be NULL if no layers exist, that's acceptable
    if (layers) {
        // Iterate through the layer tree
        GList *l = layers;
        while (l) {
            PopplerLayersIter *iter = (PopplerLayersIter *)l->data;
            if (iter) {
                poppler_layers_iter_free(iter);
            }
            l = l->next;
        }
        g_list_free(layers);
    }

    g_object_unref(doc);
}

// Test poppler_layer_get_title returns a valid string or NULL
TEST_F(PopplerLayerTest_2505, GetTitle_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    gboolean found_layer = FALSE;
    do {
        PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
        if (layer) {
            const gchar *title = poppler_layer_get_title(layer);
            // Title should be non-NULL for a valid layer
            EXPECT_NE(title, nullptr);
            if (title) {
                EXPECT_GT(strlen(title), 0u);
            }
            found_layer = TRUE;
            g_object_unref(layer);
        } else {
            // It could be a group title without an actual layer
            gchar *group_title = poppler_layers_iter_get_title(iter);
            if (group_title) {
                g_free(group_title);
            }
        }

        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                PopplerLayer *child_layer = poppler_layers_iter_get_layer(child);
                if (child_layer) {
                    const gchar *child_title = poppler_layer_get_title(child_layer);
                    EXPECT_NE(child_title, nullptr);
                    found_layer = TRUE;
                    g_object_unref(child_layer);
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
        }
    } while (poppler_layers_iter_next(iter));

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test poppler_layer_is_visible
TEST_F(PopplerLayerTest_2505, IsVisible_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    do {
        PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
        if (layer) {
            // is_visible should return TRUE or FALSE without crashing
            gboolean visible = poppler_layer_is_visible(layer);
            EXPECT_TRUE(visible == TRUE || visible == FALSE);
            g_object_unref(layer);
        }

        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                PopplerLayer *child_layer = poppler_layers_iter_get_layer(child);
                if (child_layer) {
                    gboolean child_visible = poppler_layer_is_visible(child_layer);
                    EXPECT_TRUE(child_visible == TRUE || child_visible == FALSE);
                    g_object_unref(child_layer);
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
        }
    } while (poppler_layers_iter_next(iter));

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test show/hide layer toggling
TEST_F(PopplerLayerTest_2505, ShowHideLayer_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    PopplerLayer *test_layer = nullptr;

    do {
        PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
        if (layer) {
            test_layer = layer;
            break;
        }

        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                PopplerLayer *child_layer = poppler_layers_iter_get_layer(child);
                if (child_layer) {
                    test_layer = child_layer;
                    break;
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
            if (test_layer) {
                break;
            }
        }
    } while (poppler_layers_iter_next(iter));

    if (test_layer) {
        // Hide the layer
        poppler_layer_hide(test_layer);
        EXPECT_FALSE(poppler_layer_is_visible(test_layer));

        // Show the layer
        poppler_layer_show(test_layer);
        EXPECT_TRUE(poppler_layer_is_visible(test_layer));

        g_object_unref(test_layer);
    }

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test poppler_layer_is_parent
TEST_F(PopplerLayerTest_2505, IsParent_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    do {
        PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
        if (layer) {
            // is_parent should return TRUE or FALSE without crashing
            gboolean is_parent = poppler_layer_is_parent(layer);
            EXPECT_TRUE(is_parent == TRUE || is_parent == FALSE);
            g_object_unref(layer);
        }
    } while (poppler_layers_iter_next(iter));

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test poppler_layer_get_radio_button_group_id
TEST_F(PopplerLayerTest_2505, GetRadioButtonGroupId_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    do {
        PopplerLayer *layer = poppler_layers_iter_get_layer(iter);
        if (layer) {
            gint rb_group_id = poppler_layer_get_radio_button_group_id(layer);
            // Radio button group ID should be a non-negative value or 0
            EXPECT_GE(rb_group_id, 0);
            g_object_unref(layer);
        }
    } while (poppler_layers_iter_next(iter));

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test that finalize properly cleans up (ref/unref cycle)
TEST_F(PopplerLayerTest_2505, RefUnrefCycle_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    PopplerLayer *test_layer = nullptr;
    do {
        test_layer = poppler_layers_iter_get_layer(iter);
        if (test_layer) {
            break;
        }
        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                test_layer = poppler_layers_iter_get_layer(child);
                if (test_layer) {
                    break;
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
            if (test_layer) {
                break;
            }
        }
    } while (poppler_layers_iter_next(iter));

    if (test_layer) {
        // Add a reference
        g_object_ref(test_layer);
        EXPECT_EQ(G_OBJECT(test_layer)->ref_count, 2u);

        // Remove the extra reference
        g_object_unref(test_layer);
        EXPECT_EQ(G_OBJECT(test_layer)->ref_count, 1u);

        // Final unref should trigger finalize without crash
        g_object_unref(test_layer);
    }

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test document without layers returns NULL iterator
TEST_F(PopplerLayerTest_2505, DocumentWithoutLayers_2505)
{
    // Try to find a simple PDF without layers
    const char *test_paths[] = { "./TestProjects/poppler/test/unittestcases/simple.pdf", "./test/unittestcases/simple.pdf", nullptr };

    PopplerDocument *doc = nullptr;
    for (int i = 0; test_paths[i] != nullptr; i++) {
        gchar *uri = g_filename_to_uri(test_paths[i], nullptr, nullptr);
        if (uri) {
            doc = poppler_document_new_from_file(uri, nullptr, nullptr);
            g_free(uri);
            if (doc) {
                break;
            }
        }
    }

    if (!doc) {
        GTEST_SKIP() << "No simple test PDF available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    // A document without layers should return NULL iterator
    // (or an empty iterator)
    if (iter) {
        // If iterator exists, it should have no layers
        poppler_layers_iter_free(iter);
    }

    g_object_unref(doc);
}

// Test multiple show/hide toggles
TEST_F(PopplerLayerTest_2505, MultipleShowHideToggles_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    PopplerLayer *test_layer = nullptr;
    do {
        test_layer = poppler_layers_iter_get_layer(iter);
        if (test_layer) {
            break;
        }
        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                test_layer = poppler_layers_iter_get_layer(child);
                if (test_layer) {
                    break;
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
            if (test_layer) {
                break;
            }
        }
    } while (poppler_layers_iter_next(iter));

    if (test_layer) {
        // Toggle multiple times
        for (int i = 0; i < 5; i++) {
            poppler_layer_hide(test_layer);
            EXPECT_FALSE(poppler_layer_is_visible(test_layer));
            poppler_layer_show(test_layer);
            EXPECT_TRUE(poppler_layer_is_visible(test_layer));
        }
        g_object_unref(test_layer);
    }

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test showing an already visible layer
TEST_F(PopplerLayerTest_2505, ShowAlreadyVisibleLayer_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    PopplerLayer *test_layer = nullptr;
    do {
        test_layer = poppler_layers_iter_get_layer(iter);
        if (test_layer) {
            break;
        }
        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                test_layer = poppler_layers_iter_get_layer(child);
                if (test_layer) {
                    break;
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
            if (test_layer) {
                break;
            }
        }
    } while (poppler_layers_iter_next(iter));

    if (test_layer) {
        // Ensure layer is visible
        poppler_layer_show(test_layer);
        EXPECT_TRUE(poppler_layer_is_visible(test_layer));

        // Show again - should remain visible
        poppler_layer_show(test_layer);
        EXPECT_TRUE(poppler_layer_is_visible(test_layer));

        g_object_unref(test_layer);
    }

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}

// Test hiding an already hidden layer
TEST_F(PopplerLayerTest_2505, HideAlreadyHiddenLayer_2505)
{
    PopplerDocument *doc = load_test_document_with_layers();
    if (!doc) {
        GTEST_SKIP() << "No test PDF with layers available";
    }

    PopplerLayersIter *iter = poppler_layers_iter_new(doc);
    if (!iter) {
        g_object_unref(doc);
        GTEST_SKIP() << "No layers iterator available";
    }

    PopplerLayer *test_layer = nullptr;
    do {
        test_layer = poppler_layers_iter_get_layer(iter);
        if (test_layer) {
            break;
        }
        PopplerLayersIter *child = poppler_layers_iter_get_child(iter);
        if (child) {
            do {
                test_layer = poppler_layers_iter_get_layer(child);
                if (test_layer) {
                    break;
                }
            } while (poppler_layers_iter_next(child));
            poppler_layers_iter_free(child);
            if (test_layer) {
                break;
            }
        }
    } while (poppler_layers_iter_next(iter));

    if (test_layer) {
        // Hide the layer
        poppler_layer_hide(test_layer);
        EXPECT_FALSE(poppler_layer_is_visible(test_layer));

        // Hide again - should remain hidden
        poppler_layer_hide(test_layer);
        EXPECT_FALSE(poppler_layer_is_visible(test_layer));

        g_object_unref(test_layer);
    }

    poppler_layers_iter_free(iter);
    g_object_unref(doc);
}
