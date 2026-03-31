#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

class PageAttrsTest_687 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test isCropped returns false when no crop box is explicitly set
// We construct PageAttrs with nullptr attrs and an empty dict
TEST_F(PageAttrsTest_687, IsCroppedReturnsFalseWhenNoCropBox_687) {
    // Create a minimal PDF document to get a valid Dict
    // We'll use a Dict with just a MediaBox but no CropBox
    XRef xref(nullptr);
    Dict dict(&xref);
    
    // MediaBox is required
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    EXPECT_FALSE(attrs.isCropped());
}

// Test isCropped returns true when a CropBox is explicitly set
TEST_F(PageAttrsTest_687, IsCroppedReturnsTrueWhenCropBoxSet_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    // MediaBox
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    // CropBox
    Object cropBoxArray = Object(new Array(&xref));
    cropBoxArray.arrayAdd(Object(10.0));
    cropBoxArray.arrayAdd(Object(10.0));
    cropBoxArray.arrayAdd(Object(500.0));
    cropBoxArray.arrayAdd(Object(700.0));
    dict.add("CropBox", std::move(cropBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    EXPECT_TRUE(attrs.isCropped());
}

// Test getMediaBox returns valid media box dimensions
TEST_F(PageAttrsTest_687, GetMediaBoxReturnsCorrectDimensions_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test getCropBox returns media box when no crop box is set
TEST_F(PageAttrsTest_687, GetCropBoxReturnsMediaBoxWhenNotCropped_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(mediaBox, nullptr);
    // When no crop box, crop box should equal media box
    EXPECT_DOUBLE_EQ(cropBox->x1, mediaBox->x1);
    EXPECT_DOUBLE_EQ(cropBox->y1, mediaBox->y1);
    EXPECT_DOUBLE_EQ(cropBox->x2, mediaBox->x2);
    EXPECT_DOUBLE_EQ(cropBox->y2, mediaBox->y2);
}

// Test getCropBox returns the specified crop box when set
TEST_F(PageAttrsTest_687, GetCropBoxReturnsSpecifiedCropBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    Object cropBoxArray = Object(new Array(&xref));
    cropBoxArray.arrayAdd(Object(10.0));
    cropBoxArray.arrayAdd(Object(10.0));
    cropBoxArray.arrayAdd(Object(500.0));
    cropBoxArray.arrayAdd(Object(700.0));
    dict.add("CropBox", std::move(cropBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
    EXPECT_DOUBLE_EQ(cropBox->x1, 10.0);
    EXPECT_DOUBLE_EQ(cropBox->y1, 10.0);
    EXPECT_DOUBLE_EQ(cropBox->x2, 500.0);
    EXPECT_DOUBLE_EQ(cropBox->y2, 700.0);
}

// Test that bleed/trim/art boxes are clipped to crop box
TEST_F(PageAttrsTest_687, ClipBoxesClipsToCropBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    Object cropBoxArray = Object(new Array(&xref));
    cropBoxArray.arrayAdd(Object(50.0));
    cropBoxArray.arrayAdd(Object(50.0));
    cropBoxArray.arrayAdd(Object(562.0));
    cropBoxArray.arrayAdd(Object(742.0));
    dict.add("CropBox", std::move(cropBoxArray));
    
    // BleedBox larger than CropBox - should be clipped
    Object bleedBoxArray = Object(new Array(&xref));
    bleedBoxArray.arrayAdd(Object(0.0));
    bleedBoxArray.arrayAdd(Object(0.0));
    bleedBoxArray.arrayAdd(Object(612.0));
    bleedBoxArray.arrayAdd(Object(792.0));
    dict.add("BleedBox", std::move(bleedBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(bleedBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    
    // After clipBoxes (called in constructor), bleed box should be within crop box
    EXPECT_GE(bleedBox->x1, cropBox->x1);
    EXPECT_GE(bleedBox->y1, cropBox->y1);
    EXPECT_LE(bleedBox->x2, cropBox->x2);
    EXPECT_LE(bleedBox->y2, cropBox->y2);
}

// Test getBleedBox with no explicit bleed box
TEST_F(PageAttrsTest_687, GetBleedBoxDefaultsToCropBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(bleedBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    EXPECT_DOUBLE_EQ(bleedBox->x1, cropBox->x1);
    EXPECT_DOUBLE_EQ(bleedBox->y1, cropBox->y1);
    EXPECT_DOUBLE_EQ(bleedBox->x2, cropBox->x2);
    EXPECT_DOUBLE_EQ(bleedBox->y2, cropBox->y2);
}

// Test getTrimBox with no explicit trim box
TEST_F(PageAttrsTest_687, GetTrimBoxDefaultsToCropBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(trimBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    EXPECT_DOUBLE_EQ(trimBox->x1, cropBox->x1);
    EXPECT_DOUBLE_EQ(trimBox->y1, cropBox->y1);
    EXPECT_DOUBLE_EQ(trimBox->x2, cropBox->x2);
    EXPECT_DOUBLE_EQ(trimBox->y2, cropBox->y2);
}

// Test getArtBox with no explicit art box
TEST_F(PageAttrsTest_687, GetArtBoxDefaultsToCropBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(artBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    EXPECT_DOUBLE_EQ(artBox->x1, cropBox->x1);
    EXPECT_DOUBLE_EQ(artBox->y1, cropBox->y1);
    EXPECT_DOUBLE_EQ(artBox->x2, cropBox->x2);
    EXPECT_DOUBLE_EQ(artBox->y2, cropBox->y2);
}

// Test getRotate with no explicit rotation
TEST_F(PageAttrsTest_687, GetRotateDefaultsToZero_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    EXPECT_EQ(attrs.getRotate(), 0);
}

// Test getRotate with explicit rotation value
TEST_F(PageAttrsTest_687, GetRotateReturnsSpecifiedRotation_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    dict.add("Rotate", Object(90));
    
    PageAttrs attrs(nullptr, &dict);
    
    EXPECT_EQ(attrs.getRotate(), 90);
}

// Test getRotate with 180 degrees
TEST_F(PageAttrsTest_687, GetRotateReturns180_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    dict.add("Rotate", Object(180));
    
    PageAttrs attrs(nullptr, &dict);
    
    EXPECT_EQ(attrs.getRotate(), 180);
}

// Test getRotate with 270 degrees
TEST_F(PageAttrsTest_687, GetRotateReturns270_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    dict.add("Rotate", Object(270));
    
    PageAttrs attrs(nullptr, &dict);
    
    EXPECT_EQ(attrs.getRotate(), 270);
}

// Test inheritance from parent PageAttrs
TEST_F(PageAttrsTest_687, InheritsMediaBoxFromParent_687) {
    XRef xref(nullptr);
    
    // Parent dict with MediaBox
    Dict parentDict(&xref);
    Object parentMediaBox = Object(new Array(&xref));
    parentMediaBox.arrayAdd(Object(0.0));
    parentMediaBox.arrayAdd(Object(0.0));
    parentMediaBox.arrayAdd(Object(612.0));
    parentMediaBox.arrayAdd(Object(792.0));
    parentDict.add("MediaBox", std::move(parentMediaBox));
    
    PageAttrs parentAttrs(nullptr, &parentDict);
    
    // Child dict with no MediaBox - should inherit
    Dict childDict(&xref);
    PageAttrs childAttrs(&parentAttrs, &childDict);
    
    const PDFRectangle *mediaBox = childAttrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test child overrides parent's MediaBox
TEST_F(PageAttrsTest_687, ChildOverridesParentMediaBox_687) {
    XRef xref(nullptr);
    
    // Parent dict with MediaBox
    Dict parentDict(&xref);
    Object parentMediaBox = Object(new Array(&xref));
    parentMediaBox.arrayAdd(Object(0.0));
    parentMediaBox.arrayAdd(Object(0.0));
    parentMediaBox.arrayAdd(Object(612.0));
    parentMediaBox.arrayAdd(Object(792.0));
    parentDict.add("MediaBox", std::move(parentMediaBox));
    
    PageAttrs parentAttrs(nullptr, &parentDict);
    
    // Child dict with its own MediaBox
    Dict childDict(&xref);
    Object childMediaBox = Object(new Array(&xref));
    childMediaBox.arrayAdd(Object(0.0));
    childMediaBox.arrayAdd(Object(0.0));
    childMediaBox.arrayAdd(Object(300.0));
    childMediaBox.arrayAdd(Object(400.0));
    childDict.add("MediaBox", std::move(childMediaBox));
    
    PageAttrs childAttrs(&parentAttrs, &childDict);
    
    const PDFRectangle *mediaBox = childAttrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 300.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 400.0);
}

// Test getLastModified when not set
TEST_F(PageAttrsTest_687, GetLastModifiedReturnsNullWhenNotSet_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const GooString *lastMod = attrs.getLastModified();
    // When not set, should return nullptr
    EXPECT_EQ(lastMod, nullptr);
}

// Test replaceResource replaces the resource dictionary
TEST_F(PageAttrsTest_687, ReplaceResourceReplacesDict_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    // Create a new resource dict
    Dict *newResDict = new Dict(&xref);
    Object newRes(newResDict);
    
    attrs.replaceResource(std::move(newRes));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isDict());
}

// Test CropBox larger than MediaBox gets clipped
TEST_F(PageAttrsTest_687, CropBoxClippedToMediaBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(100.0));
    mediaBoxArray.arrayAdd(Object(100.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    // CropBox larger than MediaBox
    Object cropBoxArray = Object(new Array(&xref));
    cropBoxArray.arrayAdd(Object(-50.0));
    cropBoxArray.arrayAdd(Object(-50.0));
    cropBoxArray.arrayAdd(Object(200.0));
    cropBoxArray.arrayAdd(Object(200.0));
    dict.add("CropBox", std::move(cropBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(mediaBox, nullptr);
    
    // CropBox should be clipped to MediaBox
    EXPECT_GE(cropBox->x1, mediaBox->x1);
    EXPECT_GE(cropBox->y1, mediaBox->y1);
    EXPECT_LE(cropBox->x2, mediaBox->x2);
    EXPECT_LE(cropBox->y2, mediaBox->y2);
}

// Test with explicit TrimBox
TEST_F(PageAttrsTest_687, ExplicitTrimBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    Object trimBoxArray = Object(new Array(&xref));
    trimBoxArray.arrayAdd(Object(20.0));
    trimBoxArray.arrayAdd(Object(20.0));
    trimBoxArray.arrayAdd(Object(592.0));
    trimBoxArray.arrayAdd(Object(772.0));
    dict.add("TrimBox", std::move(trimBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
    EXPECT_DOUBLE_EQ(trimBox->x1, 20.0);
    EXPECT_DOUBLE_EQ(trimBox->y1, 20.0);
    EXPECT_DOUBLE_EQ(trimBox->x2, 592.0);
    EXPECT_DOUBLE_EQ(trimBox->y2, 772.0);
}

// Test with explicit ArtBox
TEST_F(PageAttrsTest_687, ExplicitArtBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    Object artBoxArray = Object(new Array(&xref));
    artBoxArray.arrayAdd(Object(30.0));
    artBoxArray.arrayAdd(Object(30.0));
    artBoxArray.arrayAdd(Object(582.0));
    artBoxArray.arrayAdd(Object(762.0));
    dict.add("ArtBox", std::move(artBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
    EXPECT_DOUBLE_EQ(artBox->x1, 30.0);
    EXPECT_DOUBLE_EQ(artBox->y1, 30.0);
    EXPECT_DOUBLE_EQ(artBox->x2, 582.0);
    EXPECT_DOUBLE_EQ(artBox->y2, 762.0);
}

// Test getResourceDict when no resources set
TEST_F(PageAttrsTest_687, GetResourceDictReturnsNullWhenNotSet_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    Dict *resDict = attrs.getResourceDict();
    // When no resources are set, should return nullptr
    EXPECT_EQ(resDict, nullptr);
}

// Test getResourceDict when resources are set
TEST_F(PageAttrsTest_687, GetResourceDictReturnsDict_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    Dict *resDict = new Dict(&xref);
    dict.add("Resources", Object(resDict));
    
    PageAttrs attrs(nullptr, &dict);
    
    Dict *retrievedResDict = attrs.getResourceDict();
    EXPECT_NE(retrievedResDict, nullptr);
}

// Test invalid rotation value (not multiple of 90) defaults to 0
TEST_F(PageAttrsTest_687, InvalidRotateDefaultsToZero_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    dict.add("Rotate", Object(45));
    
    PageAttrs attrs(nullptr, &dict);
    
    int rotate = attrs.getRotate();
    // Invalid rotation should default to 0 or be normalized
    EXPECT_EQ(rotate % 90, 0);
}

// Test zero-sized media box
TEST_F(PageAttrsTest_687, ZeroSizedMediaBox_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 0.0);
}

// Test that getResourceDictObject is not null
TEST_F(PageAttrsTest_687, GetResourceDictObjectNotNull_687) {
    XRef xref(nullptr);
    Dict dict(&xref);
    
    Object mediaBoxArray = Object(new Array(&xref));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(0.0));
    mediaBoxArray.arrayAdd(Object(612.0));
    mediaBoxArray.arrayAdd(Object(792.0));
    dict.add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, &dict);
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}
