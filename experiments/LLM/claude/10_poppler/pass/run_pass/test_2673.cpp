#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <fstream>

#include "PDFDoc.h"
#include "Object.h"
#include "UnicodeMap.h"
#include "GooString.h"
#include "GlobalParams.h"

class PdfSubtypeTest_2673 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in memory
    std::string createMinimalPDF() {
        return "%PDF-1.4\n"
               "1 0 obj\n"
               "<< /Type /Catalog /Pages 2 0 R >>\n"
               "endobj\n"
               "2 0 obj\n"
               "<< /Type /Pages /Kids [] /Count 0 >>\n"
               "endobj\n"
               "3 0 obj\n"
               "<< /Title (Test) >>\n"
               "endobj\n"
               "xref\n"
               "0 4\n"
               "0000000000 65535 f \n"
               "0000000009 00000 n \n"
               "0000000062 00000 n \n"
               "0000000115 00000 n \n"
               "trailer\n"
               "<< /Size 4 /Root 1 0 R /Info 3 0 R >>\n"
               "startxref\n"
               "145\n"
               "%%EOF\n";
    }

    std::unique_ptr<PDFDoc> loadPDFFromString(const std::string &pdfContent) {
        // Write to temp file
        std::string tmpFile = "/tmp/test_pdfsubtype_2673.pdf";
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.write(pdfContent.data(), pdfContent.size());
        ofs.close();

        auto fileName = std::make_unique<GooString>(tmpFile);
        return std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    }
};

// Test PDFSubtype enum values
TEST_F(PdfSubtypeTest_2673, SubtypeEnumValues_2673) {
    EXPECT_EQ(subtypeNull, 0);
    EXPECT_EQ(subtypePDFA, 1);
    EXPECT_EQ(subtypePDFE, 2);
    EXPECT_EQ(subtypePDFUA, 3);
    EXPECT_EQ(subtypePDFVT, 4);
    EXPECT_EQ(subtypePDFX, 5);
    EXPECT_EQ(subtypeNone, 6);
}

// Test PDFSubtypePart enum values
TEST_F(PdfSubtypeTest_2673, SubtypePartEnumValues_2673) {
    EXPECT_EQ(subtypePartNull, 0);
    EXPECT_EQ(subtypePart1, 1);
    EXPECT_EQ(subtypePart2, 2);
    EXPECT_EQ(subtypePart3, 3);
    EXPECT_EQ(subtypePart4, 4);
    EXPECT_EQ(subtypePart5, 5);
    EXPECT_EQ(subtypePart6, 6);
    EXPECT_EQ(subtypePart7, 7);
    EXPECT_EQ(subtypePart8, 8);
    EXPECT_EQ(subtypePartNone, 9);
}

// Test PDFSubtypeConformance enum values
TEST_F(PdfSubtypeTest_2673, SubtypeConformanceEnumValues_2673) {
    EXPECT_EQ(subtypeConfNull, 0);
    EXPECT_EQ(subtypeConfA, 1);
    EXPECT_EQ(subtypeConfB, 2);
    EXPECT_EQ(subtypeConfG, 3);
    EXPECT_EQ(subtypeConfN, 4);
    EXPECT_EQ(subtypeConfP, 5);
    EXPECT_EQ(subtypeConfPG, 6);
    EXPECT_EQ(subtypeConfU, 7);
    EXPECT_EQ(subtypeConfNone, 8);
}

// Test that a minimal PDF without subtype info returns subtypeNull or subtypeNone
TEST_F(PdfSubtypeTest_2673, MinimalPDFHasNoSubtype_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        PDFSubtype subtype = doc->getPDFSubtype();
        EXPECT_TRUE(subtype == subtypeNull || subtype == subtypeNone);
    }
}

// Test that a minimal PDF has null/none subtype part
TEST_F(PdfSubtypeTest_2673, MinimalPDFHasNoSubtypePart_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        PDFSubtypePart part = doc->getPDFSubtypePart();
        EXPECT_TRUE(part == subtypePartNull || part == subtypePartNone);
    }
}

// Test that a minimal PDF has null/none conformance
TEST_F(PdfSubtypeTest_2673, MinimalPDFHasNoConformance_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        PDFSubtypeConformance conf = doc->getPDFSubtypeConformance();
        EXPECT_TRUE(conf == subtypeConfNull || conf == subtypeConfNone);
    }
}

// Test Object::isDict for doc info
TEST_F(PdfSubtypeTest_2673, DocInfoIsDictForValidPDF_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        Object info = doc->getDocInfo();
        // The minimal PDF has an Info dictionary
        EXPECT_TRUE(info.isDict() || info.isNull());
    }
}

// Test Object null behavior
TEST_F(PdfSubtypeTest_2673, ObjectNullIsNotDict_2673) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isDict());
}

// Test that PDFDoc reports correct version for minimal PDF
TEST_F(PdfSubtypeTest_2673, PDFVersionFromMinimalPDF_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        EXPECT_EQ(doc->getPDFMajorVersion(), 1);
        EXPECT_EQ(doc->getPDFMinorVersion(), 4);
    }
}

// Test that the getDocInfo returns an object from which we can query
TEST_F(PdfSubtypeTest_2673, DocInfoContainsTitle_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        auto title = doc->getDocInfoTitle();
        // Our minimal PDF has /Title (Test)
        if (title) {
            EXPECT_EQ(title->toStr(), "Test");
        }
    }
}

// Test subtypeNull is distinguishable from subtypeNone
TEST_F(PdfSubtypeTest_2673, SubtypeNullDiffersFromNone_2673) {
    EXPECT_NE(subtypeNull, subtypeNone);
}

// Test subtypePartNull is distinguishable from subtypePartNone
TEST_F(PdfSubtypeTest_2673, SubtypePartNullDiffersFromPartNone_2673) {
    EXPECT_NE(subtypePartNull, subtypePartNone);
}

// Test subtypeConfNull is distinguishable from subtypeConfNone
TEST_F(PdfSubtypeTest_2673, SubtypeConfNullDiffersFromConfNone_2673) {
    EXPECT_NE(subtypeConfNull, subtypeConfNone);
}

// Test loading a non-existent file
TEST_F(PdfSubtypeTest_2673, NonExistentFileReturnsError_2673) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_pdf_2673.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc != nullptr);
    EXPECT_FALSE(doc->isOk());
}

// Test that getPDFSubtype returns a valid enum value for non-ok document
TEST_F(PdfSubtypeTest_2673, NonOkDocSubtypeIsNullOrNone_2673) {
    auto fileName = std::make_unique<GooString>("/tmp/nonexistent_pdf_2673.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    ASSERT_TRUE(doc != nullptr);
    if (!doc->isOk()) {
        PDFSubtype subtype = doc->getPDFSubtype();
        EXPECT_TRUE(subtype == subtypeNull || subtype == subtypeNone);
    }
}

// Verify all PDFSubtype enum values are distinct
TEST_F(PdfSubtypeTest_2673, AllSubtypeValuesDistinct_2673) {
    std::set<int> values;
    values.insert(subtypeNull);
    values.insert(subtypePDFA);
    values.insert(subtypePDFE);
    values.insert(subtypePDFUA);
    values.insert(subtypePDFVT);
    values.insert(subtypePDFX);
    values.insert(subtypeNone);
    EXPECT_EQ(values.size(), 7u);
}

// Verify all PDFSubtypePart enum values are distinct
TEST_F(PdfSubtypeTest_2673, AllSubtypePartValuesDistinct_2673) {
    std::set<int> values;
    values.insert(subtypePartNull);
    values.insert(subtypePart1);
    values.insert(subtypePart2);
    values.insert(subtypePart3);
    values.insert(subtypePart4);
    values.insert(subtypePart5);
    values.insert(subtypePart6);
    values.insert(subtypePart7);
    values.insert(subtypePart8);
    values.insert(subtypePartNone);
    EXPECT_EQ(values.size(), 10u);
}

// Verify all PDFSubtypeConformance enum values are distinct
TEST_F(PdfSubtypeTest_2673, AllSubtypeConformanceValuesDistinct_2673) {
    std::set<int> values;
    values.insert(subtypeConfNull);
    values.insert(subtypeConfA);
    values.insert(subtypeConfB);
    values.insert(subtypeConfG);
    values.insert(subtypeConfN);
    values.insert(subtypeConfP);
    values.insert(subtypeConfPG);
    values.insert(subtypeConfU);
    values.insert(subtypeConfNone);
    EXPECT_EQ(values.size(), 9u);
}

// Test removing doc info and then checking subtype behavior
TEST_F(PdfSubtypeTest_2673, RemoveDocInfoAndCheckSubtype_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    if (doc->isOk()) {
        doc->removeDocInfo();
        Object info = doc->getDocInfo();
        // After removal, info should be null
        EXPECT_TRUE(info.isNull() || !info.isDict());
    }
}

// Test isOk for valid minimal PDF
TEST_F(PdfSubtypeTest_2673, ValidPDFIsOk_2673) {
    std::string pdf = createMinimalPDF();
    auto doc = loadPDFFromString(pdf);
    ASSERT_TRUE(doc != nullptr);
    EXPECT_TRUE(doc->isOk());
}
