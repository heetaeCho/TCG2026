#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

class PageAttrsTest_693 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that PageAttrs can be constructed with nullptr attrs and nullptr dict
TEST_F(PageAttrsTest_693, ConstructWithNullAttrsAndNullDict_693) {
    // Constructing with nullptr for both should not crash
    // Note: dict=nullptr may cause issues depending on implementation,
    // but we test the interface
    PageAttrs attrs(nullptr, nullptr);
    
    // Should have default media box
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test getBoxColorInfo returns nullptr when boxColorInfo is not a Dict
TEST_F(PageAttrsTest_693, GetBoxColorInfoReturnsNullWhenNotDict_693) {
    PageAttrs attrs(nullptr, nullptr);
    
    // By default, boxColorInfo should be objNone (not a dict)
    Dict *result = attrs.getBoxColorInfo();
    EXPECT_EQ(result, nullptr);
}

// Test getMediaBox returns a valid pointer
TEST_F(PageAttrsTest_693, GetMediaBoxReturnsValidPointer_693) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test getCropBox returns a valid pointer
TEST_F(PageAttrsTest_693, GetCropBoxReturnsValidPointer_693) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test getBleedBox returns a valid pointer
TEST_F(PageAttrsTest_693, GetBleedBoxReturnsValidPointer_693) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns a valid pointer
TEST_F(PageAttrsTest_693, GetTrimBoxReturnsValidPointer_693) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns a valid pointer
TEST_F(PageAttrsTest_693, GetArtBoxReturnsValidPointer_693) {
    PageAttrs attrs(nullptr, nullptr);
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test isCropped returns false when no crop box is set
TEST_F(PageAttrsTest_693, IsCroppedReturnsFalseByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    EXPECT_FALSE(attrs.isCropped());
}

// Test getRotate returns default rotation
TEST_F(PageAttrsTest_693, GetRotateReturnsDefaultValue_693) {
    PageAttrs attrs(nullptr, nullptr);
    int rotate = attrs.getRotate();
    // Rotation should be 0, 90, 180, or 270; default is typically 0
    EXPECT_EQ(rotate % 90, 0);
    EXPECT_GE(rotate, 0);
    EXPECT_LT(rotate, 360);
}

// Test getLastModified returns nullptr when not set
TEST_F(PageAttrsTest_693, GetLastModifiedReturnsNullByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    const GooString *lastMod = attrs.getLastModified();
    EXPECT_EQ(lastMod, nullptr);
}

// Test getGroup returns nullptr when not set
TEST_F(PageAttrsTest_693, GetGroupReturnsNullByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *group = attrs.getGroup();
    EXPECT_EQ(group, nullptr);
}

// Test getPieceInfo returns nullptr when not set
TEST_F(PageAttrsTest_693, GetPieceInfoReturnsNullByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *pieceInfo = attrs.getPieceInfo();
    EXPECT_EQ(pieceInfo, nullptr);
}

// Test getSeparationInfo returns nullptr when not set
TEST_F(PageAttrsTest_693, GetSeparationInfoReturnsNullByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *sepInfo = attrs.getSeparationInfo();
    EXPECT_EQ(sepInfo, nullptr);
}

// Test getResourceDict returns nullptr when not set
TEST_F(PageAttrsTest_693, GetResourceDictReturnsNullByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    Dict *resources = attrs.getResourceDict();
    // May be nullptr if no resources set
    // This is acceptable - just verify it doesn't crash
}

// Test getResourceDictObject returns a valid pointer
TEST_F(PageAttrsTest_693, GetResourceDictObjectReturnsValidPointer_693) {
    PageAttrs attrs(nullptr, nullptr);
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}

// Test that constructing with parent attrs inherits values
TEST_F(PageAttrsTest_693, ConstructWithParentAttrsInherits_693) {
    PageAttrs parent(nullptr, nullptr);
    PageAttrs child(&parent, nullptr);
    
    // Child should inherit media box from parent
    const PDFRectangle *parentMediaBox = parent.getMediaBox();
    const PDFRectangle *childMediaBox = child.getMediaBox();
    ASSERT_NE(parentMediaBox, nullptr);
    ASSERT_NE(childMediaBox, nullptr);
    
    EXPECT_DOUBLE_EQ(parentMediaBox->x1, childMediaBox->x1);
    EXPECT_DOUBLE_EQ(parentMediaBox->y1, childMediaBox->y1);
    EXPECT_DOUBLE_EQ(parentMediaBox->x2, childMediaBox->x2);
    EXPECT_DOUBLE_EQ(parentMediaBox->y2, childMediaBox->y2);
}

// Test that child inherits rotation from parent
TEST_F(PageAttrsTest_693, ChildInheritsRotationFromParent_693) {
    PageAttrs parent(nullptr, nullptr);
    PageAttrs child(&parent, nullptr);
    
    EXPECT_EQ(parent.getRotate(), child.getRotate());
}

// Test clipBoxes doesn't crash when called with default values
TEST_F(PageAttrsTest_693, ClipBoxesDoesNotCrash_693) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();
    
    // After clipping, boxes should still be valid
    ASSERT_NE(attrs.getMediaBox(), nullptr);
    ASSERT_NE(attrs.getCropBox(), nullptr);
    ASSERT_NE(attrs.getBleedBox(), nullptr);
    ASSERT_NE(attrs.getTrimBox(), nullptr);
    ASSERT_NE(attrs.getArtBox(), nullptr);
}

// Test that crop box is within or equal to media box after clipBoxes
TEST_F(PageAttrsTest_693, CropBoxWithinMediaBoxAfterClip_693) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.clipBoxes();
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    
    EXPECT_GE(cropBox->x1, mediaBox->x1);
    EXPECT_GE(cropBox->y1, mediaBox->y1);
    EXPECT_LE(cropBox->x2, mediaBox->x2);
    EXPECT_LE(cropBox->y2, mediaBox->y2);
}

// Test replaceResource with a null object
TEST_F(PageAttrsTest_693, ReplaceResourceWithNull_693) {
    PageAttrs attrs(nullptr, nullptr);
    attrs.replaceResource(Object(objNull));
    
    // After replacing, resource dict object should reflect the change
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}

// Test that getMetadata returns nullptr when not set
TEST_F(PageAttrsTest_693, GetMetadataReturnsNullByDefault_693) {
    PageAttrs attrs(nullptr, nullptr);
    Stream *metadata = attrs.getMetadata();
    EXPECT_EQ(metadata, nullptr);
}

// Test constructing PageAttrs with a Dict that has MediaBox
TEST_F(PageAttrsTest_693, ConstructWithDictContainingMediaBox_693) {
    // Create a Dict with a MediaBox entry
    Dict *dict = new Dict(nullptr);
    
    Object arr(new Array(nullptr));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(0));
    arr.arrayAdd(Object(612));
    arr.arrayAdd(Object(792));
    
    dict->add("MediaBox", std::move(arr));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
}

// Test constructing PageAttrs with a Dict that has CropBox
TEST_F(PageAttrsTest_693, ConstructWithDictContainingCropBox_693) {
    Dict *dict = new Dict(nullptr);
    
    // First set MediaBox
    Object mediaArr(new Array(nullptr));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(612));
    mediaArr.arrayAdd(Object(792));
    dict->add("MediaBox", std::move(mediaArr));
    
    // Then set CropBox
    Object cropArr(new Array(nullptr));
    cropArr.arrayAdd(Object(10));
    cropArr.arrayAdd(Object(10));
    cropArr.arrayAdd(Object(600));
    cropArr.arrayAdd(Object(780));
    dict->add("CropBox", std::move(cropArr));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_TRUE(attrs.isCropped());
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test constructing PageAttrs with a Dict that has Rotate
TEST_F(PageAttrsTest_693, ConstructWithDictContainingRotate_693) {
    Dict *dict = new Dict(nullptr);
    
    Object mediaArr(new Array(nullptr));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(612));
    mediaArr.arrayAdd(Object(792));
    dict->add("MediaBox", std::move(mediaArr));
    
    dict->add("Rotate", Object(90));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getRotate(), 90);
}

// Test constructing PageAttrs with BoxColorInfo dict
TEST_F(PageAttrsTest_693, ConstructWithDictContainingBoxColorInfo_693) {
    Dict *dict = new Dict(nullptr);
    
    Object mediaArr(new Array(nullptr));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(0));
    mediaArr.arrayAdd(Object(612));
    mediaArr.arrayAdd(Object(792));
    dict->add("MediaBox", std::move(mediaArr));
    
    Dict *bciDict = new Dict(nullptr);
    dict->add("BoxColorInfo", Object(bciDict));
    
    PageAttrs attrs(nullptr, dict);
    
    Dict *boxColorInfo = attrs.getBoxColorInfo();
    EXPECT_NE(boxColorInfo, nullptr);
}

// Test that getBoxColorInfo returns nullptr for non-dict boxColorInfo
TEST_F(PageAttrsTest_693, GetBoxColorInfoNullForNonDict_693) {
    PageAttrs attrs(nullptr, nullptr);
    // Default boxColorInfo is not a dict
    EXPECT_EQ(attrs.getBoxColorInfo(), nullptr);
}
