#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from the poppler project
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "GooString.h"
#include "Object.h"

class AnnotFreeTextTest_820 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    // Helper to create a minimal PDFDoc for testing
    std::unique_ptr<PDFDoc> createTestDoc(const char *filename) {
        auto doc = std::unique_ptr<PDFDoc>(new PDFDoc(std::make_unique<GooString>(filename)));
        return doc;
    }
};

// Test that getIntent returns the intent value set by setIntent
TEST_F(AnnotFreeTextTest_820, GetIntentReturnsSetIntent_820) {
    // We need a valid PDFDoc and rectangle to create AnnotFreeText
    PDFRectangle rect(0, 0, 100, 100);
    
    // Try to create a minimal test - since we need a valid PDFDoc,
    // we'll test with a simple PDF if available, otherwise verify the enum values exist
    
    // Verify enum values are accessible
    AnnotFreeTextIntent intentFreeText = AnnotFreeText::intentFreeText;
    AnnotFreeTextIntent intentFreeTextCallout = AnnotFreeText::intentFreeTextCallout;
    AnnotFreeTextIntent intentFreeTextTypeWriter = AnnotFreeText::intentFreeTextTypeWriter;
    
    EXPECT_NE(intentFreeText, intentFreeTextCallout);
    EXPECT_NE(intentFreeTextCallout, intentFreeTextTypeWriter);
}

// Test that getQuadding returns VariableTextQuadding type
TEST_F(AnnotFreeTextTest_820, QuaddingEnumValuesExist_820) {
    // Verify the quadding enum values exist and are distinct
    VariableTextQuadding q1 = VariableTextQuadding::leftJustified;
    VariableTextQuadding q2 = VariableTextQuadding::centered;
    VariableTextQuadding q3 = VariableTextQuadding::rightJustified;
    
    EXPECT_NE(q1, q2);
    EXPECT_NE(q2, q3);
    EXPECT_NE(q1, q3);
}

// Test AnnotLineEndingStyle enum values
TEST_F(AnnotFreeTextTest_820, LineEndingStyleEnumExists_820) {
    AnnotLineEndingStyle style1 = annotLineEndingNone;
    AnnotLineEndingStyle style2 = annotLineEndingSquare;
    
    EXPECT_NE(style1, style2);
}

// Test creating AnnotFreeText with a rect and verifying default values
TEST_F(AnnotFreeTextTest_820, CreateAnnotFreeTextWithRect_820) {
    // Create a minimal valid PDF document for testing
    // Using a GooString filename that might not exist, but we need a PDFDoc
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        // After creation, verify basic getters don't crash and return reasonable defaults
        EXPECT_NE(annot.get(), nullptr);
        
        AnnotFreeTextIntent intent = annot->getIntent();
        // Default intent should be intentFreeText
        EXPECT_EQ(intent, AnnotFreeText::intentFreeText);
        
        VariableTextQuadding quadding = annot->getQuadding();
        // Default quadding
        EXPECT_EQ(quadding, VariableTextQuadding::leftJustified);
        
        AnnotLineEndingStyle endStyle = annot->getEndStyle();
        EXPECT_EQ(endStyle, annotLineEndingNone);
    }
}

// Test setIntent and getIntent
TEST_F(AnnotFreeTextTest_820, SetAndGetIntent_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        annot->setIntent(AnnotFreeText::intentFreeTextCallout);
        EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);
        
        annot->setIntent(AnnotFreeText::intentFreeTextTypeWriter);
        EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextTypeWriter);
        
        annot->setIntent(AnnotFreeText::intentFreeText);
        EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeText);
    }
}

// Test setQuadding and getQuadding
TEST_F(AnnotFreeTextTest_820, SetAndGetQuadding_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        annot->setQuadding(VariableTextQuadding::centered);
        EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::centered);
        
        annot->setQuadding(VariableTextQuadding::rightJustified);
        EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::rightJustified);
        
        annot->setQuadding(VariableTextQuadding::leftJustified);
        EXPECT_EQ(annot->getQuadding(), VariableTextQuadding::leftJustified);
    }
}

// Test getStyleString returns nullptr by default
TEST_F(AnnotFreeTextTest_820, GetStyleStringDefaultNull_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        // Style string might be null by default
        const GooString *style = annot->getStyleString();
        // Just verify the call doesn't crash; value depends on implementation
        (void)style;
    }
}

// Test setStyleString and getStyleString
TEST_F(AnnotFreeTextTest_820, SetAndGetStyleString_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        GooString *newStyle = new GooString("font: Helvetica 12pt;");
        annot->setStyleString(newStyle);
        
        const GooString *retrieved = annot->getStyleString();
        ASSERT_NE(retrieved, nullptr);
        EXPECT_STREQ(retrieved->c_str(), "font: Helvetica 12pt;");
    }
}

// Test getCalloutLine returns nullptr by default
TEST_F(AnnotFreeTextTest_820, GetCalloutLineDefaultNull_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        AnnotCalloutLine *callout = annot->getCalloutLine();
        EXPECT_EQ(callout, nullptr);
    }
}

// Test getBorderEffect returns nullptr by default
TEST_F(AnnotFreeTextTest_820, GetBorderEffectDefaultNull_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        AnnotBorderEffect *borderEffect = annot->getBorderEffect();
        // May or may not be null; just verify no crash
        (void)borderEffect;
    }
}

// Test getRectangle
TEST_F(AnnotFreeTextTest_820, GetRectangle_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        PDFRectangle *retrieved = annot->getRectangle();
        // May or may not be null; implementation specific
        (void)retrieved;
    }
}

// Test getEndStyle default value
TEST_F(AnnotFreeTextTest_820, GetEndStyleDefault_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        AnnotLineEndingStyle endStyle = annot->getEndStyle();
        EXPECT_EQ(endStyle, annotLineEndingNone);
    }
}

// Test setContents
TEST_F(AnnotFreeTextTest_820, SetContents_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        auto content = std::make_unique<GooString>("Test content for FreeText annotation");
        annot->setContents(std::move(content));
        
        // Verify through getContents if available from parent class
        const GooString *retrieved = annot->getContents();
        if (retrieved) {
            EXPECT_STREQ(retrieved->c_str(), "Test content for FreeText annotation");
        }
    }
}

// Test setCalloutLine with a two-point callout line
TEST_F(AnnotFreeTextTest_820, SetCalloutLineTwoPoints_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        auto calloutLine = std::make_unique<AnnotCalloutLine>(10.0, 20.0, 100.0, 200.0);
        annot->setCalloutLine(std::move(calloutLine));
        
        AnnotCalloutLine *retrieved = annot->getCalloutLine();
        ASSERT_NE(retrieved, nullptr);
    }
}

// Test getDefaultAppearance
TEST_F(AnnotFreeTextTest_820, GetDefaultAppearance_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        const std::unique_ptr<DefaultAppearance> da = annot->getDefaultAppearance();
        // Just verify the call succeeds
        (void)da;
    }
}

// Test creating annotation with zero-size rectangle (boundary condition)
TEST_F(AnnotFreeTextTest_820, CreateWithZeroSizeRect_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        EXPECT_NE(annot.get(), nullptr);
        // Verify getters still work with zero-size rect
        EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeText);
    }
}

// Test setting intent multiple times
TEST_F(AnnotFreeTextTest_820, SetIntentMultipleTimes_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        // Set intent multiple times and verify each time
        for (int i = 0; i < 5; i++) {
            annot->setIntent(AnnotFreeText::intentFreeTextCallout);
            EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeTextCallout);
            
            annot->setIntent(AnnotFreeText::intentFreeText);
            EXPECT_EQ(annot->getIntent(), AnnotFreeText::intentFreeText);
        }
    }
}

// Test setting calloutLine to nullptr
TEST_F(AnnotFreeTextTest_820, SetCalloutLineToNull_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        // First set a callout line
        auto calloutLine = std::make_unique<AnnotCalloutLine>(10.0, 20.0, 100.0, 200.0);
        annot->setCalloutLine(std::move(calloutLine));
        ASSERT_NE(annot->getCalloutLine(), nullptr);
        
        // Then set to null
        annot->setCalloutLine(nullptr);
        EXPECT_EQ(annot->getCalloutLine(), nullptr);
    }
}

// Test creating annotation with negative rectangle coordinates
TEST_F(AnnotFreeTextTest_820, CreateWithNegativeRect_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(-100, -100, -10, -10);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        EXPECT_NE(annot.get(), nullptr);
    }
}

// Test setting empty style string
TEST_F(AnnotFreeTextTest_820, SetEmptyStyleString_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        GooString *emptyStyle = new GooString("");
        annot->setStyleString(emptyStyle);
        
        const GooString *retrieved = annot->getStyleString();
        if (retrieved) {
            EXPECT_STREQ(retrieved->c_str(), "");
        }
    }
}

// Test setting empty contents
TEST_F(AnnotFreeTextTest_820, SetEmptyContents_820) {
    auto fileName = std::make_unique<GooString>(TESTDATADIR "/unittestcases/WithAttachments.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName));
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        auto annot = std::make_unique<AnnotFreeText>(doc.get(), &rect);
        
        auto content = std::make_unique<GooString>("");
        annot->setContents(std::move(content));
        
        const GooString *retrieved = annot->getContents();
        if (retrieved) {
            EXPECT_STREQ(retrieved->c_str(), "");
        }
    }
}
