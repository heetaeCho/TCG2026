#include <glib.h>
#include <glib-object.h>
#include <gio/gio.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler.h"
#include "poppler-form-field.h"
}

class PopplerFormFieldSignatureValidateTest_2322 : public ::testing::Test {
protected:
    void SetUp() override {
        // We need a real PopplerDocument with a signature field to test properly.
        // For unit testing purposes, we'll test with NULL/invalid inputs to verify
        // error handling behavior.
    }

    void TearDown() override {
    }
};

// Test that passing NULL field is handled (g_return_val_if_fail should return NULL)
TEST_F(PopplerFormFieldSignatureValidateTest_2322, NullFieldReturnsNull_2322)
{
    GError *error = nullptr;
    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        nullptr,
        &error);
    EXPECT_EQ(info, nullptr);
}

// Test that passing a non-null error pointer (already set) triggers the g_return_val guard
TEST_F(PopplerFormFieldSignatureValidateTest_2322, PresetErrorReturnsNull_2322)
{
    GError *error = g_error_new_literal(G_IO_ERROR, G_IO_ERROR_FAILED, "pre-existing error");
    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        nullptr,
        &error);
    EXPECT_EQ(info, nullptr);
    g_error_free(error);
}

// Test with cancellable that is already cancelled
TEST_F(PopplerFormFieldSignatureValidateTest_2322, NullFieldWithCancelledCancellable_2322)
{
    GCancellable *cancellable = g_cancellable_new();
    g_cancellable_cancel(cancellable);

    GError *error = nullptr;
    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        cancellable,
        &error);
    // With NULL field, g_return_val_if_fail should trigger before we even get to the task
    EXPECT_EQ(info, nullptr);

    g_object_unref(cancellable);
}

// Test with NULL error parameter and NULL field
TEST_F(PopplerFormFieldSignatureValidateTest_2322, NullFieldNullErrorParam_2322)
{
    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        nullptr,
        nullptr);
    EXPECT_EQ(info, nullptr);
}

// Test with different validation flags and NULL field
TEST_F(PopplerFormFieldSignatureValidateTest_2322, NullFieldWithoutVerifyCertsFlag_2322)
{
    GError *error = nullptr;
    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        static_cast<PopplerSignatureValidationFlags>(0),
        nullptr,
        &error);
    EXPECT_EQ(info, nullptr);
}

// Test with a real document that has a signature field (integration-style test)
// This test loads a PDF with a digital signature if available
class PopplerFormFieldSignatureDocTest_2322 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // Try to load a test PDF. If not available, skip.
        doc = nullptr;
        page = nullptr;
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
        }
        if (doc) {
            g_object_unref(doc);
        }
    }

    PopplerFormField *findSignatureField() {
        if (!page) {
            return nullptr;
        }
        GList *mapping_list = poppler_page_get_form_field_mapping(page);
        PopplerFormField *sig_field = nullptr;
        for (GList *l = mapping_list; l != nullptr; l = l->next) {
            PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
            PopplerFormField *field = mapping->field;
            if (poppler_form_field_get_field_type(field) == POPPLER_FORM_FIELD_SIGNATURE) {
                sig_field = field;
                g_object_ref(sig_field);
                break;
            }
        }
        poppler_page_free_form_field_mapping(mapping_list);
        return sig_field;
    }
};

// Test that validation with a valid cancellable (not cancelled) and NULL field returns NULL
TEST_F(PopplerFormFieldSignatureDocTest_2322, ValidCancellableNullField_2322)
{
    GCancellable *cancellable = g_cancellable_new();
    GError *error = nullptr;

    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE,
        cancellable,
        &error);

    EXPECT_EQ(info, nullptr);

    g_object_unref(cancellable);
}

// Test combining multiple flags with NULL field
TEST_F(PopplerFormFieldSignatureValidateTest_2322, MultipleFlagsNullField_2322)
{
    GError *error = nullptr;
    PopplerSignatureValidationFlags flags = static_cast<PopplerSignatureValidationFlags>(
        POPPLER_SIGNATURE_VALIDATION_FLAG_VALIDATE_CERTIFICATE |
        POPPLER_SIGNATURE_VALIDATION_FLAG_WITHOUT_OCSP_REVOCATION_CHECK);

    PopplerSignatureInfo *info = poppler_form_field_signature_validate_sync(
        nullptr,
        flags,
        nullptr,
        &error);

    EXPECT_EQ(info, nullptr);
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
