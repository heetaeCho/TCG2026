#include <gtest/gtest.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class PageAttrsTest_691 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test getRotate returns a valid rotation value
TEST_F(PageAttrsTest_691, GetRotateReturnsValidValue_691) {
    // Construct PageAttrs with nullptr parent and nullptr dict
    // This tests the default behavior
    PageAttrs attrs(nullptr, nullptr);
    int rotate = attrs.getRotate();
    // Rotation should be one of 0, 90, 180, 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test getMediaBox returns non-null
TEST_F(PageAttrsTest_691, GetMediaBoxReturnsNonNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test getCropBox returns non-null
TEST_F(PageAttrsTest_691, GetCropBoxReturnsNonNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test isCropped returns a boolean value
TEST_F(PageAttrsTest_691, IsCroppedReturnsBool_691) {
    PageAttrs attrs(nullptr, nullptr);
    bool cropped = attrs.isCropped();
    // With no dict, should default to not cropped
    EXPECT_FALSE(cropped);
}

// Test getBleedBox returns non-null
TEST_F(PageAttrsTest_691, GetBleedBoxReturnsNonNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageAttrsTest_691, GetTrimBoxReturnsNonNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageAttrsTest_691, GetArtBoxReturnsNonNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test default rotation is 0
TEST_F(PageAttrsTest_691, DefaultRotateIsZero_691) {
    PageAttrs attrs(nullptr, nullptr);
    EXPECT_EQ(attrs.getRotate(), 0);
}

// Test getLastModified returns nullptr when no dict
TEST_F(PageAttrsTest_691, GetLastModifiedDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    const GooString *lastMod = attrs.getLastModified();
    // With no dict provided, lastModified should be null/empty
    EXPECT_EQ(lastMod, nullptr);
}

// Test getResourceDict returns nullptr when no resources
TEST_F(PageAttrsTest_691, GetResourceDictDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *resourceDict = attrs.getResourceDict();
    EXPECT_EQ(resourceDict, nullptr);
}

// Test getBoxColorInfo returns nullptr when no dict
TEST_F(PageAttrsTest_691, GetBoxColorInfoDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *boxColorInfo = attrs.getBoxColorInfo();
    EXPECT_EQ(boxColorInfo, nullptr);
}

// Test getGroup returns nullptr when no dict
TEST_F(PageAttrsTest_691, GetGroupDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *group = attrs.getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test getPieceInfo returns nullptr when no dict
TEST_F(PageAttrsTest_691, GetPieceInfoDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *pieceInfo = attrs.getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test getSeparationInfo returns nullptr when no dict
TEST_F(PageAttrsTest_691, GetSeparationInfoDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *separationInfo = attrs.getSeparationInfo();
    EXPECT_EQ(separationInfo, nullptr);
}

// Test that cropBox defaults to mediaBox when not cropped
TEST_F(PageAttrsTest_691, CropBoxDefaultsToMediaBox_691) {
    PageAttrs attrs(nullptr, nullptr);
    if (!attrs.isCropped()) {
        const PDFRectangle *mediaBox = attrs.getMediaBox();
        const PDFRectangle *cropBox = attrs.getCropBox();
        EXPECT_DOUBLE_EQ(mediaBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(mediaBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(mediaBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(mediaBox->y2, cropBox->y2);
    }
}

// Test clipBoxes doesn't crash
TEST_F(PageAttrsTest_691, ClipBoxesDoesNotCrash_691) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();
    // After clipping, boxes should still be valid
    ASSERT_NE(attrs.getMediaBox(), nullptr);
    ASSERT_NE(attrs.getCropBox(), nullptr);
    ASSERT_NE(attrs.getBleedBox(), nullptr);
    ASSERT_NE(attrs.getTrimBox(), nullptr);
    ASSERT_NE(attrs.getArtBox(), nullptr);
}

// Test that bleedBox, trimBox, artBox are within cropBox after clipBoxes
TEST_F(PageAttrsTest_691, ClipBoxesConstrainsBoxes_691) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    const PDFRectangle *trimBox = attrs.getTrimBox();
    const PDFRectangle *artBox = attrs.getArtBox();
    
    // After clipping, subsidiary boxes should be within crop box bounds
    EXPECT_GE(bleedBox->x1, cropBox->x1);
    EXPECT_GE(bleedBox->y1, cropBox->y1);
    EXPECT_LE(bleedBox->x2, cropBox->x2);
    EXPECT_LE(bleedBox->y2, cropBox->y2);
    
    EXPECT_GE(trimBox->x1, cropBox->x1);
    EXPECT_GE(trimBox->y1, cropBox->y1);
    EXPECT_LE(trimBox->x2, cropBox->x2);
    EXPECT_LE(trimBox->y2, cropBox->y2);
    
    EXPECT_GE(artBox->x1, cropBox->x1);
    EXPECT_GE(artBox->y1, cropBox->y1);
    EXPECT_LE(artBox->x2, cropBox->x2);
    EXPECT_LE(artBox->y2, cropBox->y2);
}

// Test inheriting from parent PageAttrs
TEST_F(PageAttrsTest_691, InheritFromParentAttrs_691) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    // Child should inherit parent's rotation
    EXPECT_EQ(childAttrs.getRotate(), parentAttrs.getRotate());
    
    // Child should inherit parent's mediaBox
    const PDFRectangle *parentMedia = parentAttrs.getMediaBox();
    const PDFRectangle *childMedia = childAttrs.getMediaBox();
    EXPECT_DOUBLE_EQ(parentMedia->x1, childMedia->x1);
    EXPECT_DOUBLE_EQ(parentMedia->y1, childMedia->y1);
    EXPECT_DOUBLE_EQ(parentMedia->x2, childMedia->x2);
    EXPECT_DOUBLE_EQ(parentMedia->y2, childMedia->y2);
}

// Test getResourceDictObject returns a valid Object
TEST_F(PageAttrsTest_691, GetResourceDictObjectNotNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Object *obj = attrs.getResourceDictObject();
    ASSERT_NE(obj, nullptr);
}

// Test replaceResource doesn't crash
TEST_F(PageAttrsTest_691, ReplaceResourceDoesNotCrash_691) {
    PageAttrs attrs(nullptr, nullptr);
    Object obj;
    attrs.replaceResource(std::move(obj));
    // Should not crash; resource dict may now be different
}

// Test getMetadata returns nullptr when no metadata stream
TEST_F(PageAttrsTest_691, GetMetadataDefaultIsNull_691) {
    PageAttrs attrs(nullptr, nullptr);
    Stream *metadata = attrs.getMetadata();
    EXPECT_EQ(metadata, nullptr);
}
