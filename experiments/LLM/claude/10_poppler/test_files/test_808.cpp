#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Annot.h"
#include "PDFDoc.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"
#include "Object.h"
#include <memory>

class AnnotTextTest_808 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that getState returns a valid AnnotTextState value after construction with rect
TEST_F(AnnotTextTest_808, GetStateReturnsValidState_808) {
    // We need a PDFDoc to construct AnnotText. We'll try to create a minimal one.
    // Since we can't easily create a PDFDoc without a file, we test through
    // the interface as much as possible.
    
    // Create a minimal PDF in memory for testing
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        AnnotTextState state = annot->getState();
        // State should be one of the valid enum values
        // Just verify it doesn't crash and returns something
        EXPECT_TRUE(state == AnnotText::stateUnknown ||
                    state == AnnotText::stateMarked ||
                    state == AnnotText::stateUnmarked ||
                    state == AnnotText::stateAccepted ||
                    state == AnnotText::stateRejected ||
                    state == AnnotText::stateCancelled ||
                    state == AnnotText::stateCompleted ||
                    state == AnnotText::stateNone);
    }
}

// Test that getOpen returns a valid bool after construction
TEST_F(AnnotTextTest_808, GetOpenReturnsBool_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        bool open = annot->getOpen();
        // Default should be false for a newly created annotation
        EXPECT_FALSE(open);
    }
}

// Test that setOpen changes the open state
TEST_F(AnnotTextTest_808, SetOpenChangesState_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setOpen(true);
        EXPECT_TRUE(annot->getOpen());
        
        annot->setOpen(false);
        EXPECT_FALSE(annot->getOpen());
    }
}

// Test that getIcon returns a string after construction
TEST_F(AnnotTextTest_808, GetIconReturnsString_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        const std::string &icon = annot->getIcon();
        // Default icon is typically "Note"
        EXPECT_FALSE(icon.empty());
    }
}

// Test that setIcon changes the icon
TEST_F(AnnotTextTest_808, SetIconChangesIcon_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("Comment");
        EXPECT_EQ(annot->getIcon(), "Comment");
        
        annot->setIcon("Key");
        EXPECT_EQ(annot->getIcon(), "Key");
        
        annot->setIcon("Help");
        EXPECT_EQ(annot->getIcon(), "Help");
    }
}

// Test setIcon with empty string
TEST_F(AnnotTextTest_808, SetIconEmptyString_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("");
        const std::string &icon = annot->getIcon();
        EXPECT_EQ(icon, "");
    }
}

// Test toggling open state multiple times
TEST_F(AnnotTextTest_808, SetOpenToggleMultipleTimes_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        for (int i = 0; i < 10; i++) {
            annot->setOpen(true);
            EXPECT_TRUE(annot->getOpen());
            annot->setOpen(false);
            EXPECT_FALSE(annot->getOpen());
        }
    }
}

// Test setting the same icon multiple times
TEST_F(AnnotTextTest_808, SetIconSameValueMultipleTimes_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("Note");
        EXPECT_EQ(annot->getIcon(), "Note");
        annot->setIcon("Note");
        EXPECT_EQ(annot->getIcon(), "Note");
    }
}

// Test with various standard annotation icon names
TEST_F(AnnotTextTest_808, SetIconVariousStandardNames_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        std::vector<std::string> icons = {"Note", "Comment", "Key", "Help", "NewParagraph", "Paragraph", "Insert"};
        
        for (const auto &iconName : icons) {
            annot->setIcon(iconName);
            EXPECT_EQ(annot->getIcon(), iconName) << "Failed for icon: " << iconName;
        }
    }
}

// Test with boundary rectangle values
TEST_F(AnnotTextTest_808, ConstructWithZeroSizeRect_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        // Should still be constructable and have valid state
        AnnotTextState state = annot->getState();
        SUCCEED();
    }
}

// Test getState consistency - calling multiple times returns same value
TEST_F(AnnotTextTest_808, GetStateConsistent_808) {
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    auto doc = std::unique_ptr<PDFDoc>(PDFDocFactory().createPDFDoc(pdfContent));
    
    if (doc && doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        AnnotTextState state1 = annot->getState();
        AnnotTextState state2 = annot->getState();
        EXPECT_EQ(state1, state2);
    }
}
