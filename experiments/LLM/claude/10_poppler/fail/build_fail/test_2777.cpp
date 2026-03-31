#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Gfx.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "OutputDev.h"
#include "GfxState.h"

#include <memory>
#include <sstream>

// Minimal OutputDev for testing
class TestOutputDev : public OutputDev {
public:
    bool upsideDown() override { return false; }
    bool useDrawChar() override { return false; }
    bool interpretType3Chars() override { return false; }
    void drawChar(GfxState *, double, double, double, double, double, double,
                  CharCode, int, const Unicode *, int) override {}

    int saveCount = 0;
    int restoreCount = 0;

    void saveState(GfxState *state) override {
        saveCount++;
    }

    void restoreState(GfxState *state) override {
        restoreCount++;
    }
};

class GfxStackStateSaverTest_2777 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Helper to create a minimal PDF in memory for testing
static std::unique_ptr<PDFDoc> createMinimalPDFDoc() {
    // Minimal valid PDF
    static const char *pdfData =
        "%PDF-1.0\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Resources<<>>>>endobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer<</Size 4/Root 1 0 R>>\nstartxref\n210\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(pdfData), 0, strlen(pdfData), Object(objNull));
    return std::make_unique<PDFDoc>(stream);
}

// Test that constructing GfxStackStateSaver calls saveState
TEST_F(GfxStackStateSaverTest_2777, ConstructorCallsSaveState_2777) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto outDev = std::make_unique<TestOutputDev>();
    PDFRectangle box(0, 0, 612, 792);

    Gfx gfx(doc.get(), outDev.get(), 1, nullptr, 72.0, 72.0, &box, nullptr, 0, nullptr, nullptr, nullptr);

    int saveBefore = outDev->saveCount;
    {
        GfxStackStateSaver saver(&gfx);
        // After construction, saveState should have been called
        EXPECT_EQ(outDev->saveCount, saveBefore + 1);
    }
}

// Test that destroying GfxStackStateSaver calls restoreState
TEST_F(GfxStackStateSaverTest_2777, DestructorCallsRestoreState_2777) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto outDev = std::make_unique<TestOutputDev>();
    PDFRectangle box(0, 0, 612, 792);

    Gfx gfx(doc.get(), outDev.get(), 1, nullptr, 72.0, 72.0, &box, nullptr, 0, nullptr, nullptr, nullptr);

    int restoreBefore = outDev->restoreCount;
    {
        GfxStackStateSaver saver(&gfx);
    }
    // After destruction, restoreState should have been called
    EXPECT_EQ(outDev->restoreCount, restoreBefore + 1);
}

// Test that save and restore are balanced with RAII
TEST_F(GfxStackStateSaverTest_2777, SaveRestoreAreBalanced_2777) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto outDev = std::make_unique<TestOutputDev>();
    PDFRectangle box(0, 0, 612, 792);

    Gfx gfx(doc.get(), outDev.get(), 1, nullptr, 72.0, 72.0, &box, nullptr, 0, nullptr, nullptr, nullptr);

    int saveBefore = outDev->saveCount;
    int restoreBefore = outDev->restoreCount;
    {
        GfxStackStateSaver saver(&gfx);
    }
    EXPECT_EQ(outDev->saveCount - saveBefore, outDev->restoreCount - restoreBefore);
}

// Test multiple nested GfxStackStateSavers
TEST_F(GfxStackStateSaverTest_2777, NestedSavers_2777) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto outDev = std::make_unique<TestOutputDev>();
    PDFRectangle box(0, 0, 612, 792);

    Gfx gfx(doc.get(), outDev.get(), 1, nullptr, 72.0, 72.0, &box, nullptr, 0, nullptr, nullptr, nullptr);

    int saveBefore = outDev->saveCount;
    int restoreBefore = outDev->restoreCount;
    {
        GfxStackStateSaver saver1(&gfx);
        EXPECT_EQ(outDev->saveCount, saveBefore + 1);
        {
            GfxStackStateSaver saver2(&gfx);
            EXPECT_EQ(outDev->saveCount, saveBefore + 2);
        }
        EXPECT_EQ(outDev->restoreCount, restoreBefore + 1);
    }
    EXPECT_EQ(outDev->saveCount, saveBefore + 2);
    EXPECT_EQ(outDev->restoreCount, restoreBefore + 2);
}

// Test that GfxStackStateSaver is not copyable (compile-time check, verifying delete)
TEST_F(GfxStackStateSaverTest_2777, NotCopyable_2777) {
    EXPECT_FALSE(std::is_copy_constructible<GfxStackStateSaver>::value);
    EXPECT_FALSE(std::is_copy_assignable<GfxStackStateSaver>::value);
}

// Test sequential (non-nested) savers
TEST_F(GfxStackStateSaverTest_2777, SequentialSavers_2777) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto outDev = std::make_unique<TestOutputDev>();
    PDFRectangle box(0, 0, 612, 792);

    Gfx gfx(doc.get(), outDev.get(), 1, nullptr, 72.0, 72.0, &box, nullptr, 0, nullptr, nullptr, nullptr);

    int saveBefore = outDev->saveCount;
    int restoreBefore = outDev->restoreCount;

    {
        GfxStackStateSaver saver1(&gfx);
    }
    EXPECT_EQ(outDev->saveCount, saveBefore + 1);
    EXPECT_EQ(outDev->restoreCount, restoreBefore + 1);

    {
        GfxStackStateSaver saver2(&gfx);
    }
    EXPECT_EQ(outDev->saveCount, saveBefore + 2);
    EXPECT_EQ(outDev->restoreCount, restoreBefore + 2);
}

// Test GfxState is preserved after RAII scope
TEST_F(GfxStackStateSaverTest_2777, StatePreservedAfterScope_2777) {
    auto doc = createMinimalPDFDoc();
    ASSERT_TRUE(doc->isOk());

    auto outDev = std::make_unique<TestOutputDev>();
    PDFRectangle box(0, 0, 612, 792);

    Gfx gfx(doc.get(), outDev.get(), 1, nullptr, 72.0, 72.0, &box, nullptr, 0, nullptr, nullptr, nullptr);

    GfxState *stateBefore = gfx.getState();
    {
        GfxStackStateSaver saver(&gfx);
        // Inside scope, state may differ (new state pushed)
    }
    GfxState *stateAfter = gfx.getState();
    // After restore, we should be back to the original state
    EXPECT_EQ(stateBefore, stateAfter);
}
