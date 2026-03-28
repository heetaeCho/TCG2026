#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary poppler headers
extern "C" {
#include <poppler.h>
#include <poppler-document.h>
#include <poppler-page.h>
}

#include <glib-object.h>
#include <memory>

class PopplerAnnotCircleTest_2055 : public ::testing::Test {
protected:
    void SetUp() override {
        // We'll try to create a simple PDF document to work with annotations
        doc_ = nullptr;
        page_ = nullptr;
    }

    void TearDown() override {
        if (page_) {
            g_object_unref(page_);
        }
        if (doc_) {
            g_object_unref(doc_);
        }
    }

    PopplerDocument *doc_;
    PopplerPage *page_;

    // Helper to load a document from a test PDF if available
    bool loadTestDocument(const char *uri) {
        GError *error = nullptr;
        doc_ = poppler_document_new_from_file(uri, nullptr, &error);
        if (error) {
            g_error_free(error);
            return false;
        }
        if (doc_ && poppler_document_get_n_pages(doc_) > 0) {
            page_ = poppler_document_get_page(doc_, 0);
            return page_ != nullptr;
        }
        return false;
    }
};

// Test that a PopplerAnnotCircle created via the page annotation mapping has the correct type
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleTypeCheck_2055)
{
    // Create a minimal PDF in memory with a circle annotation
    // We use poppler_page_get_annot_mapping to retrieve annotations
    // Since we can't easily create annotations without a document,
    // we test the type system directly

    GType circle_type = POPPLER_TYPE_ANNOT_CIRCLE;
    EXPECT_NE(circle_type, G_TYPE_INVALID);
    EXPECT_TRUE(g_type_is_a(circle_type, POPPLER_TYPE_ANNOT));
}

// Test that POPPLER_TYPE_ANNOT_CIRCLE is a valid GType
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleGTypeValid_2055)
{
    GType type = POPPLER_TYPE_ANNOT_CIRCLE;
    EXPECT_NE(type, 0u);

    const gchar *name = g_type_name(type);
    EXPECT_NE(name, nullptr);
    EXPECT_STREQ(name, "PopplerAnnotCircle");
}

// Test that POPPLER_TYPE_ANNOT_CIRCLE is derived from POPPLER_TYPE_ANNOT_MARKUP
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleIsMarkup_2055)
{
    GType circle_type = POPPLER_TYPE_ANNOT_CIRCLE;
    // Circle annotation should be a subtype of markup annotation
    EXPECT_TRUE(g_type_is_a(circle_type, POPPLER_TYPE_ANNOT_MARKUP));
}

// Test that POPPLER_TYPE_ANNOT_CIRCLE is derived from POPPLER_TYPE_ANNOT
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleIsAnnot_2055)
{
    GType circle_type = POPPLER_TYPE_ANNOT_CIRCLE;
    EXPECT_TRUE(g_type_is_a(circle_type, POPPLER_TYPE_ANNOT));
}

// Test that POPPLER_TYPE_ANNOT_CIRCLE is a GObject type
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleIsGObject_2055)
{
    GType circle_type = POPPLER_TYPE_ANNOT_CIRCLE;
    EXPECT_TRUE(g_type_is_a(circle_type, G_TYPE_OBJECT));
}

// Test the type hierarchy depth - Circle should not be the same as base Annot
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleNotSameAsBaseAnnot_2055)
{
    EXPECT_NE(POPPLER_TYPE_ANNOT_CIRCLE, POPPLER_TYPE_ANNOT);
}

// Test that the parent type of circle is markup
TEST_F(PopplerAnnotCircleTest_2055, AnnotCircleParentIsMarkup_2055)
{
    GType parent = g_type_parent(POPPLER_TYPE_ANNOT_CIRCLE);
    EXPECT_EQ(parent, POPPLER_TYPE_ANNOT_MARKUP);
}

// Test creating and destroying a circle annotation on a real document
TEST_F(PopplerAnnotCircleTest_2055, CreateCircleAnnotOnDocument_2055)
{
    // Create a PDF in memory
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n209\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (doc_) {
        page_ = poppler_document_get_page(doc_, 0);
        if (page_) {
            // Create a circle annotation
            PopplerRectangle rect;
            rect.x1 = 100.0;
            rect.y1 = 100.0;
            rect.x2 = 200.0;
            rect.y2 = 200.0;

            PopplerAnnot *annot = poppler_annot_circle_new(doc_, &rect);
            if (annot) {
                EXPECT_TRUE(POPPLER_IS_ANNOT_CIRCLE(annot));
                EXPECT_TRUE(POPPLER_IS_ANNOT(annot));
                EXPECT_TRUE(POPPLER_IS_ANNOT_MARKUP(annot));

                PopplerAnnotType annot_type = poppler_annot_get_annot_type(annot);
                EXPECT_EQ(annot_type, POPPLER_ANNOT_CIRCLE);

                g_object_unref(annot);
            }
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test poppler_annot_circle_new with a valid rectangle
TEST_F(PopplerAnnotCircleTest_2055, CircleAnnotNewValidRect_2055)
{
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n209\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (doc_) {
        PopplerRectangle rect;
        rect.x1 = 0.0;
        rect.y1 = 0.0;
        rect.x2 = 50.0;
        rect.y2 = 50.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc_, &rect);
        if (annot) {
            EXPECT_TRUE(POPPLER_IS_ANNOT_CIRCLE(annot));

            // Check that we can set and get interior color
            PopplerColor color;
            color.red = 65535;
            color.green = 0;
            color.blue = 0;
            poppler_annot_circle_set_interior_color(POPPLER_ANNOT_CIRCLE(annot), &color);

            PopplerColor *retrieved_color = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
            if (retrieved_color) {
                EXPECT_EQ(retrieved_color->red, 65535);
                EXPECT_EQ(retrieved_color->green, 0);
                EXPECT_EQ(retrieved_color->blue, 0);
                g_free(retrieved_color);
            }

            g_object_unref(annot);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test that circle annotation can be added to a page
TEST_F(PopplerAnnotCircleTest_2055, AddCircleAnnotToPage_2055)
{
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n209\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (doc_) {
        page_ = poppler_document_get_page(doc_, 0);
        if (page_) {
            PopplerRectangle rect;
            rect.x1 = 10.0;
            rect.y1 = 10.0;
            rect.x2 = 100.0;
            rect.y2 = 100.0;

            PopplerAnnot *annot = poppler_annot_circle_new(doc_, &rect);
            if (annot) {
                poppler_page_add_annot(page_, annot);

                // Verify annotation was added by checking annot mapping list
                GList *annot_list = poppler_page_get_annot_mapping(page_);
                gboolean found_circle = FALSE;
                for (GList *l = annot_list; l != nullptr; l = l->next) {
                    PopplerAnnotMapping *mapping = (PopplerAnnotMapping *)l->data;
                    if (POPPLER_IS_ANNOT_CIRCLE(mapping->annot)) {
                        found_circle = TRUE;
                        break;
                    }
                }
                EXPECT_TRUE(found_circle);

                poppler_page_free_annot_mapping(annot_list);
                g_object_unref(annot);
            }
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

// Test setting NULL interior color on circle annotation
TEST_F(PopplerAnnotCircleTest_2055, CircleAnnotNullInteriorColor_2055)
{
    const char *pdf_data =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n209\n%%EOF\n";

    GError *error = nullptr;
    GBytes *bytes = g_bytes_new_static(pdf_data, strlen(pdf_data));
    GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);

    doc_ = poppler_document_new_from_stream(stream, g_bytes_get_size(bytes), nullptr, nullptr, &error);

    if (doc_) {
        PopplerRectangle rect;
        rect.x1 = 10.0;
        rect.y1 = 10.0;
        rect.x2 = 100.0;
        rect.y2 = 100.0;

        PopplerAnnot *annot = poppler_annot_circle_new(doc_, &rect);
        if (annot) {
            // Setting NULL interior color should clear it
            poppler_annot_circle_set_interior_color(POPPLER_ANNOT_CIRCLE(annot), nullptr);

            PopplerColor *color = poppler_annot_circle_get_interior_color(POPPLER_ANNOT_CIRCLE(annot));
            // When no interior color is set, it should return NULL
            EXPECT_EQ(color, nullptr);

            g_object_unref(annot);
        }
    }

    g_object_unref(stream);
    g_bytes_unref(bytes);
    if (error) {
        g_error_free(error);
    }
}

int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
