#include <glib-object.h>
#include <gtest/gtest.h>

// Include necessary headers
extern "C" {
#include "poppler-layer.h"
#include "poppler-private.h"
}

class PopplerLayerTest_2513 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that get_radio_button_group_id returns the correct group id when rbgroup is set to a positive value
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_PositiveValue_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    int group_id = 42;
    layer->rbgroup = GINT_TO_POINTER(group_id);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, 42);

    g_object_unref(layer);
}

// Test that get_radio_button_group_id returns 0 when rbgroup is NULL (0)
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_ZeroValue_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    layer->rbgroup = GINT_TO_POINTER(0);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, 0);

    g_object_unref(layer);
}

// Test that get_radio_button_group_id returns a negative value when rbgroup encodes a negative int
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_NegativeValue_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    layer->rbgroup = GINT_TO_POINTER(-5);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, -5);

    g_object_unref(layer);
}

// Test that get_radio_button_group_id returns 1 for rbgroup set to 1
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_ValueOne_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    layer->rbgroup = GINT_TO_POINTER(1);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, 1);

    g_object_unref(layer);
}

// Test that get_radio_button_group_id returns FALSE (0) when passed NULL
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_NullLayer_2513)
{
    // g_return_val_if_fail should cause it to return FALSE when NULL is passed
    gint result = poppler_layer_get_radio_button_group_id(NULL);
    EXPECT_EQ(result, FALSE);
}

// Test with a large positive group id
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_LargePositiveValue_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    int large_val = 999999;
    layer->rbgroup = GINT_TO_POINTER(large_val);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, large_val);

    g_object_unref(layer);
}

// Test with G_MAXINT boundary value
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_MaxInt_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    // Note: GINT_TO_POINTER may not preserve values larger than pointer size allows,
    // but G_MAXINT should be safe on most platforms
    layer->rbgroup = GINT_TO_POINTER(G_MAXINT);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, G_MAXINT);

    g_object_unref(layer);
}

// Test with G_MININT boundary value
TEST_F(PopplerLayerTest_2513, GetRadioButtonGroupId_MinInt_2513)
{
    PopplerLayer *layer = POPPLER_LAYER(g_object_new(POPPLER_TYPE_LAYER, NULL));
    ASSERT_NE(layer, nullptr);

    layer->rbgroup = GINT_TO_POINTER(G_MININT);

    gint result = poppler_layer_get_radio_button_group_id(layer);
    EXPECT_EQ(result, G_MININT);

    g_object_unref(layer);
}
