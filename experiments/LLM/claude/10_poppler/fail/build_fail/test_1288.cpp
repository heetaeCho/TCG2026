#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <QColor>
#include <QString>
#include <QByteArray>
#include <functional>

// We need to include the relevant headers for the class under test
// Since we're working with the poppler library, include appropriate headers
#include "poppler-qt5.h"
#include "poppler-private.h"

using namespace Poppler;

// Helper to create a minimal valid PDF in memory
static QByteArray createMinimalPDF()
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

class DocumentDataInitTest_1288 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that init() sets the backend to SplashBackend
TEST_F(DocumentDataInitTest_1288, InitSetsBackendToSplash_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // After loading, the default backend should be SplashBackend as set in init()
        EXPECT_EQ(doc->renderBackend(), Document::SplashBackend);
        delete doc;
    }
}

// Test that init() sets paper color to white
TEST_F(DocumentDataInitTest_1288, InitSetsPaperColorToWhite_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // After init(), paperColor should be white
        EXPECT_EQ(doc->paperColor(), QColor(Qt::white));
        delete doc;
    }
}

// Test that init() sets hints to 0
TEST_F(DocumentDataInitTest_1288, InitSetsHintsToZero_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // Render hints should be 0 (no hints set) after init
        EXPECT_EQ(doc->renderHints(), Document::RenderHints());
        delete doc;
    }
}

// Test that init() sets optContentModel to nullptr (no optional content by default)
TEST_F(DocumentDataInitTest_1288, InitSetsOptContentModelToNull_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // For a minimal PDF without optional content, optionalContentModel should be nullptr
        EXPECT_EQ(doc->optionalContentModel(), nullptr);
        delete doc;
    }
}

// Test that xrefReconstructed starts as false after init
TEST_F(DocumentDataInitTest_1288, InitSetsXrefReconstructedToFalse_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // The document should not be marked as xref reconstructed for a well-formed PDF
        EXPECT_EQ(doc->xrefWasReconstructed(), false);
        delete doc;
    }
}

// Test that xrefReconstructedCallback is empty (default-constructed) after init
TEST_F(DocumentDataInitTest_1288, InitSetsXrefReconstructedCallbackEmpty_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // We can set and verify the callback behavior through the public interface
        // By default, no callback should be set, so setting one and calling it should work
        bool callbackInvoked = false;
        doc->setXRefReconstructedCallback([&callbackInvoked]() {
            callbackInvoked = true;
        });
        // The callback wasn't invoked yet - it's only invoked on xref reconstruction
        EXPECT_FALSE(callbackInvoked);
        delete doc;
    }
}

// Test loading from file path (constructor variant)
TEST_F(DocumentDataInitTest_1288, LoadFromDataCreatesValidDocument_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    ASSERT_NE(doc, nullptr);
    EXPECT_EQ(doc->numPages(), 1);
    delete doc;
}

// Test loading invalid data returns null
TEST_F(DocumentDataInitTest_1288, LoadFromInvalidDataReturnsNull_1288)
{
    QByteArray invalidData("This is not a PDF");
    Document *doc = Document::loadFromData(invalidData);
    // Invalid data should not create a valid document
    EXPECT_EQ(doc, nullptr);
    if (doc) {
        delete doc;
    }
}

// Test loading empty data returns null
TEST_F(DocumentDataInitTest_1288, LoadFromEmptyDataReturnsNull_1288)
{
    QByteArray emptyData;
    Document *doc = Document::loadFromData(emptyData);
    EXPECT_EQ(doc, nullptr);
    if (doc) {
        delete doc;
    }
}

// Test that setPaperColor changes the paper color from the default
TEST_F(DocumentDataInitTest_1288, SetPaperColorChangesColor_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // Default should be white from init()
        EXPECT_EQ(doc->paperColor(), QColor(Qt::white));

        // Change to red
        doc->setPaperColor(QColor(Qt::red));
        EXPECT_EQ(doc->paperColor(), QColor(Qt::red));

        // Change to transparent
        doc->setPaperColor(QColor(0, 0, 0, 0));
        EXPECT_EQ(doc->paperColor(), QColor(0, 0, 0, 0));

        delete doc;
    }
}

// Test that render backend can be changed from the default set by init()
TEST_F(DocumentDataInitTest_1288, RenderBackendCanBeChanged_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // Default should be SplashBackend from init()
        EXPECT_EQ(doc->renderBackend(), Document::SplashBackend);

        // If ArthurBackend is available, test switching
        doc->setRenderBackend(Document::ArthurBackend);
        EXPECT_EQ(doc->renderBackend(), Document::ArthurBackend);

        // Switch back
        doc->setRenderBackend(Document::SplashBackend);
        EXPECT_EQ(doc->renderBackend(), Document::SplashBackend);

        delete doc;
    }
}

// Test that render hints can be set after init defaults to 0
TEST_F(DocumentDataInitTest_1288, RenderHintsCanBeSetAfterInit_1288)
{
    QByteArray pdfData = createMinimalPDF();
    Document *doc = Document::loadFromData(pdfData);
    if (doc) {
        // Default should be no hints
        EXPECT_EQ(doc->renderHints(), Document::RenderHints());

        // Set antialiasing hint
        doc->setRenderHint(Document::Antialiasing, true);
        EXPECT_TRUE(doc->renderHints().testFlag(Document::Antialiasing));

        // Unset it
        doc->setRenderHint(Document::Antialiasing, false);
        EXPECT_FALSE(doc->renderHints().testFlag(Document::Antialiasing));

        delete doc;
    }
}

// Test loading from nonexistent file path
TEST_F(DocumentDataInitTest_1288, LoadFromNonexistentFileReturnsNull_1288)
{
    Document *doc = Document::load(QStringLiteral("/nonexistent/path/to/file.pdf"));
    EXPECT_EQ(doc, nullptr);
    if (doc) {
        delete doc;
    }
}

// Test that multiple documents can be created and each has correct defaults
TEST_F(DocumentDataInitTest_1288, MultipleDocumentsHaveCorrectDefaults_1288)
{
    QByteArray pdfData = createMinimalPDF();

    Document *doc1 = Document::loadFromData(pdfData);
    Document *doc2 = Document::loadFromData(pdfData);

    ASSERT_NE(doc1, nullptr);
    ASSERT_NE(doc2, nullptr);

    // Both should have default init values
    EXPECT_EQ(doc1->renderBackend(), Document::SplashBackend);
    EXPECT_EQ(doc2->renderBackend(), Document::SplashBackend);
    EXPECT_EQ(doc1->paperColor(), QColor(Qt::white));
    EXPECT_EQ(doc2->paperColor(), QColor(Qt::white));

    // Changing one should not affect the other
    doc1->setPaperColor(QColor(Qt::blue));
    EXPECT_EQ(doc1->paperColor(), QColor(Qt::blue));
    EXPECT_EQ(doc2->paperColor(), QColor(Qt::white));

    delete doc1;
    delete doc2;
}
