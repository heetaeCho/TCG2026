// poppler_structure_element_get_text_decoration_type_test.cpp
//
// Unit tests for:
//   PopplerStructureTextDecoration
//   poppler_structure_element_get_text_decoration_type()
//
// TEST_ID: 2580

#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>
#include <poppler-structure-element.h>

#include <cstdio>
#include <cstdlib>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

namespace {

class PopplerStructureTextDecorationTypeTest_2580 : public ::testing::Test {
protected:
    static void SetUpTestSuite()
    {
        // Ensure GLib testing helpers are available (g_test_expect_message).
        // It's safe to call once; if already initialized elsewhere, GLib tolerates it.
        int argc = 1;
        const char *argv0 = "poppler-structure-element-tests";
        char *argv_mut0 = const_cast<char *>(argv0);
        char **argv_mut = &argv_mut0;
        g_test_init(&argc, &argv_mut, nullptr);
    }

    static std::string BuildTaggedPdf_OneStructElem(const char *struct_type_name,
                                                    bool with_text_decoration_attr,
                                                    const char *decoration_name_or_null)
    {
        // Build a minimal tagged PDF with:
        // - Catalog + Pages + one Page
        // - StructTreeRoot with one StructElem
        // - ParentTree mapping StructParents=0 and MCID=0 to that StructElem
        //
        // Marked content is tagged as /Span in the content stream. The structure type is configurable
        // to exercise inline vs non-inline types (e.g., /Span vs /P).

        // Object list: index == object number (1..N). We'll fill 1..8.
        std::vector<std::string> obj(9);

        // 1 0 obj: Catalog
        {
            std::ostringstream o;
            o << "<< /Type /Catalog\n"
              << "   /Pages 2 0 R\n"
              << "   /StructTreeRoot 6 0 R\n"
              << "   /MarkInfo << /Marked true >>\n"
              << ">>";
            obj[1] = o.str();
        }

        // 2 0 obj: Pages
        obj[2] = "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";

        // 3 0 obj: Page
        // StructParents 0 used by ParentTree.
        {
            std::ostringstream o;
            o << "<< /Type /Page\n"
              << "   /Parent 2 0 R\n"
              << "   /MediaBox [0 0 200 200]\n"
              << "   /StructParents 0\n"
              << "   /Resources << /Font << /F1 5 0 R >> >>\n"
              << "   /Contents 4 0 R\n"
              << ">>";
            obj[3] = o.str();
        }

        // 4 0 obj: Contents stream (includes MCID 0 marked content)
        {
            const char *stream =
                "BT\n"
                "/F1 12 Tf\n"
                "10 100 Td\n"
                "/Span << /MCID 0 >> BDC\n"
                "(Hello) Tj\n"
                "EMC\n"
                "ET\n";

            std::ostringstream o;
            o << "<< /Length " << std::strlen(stream) << " >>\n"
              << "stream\n"
              << stream
              << "endstream";
            obj[4] = o.str();
        }

        // 5 0 obj: Font
        obj[5] = "<< /Type /Font /Subtype /Type1 /BaseFont /Helvetica >>";

        // 6 0 obj: StructTreeRoot
        obj[6] = "<< /Type /StructTreeRoot /K [7 0 R] /ParentTree 8 0 R >>";

        // 7 0 obj: StructElem
        {
            std::ostringstream o;
            o << "<< /Type /StructElem\n"
              << "   /S /" << struct_type_name << "\n"
              << "   /P 6 0 R\n"
              << "   /K 0\n";

            if (with_text_decoration_attr) {
                o << "   /A << /TextDecorationType ";
                if (decoration_name_or_null && *decoration_name_or_null) {
                    o << "/" << decoration_name_or_null;
                } else {
                    o << "/None";
                }
                o << " >>\n";
            }

            o << ">>";
            obj[7] = o.str();
        }

        // 8 0 obj: ParentTree mapping StructParents=0 to array where index 0 => StructElem 7 0 R
        obj[8] = "<< /Nums [ 0 [ 7 0 R ] ] >>";

        // Now assemble PDF with correct xref offsets.
        std::ostringstream pdf;
        pdf << "%PDF-1.4\n%\xE2\xE3\xCF\xD3\n";

        std::vector<long> offsets(9, 0);
        offsets[0] = 0;

        for (int i = 1; i <= 8; ++i) {
            offsets[i] = static_cast<long>(pdf.tellp());
            pdf << i << " 0 obj\n" << obj[i] << "\nendobj\n";
        }

        const long xref_offset = static_cast<long>(pdf.tellp());
        pdf << "xref\n";
        pdf << "0 9\n";
        pdf << "0000000000 65535 f \n";
        for (int i = 1; i <= 8; ++i) {
            // Each entry: 10-digit offset, 5-digit generation, n/f
            char buf[32];
            std::snprintf(buf, sizeof(buf), "%010ld 00000 n \n", offsets[i]);
            pdf << buf;
        }

        pdf << "trailer\n";
        pdf << "<< /Size 9 /Root 1 0 R >>\n";
        pdf << "startxref\n" << xref_offset << "\n%%EOF\n";

        return pdf.str();
    }

    static std::string WritePdfToTempAndReturnUri(const std::string &pdf_bytes)
    {
        gchar *tmp_path = nullptr;
        GError *error = nullptr;

        // Create a temp file path.
        int fd = g_file_open_tmp("poppler-struct-2580-XXXXXX.pdf", &tmp_path, &error);
        if (fd == -1) {
            std::string msg = error ? error->message : "unknown";
            if (error)
                g_error_free(error);
            FAIL() << "g_file_open_tmp failed: " << msg;
        }

        // Write bytes.
        FILE *f = fdopen(fd, "wb");
        ASSERT_NE(f, nullptr);
        const size_t written = fwrite(pdf_bytes.data(), 1, pdf_bytes.size(), f);
        fclose(f);

        ASSERT_EQ(written, pdf_bytes.size());

        gchar *uri = g_filename_to_uri(tmp_path, nullptr, &error);
        std::string uri_str;
        if (!uri) {
            std::string msg = error ? error->message : "unknown";
            if (error)
                g_error_free(error);
            g_free(tmp_path);
            FAIL() << "g_filename_to_uri failed: " << msg;
        } else {
            uri_str = uri;
            g_free(uri);
        }

        g_free(tmp_path);
        return uri_str;
    }

    static PopplerDocument *OpenDocFromPdfBytes(const std::string &pdf_bytes)
    {
        const std::string uri = WritePdfToTempAndReturnUri(pdf_bytes);

        GError *error = nullptr;
        PopplerDocument *doc = poppler_document_new_from_file(uri.c_str(), nullptr, &error);
        if (!doc) {
            std::string msg = error ? error->message : "unknown";
            if (error)
                g_error_free(error);
            FAIL() << "poppler_document_new_from_file failed: " << msg;
        }
        return doc;
    }

    static PopplerStructureElement *GetFirstStructureElementOrNull(PopplerDocument *doc)
    {
        PopplerStructureElementIter *iter = poppler_structure_element_iter_new(doc);
        if (!iter)
            return nullptr;

        PopplerStructureElement *elem = poppler_structure_element_iter_get_element(iter);
        poppler_structure_element_iter_free(iter);
        return elem;
    }
};

TEST_F(PopplerStructureTextDecorationTypeTest_2580, InlineSpanUnderline_ReturnsUnderline_2580)
{
    const std::string pdf =
        BuildTaggedPdf_OneStructElem("Span", /*with_attr=*/true, /*decoration=*/"Underline");
    PopplerDocument *doc = OpenDocFromPdfBytes(pdf);

    PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc);
    ASSERT_NE(elem, nullptr);

    // Normal operation: inline element with TextDecorationType=Underline.
    const PopplerStructureTextDecoration deco = poppler_structure_element_get_text_decoration_type(elem);
    EXPECT_EQ(deco, POPPLER_STRUCTURE_TEXT_DECORATION_UNDERLINE);

    g_object_unref(doc);
}

TEST_F(PopplerStructureTextDecorationTypeTest_2580, InlineSpanNoAttribute_ReturnsNone_2580)
{
    const std::string pdf =
        BuildTaggedPdf_OneStructElem("Span", /*with_attr=*/false, /*decoration=*/nullptr);
    PopplerDocument *doc = OpenDocFromPdfBytes(pdf);

    PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc);
    ASSERT_NE(elem, nullptr);

    // Boundary-ish: attribute missing => expect default enum (NONE).
    const PopplerStructureTextDecoration deco = poppler_structure_element_get_text_decoration_type(elem);
    EXPECT_EQ(deco, POPPLER_STRUCTURE_TEXT_DECORATION_NONE);

    g_object_unref(doc);
}

TEST_F(PopplerStructureTextDecorationTypeTest_2580, NonInlineParagraph_TriggersGuardAndReturnsDefault_2580)
{
    // Use a block-ish structure type (/P). Even if we attach an underline attribute,
    // the function should fail the inline guard and return the default enum value.
    const std::string pdf =
        BuildTaggedPdf_OneStructElem("P", /*with_attr=*/true, /*decoration=*/"Underline");
    PopplerDocument *doc = OpenDocFromPdfBytes(pdf);

    PopplerStructureElement *elem = GetFirstStructureElementOrNull(doc);
    ASSERT_NE(elem, nullptr);

    // Verify external interaction: GLib critical message emitted by g_return_val_if_fail.
    g_test_expect_message(
        "GLib", G_LOG_LEVEL_CRITICAL,
        "*poppler_structure_element_is_inline*failed*");

    const PopplerStructureTextDecoration deco = poppler_structure_element_get_text_decoration_type(elem);
    EXPECT_EQ(deco, POPPLER_STRUCTURE_TEXT_DECORATION_NONE);

    g_test_assert_expected_messages();

    g_object_unref(doc);
}

TEST_F(PopplerStructureTextDecorationTypeTest_2580, NullElement_ReturnsDefault_2580)
{
    // Boundary: NULL input. Behavior is observable via return value (and may emit GLib criticals).
    // We avoid asserting exact log messages here because the call may also trigger internal checks
    // in poppler_structure_element_is_inline(NULL), depending on the build.
    const PopplerStructureTextDecoration deco =
        poppler_structure_element_get_text_decoration_type(nullptr);

    EXPECT_EQ(deco, POPPLER_STRUCTURE_TEXT_DECORATION_NONE);
}

} // namespace