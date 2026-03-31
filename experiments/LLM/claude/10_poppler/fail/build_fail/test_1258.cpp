#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gfx.h"
#include "GfxState.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "OutputDev.h"
#include "Dict.h"
#include "PDFRectangle.h"
#include "XRef.h"
#include "Catalog.h"

#include <memory>
#include <type_traits>
#include <cstring>
#include <sstream>

// A minimal OutputDev that does nothing - used for testing
class NullOutputDev : public OutputDev {
public:
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
    void drawChar(GfxState *, double, double, double, double, double, double,
                  CharCode, int, const Unicode *, int) override {}
    bool needNonText() override { return false; }
};

class GfxTest_1258 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that Gfx is not copy constructible (deleted copy constructor)
TEST_F(GfxTest_1258, CopyConstructorIsDeleted_1258) {
    EXPECT_FALSE(std::is_copy_constructible<Gfx>::value);
}

// Test that Gfx is not copy assignable (deleted assignment operator)
TEST_F(GfxTest_1258, CopyAssignmentIsDeleted_1258) {
    EXPECT_FALSE(std::is_copy_assignable<Gfx>::value);
}

// Helper to create a minimal in-memory PDF for testing
static std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
    // Minimal valid PDF
    static const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n"
        "0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\n"
        "startxref\n"
        "210\n"
        "%%EOF\n";

    // Write to temp file
    FILE *f = tmpfile();
    if (!f) return nullptr;
    fwrite(pdfData, 1, strlen(pdfData), f);
    fseek(f, 0, SEEK_SET);

    auto doc = std::make_unique<PDFDoc>(f);
    if (!doc->isOk()) {
        return nullptr;
    }
    return doc;
}

// Test construction with first constructor and getState returns non-null
TEST_F(GfxTest_1258, ConstructorPageNumGetStateNotNull_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    GfxState *state = gfx.getState();
    EXPECT_NE(state, nullptr);
}

// Test getXRef returns a value (may be null if no xref passed)
TEST_F(GfxTest_1258, GetXRefReturnsValue_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, doc->getXRef());

    XRef *xref = gfx.getXRef();
    // When we pass a valid xref, it should be returned
    EXPECT_EQ(xref, doc->getXRef());
}

// Test saveState and restoreState don't crash
TEST_F(GfxTest_1258, SaveAndRestoreState_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    GfxState *stateBefore = gfx.getState();
    EXPECT_NE(stateBefore, nullptr);

    gfx.saveState();
    GfxState *stateAfterSave = gfx.getState();
    EXPECT_NE(stateAfterSave, nullptr);

    gfx.restoreState();
    GfxState *stateAfterRestore = gfx.getState();
    EXPECT_NE(stateAfterRestore, nullptr);
}

// Test pushStateGuard and popStateGuard don't crash
TEST_F(GfxTest_1258, PushAndPopStateGuard_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    gfx.pushStateGuard();
    // State should still be valid
    EXPECT_NE(gfx.getState(), nullptr);

    gfx.popStateGuard();
    EXPECT_NE(gfx.getState(), nullptr);
}

// Test multiple saveState / restoreState calls
TEST_F(GfxTest_1258, MultipleSaveRestoreState_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    gfx.saveState();
    gfx.saveState();
    gfx.saveState();

    EXPECT_NE(gfx.getState(), nullptr);

    gfx.restoreState();
    gfx.restoreState();
    gfx.restoreState();

    EXPECT_NE(gfx.getState(), nullptr);
}

// Test pushResources and popResources
TEST_F(GfxTest_1258, PushAndPopResources_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    Dict newResDict(doc->getXRef());
    gfx.pushResources(&newResDict);
    // Should not crash, state should still be valid
    EXPECT_NE(gfx.getState(), nullptr);

    gfx.popResources();
    EXPECT_NE(gfx.getState(), nullptr);
}

// Test checkTransparencyGroup with empty dict
TEST_F(GfxTest_1258, CheckTransparencyGroupEmptyDict_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    Dict emptyDict(doc->getXRef());
    bool result = gfx.checkTransparencyGroup(&emptyDict);
    // With an empty resource dict, there should be no transparency group
    EXPECT_FALSE(result);
}

// Test second constructor (sub-page Gfx)
TEST_F(GfxTest_1258, SecondConstructorSubPage_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx parentGfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
                   &box, &cropBox, 0, nullptr, nullptr, nullptr);

    Dict subResDict(doc->getXRef());
    Gfx subGfx(doc.get(), &outDev, &subResDict, &box, &cropBox,
                nullptr, nullptr, &parentGfx);

    EXPECT_NE(subGfx.getState(), nullptr);
}

// Test abort callback functionality
static bool abortCallback(void *data) {
    bool *flag = static_cast<bool *>(data);
    return *flag;
}

TEST_F(GfxTest_1258, ConstructWithAbortCallback_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());
    bool abortFlag = false;

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, abortCallback, &abortFlag, nullptr);

    // The object should be constructible with a callback
    EXPECT_NE(gfx.getState(), nullptr);
}

// Test with different rotation values
TEST_F(GfxTest_1258, ConstructWithRotation90_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 90, nullptr, nullptr, nullptr);

    EXPECT_NE(gfx.getState(), nullptr);
}

TEST_F(GfxTest_1258, ConstructWithRotation180_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 180, nullptr, nullptr, nullptr);

    EXPECT_NE(gfx.getState(), nullptr);
}

TEST_F(GfxTest_1258, ConstructWithRotation270_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 270, nullptr, nullptr, nullptr);

    EXPECT_NE(gfx.getState(), nullptr);
}

// Test with different DPI values
TEST_F(GfxTest_1258, ConstructWithHighDPI_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 300.0, 300.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    EXPECT_NE(gfx.getState(), nullptr);
}

// Test saveState followed by pushStateGuard and popStateGuard
TEST_F(GfxTest_1258, SaveStateThenGuardOperations_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    gfx.pushStateGuard();
    gfx.saveState();
    gfx.saveState();

    EXPECT_NE(gfx.getState(), nullptr);

    gfx.popStateGuard();
    EXPECT_NE(gfx.getState(), nullptr);
}

// Test with zero-sized box (boundary condition)
TEST_F(GfxTest_1258, ConstructWithZeroSizedBox_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 0, 0);
    PDFRectangle cropBox(0, 0, 0, 0);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    EXPECT_NE(gfx.getState(), nullptr);
}

// Test checkTransparencyGroup with nullptr
TEST_F(GfxTest_1258, CheckTransparencyGroupNullDict_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    bool result = gfx.checkTransparencyGroup(nullptr);
    EXPECT_FALSE(result);
}

// Test getXRef when nullptr is passed as xref
TEST_F(GfxTest_1258, GetXRefWhenNullPassed_1258) {
    auto doc = createMinimalPDFDoc();
    if (!doc) {
        GTEST_SKIP() << "Could not create minimal PDF document";
    }

    NullOutputDev outDev;
    PDFRectangle box(0, 0, 612, 792);
    PDFRectangle cropBox(0, 0, 612, 792);

    Dict resDict(doc->getXRef());

    Gfx gfx(doc.get(), &outDev, 1, &resDict, 72.0, 72.0,
             &box, &cropBox, 0, nullptr, nullptr, nullptr);

    // When nullptr is passed as xref, getXRef might return the doc's xref or null
    XRef *xref = gfx.getXRef();
    // Just verify we can call it without crashing
    (void)xref;
}
