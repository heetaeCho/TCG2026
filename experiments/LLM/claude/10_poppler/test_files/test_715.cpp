#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageTest_715 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    void SetUp() override {
    }

    void TearDown() override {
    }

    std::unique_ptr<PDFDoc> loadDocument(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test that getBoxColorInfo returns a value (may be nullptr if not set in the PDF)
// This tests the delegation from Page::getBoxColorInfo() to PageAttrs::getBoxColorInfo()
TEST_F(PageTest_715, GetBoxColorInfoDelegation_715) {
    // We need a real PDF document to test Page functionality
    // Using a simple PDF that we can load
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    ASSERT_GT(doc->getNumPages(), 0);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // getBoxColorInfo() may return nullptr if not set in the document
    // We just verify it doesn't crash and returns consistently
    Dict *boxColorInfo = page->getBoxColorInfo();
    Dict *boxColorInfo2 = page->getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, boxColorInfo2);
}

// Test basic page properties are accessible
TEST_F(PageTest_715, BasicPageProperties_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    ASSERT_GT(doc->getNumPages(), 0);
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_TRUE(page->isOk());
    EXPECT_EQ(page->getNum(), 1);
}

// Test that media box is valid
TEST_F(PageTest_715, MediaBoxIsValid_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_GT(page->getMediaWidth(), 0.0);
    EXPECT_GT(page->getMediaHeight(), 0.0);
}

// Test crop box
TEST_F(PageTest_715, CropBoxAccessible_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test bleed, trim, art boxes
TEST_F(PageTest_715, BoxesAccessible_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
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

// Test getRotate returns valid rotation value
TEST_F(PageTest_715, GetRotateReturnsValidValue_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    int rotate = page->getRotate();
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test getResourceDict
TEST_F(PageTest_715, GetResourceDict_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Resource dict should typically be non-null for a valid page
    Dict *resourceDict = page->getResourceDict();
    // May or may not be null depending on document
    (void)resourceDict;
}

// Test getDoc returns the parent document
TEST_F(PageTest_715, GetDocReturnsParentDocument_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    PDFDoc *parentDoc = page->getDoc();
    EXPECT_EQ(parentDoc, doc.get());
}

// Test getDuration
TEST_F(PageTest_715, GetDuration_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    double duration = page->getDuration();
    // Duration is typically -1 if not set
    EXPECT_TRUE(duration >= -1.0);
}

// Test getContents doesn't crash
TEST_F(PageTest_715, GetContents_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object contents = page->getContents();
    // Contents can be a stream or array of streams, or null
    (void)contents;
}

// Test getPageObj
TEST_F(PageTest_715, GetPageObj_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const Object &pageObj = page->getPageObj();
    EXPECT_TRUE(pageObj.isDict());
}

// Test getStructParents
TEST_F(PageTest_715, GetStructParents_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    int structParents = page->getStructParents();
    // structParents is -1 if not set
    (void)structParents;
}

// Test getGroup (may or may not be set)
TEST_F(PageTest_715, GetGroup_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *group = page->getGroup();
    // Group may be null if not a transparency group page
    (void)group;
}

// Test getPieceInfo
TEST_F(PageTest_715, GetPieceInfo_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *pieceInfo = page->getPieceInfo();
    // PieceInfo is optional
    (void)pieceInfo;
}

// Test getSeparationInfo
TEST_F(PageTest_715, GetSeparationInfo_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *sepInfo = page->getSeparationInfo();
    // SeparationInfo is optional
    (void)sepInfo;
}

// Test getLastModified
TEST_F(PageTest_715, GetLastModified_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const GooString *lastModified = page->getLastModified();
    // LastModified is optional, may be nullptr
    (void)lastModified;
}

// Test consistency: calling getBoxColorInfo multiple times returns same pointer
TEST_F(PageTest_715, GetBoxColorInfoConsistency_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Dict *first = page->getBoxColorInfo();
    Dict *second = page->getBoxColorInfo();
    Dict *third = page->getBoxColorInfo();
    
    EXPECT_EQ(first, second);
    EXPECT_EQ(second, third);
}

// Test getRef returns a valid Ref
TEST_F(PageTest_715, GetRef_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Ref ref = page->getRef();
    // A valid page should have a non-negative object number
    EXPECT_GE(ref.num, 0);
}

// Test hasStandaloneFields
TEST_F(PageTest_715, HasStandaloneFields_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    bool hasFields = page->hasStandaloneFields();
    // Just verify it returns without crashing
    (void)hasFields;
}

// Test isCropped
TEST_F(PageTest_715, IsCropped_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    bool cropped = page->isCropped();
    // If not cropped, crop box should equal media box
    if (!cropped) {
        const PDFRectangle *mediaBox = page->getMediaBox();
        const PDFRectangle *cropBox = page->getCropBox();
        EXPECT_DOUBLE_EQ(mediaBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(mediaBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(mediaBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(mediaBox->y2, cropBox->y2);
    }
}

// Test multiple pages if available
TEST_F(PageTest_715, MultiplePages_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr) << "Page " << i << " is null";
        EXPECT_TRUE(page->isOk()) << "Page " << i << " is not ok";
        EXPECT_EQ(page->getNum(), i) << "Page number mismatch for page " << i;
        
        // Verify getBoxColorInfo doesn't crash for any page
        Dict *boxColorInfo = page->getBoxColorInfo();
        (void)boxColorInfo;
    }
}

// Test getActions
TEST_F(PageTest_715, GetActions_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object actions = page->getActions();
    // Actions are optional
    (void)actions;
}

// Test getTrans
TEST_F(PageTest_715, GetTrans_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object trans = page->getTrans();
    // Transition is optional
    (void)trans;
}

// Test getThumb
TEST_F(PageTest_715, GetThumb_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    // Thumbnail is optional
    (void)thumb;
}

// Test getAnnotsObject
TEST_F(PageTest_715, GetAnnotsObject_715) {
    auto doc = loadDocument("./TestProjects/poppler/test_data/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object annotsObj = page->getAnnotsObject();
    // Annots array is optional
    (void)annotsObj;
}
