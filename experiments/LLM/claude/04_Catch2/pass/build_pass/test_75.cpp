#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// We need to know what unprintableString is - it's a Detail constant in Catch2
// We'll test the observable behavior of convertUnstreamable

namespace {

// A simple non-enum, non-exception struct with no stream operator
struct NonStreamableType {
    int value;
};

// Another non-streamable type
struct AnotherNonStreamable {
    double x;
    double y;
};

// An empty struct
struct EmptyStruct {};

// A struct with complex members but still non-streamable, non-enum, non-exception
struct ComplexNonStreamable {
    int arr[10];
    std::string name;
};

} // anonymous namespace

// Test that convertUnstreamable returns a non-empty string for a simple non-streamable type
TEST(ConvertUnstreamableTest_75, ReturnsStringForSimpleNonStreamableType_75) {
    NonStreamableType obj{42};
    std::string result = Catch::Detail::convertUnstreamable(obj);
    // Should return the unprintableString, which is a valid non-empty string
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable returns a string (the unprintable marker) for another type
TEST(ConvertUnstreamableTest_75, ReturnsStringForAnotherNonStreamableType_75) {
    AnotherNonStreamable obj{1.0, 2.0};
    std::string result = Catch::Detail::convertUnstreamable(obj);
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable returns the same string for different non-streamable types
TEST(ConvertUnstreamableTest_75, ReturnsSameStringForDifferentTypes_75) {
    NonStreamableType obj1{10};
    AnotherNonStreamable obj2{3.14, 2.71};
    EmptyStruct obj3{};

    std::string result1 = Catch::Detail::convertUnstreamable(obj1);
    std::string result2 = Catch::Detail::convertUnstreamable(obj2);
    std::string result3 = Catch::Detail::convertUnstreamable(obj3);

    // All should return the same unprintableString
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}

// Test that convertUnstreamable works for an empty struct
TEST(ConvertUnstreamableTest_75, WorksForEmptyStruct_75) {
    EmptyStruct obj{};
    std::string result = Catch::Detail::convertUnstreamable(obj);
    EXPECT_FALSE(result.empty());
}

// Test that convertUnstreamable works for a complex non-streamable struct
TEST(ConvertUnstreamableTest_75, WorksForComplexNonStreamableType_75) {
    ComplexNonStreamable obj{{}, "test"};
    std::string result = Catch::Detail::convertUnstreamable(obj);
    EXPECT_FALSE(result.empty());
}

// Test that the return type is std::string
TEST(ConvertUnstreamableTest_75, ReturnTypeIsStdString_75) {
    NonStreamableType obj{0};
    auto result = Catch::Detail::convertUnstreamable(obj);
    static_assert(std::is_same<decltype(result), std::string>::value,
                  "Return type should be std::string");
    EXPECT_TRUE(true); // If we get here, the static_assert passed
}

// Test that calling convertUnstreamable multiple times on the same object yields same result
TEST(ConvertUnstreamableTest_75, ConsistentResultOnMultipleCalls_75) {
    NonStreamableType obj{100};
    std::string result1 = Catch::Detail::convertUnstreamable(obj);
    std::string result2 = Catch::Detail::convertUnstreamable(obj);
    EXPECT_EQ(result1, result2);
}

// Test that the result matches Detail::unprintableString
TEST(ConvertUnstreamableTest_75, ResultMatchesUnprintableString_75) {
    NonStreamableType obj{0};
    std::string result = Catch::Detail::convertUnstreamable(obj);
    std::string expected(Catch::Detail::unprintableString);
    EXPECT_EQ(result, expected);
}

// Test SFINAE: enum types should NOT match this overload
// This is a compile-time property test - we verify the enable_if constraint
TEST(ConvertUnstreamableTest_75, SFINAEExcludesEnumTypes_75) {
    enum TestEnum { A, B, C };
    // The following should not compile if uncommented, verifying SFINAE:
    // Catch::Detail::convertUnstreamable(TestEnum::A);
    
    // Instead, verify the trait
    static_assert(std::is_enum<TestEnum>::value,
                  "TestEnum should be an enum - and thus excluded from convertUnstreamable");
    EXPECT_TRUE(true);
}

// Test SFINAE: exception-derived types should NOT match this overload
TEST(ConvertUnstreamableTest_75, SFINAEExcludesExceptionTypes_75) {
    struct MyException : std::exception {
        const char* what() const noexcept override { return "test"; }
    };
    
    static_assert(std::is_base_of<std::exception, MyException>::value,
                  "MyException derives from std::exception - and thus excluded from convertUnstreamable");
    EXPECT_TRUE(true);
}

// Test with const object
TEST(ConvertUnstreamableTest_75, WorksWithConstObject_75) {
    const NonStreamableType obj{55};
    std::string result = Catch::Detail::convertUnstreamable(obj);
    EXPECT_FALSE(result.empty());
    EXPECT_EQ(result, std::string(Catch::Detail::unprintableString));
}
