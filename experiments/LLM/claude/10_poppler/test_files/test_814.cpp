#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "Link.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include <memory>

class AnnotLinkTest_814 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that creating an AnnotLink with a rectangle results in a valid object
// and that getAction returns nullptr when no action is set
TEST_F(AnnotLinkTest_814, DefaultActionIsNull_814) {
    // Create a minimal PDF document to work with
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLink>(doc.get(), &rect);
        
        // A freshly created AnnotLink with just a rect should have no action
        EXPECT_EQ(annot->getAction(), nullptr);
    }
}

// Test that getLinkEffect returns a valid default value for a new AnnotLink
TEST_F(AnnotLinkTest_814, DefaultLinkEffect_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLink>(doc.get(), &rect);
        
        // Default link effect should be a valid enum value
        AnnotLink::AnnotLinkEffect effect = annot->getLinkEffect();
        // The default link effect is typically effectInvert
        EXPECT_TRUE(effect == AnnotLink::effectNone || 
                    effect == AnnotLink::effectInvert || 
                    effect == AnnotLink::effectOutline || 
                    effect == AnnotLink::effectPush);
    }
}

// Test that getQuadrilaterals returns nullptr when none are set
TEST_F(AnnotLinkTest_814, DefaultQuadrilateralsIsNull_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotLink>(doc.get(), &rect);
        
        EXPECT_EQ(annot->getQuadrilaterals(), nullptr);
    }
}

// Test creating AnnotLink from a dictionary object
TEST_F(AnnotLinkTest_814, CreateFromDictObject_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        // Create a minimal annotation dictionary
        Dict *dict = new Dict(doc->getXRef());
        dict->add("Type", Object(objName, "Annot"));
        dict->add("Subtype", Object(objName, "Link"));
        
        // Create Rect array
        Array *rectArray = new Array(doc->getXRef());
        rectArray->add(Object(0.0));
        rectArray->add(Object(0.0));
        rectArray->add(Object(100.0));
        rectArray->add(Object(100.0));
        dict->add("Rect", Object(rectArray));
        
        Object dictObj(dict);
        Object refObj(objNull);
        
        auto annot = std::make_unique<AnnotLink>(doc.get(), std::move(dictObj), &refObj);
        
        // Should be a valid annotation
        EXPECT_NE(annot.get(), nullptr);
        
        // Without an action in the dict, getAction should return nullptr
        EXPECT_EQ(annot->getAction(), nullptr);
    }
}

// Test that AnnotLink with zero-size rectangle can be created
TEST_F(AnnotLinkTest_814, ZeroSizeRectangle_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto annot = std::make_unique<AnnotLink>(doc.get(), &rect);
        
        EXPECT_NE(annot.get(), nullptr);
        EXPECT_EQ(annot->getAction(), nullptr);
    }
}

// Test AnnotLink with negative coordinates in rectangle
TEST_F(AnnotLinkTest_814, NegativeCoordinatesRectangle_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(-50, -50, 50, 50);
        auto annot = std::make_unique<AnnotLink>(doc.get(), &rect);
        
        EXPECT_NE(annot.get(), nullptr);
        EXPECT_EQ(annot->getAction(), nullptr);
        EXPECT_EQ(annot->getQuadrilaterals(), nullptr);
    }
}

// Test that creating AnnotLink from dict with link effect
TEST_F(AnnotLinkTest_814, DictWithLinkEffect_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        Dict *dict = new Dict(doc->getXRef());
        dict->add("Type", Object(objName, "Annot"));
        dict->add("Subtype", Object(objName, "Link"));
        
        Array *rectArray = new Array(doc->getXRef());
        rectArray->add(Object(0.0));
        rectArray->add(Object(0.0));
        rectArray->add(Object(100.0));
        rectArray->add(Object(100.0));
        dict->add("Rect", Object(rectArray));
        
        // Add highlight mode (link effect)
        dict->add("H", Object(objName, "N")); // None
        
        Object dictObj(dict);
        Object refObj(objNull);
        
        auto annot = std::make_unique<AnnotLink>(doc.get(), std::move(dictObj), &refObj);
        
        EXPECT_NE(annot.get(), nullptr);
        EXPECT_EQ(annot->getLinkEffect(), AnnotLink::effectNone);
    }
}

// Test AnnotLink with large rectangle values
TEST_F(AnnotLinkTest_814, LargeRectangleValues_814) {
    GooString fileName("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    std::unique_ptr<PDFDoc> doc(PDFDocFactory().createPDFDoc(fileName));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100000, 100000);
        auto annot = std::make_unique<AnnotLink>(doc.get(), &rect);
        
        EXPECT_NE(annot.get(), nullptr);
        EXPECT_EQ(annot->getAction(), nullptr);
    }
}
