#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "poppler-form-field.h"

#include "poppler-private.h"

#include <gio/gio.h>



using namespace testing;



class PopplerFormFieldSignatureValidateSyncTest_2322 : public Test {

protected:

    void SetUp() override {

        field = reinterpret_cast<PopplerFormField*>(g_object_new(G_TYPE_OBJECT, nullptr));

        cancellable = g_cancellable_new();

        error = nullptr;

    }



    void TearDown() override {

        if (field) {

            g_object_unref(field);

        }

        if (cancellable) {

            g_object_unref(cancellable);

        }

        if (error) {

            g_error_free(error);

        }

    }



    PopplerFormField* field;

    GCancellable* cancellable;

    GError** error;

};



TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, ValidateNormalOperation_2322) {

    PopplerSignatureInfo* signature_info = poppler_form_field_signature_validate_sync(field, POPPLER_SIGNATURE_VALIDATION_FLAG_NONE, cancellable, &error);

    EXPECT_TRUE(signature_info != nullptr || error != nullptr); // Either a valid result or an error should be returned

    if (signature_info) {

        g_object_unref(signature_info);

    }

}



TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, ValidateWithFlags_2322) {

    PopplerSignatureValidationFlags flags = POPPLER_SIGNATURE_VALIDATION_FLAG_CHECK_CERTIFICATE;

    PopplerSignatureInfo* signature_info = poppler_form_field_signature_validate_sync(field, flags, cancellable, &error);

    EXPECT_TRUE(signature_info != nullptr || error != nullptr); // Either a valid result or an error should be returned

    if (signature_info) {

        g_object_unref(signature_info);

    }

}



TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, ValidateWithCancellable_2322) {

    g_cancellable_cancel(cancellable);

    PopplerSignatureInfo* signature_info = poppler_form_field_signature_validate_sync(field, POPPLER_SIGNATURE_VALIDATION_FLAG_NONE, cancellable, &error);

    EXPECT_TRUE(signature_info == nullptr); // Operation should be cancelled

    EXPECT_EQ(error, nullptr); // No error should be returned on cancellation

}



TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, ValidateWithError_2322) {

    PopplerSignatureInfo* signature_info = poppler_form_field_signature_validate_sync(nullptr, POPPLER_SIGNATURE_VALIDATION_FLAG_NONE, cancellable, &error);

    EXPECT_TRUE(signature_info == nullptr); // Invalid input should result in null

    EXPECT_NE(error, nullptr); // Error should be set for invalid input

    g_error_free(error);

    error = nullptr;

}



TEST_F(PopplerFormFieldSignatureValidateSyncTest_2322, ValidateWithNonNullErrorPointer_2322) {

    GError* local_error = nullptr;

    PopplerSignatureInfo* signature_info = poppler_form_field_signature_validate_sync(field, POPPLER_SIGNATURE_VALIDATION_FLAG_NONE, cancellable, &local_error);

    EXPECT_TRUE(signature_info != nullptr || local_error != nullptr); // Either a valid result or an error should be returned

    if (signature_info) {

        g_object_unref(signature_info);

    }

    if (local_error) {

        g_error_free(local_error);

    }

}
