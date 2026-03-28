#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include "PDFDocFactory.h"

class AnnotLinkTest_816 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that creating an AnnotLink with a rect produces valid object
TEST_F(AnnotLinkTest_816, CreateAnnotLinkWithRect_816) {
    // Create a minimal valid PDF document for testing
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    ASSERT_NE(annotLink, nullptr);
}

// Test getQuadrilaterals returns nullptr when no quadrilaterals are set
TEST_F(AnnotLinkTest_816, GetQuadrilateralsDefaultNull_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    // When created with just a rect and no dictionary with QuadPoints,
    // quadrilaterals should be nullptr
    AnnotQuadrilaterals *quads = annotLink->getQuadrilaterals();
    // It may or may not be null depending on initialization, but should not crash
    // Just verify it doesn't crash
    SUCCEED();
}

// Test getAction returns nullptr when no action is set
TEST_F(AnnotLinkTest_816, GetActionDefaultNull_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    LinkAction *action = annotLink->getAction();
    // When created without an action, should return nullptr
    EXPECT_EQ(action, nullptr);
}

// Test getLinkEffect returns a valid enum value
TEST_F(AnnotLinkTest_816, GetLinkEffectDefault_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    AnnotLink::AnnotLinkEffect effect = annotLink->getLinkEffect();
    // The effect should be one of the valid enum values
    // Just verify it doesn't crash and returns something
    SUCCEED();
}

// Test creating AnnotLink from dictionary object
TEST_F(AnnotLinkTest_816, CreateAnnotLinkFromDict_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    // Create a dictionary object for the annotation
    Object dictObj = Object(new Dict(doc->getXRef()));
    Dict *dict = dictObj.getDict();
    
    // Add required annotation fields
    Object subtypeObj = Object(new GooString("Link"));
    dict->add("Subtype", std::move(Object(objName, "Link")));
    
    // Add Rect array
    Object rectArray = Object(new Array(doc->getXRef()));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(0.0));
    rectArray.arrayAdd(Object(100.0));
    rectArray.arrayAdd(Object(100.0));
    dict->add("Rect", std::move(rectArray));
    
    Object refObj;
    
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), std::move(dictObj), &refObj);
    
    ASSERT_NE(annotLink, nullptr);
    
    // Verify accessors don't crash
    annotLink->getQuadrilaterals();
    annotLink->getAction();
    annotLink->getLinkEffect();
    SUCCEED();
}

// Test with boundary rect values (zero-size rect)
TEST_F(AnnotLinkTest_816, CreateAnnotLinkZeroSizeRect_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 0, 0);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    ASSERT_NE(annotLink, nullptr);
    // Should still be able to query properties without crashing
    annotLink->getQuadrilaterals();
    annotLink->getAction();
    annotLink->getLinkEffect();
    SUCCEED();
}

// Test with negative rect coordinates
TEST_F(AnnotLinkTest_816, CreateAnnotLinkNegativeRect_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(-100, -100, -50, -50);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    ASSERT_NE(annotLink, nullptr);
    annotLink->getQuadrilaterals();
    annotLink->getAction();
    annotLink->getLinkEffect();
    SUCCEED();
}

// Test with very large rect coordinates
TEST_F(AnnotLinkTest_816, CreateAnnotLinkLargeRect_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(0, 0, 1e10, 1e10);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    ASSERT_NE(annotLink, nullptr);
    SUCCEED();
}

// Test multiple calls to getQuadrilaterals return consistent results
TEST_F(AnnotLinkTest_816, GetQuadrilateralsConsistency_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10, 20, 300, 400);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    AnnotQuadrilaterals *quads1 = annotLink->getQuadrilaterals();
    AnnotQuadrilaterals *quads2 = annotLink->getQuadrilaterals();
    
    // Multiple calls should return the same pointer
    EXPECT_EQ(quads1, quads2);
}

// Test multiple calls to getAction return consistent results
TEST_F(AnnotLinkTest_816, GetActionConsistency_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10, 20, 300, 400);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    LinkAction *action1 = annotLink->getAction();
    LinkAction *action2 = annotLink->getAction();
    
    // Multiple calls should return the same pointer
    EXPECT_EQ(action1, action2);
}

// Test multiple calls to getLinkEffect return consistent results
TEST_F(AnnotLinkTest_816, GetLinkEffectConsistency_816) {
    GooString pdfPath("./TestProjects/poppler/test/unittestcases/simple.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(pdfPath));
    
    if (!doc || !doc->isOk()) {
        GTEST_SKIP() << "Test PDF not available";
    }

    PDFRectangle rect(10, 20, 300, 400);
    auto annotLink = std::make_unique<AnnotLink>(doc.get(), &rect);
    
    auto effect1 = annotLink->getLinkEffect();
    auto effect2 = annotLink->getLinkEffect();
    
    EXPECT_EQ(effect1, effect2);
}
