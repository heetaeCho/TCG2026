// TEST_ID: 2183
// File: poppler-document-set-producer-test-2183.cc

#include <gtest/gtest.h>

#include <glib.h>
#include <glib/gstdio.h>

#include <poppler.h>

#include <string>
#include <vector>

// Build a minimal, valid PDF file in-memory with correct xref offsets.
// (Test helper only; does not attempt to mimic Poppler internals.)
static std::string BuildMinimalPdf()
{
    std::string pdf;
    pdf += "%PDF-1.4\n";
    pdf += "%\xE2\xE3\xCF\xD3\n";

    // Record offsets for objects 1..5 (0 is free).
    std::vector<size_t> offsets(6, 0);

    auto append_obj = [&](int objNum, const std::string &body) {
        offsets[objNum] = pdf.size();
        pdf += std::to_string(objNum) + " 0 obj\n";
        pdf += body;
        if (!body.empty() && body.back() != '\n') {
            pdf += "\n";
        }
        pdf += "endobj\n";
    };

    // 1: Catalog
    append_obj(1, "<< /Type /Catalog /Pages 2 0 R >>\n");

    // 2: Pages
    append_obj(2, "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n");

    // 3: Page
    append_obj(3, "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 200 200] /Contents 4 0 R >>\n");

    // 4: Contents stream (empty / minimal)
    {
        std::string stream = "<< /Length 0 >>\nstream\n\nendstream\n";
        append_obj(4, stream);
    }

    // 5: Info dictionary (initial producer set, so get_producer has a baseline)
    append_obj(5, "<< /Producer (InitialProducer) >>\n");

    // xref
    const size_t xref_offset = pdf.size();
    pdf += "xref\n";
    pdf += "0 6\n";
    pdf += "0000000000 65535 f \n";

    auto fmt_off = [](size_t off) {
        char buf[32];
        // PDF xref uses 10-digit, zero-padded offsets.
        g_snprintf(buf, sizeof(buf), "%010lu", static_cast<unsigned long>(off));
        return std::string(buf);
    };

    for (int i = 1; i <= 5; ++i) {
        pdf += fmt_off(offsets[i]) + " 00000 n \n";
    }

    // trailer
    pdf += "trailer\n";
    pdf += "<< /Size 6 /Root 1 0 R /Info 5 0 R >>\n";
    pdf += "startxref\n";
    pdf += std::to_string(xref_offset) + "\n";
    pdf += "%%EOF\n";

    return pdf;
}

static PopplerDocument *CreatePopplerDocumentFromTempPdf(GError **error_out)
{
    const std::string pdf = BuildMinimalPdf();

    gchar *tmp_path = nullptr;
    gint fd = g_file_open_tmp("poppler-set-producer-XXXXXX.pdf", &tmp_path, error_out);
    if (fd < 0 || tmp_path == nullptr) {
        if (tmp_path) {
            g_free(tmp_path);
        }
        return nullptr;
    }

    // Write bytes to file.
    FILE *fp = fdopen(fd, "wb");
    if (!fp) {
        close(fd);
        g_unlink(tmp_path);
        g_free(tmp_path);
        g_set_error_literal(error_out, g_quark_from_static_string("test"), 1, "fdopen failed");
        return nullptr;
    }

    const size_t wrote = fwrite(pdf.data(), 1, pdf.size(), fp);
    fclose(fp);

    if (wrote != pdf.size()) {
        g_unlink(tmp_path);
        g_free(tmp_path);
        g_set_error_literal(error_out, g_quark_from_static_string("test"), 2, "fwrite incomplete");
        return nullptr;
    }

    gchar *uri = g_filename_to_uri(tmp_path, nullptr, error_out);
    g_unlink(tmp_path);
    g_free(tmp_path);

    if (!uri) {
        return nullptr;
    }

    PopplerDocument *doc = poppler_document_new_from_file(uri, /*password=*/nullptr, error_out);
    g_free(uri);
    return doc;
}

static std::string GetProducerString(PopplerDocument *doc)
{
    gchar *producer = poppler_document_get_producer(doc);
    if (!producer) {
        return std::string();
    }
    std::string out(producer);
    g_free(producer);
    return out;
}

class PopplerDocumentSetProducerTest_2183 : public ::testing::Test {
protected:
    void SetUp() override
    {
        GError *error = nullptr;
        doc_ = CreatePopplerDocumentFromTempPdf(&error);
        ASSERT_NE(doc_, nullptr) << (error ? error->message : "Unknown error creating PopplerDocument");
        if (error) {
            g_error_free(error);
        }
    }

    void TearDown() override
    {
        if (doc_) {
            g_object_unref(doc_);
            doc_ = nullptr;
        }
    }

    PopplerDocument *doc_ = nullptr;
};

TEST(PopplerDocumentSetProducerStandaloneTest_2183, NullDocumentTriggersCriticalAndReturns_2183)
{
    // poppler_document_set_producer() has g_return_if_fail(POPPLER_IS_DOCUMENT(document))
    // Observable behavior: emits a critical log and returns without crashing.
    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    poppler_document_set_producer(nullptr, "Producer");
    g_test_assert_expected_messages();
}

TEST(PopplerDocumentSetProducerStandaloneTest_2183, WrongTypePointerTriggersCriticalAndReturns_2183)
{
    // Pass a non-PopplerDocument GObject pointer casted to PopplerDocument*.
    // Observable behavior: emits a critical log and returns without crashing.
    GObject *obj = g_object_new(G_TYPE_OBJECT, nullptr);
    ASSERT_NE(obj, nullptr);

    g_test_expect_message("Poppler", G_LOG_LEVEL_CRITICAL, "*POPPLER_IS_DOCUMENT*");
    poppler_document_set_producer(reinterpret_cast<PopplerDocument *>(obj), "Producer");
    g_test_assert_expected_messages();

    g_object_unref(obj);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerValidUtf8UpdatesGetProducer_2183)
{
    const char *kProducer = "UnitTestProducer-2183";
    poppler_document_set_producer(doc_, kProducer);

    const std::string got = GetProducerString(doc_);
    EXPECT_EQ(got, kProducer);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerEmptyStringIsAcceptedAndObservable_2183)
{
    poppler_document_set_producer(doc_, "");

    const std::string got = GetProducerString(doc_);
    EXPECT_EQ(got, std::string(""));
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerNullClearsOrEmptiesProducer_2183)
{
    // First set a known value.
    poppler_document_set_producer(doc_, "BeforeNull-2183");
    const std::string before = GetProducerString(doc_);
    ASSERT_EQ(before, "BeforeNull-2183");

    // Then set nullptr (interface allows it).
    poppler_document_set_producer(doc_, nullptr);

    // Different Poppler versions may represent "cleared" as nullptr or empty string via get_producer.
    // We accept either, but require it no longer equals the previous value.
    gchar *producer = poppler_document_get_producer(doc_);
    if (producer) {
        std::string got(producer);
        g_free(producer);
        EXPECT_TRUE(got.empty()) << "Expected cleared producer to be empty string if non-null";
    } else {
        SUCCEED() << "Producer cleared to nullptr as reported by poppler_document_get_producer()";
    }
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerInvalidUtf8DoesNotChangeProducer_2183)
{
    // Baseline
    poppler_document_set_producer(doc_, "Baseline-2183");
    const std::string baseline = GetProducerString(doc_);
    ASSERT_EQ(baseline, "Baseline-2183");

    // Invalid UTF-8 sequence (0xC3 0x28) - commonly invalid.
    const gchar invalid_utf8[] = {static_cast<gchar>(0xC3), static_cast<gchar>(0x28), 0};

    // Function is expected to return early if conversion fails (observable: producer remains unchanged).
    poppler_document_set_producer(doc_, invalid_utf8);

    const std::string after = GetProducerString(doc_);
    EXPECT_EQ(after, baseline);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerVeryLongStringRoundTrips_2183)
{
    // Boundary: long UTF-8 string (ASCII) to ensure API can handle large inputs.
    std::string long_producer(4096, 'A');
    long_producer += "-END-2183";

    poppler_document_set_producer(doc_, long_producer.c_str());

    const std::string got = GetProducerString(doc_);
    EXPECT_EQ(got, long_producer);
}