#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "config.h"
#include "poppler/Annot.h"
#include "poppler/PDFDoc.h"
#include "poppler/PDFDocFactory.h"
#include "poppler/GlobalParams.h"
#include "poppler/Object.h"

#include <memory>
#include <string>

class AnnotCaretTest_851 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal PDF document for testing
        doc = nullptr;
    }

    void TearDown() override {
        delete doc;
        doc = nullptr;
    }

    PDFDoc *createTestDoc() {
        // Try to create a PDFDoc from a minimal valid PDF in memory
        static const char minimalPDF[] =
            "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n206\n%%EOF\n";

        auto *stream = new MemStream(const_cast<char *>(minimalPDF), 0, sizeof(minimalPDF) - 1, Object(objNull));
        auto *newDoc = new PDFDoc(stream);
        return newDoc;
    }

    PDFDoc *doc;
};

TEST_F(AnnotCaretTest_851, ConstructWithRect_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);
}

TEST_F(AnnotCaretTest_851, GetSymbolDefault_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    // Default symbol should be None
    AnnotCaret::AnnotCaretSymbol sym = annot->getSymbol();
    EXPECT_EQ(sym, AnnotCaret::symbolNone);
}

TEST_F(AnnotCaretTest_851, SetSymbolParagraph_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    annot->setSymbol(AnnotCaret::symbolP);
    EXPECT_EQ(annot->getSymbol(), AnnotCaret::symbolP);
}

TEST_F(AnnotCaretTest_851, SetSymbolNone_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    annot->setSymbol(AnnotCaret::symbolP);
    annot->setSymbol(AnnotCaret::symbolNone);
    EXPECT_EQ(annot->getSymbol(), AnnotCaret::symbolNone);
}

TEST_F(AnnotCaretTest_851, SetSymbolToggle_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(50.0, 50.0, 150.0, 150.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    // Toggle between symbols multiple times
    annot->setSymbol(AnnotCaret::symbolP);
    EXPECT_EQ(annot->getSymbol(), AnnotCaret::symbolP);

    annot->setSymbol(AnnotCaret::symbolNone);
    EXPECT_EQ(annot->getSymbol(), AnnotCaret::symbolNone);

    annot->setSymbol(AnnotCaret::symbolP);
    EXPECT_EQ(annot->getSymbol(), AnnotCaret::symbolP);
}

TEST_F(AnnotCaretTest_851, GetCaretRectInitial_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(100.0, 200.0, 300.0, 400.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    // getCaretRect may return nullptr if not set from a dictionary
    // Just verify it doesn't crash
    PDFRectangle *caretRect = annot->getCaretRect();
    // caretRect can be nullptr for a newly created annotation
    (void)caretRect;
}

TEST_F(AnnotCaretTest_851, ConstructWithZeroRect_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(0.0, 0.0, 0.0, 0.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    // Should still be constructable with a zero-area rect
    AnnotCaret::AnnotCaretSymbol sym = annot->getSymbol();
    EXPECT_EQ(sym, AnnotCaret::symbolNone);
}

TEST_F(AnnotCaretTest_851, SetSameSymbolTwice_851) {
    doc = createTestDoc();
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        GTEST_SKIP() << "Could not create test PDF document";
    }

    PDFRectangle rect(10.0, 20.0, 30.0, 40.0);
    auto annot = std::make_unique<AnnotCaret>(doc, &rect);
    ASSERT_NE(annot, nullptr);

    annot->setSymbol(AnnotCaret::symbolP);
    annot->setSymbol(AnnotCaret::symbolP);
    EXPECT_EQ(annot->getSymbol(), AnnotCaret::symbolP);
}
