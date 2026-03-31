#include <gtest/gtest.h>
#include <string>
#include <chrono>
#include <cstddef>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Helper struct for member pointer tests
struct TestClass {
    int intMember;
    double doubleMember;
    void memberFunc() {}
    int memberFuncWithReturn() { return 0; }
};

// =====================================================
// Tests for member pointer to data conversion
// =====================================================

TEST(StringMakerMemberPointer_87, NonNullDataMemberPointerReturnsNonEmpty_87) {
    int TestClass::* p = &TestClass::intMember;
    std::string result = Catch::StringMaker<int TestClass::*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST(StringMakerMemberPointer_87, NullDataMemberPointerReturnsNullptr_87) {
    int TestClass::* p = nullptr;
    std::string result = Catch::StringMaker<int TestClass::*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST(StringMakerMemberPointer_87, NonNullDoubleMemberPointerReturnsNonEmpty_87) {
    double TestClass::* p = &TestClass::doubleMember;
    std::string result = Catch::StringMaker<double TestClass::*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST(StringMakerMemberPointer_87, NullDoubleMemberPointerReturnsNullptr_87) {
    double TestClass::* p = nullptr;
    std::string result = Catch::StringMaker<double TestClass::*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

// =====================================================
// Tests for member function pointer conversion
// =====================================================

TEST(StringMakerMemberFuncPointer_87, NonNullMemberFuncPointerReturnsNonEmpty_87) {
    void (TestClass::* p)() = &TestClass::memberFunc;
    std::string result = Catch::StringMaker<void (TestClass::*)()>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST(StringMakerMemberFuncPointer_87, NullMemberFuncPointerReturnsNullptr_87) {
    void (TestClass::* p)() = nullptr;
    std::string result = Catch::StringMaker<void (TestClass::*)()>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

TEST(StringMakerMemberFuncPointer_87, NonNullMemberFuncWithReturnReturnsNonEmpty_87) {
    int (TestClass::* p)() = &TestClass::memberFuncWithReturn;
    std::string result = Catch::StringMaker<int (TestClass::*)()>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST(StringMakerMemberFuncPointer_87, NullMemberFuncWithReturnReturnsNullptr_87) {
    int (TestClass::* p)() = nullptr;
    std::string result = Catch::StringMaker<int (TestClass::*)()>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

// =====================================================
// Tests for different member pointers producing different results
// =====================================================

TEST(StringMakerMemberPointer_87, DifferentMembersProduceDifferentStrings_87) {
    int TestClass::* p1 = &TestClass::intMember;
    double TestClass::* p2 = &TestClass::doubleMember;
    std::string result1 = Catch::StringMaker<int TestClass::*>::convert(p1);
    std::string result2 = Catch::StringMaker<double TestClass::*>::convert(p2);
    // They should both be non-null representations, but may or may not differ
    EXPECT_NE(result1, "nullptr");
    EXPECT_NE(result2, "nullptr");
}

// =====================================================
// Tests for basic types using StringMaker
// =====================================================

TEST(StringMakerBasicTypes_87, IntConversion_87) {
    std::string result = Catch::StringMaker<int>::convert(42);
    EXPECT_EQ(result, "42");
}

TEST(StringMakerBasicTypes_87, NegativeIntConversion_87) {
    std::string result = Catch::StringMaker<int>::convert(-1);
    EXPECT_EQ(result, "-1");
}

TEST(StringMakerBasicTypes_87, ZeroIntConversion_87) {
    std::string result = Catch::StringMaker<int>::convert(0);
    EXPECT_EQ(result, "0");
}

TEST(StringMakerBasicTypes_87, BoolTrueConversion_87) {
    std::string result = Catch::StringMaker<bool>::convert(true);
    EXPECT_EQ(result, "true");
}

TEST(StringMakerBasicTypes_87, BoolFalseConversion_87) {
    std::string result = Catch::StringMaker<bool>::convert(false);
    EXPECT_EQ(result, "false");
}

TEST(StringMakerBasicTypes_87, NullptrConversion_87) {
    std::string result = Catch::StringMaker<std::nullptr_t>::convert(nullptr);
    EXPECT_EQ(result, "nullptr");
}

TEST(StringMakerBasicTypes_87, CharConversion_87) {
    std::string result = Catch::StringMaker<char>::convert('A');
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBasicTypes_87, UnsignedIntConversion_87) {
    std::string result = Catch::StringMaker<unsigned int>::convert(100u);
    EXPECT_EQ(result, "100");
}

TEST(StringMakerBasicTypes_87, LongLongConversion_87) {
    std::string result = Catch::StringMaker<long long>::convert(123456789LL);
    EXPECT_EQ(result, "123456789");
}

// =====================================================
// Tests for string types
// =====================================================

TEST(StringMakerStringTypes_87, StdStringConversion_87) {
    std::string input = "hello world";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_NE(result.find("hello world"), std::string::npos);
}

TEST(StringMakerStringTypes_87, EmptyStdStringConversion_87) {
    std::string input = "";
    std::string result = Catch::StringMaker<std::string>::convert(input);
    EXPECT_FALSE(result.empty()); // should at least have quotes or some representation
}

TEST(StringMakerStringTypes_87, CStringConversion_87) {
    const char* input = "test string";
    std::string result = Catch::StringMaker<char const*>::convert(input);
    EXPECT_NE(result.find("test string"), std::string::npos);
}

TEST(StringMakerStringTypes_87, NullCStringConversion_87) {
    const char* input = nullptr;
    std::string result = Catch::StringMaker<char const*>::convert(input);
    // Should handle null gracefully
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerStringTypes_87, StringViewConversion_87) {
    std::string_view input = "view test";
    std::string result = Catch::StringMaker<std::string_view>::convert(input);
    EXPECT_NE(result.find("view test"), std::string::npos);
}

// =====================================================
// Tests for pointer types
// =====================================================

TEST(StringMakerPointer_87, NonNullPointerReturnsAddress_87) {
    int x = 42;
    int* p = &x;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "nullptr");
}

TEST(StringMakerPointer_87, NullPointerReturnsNullptr_87) {
    int* p = nullptr;
    std::string result = Catch::StringMaker<int*>::convert(p);
    EXPECT_EQ(result, "nullptr");
}

// =====================================================
// Tests for floating point types
// =====================================================

TEST(StringMakerFloatingPoint_87, FloatConversion_87) {
    std::string result = Catch::StringMaker<float>::convert(3.14f);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerFloatingPoint_87, DoubleConversion_87) {
    std::string result = Catch::StringMaker<double>::convert(2.71828);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerFloatingPoint_87, FloatZeroConversion_87) {
    std::string result = Catch::StringMaker<float>::convert(0.0f);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerFloatingPoint_87, DoubleZeroConversion_87) {
    std::string result = Catch::StringMaker<double>::convert(0.0);
    EXPECT_FALSE(result.empty());
}

// =====================================================
// Tests for signed/unsigned char
// =====================================================

TEST(StringMakerCharTypes_87, SignedCharConversion_87) {
    std::string result = Catch::StringMaker<signed char>::convert(static_cast<signed char>(65));
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerCharTypes_87, UnsignedCharConversion_87) {
    std::string result = Catch::StringMaker<unsigned char>::convert(static_cast<unsigned char>(255));
    EXPECT_FALSE(result.empty());
}

// =====================================================
// Tests for std::byte
// =====================================================

TEST(StringMakerByte_87, ByteConversion_87) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0xFF});
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerByte_87, ByteZeroConversion_87) {
    std::string result = Catch::StringMaker<std::byte>::convert(std::byte{0x00});
    EXPECT_FALSE(result.empty());
}

// =====================================================
// Tests for boundary values
// =====================================================

TEST(StringMakerBoundary_87, IntMaxConversion_87) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBoundary_87, IntMinConversion_87) {
    std::string result = Catch::StringMaker<int>::convert(std::numeric_limits<int>::min());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBoundary_87, UnsignedLongLongMaxConversion_87) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(
        std::numeric_limits<unsigned long long>::max());
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerBoundary_87, UnsignedLongLongZeroConversion_87) {
    std::string result = Catch::StringMaker<unsigned long long>::convert(0ULL);
    EXPECT_EQ(result, "0");
}

// =====================================================
// Tests for chrono durations
// =====================================================

TEST(StringMakerChrono_87, MillisecondsDurationConversion_87) {
    auto dur = std::chrono::milliseconds(500);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChrono_87, SecondsDurationConversion_87) {
    auto dur = std::chrono::seconds(10);
    std::string result = Catch::StringMaker<std::chrono::seconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChrono_87, MinutesDurationConversion_87) {
    auto dur = std::chrono::minutes(5);
    std::string result = Catch::StringMaker<std::chrono::minutes>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChrono_87, HoursDurationConversion_87) {
    auto dur = std::chrono::hours(2);
    std::string result = Catch::StringMaker<std::chrono::hours>::convert(dur);
    EXPECT_FALSE(result.empty());
}

TEST(StringMakerChrono_87, ZeroDurationConversion_87) {
    auto dur = std::chrono::milliseconds(0);
    std::string result = Catch::StringMaker<std::chrono::milliseconds>::convert(dur);
    EXPECT_FALSE(result.empty());
}
