#include <gtest/gtest.h>
#include "Object.h"
#include "FileSpec.h"
#include "Dict.h"
#include "Array.h"

// Forward declaration
Object getFileSpecName(const Object *fileSpec);

class FileSpecTest_1986 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a minimal XRef-less Dict for testing
        // We need to create Dict objects for testing dictionary lookups
    }
};

// Test: When fileSpec is a string, it should return a copy of that string
TEST_F(FileSpecTest_1986, StringFileSpecReturnsString_1986) {
    Object strObj(std::string("test_file.pdf"));
    Object result = getFileSpecName(&strObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "test_file.pdf");
}

// Test: When fileSpec is a string with empty content
TEST_F(FileSpecTest_1986, EmptyStringFileSpecReturnsEmptyString_1986) {
    Object strObj(std::string(""));
    Object result = getFileSpecName(&strObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "");
}

// Test: When fileSpec is neither string nor dict, return None object
TEST_F(FileSpecTest_1986, NonStringNonDictReturnsNone_1986) {
    Object intObj(42);
    Object result = getFileSpecName(&intObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Null object returns None
TEST_F(FileSpecTest_1986, NullObjectReturnsNone_1986) {
    Object nullObj = Object::null();
    Object result = getFileSpecName(&nullObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Bool object returns None
TEST_F(FileSpecTest_1986, BoolObjectReturnsNone_1986) {
    Object boolObj(true);
    Object result = getFileSpecName(&boolObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Real object returns None
TEST_F(FileSpecTest_1986, RealObjectReturnsNone_1986) {
    Object realObj(3.14);
    Object result = getFileSpecName(&realObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Dict with "UF" key returns UF value
TEST_F(FileSpecTest_1986, DictWithUFReturnsUF_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(std::string("unicode_file.pdf")));
    dict->add("F", Object(std::string("fallback_file.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "unicode_file.pdf");
}

// Test: Dict without "UF" but with "F" returns F value
TEST_F(FileSpecTest_1986, DictWithFReturnsF_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("F", Object(std::string("file.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "file.pdf");
}

// Test: Dict without "UF" and "F" but with "DOS" returns DOS value
TEST_F(FileSpecTest_1986, DictWithDOSReturnsDOS_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("DOS", Object(std::string("dosfile.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "dosfile.pdf");
}

// Test: Dict with only "Mac" key returns Mac value
TEST_F(FileSpecTest_1986, DictWithMacReturnsMac_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("Mac", Object(std::string("macfile.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "macfile.pdf");
}

// Test: Dict with only "Unix" key returns Unix value
TEST_F(FileSpecTest_1986, DictWithUnixReturnsUnix_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("Unix", Object(std::string("unixfile.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "unixfile.pdf");
}

// Test: Dict with no recognized keys returns None
TEST_F(FileSpecTest_1986, DictWithNoRecognizedKeysReturnsNone_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("SomeOtherKey", Object(std::string("value")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Empty dict returns None
TEST_F(FileSpecTest_1986, EmptyDictReturnsNone_1986) {
    Dict *dict = new Dict(nullptr);
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Dict with "UF" as non-string (int) falls through to "F"
TEST_F(FileSpecTest_1986, DictWithNonStringUFFallsToF_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(42));
    dict->add("F", Object(std::string("fallback.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "fallback.pdf");
}

// Test: Dict with non-string UF and F falls through to DOS
TEST_F(FileSpecTest_1986, DictWithNonStringUFAndFFallsToDOS_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(42));
    dict->add("F", Object(100));
    dict->add("DOS", Object(std::string("dos_fallback.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "dos_fallback.pdf");
}

// Test: Dict where all keys are non-string returns None
TEST_F(FileSpecTest_1986, DictAllNonStringValuesReturnsNone_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(1));
    dict->add("F", Object(2));
    dict->add("DOS", Object(3));
    dict->add("Mac", Object(4));
    dict->add("Unix", Object(5));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    EXPECT_TRUE(result.isNone());
}

// Test: Priority - UF takes precedence over all others
TEST_F(FileSpecTest_1986, UFTakesPrecedenceOverAll_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("UF", Object(std::string("uf.pdf")));
    dict->add("F", Object(std::string("f.pdf")));
    dict->add("DOS", Object(std::string("dos.pdf")));
    dict->add("Mac", Object(std::string("mac.pdf")));
    dict->add("Unix", Object(std::string("unix.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "uf.pdf");
}

// Test: F takes precedence over DOS, Mac, Unix
TEST_F(FileSpecTest_1986, FTakesPrecedenceOverDOSMacUnix_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("F", Object(std::string("f.pdf")));
    dict->add("DOS", Object(std::string("dos.pdf")));
    dict->add("Mac", Object(std::string("mac.pdf")));
    dict->add("Unix", Object(std::string("unix.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "f.pdf");
}

// Test: DOS takes precedence over Mac and Unix
TEST_F(FileSpecTest_1986, DOSTakesPrecedenceOverMacUnix_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("DOS", Object(std::string("dos.pdf")));
    dict->add("Mac", Object(std::string("mac.pdf")));
    dict->add("Unix", Object(std::string("unix.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "dos.pdf");
}

// Test: Mac takes precedence over Unix
TEST_F(FileSpecTest_1986, MacTakesPrecedenceOverUnix_1986) {
    Dict *dict = new Dict(nullptr);
    dict->add("Mac", Object(std::string("mac.pdf")));
    dict->add("Unix", Object(std::string("unix.pdf")));
    Object dictObj(dict);
    Object result = getFileSpecName(&dictObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "mac.pdf");
}

// Test: None object returns None
TEST_F(FileSpecTest_1986, NoneObjectReturnsNone_1986) {
    Object noneObj;
    Object result = getFileSpecName(&noneObj);
    EXPECT_TRUE(result.isNone());
}

// Test: String with special characters
TEST_F(FileSpecTest_1986, StringWithSpecialCharsReturnsString_1986) {
    Object strObj(std::string("path/to/file with spaces & (special).pdf"));
    Object result = getFileSpecName(&strObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "path/to/file with spaces & (special).pdf");
}

// Test: String with unicode-like content
TEST_F(FileSpecTest_1986, StringWithUnicodeLikeContent_1986) {
    Object strObj(std::string("\xc3\xa9\xc3\xa0\xc3\xbc"));  // UTF-8 encoded éàü
    Object result = getFileSpecName(&strObj);
    ASSERT_TRUE(result.isString());
    EXPECT_STREQ(result.getString()->c_str(), "\xc3\xa9\xc3\xa0\xc3\xbc");
}
