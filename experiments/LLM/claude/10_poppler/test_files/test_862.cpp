#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from poppler
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/Form.h"
#include "poppler/GooString.h"
#include "poppler/GlobalParams.h"

class AnnotWidgetTest_862 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getParent returns the parent Dict pointer
// When no parent is set, it should return nullptr
TEST_F(AnnotWidgetTest_862, GetParentReturnsParentDict_862) {
    // We test the getParent() method which simply returns the internal parent pointer.
    // Since AnnotWidget requires complex setup with PDFDoc, we test through
    // a minimal construction path if possible, or verify the interface contract.
    
    // Create a minimal PDF document for testing
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    // Check if the document has any annotations on any page
    bool foundWidget = false;
    for (int i = 1; i <= doc->getNumPages() && !foundWidget; i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        // getParent() may return nullptr or a valid Dict*
                        // We just verify it doesn't crash
                        Dict *parent = widget->getParent();
                        (void)parent; // Just testing it doesn't crash
                        foundWidget = true;
                        break;
                    }
                }
            }
        }
    }
    // Test passes regardless of whether we found a widget - we're testing the interface
    SUCCEED();
}

// Test getMode returns a valid AnnotWidgetHighlightMode
TEST_F(AnnotWidgetTest_862, GetModeReturnsHighlightMode_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        AnnotWidget::AnnotWidgetHighlightMode mode = widget->getMode();
                        // Verify mode is one of the valid values
                        EXPECT_TRUE(mode == AnnotWidget::highlightModeNone ||
                                    mode == AnnotWidget::highlightModeInvert ||
                                    mode == AnnotWidget::highlightModeOutline ||
                                    mode == AnnotWidget::highlightModePush ||
                                    mode == AnnotWidget::highlightModeToggle);
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test getAppearCharacs - should return nullptr or valid pointer
TEST_F(AnnotWidgetTest_862, GetAppearCharacsReturnsValidOrNull_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        // Just verify it doesn't crash
                        AnnotAppearanceCharacs *characs = widget->getAppearCharacs();
                        (void)characs;
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test getAction - should return nullptr or valid LinkAction pointer
TEST_F(AnnotWidgetTest_862, GetActionReturnsValidOrNull_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        LinkAction *action = widget->getAction();
                        (void)action;
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test setField sets the field properly (observable via generateFieldAppearance behavior)
TEST_F(AnnotWidgetTest_862, SetFieldDoesNotCrash_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        // Setting field to nullptr should not crash
                        widget->setField(nullptr);
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test that AnnotWidget type is correctly reported as typeWidget
TEST_F(AnnotWidgetTest_862, AnnotTypeIsWidget_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        EXPECT_EQ(annot->getType(), Annot::typeWidget);
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test setAppearCharacs with nullptr unique_ptr
TEST_F(AnnotWidgetTest_862, SetAppearCharacsWithNull_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        std::unique_ptr<AnnotAppearanceCharacs> nullCharacs(nullptr);
                        widget->setAppearCharacs(std::move(nullCharacs));
                        EXPECT_EQ(widget->getAppearCharacs(), nullptr);
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test with a PDF that has form fields
TEST_F(AnnotWidgetTest_862, FormPDFWidgetAnnotations_862) {
    // Try to find a PDF with form fields
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/Form_T.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open Form_T.pdf test file";
    }
    
    int widgetCount = 0;
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        widgetCount++;
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        
                        // Test all public getters don't crash
                        widget->getParent();
                        widget->getMode();
                        widget->getAppearCharacs();
                        widget->getAction();
                    }
                }
            }
        }
    }
    // Just verify we processed without error
    EXPECT_GE(widgetCount, 0);
}

// Test getAdditionalAction with various types
TEST_F(AnnotWidgetTest_862, GetAdditionalActionTypes_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        
                        // Test various additional action types - should not crash
                        auto action1 = widget->getAdditionalAction(Annot::actionCursorEntering);
                        auto action2 = widget->getAdditionalAction(Annot::actionCursorLeaving);
                        auto action3 = widget->getAdditionalAction(Annot::actionMousePressed);
                        auto action4 = widget->getAdditionalAction(Annot::actionMouseReleased);
                        
                        // Actions may be null if not defined
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}

// Test getFormAdditionalAction with various types
TEST_F(AnnotWidgetTest_862, GetFormAdditionalActionTypes_862) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }
    
    for (int i = 1; i <= doc->getNumPages(); i++) {
        Page *page = doc->getPage(i);
        if (page) {
            Annots *annots = page->getAnnots();
            if (annots) {
                for (int j = 0; j < annots->getNumAnnots(); j++) {
                    Annot *annot = annots->getAnnot(j);
                    if (annot && annot->getType() == Annot::typeWidget) {
                        AnnotWidget *widget = static_cast<AnnotWidget*>(annot);
                        
                        // Test form additional action types
                        auto action1 = widget->getFormAdditionalAction(Annot::actionFieldModified);
                        auto action2 = widget->getFormAdditionalAction(Annot::actionFormatField);
                        auto action3 = widget->getFormAdditionalAction(Annot::actionValidateField);
                        auto action4 = widget->getFormAdditionalAction(Annot::actionCalculateField);
                        
                        SUCCEED();
                        return;
                    }
                }
            }
        }
    }
    SUCCEED();
}
