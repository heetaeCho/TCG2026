#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "poppler-form-field.h"
#include "poppler-private.h"
#include "Form.h"

// We need to mock FormWidget and FormWidgetChoice since we can't easily
// construct real PDF objects. We'll create mock classes that override
// the virtual methods we need.

// Mock for FormWidgetChoice to control isCombo() and getType()
class MockFormWidgetChoice : public FormWidgetChoice {
public:
    // We can't easily call the real constructor, so we use a trick:
    // We'll create a minimal mock that overrides the methods we need.
    // However, FormWidgetChoice requires PDFDoc, Object, etc.
    // Instead, let's create a simpler approach using a fake vtable approach.
    
    // Since constructing FormWidgetChoice requires complex PDF internals,
    // we'll use a different strategy: create a test double that just
    // provides the interface we need.
};

// Since we can't easily construct FormWidgetChoice objects without a real PDF,
// we'll create a minimal mock using a different approach.
// We'll create a class that mimics FormWidget's interface for testing.

class FakeFormWidget {
public:
    virtual ~FakeFormWidget() = default;
    virtual FormFieldType getType() = 0;
    virtual bool isCombo() = 0;
};

class FakeComboWidget : public FakeFormWidget {
public:
    FormFieldType getType() override { return formChoice; }
    bool isCombo() override { return true; }
};

class FakeListWidget : public FakeFormWidget {
public:
    FormFieldType getType() override { return formChoice; }
    bool isCombo() override { return false; }
};

class FakeNonChoiceWidget : public FakeFormWidget {
public:
    FormFieldType getType() override { return formText; }
    bool isCombo() override { return false; }
};

// To properly test the function, we need actual FormWidget/FormWidgetChoice objects.
// Since the function under test does:
//   1. g_return_val_if_fail(field->widget->getType() == formChoice, POPPLER_FORM_CHOICE_COMBO)
//   2. static_cast<FormWidgetChoice*>(field->widget)->isCombo()
//
// We need to create a proper mock that can be cast and used.
// The safest approach is to use a mock that inherits from FormWidgetChoice.

// However, since constructing FormWidgetChoice requires complex PDF structures,
// we'll test at a higher level by creating a real PDF document or by mocking
// at the right level.

// Alternative approach: We'll manually create objects with controlled memory layout.
// This is fragile but necessary given the constraints.

// Actually, the cleanest approach is to create a MockFormWidgetChoice that
// we can construct without a real PDF. Let's see if we can use GMock.

// Since we cannot easily instantiate FormWidgetChoice without PDFDoc,
// let's create a stub that inherits and overrides the needed methods.

// We need a way to create a FormWidgetChoice without calling the base constructor.
// This is inherently unsafe but may work for testing purposes.

// A better approach: use the actual poppler test infrastructure or create
// a minimal PDF in memory. Let's try loading a minimal PDF.

#include <poppler.h>
#include <glib.h>
#include <gio/gio.h>
#include <cstring>
#include <cstdio>

class PopplerFormFieldChoiceTypeTest_2340 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDF with a combo box form field
    PopplerDocument* createPdfWithComboBox() {
        // Minimal PDF with a combo box form field
        const char* pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Annots [4 0 R] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Annot /Subtype /Widget /FT /Ch /Ff 131072 /T (combo1) "
            "/Opt [(Option1) (Option2) (Option3)] "
            "/Rect [100 700 300 720] /P 3 0 R >>\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000096 00000 n \n"
            "0000000153 00000 n \n"
            "0000000252 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "456\n"
            "%%EOF\n";

        GError *error = nullptr;
        gsize len = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        g_object_unref(stream);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    // Helper to create a minimal PDF with a list box form field
    PopplerDocument* createPdfWithListBox() {
        // Minimal PDF with a list box form field (Ff = 0, no combo flag)
        const char* pdf_content =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Annots [4 0 R] >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Type /Annot /Subtype /Widget /FT /Ch /Ff 0 /T (list1) "
            "/Opt [(Option1) (Option2) (Option3)] "
            "/Rect [100 700 300 720] /P 3 0 R >>\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000096 00000 n \n"
            "0000000153 00000 n \n"
            "0000000252 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "440\n"
            "%%EOF\n";

        GError *error = nullptr;
        gsize len = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, len);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
        g_object_unref(stream);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

// Test that a combo box choice field returns POPPLER_FORM_CHOICE_COMBO
TEST_F(PopplerFormFieldChoiceTypeTest_2340, ComboBoxReturnsComboType_2340) {
    PopplerDocument *doc = createPdfWithComboBox();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with combo box";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *fields = poppler_page_get_form_field_mapping(page);
    
    bool found_choice = false;
    for (GList *l = fields; l != nullptr; l = l->next) {
        PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
        PopplerFormField *field = mapping->field;
        
        if (poppler_form_field_get_field_type(field) == POPPLER_FORM_FIELD_CHOICE) {
            PopplerFormChoiceType choice_type = poppler_form_field_choice_get_choice_type(field);
            EXPECT_EQ(choice_type, POPPLER_FORM_CHOICE_COMBO);
            found_choice = true;
        }
    }

    poppler_page_free_form_field_mapping(fields);
    g_object_unref(page);
    g_object_unref(doc);
    
    if (!found_choice) {
        GTEST_SKIP() << "No choice field found in test PDF";
    }
}

// Test that a list box choice field returns POPPLER_FORM_CHOICE_LIST
TEST_F(PopplerFormFieldChoiceTypeTest_2340, ListBoxReturnsListType_2340) {
    PopplerDocument *doc = createPdfWithListBox();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with list box";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    ASSERT_NE(page, nullptr);

    GList *fields = poppler_page_get_form_field_mapping(page);
    
    bool found_choice = false;
    for (GList *l = fields; l != nullptr; l = l->next) {
        PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
        PopplerFormField *field = mapping->field;
        
        if (poppler_form_field_get_field_type(field) == POPPLER_FORM_FIELD_CHOICE) {
            PopplerFormChoiceType choice_type = poppler_form_field_choice_get_choice_type(field);
            EXPECT_EQ(choice_type, POPPLER_FORM_CHOICE_LIST);
            found_choice = true;
        }
    }

    poppler_page_free_form_field_mapping(fields);
    g_object_unref(page);
    g_object_unref(doc);
    
    if (!found_choice) {
        GTEST_SKIP() << "No choice field found in test PDF";
    }
}

// Test that the enum values are correct
TEST_F(PopplerFormFieldChoiceTypeTest_2340, EnumValuesAreCorrect_2340) {
    EXPECT_EQ(POPPLER_FORM_CHOICE_COMBO, 0);
    EXPECT_EQ(POPPLER_FORM_CHOICE_LIST, 1);
}

// Test with a non-choice field type - should return default POPPLER_FORM_CHOICE_COMBO
// due to g_return_val_if_fail guard
TEST_F(PopplerFormFieldChoiceTypeTest_2340, NonChoiceFieldReturnsDefaultCombo_2340) {
    // Create a PDF with a text field
    const char* pdf_content =
        "%PDF-1.4\n"
        "1 0 obj\n"
        "<< /Type /Catalog /Pages 2 0 R /AcroForm << /Fields [4 0 R] >> >>\n"
        "endobj\n"
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n"
        "3 0 obj\n"
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Annots [4 0 R] >>\n"
        "endobj\n"
        "4 0 obj\n"
        "<< /Type /Annot /Subtype /Widget /FT /Tx /T (textfield1) "
        "/V (hello) "
        "/Rect [100 700 300 720] /P 3 0 R >>\n"
        "endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000096 00000 n \n"
        "0000000153 00000 n \n"
        "0000000252 00000 n \n"
        "trailer\n"
        "<< /Size 5 /Root 1 0 R >>\n"
        "startxref\n"
        "430\n"
        "%%EOF\n";

    GError *error = nullptr;
    gsize len = strlen(pdf_content);
    GBytes *bytes = g_bytes_new(pdf_content, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    g_bytes_unref(bytes);

    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
    g_object_unref(stream);

    if (!doc) {
        if (error) g_error_free(error);
        GTEST_SKIP() << "Could not create test PDF with text field";
    }

    PopplerPage *page = poppler_document_get_page(doc, 0);
    if (!page) {
        g_object_unref(doc);
        GTEST_SKIP() << "Could not get page from test PDF";
    }

    GList *fields = poppler_page_get_form_field_mapping(page);
    
    bool found_text = false;
    for (GList *l = fields; l != nullptr; l = l->next) {
        PopplerFormFieldMapping *mapping = (PopplerFormFieldMapping *)l->data;
        PopplerFormField *field = mapping->field;
        
        if (poppler_form_field_get_field_type(field) == POPPLER_FORM_FIELD_TEXT) {
            // Calling choice_get_choice_type on a text field should trigger
            // g_return_val_if_fail and return POPPLER_FORM_CHOICE_COMBO (default)
            PopplerFormChoiceType choice_type = poppler_form_field_choice_get_choice_type(field);
            EXPECT_EQ(choice_type, POPPLER_FORM_CHOICE_COMBO);
            found_text = true;
        }
    }

    poppler_page_free_form_field_mapping(fields);
    g_object_unref(page);
    g_object_unref(doc);
    
    if (!found_text) {
        GTEST_SKIP() << "No text field found in test PDF";
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
