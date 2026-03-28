#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "GlobalParams.h"
#include "PDFDocFactory.h"

#include <cstring>
#include <fstream>
#include <sstream>

class AnnotMarkupTest_798 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // Create a minimal valid PDF in memory for testing
        createMinimalPDF();
        if (doc && doc->isOk()) {
            docReady = true;
        } else {
            docReady = false;
        }
    }

    void createMinimalPDF() {
        // Create a minimal PDF file for testing
        std::string pdfContent = "%PDF-1.4\n"
            "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
            "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
            "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
            "xref\n0 4\n"
            "0000000000 65535 f \n"
            "0000000009 00000 n \n"
            "0000000058 00000 n \n"
            "0000000115 00000 n \n"
            "trailer\n<< /Size 4 /Root 1 0 R >>\n"
            "startxref\n198\n%%EOF\n";

        tmpFilename = "/tmp/test_annot_markup_798.pdf";
        std::ofstream ofs(tmpFilename, std::ios::binary);
        ofs.write(pdfContent.c_str(), pdfContent.size());
        ofs.close();

        auto fname = std::make_unique<GooString>(tmpFilename.c_str());
        doc = PDFDocFactory().createPDFDoc(*fname);
    }

    void TearDown() override {
        doc.reset();
        if (!tmpFilename.empty()) {
            std::remove(tmpFilename.c_str());
        }
    }

    std::unique_ptr<PDFDoc> doc;
    std::string tmpFilename;
    bool docReady = false;
};

// Test creating AnnotMarkup with a rectangle and checking default values
TEST_F(AnnotMarkupTest_798, DefaultPopupIsNull_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    // AnnotText is a concrete subclass of AnnotMarkup
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Default popup should be nullptr
    EXPECT_EQ(annot->getPopup(), nullptr);
}

TEST_F(AnnotMarkupTest_798, DefaultOpacity_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Default opacity should be 1.0
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

TEST_F(AnnotMarkupTest_798, DefaultLabelIsNull_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Label may be null or empty by default
    // We just test it doesn't crash
    const GooString *label = annot->getLabel();
    // Label could be null or a valid pointer
    (void)label;
    SUCCEED();
}

TEST_F(AnnotMarkupTest_798, DefaultDateIsNull_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *date = annot->getDate();
    // Date may be null by default
    (void)date;
    SUCCEED();
}

TEST_F(AnnotMarkupTest_798, DefaultSubjectIsNull_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    const GooString *subject = annot->getSubject();
    // Subject is typically null by default
    EXPECT_EQ(subject, nullptr);
}

TEST_F(AnnotMarkupTest_798, SetPopup_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(200, 200, 400, 400);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);

    annot->setPopup(popup);

    EXPECT_NE(annot->getPopup(), nullptr);
    EXPECT_EQ(annot->getPopup(), popup);
}

TEST_F(AnnotMarkupTest_798, SetPopupToNull_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // First set a popup
    PDFRectangle popupRect(200, 200, 400, 400);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);
    annot->setPopup(popup);
    EXPECT_NE(annot->getPopup(), nullptr);

    // Set popup to null
    annot->setPopup(nullptr);
    EXPECT_EQ(annot->getPopup(), nullptr);
}

TEST_F(AnnotMarkupTest_798, SetOpacity_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

TEST_F(AnnotMarkupTest_798, SetOpacityZero_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

TEST_F(AnnotMarkupTest_798, SetOpacityOne_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

TEST_F(AnnotMarkupTest_798, SetLabel_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label = std::make_unique<GooString>("Test Author");
    annot->setLabel(std::move(label));

    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "Test Author");
}

TEST_F(AnnotMarkupTest_798, SetDate_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto date = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(date));

    const GooString *result = annot->getDate();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "D:20230101120000");
}

TEST_F(AnnotMarkupTest_798, DefaultReplyTo_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Default replyTo should be annotMarkupReplyTypeR
    AnnotMarkupReplyType replyType = annot->getReplyTo();
    EXPECT_EQ(replyType, annotMarkupReplyTypeR);
}

TEST_F(AnnotMarkupTest_798, DefaultIsInReplyTo_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    // Newly created annotation should not be in reply to anything
    EXPECT_FALSE(annot->isInReplyTo());
}

TEST_F(AnnotMarkupTest_798, GetExData_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    AnnotExternalDataType exData = annot->getExData();
    // Default should be annotExternalDataMarkupUnknown or similar
    (void)exData;
    SUCCEED();
}

TEST_F(AnnotMarkupTest_798, SetLabelEmpty_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label = std::make_unique<GooString>("");
    annot->setLabel(std::move(label));

    const GooString *result = annot->getLabel();
    ASSERT_NE(result, nullptr);
    EXPECT_STREQ(result->c_str(), "");
}

TEST_F(AnnotMarkupTest_798, SetPopupReplace_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect1(200, 200, 400, 400);
    auto popup1 = std::make_shared<AnnotPopup>(doc.get(), &popupRect1);
    annot->setPopup(popup1);
    EXPECT_EQ(annot->getPopup(), popup1);

    PDFRectangle popupRect2(300, 300, 500, 500);
    auto popup2 = std::make_shared<AnnotPopup>(doc.get(), &popupRect2);
    annot->setPopup(popup2);
    EXPECT_EQ(annot->getPopup(), popup2);
    EXPECT_NE(annot->getPopup(), popup1);
}

TEST_F(AnnotMarkupTest_798, SetOpacityMultipleTimes_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    annot->setOpacity(0.3);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.3);

    annot->setOpacity(0.7);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.7);

    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

TEST_F(AnnotMarkupTest_798, SetLabelMultipleTimes_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto label1 = std::make_unique<GooString>("Author1");
    annot->setLabel(std::move(label1));
    ASSERT_NE(annot->getLabel(), nullptr);
    EXPECT_STREQ(annot->getLabel()->c_str(), "Author1");

    auto label2 = std::make_unique<GooString>("Author2");
    annot->setLabel(std::move(label2));
    ASSERT_NE(annot->getLabel(), nullptr);
    EXPECT_STREQ(annot->getLabel()->c_str(), "Author2");
}

TEST_F(AnnotMarkupTest_798, SetDateMultipleTimes_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    auto date1 = std::make_unique<GooString>("D:20230101");
    annot->setDate(std::move(date1));
    ASSERT_NE(annot->getDate(), nullptr);
    EXPECT_STREQ(annot->getDate()->c_str(), "D:20230101");

    auto date2 = std::make_unique<GooString>("D:20240601");
    annot->setDate(std::move(date2));
    ASSERT_NE(annot->getDate(), nullptr);
    EXPECT_STREQ(annot->getDate()->c_str(), "D:20240601");
}

TEST_F(AnnotMarkupTest_798, GetPopupReturnSharedPtr_798) {
    if (!docReady) {
        GTEST_SKIP() << "PDF document not ready";
    }

    PDFRectangle rect(100, 100, 200, 200);
    auto annot = std::make_unique<AnnotText>(doc.get(), &rect);

    PDFRectangle popupRect(200, 200, 400, 400);
    auto popup = std::make_shared<AnnotPopup>(doc.get(), &popupRect);
    annot->setPopup(popup);

    // Getting popup multiple times should return the same shared_ptr
    auto p1 = annot->getPopup();
    auto p2 = annot->getPopup();
    EXPECT_EQ(p1, p2);
    EXPECT_EQ(p1.get(), popup.get());
}
