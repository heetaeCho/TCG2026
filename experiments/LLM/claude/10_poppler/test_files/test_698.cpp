#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

#include <memory>

class PageAttrsTest_698 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getResourceDict returns nullptr when resources is not a Dict
TEST_F(PageAttrsTest_698, GetResourceDictReturnsNullWhenNotDict_698) {
    // Create PageAttrs with nullptr parent and nullptr dict
    // This should leave resources in a non-dict state
    Dict emptyDict(nullptr);
    PageAttrs attrs(nullptr, &emptyDict);
    
    // If resources was not set to a dict, getResourceDict should return nullptr
    Dict *result = attrs.getResourceDict();
    // Result depends on whether the empty dict has a Resources entry
    // With an empty dict, Resources won't be found, so resources should remain non-dict
    // (or inherited from nullptr parent which means none)
    EXPECT_EQ(result, nullptr);
}

// Test that getResourceDict returns a valid Dict pointer when resources is a Dict
TEST_F(PageAttrsTest_698, GetResourceDictReturnsDictWhenResourcesIsDict_698) {
    // Create a dict that contains a "Resources" entry which is itself a dict
    Dict *pageDict = new Dict(nullptr);
    Dict *resDict = new Dict(nullptr);
    Object resDictObj(resDict);
    pageDict->add("Resources", std::move(resDictObj));
    
    PageAttrs attrs(nullptr, pageDict);
    
    Dict *result = attrs.getResourceDict();
    EXPECT_NE(result, nullptr);
    
    delete pageDict;
}

// Test that getResourceDict inherits from parent PageAttrs
TEST_F(PageAttrsTest_698, GetResourceDictInheritsFromParent_698) {
    // Create parent with resources
    Dict *parentDict = new Dict(nullptr);
    Dict *resDict = new Dict(nullptr);
    Object resDictObj(resDict);
    parentDict->add("Resources", std::move(resDictObj));
    
    PageAttrs parentAttrs(nullptr, parentDict);
    
    // Create child with empty dict (should inherit resources from parent)
    Dict *childDict = new Dict(nullptr);
    PageAttrs childAttrs(&parentAttrs, childDict);
    
    Dict *result = childAttrs.getResourceDict();
    EXPECT_NE(result, nullptr);
    
    delete parentDict;
    delete childDict;
}

// Test getMediaBox returns non-null
TEST_F(PageAttrsTest_698, GetMediaBoxReturnsNonNull_698) {
    Dict emptyDict(nullptr);
    // MediaBox is required, but PageAttrs should have a default
    Dict *pageDict = new Dict(nullptr);
    
    // Add a MediaBox
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    EXPECT_NE(mediaBox, nullptr);
    
    delete pageDict;
}

// Test isCropped when no CropBox is specified
TEST_F(PageAttrsTest_698, IsCroppedFalseWhenNoCropBox_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    EXPECT_FALSE(attrs.isCropped());
    
    delete pageDict;
}

// Test isCropped when CropBox is specified
TEST_F(PageAttrsTest_698, IsCroppedTrueWhenCropBoxPresent_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    Object cropBoxArray(new Array(nullptr));
    cropBoxArray.arrayAdd(Object(10));
    cropBoxArray.arrayAdd(Object(10));
    cropBoxArray.arrayAdd(Object(600));
    cropBoxArray.arrayAdd(Object(780));
    pageDict->add("CropBox", std::move(cropBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    EXPECT_TRUE(attrs.isCropped());
    
    delete pageDict;
}

// Test getCropBox returns non-null
TEST_F(PageAttrsTest_698, GetCropBoxReturnsNonNull_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    EXPECT_NE(cropBox, nullptr);
    
    delete pageDict;
}

// Test getBleedBox returns non-null
TEST_F(PageAttrsTest_698, GetBleedBoxReturnsNonNull_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    EXPECT_NE(bleedBox, nullptr);
    
    delete pageDict;
}

// Test getTrimBox returns non-null
TEST_F(PageAttrsTest_698, GetTrimBoxReturnsNonNull_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    EXPECT_NE(trimBox, nullptr);
    
    delete pageDict;
}

// Test getArtBox returns non-null
TEST_F(PageAttrsTest_698, GetArtBoxReturnsNonNull_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    EXPECT_NE(artBox, nullptr);
    
    delete pageDict;
}

// Test getRotate with no Rotate specified (default should be 0)
TEST_F(PageAttrsTest_698, GetRotateDefaultIsZero_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    EXPECT_EQ(attrs.getRotate(), 0);
    
    delete pageDict;
}

// Test getRotate with Rotate specified
TEST_F(PageAttrsTest_698, GetRotateReturnsSpecifiedValue_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    pageDict->add("Rotate", Object(90));
    
    PageAttrs attrs(nullptr, pageDict);
    
    EXPECT_EQ(attrs.getRotate(), 90);
    
    delete pageDict;
}

// Test replaceResource changes the resource dict
TEST_F(PageAttrsTest_698, ReplaceResourceChangesResourceDict_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    // Initially no resources
    EXPECT_EQ(attrs.getResourceDict(), nullptr);
    
    // Replace with a new dict resource
    Dict *newResDict = new Dict(nullptr);
    Object newResObj(newResDict);
    attrs.replaceResource(std::move(newResObj));
    
    // Now getResourceDict should return the new dict
    EXPECT_NE(attrs.getResourceDict(), nullptr);
    EXPECT_EQ(attrs.getResourceDict(), newResDict);
    
    delete pageDict;
}

// Test getResourceDictObject returns non-null
TEST_F(PageAttrsTest_698, GetResourceDictObjectReturnsNonNull_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    Object *resObj = attrs.getResourceDictObject();
    EXPECT_NE(resObj, nullptr);
    
    delete pageDict;
}

// Test getLastModified when not set
TEST_F(PageAttrsTest_698, GetLastModifiedReturnsNullWhenNotSet_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    
    const GooString *lastMod = attrs.getLastModified();
    EXPECT_EQ(lastMod, nullptr);
    
    delete pageDict;
}

// Test that clipBoxes doesn't crash (called internally but we can call it)
TEST_F(PageAttrsTest_698, ClipBoxesDoesNotCrash_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    
    // Add crop box that exceeds media box
    Object cropBoxArray(new Array(nullptr));
    cropBoxArray.arrayAdd(Object(-100));
    cropBoxArray.arrayAdd(Object(-100));
    cropBoxArray.arrayAdd(Object(1000));
    cropBoxArray.arrayAdd(Object(1000));
    pageDict->add("CropBox", std::move(cropBoxArray));
    
    PageAttrs attrs(nullptr, pageDict);
    attrs.clipBoxes();
    
    // After clipping, crop box should be clipped to media box
    const PDFRectangle *cropBox = attrs.getCropBox();
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    EXPECT_NE(cropBox, nullptr);
    EXPECT_NE(mediaBox, nullptr);
    
    delete pageDict;
}

// Test with parent attrs and child overriding resources
TEST_F(PageAttrsTest_698, ChildOverridesParentResources_698) {
    // Parent with resources
    Dict *parentDict = new Dict(nullptr);
    Dict *parentResDict = new Dict(nullptr);
    parentResDict->add("Font", Object(new Dict(nullptr)));
    parentDict->add("Resources", Object(parentResDict));
    
    Object parentMediaBox(new Array(nullptr));
    parentMediaBox.arrayAdd(Object(0));
    parentMediaBox.arrayAdd(Object(0));
    parentMediaBox.arrayAdd(Object(612));
    parentMediaBox.arrayAdd(Object(792));
    parentDict->add("MediaBox", std::move(parentMediaBox));
    
    PageAttrs parentAttrs(nullptr, parentDict);
    
    // Child with its own resources
    Dict *childDict = new Dict(nullptr);
    Dict *childResDict = new Dict(nullptr);
    childDict->add("Resources", Object(childResDict));
    
    PageAttrs childAttrs(&parentAttrs, childDict);
    
    Dict *result = childAttrs.getResourceDict();
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result, childResDict);
    
    delete parentDict;
    delete childDict;
}

// Test getRotate with invalid rotation value (not multiple of 90)
TEST_F(PageAttrsTest_698, GetRotateWithInvalidValue_698) {
    Dict *pageDict = new Dict(nullptr);
    
    Object mediaBoxArray(new Array(nullptr));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    pageDict->add("MediaBox", std::move(mediaBoxArray));
    pageDict->add("Rotate", Object(45));
    
    PageAttrs attrs(nullptr, pageDict);
    
    // Invalid rotation should likely default to 0
    int rotate = attrs.getRotate();
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    
    delete pageDict;
}
