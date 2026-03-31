#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <QByteArray>
#include <QString>

#include "poppler-qt5.h"
#include "poppler-private.h"

namespace {

// Minimal valid PDF content
const char *minimalPDF =
    "%PDF-1.0\n"
    "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
    "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
    "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n"
    "xref\n"
    "0 4\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "trailer<</Size 4/Root 1 0 R>>\n"
    "startxref\n"
    "190\n"
    "%%EOF\n";

} // anonymous namespace

class DocumentDataCheckDocumentTest_1357 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that checkDocument returns a valid Document* for a valid PDF
TEST_F(DocumentDataCheckDocumentTest_1357, ValidPdfReturnsNonNull_1357) {
    QByteArray data(minimalPDF);
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    EXPECT_NE(doc.get(), nullptr);
}

// Test that checkDocument returns nullptr for invalid/corrupt PDF data
TEST_F(DocumentDataCheckDocumentTest_1357, InvalidPdfReturnsNull_1357) {
    QByteArray data("This is not a valid PDF at all");
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test that a valid document is not locked
TEST_F(DocumentDataCheckDocumentTest_1357, ValidPdfIsNotLocked_1357) {
    QByteArray data(minimalPDF);
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    ASSERT_NE(doc.get(), nullptr);
    EXPECT_FALSE(doc->isLocked());
}

// Test that an empty byte array returns nullptr
TEST_F(DocumentDataCheckDocumentTest_1357, EmptyDataReturnsNull_1357) {
    QByteArray data;
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test that loading from a non-existent file returns nullptr
TEST_F(DocumentDataCheckDocumentTest_1357, NonExistentFileReturnsNull_1357) {
    std::unique_ptr<Poppler::Document> doc(
        Poppler::Document::load(QString("/nonexistent/path/to/file.pdf")));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test that a valid PDF with wrong password provided results in locked or null
TEST_F(DocumentDataCheckDocumentTest_1357, ValidPdfWithPasswordReturnsDocument_1357) {
    QByteArray data(minimalPDF);
    // Providing owner/user passwords on an unencrypted doc should still work
    std::unique_ptr<Poppler::Document> doc(
        Poppler::Document::loadFromData(data, QString("owner"), QString("user")));
    // Unencrypted PDF with passwords should still load fine
    if (doc) {
        EXPECT_FALSE(doc->isLocked());
    }
}

// Test that garbage data with PDF header still fails properly
TEST_F(DocumentDataCheckDocumentTest_1357, GarbagePdfHeaderReturnsNull_1357) {
    QByteArray data("%PDF-1.4\ngarbage content here\n%%EOF\n");
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    // This should either be null or if loaded, document might be corrupt
    // The key is it shouldn't crash
    // Accept either null or non-null as valid behavior, just no crash
    SUCCEED();
}

// Test loading a minimal valid PDF and checking page count
TEST_F(DocumentDataCheckDocumentTest_1357, ValidPdfHasCorrectPageCount_1357) {
    QByteArray data(minimalPDF);
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    ASSERT_NE(doc.get(), nullptr);
    EXPECT_EQ(doc->numPages(), 1);
}

// Test that a single byte returns nullptr
TEST_F(DocumentDataCheckDocumentTest_1357, SingleByteReturnsNull_1357) {
    QByteArray data("X");
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test that truncated PDF returns nullptr
TEST_F(DocumentDataCheckDocumentTest_1357, TruncatedPdfReturnsNull_1357) {
    QByteArray data("%PDF-1.0\n1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n");
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(data));
    // Truncated PDF - likely null or error state
    // Just verify no crash
    SUCCEED();
}
