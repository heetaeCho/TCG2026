// File: poppler-form-field-is-read-only-test-2311.cc
#include <gtest/gtest.h>

#include <glib.h>
#include <poppler.h>

#include <cstdio>
#include <cstdlib>
#include <string>
#include <vector>

namespace {

class ScopedNoFatalGLibLog {
public:
    ScopedNoFatalGLibLog()
    {
        old_ = g_log_set_always_fatal(static_cast<GLogLevelFlags>(0));
        // Keep existing fatal flags except make CRITICAL/WARNING non-fatal.
        g_log_set_always_fatal(static_cast<GLogLevelFlags>(old_ & ~(G_LOG_LEVEL_CRITICAL | G_LOG_LEVEL_WARNING)));
    }
    ~ScopedNoFatalGLibLog() { g_log_set_always_fatal(old_); }

private:
    GLogLevelFlags old_;
};

static std::string BuildPdfTwoTextFields(bool firstReadOnly, bool secondReadOnly)
{
    // Build a minimal PDF with 1 page and two text fields (each with one widget annotation).
    // Field flags: ReadOnly bit is 1.
    const int ff1 = firstReadOnly ? 1 : 0;
    const int ff2 = secondReadOnly ? 1 : 0;

    std::vector<std::string> obj(10); // 1..9 used

    // 1: Catalog with AcroForm
    obj[1] =
        "<< /Type /Catalog /Pages 2 0 R /AcroForm 5 0 R >>";

    // 2: Pages
    obj[2] =
        "<< /Type /Pages /Kids [3 0 R] /Count 1 >>";

    // 3: Page with Annots [6 0 R 7 0 R]
    obj[3] =
        "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] "
        "/Contents 4 0 R "
        "/Annots [6 0 R 7 0 R] >>";

    // 4: Empty content stream
    obj[4] =
        "<< /Length 0 >>\n"
        "stream\n"
        "\n"
        "endstream";

    // 5: AcroForm with Fields [8 0 R 9 0 R]
    obj[5] =
        "<< /Fields [8 0 R 9 0 R] /NeedAppearances true >>";

    // 6: Widget for field 8 (read-only controlled by /Ff in parent field)
    obj[6] =
        "<< /Type /Annot /Subtype /Widget "
        "/Parent 8 0 R "
        "/Rect [10 10 100 30] "
        "/P 3 0 R >>";

    // 7: Widget for field 9
    obj[7] =
        "<< /Type /Annot /Subtype /Widget "
        "/Parent 9 0 R "
        "/Rect [10 50 100 70] "
        "/P 3 0 R >>";

    // 8: Field 1 (Tx)
    obj[8] =
        (std::string("<< /FT /Tx /T (FieldOne) /Ff ") + std::to_string(ff1) +
         " /V (A) /Kids [6 0 R] >>");

    // 9: Field 2 (Tx)
    obj[9] =
        (std::string("<< /FT /Tx /T (FieldTwo) /Ff ") + std::to_string(ff2) +
         " /V (B) /Kids [7 0 R] >>");

    std::string pdf;
    pdf.reserve(4096);
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n";

    std::vector<size_t> offsets(10, 0);

    for (int i = 1; i <= 9; ++i) {
        offsets[i] = pdf.size();
        pdf += std::to_string(i) + " 0 obj\n";
        pdf += obj[i];
        pdf += "\nendobj\n";
    }

    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 10\n";
    pdf += "0000000000 65535 f \n";
    for (int i = 1; i <= 9; ++i) {
        char line[32];
        std::snprintf(line, sizeof(line), "%010lu 00000 n \n", static_cast<unsigned long>(offsets[i]));
        pdf += line;
    }

    pdf += "trailer\n";
    pdf += "<< /Size 10 /Root 1 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(static_cast<unsigned long>(xref_offset)) + "\n";
    pdf += "%%EOF\n";
    return pdf;
}

class TempPdfFile {
public:
    explicit TempPdfFile(const std::string& bytes)
    {
        char tmpl[] = "poppler_form_ro_XXXXXX.pdf";
        fd_ = g_mkstemp(tmpl);
        ASSERT_NE(fd_, -1) << "Failed to create temp pdf file";

        path_ = tmpl;

        // Write bytes
        size_t total = 0;
        while (total < bytes.size()) {
            const ssize_t n = ::write(fd_, bytes.data() + total, bytes.size() - total);
            ASSERT_GT(n, 0) << "Failed to write PDF bytes";
            total += static_cast<size_t>(n);
        }

        ::close(fd_);
        fd_ = -1;

        GError* err = nullptr;
        uri_ = g_filename_to_uri(path_.c_str(), /*hostname=*/nullptr, &err);
        ASSERT_NE(uri_, nullptr) << "g_filename_to_uri failed: " << (err ? err->message : "unknown");
        if (err)
            g_error_free(err);
    }

    ~TempPdfFile()
    {
        if (uri_)
            g_free(uri_);
        if (!path_.empty())
            g_remove(path_.c_str());
        if (fd_ != -1)
            ::close(fd_);
    }

    const char* uri() const { return uri_; }

private:
    int fd_{-1};
    std::string path_;
    char* uri_{nullptr};
};

static PopplerDocument* LoadDocOrFail(const char* uri)
{
    GError* error = nullptr;
    PopplerDocument* doc = poppler_document_new_from_file(uri, /*password=*/nullptr, &error);
    if (!doc) {
        std::string msg = "poppler_document_new_from_file failed";
        if (error) {
            msg += ": ";
            msg += error->message;
            g_error_free(error);
        }
        ADD_FAILURE() << msg;
    }
    return doc;
}

static int CountReadOnlyFieldsOnFirstPage(PopplerDocument* doc)
{
    PopplerPage* page = poppler_document_get_page(doc, 0);
    if (!page) {
        ADD_FAILURE() << "Failed to get page 0";
        return -1;
    }

    GList* mappings = poppler_page_get_form_field_mapping(page);
    int count = 0;

    for (GList* it = mappings; it != nullptr; it = it->next) {
        auto* mapping = static_cast<PopplerFormFieldMapping*>(it->data);
        if (!mapping || !mapping->field) {
            continue;
        }
        if (poppler_form_field_is_read_only(mapping->field)) {
            ++count;
        }
    }

    if (mappings) {
        poppler_page_free_form_field_mapping(mappings);
    }
    g_object_unref(page);
    return count;
}

class PopplerFormFieldIsReadOnlyTest_2311 : public ::testing::Test {};

TEST_F(PopplerFormFieldIsReadOnlyTest_2311, NullFieldReturnsFalse_2311)
{
    ScopedNoFatalGLibLog noFatal;
    EXPECT_FALSE(poppler_form_field_is_read_only(nullptr));
}

TEST_F(PopplerFormFieldIsReadOnlyTest_2311, NonFormFieldPointerReturnsFalse_2311)
{
    ScopedNoFatalGLibLog noFatal;

    // Create some other Poppler object and intentionally pass it as PopplerFormField*.
    // The g_return_val_if_fail(POPPLER_IS_FORM_FIELD(field), FALSE) should be observable as FALSE.
    std::string pdfBytes = BuildPdfTwoTextFields(false, false);
    TempPdfFile tmp(pdfBytes);
    PopplerDocument* doc = LoadDocOrFail(tmp.uri());
    ASSERT_NE(doc, nullptr);

    PopplerFormField* notAField = reinterpret_cast<PopplerFormField*>(doc);
    EXPECT_FALSE(poppler_form_field_is_read_only(notAField));

    g_object_unref(doc);
}

TEST_F(PopplerFormFieldIsReadOnlyTest_2311, OneReadOnlyOneEditableCountsOne_2311)
{
    std::string pdfBytes = BuildPdfTwoTextFields(true, false);
    TempPdfFile tmp(pdfBytes);

    PopplerDocument* doc = LoadDocOrFail(tmp.uri());
    ASSERT_NE(doc, nullptr);

    const int roCount = CountReadOnlyFieldsOnFirstPage(doc);
    ASSERT_GE(roCount, 0);
    EXPECT_EQ(roCount, 1);

    g_object_unref(doc);
}

TEST_F(PopplerFormFieldIsReadOnlyTest_2311, BothEditableCountsZero_2311)
{
    std::string pdfBytes = BuildPdfTwoTextFields(false, false);
    TempPdfFile tmp(pdfBytes);

    PopplerDocument* doc = LoadDocOrFail(tmp.uri());
    ASSERT_NE(doc, nullptr);

    const int roCount = CountReadOnlyFieldsOnFirstPage(doc);
    ASSERT_GE(roCount, 0);
    EXPECT_EQ(roCount, 0);

    g_object_unref(doc);
}

TEST_F(PopplerFormFieldIsReadOnlyTest_2311, BothReadOnlyCountsTwo_2311)
{
    std::string pdfBytes = BuildPdfTwoTextFields(true, true);
    TempPdfFile tmp(pdfBytes);

    PopplerDocument* doc = LoadDocOrFail(tmp.uri());
    ASSERT_NE(doc, nullptr);

    const int roCount = CountReadOnlyFieldsOnFirstPage(doc);
    ASSERT_GE(roCount, 0);
    EXPECT_EQ(roCount, 2);

    g_object_unref(doc);
}

} // namespace