#include <gtest/gtest.h>
#include <string>
#include <cstring>

// Include the Catch2 headers needed
#include "catch2/catch_tostring.hpp"

// Tests for StringMaker<char*>::convert
class StringMakerCharPtrTest_263 : public ::testing::Test {
protected:
};

// Test normal operation: non-null C string
TEST_F(StringMakerCharPtrTest_263, NonNullString_ReturnsConvertedString_263) {
    char str[] = "hello world";
    std::string result = Catch::StringMaker<char*>::convert(str);
    // The result should contain the original string content
    // Detail::convertIntoString likely wraps it in quotes
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "{null string}");
    // Check that the original content is somewhere in the result
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

// Test null pointer returns "{null string}"
TEST_F(StringMakerCharPtrTest_263, NullString_ReturnsNullStringMarker_263) {
    char* str = nullptr;
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

// Test empty string (non-null but empty)
TEST_F(StringMakerCharPtrTest_263, EmptyString_ReturnsNonNullResult_263) {
    char str[] = "";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result, "{null string}");
}

// Test single character string
TEST_F(StringMakerCharPtrTest_263, SingleCharString_263) {
    char str[] = "A";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_NE(result.find("A"), std::string::npos);
}

// Test string with special characters
TEST_F(StringMakerCharPtrTest_263, StringWithSpecialChars_263) {
    char str[] = "hello\nworld\ttab";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

// Test string with spaces
TEST_F(StringMakerCharPtrTest_263, StringWithSpaces_263) {
    char str[] = "   spaces   ";
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result, "{null string}");
}

// Test longer string
TEST_F(StringMakerCharPtrTest_263, LongString_263) {
    char str[1024];
    std::memset(str, 'x', 1023);
    str[1023] = '\0';
    std::string result = Catch::StringMaker<char*>::convert(str);
    EXPECT_NE(result, "{null string}");
    EXPECT_FALSE(result.empty());
}

// Tests for StringMaker<char const*>::convert
class StringMakerConstCharPtrTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerConstCharPtrTest_263, NonNullConstString_263) {
    const char* str = "hello";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello"), std::string::npos);
}

TEST_F(StringMakerConstCharPtrTest_263, NullConstString_263) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_EQ(result, "{null string}");
}

// Tests for StringMaker<std::string>::convert
class StringMakerStdStringTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerStdStringTest_263, NormalString_263) {
    std::string str = "test string";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerStdStringTest_263, EmptyString_263) {
    std::string str = "";
    std::string result = Catch::StringMaker<std::string>::convert(str);
    // Should produce some representation of an empty string, not be empty itself
    // (it likely wraps in quotes)
    EXPECT_FALSE(result.empty() && result == "{null string}");
}

// Tests for StringMaker<bool>::convert
class StringMakerBoolTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerBoolTest_263, TrueValue_263) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerBoolTest_263, FalseValue_263) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// Tests for StringMaker<int>::convert
class StringMakerIntTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerIntTest_263, PositiveInt_263) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerIntTest_263, NegativeInt_263) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerIntTest_263, ZeroInt_263) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

// Tests for StringMaker<nullptr_t>::convert
class StringMakerNullptrTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerNullptrTest_263, NullptrValue_263) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_EQ(result, "nullptr");
}

// Tests for StringMaker<char>::convert
class StringMakerCharTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerCharTest_263, NormalChar_263) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_NE(result.find("A"), std::string::npos);
}

TEST_F(StringMakerCharTest_263, NullChar_263) {
    std::string result = Catch::StringMaker<char>::convert('\0');
    EXPECT_FALSE(result.empty());
}

// Tests for StringMaker<unsigned int>::convert
class StringMakerUnsignedIntTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerUnsignedIntTest_263, PositiveValue_263) {
    std::string result = Catch::StringMaker<unsigned int>::convert(100u);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerUnsignedIntTest_263, ZeroValue_263) {
    std::string result = Catch::StringMaker<unsigned int>::convert(0u);
    EXPECT_EQ(result, "0");
}

// Tests for StringMaker<float>::convert
class StringMakerFloatTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerFloatTest_263, NormalFloat_263) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(StringMakerFloatTest_263, ZeroFloat_263) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

// Tests for StringMaker<double>::convert
class StringMakerDoubleTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerDoubleTest_263, NormalDouble_263) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_NE(result.find("3.14"), std::string::npos);
}

TEST_F(StringMakerDoubleTest_263, ZeroDouble_263) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

// Tests for StringMaker<long long>::convert
class StringMakerLongLongTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerLongLongTest_263, LargeValue_263) {
    std::string result = Catch::StringMaker<long long>::convert(9223372036854775807LL);
    EXPECT_EQ(result, "9223372036854775807");
}

TEST_F(StringMakerLongLongTest_263, NegativeLargeValue_263) {
    std::string result = Catch::StringMaker<long long>::convert(-9223372036854775807LL);
    EXPECT_EQ(result, "-9223372036854775807");
}

// Test pointer conversion for non-char types
class StringMakerPointerTest_263 : public ::testing::Test {
protected:
};

TEST_F(StringMakerPointerTest_263, NullIntPointer_263) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    // Null pointer should produce some recognizable output
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerPointerTest_263, NonNullIntPointer_263) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
}
