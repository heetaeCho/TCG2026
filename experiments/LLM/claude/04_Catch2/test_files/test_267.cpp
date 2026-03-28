#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include the Catch2 headers needed
#include "catch2/catch_tostring.hpp"

class StringMakerWcharPtrTest_267 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Non-null wchar_t* string converts to a non-empty result
TEST_F(StringMakerWcharPtrTest_267, NonNullWcharPtrReturnsStringifiedResult_267) {
    wchar_t str[] = L"hello";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    // The result should contain "hello" in some form (likely quoted)
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
}

// Test: Null wchar_t* returns "{null string}"
TEST_F(StringMakerWcharPtrTest_267, NullWcharPtrReturnsNullString_267) {
    wchar_t* str = nullptr;
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

// Test: Empty wchar_t* string (non-null but empty)
TEST_F(StringMakerWcharPtrTest_267, EmptyWcharPtrReturnsNonNullResult_267) {
    wchar_t str[] = L"";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
}

// Test: Single character wchar_t* string
TEST_F(StringMakerWcharPtrTest_267, SingleCharWcharPtrConverts_267) {
    wchar_t str[] = L"A";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
    // Should contain the character 'A' somewhere in the result
    EXPECT_NE(result.find('A'), std::string::npos);
}

// Test: wchar_t* with special characters
TEST_F(StringMakerWcharPtrTest_267, SpecialCharsWcharPtrConverts_267) {
    wchar_t str[] = L"test\nwith\ttabs";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
}

// Test: wchar_t* with spaces
TEST_F(StringMakerWcharPtrTest_267, SpacesWcharPtrConverts_267) {
    wchar_t str[] = L"hello world";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
}

// Test: Longer wchar_t* string
TEST_F(StringMakerWcharPtrTest_267, LongWcharPtrConverts_267) {
    wchar_t str[] = L"This is a longer string to test the conversion of wchar_t pointer";
    std::string result = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
}

// Test: Consistency - calling convert twice with the same input gives the same result
TEST_F(StringMakerWcharPtrTest_267, ConsistentResults_267) {
    wchar_t str[] = L"consistent";
    std::string result1 = Catch::StringMaker<wchar_t*>::convert(str);
    std::string result2 = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_EQ(result1, result2);
}

// Test: Consistency - null pointer gives same result on multiple calls
TEST_F(StringMakerWcharPtrTest_267, ConsistentNullResults_267) {
    wchar_t* str = nullptr;
    std::string result1 = Catch::StringMaker<wchar_t*>::convert(str);
    std::string result2 = Catch::StringMaker<wchar_t*>::convert(str);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, "{null string}");
}

// Test: The result for non-null should match what stringify(wstring) produces
// We can verify indirectly by comparing with wstring StringMaker
TEST_F(StringMakerWcharPtrTest_267, MatchesWstringConversion_267) {
    wchar_t str[] = L"match test";
    std::wstring wstr(str);
    std::string fromPtr = Catch::StringMaker<wchar_t*>::convert(str);
    std::string fromWstring = Catch::StringMaker<std::wstring>::convert(wstr);
    EXPECT_EQ(fromPtr, fromWstring);
}
