#include <glib-object.h>
#include <glib.h>
#include "poppler-layer.h"
#include "poppler-private.h"

#include <gtest/gtest.h>

// We need to include the necessary poppler headers
// Since PopplerLayer is a GObject, we need proper initialization

class PopplerLayerTest_2508 : public ::testing::Test {
protected:
    void SetUp() override {
        // Ensure GObject type system is initialized
    }

    void TearDown() override {
    }

    PopplerLayer *createPopplerLayer(const gchar *title) {
        // Create a PopplerLayer GObject instance
        PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
        if (layer) {
            layer->title = g_strdup(title);
        }
        return layer;
    }

    void destroyPopplerLayer(PopplerLayer *layer) {
        if (layer) {
            g_object_unref(layer);
        }
    }
};

// Test that get_title returns the correct title for a valid layer
TEST_F(PopplerLayerTest_2508, GetTitleReturnsCorrectTitle_2508) {
    PopplerLayer *layer = createPopplerLayer("Test Layer");
    ASSERT_NE(layer, nullptr);

    const gchar *title = poppler_layer_get_title(layer);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Test Layer");

    destroyPopplerLayer(layer);
}

// Test that get_title returns NULL when passed NULL
TEST_F(PopplerLayerTest_2508, GetTitleReturnsNullForNullInput_2508) {
    // Passing NULL should trigger g_return_val_if_fail and return NULL
    const gchar *title = poppler_layer_get_title(NULL);
    EXPECT_EQ(title, nullptr);
}

// Test with an empty string title
TEST_F(PopplerLayerTest_2508, GetTitleReturnsEmptyStringTitle_2508) {
    PopplerLayer *layer = createPopplerLayer("");
    ASSERT_NE(layer, nullptr);

    const gchar *title = poppler_layer_get_title(layer);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "");

    destroyPopplerLayer(layer);
}

// Test with a title containing special characters
TEST_F(PopplerLayerTest_2508, GetTitleWithSpecialCharacters_2508) {
    PopplerLayer *layer = createPopplerLayer("Layer with spëcîal chars & <symbols> \"quotes\"");
    ASSERT_NE(layer, nullptr);

    const gchar *title = poppler_layer_get_title(layer);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "Layer with spëcîal chars & <symbols> \"quotes\"");

    destroyPopplerLayer(layer);
}

// Test with a title containing UTF-8 characters
TEST_F(PopplerLayerTest_2508, GetTitleWithUTF8Characters_2508) {
    PopplerLayer *layer = createPopplerLayer("日本語レイヤー");
    ASSERT_NE(layer, nullptr);

    const gchar *title = poppler_layer_get_title(layer);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, "日本語レイヤー");

    destroyPopplerLayer(layer);
}

// Test with a NULL title set on the layer
TEST_F(PopplerLayerTest_2508, GetTitleReturnsNullWhenTitleIsNull_2508) {
    PopplerLayer *layer = createPopplerLayer(NULL);
    ASSERT_NE(layer, nullptr);

    // title field should be NULL since we passed NULL to g_strdup which returns NULL
    const gchar *title = poppler_layer_get_title(layer);
    EXPECT_EQ(title, nullptr);

    destroyPopplerLayer(layer);
}

// Test that calling get_title multiple times returns the same pointer (const)
TEST_F(PopplerLayerTest_2508, GetTitleReturnsSamePointerOnMultipleCalls_2508) {
    PopplerLayer *layer = createPopplerLayer("Consistent Title");
    ASSERT_NE(layer, nullptr);

    const gchar *title1 = poppler_layer_get_title(layer);
    const gchar *title2 = poppler_layer_get_title(layer);
    EXPECT_EQ(title1, title2);

    destroyPopplerLayer(layer);
}

// Test with a very long title
TEST_F(PopplerLayerTest_2508, GetTitleWithLongString_2508) {
    std::string longTitle(10000, 'A');
    PopplerLayer *layer = createPopplerLayer(longTitle.c_str());
    ASSERT_NE(layer, nullptr);

    const gchar *title = poppler_layer_get_title(layer);
    ASSERT_NE(title, nullptr);
    EXPECT_STREQ(title, longTitle.c_str());

    destroyPopplerLayer(layer);
}
