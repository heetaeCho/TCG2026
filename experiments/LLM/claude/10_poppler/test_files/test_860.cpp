#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "Object.h"
#include "GlobalParams.h"

class AnnotWidgetTest_860 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that setAppearCharacs with a valid unique_ptr stores it and getAppearCharacs returns it
TEST_F(AnnotWidgetTest_860, SetAppearCharacsStoresValue_860) {
    // We need a minimal PDFDoc to construct AnnotWidget
    // Create a minimal PDF in memory for testing
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    // Get a page's annotations to find an AnnotWidget, or create one
    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
    }

    // Create an Object for annotation dict
    Object annotObj = Object(new Dict(doc->getXRef()));
    Dict *annotDict = annotObj.getDict();
    annotDict->add("Type", Object(objName, "Annot"));
    annotDict->add("Subtype", Object(objName, "Widget"));
    
    // Create Rect array
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotDict->add("Rect", std::move(rectArray));

    Object refObj = Object(objNull);
    
    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);
    ASSERT_NE(widget, nullptr);

    // Initially, appearCharacs might be null if not set in dict
    // Now set a new AnnotAppearanceCharacs
    auto appearCharacs = std::make_unique<AnnotAppearanceCharacs>(new Dict(doc->getXRef()));
    AnnotAppearanceCharacs *rawPtr = appearCharacs.get();
    
    widget->setAppearCharacs(std::move(appearCharacs));
    
    // Verify that getAppearCharacs returns the same pointer
    EXPECT_EQ(widget->getAppearCharacs(), rawPtr);
}

// Test that setAppearCharacs with nullptr clears the appearance characteristics
TEST_F(AnnotWidgetTest_860, SetAppearCharacsWithNullptr_860) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    Dict *annotDict = annotObj.getDict();
    annotDict->add("Type", Object(objName, "Annot"));
    annotDict->add("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotDict->add("Rect", std::move(rectArray));

    Object refObj = Object(objNull);
    
    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);
    
    // First set a valid one
    auto appearCharacs = std::make_unique<AnnotAppearanceCharacs>(new Dict(doc->getXRef()));
    widget->setAppearCharacs(std::move(appearCharacs));
    EXPECT_NE(widget->getAppearCharacs(), nullptr);
    
    // Now set nullptr
    widget->setAppearCharacs(nullptr);
    EXPECT_EQ(widget->getAppearCharacs(), nullptr);
}

// Test that setAppearCharacs replaces a previously set value
TEST_F(AnnotWidgetTest_860, SetAppearCharacsReplacesPrevious_860) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    Dict *annotDict = annotObj.getDict();
    annotDict->add("Type", Object(objName, "Annot"));
    annotDict->add("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotDict->add("Rect", std::move(rectArray));

    Object refObj = Object(objNull);
    
    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);
    
    // Set first appearance characteristics
    auto appearCharacs1 = std::make_unique<AnnotAppearanceCharacs>(new Dict(doc->getXRef()));
    AnnotAppearanceCharacs *rawPtr1 = appearCharacs1.get();
    widget->setAppearCharacs(std::move(appearCharacs1));
    EXPECT_EQ(widget->getAppearCharacs(), rawPtr1);
    
    // Set second appearance characteristics (should replace first)
    auto appearCharacs2 = std::make_unique<AnnotAppearanceCharacs>(new Dict(doc->getXRef()));
    AnnotAppearanceCharacs *rawPtr2 = appearCharacs2.get();
    widget->setAppearCharacs(std::move(appearCharacs2));
    EXPECT_EQ(widget->getAppearCharacs(), rawPtr2);
    EXPECT_NE(rawPtr1, rawPtr2);
}

// Test that the moved-from unique_ptr is null after setAppearCharacs
TEST_F(AnnotWidgetTest_860, SetAppearCharacsMovesOwnership_860) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not open test PDF file";
    }

    Object annotObj = Object(new Dict(doc->getXRef()));
    Dict *annotDict = annotObj.getDict();
    annotDict->add("Type", Object(objName, "Annot"));
    annotDict->add("Subtype", Object(objName, "Widget"));
    
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    annotDict->add("Rect", std::move(rectArray));

    Object refObj = Object(objNull);
    
    auto widget = std::make_unique<AnnotWidget>(doc.get(), std::move(annotObj), &refObj);
    
    auto appearCharacs = std::make_unique<AnnotAppearanceCharacs>(new Dict(doc->getXRef()));
    AnnotAppearanceCharacs *rawPtr = appearCharacs.get();
    
    widget->setAppearCharacs(std::move(appearCharacs));
    
    // After move, the original unique_ptr should be null
    EXPECT_EQ(appearCharacs.get(), nullptr);
    // The widget should hold the object
    EXPECT_EQ(widget->getAppearCharacs(), rawPtr);
}
