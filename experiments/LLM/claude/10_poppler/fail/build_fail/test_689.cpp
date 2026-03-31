#include <gtest/gtest.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <cstring>

class PageAttrsTest_689 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getTrimBox returns a non-null pointer
TEST_F(PageAttrsTest_689, GetTrimBoxReturnsNonNull_689) {
    // We need a PDFDoc to get a valid Page with PageAttrs
    // Create a minimal test by loading a simple PDF if available
    // Since we can't easily construct PageAttrs without a Dict,
    // we test through PDFDoc if possible
    
    // For a basic test, we can construct PageAttrs with nullptr attrs and nullptr dict
    // This tests default/fallback behavior
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test that getMediaBox returns a non-null pointer
TEST_F(PageAttrsTest_689, GetMediaBoxReturnsNonNull_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test that getCropBox returns a non-null pointer
TEST_F(PageAttrsTest_689, GetCropBoxReturnsNonNull_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test that getBleedBox returns a non-null pointer
TEST_F(PageAttrsTest_689, GetBleedBoxReturnsNonNull_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test that getArtBox returns a non-null pointer
TEST_F(PageAttrsTest_689, GetArtBoxReturnsNonNull_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test that isCropped returns a valid boolean when constructed with no dict
TEST_F(PageAttrsTest_689, IsCroppedDefaultBehavior_689) {
    PageAttrs attrs(nullptr, nullptr);
    bool cropped = attrs.isCropped();
    // With no dict, there should be no crop box set
    EXPECT_FALSE(cropped);
}

// Test that getTrimBox returns consistent pointer on multiple calls
TEST_F(PageAttrsTest_689, GetTrimBoxConsistentPointer_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox1 = attrs.getTrimBox();
    const PDFRectangle *trimBox2 = attrs.getTrimBox();
    EXPECT_EQ(trimBox1, trimBox2);
}

// Test that getMediaBox returns consistent pointer on multiple calls
TEST_F(PageAttrsTest_689, GetMediaBoxConsistentPointer_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox1 = attrs.getMediaBox();
    const PDFRectangle *mediaBox2 = attrs.getMediaBox();
    EXPECT_EQ(mediaBox1, mediaBox2);
}

// Test that getResourceDict returns nullptr when no resources are set
TEST_F(PageAttrsTest_689, GetResourceDictNullWhenNoResources_689) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *resourceDict = attrs.getResourceDict();
    // With no dict provided, resources should be null/empty
    EXPECT_EQ(resourceDict, nullptr);
}

// Test that getLastModified returns nullptr when not set
TEST_F(PageAttrsTest_689, GetLastModifiedNullWhenNotSet_689) {
    PageAttrs attrs(nullptr, nullptr);
    const GooString *lastModified = attrs.getLastModified();
    EXPECT_EQ(lastModified, nullptr);
}

// Test that getBoxColorInfo returns nullptr when not set
TEST_F(PageAttrsTest_689, GetBoxColorInfoNullWhenNotSet_689) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *boxColorInfo = attrs.getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, nullptr);
}

// Test that getGroup returns nullptr when not set
TEST_F(PageAttrsTest_689, GetGroupNullWhenNotSet_689) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *group = attrs.getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test that getPieceInfo returns nullptr when not set
TEST_F(PageAttrsTest_689, GetPieceInfoNullWhenNotSet_689) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *pieceInfo = attrs.getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test that getSeparationInfo returns nullptr when not set
TEST_F(PageAttrsTest_689, GetSeparationInfoNullWhenNotSet_689) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *separationInfo = attrs.getSeparationInfo();
    EXPECT_EQ(separationInfo, nullptr);
}

// Test that getResourceDictObject returns a non-null pointer
TEST_F(PageAttrsTest_689, GetResourceDictObjectReturnsNonNull_689) {
    PageAttrs attrs(nullptr, nullptr);
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}

// Test that trimBox coordinates are valid (finite numbers)
TEST_F(PageAttrsTest_689, TrimBoxHasValidCoordinates_689) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
    // The coordinates should be finite numbers
    EXPECT_FALSE(std::isnan(trimBox->x1));
    EXPECT_FALSE(std::isnan(trimBox->y1));
    EXPECT_FALSE(std::isnan(trimBox->x2));
    EXPECT_FALSE(std::isnan(trimBox->y2));
}

// Test constructing PageAttrs with parent attrs (inheritance)
TEST_F(PageAttrsTest_689, InheritFromParentAttrs_689) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    const PDFRectangle *parentMedia = parentAttrs.getMediaBox();
    const PDFRectangle *childMedia = childAttrs.getMediaBox();
    
    ASSERT_NE(parentMedia, nullptr);
    ASSERT_NE(childMedia, nullptr);
    
    // Child should inherit parent's media box when no dict overrides it
    EXPECT_DOUBLE_EQ(parentMedia->x1, childMedia->x1);
    EXPECT_DOUBLE_EQ(parentMedia->y1, childMedia->y1);
    EXPECT_DOUBLE_EQ(parentMedia->x2, childMedia->x2);
    EXPECT_DOUBLE_EQ(parentMedia->y2, childMedia->y2);
}

// Test that child inherits parent's trimBox
TEST_F(PageAttrsTest_689, InheritTrimBoxFromParent_689) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    const PDFRectangle *parentTrim = parentAttrs.getTrimBox();
    const PDFRectangle *childTrim = childAttrs.getTrimBox();
    
    ASSERT_NE(parentTrim, nullptr);
    ASSERT_NE(childTrim, nullptr);
    
    EXPECT_DOUBLE_EQ(parentTrim->x1, childTrim->x1);
    EXPECT_DOUBLE_EQ(parentTrim->y1, childTrim->y1);
    EXPECT_DOUBLE_EQ(parentTrim->x2, childTrim->x2);
    EXPECT_DOUBLE_EQ(parentTrim->y2, childTrim->y2);
}

// Test getRotate default value
TEST_F(PageAttrsTest_689, GetRotateDefaultValue_689) {
    PageAttrs attrs(nullptr, nullptr);
    int rotate = attrs.getRotate();
    // Valid rotation values are 0, 90, 180, 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test that clipBoxes doesn't crash
TEST_F(PageAttrsTest_689, ClipBoxesDoesNotCrash_689) {
    PageAttrs attrs(nullptr, nullptr);
    EXPECT_NO_FATAL_FAILURE(attrs.clipBoxes());
}

// Test that after clipBoxes, all boxes are still valid
TEST_F(PageAttrsTest_689, ClipBoxesKeepsValidBoxes_689) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();
    
    EXPECT_NE(attrs.getMediaBox(), nullptr);
    EXPECT_NE(attrs.getCropBox(), nullptr);
    EXPECT_NE(attrs.getBleedBox(), nullptr);
    EXPECT_NE(attrs.getTrimBox(), nullptr);
    EXPECT_NE(attrs.getArtBox(), nullptr);
}

// Test replaceResource does not crash with a null-like object
TEST_F(PageAttrsTest_689, ReplaceResourceWithObject_689) {
    PageAttrs attrs(nullptr, nullptr);
    Object obj;
    EXPECT_NO_FATAL_FAILURE(attrs.replaceResource(std::move(obj)));
}

// Test getMetadata returns nullptr when not set
TEST_F(PageAttrsTest_689, GetMetadataNullWhenNotSet_689) {
    PageAttrs attrs(nullptr, nullptr);
    Stream *metadata = attrs.getMetadata();
    EXPECT_EQ(metadata, nullptr);
}
