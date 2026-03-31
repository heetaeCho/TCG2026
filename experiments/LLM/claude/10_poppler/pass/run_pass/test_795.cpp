#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "Object.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

#include <memory>
#include <string>

class AnnotPopupTest_795 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that a freshly created AnnotPopup (from rect) has no parent by default
TEST_F(AnnotPopupTest_795, NewAnnotPopupHasNoParent_795) {
    // We need a PDFDoc to create an AnnotPopup. Create a minimal one from a file.
    // Since we may not have a file, we test the hasParent logic via the Ref::INVALID check.
    // The hasParent() method checks parentRef != Ref::INVALID()
    // For a newly constructed popup without setParent called, parentRef should be INVALID.
    
    // Create a minimal PDF in memory to get a PDFDoc
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        EXPECT_FALSE(popup->hasParent());
    }
}

// Test that getOpen returns the expected default for a new AnnotPopup
TEST_F(AnnotPopupTest_795, NewAnnotPopupDefaultOpenState_795) {
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        // Default open state should be false
        EXPECT_FALSE(popup->getOpen());
    }
}

// Test that setOpen(true) changes the open state
TEST_F(AnnotPopupTest_795, SetOpenTrue_795) {
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        popup->setOpen(true);
        EXPECT_TRUE(popup->getOpen());
    }
}

// Test that setOpen(false) sets open state to false
TEST_F(AnnotPopupTest_795, SetOpenFalse_795) {
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        popup->setOpen(true);
        EXPECT_TRUE(popup->getOpen());
        
        popup->setOpen(false);
        EXPECT_FALSE(popup->getOpen());
    }
}

// Test toggling open state multiple times
TEST_F(AnnotPopupTest_795, ToggleOpenMultipleTimes_795) {
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 50, 50);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        for (int i = 0; i < 10; i++) {
            popup->setOpen(true);
            EXPECT_TRUE(popup->getOpen());
            popup->setOpen(false);
            EXPECT_FALSE(popup->getOpen());
        }
    }
}

// Test that setParent makes hasParent return true
TEST_F(AnnotPopupTest_795, SetParentMakesHasParentTrue_795) {
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        // Create a parent annotation (another popup or text annot)
        PDFRectangle parentRect(0, 0, 200, 200);
        auto parent = std::make_unique<AnnotPopup>(doc.get(), &parentRect);
        
        EXPECT_FALSE(popup->hasParent());
        popup->setParent(parent.get());
        EXPECT_TRUE(popup->hasParent());
    }
}

// Test hasParent with INVALID ref directly
TEST_F(AnnotPopupTest_795, HasParentReturnsFalseForInvalidRef_795) {
    // This tests the inline method: parentRef != Ref::INVALID()
    // When parentRef is default/INVALID, hasParent should be false
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(10, 10, 50, 50);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        // Before any parent is set
        EXPECT_FALSE(popup->hasParent());
    }
}

// Test creating popup with zero-size rectangle
TEST_F(AnnotPopupTest_795, ZeroSizeRectangle_795) {
    GooString *fileName = new GooString("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(*fileName));
    delete fileName;
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        EXPECT_FALSE(popup->hasParent());
        EXPECT_FALSE(popup->getOpen());
    }
}

// Test Ref::INVALID constexpr
TEST_F(AnnotPopupTest_795, RefInvalidIsConsistent_795) {
    Ref invalid1 = Ref::INVALID();
    Ref invalid2 = Ref::INVALID();
    
    EXPECT_EQ(invalid1, invalid2);
}
