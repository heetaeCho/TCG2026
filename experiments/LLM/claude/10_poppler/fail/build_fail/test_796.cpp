#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "PDFRectangle.h"

#include <memory>

class AnnotPopupTest_796 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that a newly created AnnotPopup with a rectangle has getOpen() returning false by default
TEST_F(AnnotPopupTest_796, DefaultOpenIsFalse_796) {
    // We need a PDFDoc to create an AnnotPopup. Since we're testing via the interface,
    // we try to create one. If PDFDoc creation requires a file, we may need a minimal PDF.
    // For unit testing purposes, we test what we can through the interface.
    
    // Create a minimal PDF document for testing
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        // By default, the popup should not be open
        EXPECT_FALSE(popup->getOpen());
    }
}

// Test that setOpen(true) makes getOpen() return true
TEST_F(AnnotPopupTest_796, SetOpenTrue_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        popup->setOpen(true);
        EXPECT_TRUE(popup->getOpen());
    }
}

// Test that setOpen(false) makes getOpen() return false
TEST_F(AnnotPopupTest_796, SetOpenFalse_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        popup->setOpen(true);
        EXPECT_TRUE(popup->getOpen());
        
        popup->setOpen(false);
        EXPECT_FALSE(popup->getOpen());
    }
}

// Test toggling open state multiple times
TEST_F(AnnotPopupTest_796, ToggleOpenMultipleTimes_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        for (int i = 0; i < 10; ++i) {
            popup->setOpen(true);
            EXPECT_TRUE(popup->getOpen());
            popup->setOpen(false);
            EXPECT_FALSE(popup->getOpen());
        }
    }
}

// Test hasParent() returns false when no parent is set
TEST_F(AnnotPopupTest_796, DefaultHasParentFalse_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        EXPECT_FALSE(popup->hasParent());
    }
}

// Test setParent sets the parent and hasParent returns true
TEST_F(AnnotPopupTest_796, SetParentMakesHasParentTrue_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        // Create another annotation to serve as parent
        PDFRectangle parentRect(0, 0, 200, 200);
        auto parentPopup = std::make_unique<AnnotPopup>(doc.get(), &parentRect);
        
        popup->setParent(parentPopup.get());
        EXPECT_TRUE(popup->hasParent());
    }
}

// Test setting open to same value repeatedly
TEST_F(AnnotPopupTest_796, SetOpenSameValueRepeatedly_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        popup->setOpen(true);
        popup->setOpen(true);
        popup->setOpen(true);
        EXPECT_TRUE(popup->getOpen());
        
        popup->setOpen(false);
        popup->setOpen(false);
        popup->setOpen(false);
        EXPECT_FALSE(popup->getOpen());
    }
}

// Test with zero-size rectangle (boundary condition)
TEST_F(AnnotPopupTest_796, ZeroSizeRectangle_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        EXPECT_FALSE(popup->getOpen());
        popup->setOpen(true);
        EXPECT_TRUE(popup->getOpen());
    }
}

// Test with negative coordinates rectangle (boundary condition)
TEST_F(AnnotPopupTest_796, NegativeCoordinatesRectangle_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(-100, -100, -50, -50);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        EXPECT_FALSE(popup->getOpen());
        EXPECT_FALSE(popup->hasParent());
    }
}

// Test that AnnotPopup is a subclass of Annot (type verification through interface)
TEST_F(AnnotPopupTest_796, IsAnnotSubclass_796) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&fileName);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto popup = std::make_unique<AnnotPopup>(doc.get(), &rect);
        
        // AnnotPopup should be usable as Annot*
        Annot* annotPtr = popup.get();
        EXPECT_NE(annotPtr, nullptr);
    }
}
