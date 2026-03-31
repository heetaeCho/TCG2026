#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <QBuffer>
#include <QByteArray>
#include <QColor>
#include <QFile>
#include <QIODevice>
#include <QString>
#include <QTemporaryFile>

#include "poppler-private.h"
#include "poppler-qt6.h"

#include <optional>
#include <functional>

// Helper to get a minimal valid PDF as QByteArray
static QByteArray getMinimalPDF()
{
    // A minimal valid PDF document
    QByteArray pdf;
    pdf.append("%PDF-1.0\n");
    pdf.append("1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n");
    pdf.append("2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n");
    pdf.append("3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R>>endobj\n");
    pdf.append("xref\n");
    pdf.append("0 4\n");
    pdf.append("0000000000 65535 f \n");
    pdf.append("0000000009 00000 n \n");
    pdf.append("0000000058 00000 n \n");
    pdf.append("0000000115 00000 n \n");
    pdf.append("trailer<</Size 4/Root 1 0 R>>\n");
    pdf.append("startxref\n");
    pdf.append("190\n");
    pdf.append("%%EOF\n");
    return pdf;
}

static QByteArray getInvalidPDF()
{
    return QByteArray("This is not a valid PDF file at all.");
}

class DocumentDataTest_2760 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction from QByteArray with valid minimal PDF
TEST_F(DocumentDataTest_2760, ConstructFromByteArray_ValidPDF_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(pdfData, ownerPass, userPass);
    });
}

// Test construction from QByteArray with invalid data
TEST_F(DocumentDataTest_2760, ConstructFromByteArray_InvalidPDF_2760)
{
    QByteArray invalidData = getInvalidPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    // Should not crash; the doc may be invalid but construction should complete
    EXPECT_NO_THROW({
        Poppler::DocumentData docData(invalidData, ownerPass, userPass);
    });
}

// Test construction from QIODevice with valid PDF
TEST_F(DocumentDataTest_2760, ConstructFromQIODevice_ValidPDF_2760)
{
    QByteArray pdfData = getMinimalPDF();
    QBuffer buffer(&pdfData);
    buffer.open(QIODevice::ReadOnly);

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(&buffer, ownerPass, userPass);
    });
}

// Test construction from QIODevice with invalid data
TEST_F(DocumentDataTest_2760, ConstructFromQIODevice_InvalidPDF_2760)
{
    QByteArray invalidData = getInvalidPDF();
    QBuffer buffer(&invalidData);
    buffer.open(QIODevice::ReadOnly);

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(&buffer, ownerPass, userPass);
    });
}

// Test construction from file path with valid PDF
TEST_F(DocumentDataTest_2760, ConstructFromFilePath_ValidPDF_2760)
{
    QByteArray pdfData = getMinimalPDF();
    QTemporaryFile tempFile;
    ASSERT_TRUE(tempFile.open());
    tempFile.write(pdfData);
    tempFile.flush();
    tempFile.close();

    QString filePath = tempFile.fileName();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(filePath, ownerPass, userPass);
    });
}

// Test construction from non-existent file path
TEST_F(DocumentDataTest_2760, ConstructFromFilePath_NonExistentFile_2760)
{
    QString filePath = "/nonexistent/path/to/file.pdf";
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    // Should not crash; doc will be in an error state
    EXPECT_NO_THROW({
        Poppler::DocumentData docData(filePath, ownerPass, userPass);
    });
}

// Test construction from empty QByteArray
TEST_F(DocumentDataTest_2760, ConstructFromByteArray_EmptyData_2760)
{
    QByteArray emptyData;
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(emptyData, ownerPass, userPass);
    });
}

// Test setPaperColor
TEST_F(DocumentDataTest_2760, SetPaperColor_White_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);

    QColor white(255, 255, 255);
    EXPECT_NO_THROW({
        docData.setPaperColor(white);
    });
    EXPECT_EQ(docData.paperColor, white.rgba());
}

// Test setPaperColor with different color
TEST_F(DocumentDataTest_2760, SetPaperColor_Red_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);

    QColor red(255, 0, 0);
    EXPECT_NO_THROW({
        docData.setPaperColor(red);
    });
}

// Test construction with owner password
TEST_F(DocumentDataTest_2760, ConstructFromByteArray_WithOwnerPassword_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = GooString("owner123");
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(pdfData, ownerPass, userPass);
    });
}

// Test construction with user password
TEST_F(DocumentDataTest_2760, ConstructFromByteArray_WithUserPassword_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = GooString("user123");

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(pdfData, ownerPass, userPass);
    });
}

// Test construction with both passwords
TEST_F(DocumentDataTest_2760, ConstructFromByteArray_WithBothPasswords_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = GooString("owner123");
    std::optional<GooString> userPass = GooString("user123");

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(pdfData, ownerPass, userPass);
    });
}

// Test that xrefReconstructedCallback is callable
TEST_F(DocumentDataTest_2760, XRefReconstructedCallback_IsSettable_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);

    bool callbackCalled = false;
    docData.xrefReconstructedCallback = [&callbackCalled]() {
        callbackCalled = true;
    };

    // Manually invoke to verify it's settable and callable
    if (docData.xrefReconstructedCallback) {
        docData.xrefReconstructedCallback();
    }
    EXPECT_TRUE(callbackCalled);
}

// Test notifyXRefReconstructed invokes the callback
TEST_F(DocumentDataTest_2760, NotifyXRefReconstructed_InvokesCallback_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);

    bool callbackCalled = false;
    docData.xrefReconstructedCallback = [&callbackCalled]() {
        callbackCalled = true;
    };

    docData.notifyXRefReconstructed();
    EXPECT_TRUE(callbackCalled);
}

// Test notifyXRefReconstructed with no callback set doesn't crash
TEST_F(DocumentDataTest_2760, NotifyXRefReconstructed_NoCallback_NoCrash_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);
    docData.xrefReconstructedCallback = nullptr;

    EXPECT_NO_THROW({
        docData.notifyXRefReconstructed();
    });
}

// Test checkDocument with valid document
TEST_F(DocumentDataTest_2760, CheckDocument_ValidPDF_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    auto *docData = new Poppler::DocumentData(pdfData, ownerPass, userPass);

    // checkDocument takes ownership or returns a Document*
    auto *result = Poppler::DocumentData::checkDocument(docData);
    // If result is non-null, valid document was created
    // If result is null, docData was deleted
    if (result) {
        delete result;
    }
}

// Test checkDocument with invalid document
TEST_F(DocumentDataTest_2760, CheckDocument_InvalidPDF_2760)
{
    QByteArray invalidData = getInvalidPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    auto *docData = new Poppler::DocumentData(invalidData, ownerPass, userPass);

    auto *result = Poppler::DocumentData::checkDocument(docData);
    // For invalid PDF, checkDocument should return nullptr
    if (result) {
        delete result;
    } else {
        // docData should have been cleaned up by checkDocument
        // No manual delete needed
    }
}

// Test locked member initialization
TEST_F(DocumentDataTest_2760, LockedMember_InitialValue_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);
    EXPECT_FALSE(docData.locked);
}

// Test construction from QIODevice with zero-size device
TEST_F(DocumentDataTest_2760, ConstructFromQIODevice_ZeroSize_2760)
{
    QByteArray emptyData;
    QBuffer buffer(&emptyData);
    buffer.open(QIODevice::ReadOnly);

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData(&buffer, ownerPass, userPass);
    });
}

// Test fillMembers does not crash on valid document
TEST_F(DocumentDataTest_2760, FillMembers_ValidPDF_NoCrash_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    Poppler::DocumentData docData(pdfData, ownerPass, userPass);

    EXPECT_NO_THROW({
        docData.fillMembers();
    });
}

// Test destruction does not crash
TEST_F(DocumentDataTest_2760, Destruction_NoCrash_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        auto *docData = new Poppler::DocumentData(pdfData, ownerPass, userPass);
        delete docData;
    });
}

// Test copy constructor is deleted (compile-time check implied, but we verify move isn't available either)
// This is a compile-time constraint; we just document it exists.

// Test multiple DocumentData instances can coexist
TEST_F(DocumentDataTest_2760, MultipleInstances_Coexist_2760)
{
    QByteArray pdfData = getMinimalPDF();
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    EXPECT_NO_THROW({
        Poppler::DocumentData docData1(pdfData, ownerPass, userPass);
        Poppler::DocumentData docData2(pdfData, ownerPass, userPass);
    });
}
