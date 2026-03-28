#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "./TestProjects/poppler/poppler/FileSpec.h"
#include "./TestProjects/poppler/poppler/Object.h"
#include "./TestProjects/poppler/poppler/Error.h"

// Mock dependencies if needed
class MockObject : public Object {
public:
    MOCK_METHOD(bool, isString, (), (const, override));
    MOCK_METHOD(Object, dictLookup, (std::string_view key, int recursion), (const, override));
    MOCK_METHOD(bool, isDict, (std::string_view dictType), (const, override));
    MOCK_METHOD(std::unique_ptr<GooString>, getString, (), (const, override));
};

// Test case 1: Normal operation with a valid string type
TEST_F(FileSpecTest_1987, getFileSpecNameForPlatform_ValidString_1987) {
    MockObject fileSpec;
    EXPECT_CALL(fileSpec, isString()).WillOnce(testing::Return(true));
    EXPECT_CALL(fileSpec, copy()).WillOnce(testing::Return(fileSpec));

    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
}

// Test case 2: Normal operation with a valid dictionary type containing "UF"
TEST_F(FileSpecTest_1988, getFileSpecNameForPlatform_ValidDictWithUF_1988) {
    MockObject fileSpec;
    MockObject dictValue;
    
    EXPECT_CALL(fileSpec, isDict("UF")).WillOnce(testing::Return(true));
    EXPECT_CALL(fileSpec, dictLookup("UF", 0)).WillOnce(testing::Return(dictValue));
    EXPECT_CALL(dictValue, isString()).WillOnce(testing::Return(true));

    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
}

// Test case 3: Normal operation with a dictionary containing "F" (fallback case)
TEST_F(FileSpecTest_1989, getFileSpecNameForPlatform_ValidDictWithF_1989) {
    MockObject fileSpec;
    MockObject dictValue;
    
    EXPECT_CALL(fileSpec, isDict("F")).WillOnce(testing::Return(true));
    EXPECT_CALL(fileSpec, dictLookup("F", 0)).WillOnce(testing::Return(dictValue));
    EXPECT_CALL(dictValue, isString()).WillOnce(testing::Return(true));

    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
}

// Test case 4: Invalid dictionary type, neither "UF" nor "F", expecting error
TEST_F(FileSpecTest_1990, getFileSpecNameForPlatform_InvalidDict_1990) {
    MockObject fileSpec;

    EXPECT_CALL(fileSpec, isDict("UF")).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict("F")).WillOnce(testing::Return(false));

    EXPECT_CALL(fileSpec, dictLookup("UF", 0)).Times(0);
    EXPECT_CALL(fileSpec, dictLookup("F", 0)).Times(0);

    EXPECT_CALL(fileSpec, dictLookup("DOS", 0)).Times(0);
    EXPECT_CALL(fileSpec, dictLookup("Unix", 0)).Times(0);
    
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isError());
}

// Test case 5: Platform-specific handling for Windows
TEST_F(FileSpecTest_1991, getFileSpecNameForPlatform_WindowsPlatform_1991) {
#ifdef _WIN32
    MockObject fileSpec;
    MockObject dictValue;

    EXPECT_CALL(fileSpec, isDict("UF")).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict("F")).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, dictLookup("UF", 0)).Times(0);
    EXPECT_CALL(fileSpec, dictLookup("F", 0)).Times(0);
    EXPECT_CALL(fileSpec, dictLookup("DOS", 0)).WillOnce(testing::Return(dictValue));
    EXPECT_CALL(dictValue, isString()).WillOnce(testing::Return(true));

    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
#endif
}

// Test case 6: Platform-specific handling for Unix
TEST_F(FileSpecTest_1992, getFileSpecNameForPlatform_UnixPlatform_1992) {
#ifndef _WIN32
    MockObject fileSpec;
    MockObject dictValue;

    EXPECT_CALL(fileSpec, isDict("UF")).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict("F")).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, dictLookup("UF", 0)).Times(0);
    EXPECT_CALL(fileSpec, dictLookup("F", 0)).Times(0);
    EXPECT_CALL(fileSpec, dictLookup("Unix", 0)).WillOnce(testing::Return(dictValue));
    EXPECT_CALL(dictValue, isString()).WillOnce(testing::Return(true));

    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
#endif
}

// Test case 7: Invalid file spec (not a string or dict)
TEST_F(FileSpecTest_1993, getFileSpecNameForPlatform_InvalidFileSpecType_1993) {
    MockObject fileSpec;

    EXPECT_CALL(fileSpec, isString()).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict("UF")).WillOnce(testing::Return(false));
    EXPECT_CALL(fileSpec, isDict("F")).WillOnce(testing::Return(false));

    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isError());
}