#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "Annot.h"
#include "PDFDoc.h"
#include "Object.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotScreenTest_812 : public ::testing::Test {
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

// Test that getAppearCharacs returns nullptr when no appearance characteristics are set
TEST_F(AnnotScreenTest_812, GetAppearCharacsReturnsNullWhenNotSet_812) {
    // Create a minimal PDF document for testing
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), &rect);
        
        // When created with just a rectangle and no dictionary with MK entry,
        // appearCharacs should be null
        AnnotAppearanceCharacs *characs = annotScreen->getAppearCharacs();
        EXPECT_EQ(characs, nullptr);
    }
}

// Test that getAction returns nullptr when no action is set
TEST_F(AnnotScreenTest_812, GetActionReturnsNullWhenNotSet_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), &rect);
        
        LinkAction *action = annotScreen->getAction();
        EXPECT_EQ(action, nullptr);
    }
}

// Test that getTitle returns a value (possibly null) without crashing
TEST_F(AnnotScreenTest_812, GetTitleDoesNotCrash_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), &rect);
        
        // Should not crash; title may be null for a freshly created annotation
        const GooString *title = annotScreen->getTitle();
        // Just verify it doesn't crash - title could be nullptr or empty
        SUCCEED();
    }
}

// Test creating AnnotScreen with a dictionary object
TEST_F(AnnotScreenTest_812, ConstructFromDictObject_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        // Create a minimal annotation dictionary
        Object dictObj = Object(new Dict(doc->getXRef()));
        Dict *dict = dictObj.getDict();
        
        // Set required annotation fields
        dict->add("Type", Object(objName, "Annot"));
        dict->add("Subtype", Object(objName, "Screen"));
        
        // Create Rect array
        Object rectArray = Object(new Array(doc->getXRef()));
        rectArray.arrayAdd(Object(0.0));
        rectArray.arrayAdd(Object(0.0));
        rectArray.arrayAdd(Object(100.0));
        rectArray.arrayAdd(Object(100.0));
        dict->add("Rect", std::move(rectArray));
        
        Object refObj = Object(objNull);
        
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), std::move(dictObj), &refObj);
        
        // Verify basic accessors don't crash
        AnnotAppearanceCharacs *characs = annotScreen->getAppearCharacs();
        LinkAction *action = annotScreen->getAction();
        
        // Without MK and A entries in dict, these should be null
        EXPECT_EQ(characs, nullptr);
        EXPECT_EQ(action, nullptr);
    }
}

// Test getAdditionalAction returns nullptr when no additional actions exist
TEST_F(AnnotScreenTest_812, GetAdditionalActionReturnsNullWhenNotSet_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), &rect);
        
        // Test various additional action types
        auto action = annotScreen->getAdditionalAction(Annot::actionCursorEntering);
        EXPECT_EQ(action, nullptr);
        
        action = annotScreen->getAdditionalAction(Annot::actionCursorLeaving);
        EXPECT_EQ(action, nullptr);
        
        action = annotScreen->getAdditionalAction(Annot::actionMousePressed);
        EXPECT_EQ(action, nullptr);
        
        action = annotScreen->getAdditionalAction(Annot::actionMouseReleased);
        EXPECT_EQ(action, nullptr);
    }
}

// Boundary test: AnnotScreen with zero-size rectangle
TEST_F(AnnotScreenTest_812, ZeroSizeRectangle_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), &rect);
        
        // Should still be constructible with zero-size rect
        EXPECT_EQ(annotScreen->getAppearCharacs(), nullptr);
        EXPECT_EQ(annotScreen->getAction(), nullptr);
    }
}

// Boundary test: AnnotScreen with negative coordinates in rectangle
TEST_F(AnnotScreenTest_812, NegativeCoordinatesRectangle_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(-100, -100, -50, -50);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), &rect);
        
        EXPECT_EQ(annotScreen->getAppearCharacs(), nullptr);
        EXPECT_EQ(annotScreen->getAction(), nullptr);
    }
}

// Test that AnnotScreen with appearance characteristics dictionary returns non-null
TEST_F(AnnotScreenTest_812, ConstructWithAppearanceCharacs_812) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        Object dictObj = Object(new Dict(doc->getXRef()));
        Dict *dict = dictObj.getDict();
        
        dict->add("Type", Object(objName, "Annot"));
        dict->add("Subtype", Object(objName, "Screen"));
        
        Object rectArray = Object(new Array(doc->getXRef()));
        rectArray.arrayAdd(Object(0.0));
        rectArray.arrayAdd(Object(0.0));
        rectArray.arrayAdd(Object(100.0));
        rectArray.arrayAdd(Object(100.0));
        dict->add("Rect", std::move(rectArray));
        
        // Add MK (appearance characteristics) dictionary
        Object mkDict = Object(new Dict(doc->getXRef()));
        mkDict.getDict()->add("R", Object(90));
        dict->add("MK", std::move(mkDict));
        
        Object refObj = Object(objNull);
        auto annotScreen = std::make_unique<AnnotScreen>(doc.get(), std::move(dictObj), &refObj);
        
        // With MK entry, getAppearCharacs should return non-null
        AnnotAppearanceCharacs *characs = annotScreen->getAppearCharacs();
        EXPECT_NE(characs, nullptr);
    }
}
