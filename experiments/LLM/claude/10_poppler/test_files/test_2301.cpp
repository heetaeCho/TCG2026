#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
#include "poppler-document.h"
#include "poppler-layer.h"
#include "poppler-action.h"
#include "poppler-private.h"
#include "Object.h"

#include <glib.h>

// Since get_layer_for_ref is a static function in poppler-action.cc,
// we include the source file to access it for testing purposes.
// This is a common technique for testing static functions.
#include "poppler-action.cc"

class GetLayerForRefTest_2301 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that nullptr/NULL is returned when layers list is NULL
TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenLayersListIsNull_2301)
{
    Ref ref;
    ref.num = 1;
    ref.gen = 0;

    PopplerLayer *result = get_layer_for_ref(nullptr, nullptr, ref, FALSE);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when layers list is empty
TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenLayersListIsEmpty_2301)
{
    Ref ref;
    ref.num = 1;
    ref.gen = 0;

    GList *empty_list = nullptr; // GList NULL is empty
    PopplerLayer *result = get_layer_for_ref(nullptr, empty_list, ref, FALSE);
    EXPECT_EQ(result, nullptr);
}

// Test that nullptr is returned when no matching ref is found in layers
TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenNoMatchingRefFound_2301)
{
    Ref ref;
    ref.num = 99;
    ref.gen = 99;

    // Create a Layer with no oc and no kids
    Layer layer;
    layer.oc = nullptr;
    layer.kids = nullptr;

    GList *layers = nullptr;
    layers = g_list_append(layers, &layer);

    PopplerLayer *result = get_layer_for_ref(nullptr, layers, ref, FALSE);
    EXPECT_EQ(result, nullptr);

    g_list_free(layers);
}

// Test that nullptr is returned when layer has no oc and no kids
TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenLayerHasNoOcAndNoKids_2301)
{
    Ref ref;
    ref.num = 1;
    ref.gen = 0;

    Layer layer;
    layer.oc = nullptr;
    layer.kids = nullptr;

    GList *layers = nullptr;
    layers = g_list_append(layers, &layer);

    PopplerLayer *result = get_layer_for_ref(nullptr, layers, ref, FALSE);
    EXPECT_EQ(result, nullptr);

    g_list_free(layers);
}

// Test with multiple layers none matching
TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenMultipleLayersNoneMatch_2301)
{
    Ref ref;
    ref.num = 50;
    ref.gen = 50;

    Layer layer1;
    layer1.oc = nullptr;
    layer1.kids = nullptr;

    Layer layer2;
    layer2.oc = nullptr;
    layer2.kids = nullptr;

    GList *layers = nullptr;
    layers = g_list_append(layers, &layer1);
    layers = g_list_append(layers, &layer2);

    PopplerLayer *result = get_layer_for_ref(nullptr, layers, ref, FALSE);
    EXPECT_EQ(result, nullptr);

    g_list_free(layers);
}

// Test recursive search returns null when kids also don't match
TEST_F(GetLayerForRefTest_2301, ReturnsNullWhenKidsDontMatch_2301)
{
    Ref ref;
    ref.num = 100;
    ref.gen = 100;

    Layer kid_layer;
    kid_layer.oc = nullptr;
    kid_layer.kids = nullptr;

    GList *kids = nullptr;
    kids = g_list_append(kids, &kid_layer);

    Layer parent_layer;
    parent_layer.oc = nullptr;
    parent_layer.kids = kids;

    GList *layers = nullptr;
    layers = g_list_append(layers, &parent_layer);

    PopplerLayer *result = get_layer_for_ref(nullptr, layers, ref, FALSE);
    EXPECT_EQ(result, nullptr);

    g_list_free(kids);
    g_list_free(layers);
}
