// File: poppler-document-get-n-pages-test-2151.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <glib-object.h>

#include <poppler.h>

#include <cstddef>
#include <sstream>
#include <string>
#include <vector>

namespace {

class ScopedGLogCapture {
public:
    ScopedGLogCapture()
        : old_handler_(g_log_set_default_handler(&ScopedGLogCapture::Handler, this))
    {
    }

    ~ScopedGLogCapture() { g_log_set_default_handler(old_handler_, nullptr); }

    int critical_count() const { return critical_count_; }

private:
    static void Handler(const gchar* /*log_domain*/,
                        GLogLevelFlags log_level,
                        const gchar* /*message*/,
                        gpointer user_data)
    {
        auto* self = static_cast<ScopedGLogCapture*>(user_data);
        if (log_level & G_LOG_LEVEL_CRITICAL) {
            self->critical_count_++;
        }
        // Swallow logs to keep test output clean.
    }

    GLogFunc old_handler_ = nullptr;
    int critical_count_ = 0;
};

// Build a minimal-but-valid PDF with N blank pages, with correct xref offsets.
// This is test data generation; it does not depend on Poppler internals.
static std::string BuildMinimalPdfWithNPages(int n_pages)
{
    // Objects:
    // 1: Catalog -> /Pages 2 0 R
    // 2: Pages -> /Count N /Kids [page objs...]
    // For each page i:
    //   page obj: /Type /Page /Parent 2 0 R /MediaBox [...] /Contents content_i 0 R /Resources <<>>
    //   content obj: stream with a single space
    //
    // Total objects = 2 + 2*N
    const int first_page_obj = 3;
    const int first_content_obj = first_page_obj + n_pages;

    std::vector<std::string> objs;
    objs.reserve(static_cast<size_t>(2 + 2 * n_pages));

    {
        std::ostringstream o;
        o << "1 0 obj\n"
          << "<< /Type /Catalog /Pages 2 0 R >>\n"
          << "endobj\n";
        objs.push_back(o.str());
    }

    {
        std::ostringstream kids;
        kids << "[ ";
        for (int i = 0; i < n_pages; ++i) {
            kids << (first_page_obj + i) << " 0 R ";
        }
        kids << "]";

        std::ostringstream o;
        o << "2 0 obj\n"
          << "<< /Type /Pages /Count " << n_pages << " /Kids " << kids.str() << " >>\n"
          << "endobj\n";
        objs.push_back(o.str());
    }

    for (int i = 0; i < n_pages; ++i) {
        const int page_id = first_page_obj + i;
        const int content_id = first_content_obj + i;

        {
            std::ostringstream o;
            o << page_id << " 0 obj\n"
              << "<< /Type /Page /Parent 2 0 R "
              << "/MediaBox [0 0 612 792] "
              << "/Contents " << content_id << " 0 R "
              << "/Resources << >> >>\n"
              << "endobj\n";
            objs.push_back(o.str());
        }

        {
            // Stream contains a single space; Length=1.
            std::ostringstream o;
            o << content_id << " 0 obj\n"
              << "<< /Length 1 >>\n"
              << "stream\n"
              << " \n"
              << "endstream\n"
              << "endobj\n";
            objs.push_back(o.str());
        }
    }

    std::string pdf;
    pdf.reserve(2048);

    pdf += "%PDF-1.4\n";

    // xref offsets: index 0 is the free object.
    const int num_objects = 2 + 2 * n_pages;
    std::vector<size_t> offsets(static_cast<size_t>(num_objects + 1), 0);

    for (int obj_index = 1; obj_index <= num_objects; ++obj_index) {
        offsets[static_cast<size_t>(obj_index)] = pdf.size();
        pdf += objs[static_cast<size_t>(obj_index - 1)];
    }

    const size_t xref_start = pdf.size();
    {
        std::ostringstream x;
        x << "xref\n"
          << "0 " << (num_objects + 1) << "\n"
          << "0000000000 65535 f \n";
        for (int i = 1; i <= num_objects; ++i) {
            // PDF xref uses 10-digit, zero-padded byte offsets.
            char buf[64];
            std::snprintf(buf, sizeof(buf), "%010zu 00000 n \n", offsets[static_cast<size_t>(i)]);
            x << buf;
        }
        pdf += x.str();
    }

    {
        std::ostringstream t;
        t << "trailer\n"
          << "<< /Size " << (num_objects + 1) << " /Root 1 0 R >>\n"
          << "startxref\n"
          << xref_start << "\n"
          << "%%EOF\n";
        pdf += t.str();
    }

    return pdf;
}

struct GErrorDeleter {
    void operator()(GError* e) const
    {
        if (e) {
            g_error_free(e);
        }
    }
};

class PopplerDocumentGetNPagesTest_2151 : public ::testing::Test {
protected:
    static PopplerDocument* LoadDocFromPdfBytesOrFail(const std::string& pdf)
    {
        std::unique_ptr<GError, GErrorDeleter> err(nullptr);

        // poppler_document_new_from_data() is public Poppler GLib API.
        PopplerDocument* doc =
            poppler_document_new_from_data(pdf.data(), static_cast<int>(pdf.size()), /*password*/ nullptr, &err);

        EXPECT_EQ(err.get(), nullptr);
        EXPECT_NE(doc, nullptr);
        return doc;
    }
};

TEST_F(PopplerDocumentGetNPagesTest_2151, NullDocumentReturnsZeroAndLogsCritical_2151)
{
    ScopedGLogCapture log;

    const int n = poppler_document_get_n_pages(nullptr);
    EXPECT_EQ(n, 0);
    EXPECT_GE(log.critical_count(), 1);
}

TEST_F(PopplerDocumentGetNPagesTest_2151, NonDocumentGObjectReturnsZeroAndLogsCritical_2151)
{
    ScopedGLogCapture log;

    // Create a valid GObject instance of the wrong type, then cast.
    GObject* not_a_doc = G_OBJECT(g_object_new(G_TYPE_OBJECT, nullptr));
    ASSERT_NE(not_a_doc, nullptr);

    const int n = poppler_document_get_n_pages(reinterpret_cast<PopplerDocument*>(not_a_doc));
    EXPECT_EQ(n, 0);
    EXPECT_GE(log.critical_count(), 1);

    g_object_unref(not_a_doc);
}

TEST_F(PopplerDocumentGetNPagesTest_2151, OnePagePdfReturnsOne_2151)
{
    const std::string pdf = BuildMinimalPdfWithNPages(1);
    PopplerDocument* doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    EXPECT_EQ(poppler_document_get_n_pages(doc), 1);

    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetNPagesTest_2151, TwoPagePdfReturnsTwo_2151)
{
    const std::string pdf = BuildMinimalPdfWithNPages(2);
    PopplerDocument* doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    EXPECT_EQ(poppler_document_get_n_pages(doc), 2);

    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetNPagesTest_2151, MultiplePagesPdfReturnsExactCount_Boundary_2151)
{
    const int kPages = 10; // boundary-ish: more than trivial, still small/fast
    const std::string pdf = BuildMinimalPdfWithNPages(kPages);
    PopplerDocument* doc = LoadDocFromPdfBytesOrFail(pdf);
    ASSERT_NE(doc, nullptr);

    EXPECT_EQ(poppler_document_get_n_pages(doc), kPages);

    g_object_unref(doc);
}

} // namespace