#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Page.h"
#include "Object.h"
#include "Dict.h"
#include "GooString.h"

// Test fixture for PageAttrs
class PageAttrsTest_692 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that PageAttrs constructed with nullptr attrs and nullptr dict doesn't crash
TEST_F(PageAttrsTest_692, ConstructWithNullParams_692) {
    // Creating a minimal Dict for construction
    // PageAttrs requires a Dict*, passing nullptr for attrs (no parent)
    // We need at least a valid Dict with MediaBox for PageAttrs
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Add a MediaBox entry
    Object obj1;
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    // Basic checks - should not crash
    ASSERT_NE(attrs, nullptr);
    
    const PDFRectangle *mediaBox = attrs->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    
    delete attrs;
    delete dict;
}

// Test getLastModified returns nullptr when lastModified is not a string
TEST_F(PageAttrsTest_692, GetLastModifiedReturnsNullWhenNotString_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Add MediaBox
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    // Don't add LastModified - it should remain non-string
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    const GooString *lastMod = attrs->getLastModified();
    EXPECT_EQ(lastMod, nullptr);
    
    delete attrs;
    delete dict;
}

// Test getLastModified returns string when lastModified is a string
TEST_F(PageAttrsTest_692, GetLastModifiedReturnsStringWhenSet_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Add MediaBox
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    // Add LastModified as a string
    dict->add("LastModified", Object(std::make_unique<GooString>("D:20230101120000")));
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    const GooString *lastMod = attrs->getLastModified();
    ASSERT_NE(lastMod, nullptr);
    EXPECT_STREQ(lastMod->c_str(), "D:20230101120000");
    
    delete attrs;
    delete dict;
}

// Test isCropped returns false when no CropBox is set
TEST_F(PageAttrsTest_692, IsCroppedReturnsFalseWhenNoCropBox_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Add MediaBox only
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    EXPECT_FALSE(attrs->isCropped());
    
    delete attrs;
    delete dict;
}

// Test isCropped returns true when CropBox is set
TEST_F(PageAttrsTest_692, IsCroppedReturnsTrueWhenCropBoxSet_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    // Add MediaBox
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    // Add CropBox
    {
        Array *arr = new Array(xref);
        arr->add(Object(10));
        arr->add(Object(10));
        arr->add(Object(600));
        arr->add(Object(780));
        dict->add("CropBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    EXPECT_TRUE(attrs->isCropped());
    
    delete attrs;
    delete dict;
}

// Test getMediaBox returns valid box
TEST_F(PageAttrsTest_692, GetMediaBoxReturnsValidBox_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    const PDFRectangle *mediaBox = attrs->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
    
    delete attrs;
    delete dict;
}

// Test getCropBox returns valid box when CropBox is set
TEST_F(PageAttrsTest_692, GetCropBoxReturnsValidBox_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(10));
        arr->add(Object(10));
        arr->add(Object(600));
        arr->add(Object(780));
        dict->add("CropBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    const PDFRectangle *cropBox = attrs->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    
    delete attrs;
    delete dict;
}

// Test that getBleedBox, getTrimBox, getArtBox return valid pointers
TEST_F(PageAttrsTest_692, GetOtherBoxesReturnValidPointers_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    EXPECT_NE(attrs->getBleedBox(), nullptr);
    EXPECT_NE(attrs->getTrimBox(), nullptr);
    EXPECT_NE(attrs->getArtBox(), nullptr);
    
    delete attrs;
    delete dict;
}

// Test replaceResource replaces the resource dict object
TEST_F(PageAttrsTest_692, ReplaceResourceChangesResource_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    // Create a new resource dict
    Dict *resDict = new Dict(xref);
    resDict->add("Font", Object(new Dict(xref)));
    
    attrs->replaceResource(Object(resDict));
    
    Object *resourceObj = attrs->getResourceDictObject();
    ASSERT_NE(resourceObj, nullptr);
    EXPECT_TRUE(resourceObj->isDict());
    
    delete attrs;
    delete dict;
}

// Test PageAttrs with parent attributes (attrs not null)
TEST_F(PageAttrsTest_692, ConstructWithParentAttrs_692) {
    XRef *xref = nullptr;
    
    // Create parent dict with MediaBox
    Dict *parentDict = new Dict(xref);
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        parentDict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *parentAttrs = new PageAttrs(nullptr, parentDict);
    
    // Create child dict (empty, should inherit from parent)
    Dict *childDict = new Dict(xref);
    
    PageAttrs *childAttrs = new PageAttrs(parentAttrs, childDict);
    
    // Child should inherit MediaBox from parent
    const PDFRectangle *mediaBox = childAttrs->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    EXPECT_DOUBLE_EQ(mediaBox->x1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->y1, 0.0);
    EXPECT_DOUBLE_EQ(mediaBox->x2, 612.0);
    EXPECT_DOUBLE_EQ(mediaBox->y2, 792.0);
    
    delete childAttrs;
    delete parentAttrs;
    delete childDict;
    delete parentDict;
}

// Test getRotate default value
TEST_F(PageAttrsTest_692, GetRotateDefaultValue_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    // Default rotation should be 0
    EXPECT_EQ(attrs->getRotate(), 0);
    
    delete attrs;
    delete dict;
}

// Test getRotate with explicit rotation
TEST_F(PageAttrsTest_692, GetRotateWithExplicitRotation_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    dict->add("Rotate", Object(90));
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    EXPECT_EQ(attrs->getRotate(), 90);
    
    delete attrs;
    delete dict;
}

// Test getResourceDict when no resources set
TEST_F(PageAttrsTest_692, GetResourceDictWhenNoResources_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    
    // Without resources, getResourceDict may return nullptr
    // This is implementation dependent but we test the interface
    Dict *resDict = attrs->getResourceDict();
    // Just verify it doesn't crash - result may be nullptr or valid
    (void)resDict;
    
    delete attrs;
    delete dict;
}

// Test clipBoxes doesn't crash
TEST_F(PageAttrsTest_692, ClipBoxesDoesNotCrash_692) {
    XRef *xref = nullptr;
    Dict *dict = new Dict(xref);
    
    {
        Array *arr = new Array(xref);
        arr->add(Object(0));
        arr->add(Object(0));
        arr->add(Object(612));
        arr->add(Object(792));
        dict->add("MediaBox", Object(arr));
    }
    
    // Add a CropBox larger than MediaBox to test clipping
    {
        Array *arr = new Array(xref);
        arr->add(Object(-10));
        arr->add(Object(-10));
        arr->add(Object(700));
        arr->add(Object(900));
        dict->add("CropBox", Object(arr));
    }
    
    PageAttrs *attrs = new PageAttrs(nullptr, dict);
    attrs->clipBoxes();
    
    // After clipping, CropBox should be clipped to MediaBox
    const PDFRectangle *cropBox = attrs->getCropBox();
    ASSERT_NE(cropBox, nullptr);
    
    const PDFRectangle *mediaBox = attrs->getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
    
    // CropBox should not exceed MediaBox after clipping
    EXPECT_GE(cropBox->x1, mediaBox->x1);
    EXPECT_GE(cropBox->y1, mediaBox->y1);
    EXPECT_LE(cropBox->x2, mediaBox->x2);
    EXPECT_LE(cropBox->y2, mediaBox->y2);
    
    delete attrs;
    delete dict;
}
