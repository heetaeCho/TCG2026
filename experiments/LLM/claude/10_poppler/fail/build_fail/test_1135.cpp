#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "FileSpec.h"
#include "Object.h"
#include "PDFDoc.h"
#include "GlobalParams.h"

class FileSpecTest_1135 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

TEST_F(FileSpecTest_1135, ConstructFromNullObject_1135) {
    Object obj;
    obj.initNull();
    FileSpec fileSpec(&obj);
    EXPECT_FALSE(fileSpec.isOk());
}

TEST_F(FileSpecTest_1135, ConstructFromInvalidObject_1135) {
    Object obj;
    obj.initInt(42);
    FileSpec fileSpec(&obj);
    EXPECT_FALSE(fileSpec.isOk());
}

TEST_F(FileSpecTest_1135, ConstructFromStringObject_1135) {
    Object obj;
    obj = Object(new GooString("test_file.pdf"));
    FileSpec fileSpec(&obj);
    // A string object should be a valid simple file spec
    EXPECT_TRUE(fileSpec.isOk());
}

TEST_F(FileSpecTest_1135, GetFileNameFromStringSpec_1135) {
    Object obj;
    obj = Object(new GooString("test_document.pdf"));
    FileSpec fileSpec(&obj);
    ASSERT_TRUE(fileSpec.isOk());
    const GooString *name = fileSpec.getFileName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name->c_str(), "test_document.pdf");
}

TEST_F(FileSpecTest_1135, GetFileNameReturnsNullForInvalidSpec_1135) {
    Object obj;
    obj.initNull();
    FileSpec fileSpec(&obj);
    EXPECT_FALSE(fileSpec.isOk());
    const GooString *name = fileSpec.getFileName();
    EXPECT_EQ(name, nullptr);
}

TEST_F(FileSpecTest_1135, GetDescriptionForInvalidSpec_1135) {
    Object obj;
    obj.initNull();
    FileSpec fileSpec(&obj);
    EXPECT_FALSE(fileSpec.isOk());
    const GooString *desc = fileSpec.getDescription();
    EXPECT_EQ(desc, nullptr);
}

TEST_F(FileSpecTest_1135, ConstructFromDictWithUFKey_1135) {
    Object dict = Object(new Dict(nullptr));
    dict.dictAdd("Type", Object(objName, "Filespec"));
    dict.dictAdd("UF", Object(new GooString("unicode_file.pdf")));
    dict.dictAdd("F", Object(new GooString("fallback_file.pdf")));

    FileSpec fileSpec(&dict);
    if (fileSpec.isOk()) {
        const GooString *name = fileSpec.getFileName();
        ASSERT_NE(name, nullptr);
    }
}

TEST_F(FileSpecTest_1135, ConstructFromDictWithFKey_1135) {
    Object dict = Object(new Dict(nullptr));
    dict.dictAdd("Type", Object(objName, "Filespec"));
    dict.dictAdd("F", Object(new GooString("regular_file.pdf")));

    FileSpec fileSpec(&dict);
    if (fileSpec.isOk()) {
        const GooString *name = fileSpec.getFileName();
        ASSERT_NE(name, nullptr);
        EXPECT_STREQ(name->c_str(), "regular_file.pdf");
    }
}

TEST_F(FileSpecTest_1135, GetEmbeddedFileForSimpleStringSpec_1135) {
    Object obj;
    obj = Object(new GooString("simple_file.txt"));
    FileSpec fileSpec(&obj);
    ASSERT_TRUE(fileSpec.isOk());
    // A simple string spec typically has no embedded file
    EmbFile *embFile = fileSpec.getEmbeddedFile();
    // May or may not be null depending on implementation
    // Just ensure it doesn't crash
}

TEST_F(FileSpecTest_1135, GetFileNameForPlatformFromStringSpec_1135) {
    Object obj;
    obj = Object(new GooString("platform_file.pdf"));
    FileSpec fileSpec(&obj);
    ASSERT_TRUE(fileSpec.isOk());
    GooString *platformName = fileSpec.getFileNameForPlatform();
    // Should return a valid platform-specific filename
    if (platformName) {
        EXPECT_GT(platformName->getLength(), 0);
    }
}

TEST_F(FileSpecTest_1135, EmptyStringFileSpec_1135) {
    Object obj;
    obj = Object(new GooString(""));
    FileSpec fileSpec(&obj);
    // An empty string may or may not be considered valid
    if (fileSpec.isOk()) {
        const GooString *name = fileSpec.getFileName();
        ASSERT_NE(name, nullptr);
        EXPECT_EQ(name->getLength(), 0);
    }
}

TEST_F(FileSpecTest_1135, EmptyDictSpec_1135) {
    Object dict = Object(new Dict(nullptr));
    FileSpec fileSpec(&dict);
    // An empty dict with no filename keys should not be ok
    EXPECT_FALSE(fileSpec.isOk());
}

TEST_F(FileSpecTest_1135, ConstructFromBoolObject_1135) {
    Object obj;
    obj = Object(true);
    FileSpec fileSpec(&obj);
    EXPECT_FALSE(fileSpec.isOk());
}

TEST_F(FileSpecTest_1135, ConstructFromRealObject_1135) {
    Object obj;
    obj = Object(3.14);
    FileSpec fileSpec(&obj);
    EXPECT_FALSE(fileSpec.isOk());
}
