#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// We need to include the necessary headers from the poppler project
#include "Annot.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"

#include <memory>

class AnnotTextTest_807 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }
};

// Test that a newly created AnnotText has a default icon
TEST_F(AnnotTextTest_807, DefaultIconIsNote_807) {
    // Create a minimal AnnotText using a PDFRectangle
    // Since we can't easily create a full PDFDoc without a file,
    // we test through the interface what we can observe
    PDFRectangle rect(0, 0, 100, 100);
    
    // We need a valid PDFDoc to create an AnnotText
    // Try creating from a minimal PDF in memory
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        // The default icon for a text annotation is typically "Note"
        const std::string &icon = annot->getIcon();
        EXPECT_FALSE(icon.empty());
    }
}

// Test setIcon and getIcon
TEST_F(AnnotTextTest_807, SetIconAndGetIcon_807) {
    PDFRectangle rect(0, 0, 100, 100);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("Comment");
        EXPECT_EQ(annot->getIcon(), "Comment");
    }
}

// Test setIcon with various standard icon names
TEST_F(AnnotTextTest_807, SetIconVariousNames_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        // Test with different standard icon names
        std::vector<std::string> iconNames = {
            "Note", "Comment", "Key", "Help", "NewParagraph",
            "Paragraph", "Insert"
        };
        
        for (const auto &name : iconNames) {
            annot->setIcon(name);
            EXPECT_EQ(annot->getIcon(), name) << "Failed for icon: " << name;
        }
    }
}

// Test setIcon with empty string
TEST_F(AnnotTextTest_807, SetIconEmptyString_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("");
        EXPECT_EQ(annot->getIcon(), "");
    }
}

// Test setOpen and getOpen
TEST_F(AnnotTextTest_807, SetOpenAndGetOpen_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setOpen(true);
        EXPECT_TRUE(annot->getOpen());
        
        annot->setOpen(false);
        EXPECT_FALSE(annot->getOpen());
    }
}

// Test getOpen default value
TEST_F(AnnotTextTest_807, DefaultOpenIsFalse_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        // Default should be false (closed)
        EXPECT_FALSE(annot->getOpen());
    }
}

// Test getState on newly created annotation
TEST_F(AnnotTextTest_807, GetStateDefault_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        // Just verify getState returns without crashing
        auto state = annot->getState();
        // The state should be a valid AnnotTextState value
        (void)state;
    }
}

// Test setIcon overwrite behavior
TEST_F(AnnotTextTest_807, SetIconOverwrite_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("Comment");
        EXPECT_EQ(annot->getIcon(), "Comment");
        
        annot->setIcon("Key");
        EXPECT_EQ(annot->getIcon(), "Key");
        
        // Verify old value is gone
        EXPECT_NE(annot->getIcon(), "Comment");
    }
}

// Test setIcon with non-standard icon name
TEST_F(AnnotTextTest_807, SetIconNonStandardName_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("CustomIconName");
        EXPECT_EQ(annot->getIcon(), "CustomIconName");
    }
}

// Test toggling open state multiple times
TEST_F(AnnotTextTest_807, ToggleOpenMultipleTimes_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        for (int i = 0; i < 10; i++) {
            annot->setOpen(true);
            EXPECT_TRUE(annot->getOpen());
            annot->setOpen(false);
            EXPECT_FALSE(annot->getOpen());
        }
    }
}

// Test getIcon returns a const reference
TEST_F(AnnotTextTest_807, GetIconReturnsConstRef_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        annot->setIcon("Note");
        const std::string &iconRef1 = annot->getIcon();
        const std::string &iconRef2 = annot->getIcon();
        
        // Both references should point to the same string
        EXPECT_EQ(&iconRef1, &iconRef2);
        EXPECT_EQ(iconRef1, "Note");
    }
}

// Test with boundary rectangle values
TEST_F(AnnotTextTest_807, BoundaryRectangleValues_807) {
    PDFRectangle rect(0, 0, 0, 0);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        // Should still be able to get/set icon on zero-sized annotation
        const std::string &icon = annot->getIcon();
        EXPECT_FALSE(icon.empty());
    }
}

// Test setIcon with a very long string
TEST_F(AnnotTextTest_807, SetIconLongString_807) {
    PDFRectangle rect(0, 0, 50, 50);
    GooString pdfContent("./TestProjects/poppler/test/unittestcases/truetype.pdf");
    auto doc = std::make_unique<PDFDoc>(&pdfContent);
    
    if (doc->isOk()) {
        auto annot = std::make_unique<AnnotText>(doc.get(), &rect);
        
        std::string longIcon(1000, 'A');
        annot->setIcon(longIcon);
        EXPECT_EQ(annot->getIcon(), longIcon);
    }
}
