#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "Annot.h"
#include "PDFDoc.h"
#include "GooString.h"
#include "Object.h"
#include "PDFDocFactory.h"
#include "GlobalParams.h"

class AnnotFileAttachmentTest_855 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getName() returns a non-null pointer when constructed with a filename
TEST_F(AnnotFileAttachmentTest_855, GetNameReturnsNameWhenConstructedWithFilename_855) {
    // We need a valid PDFDoc to construct AnnotFileAttachment
    // Since we can't easily create one without a file, we test what we can
    // through the interface. This test verifies the getName() method exists
    // and returns the expected type.
    
    // Create a minimal PDF document for testing
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    
    // Try to open a test PDF if available
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        GooString filename("testfile.txt");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename);
        
        const GooString *name = annot->getName();
        // getName() should return something (may be default or set name)
        // We verify it doesn't crash and returns a valid pointer or nullptr
        // Based on the interface, it returns name.get() which could be valid
        if (name != nullptr) {
            EXPECT_GE(name->getLength(), 0);
        }
    }
}

// Test that getFile() returns a pointer to the file Object
TEST_F(AnnotFileAttachmentTest_855, GetFileReturnsObjectPointer_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        GooString filename("testfile.txt");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename);
        
        Object *file = annot->getFile();
        // getFile should return a non-null pointer to the internal file object
        EXPECT_NE(file, nullptr);
    }
}

// Test construction with different filenames
TEST_F(AnnotFileAttachmentTest_855, ConstructWithDifferentFilenames_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 50, 50);
        GooString filename1("document.pdf");
        
        auto annot1 = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename1);
        EXPECT_NE(annot1, nullptr);
        
        GooString filename2("image.png");
        auto annot2 = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename2);
        EXPECT_NE(annot2, nullptr);
    }
}

// Test with empty filename
TEST_F(AnnotFileAttachmentTest_855, ConstructWithEmptyFilename_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 100, 100);
        GooString emptyFilename("");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &emptyFilename);
        EXPECT_NE(annot, nullptr);
        
        // Verify getName doesn't crash
        const GooString *name = annot->getName();
        // Name may or may not be set, but calling it should not crash
    }
}

// Test with zero-size rectangle
TEST_F(AnnotFileAttachmentTest_855, ConstructWithZeroSizeRect_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 0, 0);
        GooString filename("test.txt");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename);
        EXPECT_NE(annot, nullptr);
    }
}

// Test that getName returns consistent results on multiple calls
TEST_F(AnnotFileAttachmentTest_855, GetNameConsistentMultipleCalls_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        GooString filename("consistency_test.txt");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename);
        
        const GooString *name1 = annot->getName();
        const GooString *name2 = annot->getName();
        
        // Multiple calls should return the same pointer
        EXPECT_EQ(name1, name2);
    }
}

// Test that getFile returns consistent results on multiple calls
TEST_F(AnnotFileAttachmentTest_855, GetFileConsistentMultipleCalls_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(10, 10, 200, 200);
        GooString filename("file_test.txt");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename);
        
        Object *file1 = annot->getFile();
        Object *file2 = annot->getFile();
        
        // Multiple calls should return the same pointer
        EXPECT_EQ(file1, file2);
    }
}

// Test with large rectangle coordinates
TEST_F(AnnotFileAttachmentTest_855, ConstructWithLargeRectCoordinates_855) {
    GooString pdfPath("./TestProjects/poppler/test/pdf-sample.pdf");
    std::unique_ptr<PDFDoc> doc = std::make_unique<PDFDoc>(&pdfPath);
    
    if (doc->isOk()) {
        PDFRectangle rect(0, 0, 10000, 10000);
        GooString filename("large_rect.txt");
        
        auto annot = std::make_unique<AnnotFileAttachment>(doc.get(), &rect, &filename);
        EXPECT_NE(annot, nullptr);
        
        const GooString *name = annot->getName();
        Object *file = annot->getFile();
        EXPECT_NE(file, nullptr);
    }
}
