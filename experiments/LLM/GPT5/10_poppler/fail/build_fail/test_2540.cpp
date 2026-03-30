// poppler_structure_element_iter_get_child_test_2540.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <string>
#include <vector>

namespace {

static std::string BuildPdfFromObjects(const std::vector<std::string> &objects)
{
    // objects[i] is the full text for object (i+1) without leading/trailing whitespace requirements.
    std::string pdf;
    pdf += "%PDF-1.5\n";
    pdf += "%\xE2\xE3\xCF\xD3\n"; // binary marker

    std::vector<size_t> offsets;
    offsets.reserve(objects.size() + 1);
    offsets.push_back(0); // object 0 (free)

    for (size_t i = 0; i < objects.size(); ++i) {
        offsets.push_back(pdf.size());
        pdf += objects[i];
        if (pdf.back() != '\n') {
            pdf += "\n";
        }
    }

    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 " + std::to_string(objects.size() + 1) + "\n";
    pdf += "0000000000 65535 f \n";
    for (size_t i = 1; i < offsets.size(); ++i) {
        char buf[32];
        // 10-digit, zero-padded byte offset
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[i]);
        pdf += buf;
    }

    pdf += "trailer\n";
    pdf += "<< /Size " + std::to_string(objects.size() + 1) + " /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset) + "\n";
    pdf += "%%EOF\n";
    return pdf;
}

static std::string MakeTaggedPdf_WithDocumentAndParagraph()
{
    // Minimal tagged PDF with:
    // StructTreeRoot -> Document -> P
    // P contains an MCID (content item), but we do NOT rely on that for child iteration tests.
    const char *content_stream = "q\n/Span <</MCID 0>> BDC\nQ\nEMC\n";
    const int content_len = static_cast<int>(strlen(content_stream));

    std::vector<std::string> objs;
    objs.emplace_back(
        "1 0 obj\n"
        "<< /Type /Catalog\n"
        "   /Pages 2 0 R\n"
        "   /StructTreeRoot 5 0 R\n"
        "   /MarkInfo << /Marked true >>\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n");

    objs.emplace_back(
        "3 0 obj\n"
        "<< /Type /Page\n"
        "   /Parent 2 0 R\n"
        "   /MediaBox [0 0 200 200]\n"
        "   /Contents 4 0 R\n"
        "   /Resources << >>\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "4 0 obj\n"
        "<< /Length " +
        std::to_string(content_len) +
        " >>\n"
        "stream\n" +
        std::string(content_stream) +
        "endstream\n"
        "endobj\n");

    objs.emplace_back(
        "5 0 obj\n"
        "<< /Type /StructTreeRoot\n"
        "   /K [6 0 R]\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "6 0 obj\n"
        "<< /Type /StructElem\n"
        "   /S /Document\n"
        "   /K [7 0 R]\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "7 0 obj\n"
        "<< /Type /StructElem\n"
        "   /S /P\n"
        "   /Pg 3 0 R\n"
        "   /K 0\n"
        ">>\n"
        "endobj\n");

    return BuildPdfFromObjects(objs);
}

static std::string MakeTaggedPdf_WithDocumentNoChildren()
{
    // StructTreeRoot -> Document (no /K children)
    std::vector<std::string> objs;
    objs.emplace_back(
        "1 0 obj\n"
        "<< /Type /Catalog\n"
        "   /Pages 2 0 R\n"
        "   /StructTreeRoot 4 0 R\n"
        "   /MarkInfo << /Marked true >>\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "2 0 obj\n"
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
        "endobj\n");

    objs.emplace_back(
        "3 0 obj\n"
        "<< /Type /Page\n"
        "   /Parent 2 0 R\n"
        "   /MediaBox [0 0 200 200]\n"
        "   /Contents 0 0 R\n"
        "   /Resources << >>\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "4 0 obj\n"
        "<< /Type /StructTreeRoot\n"
        "   /K [5 0 R]\n"
        ">>\n"
        "endobj\n");

    objs.emplace_back(
        "5 0 obj\n"
        "<< /Type /StructElem\n"
        "   /S /Document\n"
        ">>\n"
        "endobj\n");

    return BuildPdfFromObjects(objs);
}

class PopplerStructureElementIterGetChildTest_2540 : public ::testing::Test {
protected:
    static PopplerDocument *OpenDocumentFromPdfBytes(const std::string &pdf_bytes)
    {
        // Write to a temp file, open via poppler_document_new_from_file
        GError *error = nullptr;

        gchar *tmp_name = nullptr;
        int fd = g_file_open_tmp("poppler-struct-2540-XXXXXX.pdf", &tmp_name, &error);
        if (fd >= 0) {
            close(fd);
        }
        EXPECT_NE(tmp_name, nullptr);
        EXPECT_EQ(error, nullptr);

        gboolean ok = g_file_set_contents(tmp_name, pdf_bytes.data(), (gssize)pdf_bytes.size(), &error);
        EXPECT_TRUE(ok);
        EXPECT_EQ(error, nullptr);

        gchar *uri = g_filename_to_uri(tmp_name, nullptr, &error);
        EXPECT_NE(uri, nullptr);
        EXPECT_EQ(error, nullptr);

        PopplerDocument *doc = poppler_document_new_from_file(uri, /*password*/ nullptr, &error);
        EXPECT_NE(doc, nullptr);
        EXPECT_EQ(error, nullptr);

        g_free(uri);
        g_remove(tmp_name);
        g_free(tmp_name);

        return doc;
    }
};

TEST_F(PopplerStructureElementIterGetChildTest_2540, NullParentReturnsNull_2540)
{
    // g_return_val_if_fail(parent != nullptr, NULL);
    EXPECT_EQ(poppler_structure_element_iter_get_child(nullptr), nullptr);
}

TEST_F(PopplerStructureElementIterGetChildTest_2540, RootChildWithChildrenReturnsNonNullIter_2540)
{
    PopplerDocument *doc = OpenDocumentFromPdfBytes(MakeTaggedPdf_WithDocumentAndParagraph());
    ASSERT_NE(doc, nullptr);

    PopplerStructureElementIter *root_iter = poppler_structure_element_iter_new(doc);
    ASSERT_NE(root_iter, nullptr);

    PopplerStructureElementIter *child_iter = poppler_structure_element_iter_get_child(root_iter);
    ASSERT_NE(child_iter, nullptr);

    // Observable behavior through public API: returned iter yields a valid element.
    PopplerStructureElement *elem = poppler_structure_element_iter_get_element(child_iter);
    ASSERT_NE(elem, nullptr);

    // For this PDF, the first root element is /Document.
    EXPECT_EQ(poppler_structure_element_get_kind(elem), POPPLER_STRUCTURE_ELEMENT_DOCUMENT);

    poppler_structure_element_iter_free(child_iter);
    poppler_structure_element_iter_free(root_iter);
    g_object_unref(doc);
}

TEST_F(PopplerStructureElementIterGetChildTest_2540, RootChildWithNoChildrenReturnsNull_2540)
{
    PopplerDocument *doc = OpenDocumentFromPdfBytes(MakeTaggedPdf_WithDocumentNoChildren());
    ASSERT_NE(doc, nullptr);

    PopplerStructureElementIter *root_iter = poppler_structure_element_iter_new(doc);
    ASSERT_NE(root_iter, nullptr);

    // The root's first child exists, but has no children => should return nullptr.
    EXPECT_EQ(poppler_structure_element_iter_get_child(root_iter), nullptr);

    poppler_structure_element_iter_free(root_iter);
    g_object_unref(doc);
}

TEST_F(PopplerStructureElementIterGetChildTest_2540, ReturnedChildIterKeepsDocumentAliveUntilFreed_2540)
{
    PopplerDocument *doc = OpenDocumentFromPdfBytes(MakeTaggedPdf_WithDocumentAndParagraph());
    ASSERT_NE(doc, nullptr);

    gboolean finalized = FALSE;
    g_object_weak_ref(G_OBJECT(doc),
                      [](gpointer data, GObject *) { *static_cast<gboolean *>(data) = TRUE; },
                      &finalized);

    PopplerStructureElementIter *root_iter = poppler_structure_element_iter_new(doc);
    ASSERT_NE(root_iter, nullptr);

    PopplerStructureElementIter *child_iter = poppler_structure_element_iter_get_child(root_iter);
    ASSERT_NE(child_iter, nullptr);

    // Drop the caller reference. If get_child took a ref internally for the child iter,
    // the document should NOT be finalized yet.
    g_object_unref(doc);
    EXPECT_FALSE(finalized);

    // Freeing the root iter may drop one internal ref, but the child iter should still keep it alive.
    poppler_structure_element_iter_free(root_iter);
    EXPECT_FALSE(finalized);

    // Once the child iter is freed, the document should be allowed to finalize.
    poppler_structure_element_iter_free(child_iter);
    EXPECT_TRUE(finalized);
}

} // namespace