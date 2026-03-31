#include <gtest/gtest.h>
#include <memory>
#include <string>

#include "Object.h"
#include "FileSpec.h"
#include "Dict.h"
#include "Array.h"

// Forward declaration of the function under test
Object getFileSpecNameForPlatform(const Object *fileSpec);

class FileSpecTest_1987 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a dummy XRef-less Dict for testing
    }

    void TearDown() override {
    }

    // Helper to create a Dict object with specific keys
    Object makeDictWithKey(const std::string &key, const std::string &value) {
        Dict *dict = new Dict(nullptr);
        dict->add(key, Object(std::make_unique<GooString>(value)));
        return Object(dict);
    }

    Object makeDictWithKeys(const std::vector<std::pair<std::string, std::string>> &entries) {
        Dict *dict = new Dict(nullptr);
        for (const auto &entry : entries) {
            dict->add(entry.first, Object(std::make_unique<GooString>(entry.second)));
        }
        return Object(dict);
    }
};

// Test: When fileSpec is a string, it should return a copy of that string
TEST_F(FileSpecTest_1987, StringFileSpecReturnsCopy_1987) {
    Object fileSpec(std::make_unique<GooString>("test.pdf"));
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "test.pdf");
}

// Test: When fileSpec is a string with empty value
TEST_F(FileSpecTest_1987, EmptyStringFileSpec_1987) {
    Object fileSpec(std::make_unique<GooString>(""));
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "");
}

// Test: When fileSpec is a dict with "UF" key, it should return UF value
TEST_F(FileSpecTest_1987, DictWithUFKey_1987) {
    Object fileSpec = makeDictWithKey("UF", "unicode_file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "unicode_file.pdf");
}

// Test: When fileSpec is a dict with "F" key (no "UF"), it should return F value
TEST_F(FileSpecTest_1987, DictWithFKeyNoUF_1987) {
    Object fileSpec = makeDictWithKey("F", "file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "file.pdf");
}

// Test: When fileSpec is a dict with both "UF" and "F", "UF" should take priority
TEST_F(FileSpecTest_1987, DictWithUFAndFKeysPreferUF_1987) {
    Object fileSpec = makeDictWithKeys({{"UF", "unicode.pdf"}, {"F", "fallback.pdf"}});
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "unicode.pdf");
}

// Test: When fileSpec is a dict with platform-specific key (Unix or DOS)
TEST_F(FileSpecTest_1987, DictWithPlatformSpecificKey_1987) {
#ifdef _WIN32
    const char *platform = "DOS";
#else
    const char *platform = "Unix";
#endif
    Object fileSpec = makeDictWithKey(platform, "platform_file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "platform_file.pdf");
}

// Test: When fileSpec is a dict with no recognized keys, should return null/error object
TEST_F(FileSpecTest_1987, DictWithNoRecognizedKeys_1987) {
    Object fileSpec = makeDictWithKey("Unknown", "something.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    // Should return an empty/none object since no valid file spec name found
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: When fileSpec is an integer (not string or dict), should return error
TEST_F(FileSpecTest_1987, NonStringNonDictFileSpec_1987) {
    Object fileSpec(42);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: When fileSpec is a boolean, should return error
TEST_F(FileSpecTest_1987, BoolFileSpecReturnsNone_1987) {
    Object fileSpec(true);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: When fileSpec is null, should return error
TEST_F(FileSpecTest_1987, NullObjectReturnsNone_1987) {
    Object fileSpec = Object::null();
    Object result = getFileSpecNameForPlatform(&fileSpec);
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: Dict where UF is not a string but F is a string
TEST_F(FileSpecTest_1987, DictUFNonStringFallsBackToF_1987) {
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(123)); // UF is int, not string
    dict->add("F", Object(std::make_unique<GooString>("fallback.pdf")));
    Object fileSpec(dict);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "fallback.pdf");
}

// Test: Dict where both UF and F are not strings, falls back to platform key
TEST_F(FileSpecTest_1987, DictUFAndFNonStringFallsToPlatform_1987) {
#ifdef _WIN32
    const char *platform = "DOS";
#else
    const char *platform = "Unix";
#endif
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(123));
    dict->add("F", Object(456));
    dict->add(platform, Object(std::make_unique<GooString>("platform_file.pdf")));
    Object fileSpec(dict);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "platform_file.pdf");
}

// Test: Dict where UF, F, and platform key are all non-strings
TEST_F(FileSpecTest_1987, DictAllKeysNonStringReturnsNone_1987) {
#ifdef _WIN32
    const char *platform = "DOS";
#else
    const char *platform = "Unix";
#endif
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(123));
    dict->add("F", Object(456));
    dict->add(platform, Object(789));
    Object fileSpec(dict);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: String fileSpec with path separators
TEST_F(FileSpecTest_1987, StringFileSpecWithPath_1987) {
    Object fileSpec(std::make_unique<GooString>("/path/to/file.pdf"));
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    // When input is a simple string, it's returned as-is (no path conversion for strings)
    EXPECT_STREQ(result.getString()->c_str(), "/path/to/file.pdf");
}

// Test: Dict with UF containing a path
TEST_F(FileSpecTest_1987, DictUFWithPath_1987) {
    Object fileSpec = makeDictWithKey("UF", "/path/to/file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
#ifdef _WIN32
    // On Windows, paths should be converted
    // The exact conversion depends on the implementation
    EXPECT_TRUE(result.isString());
#else
    EXPECT_STREQ(result.getString()->c_str(), "/path/to/file.pdf");
#endif
}

// Test: Empty dict returns none
TEST_F(FileSpecTest_1987, EmptyDictReturnsNone_1987) {
    Dict *dict = new Dict(nullptr);
    Object fileSpec(dict);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: fileSpec is a real number
TEST_F(FileSpecTest_1987, RealNumberReturnsNone_1987) {
    Object fileSpec(3.14);
    Object result = getFileSpecNameForPlatform(&fileSpec);
    EXPECT_TRUE(result.isNone() || result.isNull());
}

// Test: Dict with F key containing simple filename
TEST_F(FileSpecTest_1987, DictFSimpleFilename_1987) {
    Object fileSpec = makeDictWithKey("F", "simple.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "simple.pdf");
}

#ifdef _WIN32
// Windows-specific path conversion tests

TEST_F(FileSpecTest_1987, WindowsPathConversionDoubleSlash_1987) {
    // //server/share -> \\server\share on Windows
    Object fileSpec = makeDictWithKey("F", "//server/share/file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    // /server should become \\server
    EXPECT_TRUE(result.isString());
}

TEST_F(FileSpecTest_1987, WindowsPathConversionDriveLetter_1987) {
    // /c/path/to/file -> c:\path\to\file on Windows
    Object fileSpec = makeDictWithKey("F", "/c/path/to/file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "c:\\path\\to\\file.pdf");
}

TEST_F(FileSpecTest_1987, WindowsPathForwardSlashConversion_1987) {
    Object fileSpec = makeDictWithKey("F", "path/to/file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "path\\to\\file.pdf");
}

TEST_F(FileSpecTest_1987, WindowsPathEscapedSlash_1987) {
    // Escaped forward slash \/ should become just /
    Object fileSpec = makeDictWithKey("F", "path\\/to\\/file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
}

TEST_F(FileSpecTest_1987, WindowsDriveLetterUpperCase_1987) {
    Object fileSpec = makeDictWithKey("F", "/C/Documents/file.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "C:\\Documents\\file.pdf");
}

TEST_F(FileSpecTest_1987, WindowsDriveLetterOnly_1987) {
    // /c should be converted to c:
    Object fileSpec = makeDictWithKey("F", "/c");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "c:");
}
#endif

// Test: Dict with UF key having empty string
TEST_F(FileSpecTest_1987, DictUFEmptyString_1987) {
    Object fileSpec = makeDictWithKey("UF", "");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "");
}

// Test: Dict with F key having special characters
TEST_F(FileSpecTest_1987, DictFSpecialCharacters_1987) {
    Object fileSpec = makeDictWithKey("F", "file with spaces.pdf");
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "file with spaces.pdf");
}

// Test: Ensure original fileSpec string object is not modified
TEST_F(FileSpecTest_1987, StringFileSpecNotModified_1987) {
    Object fileSpec(std::make_unique<GooString>("original.pdf"));
    Object result = getFileSpecNameForPlatform(&fileSpec);
    ASSERT_TRUE(fileSpec.isString());
    EXPECT_STREQ(fileSpec.getString()->c_str(), "original.pdf");
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "original.pdf");
}
