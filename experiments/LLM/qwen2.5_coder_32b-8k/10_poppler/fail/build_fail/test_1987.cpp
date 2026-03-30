#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"

#include "FileSpec.cc"



using namespace testing;



class FileSpecTest_1987 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_StringInput_1987) {

    Object fileSpec(Object(std::unique_ptr<GooString>(new GooString("testfile.txt"))));

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getString()->c_str(), "testfile.txt");

}



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_DictWithUF_1987) {

    Dict dict;

    dict.dictAdd("UF", Object(std::unique_ptr<GooString>(new GooString("userFriendly.txt"))));

    Object fileSpec(&dict);

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getString()->c_str(), "userFriendly.txt");

}



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_DictWithF_1987) {

    Dict dict;

    dict.dictAdd("F", Object(std::unique_ptr<GooString>(new GooString("filename.txt"))));

    Object fileSpec(&dict);

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getString()->c_str(), "filename.txt");

}



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_DictWithUnix_1987) {

    Dict dict;

#ifndef _WIN32

    dict.dictAdd("Unix", Object(std::unique_ptr<GooString>(new GooString("unixfile.txt"))));

#else

    dict.dictAdd("DOS", Object(std::unique_ptr<GooString>(new GooString("dosfile.txt"))));

#endif

    Object fileSpec(&dict);

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isString());

#ifndef _WIN32

    EXPECT_EQ(result.getString()->c_str(), "unixfile.txt");

#else

    EXPECT_EQ(result.getString()->c_str(), "dosfile.txt");

#endif

}



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_IllegalDictEntries_1987) {

    Dict dict;

    Object fileSpec(&dict);

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isNull());

}



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_EmptyObject_1987) {

    Object fileSpec;

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isNull());

}



#ifdef _WIN32

TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_WindowsPathConversion_1987) {

    Dict dict;

    dict.dictAdd("UF", Object(std::unique_ptr<GooString>(new GooString("/path/to/file.txt"))));

    Object fileSpec(&dict);

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getString()->c_str(), "\\path\\to\\file.txt");

}



TEST_F(FileSpecTest_1987, GetFileSpecNameForPlatform_WindowsPathConversionWithDriveLetter_1987) {

    Dict dict;

    dict.dictAdd("UF", Object(std::unique_ptr<GooString>(new GooString("/c/path/to/file.txt"))));

    Object fileSpec(&dict);

    Object result = getFileSpecNameForPlatform(&fileSpec);

    EXPECT_TRUE(result.isString());

    EXPECT_EQ(result.getString()->c_str(), "c:\\path\\to\\file.txt");

}

#endif
