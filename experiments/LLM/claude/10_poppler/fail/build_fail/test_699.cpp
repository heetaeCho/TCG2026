#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include "Object.h"
#include <memory>
#include <string>

class PageAttrsTest_699 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getResourceDictObject returns a non-null pointer
TEST_F(PageAttrsTest_699, GetResourceDictObjectReturnsNonNull_699) {
    // Create PageAttrs with nullptr parent and nullptr dict
    // This tests default construction behavior
    PageAttrs attrs(nullptr, nullptr);
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}

// Test that getResourceDictObject returns an Object (may be null type by default)
TEST_F(PageAttrsTest_699, GetResourceDictObjectDefaultIsNullType_699) {
    PageAttrs attrs(nullptr, nullptr);
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    // With no dict provided, the resources object should be null/none type
    EXPECT_TRUE(resObj->isNull() || resObj->isNone() || resObj->isDict());
}

// Test getMediaBox returns non-null
TEST_F(PageAttrsTest_699, GetMediaBoxReturnsNonNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test getCropBox returns non-null
TEST_F(PageAttrsTest_699, GetCropBoxReturnsNonNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test isCropped with default construction (no dict)
TEST_F(PageAttrsTest_699, IsCroppedDefaultIsFalse_699) {
    PageAttrs attrs(nullptr, nullptr);
    // Without explicit crop box, isCropped should be false
    EXPECT_FALSE(attrs.isCropped());
}

// Test getBleedBox returns non-null
TEST_F(PageAttrsTest_699, GetBleedBoxReturnsNonNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageAttrsTest_699, GetTrimBoxReturnsNonNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageAttrsTest_699, GetArtBoxReturnsNonNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test getRotate default value
TEST_F(PageAttrsTest_699, GetRotateDefaultIsZero_699) {
    PageAttrs attrs(nullptr, nullptr);
    int rotate = attrs.getRotate();
    // Default rotation should be 0
    EXPECT_EQ(rotate, 0);
}

// Test getLastModified with default (no dict)
TEST_F(PageAttrsTest_699, GetLastModifiedDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    const GooString *lastMod = attrs.getLastModified();
    // With no dict, lastModified should be nullptr
    EXPECT_EQ(lastMod, nullptr);
}

// Test replaceResource changes the resource dict object
TEST_F(PageAttrsTest_699, ReplaceResourceChangesResourceDictObject_699) {
    PageAttrs attrs(nullptr, nullptr);
    
    // Get initial state
    Object *initialRes = attrs.getResourceDictObject();
    ObjType initialType = initialRes->getType();
    
    // Replace with a new integer object
    Object newObj(42);
    attrs.replaceResource(std::move(newObj));
    
    Object *replacedRes = attrs.getResourceDictObject();
    ASSERT_NE(replacedRes, nullptr);
    EXPECT_TRUE(replacedRes->isInt());
    EXPECT_EQ(replacedRes->getInt(), 42);
}

// Test that replaceResource can be called multiple times
TEST_F(PageAttrsTest_699, ReplaceResourceMultipleTimes_699) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object obj1(10);
    attrs.replaceResource(std::move(obj1));
    Object *res1 = attrs.getResourceDictObject();
    ASSERT_NE(res1, nullptr);
    EXPECT_TRUE(res1->isInt());
    EXPECT_EQ(res1->getInt(), 10);
    
    Object obj2(20);
    attrs.replaceResource(std::move(obj2));
    Object *res2 = attrs.getResourceDictObject();
    ASSERT_NE(res2, nullptr);
    EXPECT_TRUE(res2->isInt());
    EXPECT_EQ(res2->getInt(), 20);
}

// Test clipBoxes doesn't crash with default construction
TEST_F(PageAttrsTest_699, ClipBoxesDoesNotCrashDefault_699) {
    PageAttrs attrs(nullptr, nullptr);
    EXPECT_NO_THROW(attrs.clipBoxes());
}

// Test that after clipBoxes, crop box is within media box
TEST_F(PageAttrsTest_699, ClipBoxesCropWithinMedia_699) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    
    ASSERT_NE(mediaBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    
    // After clipping, crop box coordinates should be within or equal to media box
    EXPECT_GE(cropBox->x1, mediaBox->x1);
    EXPECT_GE(cropBox->y1, mediaBox->y1);
    EXPECT_LE(cropBox->x2, mediaBox->x2);
    EXPECT_LE(cropBox->y2, mediaBox->y2);
}

// Test getBoxColorInfo with default construction
TEST_F(PageAttrsTest_699, GetBoxColorInfoDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *boxColorInfo = attrs.getBoxColorInfo();
    // With no dict provided, should be nullptr
    EXPECT_EQ(boxColorInfo, nullptr);
}

// Test getGroup with default construction
TEST_F(PageAttrsTest_699, GetGroupDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *group = attrs.getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test getPieceInfo with default construction
TEST_F(PageAttrsTest_699, GetPieceInfoDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *pieceInfo = attrs.getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test getSeparationInfo with default construction
TEST_F(PageAttrsTest_699, GetSeparationInfoDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *sepInfo = attrs.getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getResourceDict with default construction
TEST_F(PageAttrsTest_699, GetResourceDictDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *resDict = attrs.getResourceDict();
    // With no resources set, may be nullptr
    EXPECT_EQ(resDict, nullptr);
}

// Test constructing PageAttrs with a parent PageAttrs
TEST_F(PageAttrsTest_699, ConstructWithParentAttrs_699) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    // Child should inherit parent's media box
    const PDFRectangle *parentMedia = parentAttrs.getMediaBox();
    const PDFRectangle *childMedia = childAttrs.getMediaBox();
    
    ASSERT_NE(parentMedia, nullptr);
    ASSERT_NE(childMedia, nullptr);
    
    EXPECT_DOUBLE_EQ(childMedia->x1, parentMedia->x1);
    EXPECT_DOUBLE_EQ(childMedia->y1, parentMedia->y1);
    EXPECT_DOUBLE_EQ(childMedia->x2, parentMedia->x2);
    EXPECT_DOUBLE_EQ(childMedia->y2, parentMedia->y2);
}

// Test that getResourceDictObject returns the same pointer on multiple calls
TEST_F(PageAttrsTest_699, GetResourceDictObjectConsistentPointer_699) {
    PageAttrs attrs(nullptr, nullptr);
    Object *res1 = attrs.getResourceDictObject();
    Object *res2 = attrs.getResourceDictObject();
    EXPECT_EQ(res1, res2);
}

// Test media box default dimensions
TEST_F(PageAttrsTest_699, MediaBoxDefaultDimensions_699) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    // Default media box should have some reasonable values (typically letter size or similar)
    // At minimum, x2 should be >= x1 and y2 should be >= y1
    EXPECT_LE(mediaBox->x1, mediaBox->x2);
    EXPECT_LE(mediaBox->y1, mediaBox->y2);
}

// Integration test: loading from a real PDF file if available
class PageAttrsFromPDFTest_699 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getMetadata with default construction doesn't crash
TEST_F(PageAttrsTest_699, GetMetadataDefaultIsNull_699) {
    PageAttrs attrs(nullptr, nullptr);
    Stream *metadata = attrs.getMetadata();
    EXPECT_EQ(metadata, nullptr);
}
