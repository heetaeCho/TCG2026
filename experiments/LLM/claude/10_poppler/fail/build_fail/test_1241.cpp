#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QByteArray>
#include <QColor>
#include <QString>
#include <QIODevice>
#include <QBuffer>
#include <QFile>
#include <memory>
#include <optional>

#include "poppler-qt6.h"
#include "poppler-private.h"

namespace {

// Minimal valid PDF content with no embedded files
const QByteArray minimalPdf = QByteArray(
    "%PDF-1.4\n"
    "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
    "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
    "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
    "xref\n0 4\n"
    "0000000000 65535 f \n"
    "0000000009 00000 n \n"
    "0000000058 00000 n \n"
    "0000000115 00000 n \n"
    "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n196\n%%EOF\n"
);

class DocumentDataFillMembersTest_1241 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that fillMembers does not crash with a document that has no embedded files
TEST_F(DocumentDataFillMembersTest_1241, FillMembersNoEmbeddedFiles_1241)
{
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(minimalPdf));
    // If document loads successfully, fillMembers should have been called during init
    // or we can verify the embedded files list is empty
    if (doc) {
        EXPECT_TRUE(doc->embeddedFiles().isEmpty());
    }
}

// Test that loading a document from data works and fillMembers handles zero embedded files
TEST_F(DocumentDataFillMembersTest_1241, LoadFromDataMinimalPdf_1241)
{
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(minimalPdf));
    if (doc) {
        QList<Poppler::EmbeddedFile *> files = doc->embeddedFiles();
        EXPECT_EQ(files.size(), 0);
    }
}

// Test that loading from empty data doesn't crash
TEST_F(DocumentDataFillMembersTest_1241, LoadFromEmptyData_1241)
{
    QByteArray emptyData;
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(emptyData));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test that loading from garbage data doesn't crash
TEST_F(DocumentDataFillMembersTest_1241, LoadFromGarbageData_1241)
{
    QByteArray garbageData("this is not a pdf at all");
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(garbageData));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test that loading from a QIODevice (QBuffer) with minimal PDF works and fillMembers is safe
TEST_F(DocumentDataFillMembersTest_1241, LoadFromQBufferNoEmbeddedFiles_1241)
{
    QByteArray data = minimalPdf;
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::load(&buffer));
    if (doc) {
        EXPECT_EQ(doc->embeddedFiles().size(), 0);
    }
}

// Test that setPaperColor works without affecting fillMembers behavior
TEST_F(DocumentDataFillMembersTest_1241, SetPaperColorDoesNotAffectEmbeddedFiles_1241)
{
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(minimalPdf));
    if (doc) {
        doc->setPaperColor(QColor(255, 255, 255));
        // Embedded files should still be empty after setting paper color
        EXPECT_EQ(doc->embeddedFiles().size(), 0);
    }
}

// Test that calling embeddedFiles multiple times returns consistent results
TEST_F(DocumentDataFillMembersTest_1241, EmbeddedFilesConsistentResults_1241)
{
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(minimalPdf));
    if (doc) {
        QList<Poppler::EmbeddedFile *> files1 = doc->embeddedFiles();
        QList<Poppler::EmbeddedFile *> files2 = doc->embeddedFiles();
        EXPECT_EQ(files1.size(), files2.size());
    }
}

// Test with a truncated PDF header
TEST_F(DocumentDataFillMembersTest_1241, LoadFromTruncatedPdf_1241)
{
    QByteArray truncatedPdf("%PDF-1.4\n");
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::loadFromData(truncatedPdf));
    // Should either be null or handle gracefully
    if (doc) {
        // If it loads, fillMembers should not crash
        EXPECT_GE(doc->embeddedFiles().size(), 0);
    }
}

// Test loading from a non-existent file path
TEST_F(DocumentDataFillMembersTest_1241, LoadFromNonExistentFile_1241)
{
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::load(QString("/nonexistent/path/to/file.pdf")));
    EXPECT_EQ(doc.get(), nullptr);
}

// Test loading from an empty file path
TEST_F(DocumentDataFillMembersTest_1241, LoadFromEmptyFilePath_1241)
{
    std::unique_ptr<Poppler::Document> doc(Poppler::Document::load(QString("")));
    EXPECT_EQ(doc.get(), nullptr);
}

} // namespace
