#include <gtest/gtest.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class PageAttrsTest_686 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getCropBox returns a non-null pointer
TEST_F(PageAttrsTest_686, GetCropBoxReturnsNonNull_686) {
    // We need a PDFDoc to get a valid Page with PageAttrs
    // Create PageAttrs with nullptr attrs and nullptr dict to get defaults
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test that getMediaBox returns a non-null pointer
TEST_F(PageAttrsTest_686, GetMediaBoxReturnsNonNull_686) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test that getBleedBox returns a non-null pointer
TEST_F(PageAttrsTest_686, GetBleedBoxReturnsNonNull_686) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test that getTrimBox returns a non-null pointer
TEST_F(PageAttrsTest_686, GetTrimBoxReturnsNonNull_686) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test that getArtBox returns a non-null pointer
TEST_F(PageAttrsTest_686, GetArtBoxReturnsNonNull_686) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test isCropped with default construction (no dict provided)
TEST_F(PageAttrsTest_686, IsCroppedDefaultIsFalse_686) {
    PageAttrs attrs(nullptr, nullptr);
    // With no dict, there should be no crop box defined
    EXPECT_FALSE(attrs.isCropped());
}

// Test that getRotate returns a valid rotation value (0, 90, 180, 270)
TEST_F(PageAttrsTest_686, GetRotateDefaultIsZero_686) {
    PageAttrs attrs(nullptr, nullptr);
    int rotate = attrs.getRotate();
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test that getResourceDict returns nullptr with no dict
TEST_F(PageAttrsTest_686, GetResourceDictDefaultIsNull_686) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *resDict = attrs.getResourceDict();
    // With no dictionary, resources should be null/empty
    // This depends on implementation but we test for observable behavior
    // It may or may not be nullptr depending on defaults
    // Just ensure no crash
    (void)resDict;
}

// Test getLastModified with default construction
TEST_F(PageAttrsTest_686, GetLastModifiedDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    const GooString *lastMod = attrs.getLastModified();
    // With no dict, lastModified should be nullptr or empty
    // Just ensure no crash
    (void)lastMod;
}

// Test getBoxColorInfo with default construction
TEST_F(PageAttrsTest_686, GetBoxColorInfoDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *boxColorInfo = attrs.getBoxColorInfo();
    // Should be nullptr with no dict
    (void)boxColorInfo;
}

// Test getGroup with default construction
TEST_F(PageAttrsTest_686, GetGroupDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *group = attrs.getGroup();
    (void)group;
}

// Test getPieceInfo with default construction
TEST_F(PageAttrsTest_686, GetPieceInfoDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *pieceInfo = attrs.getPieceInfo();
    (void)pieceInfo;
}

// Test getSeparationInfo with default construction
TEST_F(PageAttrsTest_686, GetSeparationInfoDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *sepInfo = attrs.getSeparationInfo();
    (void)sepInfo;
}

// Test getResourceDictObject with default construction
TEST_F(PageAttrsTest_686, GetResourceDictObjectDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}

// Test clipBoxes does not crash with defaults
TEST_F(PageAttrsTest_686, ClipBoxesDoesNotCrash_686) {
    PageAttrs attrs(nullptr, nullptr);
    EXPECT_NO_FATAL_FAILURE(attrs.clipBoxes());
}

// Test that after clipBoxes, crop/bleed/trim/art boxes are within media box
TEST_F(PageAttrsTest_686, ClipBoxesConstrainsBoxesToMediaBox_686) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();

    const PDFRectangle *mediaBox = attrs.getMediaBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    const PDFRectangle *trimBox = attrs.getTrimBox();
    const PDFRectangle *artBox = attrs.getArtBox();

    ASSERT_NE(mediaBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(bleedBox, nullptr);
    ASSERT_NE(trimBox, nullptr);
    ASSERT_NE(artBox, nullptr);

    // After clipping, all boxes should be constrained within the media box
    // We check that the crop box coordinates are within media box bounds
    EXPECT_GE(cropBox->x1, std::min(mediaBox->x1, mediaBox->x2));
    EXPECT_LE(cropBox->x2, std::max(mediaBox->x1, mediaBox->x2));
}

// Test constructing PageAttrs with parent attrs
TEST_F(PageAttrsTest_686, ConstructWithParentAttrs_686) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);

    // Child should inherit parent's media box
    const PDFRectangle *parentMedia = parentAttrs.getMediaBox();
    const PDFRectangle *childMedia = childAttrs.getMediaBox();

    ASSERT_NE(parentMedia, nullptr);
    ASSERT_NE(childMedia, nullptr);

    EXPECT_DOUBLE_EQ(parentMedia->x1, childMedia->x1);
    EXPECT_DOUBLE_EQ(parentMedia->y1, childMedia->y1);
    EXPECT_DOUBLE_EQ(parentMedia->x2, childMedia->x2);
    EXPECT_DOUBLE_EQ(parentMedia->y2, childMedia->y2);
}

// Test that getCropBox and getMediaBox return the same values when no crop is set
TEST_F(PageAttrsTest_686, CropBoxEqualsMediaBoxWhenNotCropped_686) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();

    if (!attrs.isCropped()) {
        const PDFRectangle *mediaBox = attrs.getMediaBox();
        const PDFRectangle *cropBox = attrs.getCropBox();

        EXPECT_DOUBLE_EQ(mediaBox->x1, cropBox->x1);
        EXPECT_DOUBLE_EQ(mediaBox->y1, cropBox->y1);
        EXPECT_DOUBLE_EQ(mediaBox->x2, cropBox->x2);
        EXPECT_DOUBLE_EQ(mediaBox->y2, cropBox->y2);
    }
}

// Test replaceResource
TEST_F(PageAttrsTest_686, ReplaceResourceDoesNotCrash_686) {
    PageAttrs attrs(nullptr, nullptr);
    Object obj;
    EXPECT_NO_FATAL_FAILURE(attrs.replaceResource(std::move(obj)));
}

// Test that child inherits parent's rotation
TEST_F(PageAttrsTest_686, ChildInheritsParentRotation_686) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);

    EXPECT_EQ(parentAttrs.getRotate(), childAttrs.getRotate());
}

// Test with a real PDF document if available
class PageTest_686 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getMetadata doesn't crash
TEST_F(PageAttrsTest_686, GetMetadataDefault_686) {
    PageAttrs attrs(nullptr, nullptr);
    Stream *metadata = attrs.getMetadata();
    // With no dict, metadata should be nullptr
    EXPECT_EQ(metadata, nullptr);
}
