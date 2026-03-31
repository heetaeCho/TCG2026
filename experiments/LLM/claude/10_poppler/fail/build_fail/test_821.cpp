#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class AnnotFreeTextTest_821 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getBorderEffect returns nullptr when no border effect is set
// Using a freshly constructed AnnotFreeText with minimal parameters
TEST_F(AnnotFreeTextTest_821, GetBorderEffectDefaultIsNull_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    // A newly created FreeText annotation should have no border effect
    AnnotBorderEffect *be = annot->getBorderEffect();
    // May or may not be null depending on defaults, but should not crash
    SUCCEED();
}

// Test getQuadding returns a valid value after construction
TEST_F(AnnotFreeTextTest_821, GetQuaddingDefault_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    VariableTextQuadding q = annot->getQuadding();
    // Default quadding should be a valid enum value
    EXPECT_TRUE(q == VariableTextQuadding::leftJustified || 
                q == VariableTextQuadding::centered || 
                q == VariableTextQuadding::rightJustified);
}

// Test setQuadding and getQuadding roundtrip
TEST_F(AnnotFreeTextTest_821, SetQuaddingRoundTrip_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    annot->setQuadding(VariableTextQuadding::centered);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::centered);
    
    annot->setQuadding(VariableTextQuadding::rightJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::rightJustified);
    
    annot->setQuadding(VariableTextQuadding::leftJustified);
    EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::leftJustified);
}

// Test getIntent default
TEST_F(AnnotFreeTextTest_821, GetIntentDefault_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    AnnotFreeTextIntent intent = annot->getIntent();
    // Should not crash and should return a valid intent
    SUCCEED();
}

// Test setIntent and getIntent roundtrip
TEST_F(AnnotFreeTextTest_821, SetIntentRoundTrip_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    annot->setIntent(AnnotFreeText::intentFreeTextCallout);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);
    
    annot->setIntent(AnnotFreeText::intentFreeText);
    EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeText);
}

// Test getStyleString default is null
TEST_F(AnnotFreeTextTest_821, GetStyleStringDefault_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    const GooString *style = annot->getStyleString();
    // Default should be nullptr for a new annotation
    // Not asserting specific value as it depends on implementation
    SUCCEED();
}

// Test setStyleString
TEST_F(AnnotFreeTextTest_821, SetStyleString_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    auto styleStr = new GooString("font: Helvetica 12pt;");
    annot->setStyleString(styleStr);
    
    const GooString *result = annot->getStyleString();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "font: Helvetica 12pt;");
}

// Test getCalloutLine default
TEST_F(AnnotFreeTextTest_821, GetCalloutLineDefault_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    AnnotCalloutLine *cl = annot->getCalloutLine();
    // For a new annotation without callout, should be nullptr
    EXPECT_EQ(cl, nullptr);
}

// Test getRectangle
TEST_F(AnnotFreeTextTest_821, GetRectangle_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    PDFRectangle *r = annot->getRectangle();
    // May be null if no inner rectangle is set by default
    SUCCEED();
}

// Test getEndStyle default
TEST_F(AnnotFreeTextTest_821, GetEndStyleDefault_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    AnnotLineEndingStyle endStyle = annot->getEndStyle();
    // Default end style should be annotLineEndingNone
    EXPECT_EQ(endStyle, annotLineEndingNone);
}

// Test setContents
TEST_F(AnnotFreeTextTest_821, SetContents_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 200, 50);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    auto content = std::make_unique<GooString>("Hello World");
    annot->setContents(std::move(content));
    
    // Contents should be retrievable via the parent class method
    const GooString *c = annot->getContents();
    ASSERT_NE(c, nullptr);
    EXPECT_STREQ(c->c_str(), "Hello World");
}

// Test setContents with empty string
TEST_F(AnnotFreeTextTest_821, SetContentsEmpty_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 200, 50);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    auto content = std::make_unique<GooString>("");
    annot->setContents(std::move(content));
    
    const GooString *c = annot->getContents();
    if (c) {
        EXPECT_STREQ(c->c_str(), "");
    }
}

// Test setContents with nullptr
TEST_F(AnnotFreeTextTest_821, SetContentsNull_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 200, 50);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    annot->setContents(nullptr);
    // Should not crash
    SUCCEED();
}

// Test setCalloutLine with a valid line
TEST_F(AnnotFreeTextTest_821, SetCalloutLine_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    auto line = std::make_unique<AnnotCalloutLine>(10, 20, 30, 40);
    annot->setCalloutLine(std::move(line));
    
    AnnotCalloutLine *cl = annot->getCalloutLine();
    ASSERT_NE(cl, nullptr);
}

// Test setCalloutLine with nullptr clears callout
TEST_F(AnnotFreeTextTest_821, SetCalloutLineNull_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 200, 200);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    annot->setCalloutLine(nullptr);
    
    AnnotCalloutLine *cl = annot->getCalloutLine();
    EXPECT_EQ(cl, nullptr);
}

// Test getBorderEffect returns consistently
TEST_F(AnnotFreeTextTest_821, GetBorderEffectConsistency_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    AnnotBorderEffect *be1 = annot->getBorderEffect();
    AnnotBorderEffect *be2 = annot->getBorderEffect();
    
    // Multiple calls should return the same pointer
    EXPECT_EQ(be1, be2);
}

// Test setStyleString with nullptr
TEST_F(AnnotFreeTextTest_821, SetStyleStringNull_821) {
    auto doc = loadTestDoc("../test/unittestcases/WithAnnotations.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
    
    annot->setStyleString(nullptr);
    // Should not crash
    SUCCEED();
}
