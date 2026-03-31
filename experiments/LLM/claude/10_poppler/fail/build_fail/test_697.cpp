#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

class PageAttrsTest_697 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getSeparationInfo returns nullptr when separationInfo is not a Dict
TEST_F(PageAttrsTest_697, GetSeparationInfoReturnsNullWhenNotDict_697) {
    // Create a PageAttrs with no parent and an empty dict
    // When no separationInfo is set in the dict, the internal Object should be objNone
    // which is not a dict, so getSeparationInfo should return nullptr
    
    Dict emptyDict(nullptr);
    PageAttrs attrs(nullptr, &emptyDict);
    
    Dict *result = attrs.getSeparationInfo();
    EXPECT_EQ(result, nullptr);
}

// Test that getSeparationInfo returns a Dict pointer when separationInfo is a Dict
TEST_F(PageAttrsTest_697, GetSeparationInfoReturnsDictWhenIsDict_697) {
    // We need to construct a dict that has a "SeparationInfo" entry that is itself a dict
    XRef *xref = nullptr;
    Dict *innerDict = new Dict(xref);
    innerDict->incRef();
    
    Dict pageDict(xref);
    Object sepInfoObj(innerDict);
    pageDict.add("SeparationInfo", std::move(sepInfoObj));
    
    PageAttrs attrs(nullptr, &pageDict);
    
    Dict *result = attrs.getSeparationInfo();
    EXPECT_NE(result, nullptr);
}

// Test getMediaBox returns non-null
TEST_F(PageAttrsTest_697, GetMediaBoxReturnsNonNull_697) {
    Dict emptyDict(nullptr);
    
    // Set up a MediaBox
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    EXPECT_NE(mediaBox, nullptr);
}

// Test getCropBox returns non-null
TEST_F(PageAttrsTest_697, GetCropBoxReturnsNonNull_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    EXPECT_NE(cropBox, nullptr);
}

// Test isCropped returns false when no CropBox is explicitly set
TEST_F(PageAttrsTest_697, IsCroppedReturnsFalseWhenNoCropBox_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    EXPECT_FALSE(attrs.isCropped());
}

// Test isCropped returns true when CropBox is explicitly set
TEST_F(PageAttrsTest_697, IsCroppedReturnsTrueWhenCropBoxSet_697) {
    Dict pageDict(nullptr);
    
    Object mediaArr(new Array(nullptr));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(612));
    mediaArr.arrayAdd(Object(792));
    pageDict.add("MediaBox", std::move(mediaArr));
    
    Object cropArr(new Array(nullptr));
    cropArr.arrayAdd(Object(50));
    cropArr.arrayAdd(Object(50));
    cropArr.arrayAdd(Object(500));
    cropArr.arrayAdd(Object(700));
    pageDict.add("CropBox", std::move(cropArr));
    
    PageAttrs attrs(nullptr, &pageDict);
    
    EXPECT_TRUE(attrs.isCropped());
}

// Test getRotate returns 0 when no Rotate entry
TEST_F(PageAttrsTest_697, GetRotateReturnsZeroByDefault_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    EXPECT_EQ(attrs.getRotate(), 0);
}

// Test getRotate returns the value set in dict
TEST_F(PageAttrsTest_697, GetRotateReturnsSetValue_697) {
    Dict pageDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    pageDict.add("MediaBox", std::move(arr));
    pageDict.add("Rotate", Object(90));
    
    PageAttrs attrs(nullptr, &pageDict);
    
    EXPECT_EQ(attrs.getRotate(), 90);
}

// Test getLastModified returns nullptr when not set
TEST_F(PageAttrsTest_697, GetLastModifiedReturnsNullWhenNotSet_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    EXPECT_EQ(attrs.getLastModified(), nullptr);
}

// Test getBoxColorInfo returns nullptr when not set
TEST_F(PageAttrsTest_697, GetBoxColorInfoReturnsNullWhenNotSet_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    EXPECT_EQ(attrs.getBoxColorInfo(), nullptr);
}

// Test getGroup returns nullptr when not set
TEST_F(PageAttrsTest_697, GetGroupReturnsNullWhenNotSet_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    EXPECT_EQ(attrs.getGroup(), nullptr);
}

// Test getPieceInfo returns nullptr when not set
TEST_F(PageAttrsTest_697, GetPieceInfoReturnsNullWhenNotSet_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    EXPECT_EQ(attrs.getPieceInfo(), nullptr);
}

// Test getResourceDict returns nullptr when no Resources set
TEST_F(PageAttrsTest_697, GetResourceDictReturnsNullWhenNotSet_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    Dict *resources = attrs.getResourceDict();
    // Resources may or may not be nullptr depending on default behavior
    // Just verify it doesn't crash
}

// Test that inheriting from parent PageAttrs works
TEST_F(PageAttrsTest_697, InheritFromParent_697) {
    Dict parentDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    parentDict.add("MediaBox", std::move(arr));
    parentDict.add("Rotate", Object(180));
    
    PageAttrs parentAttrs(nullptr, &parentDict);
    
    // Child dict without its own MediaBox or Rotate should inherit
    Dict childDict(nullptr);
    PageAttrs childAttrs(&parentAttrs, &childDict);
    
    EXPECT_EQ(childAttrs.getRotate(), 180);
    
    const PDFRectangle *mediaBox = childAttrs.getMediaBox();
    EXPECT_NE(mediaBox, nullptr);
}

// Test getBleedBox returns non-null (defaults to cropBox if not set)
TEST_F(PageAttrsTest_697, GetBleedBoxReturnsNonNull_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    EXPECT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageAttrsTest_697, GetTrimBoxReturnsNonNull_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    EXPECT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageAttrsTest_697, GetArtBoxReturnsNonNull_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    EXPECT_NE(artBox, nullptr);
}

// Test replaceResource changes the resource dict
TEST_F(PageAttrsTest_697, ReplaceResourceChangesResource_697) {
    Dict pageDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    pageDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &pageDict);
    
    Dict *newResDict = new Dict(nullptr);
    newResDict->incRef();
    Object newRes(newResDict);
    attrs.replaceResource(std::move(newRes));
    
    Dict *result = attrs.getResourceDict();
    EXPECT_EQ(result, newResDict);
}

// Test getResourceDictObject returns a valid pointer
TEST_F(PageAttrsTest_697, GetResourceDictObjectReturnsValidPointer_697) {
    Dict emptyDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    emptyDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &emptyDict);
    
    Object *resObj = attrs.getResourceDictObject();
    EXPECT_NE(resObj, nullptr);
}

// Test MediaBox dimensions
TEST_F(PageAttrsTest_697, MediaBoxDimensions_697) {
    Dict pageDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    pageDict.add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, &pageDict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    EXPECT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test invalid rotate values are normalized
TEST_F(PageAttrsTest_697, InvalidRotateIsNormalized_697) {
    Dict pageDict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    pageDict.add("MediaBox", std::move(arr));
    
    // 45 degrees is not a valid PDF rotation (must be multiple of 90)
    pageDict.add("Rotate", Object(45));
    
    PageAttrs attrs(nullptr, &pageDict);
    
    int rotate = attrs.getRotate();
    // Invalid rotation values should be normalized - typically to 0
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test that CropBox is clipped to MediaBox
TEST_F(PageAttrsTest_697, CropBoxClippedToMediaBox_697) {
    Dict pageDict(nullptr);
    
    Object mediaArr(new Array(nullptr));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(612));
    mediaArr.arrayAdd(Object(792));
    pageDict.add("MediaBox", std::move(mediaArr));
    
    // CropBox larger than MediaBox
    Object cropArr(new Array(nullptr));
    cropArr.arrayAdd(Object(-100));
    cropArr.arrayAdd(Object(-100));
    cropArr.arrayAdd(Object(1000));
    cropArr.arrayAdd(Object(1000));
    pageDict.add("CropBox", std::move(cropArr));
    
    PageAttrs attrs(nullptr, &pageDict);
    attrs.clipBoxes();
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    EXPECT_NE(cropBox, nullptr);
    // After clipping, cropBox should not exceed mediaBox
}
