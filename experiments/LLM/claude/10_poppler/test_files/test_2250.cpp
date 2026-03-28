#include <glib.h>
#include <gtest/gtest.h>

// Forward declarations and necessary structures
// We need to replicate the structures that are used by the public API

// Based on the code, we need these structures
struct Layer {
    gchar *label;
    // Other fields may exist but we only care about label for this test
};

struct _PopplerLayersIter {
    GList *items;
    int index;
};

typedef struct _PopplerLayersIter PopplerLayersIter;

// Declaration of the function under test
extern "C" {
    gchar *poppler_layers_iter_get_title(PopplerLayersIter *iter);
}

class PopplerLayersIterTest_2250 : public ::testing::Test {
protected:
    void SetUp() override {
        iter = nullptr;
    }

    void TearDown() override {
        if (iter) {
            // Clean up the items list but not the Layer data (we manage that separately)
            g_list_free(iter->items);
            delete iter;
        }
        for (auto *layer : layers) {
            g_free(layer->label);
            delete layer;
        }
        layers.clear();
    }

    PopplerLayersIter *createIter() {
        iter = new PopplerLayersIter();
        iter->items = nullptr;
        iter->index = 0;
        return iter;
    }

    Layer *createLayer(const gchar *label) {
        Layer *layer = new Layer();
        layer->label = label ? g_strdup(label) : nullptr;
        layers.push_back(layer);
        return layer;
    }

    void addLayerToIter(Layer *layer) {
        iter->items = g_list_append(iter->items, layer);
    }

    PopplerLayersIter *iter;
    std::vector<Layer *> layers;
};

// Test that passing nullptr returns NULL
TEST_F(PopplerLayersIterTest_2250, NullIterReturnsNull_2250) {
    gchar *result = poppler_layers_iter_get_title(nullptr);
    EXPECT_EQ(result, nullptr);
}

// Test normal operation with a valid label at index 0
TEST_F(PopplerLayersIterTest_2250, ValidLabelReturnsTitle_2250) {
    createIter();
    Layer *layer = createLayer("Test Layer");
    addLayerToIter(layer);
    iter->index = 0;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Test Layer");
    // Verify it's a copy, not the same pointer
    EXPECT_NE(result, layer->label);
    g_free(result);
}

// Test that a layer with a null label returns nullptr
TEST_F(PopplerLayersIterTest_2250, NullLabelReturnsNull_2250) {
    createIter();
    Layer *layer = createLayer(nullptr);
    addLayerToIter(layer);
    iter->index = 0;

    gchar *result = poppler_layers_iter_get_title(iter);
    EXPECT_EQ(result, nullptr);
}

// Test with multiple layers, selecting a specific index
TEST_F(PopplerLayersIterTest_2250, MultipleLayersCorrectIndex_2250) {
    createIter();
    Layer *layer0 = createLayer("First Layer");
    Layer *layer1 = createLayer("Second Layer");
    Layer *layer2 = createLayer("Third Layer");
    addLayerToIter(layer0);
    addLayerToIter(layer1);
    addLayerToIter(layer2);
    iter->index = 1;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Second Layer");
    g_free(result);
}

// Test with multiple layers, selecting the last index
TEST_F(PopplerLayersIterTest_2250, LastIndexReturnsCorrectTitle_2250) {
    createIter();
    Layer *layer0 = createLayer("First");
    Layer *layer1 = createLayer("Second");
    Layer *layer2 = createLayer("Third");
    addLayerToIter(layer0);
    addLayerToIter(layer1);
    addLayerToIter(layer2);
    iter->index = 2;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Third");
    g_free(result);
}

// Test that the returned string is a duplicate (modifying it doesn't affect original)
TEST_F(PopplerLayersIterTest_2250, ReturnedStringIsACopy_2250) {
    createIter();
    Layer *layer = createLayer("Original Title");
    addLayerToIter(layer);
    iter->index = 0;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Original Title");

    // Modify the returned string
    result[0] = 'X';

    // Original should be unchanged
    EXPECT_STREQ(layer->label, "Original Title");
    g_free(result);
}

// Test with an empty label string
TEST_F(PopplerLayersIterTest_2250, EmptyLabelReturnsEmptyString_2250) {
    createIter();
    Layer *layer = createLayer("");
    addLayerToIter(layer);
    iter->index = 0;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "");
    g_free(result);
}

// Test with a label containing special characters
TEST_F(PopplerLayersIterTest_2250, SpecialCharactersInLabel_2250) {
    createIter();
    Layer *layer = createLayer("Layer with spëcial chars: αβγ & <tag>");
    addLayerToIter(layer);
    iter->index = 0;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, "Layer with spëcial chars: αβγ & <tag>");
    g_free(result);
}

// Test with multiple layers where some have null labels
TEST_F(PopplerLayersIterTest_2250, MixedNullAndValidLabels_2250) {
    createIter();
    Layer *layer0 = createLayer("Valid");
    Layer *layer1 = createLayer(nullptr);
    Layer *layer2 = createLayer("Also Valid");
    addLayerToIter(layer0);
    addLayerToIter(layer1);
    addLayerToIter(layer2);

    iter->index = 0;
    gchar *result0 = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result0, nullptr);
    EXPECT_STREQ(result0, "Valid");
    g_free(result0);

    iter->index = 1;
    gchar *result1 = poppler_layers_iter_get_title(iter);
    EXPECT_EQ(result1, nullptr);

    iter->index = 2;
    gchar *result2 = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result2, nullptr);
    EXPECT_STREQ(result2, "Also Valid");
    g_free(result2);
}

// Test with a very long label
TEST_F(PopplerLayersIterTest_2250, VeryLongLabel_2250) {
    createIter();
    std::string longLabel(10000, 'A');
    Layer *layer = createLayer(longLabel.c_str());
    addLayerToIter(layer);
    iter->index = 0;

    gchar *result = poppler_layers_iter_get_title(iter);
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result, longLabel.c_str());
    EXPECT_EQ(strlen(result), 10000u);
    g_free(result);
}
