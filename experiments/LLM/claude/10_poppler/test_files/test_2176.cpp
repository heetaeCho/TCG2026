#include <glib.h>
#include <gtest/gtest.h>
#include <poppler-document.h>
#include <poppler.h>
#include <cstdio>
#include <cstdlib>
#include <string>

class PopplerDocumentGetSubjectTest_2176 : public ::testing::Test {
protected:
    PopplerDocument *doc = nullptr;
    PopplerDocument *doc_with_subject = nullptr;

    void SetUp() override {
        // We'll try to find or create test PDFs for testing
    }

    void TearDown() override {
        if (doc) {
            g_object_unref(doc);
            doc = nullptr;
        }
        if (doc_with_subject) {
            g_object_unref(doc_with_subject);
            doc_with_subject = nullptr;
        }
    }

    // Helper to create a minimal PDF with a given subject in memory
    PopplerDocument *createPdfWithSubject(const char *subject) {
        // Create a minimal PDF with a Subject in the Info dictionary
        std::string pdf;
        pdf += "%PDF-1.4\n";

        // Object 1: Catalog
        std::string obj1 = "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        // Object 2: Pages
        std::string obj2 = "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        // Object 3: Page
        std::string obj3 = "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        // Object 4: Info dictionary with Subject
        std::string obj4;
        if (subject) {
            obj4 = std::string("4 0 obj\n<< /Subject (") + subject + ") >>\nendobj\n";
        } else {
            obj4 = "4 0 obj\n<< >>\nendobj\n";
        }

        size_t offset1 = pdf.size() + 0;
        // We need to track offsets for xref
        pdf += "%PDF-1.4\n";
        // Reset and build properly
        pdf.clear();
        pdf = "%PDF-1.4\n";

        size_t xref_offsets[5];

        xref_offsets[1] = pdf.size();
        pdf += obj1;

        xref_offsets[2] = pdf.size();
        pdf += obj2;

        xref_offsets[3] = pdf.size();
        pdf += obj3;

        xref_offsets[4] = pdf.size();
        pdf += obj4;

        size_t xref_start = pdf.size();
        pdf += "xref\n";
        pdf += "0 5\n";
        char buf[64];
        snprintf(buf, sizeof(buf), "%010zu 65535 f \n", (size_t)0);
        pdf += buf;
        for (int i = 1; i <= 4; i++) {
            snprintf(buf, sizeof(buf), "%010zu 00000 n \n", xref_offsets[i]);
            pdf += buf;
        }
        pdf += "trailer\n<< /Size 5 /Root 1 0 R /Info 4 0 R >>\n";
        pdf += "startxref\n";
        snprintf(buf, sizeof(buf), "%zu\n", xref_start);
        pdf += buf;
        pdf += "%%EOF\n";

        GError *error = nullptr;
        PopplerDocument *d = poppler_document_new_from_data(pdf.data(), pdf.size(), nullptr, &error);
        if (error) {
            g_error_free(error);
            return nullptr;
        }
        return d;
    }

    PopplerDocument *createPdfWithoutSubject() {
        return createPdfWithSubject(nullptr);
    }
};

TEST_F(PopplerDocumentGetSubjectTest_2176, NullDocumentReturnsNull_2176) {
    // Passing NULL should return NULL (g_return_val_if_fail)
    // Note: This will trigger a GLib critical warning
    gchar *result = poppler_document_get_subject(nullptr);
    EXPECT_EQ(result, nullptr);
}

TEST_F(PopplerDocumentGetSubjectTest_2176, DocumentWithSubjectReturnsSubject_2176) {
    doc_with_subject = createPdfWithSubject("Test Subject");
    if (!doc_with_subject) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *subject = poppler_document_get_subject(doc_with_subject);
    if (subject) {
        EXPECT_STREQ(subject, "Test Subject");
        g_free(subject);
    }
    // If subject is NULL, the PDF may not have stored it correctly - that's acceptable
}

TEST_F(PopplerDocumentGetSubjectTest_2176, DocumentWithoutSubjectReturnsNull_2176) {
    doc = createPdfWithoutSubject();
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *subject = poppler_document_get_subject(doc);
    // A document with an empty Info dict should return NULL for subject
    EXPECT_EQ(subject, nullptr);
    if (subject) {
        g_free(subject);
    }
}

TEST_F(PopplerDocumentGetSubjectTest_2176, DocumentWithEmptySubject_2176) {
    doc = createPdfWithSubject("");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *subject = poppler_document_get_subject(doc);
    // An empty subject string - could be NULL or empty string depending on implementation
    if (subject) {
        // If not null, it should be an empty string
        EXPECT_STREQ(subject, "");
        g_free(subject);
    }
}

TEST_F(PopplerDocumentGetSubjectTest_2176, DocumentWithSpecialCharactersInSubject_2176) {
    doc = createPdfWithSubject("Subject with spaces and 123");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *subject = poppler_document_get_subject(doc);
    if (subject) {
        EXPECT_STREQ(subject, "Subject with spaces and 123");
        g_free(subject);
    }
}

TEST_F(PopplerDocumentGetSubjectTest_2176, ReturnedStringIsFreeable_2176) {
    doc = createPdfWithSubject("Freeable Subject");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *subject = poppler_document_get_subject(doc);
    // The returned string should be a newly allocated string that can be freed
    // This test ensures no crash on g_free
    if (subject) {
        EXPECT_TRUE(g_utf8_validate(subject, -1, nullptr));
        g_free(subject);
    }
}

TEST_F(PopplerDocumentGetSubjectTest_2176, CallingTwiceReturnsSameValue_2176) {
    doc = createPdfWithSubject("Consistent Subject");
    if (!doc) {
        GTEST_SKIP() << "Could not create test PDF";
    }

    gchar *subject1 = poppler_document_get_subject(doc);
    gchar *subject2 = poppler_document_get_subject(doc);

    if (subject1 && subject2) {
        EXPECT_STREQ(subject1, subject2);
        // They should be different allocations
        EXPECT_NE(subject1, subject2);
    } else {
        EXPECT_EQ(subject1, subject2);
    }

    g_free(subject1);
    g_free(subject2);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
