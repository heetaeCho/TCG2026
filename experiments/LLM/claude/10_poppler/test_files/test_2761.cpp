#include <gtest/gtest.h>
#include <QByteArray>
#include <QString>
#include <QColor>
#include <optional>
#include <string>

// Include the header under test
#include "poppler-private.h"

// We need poppler-qt6.h for the Document class if available
// But we'll focus on DocumentData which is in poppler-private.h

using namespace Poppler;

// Helper to create a minimal valid PDF byte array
static QByteArray createMinimalPDF()
{
    // A minimal valid PDF structure
    QByteArray pdf;
    pdf.append("%PDF-1.0\n");
    pdf.append("1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n");
    pdf.append("2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n");
    pdf.append("3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n");
    pdf.append("xref\n0 4\n");
    pdf.append("0000000000 65535 f \n");
    pdf.append("0000000009 00000 n \n");
    pdf.append("0000000058 00000 n \n");
    pdf.append("0000000115 00000 n \n");
    pdf.append("trailer\n<< /Size 4 /Root 1 0 R >>\n");
    pdf.append("startxref\n190\n%%EOF\n");
    return pdf;
}

static QByteArray createInvalidPDF()
{
    return QByteArray("This is not a valid PDF document at all");
}

static QByteArray createEmptyData()
{
    return QByteArray();
}

// Test fixture
class DocumentDataTest_2761 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction from QByteArray with valid minimal PDF, no passwords
TEST_F(DocumentDataTest_2761, ConstructFromByteArrayNoPasswords_2761)
{
    QByteArray pdfData = createMinimalPDF();
    EXPECT_NO_THROW({
        DocumentData docData(pdfData, std::nullopt, std::nullopt);
    });
}

// Test: Construction from QByteArray with empty data
TEST_F(DocumentDataTest_2761, ConstructFromEmptyByteArray_2761)
{
    QByteArray emptyData = createEmptyData();
    // Should not crash; the document may be invalid but construction should handle it
    EXPECT_NO_THROW({
        DocumentData docData(emptyData, std::nullopt, std::nullopt);
    });
}

// Test: Construction from QByteArray with invalid PDF data
TEST_F(DocumentDataTest_2761, ConstructFromInvalidByteArray_2761)
{
    QByteArray invalidData = createInvalidPDF();
    EXPECT_NO_THROW({
        DocumentData docData(invalidData, std::nullopt, std::nullopt);
    });
}

// Test: Construction from QByteArray with owner password
TEST_F(DocumentDataTest_2761, ConstructWithOwnerPassword_2761)
{
    QByteArray pdfData = createMinimalPDF();
    GooString ownerPass("ownerpass");
    EXPECT_NO_THROW({
        DocumentData docData(pdfData, std::optional<GooString>(ownerPass), std::nullopt);
    });
}

// Test: Construction from QByteArray with user password
TEST_F(DocumentDataTest_2761, ConstructWithUserPassword_2761)
{
    QByteArray pdfData = createMinimalPDF();
    GooString userPass("userpass");
    EXPECT_NO_THROW({
        DocumentData docData(pdfData, std::nullopt, std::optional<GooString>(userPass));
    });
}

// Test: Construction from QByteArray with both passwords
TEST_F(DocumentDataTest_2761, ConstructWithBothPasswords_2761)
{
    QByteArray pdfData = createMinimalPDF();
    GooString ownerPass("ownerpass");
    GooString userPass("userpass");
    EXPECT_NO_THROW({
        DocumentData docData(pdfData, std::optional<GooString>(ownerPass), std::optional<GooString>(userPass));
    });
}

// Test: Construction from file path with non-existent file
TEST_F(DocumentDataTest_2761, ConstructFromNonExistentFilePath_2761)
{
    QString nonExistentPath = "/tmp/definitely_nonexistent_file_poppler_test_2761.pdf";
    EXPECT_NO_THROW({
        DocumentData docData(nonExistentPath, std::nullopt, std::nullopt);
    });
}

// Test: Construction from file path with empty string
TEST_F(DocumentDataTest_2761, ConstructFromEmptyFilePath_2761)
{
    QString emptyPath;
    EXPECT_NO_THROW({
        DocumentData docData(emptyPath, std::nullopt, std::nullopt);
    });
}

// Test: DocumentData is not copyable
TEST_F(DocumentDataTest_2761, NotCopyable_2761)
{
    EXPECT_FALSE(std::is_copy_constructible<DocumentData>::value);
    EXPECT_FALSE(std::is_copy_assignable<DocumentData>::value);
}

// Test: setPaperColor can be called
TEST_F(DocumentDataTest_2761, SetPaperColor_2761)
{
    QByteArray pdfData = createMinimalPDF();
    DocumentData docData(pdfData, std::nullopt, std::nullopt);
    EXPECT_NO_THROW({
        docData.setPaperColor(QColor(Qt::white));
    });
}

// Test: setPaperColor with different colors
TEST_F(DocumentDataTest_2761, SetPaperColorVariousColors_2761)
{
    QByteArray pdfData = createMinimalPDF();
    DocumentData docData(pdfData, std::nullopt, std::nullopt);
    
    EXPECT_NO_THROW(docData.setPaperColor(QColor(Qt::red)));
    EXPECT_NO_THROW(docData.setPaperColor(QColor(Qt::black)));
    EXPECT_NO_THROW(docData.setPaperColor(QColor(0, 0, 0, 0))); // transparent
    EXPECT_NO_THROW(docData.setPaperColor(QColor())); // invalid color
}

// Test: xrefReconstructedCallback can be set
TEST_F(DocumentDataTest_2761, XRefReconstructedCallbackCanBeSet_2761)
{
    QByteArray pdfData = createMinimalPDF();
    DocumentData docData(pdfData, std::nullopt, std::nullopt);
    
    bool callbackCalled = false;
    docData.xrefReconstructedCallback = [&callbackCalled]() {
        callbackCalled = true;
    };
    
    // Verify the callback was assigned (we can call notifyXRefReconstructed)
    EXPECT_NO_THROW({
        docData.notifyXRefReconstructed();
    });
    EXPECT_TRUE(callbackCalled);
}

// Test: notifyXRefReconstructed with no callback set
TEST_F(DocumentDataTest_2761, NotifyXRefReconstructedNoCallback_2761)
{
    QByteArray pdfData = createMinimalPDF();
    DocumentData docData(pdfData, std::nullopt, std::nullopt);
    
    // With no callback set, this should not crash
    EXPECT_NO_THROW({
        docData.notifyXRefReconstructed();
    });
}

// Test: Multiple DocumentData instances can coexist
TEST_F(DocumentDataTest_2761, MultipleInstances_2761)
{
    QByteArray pdfData = createMinimalPDF();
    EXPECT_NO_THROW({
        DocumentData docData1(pdfData, std::nullopt, std::nullopt);
        DocumentData docData2(pdfData, std::nullopt, std::nullopt);
    });
}

// Test: Construction with empty passwords (empty GooString, not nullopt)
TEST_F(DocumentDataTest_2761, ConstructWithEmptyPasswords_2761)
{
    QByteArray pdfData = createMinimalPDF();
    GooString emptyOwner("");
    GooString emptyUser("");
    EXPECT_NO_THROW({
        DocumentData docData(pdfData, std::optional<GooString>(emptyOwner), std::optional<GooString>(emptyUser));
    });
}

// Test: Large PDF data
TEST_F(DocumentDataTest_2761, ConstructFromLargeByteArray_2761)
{
    // Create a large but still invalid PDF to test memory handling
    QByteArray largeData(1024 * 1024, 'A'); // 1MB of 'A's
    EXPECT_NO_THROW({
        DocumentData docData(largeData, std::nullopt, std::nullopt);
    });
}

// Test: Destruction cleans up properly (no crash on destruction)
TEST_F(DocumentDataTest_2761, DestructionIsClean_2761)
{
    QByteArray pdfData = createMinimalPDF();
    auto docData = new DocumentData(pdfData, std::nullopt, std::nullopt);
    EXPECT_NO_THROW({
        delete docData;
    });
}
