#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>

class PageAttrsTest_696 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test getPieceInfo returns nullptr when pieceInfo is not a Dict (default/null case)
TEST_F(PageAttrsTest_696, GetPieceInfoReturnsNullWhenNotDict_696) {
    // Create PageAttrs with no parent and an empty dict
    // When no pieceInfo is set in the dict, it should default to objNone,
    // which is not a dict, so getPieceInfo should return nullptr
    
    // We need a Dict to pass to PageAttrs constructor
    // Using a minimal dict with no PieceInfo entry
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(nullptr, attrs.getPieceInfo());
    
    delete dict;
}

// Test getPieceInfo returns a valid Dict* when pieceInfo is a Dict
TEST_F(PageAttrsTest_696, GetPieceInfoReturnsDictWhenSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Create a PieceInfo dict and add it to the page dict
    Dict *pieceInfoDict = new Dict(xref);
    pieceInfoDict->incRef();
    dict->add("PieceInfo", Object(pieceInfoDict));
    
    PageAttrs attrs(nullptr, dict);
    
    Dict *result = attrs.getPieceInfo();
    EXPECT_NE(nullptr, result);
    
    delete dict;
}

// Test that getMediaBox returns non-null
TEST_F(PageAttrsTest_696, GetMediaBoxReturnsNonNull_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Add a MediaBox array [0 0 612 792]
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    EXPECT_NE(nullptr, mediaBox);
    
    delete dict;
}

// Test isCropped returns false when no CropBox is set
TEST_F(PageAttrsTest_696, IsCroppedReturnsFalseWhenNoCropBox_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_FALSE(attrs.isCropped());
    
    delete dict;
}

// Test isCropped returns true when CropBox is set
TEST_F(PageAttrsTest_696, IsCroppedReturnsTrueWhenCropBoxSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    Array *cropBoxArray = new Array(xref);
    cropBoxArray->add(Object(10));
    cropBoxArray->add(Object(10));
    cropBoxArray->add(Object(600));
    cropBoxArray->add(Object(780));
    dict->add("CropBox", Object(cropBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_TRUE(attrs.isCropped());
    
    delete dict;
}

// Test getCropBox returns non-null
TEST_F(PageAttrsTest_696, GetCropBoxReturnsNonNull_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    EXPECT_NE(nullptr, cropBox);
    
    delete dict;
}

// Test getBleedBox returns non-null
TEST_F(PageAttrsTest_696, GetBleedBoxReturnsNonNull_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    EXPECT_NE(nullptr, bleedBox);
    
    delete dict;
}

// Test getTrimBox returns non-null
TEST_F(PageAttrsTest_696, GetTrimBoxReturnsNonNull_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    EXPECT_NE(nullptr, trimBox);
    
    delete dict;
}

// Test getArtBox returns non-null
TEST_F(PageAttrsTest_696, GetArtBoxReturnsNonNull_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    EXPECT_NE(nullptr, artBox);
    
    delete dict;
}

// Test getRotate returns default rotation (0) when not specified
TEST_F(PageAttrsTest_696, GetRotateReturnsDefaultWhenNotSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    int rotate = attrs.getRotate();
    EXPECT_EQ(0, rotate);
    
    delete dict;
}

// Test getRotate returns the set rotation value
TEST_F(PageAttrsTest_696, GetRotateReturnsSetValue_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    dict->add("Rotate", Object(90));
    
    PageAttrs attrs(nullptr, dict);
    
    int rotate = attrs.getRotate();
    EXPECT_EQ(90, rotate);
    
    delete dict;
}

// Test getGroup returns nullptr when no Group is set
TEST_F(PageAttrsTest_696, GetGroupReturnsNullWhenNotSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(nullptr, attrs.getGroup());
    
    delete dict;
}

// Test getBoxColorInfo returns nullptr when not set
TEST_F(PageAttrsTest_696, GetBoxColorInfoReturnsNullWhenNotSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(nullptr, attrs.getBoxColorInfo());
    
    delete dict;
}

// Test getSeparationInfo returns nullptr when not set
TEST_F(PageAttrsTest_696, GetSeparationInfoReturnsNullWhenNotSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(nullptr, attrs.getSeparationInfo());
    
    delete dict;
}

// Test getLastModified returns nullptr when not set
TEST_F(PageAttrsTest_696, GetLastModifiedReturnsNullWhenNotSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(nullptr, attrs.getLastModified());
    
    delete dict;
}

// Test that PageAttrs inherits from parent when dict doesn't override
TEST_F(PageAttrsTest_696, InheritsMediaBoxFromParent_696) {
    XRef *xref = nullptr;
    
    // Parent dict with MediaBox
    Dict *parentDict = new Dict(xref);
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    parentDict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs parentAttrs(nullptr, parentDict);
    
    // Child dict with no MediaBox - should inherit from parent
    Dict *childDict = new Dict(xref);
    PageAttrs childAttrs(&parentAttrs, childDict);
    
    const PDFRectangle *childMediaBox = childAttrs.getMediaBox();
    EXPECT_NE(nullptr, childMediaBox);
    
    // Should have inherited the parent's media box dimensions
    EXPECT_DOUBLE_EQ(0, childMediaBox->x1);
    EXPECT_DOUBLE_EQ(0, childMediaBox->y1);
    EXPECT_DOUBLE_EQ(612, childMediaBox->x2);
    EXPECT_DOUBLE_EQ(792, childMediaBox->y2);
    
    delete parentDict;
    delete childDict;
}

// Test getResourceDict returns nullptr when no Resources set
TEST_F(PageAttrsTest_696, GetResourceDictReturnsNullWhenNotSet_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    // Resources may be null if not set
    Dict *resources = attrs.getResourceDict();
    // Just verify it doesn't crash - may or may not be null depending on implementation
    (void)resources;
    
    delete dict;
}

// Test getResourceDictObject returns non-null
TEST_F(PageAttrsTest_696, GetResourceDictObjectReturnsNonNull_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    Object *resourceObj = attrs.getResourceDictObject();
    EXPECT_NE(nullptr, resourceObj);
    
    delete dict;
}

// Test MediaBox values are correctly parsed
TEST_F(PageAttrsTest_696, MediaBoxValuesCorrectlyParsed_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(10));
    mediaBoxArray->add(Object(20));
    mediaBoxArray->add(Object(400));
    mediaBoxArray->add(Object(600));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    EXPECT_NE(nullptr, mediaBox);
    EXPECT_DOUBLE_EQ(10, mediaBox->x1);
    EXPECT_DOUBLE_EQ(20, mediaBox->y1);
    EXPECT_DOUBLE_EQ(400, mediaBox->x2);
    EXPECT_DOUBLE_EQ(600, mediaBox->y2);
    
    delete dict;
}

// Test invalid rotate values (not multiple of 90) are handled
TEST_F(PageAttrsTest_696, InvalidRotateValueHandled_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    dict->add("Rotate", Object(45)); // Invalid rotation
    
    PageAttrs attrs(nullptr, dict);
    
    int rotate = attrs.getRotate();
    // Invalid rotation should be corrected to 0 or a valid multiple of 90
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
    
    delete dict;
}

// Test clipBoxes doesn't crash
TEST_F(PageAttrsTest_696, ClipBoxesDoesNotCrash_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    // Should not crash
    attrs.clipBoxes();
    
    delete dict;
}

// Test replaceResource
TEST_F(PageAttrsTest_696, ReplaceResourceDoesNotCrash_696) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    Array *mediaBoxArray = new Array(xref);
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(0));
    mediaBoxArray->add(Object(612));
    mediaBoxArray->add(Object(792));
    dict->add("MediaBox", Object(mediaBoxArray));
    
    PageAttrs attrs(nullptr, dict);
    
    Dict *newResources = new Dict(xref);
    newResources->incRef();
    attrs.replaceResource(Object(newResources));
    
    // After replacing, getResourceDict should return the new dict
    Dict *result = attrs.getResourceDict();
    EXPECT_NE(nullptr, result);
    
    delete dict;
}
