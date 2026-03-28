#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <poppler/poppler-document-private.h>

#include <poppler/poppler-action.h>



using namespace testing;



class PopplerLayer {

public:

    _PopplerDocument* document;

    Layer* layer;

    GList* rb_group;



    // Mock constructor for testing

    PopplerLayer(_PopplerDocument* doc, Layer* lay, GList* group)

        : document(doc), layer(lay), rb_group(group) {}

};



class PopplerActionTest_2301 : public ::testing::Test {

protected:

    void SetUp() override {

        // Initialize necessary objects for testing

        document = new _PopplerDocument();

        layer_with_oc = new Layer();

        layer_without_oc = new Layer();

        ref_valid = {1, 0};

        ref_invalid = Ref::INVALID();



        // Set up valid and invalid layers

        layer_with_oc->oc = new OptionalContentGroup(ref_valid);

        layer_without_oc->oc = nullptr;



        // Create a GList of layers for testing

        layers = g_list_append(layers, static_cast<gpointer>(layer_with_oc));

        layers = g_list_append(layers, static_cast<gpointer>(layer_without_oc));

    }



    void TearDown() override {

        // Clean up allocated memory

        g_list_free_full(layers, g_free);

        delete document;

        delete layer_with_oc->oc;

        delete layer_with_oc;

        delete layer_without_oc;

    }



    _PopplerDocument* document;

    Layer* layer_with_oc;

    Layer* layer_without_oc;

    Ref ref_valid;

    Ref ref_invalid;

    GList* layers = nullptr;

};



TEST_F(PopplerActionTest_2301, GetLayerForRef_ValidRef_PreservesRBGroup_2301) {

    // Test with a valid reference and preserve_rb set to TRUE

    auto* result = get_layer_for_ref(document, layers, ref_valid, TRUE);

    ASSERT_NE(result, nullptr);

}



TEST_F(PopplerActionTest_2301, GetLayerForRef_ValidRef_DoesNotPreserveRBGroup_2301) {

    // Test with a valid reference and preserve_rb set to FALSE

    auto* result = get_layer_for_ref(document, layers, ref_valid, FALSE);

    ASSERT_NE(result, nullptr);

}



TEST_F(PopplerActionTest_2301, GetLayerForRef_InvalidRef_ReturnsNull_2301) {

    // Test with an invalid reference

    auto* result = get_layer_for_ref(document, layers, ref_invalid, TRUE);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerActionTest_2301, GetLayerForRef_EmptyLayersList_ReturnsNull_2301) {

    // Test with an empty list of layers

    GList* empty_layers = nullptr;

    auto* result = get_layer_for_ref(document, empty_layers, ref_valid, TRUE);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerActionTest_2301, GetLayerForRef_LayerWithoutOC_ReturnsNull_2301) {

    // Test with a layer that does not have OC

    auto* result = get_layer_for_ref(document, layers, Ref{2, 0}, TRUE);

    ASSERT_EQ(result, nullptr);

}



TEST_F(PopplerActionTest_2301, GetLayerForRef_DeepNestedLayers_ReturnsCorrectLayer_2301) {

    // Test with nested layers

    Layer* child_layer = new Layer();

    child_layer->oc = new OptionalContentGroup(ref_valid);

    layer_with_oc->kids = g_list_append(layer_with_oc->kids, static_cast<gpointer>(child_layer));



    auto* result = get_layer_for_ref(document, layers, ref_valid, TRUE);

    ASSERT_NE(result, nullptr);



    // Clean up nested layer

    delete child_layer->oc;

    delete child_layer;

}
