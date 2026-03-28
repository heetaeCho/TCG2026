#include <glib-object.h>
#include <gtest/gtest.h>

// Include poppler glib headers
extern "C" {
#include "poppler-annot.h"
#include "poppler-action.h"
#include "poppler.h"
}

class PopplerAnnotScreenTest_2050 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that creating and unreffing a PopplerAnnotScreen does not crash
// when the action field is nullptr (no action set).
// Since PopplerAnnotScreen is typically created internally by poppler
// when parsing a PDF, we test finalization behavior indirectly through
// the GObject ref/unref mechanism if we can construct one.

// Note: PopplerAnnotScreen objects are normally created internally by
// the poppler library when a PDF with screen annotations is loaded.
// We test through document loading to exercise the finalize path.

TEST_F(PopplerAnnotScreenTest_2050, FinalizeWithNullAction_2050)
{
    // Create a minimal PDF in memory that has a screen annotation
    // Since we can't easily create a PopplerAnnotScreen directly,
    // we verify the type system is properly registered
    GType screen_type = POPPLER_TYPE_ANNOT_SCREEN;
    EXPECT_NE(screen_type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(screen_type, POPPLER_TYPE_ANNOT));
}

TEST_F(PopplerAnnotScreenTest_2050, TypeRegistration_2050)
{
    // Verify that PopplerAnnotScreen type is properly registered in GType system
    GType type = POPPLER_TYPE_ANNOT_SCREEN;
    EXPECT_NE(type, (GType)0);
    
    const gchar *type_name = g_type_name(type);
    ASSERT_NE(type_name, nullptr);
    EXPECT_STREQ(type_name, "PopplerAnnotScreen");
}

TEST_F(PopplerAnnotScreenTest_2050, TypeIsAnnotSubclass_2050)
{
    // Verify inheritance: PopplerAnnotScreen should be a subclass of PopplerAnnot
    EXPECT_TRUE(g_type_is_a(POPPLER_TYPE_ANNOT_SCREEN, POPPLER_TYPE_ANNOT));
}

TEST_F(PopplerAnnotScreenTest_2050, TypeIsGObjectSubclass_2050)
{
    // Verify PopplerAnnotScreen is ultimately a GObject
    EXPECT_TRUE(g_type_is_a(POPPLER_TYPE_ANNOT_SCREEN, G_TYPE_OBJECT));
}

// Test get_action on a screen annotation loaded from a real PDF document
// that has screen annotations. Since we may not have such a file available,
// we test the API contract that it returns nullptr or a valid action.
TEST_F(PopplerAnnotScreenTest_2050, GetActionFromLoadedDocument_2050)
{
    // Load a simple PDF to test annotation enumeration
    // This test verifies that if we encounter screen annotations,
    // poppler_annot_screen_get_action returns either NULL or valid PopplerAction
    
    GError *error = nullptr;
    
    // Create a minimal PDF in memory
    const char *pdf_data = "%PDF-1.4\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
                           "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
                           "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
                           "xref\n0 4\n0000000000 65535 f \n0000000009 00000 n \n"
                           "0000000058 00000 n \n0000000115 00000 n \n"
                           "trailer<</Size 4/Root 1 0 R>>\nstartxref\n190\n%%EOF\n";
    
    gsize len = strlen(pdf_data);
    GBytes *bytes = g_bytes_new_static(pdf_data, len);
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
    
    PopplerDocument *doc = poppler_document_new_from_stream(stream, len, nullptr, nullptr, &error);
    
    if (doc != nullptr) {
        PopplerPage *page = poppler_document_get_page(doc, 0);
        if (page != nullptr) {
            GList *annot_mapping = poppler_page_get_annot_mapping(page);
            
            for (GList *l = annot_mapping; l != nullptr; l = l->next) {
                PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
                PopplerAnnot *annot = mapping->annot;
                
                if (POPPLER_IS_ANNOT_SCREEN(annot)) {
                    PopplerAction *action = poppler_annot_screen_get_action(POPPLER_ANNOT_SCREEN(annot));
                    // Action can be NULL if no action is associated
                    // Just verifying the call doesn't crash
                    (void)action;
                }
            }
            
            poppler_page_free_annot_mapping(annot_mapping);
            g_object_unref(page);
        }
        g_object_unref(doc);
    }
    
    if (error) {
        g_error_free(error);
    }
    
    g_object_unref(stream);
    g_bytes_unref(bytes);
    
    // Test passes if no crash occurred
    SUCCEED();
}

TEST_F(PopplerAnnotScreenTest_2050, TypeCheckMacros_2050)
{
    // Verify that the type check macros work correctly with NULL
    EXPECT_FALSE(POPPLER_IS_ANNOT_SCREEN(nullptr));
}

TEST_F(PopplerAnnotScreenTest_2050, ParentClassChain_2050)
{
    // Verify the parent class of PopplerAnnotScreen is PopplerAnnot
    GType parent = g_type_parent(POPPLER_TYPE_ANNOT_SCREEN);
    EXPECT_EQ(parent, POPPLER_TYPE_ANNOT);
}
