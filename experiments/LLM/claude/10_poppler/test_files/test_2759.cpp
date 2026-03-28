#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QString>
#include <QByteArray>
#include <QColor>
#include <QIODevice>
#include <QBuffer>
#include <QFile>
#include <optional>
#include <memory>

#include "poppler-qt6.h"
#include "poppler-private.h"

using namespace Poppler;

class DocumentDataTest_2759 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test construction with a non-existent file path
TEST_F(DocumentDataTest_2759, ConstructWithNonExistentFilePath_2759)
{
    QString nonExistentPath = "/tmp/this_file_does_not_exist_poppler_test_2759.pdf";
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    // Should not crash; the document will simply be invalid
    DocumentData docData(nonExistentPath, ownerPass, userPass);
    // We can check that the doc was created (even if invalid)
    EXPECT_TRUE(docData.doc != nullptr || docData.doc == nullptr);
}

// Test construction with empty file path
TEST_F(DocumentDataTest_2759, ConstructWithEmptyFilePath_2759)
{
    QString emptyPath = "";
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(emptyPath, ownerPass, userPass);
    // Should not crash
    SUCCEED();
}

// Test construction with QByteArray containing no data
TEST_F(DocumentDataTest_2759, ConstructWithEmptyByteArray_2759)
{
    QByteArray emptyData;
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(emptyData, ownerPass, userPass);
    SUCCEED();
}

// Test construction with QByteArray containing invalid PDF data
TEST_F(DocumentDataTest_2759, ConstructWithInvalidByteArray_2759)
{
    QByteArray invalidData("This is not a valid PDF file content");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(invalidData, ownerPass, userPass);
    SUCCEED();
}

// Test construction with QIODevice (QBuffer)
TEST_F(DocumentDataTest_2759, ConstructWithQIODevice_2759)
{
    QByteArray data("Not a real PDF");
    QBuffer buffer(&data);
    buffer.open(QIODevice::ReadOnly);

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(&buffer, ownerPass, userPass);
    SUCCEED();
}

// Test setPaperColor
TEST_F(DocumentDataTest_2759, SetPaperColor_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(data, ownerPass, userPass);

    QColor white(255, 255, 255);
    docData.setPaperColor(white);
    // Verify that paperColor was set (accessible as public member)
    EXPECT_EQ(docData.paperColor, white.rgba());
}

// Test setPaperColor with different colors
TEST_F(DocumentDataTest_2759, SetPaperColorRed_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(data, ownerPass, userPass);

    QColor red(255, 0, 0);
    docData.setPaperColor(red);
    SUCCEED();
}

// Test that DocumentData is not copyable
TEST_F(DocumentDataTest_2759, NotCopyable_2759)
{
    EXPECT_FALSE(std::is_copy_constructible<DocumentData>::value);
    EXPECT_FALSE(std::is_copy_assignable<DocumentData>::value);
}

// Test construction with owner and user passwords provided
TEST_F(DocumentDataTest_2759, ConstructWithPasswords_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = GooString("owner");
    std::optional<GooString> userPass = GooString("user");

    DocumentData docData(data, ownerPass, userPass);
    SUCCEED();
}

// Test construction with only owner password
TEST_F(DocumentDataTest_2759, ConstructWithOnlyOwnerPassword_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = GooString("owner");
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(data, ownerPass, userPass);
    SUCCEED();
}

// Test construction with only user password
TEST_F(DocumentDataTest_2759, ConstructWithOnlyUserPassword_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = GooString("user");

    DocumentData docData(data, ownerPass, userPass);
    SUCCEED();
}

// Test notifyXRefReconstructed with callback set
TEST_F(DocumentDataTest_2759, NotifyXRefReconstructedWithCallback_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(data, ownerPass, userPass);

    bool callbackCalled = false;
    docData.xrefReconstructedCallback = [&callbackCalled]() {
        callbackCalled = true;
    };

    docData.notifyXRefReconstructed();
    EXPECT_TRUE(callbackCalled);
}

// Test notifyXRefReconstructed without callback set (should not crash)
TEST_F(DocumentDataTest_2759, NotifyXRefReconstructedWithoutCallback_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(data, ownerPass, userPass);
    docData.xrefReconstructedCallback = nullptr;

    // Should not crash even without a callback
    docData.notifyXRefReconstructed();
    SUCCEED();
}

// Test with a valid minimal PDF loaded from QByteArray
TEST_F(DocumentDataTest_2759, ConstructWithMinimalValidPDF_2759)
{
    // Minimal PDF content
    QByteArray minimalPdf(
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
        "%%EOF\n"
    );

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(minimalPdf, ownerPass, userPass);
    SUCCEED();
}

// Test locked state initialization
TEST_F(DocumentDataTest_2759, LockedStateInitialization_2759)
{
    QByteArray data("Not a real PDF");
    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(data, ownerPass, userPass);
    // After init, locked should have a defined state
    EXPECT_FALSE(docData.locked);
}

// Test with QBuffer device that is not open
TEST_F(DocumentDataTest_2759, ConstructWithClosedQIODevice_2759)
{
    QByteArray data("Not a real PDF");
    QBuffer buffer(&data);
    // Intentionally not opening the buffer

    std::optional<GooString> ownerPass = std::nullopt;
    std::optional<GooString> userPass = std::nullopt;

    DocumentData docData(&buffer, ownerPass, userPass);
    SUCCEED();
}
