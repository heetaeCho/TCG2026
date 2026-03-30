// poppler-structure-element-get-width-test.cpp
#include <gtest/gtest.h>

#include <cmath>
#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

#include <glib.h>
#include <poppler.h>

// Builds a minimal, valid PDF (as bytes) with a simple tagged structure tree:
//
// 1 0 obj: Catalog (/StructTreeRoot 4 0 R)
// 2 0 obj: Pages
// 3 0 obj: Page
// 4 0 obj: StructTreeRoot (/K [5 0 R])
// 5 0 obj: StructElem (/S /Div or /Span, /A with /Width)
// 6 0 obj: empty contents stream
//
// width_token examples: "72", "0", "-5.5", "/Auto"
static std::string BuildTaggedPdfWithStructElem(const std::string &struct_type_name,
                                                const std::string &width_token)
{
    std::vector<std::string> objs;
    objs.resize(7); // index 0 unused; objects 1..6

    objs[1] =
        "<< /Type /Catalog /Pages 2 0 R /StructTreeRoot 4 0 R >>";
    objs[2] =
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";
    objs[3] =
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
        "/Contents 6 0 R /Resources << >> /StructParents 0 >>";
    objs[4] =
        "<< /Type /StructTreeRoot /K [5 0 R] >>";
    // Attribute owner /O /Layout is commonly used for layout attributes like /Width.
    objs[5] =
        "<< /Type /StructElem /S /" + struct_type_name + " /P 4 0 R /Pg 3 0 R "
        "/A << /O /Layout /Width " + width_token + " >> >>";
    // Empty content stream
    objs[6] =
        "<< /Length 0 >>\nstream\n\nendstream";

    std::string pdf;
    pdf.reserve(2048);
    pdf += "%PDF-1.7\n";
    pdf += "%\xE2\xE3\xCF\xD3\n";

    std::vector<std::size_t> offsets;
    offsets.resize(7, 0);

    for (int i = 1; i <= 6; ++i) {
        offsets[i] = pdf.size();
        pdf += std::to_string(i);
        pdf += " 0 obj\n";
        pdf += objs[i];
        pdf += "\nendobj\n";
    }

    const std::size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 7\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 6; ++i) {
        char buf[32];
        // PDF xref offsets are 10 digits, zero-padded.
        std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
        pdf += buf;
    }

    pdf += "trailer\n";
    pdf += "<< /Size 7 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset);
    pdf += "\n%%EOF\n";

    return pdf;
}

static PopplerDocument *LoadDocFromPdfBytesOrFail(const std::string &pdf_bytes)
{
    GError *error = nullptr;

    // poppler_document_new_from_data takes (const char*, int, const char*, GError**)
    PopplerDocument *doc =
        poppler_document_new_from_data(pdf_bytes.data(),
                                       static_cast<int>(pdf_bytes.size()),
                                       /*password=*/nullptr,
                                       &error);
    if (!doc) {
        std::string msg = "poppler_document_new_from_data failed";
        if (error && error->message) {
            msg += ": ";
            msg += error->message;
        }
        if (error) {
            g_error_free(error);
        }
        ADD_FAILURE() << msg;
    }
    if (error) {
        g_error_free(error);
    }
    return doc;
}

static PopplerStructureElement *GetSingleStructChildOrFail(PopplerStructureElement *root)
{
    if (!root) {
        ADD_FAILURE() << "Structure root is null";
        return nullptr;
    }

    // poppler_structure_element_get_children returns a GList* of PopplerStructureElement*
    GList *children = poppler_structure_element_get_children(root);
    if (!children) {
        ADD_FAILURE() << "No children in structure root";
        return nullptr;
    }

    // Take first child; add a ref so we can free the list safely.
    PopplerStructureElement *child = POPPLER_STRUCTURE_ELEMENT(children->data);
    if (child) {
        g_object_ref(child);
    }
    g_list_free_full(children, (GDestroyNotify)g_object_unref);

    if (!child) {
        ADD_FAILURE() << "First child in structure root is null";
    }
    return child;
}

class PopplerStructureElementGetWidthTest_2570 : public ::testing::Test {};

// Normal operation: numeric width on a block element (/Div) should be returned.
TEST_F(PopplerStructureElementGetWidthTest_2570, NumericWidthReturned_2570)
{
    const std::string pdf = BuildTaggedPdfWithStructElem("Div", "72");
    PopplerDocument *doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElement *root = poppler_document_get_structure(doc);
    ASSERT_NE(root, nullptr);

    PopplerStructureElement *elem = GetSingleStructChildOrFail(root);
    ASSERT_NE(elem, nullptr);

    ASSERT_TRUE(poppler_structure_element_is_block(elem));

    const gdouble w = poppler_structure_element_get_width(elem);
    EXPECT_FALSE(std::isnan(static_cast<double>(w)));
    EXPECT_DOUBLE_EQ(static_cast<double>(w), 72.0);

    g_object_unref(elem);
    g_object_unref(root);
    g_object_unref(doc);
}

// Normal operation: /Width /Auto should return -1.0 for block elements.
TEST_F(PopplerStructureElementGetWidthTest_2570, AutoWidthReturnsMinusOne_2570)
{
    const std::string pdf = BuildTaggedPdfWithStructElem("Div", "/Auto");
    PopplerDocument *doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElement *root = poppler_document_get_structure(doc);
    ASSERT_NE(root, nullptr);

    PopplerStructureElement *elem = GetSingleStructChildOrFail(root);
    ASSERT_NE(elem, nullptr);

    ASSERT_TRUE(poppler_structure_element_is_block(elem));

    const gdouble w = poppler_structure_element_get_width(elem);
    EXPECT_FALSE(std::isnan(static_cast<double>(w)));
    EXPECT_DOUBLE_EQ(static_cast<double>(w), -1.0);

    g_object_unref(elem);
    g_object_unref(root);
    g_object_unref(doc);
}

// Boundary: width = 0 should be returned as 0 for block elements.
TEST_F(PopplerStructureElementGetWidthTest_2570, ZeroWidthBoundary_2570)
{
    const std::string pdf = BuildTaggedPdfWithStructElem("Div", "0");
    PopplerDocument *doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElement *root = poppler_document_get_structure(doc);
    ASSERT_NE(root, nullptr);

    PopplerStructureElement *elem = GetSingleStructChildOrFail(root);
    ASSERT_NE(elem, nullptr);

    ASSERT_TRUE(poppler_structure_element_is_block(elem));

    const gdouble w = poppler_structure_element_get_width(elem);
    EXPECT_FALSE(std::isnan(static_cast<double>(w)));
    EXPECT_DOUBLE_EQ(static_cast<double>(w), 0.0);

    g_object_unref(elem);
    g_object_unref(root);
    g_object_unref(doc);
}

// Boundary: negative numeric width should be returned as-is for block elements (if present).
TEST_F(PopplerStructureElementGetWidthTest_2570, NegativeWidthBoundary_2570)
{
    const std::string pdf = BuildTaggedPdfWithStructElem("Div", "-5.5");
    PopplerDocument *doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElement *root = poppler_document_get_structure(doc);
    ASSERT_NE(root, nullptr);

    PopplerStructureElement *elem = GetSingleStructChildOrFail(root);
    ASSERT_NE(elem, nullptr);

    ASSERT_TRUE(poppler_structure_element_is_block(elem));

    const gdouble w = poppler_structure_element_get_width(elem);
    EXPECT_FALSE(std::isnan(static_cast<double>(w)));
    EXPECT_DOUBLE_EQ(static_cast<double>(w), -5.5);

    g_object_unref(elem);
    g_object_unref(root);
    g_object_unref(doc);
}

// Error/exceptional (observable): non-block element should trigger g_return_val_if_fail and return NaN.
TEST_F(PopplerStructureElementGetWidthTest_2570, NonBlockElementReturnsNaN_2570)
{
    const std::string pdf = BuildTaggedPdfWithStructElem("Span", "72");
    PopplerDocument *doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    PopplerStructureElement *root = poppler_document_get_structure(doc);
    ASSERT_NE(root, nullptr);

    PopplerStructureElement *elem = GetSingleStructChildOrFail(root);
    ASSERT_NE(elem, nullptr);

    ASSERT_FALSE(poppler_structure_element_is_block(elem));

    const gdouble w = poppler_structure_element_get_width(elem);
    EXPECT_TRUE(std::isnan(static_cast<double>(w)));

    g_object_unref(elem);
    g_object_unref(root);
    g_object_unref(doc);
}

// Error/exceptional (observable): null argument should return NaN (via the block check failing).
TEST_F(PopplerStructureElementGetWidthTest_2570, NullElementReturnsNaN_2570)
{
    const gdouble w = poppler_structure_element_get_width(nullptr);
    EXPECT_TRUE(std::isnan(static_cast<double>(w)));
}