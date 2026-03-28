#include <gtest/gtest.h>
#include "Page.h"
#include "Object.h"

// Test fixture for PageAttrs
class PageAttrsTest_700 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that replaceResource replaces the resource with a new Object
TEST_F(PageAttrsTest_700, ReplaceResourceWithNullObject_700) {
    // Create PageAttrs with null parent and null dict
    // Since constructor requires Dict*, we need to handle this carefully
    // We'll create a minimal PageAttrs and test replaceResource
    PageAttrs attrs(nullptr, nullptr);
    
    // Replace resource with a null object
    Object nullObj = Object::null();
    attrs.replaceResource(std::move(nullObj));
    
    // After replacing, the resource dict object should reflect the change
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isNull());
}

// Test replacing resource with an integer object
TEST_F(PageAttrsTest_700, ReplaceResourceWithIntObject_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object intObj(42);
    attrs.replaceResource(std::move(intObj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isInt());
    EXPECT_EQ(resObj->getInt(), 42);
}

// Test replacing resource with a boolean object
TEST_F(PageAttrsTest_700, ReplaceResourceWithBoolObject_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object boolObj(true);
    attrs.replaceResource(std::move(boolObj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isBool());
    EXPECT_TRUE(resObj->getBool());
}

// Test replacing resource with a real (double) object
TEST_F(PageAttrsTest_700, ReplaceResourceWithRealObject_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object realObj(3.14);
    attrs.replaceResource(std::move(realObj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isReal());
    EXPECT_DOUBLE_EQ(resObj->getReal(), 3.14);
}

// Test replacing resource multiple times
TEST_F(PageAttrsTest_700, ReplaceResourceMultipleTimes_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    // First replacement
    Object intObj1(10);
    attrs.replaceResource(std::move(intObj1));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isInt());
    EXPECT_EQ(resObj->getInt(), 10);
    
    // Second replacement
    Object intObj2(20);
    attrs.replaceResource(std::move(intObj2));
    
    resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isInt());
    EXPECT_EQ(resObj->getInt(), 20);
    
    // Third replacement with different type
    Object nullObj = Object::null();
    attrs.replaceResource(std::move(nullObj));
    
    resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isNull());
}

// Test that after replaceResource, getResourceDict returns appropriate value
TEST_F(PageAttrsTest_700, ReplaceResourceAffectsGetResourceDict_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    // Replace with a non-dict object; getResourceDict should return nullptr for non-dict
    Object intObj(100);
    attrs.replaceResource(std::move(intObj));
    
    // getResourceDict returns Dict*, which should be nullptr if the resource is not a dict
    Dict *resDict = attrs.getResourceDict();
    EXPECT_EQ(resDict, nullptr);
}

// Test replacing resource with a none object
TEST_F(PageAttrsTest_700, ReplaceResourceWithNoneObject_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object noneObj;  // Default constructor creates objNone
    attrs.replaceResource(std::move(noneObj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isNone());
}

// Test default state of PageAttrs created with nullptr
TEST_F(PageAttrsTest_700, DefaultMediaBox_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *mediaBox = attrs.getMediaBox();
    ASSERT_NE(mediaBox, nullptr);
}

// Test isCropped with default construction
TEST_F(PageAttrsTest_700, DefaultIsCropped_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    // With no dict, there should be no crop box
    EXPECT_FALSE(attrs.isCropped());
}

// Test getCropBox returns non-null
TEST_F(PageAttrsTest_700, DefaultCropBox_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *cropBox = attrs.getCropBox();
    ASSERT_NE(cropBox, nullptr);
}

// Test getBleedBox returns non-null
TEST_F(PageAttrsTest_700, DefaultBleedBox_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *bleedBox = attrs.getBleedBox();
    ASSERT_NE(bleedBox, nullptr);
}

// Test getTrimBox returns non-null
TEST_F(PageAttrsTest_700, DefaultTrimBox_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *trimBox = attrs.getTrimBox();
    ASSERT_NE(trimBox, nullptr);
}

// Test getArtBox returns non-null
TEST_F(PageAttrsTest_700, DefaultArtBox_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    const PDFRectangle *artBox = attrs.getArtBox();
    ASSERT_NE(artBox, nullptr);
}

// Test replacing resource with an int64 object
TEST_F(PageAttrsTest_700, ReplaceResourceWithInt64Object_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object int64Obj(static_cast<long long>(1234567890123LL));
    attrs.replaceResource(std::move(int64Obj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isInt64());
    EXPECT_EQ(resObj->getInt64(), 1234567890123LL);
}

// Test replacing resource with error object
TEST_F(PageAttrsTest_700, ReplaceResourceWithErrorObject_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object errObj = Object::error();
    attrs.replaceResource(std::move(errObj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isError());
}

// Test replacing resource with eof object
TEST_F(PageAttrsTest_700, ReplaceResourceWithEofObject_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object eofObj = Object::eof();
    attrs.replaceResource(std::move(eofObj));
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
    EXPECT_TRUE(resObj->isEOF());
}

// Test getResourceDictObject returns a valid pointer
TEST_F(PageAttrsTest_700, GetResourceDictObjectNotNull_700) {
    PageAttrs attrs(nullptr, nullptr);
    
    Object *resObj = attrs.getResourceDictObject();
    ASSERT_NE(resObj, nullptr);
}
