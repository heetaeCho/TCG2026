#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "GooString.h"

class FileSpecTest_1134 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that a FileSpec constructed from a null Object is not ok
TEST_F(FileSpecTest_1134, ConstructFromNullObject_IsNotOk_1134) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test that a FileSpec constructed from an invalid/empty Object is not ok
TEST_F(FileSpecTest_1134, ConstructFromEmptyObject_IsNotOk_1134) {
    Object obj;
    obj = Object();
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test that getFileName returns nullptr when FileSpec is not ok
TEST_F(FileSpecTest_1134, GetFileName_WhenNotOk_ReturnsNull_1134) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
    EXPECT_EQ(fs.getFileName(), nullptr);
}

// Test that getDescription returns nullptr when FileSpec is not ok
TEST_F(FileSpecTest_1134, GetDescription_WhenNotOk_ReturnsNull_1134) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
    EXPECT_EQ(fs.getDescription(), nullptr);
}

// Test that getFileNameForPlatform returns nullptr when FileSpec is not ok
TEST_F(FileSpecTest_1134, GetFileNameForPlatform_WhenNotOk_ReturnsNull_1134) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
    EXPECT_EQ(fs.getFileNameForPlatform(), nullptr);
}

// Test that getEmbeddedFile returns nullptr when FileSpec is not ok
TEST_F(FileSpecTest_1134, GetEmbeddedFile_WhenNotOk_ReturnsNull_1134) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
    EXPECT_EQ(fs.getEmbeddedFile(), nullptr);
}

// Test constructing FileSpec from a string object (valid simple file spec)
TEST_F(FileSpecTest_1134, ConstructFromStringObject_IsOk_1134) {
    Object obj = Object(new GooString("test.pdf"));
    FileSpec fs(&obj);
    EXPECT_TRUE(fs.isOk());
}

// Test that getFileName returns the correct name for a string-based FileSpec
TEST_F(FileSpecTest_1134, GetFileName_FromStringObject_ReturnsCorrectName_1134) {
    Object obj = Object(new GooString("test.pdf"));
    FileSpec fs(&obj);
    EXPECT_TRUE(fs.isOk());
    const GooString *name = fs.getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "test.pdf");
}

// Test constructing FileSpec from a dictionary object with /F key
TEST_F(FileSpecTest_1134, ConstructFromDictWithFKey_IsOk_1134) {
    Object obj = Object(new Dict(nullptr));
    obj.dictAdd("F", Object(new GooString("document.pdf")));
    obj.dictAdd("Type", Object(objName, "Filespec"));
    FileSpec fs(&obj);
    EXPECT_TRUE(fs.isOk());
}

// Test getFileName from a dict-based FileSpec with /F key
TEST_F(FileSpecTest_1134, GetFileName_FromDictWithFKey_1134) {
    Object obj = Object(new Dict(nullptr));
    obj.dictAdd("F", Object(new GooString("document.pdf")));
    obj.dictAdd("Type", Object(objName, "Filespec"));
    FileSpec fs(&obj);
    if (fs.isOk()) {
        const GooString *name = fs.getFileName();
        ASSERT_NE(name, nullptr);
        EXPECT_STREQ(name->c_str(), "document.pdf");
    }
}

// Test that an integer Object does not produce a valid FileSpec
TEST_F(FileSpecTest_1134, ConstructFromIntObject_IsNotOk_1134) {
    Object obj = Object(42);
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test that a boolean Object does not produce a valid FileSpec
TEST_F(FileSpecTest_1134, ConstructFromBoolObject_IsNotOk_1134) {
    Object obj = Object(true);
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test that a real Object does not produce a valid FileSpec
TEST_F(FileSpecTest_1134, ConstructFromRealObject_IsNotOk_1134) {
    Object obj = Object(3.14);
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test FileSpec with empty string
TEST_F(FileSpecTest_1134, ConstructFromEmptyString_1134) {
    Object obj = Object(new GooString(""));
    FileSpec fs(&obj);
    // An empty string might still be "ok" as it's a valid string object
    if (fs.isOk()) {
        const GooString *name = fs.getFileName();
        ASSERT_NE(name, nullptr);
        EXPECT_STREQ(name->c_str(), "");
    }
}

// Test getFileNameForPlatform when FileSpec is valid
TEST_F(FileSpecTest_1134, GetFileNameForPlatform_WhenOk_1134) {
    Object obj = Object(new GooString("test.pdf"));
    FileSpec fs(&obj);
    if (fs.isOk()) {
        GooString *platformName = fs.getFileNameForPlatform();
        ASSERT_NE(platformName, nullptr);
    }
}

// Test that description is null for a simple string-based FileSpec
TEST_F(FileSpecTest_1134, GetDescription_SimpleStringSpec_ReturnsNull_1134) {
    Object obj = Object(new GooString("test.pdf"));
    FileSpec fs(&obj);
    if (fs.isOk()) {
        const GooString *desc = fs.getDescription();
        // Simple string FileSpec shouldn't have a description
        EXPECT_EQ(desc, nullptr);
    }
}

// Test FileSpec with a dict that has a /Desc key
TEST_F(FileSpecTest_1134, GetDescription_DictWithDescKey_1134) {
    Object obj = Object(new Dict(nullptr));
    obj.dictAdd("F", Object(new GooString("document.pdf")));
    obj.dictAdd("Desc", Object(new GooString("A test document")));
    obj.dictAdd("Type", Object(objName, "Filespec"));
    FileSpec fs(&obj);
    if (fs.isOk()) {
        const GooString *desc = fs.getDescription();
        if (desc) {
            EXPECT_STREQ(desc->c_str(), "A test document");
        }
    }
}
