#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-document.h"

#include "poppler-private.h"



// Mock GError structure for testing error handling

class MockGError {

public:

    static void reset(GError **error) {

        if (*error) {

            g_error_free(*error);

            *error = nullptr;

        }

    }



    static void set(GError **error, int code, const char *message) {

        reset(error);

        *error = g_error_new(g_quark_from_static_string("MockQuark"), code, "%s", message);

    }

};



// Mock PopplerDocument for testing external interactions

class MockPopplerDocument : public _PopplerDocument {

public:

    MOCK_METHOD(int, saveWithoutChangesAs, (const std::string&), ());

};



TEST_F(PopplerDocumentTest_2147, SaveACopyWithValidUri_2147) {

    GError *error = nullptr;

    MockPopplerDocument mock_doc;



    EXPECT_CALL(mock_doc, saveWithoutChangesAs(::testing::_)).WillOnce(::testing::Return(0));



    gboolean result = poppler_document_save_a_copy(&mock_doc, "file:///path/to/document.pdf", &error);

    ASSERT_TRUE(result);

    MockGError::reset(&error);

}



TEST_F(PopplerDocumentTest_2147, SaveACopyWithInvalidUri_2147) {

    GError *error = nullptr;

    PopplerDocument mock_doc;



    gboolean result = poppler_document_save_a_copy(&mock_doc, "invalid_uri", &error);

    ASSERT_FALSE(result);

    ASSERT_NE(error, nullptr);

    MockGError::reset(&error);

}



TEST_F(PopplerDocumentTest_2147, SaveACopyWithNullUri_2147) {

    GError *error = nullptr;

    PopplerDocument mock_doc;



    gboolean result = poppler_document_save_a_copy(&mock_doc, nullptr, &error);

    ASSERT_FALSE(result);

    MockGError::reset(&error);

}



TEST_F(PopplerDocumentTest_2147, SaveACopyWithNonNullErrorPointer_2147) {

    GError *error = nullptr;

    MockPopplerDocument mock_doc;



    EXPECT_CALL(mock_doc, saveWithoutChangesAs(::testing::_)).WillOnce(::testing::Return(-1));

    MockGError::set(&error, 1, "Mock error message");



    gboolean result = poppler_document_save_a_copy(&mock_doc, "file:///path/to/document.pdf", &error);

    ASSERT_FALSE(result);

    ASSERT_NE(error, nullptr);

    MockGError::reset(&error);

}



TEST_F(PopplerDocumentTest_2147, SaveACopyWithNonPopplerDocumentPointer_2147) {

    GError *error = nullptr;

    void *non_poppler_doc = reinterpret_cast<void*>(new int(0));



    gboolean result = poppler_document_save_a_copy(static_cast<PopplerDocument*>(non_poppler_doc), "file:///path/to/document.pdf", &error);

    ASSERT_FALSE(result);

    MockGError::reset(&error);

    delete static_cast<int*>(non_poppler_doc);

}
