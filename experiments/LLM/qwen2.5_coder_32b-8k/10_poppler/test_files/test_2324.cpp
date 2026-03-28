#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <glib-object.h>

#include "poppler-form-field.cc"

#include "poppler-private.h"



// Mock GAsyncResult for testing purposes

class MockGAsyncResult : public GAsyncResult {

public:

    MOCK_METHOD(GObject*, get_source_object, (), (const));

};



// Mock GError for error handling in tests

class MockGError : public GError {

public:

    static void resetInstance() {

        if (instance) {

            g_error_free(instance);

            instance = nullptr;

        }

    }



    static GError* getInstance() {

        if (!instance) {

            instance = new GError();

        }

        return instance;

    }



private:

    static GError* instance;

};



GError* MockGError::instance = nullptr;



class PopplerSignatureInfoMock : public PopplerSignatureInfo {

public:

    MOCK_METHOD(void, someMethod, (), ());

};



// Fixture for setting up common test environment

class PopplerFormFieldTest_2324 : public ::testing::Test {

protected:

    void SetUp() override {

        field = new PopplerFormField();

        mock_result = new MockGAsyncResult();

        error = nullptr;

    }



    void TearDown() override {

        if (field) delete field;

        if (mock_result) g_object_unref(mock_result);

        MockGError::resetInstance();

    }



protected:

    PopplerFormField* field;

    MockGAsyncResult* mock_result;

    GError** error;

};



TEST_F(PopplerFormFieldTest_2324, ValidateFinish_SuccessfulValidation_2324) {

    // Arrange

    auto mock_signature_info = new PopplerSignatureInfoMock();

    g_task_return_pointer(G_TASK(mock_result), mock_signature_info, g_object_unref);



    // Act

    PopplerSignatureInfo* result = poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(mock_result), error);



    // Assert

    EXPECT_EQ(result, mock_signature_info);

}



TEST_F(PopplerFormFieldTest_2324, ValidateFinish_InvalidAsyncResult_2324) {

    // Arrange

    g_task_return_pointer(G_TASK(mock_result), nullptr, g_object_unref);



    // Act & Assert

    EXPECT_DEATH(poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(nullptr), error),

                 "g_return_val_if_fail\\(g_task_is_valid\\(result, field\\)\\)");

}



TEST_F(PopplerFormFieldTest_2324, ValidateFinish_ErrorPropagation_2324) {

    // Arrange

    error = &MockGError::getInstance();

    GQuark domain = g_quark_from_string("test-domain");

    g_task_return_new_error(G_TASK(mock_result), domain, 1, "Test Error");



    // Act

    PopplerSignatureInfo* result = poppler_form_field_signature_validate_finish(field, G_ASYNC_RESULT(mock_result), error);



    // Assert

    EXPECT_EQ(result, nullptr);

    ASSERT_TRUE(error && *error);

    EXPECT_EQ((*error)->domain, domain);

    EXPECT_EQ((*error)->code, 1);

    EXPECT_STREQ((*error)->message, "Test Error");

}
