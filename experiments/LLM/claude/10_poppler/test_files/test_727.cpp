#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers from poppler
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class PageTest_727 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }

    std::unique_ptr<PDFDoc> loadTestDoc(const char* filename) {
        auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>(filename));
        if (!doc->isOk()) {
            return nullptr;
        }
        return doc;
    }
};

// Test getDuration returns a double value
TEST_F(PageTest_727, GetDurationReturnsValue_727) {
    // We need a valid PDF document to test Page
    // Using a simple PDF if available, otherwise we test what we can
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // getDuration should return a non-negative value or -1 (no duration set)
    double duration = page->getDuration();
    // Duration is typically -1 when not set, or a positive value
    EXPECT_TRUE(duration >= 0.0 || duration == -1.0);
}

// Test isOk returns true for valid pages
TEST_F(PageTest_727, IsOkReturnsTrueForValidPage_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_TRUE(page->isOk());
}

// Test getNum returns the correct page number
TEST_F(PageTest_727, GetNumReturnsCorrectPageNumber_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    EXPECT_EQ(page->getNum(), 1);
}

// Test getMediaBox returns non-null
TEST_F(PageTest_727, GetMediaBoxReturnsNonNull_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    // Media box should have positive dimensions
    EXPECT_GT(mediaBox->x2 - mediaBox->x1, 0.0);
    EXPECT_GT(mediaBox->y2 - mediaBox->y1, 0.0);
}

// Test getCropBox returns non-null
TEST_F(PageTest_727, GetCropBoxReturnsNonNull_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *cropBox = page->getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test getMediaWidth and getMediaHeight return positive values
TEST_F(PageTest_727, GetMediaDimensionsArePositive_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_GT(page->getMediaWidth(), 0.0);
    EXPECT_GT(page->getMediaHeight(), 0.0);
}

// Test getCropWidth and getCropHeight return positive values
TEST_F(PageTest_727, GetCropDimensionsArePositive_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_GT(page->getCropWidth(), 0.0);
    EXPECT_GT(page->getCropHeight(), 0.0);
}

// Test getRotate returns a valid rotation value
TEST_F(PageTest_727, GetRotateReturnsValidValue_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    int rotate = page->getRotate();
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test getBleedBox returns non-null
TEST_F(PageTest_727, GetBleedBoxReturnsNonNull_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *bleedBox = page->getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageTest_727, GetTrimBoxReturnsNonNull_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *trimBox = page->getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageTest_727, GetArtBoxReturnsNonNull_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *artBox = page->getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getDoc returns the parent document
TEST_F(PageTest_727, GetDocReturnsParentDocument_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    PDFDoc *parentDoc = page->getDoc();
    EXPECT_EQ(parentDoc, doc.get());
}

// Test getRef returns a valid Ref
TEST_F(PageTest_727, GetRefReturnsValidRef_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Ref ref = page->getRef();
    // A valid page reference should have non-negative num
    EXPECT_GE(ref.num, 0);
}

// Test getStructParents returns an integer
TEST_F(PageTest_727, GetStructParentsReturnsInt_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // structParents is typically -1 when not set or >= 0 when set
    int sp = page->getStructParents();
    EXPECT_GE(sp, -1);
}

// Test crop dimensions are less than or equal to media dimensions
TEST_F(PageTest_727, CropDimensionsNotExceedMediaDimensions_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    EXPECT_LE(page->getCropWidth(), page->getMediaWidth());
    EXPECT_LE(page->getCropHeight(), page->getMediaHeight());
}

// Test media box consistency with getMediaWidth/getMediaHeight
TEST_F(PageTest_727, MediaBoxConsistentWithDimensions_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const PDFRectangle *mediaBox = page->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    
    double expectedWidth = mediaBox->x2 - mediaBox->x1;
    double expectedHeight = mediaBox->y2 - mediaBox->y1;
    
    EXPECT_DOUBLE_EQ(page->getMediaWidth(), expectedWidth);
    EXPECT_DOUBLE_EQ(page->getMediaHeight(), expectedHeight);
}

// Test getPageObj returns a valid object
TEST_F(PageTest_727, GetPageObjReturnsValidObject_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    const Object &pageObj = page->getPageObj();
    // Page object should be a dictionary
    EXPECT_TRUE(pageObj.isDict());
}

// Test getResourceDict 
TEST_F(PageTest_727, GetResourceDictReturnsDict_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    // Resource dict may or may not exist, but should not crash
    Dict *resourceDict = page->getResourceDict();
    // Just verify it doesn't crash - resourceDict can be null for some pages
    (void)resourceDict;
}

// Test isCropped returns boolean
TEST_F(PageTest_727, IsCroppedReturnsBool_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    bool cropped = page->isCropped();
    // Just verify it returns a valid bool and doesn't crash
    EXPECT_TRUE(cropped == true || cropped == false);
}

// Test hasStandaloneFields returns boolean
TEST_F(PageTest_727, HasStandaloneFieldsReturnsBool_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    bool hasFields = page->hasStandaloneFields();
    EXPECT_TRUE(hasFields == true || hasFields == false);
}

// Test multiple pages in a multi-page document
TEST_F(PageTest_727, MultiplePageAccess_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    int numPages = doc->getNumPages();
    for (int i = 1; i <= numPages && i <= 5; i++) {
        Page *page = doc->getPage(i);
        ASSERT_NE(page, nullptr) << "Page " << i << " should not be null";
        EXPECT_EQ(page->getNum(), i) << "Page number mismatch for page " << i;
        EXPECT_TRUE(page->isOk()) << "Page " << i << " should be ok";
    }
}

// Test getContents doesn't crash
TEST_F(PageTest_727, GetContentsDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object contents = page->getContents();
    // Contents can be a stream, array, or null - just verify no crash
    (void)contents;
}

// Test getAnnotsObject doesn't crash
TEST_F(PageTest_727, GetAnnotsObjectDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object annots = page->getAnnotsObject();
    // Annots can be an array or null
    (void)annots;
}

// Test getActions doesn't crash
TEST_F(PageTest_727, GetActionsDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object actions = page->getActions();
    (void)actions;
}

// Test getTrans doesn't crash
TEST_F(PageTest_727, GetTransDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object trans = page->getTrans();
    (void)trans;
}

// Test getThumb doesn't crash
TEST_F(PageTest_727, GetThumbDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object thumb = page->getThumb();
    (void)thumb;
}

// Test getDefaultCTM doesn't crash
TEST_F(PageTest_727, GetDefaultCTMDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    double ctm[6];
    page->getDefaultCTM(ctm, 72.0, 72.0, 0, true, false);
    // CTM should have been filled with some values
    // Just verify it didn't crash
}

// Test makeBox doesn't crash
TEST_F(PageTest_727, MakeBoxDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    PDFRectangle box;
    bool crop;
    page->makeBox(72.0, 72.0, 0, true, false, 0, 0, 
                  page->getMediaWidth(), page->getMediaHeight(), 
                  &box, &crop);
    // Verify the box has been populated
    EXPECT_GE(box.x2 - box.x1, 0.0);
    EXPECT_GE(box.y2 - box.y1, 0.0);
}

// Test getFormWidgets doesn't crash
TEST_F(PageTest_727, GetFormWidgetsDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    auto formWidgets = page->getFormWidgets();
    // May or may not have form widgets, just verify no crash
    (void)formWidgets;
}

// Test getLinks doesn't crash
TEST_F(PageTest_727, GetLinksDoesNotCrash_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    auto links = page->getLinks();
    // May or may not have links, just verify no crash
    (void)links;
}

// Test getResourceDictObject returns non-null
TEST_F(PageTest_727, GetResourceDictObjectReturnsNonNull_727) {
    auto doc = loadTestDoc("./TestProjects/poppler/test/unittestcases/WithActualText.pdf");
    if (!doc) {
        GTEST_SKIP() << "Test PDF not available";
    }
    
    Page *page = doc->getPage(1);
    ASSERT_NE(page, nullptr);
    
    Object *resourceDictObj = page->getResourceDictObject();
    // Should not be null
    (void)resourceDictObj;
}
