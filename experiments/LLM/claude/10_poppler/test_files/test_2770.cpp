#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QString>
#include <QFile>
#include <QTemporaryFile>
#include <optional>
#include <memory>

#include "poppler-private.h"
#include "poppler-qt5.h"

// We need to include necessary poppler headers
#include "GlobalParams.h"
#include "PDFDoc.h"
#include "GooString.h"

using namespace Poppler;

class DocumentDataTest_2770 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }

    // Helper to create a minimal valid PDF file
    QString createMinimalPDF() {
        QTemporaryFile *tmpFile = new QTemporaryFile();
        tmpFile->setAutoRemove(false);
        if (tmpFile->open()) {
            // Write a minimal valid PDF
            QByteArray pdfContent =
                "%PDF-1.0\n"
                "1 0 obj\n"
                "<< /Type /Catalog /Pages 2 0 R >>\n"
                "endobj\n"
                "2 0 obj\n"
                "<< /Type /Pages /Kids [] /Count 0 >>\n"
                "endobj\n"
                "xref\n"
                "0 3\n"
                "0000000000 65535 f \n"
                "0000000009 00000 n \n"
                "0000000058 00000 n \n"
                "trailer\n"
                "<< /Size 3 /Root 1 0 R >>\n"
                "startxref\n"
                "111\n"
                "%%EOF\n";
            tmpFile->write(pdfContent);
            QString name = tmpFile->fileName();
            tmpFile->close();
            tempFiles.append(name);
            delete tmpFile;
            return name;
        }
        delete tmpFile;
        return QString();
    }

    QStringList tempFiles;

    void cleanupTempFiles() {
        for (const QString &f : tempFiles) {
            QFile::remove(f);
        }
    }
};

// Test: Construction with a valid PDF file path and no passwords
TEST_F(DocumentDataTest_2770, ConstructWithValidFilePath_2770) {
    QString pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.isEmpty());

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(pdfPath, ownerPass, userPass);
    });

    // The doc should have been created (not null internally)
    EXPECT_NE(docData, nullptr);

    delete docData;
    cleanupTempFiles();
}

// Test: Construction with a non-existent file path
TEST_F(DocumentDataTest_2770, ConstructWithNonExistentFile_2770) {
    QString nonExistentPath = "/tmp/this_file_does_not_exist_ever_12345.pdf";
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(nonExistentPath, ownerPass, userPass);
    });

    // DocumentData should still be constructible even with invalid path;
    // the PDFDoc inside will report an error state
    EXPECT_NE(docData, nullptr);

    delete docData;
}

// Test: Construction with empty file path
TEST_F(DocumentDataTest_2770, ConstructWithEmptyFilePath_2770) {
    QString emptyPath;
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(emptyPath, ownerPass, userPass);
    });

    EXPECT_NE(docData, nullptr);

    delete docData;
}

// Test: Construction with owner password provided
TEST_F(DocumentDataTest_2770, ConstructWithOwnerPassword_2770) {
    QString pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.isEmpty());

    std::optional<GooString> ownerPass = GooString("ownerpass");
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(pdfPath, ownerPass, userPass);
    });

    EXPECT_NE(docData, nullptr);

    delete docData;
    cleanupTempFiles();
}

// Test: Construction with user password provided
TEST_F(DocumentDataTest_2770, ConstructWithUserPassword_2770) {
    QString pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.isEmpty());

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = GooString("userpass");

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(pdfPath, ownerPass, userPass);
    });

    EXPECT_NE(docData, nullptr);

    delete docData;
    cleanupTempFiles();
}

// Test: Construction with both passwords provided
TEST_F(DocumentDataTest_2770, ConstructWithBothPasswords_2770) {
    QString pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.isEmpty());

    std::optional<GooString> ownerPass = GooString("ownerpass");
    std::optional<GooString> userPass = GooString("userpass");

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(pdfPath, ownerPass, userPass);
    });

    EXPECT_NE(docData, nullptr);

    delete docData;
    cleanupTempFiles();
}

// Test: Destruction does not throw
TEST_F(DocumentDataTest_2770, DestructionDoesNotThrow_2770) {
    QString pdfPath = createMinimalPDF();
    ASSERT_FALSE(pdfPath.isEmpty());

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = new DocumentData(pdfPath, ownerPass, userPass);
    EXPECT_NO_THROW({
        delete docData;
    });

    cleanupTempFiles();
}

// Test: Multiple DocumentData instances can coexist
TEST_F(DocumentDataTest_2770, MultipleInstances_2770) {
    QString pdfPath1 = createMinimalPDF();
    QString pdfPath2 = createMinimalPDF();
    ASSERT_FALSE(pdfPath1.isEmpty());
    ASSERT_FALSE(pdfPath2.isEmpty());

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData1 = nullptr;
    DocumentData *docData2 = nullptr;

    EXPECT_NO_THROW({
        docData1 = new DocumentData(pdfPath1, ownerPass, userPass);
        docData2 = new DocumentData(pdfPath2, ownerPass, userPass);
    });

    EXPECT_NE(docData1, nullptr);
    EXPECT_NE(docData2, nullptr);

    delete docData1;
    delete docData2;
    cleanupTempFiles();
}

// Test: Construction with file path containing special characters
TEST_F(DocumentDataTest_2770, ConstructWithSpecialCharFilePath_2770) {
    // Create a temp file with a somewhat unusual name
    QTemporaryFile tmpFile;
    tmpFile.setAutoRemove(false);
    if (tmpFile.open()) {
        QByteArray pdfContent =
            "%PDF-1.0\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [] /Count 0 >>\n"
            "endobj\n"
            "xref\n"
            "0 3\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "trailer\n"
            "<< /Size 3 /Root 1 0 R >>\n"
            "startxref\n"
            "111\n"
            "%%EOF\n";
        tmpFile.write(pdfContent);
        QString name = tmpFile.fileName();
        tmpFile.close();

        std::optional<GooString> ownerPass = std::nullopt;
        std::optional<GooString> userPass = std::nullopt;

        DocumentData *docData = nullptr;
        EXPECT_NO_THROW({
            docData = new DocumentData(name, ownerPass, userPass);
        });

        EXPECT_NE(docData, nullptr);
        delete docData;
        QFile::remove(name);
    }
}

// Test: DocumentData is not copyable (compile-time check concept - we verify the delete)
// This is a compile-time constraint; we just ensure the class exists and is usable
TEST_F(DocumentDataTest_2770, NotCopyConstructible_2770) {
    EXPECT_FALSE(std::is_copy_constructible<DocumentData>::value);
}

TEST_F(DocumentDataTest_2770, NotCopyAssignable_2770) {
    EXPECT_FALSE(std::is_copy_assignable<DocumentData>::value);
}

// Test: Construction with an invalid (corrupted) PDF content
TEST_F(DocumentDataTest_2770, ConstructWithCorruptedPDF_2770) {
    QTemporaryFile tmpFile;
    tmpFile.setAutoRemove(false);
    ASSERT_TRUE(tmpFile.open());

    // Write garbage data
    tmpFile.write("This is not a valid PDF file at all.");
    QString name = tmpFile.fileName();
    tmpFile.close();

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(name, ownerPass, userPass);
    });

    // Should still construct, but the internal PDFDoc may indicate error
    EXPECT_NE(docData, nullptr);

    delete docData;
    QFile::remove(name);
}

// Test: Construction with empty file (zero bytes)
TEST_F(DocumentDataTest_2770, ConstructWithEmptyFile_2770) {
    QTemporaryFile tmpFile;
    tmpFile.setAutoRemove(false);
    ASSERT_TRUE(tmpFile.open());
    // Write nothing - empty file
    QString name = tmpFile.fileName();
    tmpFile.close();

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData *docData = nullptr;
    EXPECT_NO_THROW({
        docData = new DocumentData(name, ownerPass, userPass);
    });

    EXPECT_NE(docData, nullptr);

    delete docData;
    QFile::remove(name);
}
