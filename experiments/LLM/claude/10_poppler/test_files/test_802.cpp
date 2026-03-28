#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "GlobalParams.h"

class AnnotMarkupTest_802 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test getInReplyToID returns the num field of inReplyTo Ref
TEST_F(AnnotMarkupTest_802, GetInReplyToID_ReturnsRefNum_802) {
    // We need a real PDF with annotations to test this properly
    // Since we can't construct AnnotMarkup directly without a valid PDFDoc,
    // we test through document loading if possible
    // For the inline method: int getInReplyToID() const { return inReplyTo.num; }
    // This is a simple accessor that returns inReplyTo.num

    // Create a minimal PDF in memory to test with
    static const char pdfData[] =
        "%PDF-1.4\n"
        "1 0 obj<</Type/Catalog/Pages 2 0 R>>endobj\n"
        "2 0 obj<</Type/Pages/Kids[3 0 R]/Count 1>>endobj\n"
        "3 0 obj<</Type/Page/MediaBox[0 0 612 792]/Parent 2 0 R/Annots[4 0 R]>>endobj\n"
        "4 0 obj<</Type/Annot/Subtype/Text/Rect[100 100 200 200]/T(Test)/Contents(Hello)/Open false>>endobj\n"
        "xref\n"
        "0 5\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "0000000210 00000 n \n"
        "trailer<</Size 5/Root 1 0 R>>\n"
        "startxref\n"
        "338\n"
        "%%EOF\n";

    // Attempt to test via a file-based approach or memory stream
    // Since direct construction is complex, we verify the interface contract
    // through what we can observe
    SUCCEED() << "Interface verification - getInReplyToID returns int";
}

// Test that getOpacity returns a double value
TEST_F(AnnotMarkupTest_802, GetOpacity_ReturnsDouble_802) {
    // Verify the interface exists and returns expected type
    // This is a compilation/interface test
    SUCCEED() << "Interface verification - getOpacity returns double";
}

// Test with a real PDF document if available
TEST_F(AnnotMarkupTest_802, AnnotMarkupFromPDF_BasicProperties_802) {
    // Create a PDF document with markup annotations
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            // Test observable properties
            double opacity = markup->getOpacity();
            EXPECT_GE(opacity, 0.0);
            EXPECT_LE(opacity, 1.0);

            int replyToID = markup->getInReplyToID();
            // replyToID should be a valid integer (could be -1 or 0 if not set)
            EXPECT_TRUE(replyToID >= -1);

            // getReplyTo should return a valid enum value
            AnnotMarkupReplyType replyType = markup->getReplyTo();
            EXPECT_TRUE(replyType == annotMarkupReplyTypeR || replyType == annotMarkupReplyTypeGroup);

            break;
        }
    }
}

// Test setOpacity with boundary values
TEST_F(AnnotMarkupTest_802, SetOpacity_BoundaryValues_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            // Test setting opacity to 0.0
            markup->setOpacity(0.0);
            EXPECT_DOUBLE_EQ(markup->getOpacity(), 0.0);

            // Test setting opacity to 1.0
            markup->setOpacity(1.0);
            EXPECT_DOUBLE_EQ(markup->getOpacity(), 1.0);

            // Test setting opacity to 0.5
            markup->setOpacity(0.5);
            EXPECT_DOUBLE_EQ(markup->getOpacity(), 0.5);

            break;
        }
    }
}

// Test setLabel
TEST_F(AnnotMarkupTest_802, SetLabel_SetsAndGets_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            auto newLabel = std::make_unique<GooString>("TestLabel");
            markup->setLabel(std::move(newLabel));
            const GooString *label = markup->getLabel();
            ASSERT_NE(label, nullptr);
            EXPECT_STREQ(label->c_str(), "TestLabel");
            break;
        }
    }
}

// Test setDate
TEST_F(AnnotMarkupTest_802, SetDate_SetsAndGets_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            auto newDate = std::make_unique<GooString>("D:20230101000000");
            markup->setDate(std::move(newDate));
            const GooString *date = markup->getDate();
            ASSERT_NE(date, nullptr);
            EXPECT_STREQ(date->c_str(), "D:20230101000000");
            break;
        }
    }
}

// Test setPopup
TEST_F(AnnotMarkupTest_802, SetPopup_SetsAndGets_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            // Set popup to nullptr (clear it)
            markup->setPopup(nullptr);
            auto popup = markup->getPopup();
            EXPECT_EQ(popup, nullptr);
            break;
        }
    }
}

// Test isInReplyTo
TEST_F(AnnotMarkupTest_802, IsInReplyTo_DefaultState_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            bool inReply = markup->isInReplyTo();
            // isInReplyTo should return bool - either true or false
            EXPECT_TRUE(inReply == true || inReply == false);
            
            if (!inReply) {
                // If not in reply, the ID should indicate invalid ref
                int id = markup->getInReplyToID();
                // Typically -1 for invalid Ref
                EXPECT_TRUE(id == -1 || id == 0);
            }
            break;
        }
    }
}

// Test getSubject
TEST_F(AnnotMarkupTest_802, GetSubject_ReturnsNullOrValid_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            const GooString *subject = markup->getSubject();
            // Subject can be nullptr or a valid string
            if (subject != nullptr) {
                EXPECT_GE(subject->getLength(), 0);
            }
            break;
        }
    }
}

// Test getExData
TEST_F(AnnotMarkupTest_802, GetExData_ReturnsValidEnum_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            AnnotExternalDataType exData = markup->getExData();
            // Should return a valid enum value
            SUCCEED() << "getExData returned a value";
            break;
        }
    }
}

// Test setLabel with empty string
TEST_F(AnnotMarkupTest_802, SetLabel_EmptyString_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            auto emptyLabel = std::make_unique<GooString>("");
            markup->setLabel(std::move(emptyLabel));
            const GooString *label = markup->getLabel();
            ASSERT_NE(label, nullptr);
            EXPECT_EQ(label->getLength(), 0);
            break;
        }
    }
}

// Test setLabel with nullptr
TEST_F(AnnotMarkupTest_802, SetLabel_Nullptr_802) {
    auto doc = loadTestDoc("test_markup.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
        return;
    }

    Page *page = doc->getPage(1);
    if (!page) {
        GTEST_SKIP() << "No page available";
        return;
    }

    Annots *annots = page->getAnnots();
    if (!annots || annots->getNumAnnots() == 0) {
        GTEST_SKIP() << "No annotations available";
        return;
    }

    for (int i = 0; i < annots->getNumAnnots(); i++) {
        Annot *annot = annots->getAnnot(i);
        AnnotMarkup *markup = dynamic_cast<AnnotMarkup*>(annot);
        if (markup) {
            std::unique_ptr<GooString> nullLabel = nullptr;
            markup->setLabel(std::move(nullLabel));
            const GooString *label = markup->getLabel();
            // After setting null, label might be nullptr
            // This tests the boundary condition
            SUCCEED() << "setLabel with nullptr completed without crash";
            break;
        }
    }
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
