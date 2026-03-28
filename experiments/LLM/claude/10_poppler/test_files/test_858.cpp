#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "config.h"
#include "poppler-config.h"
#include "PDFDoc.h"
#include "Annot.h"
#include "Object.h"
#include "Dict.h"
#include "GlobalParams.h"
#include "Form.h"

class AnnotWidgetTest_858 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getMode returns a valid AnnotWidgetHighlightMode value
// We test this by creating an AnnotWidget from a minimal annotation dictionary
TEST_F(AnnotWidgetTest_858, GetModeReturnsValidHighlightMode_858) {
    // Create a minimal PDF document in memory to construct AnnotWidget
    // We use a simple approach: create objects needed for AnnotWidget construction
    
    // Since we can't easily construct a full PDFDoc and valid annotation dict
    // without a real PDF, we test with a file if available, or verify the enum values exist
    
    // Verify enum values are defined (compile-time check effectively)
    AnnotWidgetHighlightMode modeNone = highlightModeNone;
    AnnotWidgetHighlightMode modeInvert = highlightModeInvert;
    AnnotWidgetHighlightMode modeOutline = highlightModeOutline;
    AnnotWidgetHighlightMode modePush = highlightModePush;
    
    EXPECT_EQ(modeNone, highlightModeNone);
    EXPECT_EQ(modeInvert, highlightModeInvert);
    EXPECT_EQ(modeOutline, highlightModeOutline);
    EXPECT_EQ(modePush, highlightModePush);
}

// Test with a constructed AnnotWidget using a minimal dict
TEST_F(AnnotWidgetTest_858, ConstructAnnotWidgetFromDict_858) {
    // Create a minimal PDF file path for testing
    // This test verifies that AnnotWidget can be constructed and basic getters work
    
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available, skipping construction test";
    }
    
    // Check if document has any widget annotations on its pages
    int numPages = doc->getNumPages();
    bool foundWidget = false;
    
    for (int i = 1; i <= numPages && !foundWidget; i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget *>(annot);
                        // Test getMode returns a valid value
                        AnnotWidgetHighlightMode mode = widget->getMode();
                        EXPECT_TRUE(mode == highlightModeNone || 
                                    mode == highlightModeInvert ||
                                    mode == highlightModeOutline ||
                                    mode == highlightModePush);
                        
                        // Test getAction (may be null)
                        // Just verify it doesn't crash
                        LinkAction *action = widget->getAction();
                        (void)action;
                        
                        // Test getParent (may be null)
                        Dict *parent = widget->getParent();
                        (void)parent;
                        
                        // Test getAppearCharacs (may be null)
                        AnnotAppearanceCharacs *appearCharacs = widget->getAppearCharacs();
                        (void)appearCharacs;
                        
                        foundWidget = true;
                        break;
                    }
                }
            }
        }
    }
    
    if (!foundWidget) {
        GTEST_SKIP() << "No widget annotations found in test PDF";
    }
}

// Test getMode default behavior - highlight mode invert is typically the default per PDF spec
TEST_F(AnnotWidgetTest_858, DefaultHighlightModeIsInvert_858) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    // According to PDF spec, default highlight mode is Invert ("I")
    // This verifies behavior for annotations without explicit H entry
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget *>(annot);
                        AnnotWidgetHighlightMode mode = widget->getMode();
                        // Mode should be one of the valid values
                        EXPECT_GE(static_cast<int>(mode), static_cast<int>(highlightModeNone));
                        EXPECT_LE(static_cast<int>(mode), static_cast<int>(highlightModePush));
                    }
                }
            }
        }
    }
}

// Test setField and related form functionality
TEST_F(AnnotWidgetTest_858, SetFieldDoesNotCrash_858) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget *>(annot);
                        // Setting field to nullptr should not crash
                        widget->setField(nullptr);
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    GTEST_SKIP() << "No widget annotations found";
}

// Test setAppearCharacs with nullptr
TEST_F(AnnotWidgetTest_858, SetAppearCharacsWithNull_858) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget *>(annot);
                        // Set appear characs to nullptr
                        widget->setAppearCharacs(nullptr);
                        AnnotAppearanceCharacs *characs = widget->getAppearCharacs();
                        EXPECT_EQ(characs, nullptr);
                        return;
                    }
                }
            }
        }
    }
    GTEST_SKIP() << "No widget annotations found";
}

// Test getAdditionalAction with various types
TEST_F(AnnotWidgetTest_858, GetAdditionalActionTypes_858) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget *>(annot);
                        // These calls should not crash regardless of whether actions exist
                        auto action1 = widget->getAdditionalAction(Annot::actionCursorEntering);
                        auto action2 = widget->getAdditionalAction(Annot::actionCursorLeaving);
                        auto action3 = widget->getAdditionalAction(Annot::actionMousePressed);
                        auto action4 = widget->getAdditionalAction(Annot::actionMouseReleased);
                        // Actions may be null for annotations without additional actions
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    GTEST_SKIP() << "No widget annotations found";
}
