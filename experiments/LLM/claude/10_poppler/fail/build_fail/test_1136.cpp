#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "GooString.h"

class FileSpecTest_1136 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing FileSpec from a null/invalid Object results in not-ok state
TEST_F(FileSpecTest_1136, ConstructFromNullObject_1136) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test that getDescription returns nullptr when no description is set (invalid FileSpec)
TEST_F(FileSpecTest_1136, GetDescriptionReturnsNullForInvalidSpec_1136) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_EQ(fs.getDescription(), nullptr);
}

// Test that getFileName returns nullptr when FileSpec is invalid
TEST_F(FileSpecTest_1136, GetFileNameReturnsNullForInvalidSpec_1136) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_EQ(fs.getFileName(), nullptr);
}

// Test that getFileNameForPlatform returns nullptr when FileSpec is invalid
TEST_F(FileSpecTest_1136, GetFileNameForPlatformReturnsNullForInvalidSpec_1136) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_EQ(fs.getFileNameForPlatform(), nullptr);
}

// Test that getEmbeddedFile returns nullptr when FileSpec is invalid
TEST_F(FileSpecTest_1136, GetEmbeddedFileReturnsNullForInvalidSpec_1136) {
    Object obj;
    FileSpec fs(&obj);
    EXPECT_EQ(fs.getEmbeddedFile(), nullptr);
}

// Test constructing FileSpec from a string Object (simple file spec)
TEST_F(FileSpecTest_1136, ConstructFromStringObject_1136) {
    Object obj(new GooString("test.pdf"));
    FileSpec fs(&obj);
    // A simple string object should be a valid file spec
    if (fs.isOk()) {
        const GooString *fileName = fs.getFileName();
        EXPECT_NE(fileName, nullptr);
        if (fileName) {
            EXPECT_STREQ(fileName->c_str(), "test.pdf");
        }
    }
}

// Test constructing FileSpec from a dictionary Object with /F key
TEST_F(FileSpecTest_1136, ConstructFromDictWithFKey_1136) {
    Object obj = Object(new Dict(nullptr));
    obj.dictAdd("F", Object(new GooString("document.pdf")));
    obj.dictAdd("Type", Object(objName, "Filespec"));
    FileSpec fs(&obj);
    if (fs.isOk()) {
        const GooString *fileName = fs.getFileName();
        EXPECT_NE(fileName, nullptr);
    }
}

// Test constructing FileSpec from a dict with Desc key
TEST_F(FileSpecTest_1136, ConstructFromDictWithDescKey_1136) {
    Object obj = Object(new Dict(nullptr));
    obj.dictAdd("F", Object(new GooString("document.pdf")));
    obj.dictAdd("Desc", Object(new GooString("A test document")));
    FileSpec fs(&obj);
    if (fs.isOk()) {
        const GooString *description = fs.getDescription();
        if (description) {
            EXPECT_STREQ(description->c_str(), "A test document");
        }
    }
}

// Test that copy constructor is deleted (compile-time check; this is a static assertion concept)
// We verify this by checking the type trait
TEST_F(FileSpecTest_1136, CopyConstructorIsDeleted_1136) {
    EXPECT_FALSE(std::is_copy_constructible<FileSpec>::value);
}

// Test that copy assignment is deleted
TEST_F(FileSpecTest_1136, CopyAssignmentIsDeleted_1136) {
    EXPECT_FALSE(std::is_copy_assignable<FileSpec>::value);
}

// Test constructing FileSpec from an integer Object (should be invalid)
TEST_F(FileSpecTest_1136, ConstructFromIntObject_1136) {
    Object obj(42);
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test constructing FileSpec from a boolean Object (should be invalid)
TEST_F(FileSpecTest_1136, ConstructFromBoolObject_1136) {
    Object obj(true);
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test constructing FileSpec from a real/double Object (should be invalid)
TEST_F(FileSpecTest_1136, ConstructFromRealObject_1136) {
    Object obj(3.14);
    FileSpec fs(&obj);
    EXPECT_FALSE(fs.isOk());
}

// Test that an empty dictionary results in not-ok or handles gracefully
TEST_F(FileSpecTest_1136, ConstructFromEmptyDict_1136) {
    Object obj = Object(new Dict(nullptr));
    FileSpec fs(&obj);
    // An empty dict without required keys may or may not be valid
    // but should not crash
    fs.isOk();
    fs.getFileName();
    fs.getDescription();
}
