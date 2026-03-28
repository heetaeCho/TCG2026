#include <gtest/gtest.h>
#include <string>
#include <cstddef>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Test fixture
class StringMakerTest_86 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ==================== Pointer conversion tests ====================

TEST_F(StringMakerTest_86, ConvertNullPointerReturnsNullptr_86) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertNonNullIntPointerReturnsNonEmpty_86) {
    int value = 42;
    int* p = &value;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertNonNullCharPointerReturnsNonEmpty_86) {
    char value = 'A';
    char* p = &value;
    // Note: char* has a special overload for C-strings, but here we test the U* template
    // The behavior depends on which overload is selected
    std::string result = Catch::StringMaker<char*>::convert(p);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_86, ConvertNullVoidPointerReturnsNullptr_86) {
    void* p = nullptr;
    std::string result = Catch::StringMaker<void*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertNonNullVoidPointerReturnsNonEmpty_86) {
    int value = 10;
    void* p = &value;
    std::string result = Catch::StringMaker<void*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertNullDoublePointerReturnsNullptr_86) {
    double* p = nullptr;
    std::string result = Catch::StringMaker<double*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertNonNullDoublePointerReturnsNonEmpty_86) {
    double value = 3.14;
    double* p = &value;
    std::string result = Catch::StringMaker<double*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

// ==================== nullptr_t conversion tests ====================

TEST_F(StringMakerTest_86, ConvertNullptrTReturnsNullptr_86) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_EQ(result, "nullptr");
}

// ==================== Bool conversion tests ====================

TEST_F(StringMakerTest_86, ConvertBoolTrueReturnsTrue_86) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST_F(StringMakerTest_86, ConvertBoolFalseReturnsFalse_86) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

// ==================== Integer conversion tests ====================

TEST_F(StringMakerTest_86, ConvertIntZero_86) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST_F(StringMakerTest_86, ConvertIntPositive_86) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_86, ConvertIntNegative_86) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST_F(StringMakerTest_86, ConvertLong_86) {
    std::string result = Catch::StringMaker<long>::convert(100L);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerTest_86, ConvertLongLong_86) {
    std::string result = Catch::StringMaker<long long>::convert(123456789LL);
    EXPECT_EQ(result, "123456789");
}

TEST_F(StringMakerTest_86, ConvertUnsignedInt_86) {
    std::string result = Catch::StringMaker<unsigned int>::convert(42u);
    EXPECT_EQ(result, "42");
}

TEST_F(StringMakerTest_86, ConvertUnsignedLong_86) {
    std::string result = Catch::StringMaker<unsigned long>::convert(100UL);
    EXPECT_EQ(result, "100");
}

TEST_F(StringMakerTest_86, ConvertUnsignedLongLong_86) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(999ULL);
    EXPECT_EQ(result, "999");
}

// ==================== Char conversion tests ====================

TEST_F(StringMakerTest_86, ConvertCharA_86) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
    // Should contain the character 'A' in some representation
    EXPECT_NE(result.find('A'), std::string::npos);
}

TEST_F(StringMakerTest_86, ConvertSignedChar_86) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_86, ConvertUnsignedChar_86) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(65));
    EXPECT_FALSE(result.empty());
}

// ==================== Float/Double conversion tests ====================

TEST_F(StringMakerTest_86, ConvertFloat_86) {
    std::string result = Catch::StringMaker<float>::convert(1.5f);
    EXPECT_FALSE(result.empty());
    // Should contain "1.5" in some form
    EXPECT_NE(result.find("1.5"), std::string::npos);
}

TEST_F(StringMakerTest_86, ConvertDouble_86) {
    std::string result = Catch::StringMaker<double>::convert(3.14);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_86, ConvertDoubleZero_86) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

// ==================== String conversion tests ====================

TEST_F(StringMakerTest_86, ConvertStdString_86) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST_F(StringMakerTest_86, ConvertEmptyStdString_86) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    // Should produce some representation of empty string (e.g., "\"\"")
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_86, ConvertStringView_86) {
    std::string_view sv = "test string";
    std::string result = Catch::StringMaker<std::string_view>::convert(sv);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST_F(StringMakerTest_86, ConvertConstCharPointerString_86) {
    const char* str = "abc";
    std::string result = Catch::StringMaker<char const*>::convert(str);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result.find("abc"), std::string::npos);
}

TEST_F(StringMakerTest_86, ConvertNullConstCharPointer_86) {
    const char* str = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(str);
    // Should handle null gracefully
    EXPECT_FALSE(result.empty());
}

// ==================== Struct/Class pointer tests ====================

TEST_F(StringMakerTest_86, ConvertStructPointerNull_86) {
    struct MyStruct { int x; };
    MyStruct* p = nullptr;
    std::string result = Catch::StringMaker<MyStruct*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertStructPointerNonNull_86) {
    struct MyStruct { int x; };
    MyStruct s{42};
    MyStruct* p = &s;
    std::string result = Catch::StringMaker<MyStruct*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

// ==================== Const pointer tests ====================

TEST_F(StringMakerTest_86, ConvertConstIntPointerNull_86) {
    const int* p = nullptr;
    std::string result = Catch::StringMaker<const int*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST_F(StringMakerTest_86, ConvertConstIntPointerNonNull_86) {
    const int value = 99;
    const int* p = &value;
    std::string result = Catch::StringMaker<const int*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

// ==================== Two different non-null pointers produce different strings ====================

TEST_F(StringMakerTest_86, TwoDifferentPointersProduceDifferentStrings_86) {
    int a = 1;
    int b = 2;
    std::string resultA = Catch::StringMaker<int*>::convert(&a);
    std::string resultB = Catch::StringMaker<int*>::convert(&b);
    // Two different addresses should generally produce different strings
    // (unless they happen to be at the same address, which shouldn't happen for stack vars)
    EXPECT_NE(resultA, resultB);
}

// ==================== Same pointer produces same string ====================

TEST_F(StringMakerTest_86, SamePointerProducesSameString_86) {
    int a = 1;
    std::string result1 = Catch::StringMaker<int*>::convert(&a);
    std::string result2 = Catch::StringMaker<int*>::convert(&a);
    EXPECT_EQ(result1, result2);
}

// ==================== std::byte conversion test ====================

TEST_F(StringMakerTest_86, ConvertStdByte_86) {
    std::byte b{0xFF};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

TEST_F(StringMakerTest_86, ConvertStdByteZero_86) {
    std::byte b{0x00};
    std::string result = Catch::StringMaker<std::byte>::convert(b);
    EXPECT_FALSE(result.empty());
}

// ==================== Edge cases for integers ====================

TEST_F(StringMakerTest_86, ConvertIntMaxValue_86) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::max()));
}

TEST_F(StringMakerTest_86, ConvertIntMinValue_86) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<int>::min()));
}

TEST_F(StringMakerTest_86, ConvertUnsignedIntMaxValue_86) {
    std::string result = Catch::StringMaker<unsigned int>::convert(std::numeric_limits<unsigned int>::max());
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::to_string(std::numeric_limits<unsigned int>::max()));
}
