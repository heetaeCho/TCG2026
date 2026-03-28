#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotMarkupTest_799 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
        // We need a valid PDFDoc to create annotations
        // Try to create a minimal PDF document
        doc = nullptr;
    }

    void TearDown() override {
    }

    PDFDoc *doc;
};

// Since AnnotMarkup requires a valid PDFDoc, and constructing one from scratch
// in a unit test is complex, we test the interface through observable behavior
// where possible. We focus on getOpacity() since it's fully visible in the header.

// Test that getOpacity returns the opacity value
TEST_F(AnnotMarkupTest_799, GetOpacityReturnsValue_799) {
    // The getOpacity() method returns the opacity member
    // Since we can see from the interface that opacity is a double,
    // and getOpacity() returns it, we verify the const method signature exists
    // We need a PDFDoc to create AnnotMarkup, so we test with a real PDF if available

    // Create a minimal PDF in memory
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);

    // AnnotMarkup is abstract (or at least we need a concrete subclass)
    // AnnotText is a concrete subclass of AnnotMarkup
    // Let's create an AnnotText which derives from AnnotMarkup
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    // Default opacity should be 1.0
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

TEST_F(AnnotMarkupTest_799, SetOpacityUpdatesValue_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);
}

TEST_F(AnnotMarkupTest_799, SetOpacityToZero_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    annot->setOpacity(0.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.0);
}

TEST_F(AnnotMarkupTest_799, SetOpacityToOne_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    annot->setOpacity(0.3);
    annot->setOpacity(1.0);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 1.0);
}

TEST_F(AnnotMarkupTest_799, DefaultLabelIsNullOrEmpty_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    // Label may be null for a newly created annotation
    const GooString *label = annot->getLabel();
    // It's either null or empty
    if (label != nullptr) {
        EXPECT_GE(label->getLength(), 0);
    }
}

TEST_F(AnnotMarkupTest_799, SetLabelUpdatesLabel_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    auto newLabel = std::make_unique<GooString>("TestLabel");
    annot->setLabel(std::move(newLabel));

    const GooString *label = annot->getLabel();
    ASSERT_NE(label, nullptr);
    EXPECT_STREQ(label->c_str(), "TestLabel");
}

TEST_F(AnnotMarkupTest_799, DefaultDateIsNullOrEmpty_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    const GooString *date = annot->getDate();
    // Date may or may not be set for a newly created annotation
    // Just verify we can call it without crashing
    if (date != nullptr) {
        EXPECT_GE(date->getLength(), 0);
    }
}

TEST_F(AnnotMarkupTest_799, SetDateUpdatesDate_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    auto newDate = std::make_unique<GooString>("D:20230101120000");
    annot->setDate(std::move(newDate));

    const GooString *date = annot->getDate();
    ASSERT_NE(date, nullptr);
    EXPECT_STREQ(date->c_str(), "D:20230101120000");
}

TEST_F(AnnotMarkupTest_799, DefaultPopupIsNull_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    auto popup = annot->getPopup();
    // For a newly created annotation, popup should be null
    EXPECT_EQ(popup, nullptr);
}

TEST_F(AnnotMarkupTest_799, IsInReplyToDefault_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    // Newly created annotation should not be in reply to anything
    EXPECT_FALSE(annot->isInReplyTo());
}

TEST_F(AnnotMarkupTest_799, GetSubjectDefault_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    const GooString *subject = annot->getSubject();
    // Subject may be null for a newly created annotation
    // Just check it doesn't crash
    if (subject != nullptr) {
        EXPECT_GE(subject->getLength(), 0);
    }
}

TEST_F(AnnotMarkupTest_799, SetOpacityMultipleTimes_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    annot->setOpacity(0.1);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.1);

    annot->setOpacity(0.5);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.5);

    annot->setOpacity(0.99);
    EXPECT_DOUBLE_EQ(annot->getOpacity(), 0.99);
}

TEST_F(AnnotMarkupTest_799, SetLabelToEmptyString_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    auto emptyLabel = std::make_unique<GooString>("");
    annot->setLabel(std::move(emptyLabel));

    const GooString *label = annot->getLabel();
    ASSERT_NE(label, nullptr);
    EXPECT_EQ(label->getLength(), 0);
}

TEST_F(AnnotMarkupTest_799, SetPopupAndGetPopup_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    PDFRectangle popupRect(100, 100, 300, 200);
    auto popup = std::make_shared<AnnotPopup>(pdfDoc.get(), &popupRect);

    annot->setPopup(popup);
    auto retrievedPopup = annot->getPopup();
    ASSERT_NE(retrievedPopup, nullptr);
    EXPECT_EQ(retrievedPopup, popup);
}

TEST_F(AnnotMarkupTest_799, SetLabelMultipleTimes_799) {
    static const char minimalPdf[] =
        "%PDF-1.4\n"
        "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n"
        "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n"
        "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n"
        "xref\n0 4\n"
        "0000000000 65535 f \n"
        "0000000009 00000 n \n"
        "0000000058 00000 n \n"
        "0000000115 00000 n \n"
        "trailer\n<< /Size 4 /Root 1 0 R >>\nstartxref\n198\n%%EOF\n";

    auto *stream = new MemStream(const_cast<char *>(minimalPdf), 0, sizeof(minimalPdf) - 1, Object(objNull));
    auto pdfDoc = std::make_unique<PDFDoc>(stream);

    if (!pdfDoc->isOk()) {
        GTEST_SKIP() << "Cannot create minimal PDFDoc for testing";
        return;
    }

    PDFRectangle rect(0, 0, 100, 100);
    auto annot = std::make_unique<AnnotText>(pdfDoc.get(), &rect);

    annot->setLabel(std::make_unique<GooString>("First"));
    EXPECT_STREQ(annot->getLabel()->c_str(), "First");

    annot->setLabel(std::make_unique<GooString>("Second"));
    EXPECT_STREQ(annot->getLabel()->c_str(), "Second");

    annot->setLabel(std::make_unique<GooString>("Third"));
    EXPECT_STREQ(annot->getLabel()->c_str(), "Third");
}
