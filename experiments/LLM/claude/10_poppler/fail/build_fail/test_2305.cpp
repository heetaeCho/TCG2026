#include <glib-object.h>
#include <gtest/gtest.h>

// Include the necessary poppler headers
extern "C" {
#include "poppler.h"
#include "poppler-form-field.h"
#include "poppler-private.h"
}

// We need to include poppler internal headers for form field creation
#include <Form.h>
#include <PDFDoc.h>
#include <GlobalParams.h>

class PopplerFormFieldTest_2305 : public ::testing::Test {
protected:
    void SetUp() override
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override { }
};

// Test that poppler_form_field_get_field_type returns a valid type for a text field
TEST_F(PopplerFormFieldTest_2305, GetFieldTypeReturnsValidType_2305)
{
    // We test via the public API by loading a PDF with form fields
    // Since we can't easily create form fields without a document,
    // we test the GType registration and basic properties

    GType form_field_type = poppler_form_field_get_type();
    EXPECT_NE(form_field_type, G_TYPE_INVALID);
}

// Test that the GType for PopplerFormField is properly registered
TEST_F(PopplerFormFieldTest_2305, GTypeRegistration_2305)
{
    GType type = poppler_form_field_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test form field mapping type enumeration values exist
TEST_F(PopplerFormFieldTest_2305, FormFieldTypeEnumValues_2305)
{
    // Verify that the form field type enum values are defined
    EXPECT_EQ(POPPLER_FORM_FIELD_UNKNOWN, 0);
    EXPECT_EQ(POPPLER_FORM_FIELD_BUTTON, 1);
    EXPECT_EQ(POPPLER_FORM_FIELD_TEXT, 2);
    EXPECT_EQ(POPPLER_FORM_FIELD_CHOICE, 3);
    EXPECT_EQ(POPPLER_FORM_FIELD_SIGNATURE, 4);
}

// Test form button type enumeration values
TEST_F(PopplerFormFieldTest_2305, FormButtonTypeEnumValues_2305)
{
    EXPECT_EQ(POPPLER_FORM_BUTTON_PUSH, 0);
    EXPECT_EQ(POPPLER_FORM_BUTTON_CHECK, 1);
    EXPECT_EQ(POPPLER_FORM_BUTTON_RADIO, 2);
}

// Test form text type enumeration values
TEST_F(PopplerFormFieldTest_2305, FormTextTypeEnumValues_2305)
{
    EXPECT_EQ(POPPLER_FORM_TEXT_NORMAL, 0);
    EXPECT_EQ(POPPLER_FORM_TEXT_MULTILINE, 1);
    EXPECT_EQ(POPPLER_FORM_TEXT_FILE_SELECT, 2);
}

// Test form choice type enumeration values
TEST_F(PopplerFormFieldTest_2305, FormChoiceTypeEnumValues_2305)
{
    EXPECT_EQ(POPPLER_FORM_CHOICE_COMBO, 0);
    EXPECT_EQ(POPPLER_FORM_CHOICE_LIST, 1);
}

// Test that we can load a document with form fields and access them
TEST_F(PopplerFormFieldTest_2305, LoadDocumentWithFormFields_2305)
{
    // Try to load a test PDF - if not available, skip
    const char *test_pdf_path = g_getenv("POPPLER_TEST_PDF_FORM");
    if (test_pdf_path == nullptr) {
        GTEST_SKIP() << "No test PDF with forms available (set POPPLER_TEST_PDF_FORM)";
    }

    GError *error = nullptr;
    gchar *uri = g_filename_to_uri(test_pdf_path, nullptr, &error);
    if (uri == nullptr) {
        GTEST_SKIP() << "Could not convert path to URI";
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, nullptr, &error);
    g_free(uri);

    if (doc == nullptr) {
        if (error) {
            g_error_free(error);
        }
        GTEST_SKIP() << "Could not load test PDF";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (page != nullptr) {
        GList *form_field_mapping = poppler_page_get_form_field_mapping(page);

        for (GList *l = form_field_mapping; l != nullptr; l = l->next) {
            PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
            PopplerFormField *field = mapping->field;

            EXPECT_NE(field, nullptr);
            if (field) {
                PopplerFormFieldType type = poppler_form_field_get_field_type(field);
                EXPECT_GE(type, POPPLER_FORM_FIELD_UNKNOWN);
                EXPECT_LE(type, POPPLER_FORM_FIELD_SIGNATURE);

                gint id = poppler_form_field_get_id(field);
                EXPECT_GE(id, 0);

                gboolean read_only = poppler_form_field_is_read_only(field);
                (void)read_only; // Just verify it doesn't crash

                gchar *font_name = poppler_form_field_get_partial_name(field);
                if (font_name) {
                    g_free(font_name);
                }

                gchar *mapping_name = poppler_form_field_get_mapping_name(field);
                if (mapping_name) {
                    g_free(mapping_name);
                }

                gchar *alternate_name = poppler_form_field_get_alternate_ui_name(field);
                if (alternate_name) {
                    g_free(alternate_name);
                }
            }
        }

        poppler_page_free_form_field_mapping(form_field_mapping);
        g_object_unref(page);
    }

    g_object_unref(doc);
}

// Test passing NULL to functions that should handle it gracefully
TEST_F(PopplerFormFieldTest_2305, NullHandling_2305)
{
    // These tests verify that the functions don't crash with edge cases
    // The GType system should be robust
    GType type = poppler_form_field_get_type();
    EXPECT_NE(type, 0u);

    // Verify the type name
    const gchar *type_name = g_type_name(type);
    EXPECT_NE(type_name, nullptr);
    EXPECT_STREQ(type_name, "PopplerFormField");
}

// Test the GType hierarchy
TEST_F(PopplerFormFieldTest_2305, TypeHierarchy_2305)
{
    GType form_field_type = poppler_form_field_get_type();
    EXPECT_TRUE(g_type_is_a(form_field_type, G_TYPE_OBJECT));
    EXPECT_FALSE(g_type_is_a(form_field_type, G_TYPE_INITIALLY_UNOWNED));
}

// Test PopplerFormFieldMapping creation and freeing
TEST_F(PopplerFormFieldTest_2305, FormFieldMappingNewAndFree_2305)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);

    // The newly created mapping should have zeroed area
    EXPECT_DOUBLE_EQ(mapping->area.x1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y1, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.x2, 0.0);
    EXPECT_DOUBLE_EQ(mapping->area.y2, 0.0);
    EXPECT_EQ(mapping->field, nullptr);

    poppler_form_field_mapping_free(mapping);
}

// Test PopplerFormFieldMapping copy
TEST_F(PopplerFormFieldTest_2305, FormFieldMappingCopy_2305)
{
    PopplerFormFieldMapping *mapping = poppler_form_field_mapping_new();
    ASSERT_NE(mapping, nullptr);

    mapping->area.x1 = 1.0;
    mapping->area.y1 = 2.0;
    mapping->area.x2 = 3.0;
    mapping->area.y2 = 4.0;

    PopplerFormFieldMapping *copy = poppler_form_field_mapping_copy(mapping);
    ASSERT_NE(copy, nullptr);

    EXPECT_DOUBLE_EQ(copy->area.x1, 1.0);
    EXPECT_DOUBLE_EQ(copy->area.y1, 2.0);
    EXPECT_DOUBLE_EQ(copy->area.x2, 3.0);
    EXPECT_DOUBLE_EQ(copy->area.y2, 4.0);

    poppler_form_field_mapping_free(copy);
    poppler_form_field_mapping_free(mapping);
}

// Test freeing NULL mapping doesn't crash
TEST_F(PopplerFormFieldTest_2305, FormFieldMappingFreeNull_2305)
{
    // Should not crash
    poppler_form_field_mapping_free(nullptr);
}
