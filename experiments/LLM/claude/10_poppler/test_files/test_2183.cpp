#include <glib.h>
#include <glib-object.h>
#include <poppler.h>
#include <gtest/gtest.h>
#include <cstring>

class PopplerDocumentSetProducerTest_2183 : public ::testing::Test {
protected:
    PopplerDocument *document = nullptr;

    void SetUp() override {
        // Create a minimal PDF in memory to get a valid PopplerDocument
        // This is a minimal valid PDF
        const char *pdf_content =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\n"
            "endobj\n"
            "xref\n"
            "0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n"
            "<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n"
            "190\n"
            "%%EOF\n";

        gsize length = strlen(pdf_content);
        GBytes *bytes = g_bytes_new(pdf_content, length);
        GInputStream *stream = g_memory_input_stream_new_from_bytes(bytes);
        g_bytes_unref(bytes);

        GError *error = nullptr;
        document = poppler_document_new_from_stream(stream, length, nullptr, nullptr, &error);
        g_object_unref(stream);

        if (error) {
            g_error_free(error);
        }

        // If stream-based loading doesn't work, try from data
        if (!document) {
            document = poppler_document_new_from_data((char *)pdf_content, (int)length, nullptr, &error);
            if (error) {
                g_error_free(error);
                error = nullptr;
            }
        }
    }

    void TearDown() override {
        if (document) {
            g_object_unref(document);
            document = nullptr;
        }
    }
};

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithValidString_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *producer = "TestProducer";
    poppler_document_set_producer(document, producer);

    gchar *retrieved = poppler_document_get_producer(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, producer);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithNullString_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // First set a producer
    poppler_document_set_producer(document, "InitialProducer");

    // Then set to NULL which should clear it
    poppler_document_set_producer(document, nullptr);

    gchar *retrieved = poppler_document_get_producer(document);
    // After setting NULL, producer should be cleared (NULL or empty)
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithEmptyString_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_producer(document, "");

    gchar *retrieved = poppler_document_get_producer(document);
    if (retrieved != nullptr) {
        EXPECT_STREQ(retrieved, "");
        g_free(retrieved);
    }
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithUTF8String_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *producer = "Tëst Prödücer ñ";
    poppler_document_set_producer(document, producer);

    gchar *retrieved = poppler_document_get_producer(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, producer);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerOverwritesPrevious_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    poppler_document_set_producer(document, "FirstProducer");
    poppler_document_set_producer(document, "SecondProducer");

    gchar *retrieved = poppler_document_get_producer(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "SecondProducer");
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithNullDocument_2183) {
    // Should not crash - g_return_if_fail should handle this
    poppler_document_set_producer(nullptr, "SomeProducer");
    // If we get here without crashing, the guard worked
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithLongString_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    // Create a long producer string
    std::string long_producer(10000, 'A');
    poppler_document_set_producer(document, long_producer.c_str());

    gchar *retrieved = poppler_document_get_producer(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, long_producer.c_str());
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerWithSpecialCharacters_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    const gchar *producer = "Producer (v1.0) <test> & \"quoted\"";
    poppler_document_set_producer(document, producer);

    gchar *retrieved = poppler_document_get_producer(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, producer);
    g_free(retrieved);
}

TEST_F(PopplerDocumentSetProducerTest_2183, SetProducerMultipleTimes_2183) {
    if (!document) {
        GTEST_SKIP() << "Could not create test document";
    }

    for (int i = 0; i < 100; i++) {
        std::string producer = "Producer_" + std::to_string(i);
        poppler_document_set_producer(document, producer.c_str());
    }

    gchar *retrieved = poppler_document_get_producer(document);
    ASSERT_NE(retrieved, nullptr);
    EXPECT_STREQ(retrieved, "Producer_99");
    g_free(retrieved);
}
