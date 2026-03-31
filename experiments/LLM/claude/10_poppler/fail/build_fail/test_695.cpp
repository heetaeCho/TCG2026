#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "Object.h"
#include "Stream.h"
#include "Dict.h"

// We need to test PageAttrs::getMetadata() which checks if the internal
// metadata Object isStream() and returns getStream() or nullptr.

// Since PageAttrs requires a constructor with (const PageAttrs*, Dict*),
// we need to create appropriate test fixtures.

class PageAttrsGetMetadataTest_695 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getMetadata returns nullptr when metadata is not a stream
// (default/null case - no Metadata key in dict)
TEST_F(PageAttrsGetMetadataTest_695, ReturnsNullWhenNoMetadata_695) {
    // Create an empty dict with no Metadata entry
    // PageAttrs constructed with nullptr parent and an empty dict
    // should have metadata as a non-stream object
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getMetadata(), nullptr);
    
    delete dict;
}

// Test that getMetadata returns nullptr when parent attrs have no metadata
// and child dict has no metadata either
TEST_F(PageAttrsGetMetadataTest_695, ReturnsNullWhenParentAndChildHaveNoMetadata_695) {
    XRef *xref = nullptr;
    Dict *parentDict = new Dict(xref);
    
    PageAttrs parentAttrs(nullptr, parentDict);
    
    Dict *childDict = new Dict(xref);
    PageAttrs childAttrs(&parentAttrs, childDict);
    
    EXPECT_EQ(childAttrs.getMetadata(), nullptr);
    
    delete parentDict;
    delete childDict;
}

// Test basic accessors that should return valid pointers after construction
TEST_F(PageAttrsGetMetadataTest_695, MediaBoxIsNotNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    // MediaBox should always exist (default values)
    EXPECT_NE(attrs.getMediaBox(), nullptr);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, CropBoxIsNotNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_NE(attrs.getCropBox(), nullptr);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, BleedBoxIsNotNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_NE(attrs.getBleedBox(), nullptr);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, TrimBoxIsNotNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_NE(attrs.getTrimBox(), nullptr);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, ArtBoxIsNotNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_NE(attrs.getArtBox(), nullptr);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, DefaultRotateIsZero_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getRotate(), 0);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, IsCroppedDefaultFalse_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    // Without explicit CropBox, isCropped should be false
    EXPECT_FALSE(attrs.isCropped());
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, GetLastModifiedDefaultNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    // Without LastModified key, should return nullptr
    EXPECT_EQ(attrs.getLastModified(), nullptr);
    
    delete dict;
}

TEST_F(PageAttrsGetMetadataTest_695, ResourceDictObjectNotNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    // getResourceDictObject should return a valid pointer to the internal Object
    EXPECT_NE(attrs.getResourceDictObject(), nullptr);
    
    delete dict;
}

// Test with a Rotate value in dict
TEST_F(PageAttrsGetMetadataTest_695, RotateFromDict_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    dict->add("Rotate", Object(90));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getRotate(), 90);
    
    delete dict;
}

// Test that invalid Rotate values get normalized
TEST_F(PageAttrsGetMetadataTest_695, RotateNormalization_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    // Rotate should be multiple of 90; non-standard values may be normalized
    dict->add("Rotate", Object(270));
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getRotate(), 270);
    
    delete dict;
}

// Test replaceResource
TEST_F(PageAttrsGetMetadataTest_695, ReplaceResource_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    // Replace with a null object
    attrs.replaceResource(Object(objNull));
    
    // After replacement, getResourceDict may return nullptr
    // This is just verifying the call doesn't crash
    SUCCEED();
    
    delete dict;
}

// Test child inherits from parent
TEST_F(PageAttrsGetMetadataTest_695, ChildInheritsParentMediaBox_695) {
    XRef *xref = nullptr;
    Dict *parentDict = new Dict(xref);
    
    // Set up a MediaBox in parent
    Object mediaBoxArray(new Array(xref));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(0));
    mediaBoxArray.arrayAdd(Object(612));
    mediaBoxArray.arrayAdd(Object(792));
    parentDict->add("MediaBox", std::move(mediaBoxArray));
    
    PageAttrs parentAttrs(nullptr, parentDict);
    
    // Child with empty dict should inherit parent's MediaBox
    Dict *childDict = new Dict(xref);
    PageAttrs childAttrs(&parentAttrs, childDict);
    
    const PDFRectangle *parentBox = parentAttrs.getMediaBox();
    const PDFRectangle *childBox = childAttrs.getMediaBox();
    
    EXPECT_DOUBLE_EQ(parentBox->x1, childBox->x1);
    EXPECT_DOUBLE_EQ(parentBox->y1, childBox->y1);
    EXPECT_DOUBLE_EQ(parentBox->x2, childBox->x2);
    EXPECT_DOUBLE_EQ(parentBox->y2, childBox->y2);
    
    delete parentDict;
    delete childDict;
}

// Test getGroup returns nullptr when no Group in dict
TEST_F(PageAttrsGetMetadataTest_695, GetGroupDefaultNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getGroup(), nullptr);
    
    delete dict;
}

// Test getBoxColorInfo returns nullptr when not set
TEST_F(PageAttrsGetMetadataTest_695, GetBoxColorInfoDefaultNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getBoxColorInfo(), nullptr);
    
    delete dict;
}

// Test getPieceInfo returns nullptr when not set
TEST_F(PageAttrsGetMetadataTest_695, GetPieceInfoDefaultNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getPieceInfo(), nullptr);
    
    delete dict;
}

// Test getSeparationInfo returns nullptr when not set
TEST_F(PageAttrsGetMetadataTest_695, GetSeparationInfoDefaultNull_695) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    PageAttrs attrs(nullptr, dict);
    
    EXPECT_EQ(attrs.getSeparationInfo(), nullptr);
    
    delete dict;
}
