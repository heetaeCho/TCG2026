#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"

#include "poppler-form-field.h"



using namespace testing;



class PopplerDocumentTest_2265 : public Test {

protected:

    void SetUp() override {

        document = reinterpret_cast<PopplerDocument*>(g_object_new(POPPLER_TYPE_DOCUMENT, nullptr));

        signing_data = new PopplerSigningData();

        memset(signing_data, 0, sizeof(PopplerSigningData));

    }



    void TearDown() override {

        g_clear_object(&document);

        poppler_signing_data_free(signing_data);

    }



    PopplerDocument *document;

    PopplerSigningData *signing_data;

};



class MockGAsyncReadyCallback : public testing::MockFunction<void(GObject*, GAsyncResult*, gpointer)> {};



TEST_F(PopplerDocumentTest_2265, SignWithValidData_2265) {

    MockGAsyncReadyCallback mock_callback;

    auto callback = reinterpret_cast<GAsyncReadyCallback>(mock_callback.AsStdFunction().target());



    poppler_document_sign(document, signing_data, nullptr, callback, nullptr);



    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

}



TEST_F(PopplerDocumentTest_2265, SignWithNullDocument_2265) {

    MockGAsyncReadyCallback mock_callback;

    auto callback = reinterpret_cast<GAsyncReadyCallback>(mock_callback.AsStdFunction().target());



    poppler_document_sign(nullptr, signing_data, nullptr, callback, nullptr);



    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(0);

}



TEST_F(PopplerDocumentTest_2265, SignWithNullSigningData_2265) {

    MockGAsyncReadyCallback mock_callback;

    auto callback = reinterpret_cast<GAsyncReadyCallback>(mock_callback.AsStdFunction().target());



    poppler_document_sign(document, nullptr, nullptr, callback, nullptr);



    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(0);

}



TEST_F(PopplerDocumentTest_2265, SignWithNonNullCancellable_2265) {

    MockGAsyncReadyCallback mock_callback;

    auto callback = reinterpret_cast<GAsyncReadyCallback>(mock_callback.AsStdFunction().target());

    GCancellable *cancellable = g_cancellable_new();



    poppler_document_sign(document, signing_data, cancellable, callback, nullptr);



    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

    g_object_unref(cancellable);

}



TEST_F(PopplerDocumentTest_2265, SignWithUserData_2265) {

    MockGAsyncReadyCallback mock_callback;

    auto callback = reinterpret_cast<GAsyncReadyCallback>(mock_callback.AsStdFunction().target());

    gpointer user_data = reinterpret_cast<gpointer>(new int(42));



    poppler_document_sign(document, signing_data, nullptr, callback, user_data);



    EXPECT_CALL(mock_callback, Call(_, _, _)).Times(1);

    delete reinterpret_cast<int*>(user_data);

}
