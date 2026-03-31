#include <glib.h>
#include <glib-object.h>
#include <poppler-document.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>
#include <cstdlib>

class PopplerDocumentGetProducerTest_2182 : public ::testing::Test {
protected:
    PopplerDocument *doc_with_producer = nullptr;
    PopplerDocument *doc_without_producer = nullptr;

    void SetUp() override {
        // We'll try to load a PDF that has producer metadata
        // and one that might not, using poppler_document_new_from_file or from_data
    }

    void TearDown() override {
        if (doc_with_producer) {
            g_object_unref(doc_with_producer);
            doc_with_producer = nullptr;
        }
        if (doc_without_producer) {
            g_object_unref(doc_without_producer);
            doc_without_producer = nullptr;
        }
    }

    // Helper to create a minimal PDF in memory with a given Producer field
    PopplerDocument *create_pdf_with_producer(const char *producer) {
        // Build a minimal PDF with Info dict containing Producer
        GString *pdf = g_string_new(nullptr);
        g_string_append(pdf, "%PDF-1.4\n");
        g_string_append(pdf, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
        g_string_append(pdf, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
        g_string_append(pdf, "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");

        if (producer) {
            g_string_append_printf(pdf, "4 0 obj\n<< /Producer (%s) >>\nendobj\n", producer);
        } else {
            g_string_append(pdf, "4 0 obj\n<< >>\nendobj\n");
        }

        // xref
        long xref_offset = pdf->len;
        g_string_append(pdf, "xref\n0 5\n");
        g_string_append(pdf, "0000000000 65535 f \n");
        // We need proper offsets but for a quick test we use approximate
        // Let's rebuild with proper offsets

        g_string_free(pdf, TRUE);

        // Use a simpler approach: build the PDF byte by byte with tracked offsets
        char buf[4096];
        int offsets[5];
        int pos = 0;

        pos += snprintf(buf + pos, sizeof(buf) - pos, "%%PDF-1.4\n");

        offsets[1] = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

        offsets[2] = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

        offsets[3] = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");

        offsets[4] = pos;
        if (producer) {
            pos += snprintf(buf + pos, sizeof(buf) - pos, "4 0 obj\n<< /Producer (%s) >>\nendobj\n", producer);
        } else {
            pos += snprintf(buf + pos, sizeof(buf) - pos, "4 0 obj\n<< >>\nendobj\n");
        }

        int xref_pos = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "xref\n0 5\n");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "0000000000 65535 f \n");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[1]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[2]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[3]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[4]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "startxref\n%d\n%%%%EOF\n", xref_pos);

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(buf, pos);
        PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
        g_bytes_unref(bytes);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }

    PopplerDocument *create_minimal_pdf_no_info() {
        char buf[4096];
        int offsets[4];
        int pos = 0;

        pos += snprintf(buf + pos, sizeof(buf) - pos, "%%PDF-1.4\n");

        offsets[1] = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");

        offsets[2] = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");

        offsets[3] = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");

        int xref_pos = pos;
        pos += snprintf(buf + pos, sizeof(buf) - pos, "xref\n0 4\n");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "0000000000 65535 f \n");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[1]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[2]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "%010d 00000 n \n", offsets[3]);
        pos += snprintf(buf + pos, sizeof(buf) - pos, "trailer\n<< /Size 4 /Root 1 0 R >>\n");
        pos += snprintf(buf + pos, sizeof(buf) - pos, "startxref\n%d\n%%%%EOF\n", xref_pos);

        GError *error = nullptr;
        GBytes *bytes = g_bytes_new(buf, pos);
        PopplerDocument *doc = poppler_document_new_from_bytes(bytes, nullptr, &error);
        g_bytes_unref(bytes);

        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return doc;
    }
};

TEST_F(PopplerDocumentGetProducerTest_2182, NullDocumentReturnsNull_2182) {
    // Passing NULL should return NULL (g_return_val_if_fail check)
    gchar *result = poppler_document_get_producer(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerDocumentGetProducerTest_2182, DocumentWithProducerReturnsProducerString_2182) {
    PopplerDocument *doc = create_pdf_with_producer("TestProducerApp");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *producer = poppler_document_get_producer(doc);
    ASSERT_NE(producer, nullptr);
    EXPECT_STREQ(producer, "TestProducerApp");
    g_free(producer);
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, DocumentWithoutInfoDictReturnsNull_2182) {
    PopplerDocument *doc = create_minimal_pdf_no_info();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF without info";
    }

    gchar *producer = poppler_document_get_producer(doc);
    // No Info dict means no producer
    EXPECT_EQ(producer, nullptr);
    if (producer) {
        g_free(producer);
    }
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, DocumentWithEmptyInfoDictReturnsNull_2182) {
    PopplerDocument *doc = create_pdf_with_producer(nullptr);
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with empty info";
    }

    gchar *producer = poppler_document_get_producer(doc);
    // Info dict exists but has no Producer key
    EXPECT_EQ(producer, nullptr);
    if (producer) {
        g_free(producer);
    }
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, DocumentWithEmptyProducerString_2182) {
    PopplerDocument *doc = create_pdf_with_producer("");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF with empty producer";
    }

    gchar *producer = poppler_document_get_producer(doc);
    // Empty producer string - could be NULL or empty string
    if (producer != nullptr) {
        EXPECT_STREQ(producer, "");
        g_free(producer);
    }
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, ReturnedStringIsFreeable_2182) {
    PopplerDocument *doc = create_pdf_with_producer("SomeProducer");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *producer = poppler_document_get_producer(doc);
    // The returned string should be a newly allocated string that can be freed
    if (producer) {
        g_free(producer);
    }
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, MultipleCallsReturnConsistentResults_2182) {
    PopplerDocument *doc = create_pdf_with_producer("ConsistentProducer");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *producer1 = poppler_document_get_producer(doc);
    gchar *producer2 = poppler_document_get_producer(doc);

    ASSERT_NE(producer1, nullptr);
    ASSERT_NE(producer2, nullptr);
    EXPECT_STREQ(producer1, producer2);
    // They should be different allocations
    EXPECT_NE(producer1, producer2);

    g_free(producer1);
    g_free(producer2);
    g_object_unref(doc);
}

TEST_F(PopplerDocumentGetProducerTest_2182, ProducerWithSpecialCharacters_2182) {
    PopplerDocument *doc = create_pdf_with_producer("Producer with spaces & chars 123");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *producer = poppler_document_get_producer(doc);
    ASSERT_NE(producer, nullptr);
    EXPECT_STREQ(producer, "Producer with spaces & chars 123");
    g_free(producer);
    g_object_unref(doc);
}
