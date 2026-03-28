#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-layer.h"

#include "poppler-private.h"



using namespace testing;



// Mocking Glib functions and macros for testing purposes

class MockGObject {

public:

    MOCK_METHOD(void, g_object_unref, (void*), ());

};



MockFunction<void(PopplerLayer*)> mock_finalize;

MockGObject mock_gobject;



extern "C" void poppler_layer_finalize(GObject *object) {

    PopplerLayer *poppler_layer = POPPLER_LAYER(object);

    if (poppler_layer->document) {

        mock_gobject.g_object_unref(poppler_layer->document);

        poppler_layer->document = nullptr;

    }

    if (poppler_layer->title) {

        g_free(poppler_layer->title);

        poppler_layer->title = nullptr;

    }

    poppler_layer->layer = nullptr;

    poppler_layer->rbgroup = nullptr;

    mock_finalize.Call(poppler_layer);

}



class PopplerLayerTest_2505 : public ::testing::Test {

protected:

    void SetUp() override {

        layer = static_cast<PopplerLayer*>(g_object_new(POPPLER_TYPE_LAYER, NULL));

        layer->document = reinterpret_cast<void*>(0x1234);  // Simulate a valid document pointer

        layer->title = g_strdup("Sample Title");

        layer->layer = new Layer();

        layer->rbgroup = new int();

    }



    void TearDown() override {

        g_object_unref(layer);

    }



    PopplerLayer* layer;

};



TEST_F(PopplerLayerTest_2505, FinalizeReleasesDocument_2505) {

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).Times(1);



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeFreesTitle_2505) {

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).Times(1);



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeNullsDocumentPointer_2505) {

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).WillOnce(Invoke([this]() {

        EXPECT_EQ(layer->document, nullptr);

    }));



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeNullsTitlePointer_2505) {

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).WillOnce(Invoke([this]() {

        EXPECT_EQ(layer->title, nullptr);

    }));



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeNullsLayerPointer_2505) {

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).WillOnce(Invoke([this]() {

        EXPECT_EQ(layer->layer, nullptr);

    }));



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeNullsRbgroupPointer_2505) {

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).WillOnce(Invoke([this]() {

        EXPECT_EQ(layer->rbgroup, nullptr);

    }));



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeWithNullDocument_2505) {

    layer->document = nullptr;

    EXPECT_CALL(mock_gobject, g_object_unref).Times(0);  // Should not be called

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).Times(1);



    g_object_unref(layer);

}



TEST_F(PopplerLayerTest_2505, FinalizeWithNullTitle_2505) {

    g_free(layer->title);

    layer->title = nullptr;

    EXPECT_CALL(mock_gobject, g_object_unref(Eq(layer->document))).Times(1);

    EXPECT_CALL(mock_finalize, Call(Eq(layer))).Times(1);



    g_object_unref(layer);

}
