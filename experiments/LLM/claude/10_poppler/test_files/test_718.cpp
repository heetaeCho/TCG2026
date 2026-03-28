#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageTest_718 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadDoc(const char *filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getPieceInfo returns non-null or null depending on the document
// For a typical PDF without piece info, it should return nullptr
TEST_F(PageTest_718, GetPieceInfoReturnsNullForTypicalPage_718) {
    // We need a real PDF to test. Use a simple test PDF if available.
    // Since we can't guarantee a specific file exists, we'll create a minimal doc
    // from a buffer or use a known test file path.
    
    // Try loading a simple PDF
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    ASSERT_GT(doc->getNumPages(), 0);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // For most standard PDFs, getPieceInfo() will return nullptr
    // since PieceInfo is an optional entry
    Dict *pieceInfo = page->getPieceInfo();
    // We just verify it doesn't crash - the value depends on the PDF content
    // For a typical test PDF without piece info, it should be null
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test basic page properties alongside getPieceInfo
TEST_F(PageTest_718, PageBasicPropertiesAreValid_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    ASSERT_GT(doc->getNumPages(), 0);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_TRUE(page->isOk());
    EXPECT_EQ(page->getNum(), 1);
    EXPECT_GT(page->getMediaWidth(), 0.0);
    EXPECT_GT(page->getMediaHeight(), 0.0);
    
    // getPieceInfo should be callable without issues
    page->getPieceInfo();
}

// Test that getMediaBox and getCropBox return valid boxes
TEST_F(PageTest_718, MediaBoxAndCropBoxAreValid_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_GE(mediaBox->x2 - mediaBox->x1, 0.0);
    EXPECT_GE(mediaBox->y2 - mediaBox->y1, 0.0);
    
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test bleedBox, trimBox, artBox are accessible
TEST_F(PageTest_718, BleedTrimArtBoxAccessible_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
    
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
    
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getRotate returns a valid rotation
TEST_F(PageTest_718, GetRotateReturnsValidValue_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    int rotate = page->getRotate();
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test getResourceDict doesn't crash
TEST_F(PageTest_718, GetResourceDictAccessible_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Should not crash
    Dict *resDict = page->getResourceDict();
    // Resource dict may or may not be null depending on the page
    (void)resDict;
}

// Test getGroup and getSeparationInfo
TEST_F(PageTest_718, GetGroupAndSeparationInfo_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // These should not crash
    Dict *group = page->getGroup();
    Dict *sepInfo = page->getSeparationInfo();
    // For typical test PDFs these will be null
    (void)group;
    (void)sepInfo;
}

// Test getBoxColorInfo
TEST_F(PageTest_718, GetBoxColorInfo_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *boxColorInfo = page->getBoxColorInfo();
    // Typically null for simple PDFs
    (void)boxColorInfo;
}

// Test getDuration
TEST_F(PageTest_718, GetDuration_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    double duration = page->getDuration();
    // Duration should be >= -1 (where -1 typically means not set)
    EXPECT_GE(duration, -1.0);
}

// Test getCropWidth and getCropHeight
TEST_F(PageTest_718, CropDimensionsValid_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test getContents and getThumb
TEST_F(PageTest_718, GetContentsAndThumb_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object contents = page->getContents();
    Object thumb = page->getThumb();
    // Just verify these don't crash
}

// Test getRef returns a valid ref
TEST_F(PageTest_718, GetRefReturnsValidRef_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Ref ref = page->getRef();
    EXPECT_GE(ref.num, 0);
    EXPECT_GE(ref.gen, 0);
}

// Test getPageObj returns a valid object
TEST_F(PageTest_718, GetPageObjReturnsDict_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test getDoc returns the parent doc
TEST_F(PageTest_718, GetDocReturnsParentDoc_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_EQ(page->getDoc(), doc.get());
}

// Test isCropped
TEST_F(PageTest_718, IsCroppedReturnsBool_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Just verify it returns a boolean value without crashing
    bool cropped = page->isCropped();
    (void)cropped;
}

// Test hasStandaloneFields
TEST_F(PageTest_718, HasStandaloneFields_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    bool hasFields = page->hasStandaloneFields();
    // For a typical non-form PDF, this should be false
    EXPECT_FALSE(hasFields);
}

// Test multiple pages if document has more than one
TEST_F(PageTest_718, MultiplePagesPieceInfoConsistency_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr) << "Page " << i << " should not be null";
        EXPECT_EQ(page->getNum(), i);
        
        // getPieceInfo should be safe to call on every page
        page->getPieceInfo();
    }
}

// Test getStructParents
TEST_F(PageTest_718, GetStructParents_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    int structParents = page->getStructParents();
    // structParents can be -1 if not set, or >= 0
    EXPECT_GE(structParents, -1);
}

// Test getTrans and getActions
TEST_F(PageTest_718, GetTransAndActions_718) {
    auto doc = loadDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object trans = page->getTrans();
    Object actions = page->getActions();
    // Just ensure no crashes
}
