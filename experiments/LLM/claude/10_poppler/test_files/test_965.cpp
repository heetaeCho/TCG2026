#include <gtest/gtest.h>
#include <memory>
#include <string>
#include <cstring>

#include "PDFDoc.h"
#include "GlobalParams.h"
#include "GooString.h"

class PDFDocOkToPrintHighResTest_965 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    // Helper to create a minimal valid PDF in memory as a string
    static std::string createMinimalPDF() {
        std::string pdf;
        pdf += "%PDF-1.4\n";
        pdf += "1 0 obj\n<< /Type /Catalog /Pages 2 0 R >>\nendobj\n";
        pdf += "2 0 obj\n<< /Type /Pages /Kids [3 0 R] /Count 1 >>\nendobj\n";
        pdf += "3 0 obj\n<< /Type /Page /Parent 2 0 R /MediaBox [0 0 612 792] >>\nendobj\n";
        
        std::string xrefStr;
        xrefStr += "xref\n";
        xrefStr += "0 4\n";
        xrefStr += "0000000000 65535 f \n";
        
        // Calculate offsets
        size_t obj1Off = pdf.find("1 0 obj");
        size_t obj2Off = pdf.find("2 0 obj");
        size_t obj3Off = pdf.find("3 0 obj");
        
        char buf[21];
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj1Off);
        xrefStr += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj2Off);
        xrefStr += buf;
        snprintf(buf, sizeof(buf), "%010zu 00000 n \n", obj3Off);
        xrefStr += buf;
        
        size_t xrefOff = pdf.size();
        pdf += xrefStr;
        pdf += "trailer\n<< /Size 4 /Root 1 0 R >>\n";
        pdf += "startxref\n";
        pdf += std::to_string(xrefOff) + "\n";
        pdf += "%%EOF\n";
        
        return pdf;
    }

    std::unique_ptr<PDFDoc> createDocFromString(const std::string &pdfData) {
        // Create a MemStream-based PDFDoc
        auto *dataCopy = (char *)gmalloc(pdfData.size());
        memcpy(dataCopy, pdfData.data(), pdfData.size());
        Object obj;
        auto str = std::make_unique<MemStream>(dataCopy, 0, pdfData.size(), Object(objNull));
        return std::make_unique<PDFDoc>(std::move(str), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    }
};

// Test that okToPrintHighRes returns true for an unencrypted PDF
TEST_F(PDFDocOkToPrintHighResTest_965, UnencryptedPDFAllowsPrintHighRes_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes());
}

// Test okToPrintHighRes with default parameter (ignoreOwnerPW = false)
TEST_F(PDFDocOkToPrintHighResTest_965, DefaultParameterFalse_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes(false));
}

// Test okToPrintHighRes with ignoreOwnerPW = true on unencrypted doc
TEST_F(PDFDocOkToPrintHighResTest_965, IgnoreOwnerPWTrueOnUnencrypted_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrintHighRes(true));
}

// Test that okToPrint also returns true for unencrypted PDF (related permission)
TEST_F(PDFDocOkToPrintHighResTest_965, UnencryptedPDFOkToPrint_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
}

// Test that isEncrypted returns false for a minimal unencrypted PDF
TEST_F(PDFDocOkToPrintHighResTest_965, UnencryptedPDFNotEncrypted_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    EXPECT_FALSE(doc->isEncrypted());
}

// Test that all permission methods return true for unencrypted PDF
TEST_F(PDFDocOkToPrintHighResTest_965, AllPermissionsTrueForUnencrypted_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    EXPECT_TRUE(doc->okToPrint());
    EXPECT_TRUE(doc->okToPrintHighRes());
    EXPECT_TRUE(doc->okToChange());
    EXPECT_TRUE(doc->okToCopy());
    EXPECT_TRUE(doc->okToAddNotes());
    EXPECT_TRUE(doc->okToFillForm());
    EXPECT_TRUE(doc->okToAccessibility());
    EXPECT_TRUE(doc->okToAssemble());
}

// Test that okToPrintHighRes with both true and false returns same result for unencrypted
TEST_F(PDFDocOkToPrintHighResTest_965, BothIgnoreOwnerPWValuesSameForUnencrypted_965) {
    std::string pdfData = createMinimalPDF();
    auto doc = createDocFromString(pdfData);
    
    ASSERT_TRUE(doc->isOk());
    bool resultFalse = doc->okToPrintHighRes(false);
    bool resultTrue = doc->okToPrintHighRes(true);
    EXPECT_EQ(resultFalse, resultTrue);
}

// Test that an error/invalid PDFDoc can be created via ErrorPDFDoc
TEST_F(PDFDocOkToPrintHighResTest_965, ErrorPDFDocNotOk_965) {
    auto doc = PDFDoc::ErrorPDFDoc(1, std::make_unique<GooString>("nonexistent.pdf"));
    ASSERT_NE(doc, nullptr);
    EXPECT_FALSE(doc->isOk());
}

// Test creating PDFDoc from a non-existent file
TEST_F(PDFDocOkToPrintHighResTest_965, NonExistentFileNotOk_965) {
    auto fileName = std::make_unique<GooString>("/tmp/this_file_should_not_exist_965.pdf");
    auto doc = std::make_unique<PDFDoc>(std::move(fileName), std::optional<GooString>(), std::optional<GooString>(), std::function<void()>());
    EXPECT_FALSE(doc->isOk());
}
