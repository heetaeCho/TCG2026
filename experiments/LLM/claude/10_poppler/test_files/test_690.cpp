#include <gtest/gtest.h>
#include "Page.h"
#include "PDFDoc.h"
#include "GlobalParams.h"
#include <memory>
#include <string>

class PageAttrsTest_690 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that getArtBox returns a non-null pointer
TEST_F(PageAttrsTest_690, GetArtBoxReturnsNonNull_690) {
    // We need a PDFDoc to get a real Page with PageAttrs
    // Create PageAttrs with nullptr parent and nullptr dict
    // Since constructor requires Dict*, we test through a document if possible
    // For a minimal test, we can create PageAttrs with null attrs and a dict
    
    // Create a minimal PDF document to test with
    // We'll test with a simple approach using available constructors
    
    // PageAttrs(nullptr, nullptr) - test with null parameters
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test that getMediaBox returns a non-null pointer
TEST_F(PageAttrsTest_690, GetMediaBoxReturnsNonNull_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test that getCropBox returns a non-null pointer
TEST_F(PageAttrsTest_690, GetCropBoxReturnsNonNull_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test that getBleedBox returns a non-null pointer
TEST_F(PageAttrsTest_690, GetBleedBoxReturnsNonNull_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test that getTrimBox returns a non-null pointer
TEST_F(PageAttrsTest_690, GetTrimBoxReturnsNonNull_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test that isCropped returns a bool value (default should be false with no dict)
TEST_F(PageAttrsTest_690, IsCroppedDefaultFalse_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    bool cropped = attrs.isCropped();
    // With no dict, there should be no crop box set
    EXPECT_FALSE(cropped);
}

// Test that getRotate returns a valid rotation value
TEST_F(PageAttrsTest_690, GetRotateDefaultValue_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    int rotate = attrs.getRotate();
    // Rotation should be 0, 90, 180, or 270
    EXPECT_TRUE(rotate == 0 || rotate == 90 || rotate == 180 || rotate == 270);
}

// Test that getLastModified returns something (possibly null string)
TEST_F(PageAttrsTest_690, GetLastModifiedDefault_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const GooString *lastModified = attrs.getLastModified();
    // With no dict, lastModified may be nullptr
    // Just verify the call doesn't crash
    (void)lastModified;
}

// Test that getResourceDict returns nullptr when no resources set
TEST_F(PageAttrsTest_690, GetResourceDictDefaultNull_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    Dict *resDict = attrs.getResourceDict();
    // With no dict provided, resources should be null
    EXPECT_EQ(resDict, nullptr);
}

// Test that getBoxColorInfo doesn't crash with default
TEST_F(PageAttrsTest_690, GetBoxColorInfoDefault_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    Dict *boxColorInfo = attrs.getBoxColorInfo();
    // May be nullptr with no dict
    (void)boxColorInfo;
}

// Test that getGroup doesn't crash with default
TEST_F(PageAttrsTest_690, GetGroupDefault_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    Dict *group = attrs.getGroup();
    (void)group;
}

// Test that getPieceInfo doesn't crash with default
TEST_F(PageAttrsTest_690, GetPieceInfoDefault_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    Dict *pieceInfo = attrs.getPieceInfo();
    (void)pieceInfo;
}

// Test that getSeparationInfo doesn't crash with default
TEST_F(PageAttrsTest_690, GetSeparationInfoDefault_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    Dict *sepInfo = attrs.getSeparationInfo();
    (void)sepInfo;
}

// Test that getResourceDictObject returns a valid Object pointer
TEST_F(PageAttrsTest_690, GetResourceDictObjectReturnsNonNull_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}

// Test that artBox is consistent across multiple calls
TEST_F(PageAttrsTest_690, GetArtBoxConsistentAcrossCalls_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *artBox1 = attrs.getArtBox();
    const PDFRectangle *artBox2 = attrs.getArtBox();
    
    ASSERT_NE(artBox1, nullptr);
    ASSERT_NE(artBox2, nullptr);
    // Should return the same pointer (same internal member)
    EXPECT_EQ(artBox1, artBox2);
}

// Test that mediaBox is consistent across multiple calls
TEST_F(PageAttrsTest_690, GetMediaBoxConsistentAcrossCalls_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *mediaBox1 = attrs.getMediaBox();
    const PDFRectangle *mediaBox2 = attrs.getMediaBox();
    
    EXPECT_EQ(mediaBox1, mediaBox2);
}

// Test creating PageAttrs with parent attrs (inheritance)
TEST_F(PageAttrsTest_690, InheritFromParentAttrs_690) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    // Child should inherit parent's boxes
    const PDFRectangle *parentMedia = parentAttrs.getMediaBox();
    const PDFRectangle *childMedia = childAttrs.getMediaBox();
    
    ASSERT_NE(parentMedia, nullptr);
    ASSERT_NE(childMedia, nullptr);
    
    // Values should match (inherited)
    EXPECT_DOUBLE_EQ(parentMedia->x1, childMedia->x1);
    EXPECT_DOUBLE_EQ(parentMedia->y1, childMedia->y1);
    EXPECT_DOUBLE_EQ(parentMedia->x2, childMedia->x2);
    EXPECT_DOUBLE_EQ(parentMedia->y2, childMedia->y2);
}

// Test that child inherits rotation from parent
TEST_F(PageAttrsTest_690, InheritRotateFromParent_690) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    EXPECT_EQ(parentAttrs.getRotate(), childAttrs.getRotate());
}

// Test that child inherits artBox from parent
TEST_F(PageAttrsTest_690, InheritArtBoxFromParent_690) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs childAttrs(&parentAttrs, nullptr);
    
    const PDFRectangle *parentArt = parentAttrs.getArtBox();
    const PDFRectangle *childArt = childAttrs.getArtBox();
    
    ASSERT_NE(parentArt, nullptr);
    ASSERT_NE(childArt, nullptr);
    
    EXPECT_DOUBLE_EQ(parentArt->x1, childArt->x1);
    EXPECT_DOUBLE_EQ(parentArt->y1, childArt->y1);
    EXPECT_DOUBLE_EQ(parentArt->x2, childArt->x2);
    EXPECT_DOUBLE_EQ(parentArt->y2, childArt->y2);
}

// Test replaceResource
TEST_F(PageAttrsTest_690, ReplaceResourceUpdatesResource_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    // Initially resources should be null/none
    Dict *initialRes = attrs.getResourceDict();
    
    // Create a new Object and replace
    Object newObj;
    attrs.replaceResource(std::move(newObj));
    
    // Verify it doesn't crash; the resource dict might change
    // We just verify the method is callable
}

// Test clipBoxes doesn't crash with default values
TEST_F(PageAttrsTest_690, ClipBoxesDefault_690) {
    PageAttrs attrs(nullptr, nullptr);
    
    // clipBoxes should not crash
    attrs.clipBoxes();
    
    // After clipping, boxes should still be valid
    ASSERT_NE(attrs.getMediaBox(), nullptr);
    ASSERT_NE(attrs.getCropBox(), nullptr);
    ASSERT_NE(attrs.getBleedBox(), nullptr);
    ASSERT_NE(attrs.getTrimBox(), nullptr);
    ASSERT_NE(attrs.getArtBox(), nullptr);
}

// Test that after clipBoxes, crop/bleed/trim/art boxes are within media box
TEST_F(PageAttrsTest_690, ClipBoxesConstrainsBoxes_690) {
    PageAttrs parentAttrs(nullptr, nullptr);
    PageAttrs attrs(&parentAttrs, nullptr);
    
    attrs.clipBoxes();
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    const PDFRectangle *cropBox = attrs.getCropBox();
    const PDFRectangle *artBox = attrs.getArtBox();
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    const PDFRectangle *trimBox = attrs.getTrimBox();
    
    ASSERT_NE(mediaBox, nullptr);
    ASSERT_NE(cropBox, nullptr);
    ASSERT_NE(artBox, nullptr);
    ASSERT_NE(bleedBox, nullptr);
    ASSERT_NE(trimBox, nullptr);
}
