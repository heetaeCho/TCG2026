#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
extern "C" {
#include <poppler.h>
}

#include <memory>

class PopplerAnnotLineTest_2053 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal PDF document in memory for testing
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

    PopplerDocument *doc;
    PopplerPage *page;

    // Helper to create a document from a file or generate one
    bool loadTestDocument(const char *uri) {
        GError *error = nullptr;
        doc = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return false;
        }
        if (doc && poppler_document_get_n_pages(doc) > 0) {
            page = poppler_document_get_page(doc, 0);
            return page != nullptr;
        }
        return false;
    }
};

// Test that PopplerAnnotLine type is properly registered in GType system
TEST_F(PopplerAnnotLineTest_2053, AnnotLineTypeIsRegistered_2053)
{
    GType type = POPPLER_TYPE_ANNOT_LINE;
    EXPECT_NE(type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(type, POPPLER_TYPE_ANNOT_MARKUP));
    EXPECT_TRUE(g_type_is_a(type, POPPLER_TYPE_ANNOT));
}

// Test that PopplerAnnotLine is a subtype of PopplerAnnot
TEST_F(PopplerAnnotLineTest_2053, AnnotLineIsSubtypeOfAnnot_2053)
{
    EXPECT_TRUE(g_type_is_a(POPPLER_TYPE_ANNOT_LINE, POPPLER_TYPE_ANNOT));
}

// Test that PopplerAnnotLine is a subtype of PopplerAnnotMarkup
TEST_F(PopplerAnnotLineTest_2053, AnnotLineIsSubtypeOfAnnotMarkup_2053)
{
    EXPECT_TRUE(g_type_is_a(POPPLER_TYPE_ANNOT_LINE, POPPLER_TYPE_ANNOT_MARKUP));
}

// Test that POPPLER_TYPE_ANNOT_LINE is not the same as POPPLER_TYPE_ANNOT
TEST_F(PopplerAnnotLineTest_2053, AnnotLineTypeIsDifferentFromAnnot_2053)
{
    EXPECT_NE(POPPLER_TYPE_ANNOT_LINE, POPPLER_TYPE_ANNOT);
}

// Test GType name for PopplerAnnotLine
TEST_F(PopplerAnnotLineTest_2053, AnnotLineTypeNameIsCorrect_2053)
{
    const gchar *name = g_type_name(POPPLER_TYPE_ANNOT_LINE);
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAnnotLine");
}

// Test that the type is instantiatable (it's a GObject type)
TEST_F(PopplerAnnotLineTest_2053, AnnotLineTypeIsInstantiatable_2053)
{
    // GObject derived types should have a class structure
    gpointer klass = g_type_class_ref(POPPLER_TYPE_ANNOT_LINE);
    EXPECT_NE(klass, nullptr);
    if (klass) {
        g_type_class_unref(klass);
    }
}

// Test parent type of PopplerAnnotLine
TEST_F(PopplerAnnotLineTest_2053, AnnotLineParentTypeIsAnnotMarkup_2053)
{
    GType parent = g_type_parent(POPPLER_TYPE_ANNOT_LINE);
    EXPECT_EQ(parent, POPPLER_TYPE_ANNOT_MARKUP);
}

// Test that POPPLER_IS_ANNOT_LINE macro works with nullptr (should be FALSE)
TEST_F(PopplerAnnotLineTest_2053, IsAnnotLineMacroReturnsFalseForNull_2053)
{
    EXPECT_FALSE(POPPLER_IS_ANNOT_LINE(nullptr));
}

// Test type hierarchy depth
TEST_F(PopplerAnnotLineTest_2053, AnnotLineTypeHierarchyDepth_2053)
{
    // PopplerAnnotLine -> PopplerAnnotMarkup -> PopplerAnnot -> GObject
    GType type = POPPLER_TYPE_ANNOT_LINE;
    int depth = 0;
    while (type != G_TYPE_INVALID && type != 0) {
        depth++;
        type = g_type_parent(type);
    }
    // Should have at least 4 levels: AnnotLine, AnnotMarkup, Annot, GObject
    EXPECT_GE(depth, 4);
}

// Test that checking IS_ANNOT on a non-GObject pointer doesn't crash 
// (we just check with NULL which is safe)
TEST_F(PopplerAnnotLineTest_2053, IsAnnotMacroSafeWithNull_2053)
{
    EXPECT_FALSE(POPPLER_IS_ANNOT(nullptr));
    EXPECT_FALSE(POPPLER_IS_ANNOT_LINE(nullptr));
    EXPECT_FALSE(POPPLER_IS_ANNOT_MARKUP(nullptr));
}
