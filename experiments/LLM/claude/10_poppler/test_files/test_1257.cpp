#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "config.h"
#include "PDFDoc.h"
#include "Gfx.h"
#include "GlobalParams.h"
#include "OutputDev.h"
#include "PDFDocFactory.h"
#include "Stream.h"
#include "Dict.h"
#include "XRef.h"
#include "Page.h"
#include "Catalog.h"
#include "GfxState.h"

#include <memory>
#include <cstring>
#include <sstream>

// A minimal OutputDev for testing
class TestOutputDev : public OutputDev
{
public:
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
    void drawChar(GfxState *, double, double, double, double, double, double, CharCode, int, const Unicode *, int) override { }
    bool needNonText() override { return false; }
    void startPage(int pageNum, GfxState *state, XRef *xref) override { }
    void endPage() override { }
};

class GfxTest_1257 : public ::testing::Test
{
protected:
    void SetUp() override
    {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override
    {
    }

    // Helper to create a minimal valid PDF in memory
    std::unique_ptr<PDFDoc> createMinimalPDFDoc()
    {
        // Minimal PDF content
        static const char *pdfContent =
            "%PDF-1.4\n"
            "1 0 obj\n"
            "<< /Type /Catalog /Pages 2 0 R >>\n"
            "endobj\n"
            "2 0 obj\n"
            "<< /Type /Pages /Kids [3 0 R] /Count 1 >>\n"
            "endobj\n"
            "3 0 obj\n"
            "<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] /Contents 4 0 R /Resources << >> >>\n"
            "endobj\n"
            "4 0 obj\n"
            "<< /Length 0 >>\n"
            "stream\n"
            "\n"
            "endstream\n"
            "endobj\n"
            "xref\n"
            "0 5\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "0000000248 00000 n \n"
            "trailer\n"
            "<< /Size 5 /Root 1 0 R >>\n"
            "startxref\n"
            "298\n"
            "%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(pdfContent), 0, strlen(pdfContent), Object(objNull));
        auto doc = std::make_unique<PDFDoc>(stream);
        return doc;
    }
};

TEST_F(GfxTest_1257, ConstructorWithPageNum_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    ASSERT_NE(gfx, nullptr);

    delete resDict;
}

TEST_F(GfxTest_1257, GetXRefReturnsNonNull_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    XRef *xref = gfx->getXRef();
    // When xrefA is nullptr, it should use the doc's XRef
    EXPECT_NE(xref, nullptr);

    delete resDict;
}

TEST_F(GfxTest_1257, GetXRefWithExplicitXRef_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    XRef *docXRef = doc->getXRef();

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, docXRef);

    XRef *xref = gfx->getXRef();
    EXPECT_EQ(xref, docXRef);

    delete resDict;
}

TEST_F(GfxTest_1257, GetStateReturnsNonNull_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    GfxState *state = gfx->getState();
    EXPECT_NE(state, nullptr);

    delete resDict;
}

TEST_F(GfxTest_1257, SaveAndRestoreState_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Save and restore should not crash
    gfx->saveState();
    gfx->restoreState();

    delete resDict;
}

TEST_F(GfxTest_1257, PushPopStateGuard_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Push and pop state guard should not crash
    gfx->pushStateGuard();
    gfx->popStateGuard();

    delete resDict;
}

TEST_F(GfxTest_1257, SaveRestoreMultipleTimes_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Multiple saves followed by multiple restores
    gfx->saveState();
    gfx->saveState();
    gfx->saveState();
    gfx->restoreState();
    gfx->restoreState();
    gfx->restoreState();

    delete resDict;
}

TEST_F(GfxTest_1257, PushPopResources_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    Dict *newResDict = new Dict(doc->getXRef());
    gfx->pushResources(newResDict);
    gfx->popResources();

    delete newResDict;
    delete resDict;
}

TEST_F(GfxTest_1257, CheckTransparencyGroupEmptyDict_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    Dict *emptyDict = new Dict(doc->getXRef());
    bool result = gfx->checkTransparencyGroup(emptyDict);
    // An empty dict should not have transparency group references
    EXPECT_FALSE(result);

    delete emptyDict;
    delete resDict;
}

TEST_F(GfxTest_1257, ConstructorSubPage_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    // Create parent Gfx
    auto parentGfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Create sub-page Gfx using the second constructor
    Dict *subResDict = new Dict(doc->getXRef());
    auto subGfx = std::make_unique<Gfx>(doc.get(), &outDev, subResDict, &box, &cropBox, nullptr, nullptr, parentGfx.get());

    ASSERT_NE(subGfx, nullptr);
    EXPECT_NE(subGfx->getXRef(), nullptr);
    EXPECT_NE(subGfx->getState(), nullptr);

    delete subResDict;
    delete resDict;
}

TEST_F(GfxTest_1257, StateGuardWithSaveRestore_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Push a state guard, save some states, then pop guard (should restore back)
    gfx->pushStateGuard();
    gfx->saveState();
    gfx->saveState();
    gfx->popStateGuard();

    delete resDict;
}

static bool abortCallback(void *data)
{
    bool *flag = static_cast<bool *>(data);
    return *flag;
}

TEST_F(GfxTest_1257, ConstructorWithAbortCallback_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());
    bool abortFlag = false;

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, abortCallback, &abortFlag, nullptr);

    ASSERT_NE(gfx, nullptr);
    EXPECT_NE(gfx->getXRef(), nullptr);

    delete resDict;
}

TEST_F(GfxTest_1257, DifferentRotationValues_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    // Test with different rotation values
    int rotations[] = {0, 90, 180, 270};
    for (int rot : rotations) {
        Dict *resDict = new Dict(doc->getXRef());
        auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, rot, nullptr, nullptr, nullptr);
        ASSERT_NE(gfx, nullptr);
        EXPECT_NE(gfx->getState(), nullptr);
        delete resDict;
    }
}

TEST_F(GfxTest_1257, DifferentDPIValues_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    // Test with various DPI values
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 300.0, 300.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);
    ASSERT_NE(gfx, nullptr);
    EXPECT_NE(gfx->getXRef(), nullptr);

    delete resDict;
}

TEST_F(GfxTest_1257, SmallMediaBox_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 1, 1);
    PDFRectangle cropBox(0, 0, 1, 1);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);
    ASSERT_NE(gfx, nullptr);

    delete resDict;
}

TEST_F(GfxTest_1257, CopyConstructorDeleted_1257)
{
    // Verify copy constructor is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_constructible<Gfx>::value);
}

TEST_F(GfxTest_1257, CopyAssignmentDeleted_1257)
{
    // Verify copy assignment is deleted - this is a compile-time check
    EXPECT_FALSE(std::is_copy_assignable<Gfx>::value);
}

TEST_F(GfxTest_1257, CheckTransparencyGroupNullDict_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // nullptr dict
    bool result = gfx->checkTransparencyGroup(nullptr);
    EXPECT_FALSE(result);

    delete resDict;
}

TEST_F(GfxTest_1257, NestedStateGuards_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Nested state guards
    gfx->pushStateGuard();
    gfx->saveState();
    gfx->pushStateGuard();
    gfx->saveState();
    gfx->popStateGuard();
    gfx->popStateGuard();

    delete resDict;
}

TEST_F(GfxTest_1257, DisplayNullObject_1257)
{
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict *resDict = new Dict(doc->getXRef());

    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, resDict, 72.0, 72.0, &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // Display with a null object should not crash
    Object nullObj(objNull);
    gfx->display(&nullObj, Gfx::DisplayType::display);

    delete resDict;
}
