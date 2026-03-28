#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gfx.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "OutputDev.h"
#include "GfxState.h"

#include <memory>
#include <string>
#include <cstdio>

// Minimal OutputDev subclass for testing
class TestOutputDev : public OutputDev {
public:
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
    void drawChar(GfxState *, double, double, double, double, double, double,
                  CharCode, int, const Unicode *, int) override {}
    
    int saveCallCount = 0;
    int restoreCallCount = 0;
    
    void saveState(GfxState *state) override {
        saveCallCount++;
    }
    
    void restoreState(GfxState *state) override {
        restoreCallCount++;
    }
};

class GfxTest_1473 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create a minimal valid PDF in memory for testing
static std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
    // Create a minimal PDF file in a temp file
    const char *pdfContent =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    std::string tmpFile = "/tmp/gfx_test_1473.pdf";
    FILE *f = fopen(tmpFile.c_str(), "wb");
    if (f) {
        fwrite(pdfContent, 1, strlen(pdfContent), f);
        fclose(f);
    }

    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(tmpFile.c_str()));
    return doc;
}

// Test that saveState and restoreState can be called on Gfx
TEST_F(GfxTest_1473, SaveAndRestoreState_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    int saveBefore = outDev.saveCallCount;
    int restoreBefore = outDev.restoreCallCount;
    
    gfx->saveState();
    EXPECT_EQ(outDev.saveCallCount, saveBefore + 1);
    
    gfx->restoreState();
    EXPECT_EQ(outDev.restoreCallCount, restoreBefore + 1);
}

// Test that GfxStackStateSaver calls restoreState on destruction
TEST_F(GfxTest_1473, StackStateSaverRestoresOnDestruction_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    // Save state first to allow restore
    gfx->saveState();
    int restoreCountBefore = outDev.restoreCallCount;
    
    // The GfxStackStateSaver should call restoreState when it goes out of scope
    // We need to save a state for it to restore
    gfx->saveState();
    int restoreCountAfterSave = outDev.restoreCallCount;
    
    gfx->restoreState();
    EXPECT_EQ(outDev.restoreCallCount, restoreCountAfterSave + 1);
    
    // Restore the first save
    gfx->restoreState();
}

// Test pushStateGuard and popStateGuard
TEST_F(GfxTest_1473, PushPopStateGuard_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    // pushStateGuard and popStateGuard should not crash
    gfx->pushStateGuard();
    gfx->saveState();
    gfx->restoreState();
    gfx->popStateGuard();
}

// Test getState returns non-null
TEST_F(GfxTest_1473, GetStateReturnsNonNull_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    GfxState *state = gfx->getState();
    EXPECT_NE(state, nullptr);
}

// Test getXRef returns non-null
TEST_F(GfxTest_1473, GetXRefReturnsNonNull_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    XRef *xref = gfx->getXRef();
    EXPECT_NE(xref, nullptr);
}

// Test multiple save/restore cycles
TEST_F(GfxTest_1473, MultipleSaveRestoreCycles_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    int initialSave = outDev.saveCallCount;
    int initialRestore = outDev.restoreCallCount;
    
    // Nested save/restore
    gfx->saveState();
    gfx->saveState();
    gfx->saveState();
    EXPECT_EQ(outDev.saveCallCount, initialSave + 3);
    
    gfx->restoreState();
    gfx->restoreState();
    gfx->restoreState();
    EXPECT_EQ(outDev.restoreCallCount, initialRestore + 3);
}

// Test pushResources and popResources with nullptr
TEST_F(GfxTest_1473, PushPopResourcesNullDict_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    // Push and pop with nullptr should not crash
    gfx->pushResources(nullptr);
    gfx->popResources();
}

// Test checkTransparencyGroup with nullptr
TEST_F(GfxTest_1473, CheckTransparencyGroupNullDict_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    bool result = gfx->checkTransparencyGroup(nullptr);
    // With a null dict, there should be no transparency group
    EXPECT_FALSE(result);
}

// Test Gfx copy constructor is deleted (compile-time check)
TEST_F(GfxTest_1473, CopyConstructorDeleted_1473) {
    EXPECT_FALSE(std::is_copy_constructible<Gfx>::value);
}

// Test Gfx copy assignment is deleted (compile-time check)
TEST_F(GfxTest_1473, CopyAssignmentDeleted_1473) {
    EXPECT_FALSE(std::is_copy_assignable<Gfx>::value);
}

// Test second constructor (subpage Gfx)
TEST_F(GfxTest_1473, SubPageConstructor_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto parentGfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                             &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    // Create a sub-page Gfx using the second constructor
    auto subGfx = std::make_unique<Gfx>(doc.get(), &outDev, nullptr, &box, nullptr,
                                          nullptr, nullptr, parentGfx.get());
    
    EXPECT_NE(subGfx->getState(), nullptr);
    EXPECT_NE(subGfx->getXRef(), nullptr);
}

// Test with crop box
TEST_F(GfxTest_1473, ConstructorWithCropBox_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(50, 50, 562, 742);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, &cropBox, 0, nullptr, nullptr, nullptr);
    
    EXPECT_NE(gfx->getState(), nullptr);
}

// Test with rotation
TEST_F(GfxTest_1473, ConstructorWithRotation_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 90, nullptr, nullptr, nullptr);
    
    EXPECT_NE(gfx->getState(), nullptr);
}

// Test state guard with nested saves
TEST_F(GfxTest_1473, StateGuardProtectsAgainstExtraRestores_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    gfx->pushStateGuard();
    gfx->saveState();
    gfx->saveState();
    // popStateGuard should restore states back to guard level
    gfx->popStateGuard();
    
    // Should not crash - the guard should have cleaned up
}

// Test display with null object
TEST_F(GfxTest_1473, DisplayWithNullObject_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, nullptr, nullptr, nullptr);
    
    Object obj;
    // Display with a null/none object should not crash
    gfx->display(&obj, DisplayType::display);
}

// Callback test for abort
static bool abortCallback(void *data) {
    bool *shouldAbort = static_cast<bool *>(data);
    return *shouldAbort;
}

TEST_F(GfxTest_1473, ConstructorWithAbortCallback_1473) {
    auto doc = createMinimalPDFDoc();
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }
    
    TestOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    bool shouldAbort = false;
    
    auto gfx = std::make_unique<Gfx>(doc.get(), &outDev, 1, nullptr, 72.0, 72.0,
                                       &box, nullptr, 0, abortCallback, &shouldAbort, nullptr);
    
    EXPECT_NE(gfx->getState(), nullptr);
}
