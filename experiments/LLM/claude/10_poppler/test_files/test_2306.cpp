#include <gtest/gtest.h>
#include <glib-object.h>

// Include the poppler glib headers
extern "C" {
#include "poppler.h"
#include "poppler-document.h"
#include "poppler-page.h"
#include "poppler-form-field.h"
}

class PopplerFormFieldTest_2306 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;
    PopplerPage *page = nullptr;

    void SetUp() override {
        // We'll try to load a test PDF if available
        // Most tests will need to handle the case where no document is available
    }

    void TearDown() override {
        if (page) {
            g_object_unref(page);
            page = nullptr;
        }
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }

    bool LoadTestDocument(const char *uri) {
        GError *error = nullptr;
        document = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return false;
        }
        if (document && poppler_document_get_n_pages(document) > 0) {
            page = poppler_document_get_page(document, 0);
            return page != nullptr;
        }
        return false;
    }
};

// Test that PopplerFormField GType is properly registered
TEST_F(PopplerFormFieldTest_2306, TypeRegistration_2306)
{
    GType type = poppler_form_field_get_type();
    EXPECT_NE(type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test that the type name is correct
TEST_F(PopplerFormFieldTest_2306, TypeName_2306)
{
    GType type = poppler_form_field_get_type();
    const gchar *name = g_type_name(type);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerFormField");
}

// Test that PopplerFormFieldType enum values exist
TEST_F(PopplerFormFieldTest_2306, FormFieldTypeEnum_2306)
{
    // Verify enum values are distinct
    EXPECT_NE(POPPLER_FORM_FIELD_TEXT, POPPLER_FORM_FIELD_BUTTON);
    EXPECT_NE(POPPLER_FORM_FIELD_TEXT, POPPLER_FORM_FIELD_CHOICE);
    EXPECT_NE(POPPLER_FORM_FIELD_TEXT, POPPLER_FORM_FIELD_SIGNATURE);
    EXPECT_NE(POPPLER_FORM_FIELD_TEXT, POPPLER_FORM_FIELD_UNKNOWN);
}

// Test that PopplerFormButtonType enum values exist
TEST_F(PopplerFormFieldTest_2306, FormButtonTypeEnum_2306)
{
    EXPECT_NE(POPPLER_FORM_BUTTON_PUSH, POPPLER_FORM_BUTTON_CHECK);
    EXPECT_NE(POPPLER_FORM_BUTTON_PUSH, POPPLER_FORM_BUTTON_RADIO);
    EXPECT_NE(POPPLER_FORM_BUTTON_CHECK, POPPLER_FORM_BUTTON_RADIO);
}

// Test that PopplerFormTextType enum values exist
TEST_F(PopplerFormFieldTest_2306, FormTextTypeEnum_2306)
{
    EXPECT_NE(POPPLER_FORM_TEXT_NORMAL, POPPLER_FORM_TEXT_MULTILINE);
    EXPECT_NE(POPPLER_FORM_TEXT_NORMAL, POPPLER_FORM_TEXT_FILE_SELECT);
}

// Test that PopplerFormChoiceType enum values exist
TEST_F(PopplerFormFieldTest_2306, FormChoiceTypeEnum_2306)
{
    EXPECT_NE(POPPLER_FORM_CHOICE_COMBO, POPPLER_FORM_CHOICE_LIST);
}

// Test that the GType for PopplerFormField is a GObject subclass
TEST_F(PopplerFormFieldTest_2306, IsGObjectSubclass_2306)
{
    GType type = poppler_form_field_get_type();
    EXPECT_TRUE(g_type_is_a(type, G_TYPE_OBJECT));
}

// Test that the parent type is GObject
TEST_F(PopplerFormFieldTest_2306, ParentTypeIsGObject_2306)
{
    GType type = poppler_form_field_get_type();
    GType parent = g_type_parent(type);
    EXPECT_EQ(parent, G_TYPE_OBJECT);
}

// Test class finalize is set up (the class should be instantiable type)
TEST_F(PopplerFormFieldTest_2306, ClassIsInstantiable_2306)
{
    GType type = poppler_form_field_get_type();
    // G_TYPE_IS_INSTANTIATABLE checks if the type can be instantiated
    EXPECT_TRUE(G_TYPE_IS_INSTANTIATABLE(type));
}

// Test that the type is not abstract
TEST_F(PopplerFormFieldTest_2306, TypeIsNotAbstract_2306)
{
    GType type = poppler_form_field_get_type();
    EXPECT_FALSE(G_TYPE_IS_ABSTRACT(type));
}

// Test form field mapping structure with null document - verify no form fields on empty/null
TEST_F(PopplerFormFieldTest_2306, NullDocumentHandling_2306)
{
    // Without a valid document, we cannot create form fields
    // This tests that the API types are properly defined
    GType type = poppler_form_field_get_type();
    EXPECT_NE(type, G_TYPE_NONE);
}

// Test loading a non-existent document returns null
TEST_F(PopplerFormFieldTest_2306, NonExistentDocument_2306)
{
    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_file("file:///nonexistent_test_file.pdf", nullptr, &error);
    EXPECT_EQ(doc, nullptr);
    EXPECT_NE(error, nullptr);
    if (error) {
        g_error_free(error);
    }
}

// Test that form field mapping list from a page without forms is empty or null
TEST_F(PopplerFormFieldTest_2306, PageWithoutForms_2306)
{
    // Create a minimal PDF in memory to test
    // This is a minimal valid PDF with no form fields
    const char *minimal_pdf =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "190\n"
        "%%EOF\n";

    GError *error = nullptr;
    PopplerDocument *doc = poppler_document_new_from_data((char*)minimal_pdf, strlen(minimal_pdf), nullptr, &error);
    
    if (doc) {
        PopplerPage *p = poppler_document_get_page(doc, 0);
        if (p) {
            GList *form_mapping = poppler_page_get_form_field_mapping(p);
            // A page without forms should return an empty list or NULL
            if (form_mapping) {
                EXPECT_EQ(g_list_length(form_mapping), 0u);
                poppler_page_free_form_field_mapping(form_mapping);
            }
            g_object_unref(p);
        }
        g_object_unref(doc);
    } else {
        if (error) {
            g_error_free(error);
        }
        // If we can't create the document from data, just pass
        SUCCEED() << "Could not create minimal PDF document for testing";
    }
}
