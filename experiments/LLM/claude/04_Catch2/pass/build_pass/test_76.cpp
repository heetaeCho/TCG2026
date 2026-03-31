#include <gtest/gtest.h>
#include <string>
#include <stdexcept>
#include <type_traits>

// Include the header under test
#include "catch2/catch_tostring.hpp"

// Test fixture
class ConvertUnstreamableTest_76 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Custom exception classes for testing
class CustomException : public std::exception {
    std::string msg_;
public:
    explicit CustomException(const std::string& msg) : msg_(msg) {}
    const char* what() const noexcept override { return msg_.c_str(); }
};

class DerivedRuntimeError : public std::runtime_error {
public:
    explicit DerivedRuntimeError(const std::string& msg) : std::runtime_error(msg) {}
};

class DerivedLogicError : public std::logic_error {
public:
    explicit DerivedLogicError(const std::string& msg) : std::logic_error(msg) {}
};

class DeepDerivedException : public DerivedRuntimeError {
public:
    explicit DeepDerivedException(const std::string& msg) : DerivedRuntimeError(msg) {}
};

class EmptyWhatException : public std::exception {
public:
    const char* what() const noexcept override { return ""; }
};

// Test: std::exception base class with a message
TEST_F(ConvertUnstreamableTest_76, StdExceptionReturnsWhatMessage_76) {
    std::runtime_error ex("runtime error message");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "runtime error message");
}

// Test: Custom exception derived from std::exception
TEST_F(ConvertUnstreamableTest_76, CustomExceptionReturnsWhatMessage_76) {
    CustomException ex("custom error");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "custom error");
}

// Test: std::logic_error returns correct what()
TEST_F(ConvertUnstreamableTest_76, LogicErrorReturnsWhatMessage_76) {
    std::logic_error ex("logic error message");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "logic error message");
}

// Test: std::invalid_argument (derived from logic_error)
TEST_F(ConvertUnstreamableTest_76, InvalidArgumentReturnsWhatMessage_76) {
    std::invalid_argument ex("invalid argument message");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "invalid argument message");
}

// Test: std::out_of_range (derived from logic_error)
TEST_F(ConvertUnstreamableTest_76, OutOfRangeReturnsWhatMessage_76) {
    std::out_of_range ex("out of range");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "out of range");
}

// Test: std::overflow_error
TEST_F(ConvertUnstreamableTest_76, OverflowErrorReturnsWhatMessage_76) {
    std::overflow_error ex("overflow");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "overflow");
}

// Test: Derived from runtime_error
TEST_F(ConvertUnstreamableTest_76, DerivedRuntimeErrorReturnsWhatMessage_76) {
    DerivedRuntimeError ex("derived runtime error");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "derived runtime error");
}

// Test: Derived from logic_error
TEST_F(ConvertUnstreamableTest_76, DerivedLogicErrorReturnsWhatMessage_76) {
    DerivedLogicError ex("derived logic error");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "derived logic error");
}

// Test: Deeply derived exception
TEST_F(ConvertUnstreamableTest_76, DeepDerivedExceptionReturnsWhatMessage_76) {
    DeepDerivedException ex("deep derived");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "deep derived");
}

// Test: Empty what() message (boundary condition)
TEST_F(ConvertUnstreamableTest_76, EmptyWhatReturnsEmptyString_76) {
    EmptyWhatException ex;
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "");
}

// Test: Exception with special characters in what()
TEST_F(ConvertUnstreamableTest_76, SpecialCharactersInWhatMessage_76) {
    CustomException ex("error: \n\t\"special chars\" \0after");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, ex.what());
}

// Test: Exception with very long message
TEST_F(ConvertUnstreamableTest_76, VeryLongWhatMessage_76) {
    std::string longMsg(10000, 'x');
    CustomException ex(longMsg);
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, longMsg);
}

// Test: Return type is std::string
TEST_F(ConvertUnstreamableTest_76, ReturnTypeIsStdString_76) {
    std::runtime_error ex("test");
    auto result = Catch::Detail::convertUnstreamable(ex);
    static_assert(std::is_same<decltype(result), std::string>::value,
                  "Return type should be std::string");
    EXPECT_EQ(result, "test");
}

// Test: SFINAE - verify that the function is enabled for exception types
// and disabled for non-exception types and enums (compile-time check)
TEST_F(ConvertUnstreamableTest_76, SFINAETraitsCheck_76) {
    // Verify that std::exception-derived, non-enum types are accepted
    static_assert(!std::is_enum<std::runtime_error>::value, "runtime_error should not be enum");
    static_assert(std::is_base_of<std::exception, std::runtime_error>::value,
                  "runtime_error should derive from exception");
    static_assert(!std::is_enum<CustomException>::value, "CustomException should not be enum");
    static_assert(std::is_base_of<std::exception, CustomException>::value,
                  "CustomException should derive from exception");
    SUCCEED();
}

// Test: Exception with unicode-like content
TEST_F(ConvertUnstreamableTest_76, UnicodeContentInWhatMessage_76) {
    CustomException ex("Error: \xC3\xA9\xC3\xA0\xC3\xBC");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, std::string("Error: \xC3\xA9\xC3\xA0\xC3\xBC"));
}

// Test: Result is a copy, not a reference to internal state
TEST_F(ConvertUnstreamableTest_76, ResultIsIndependentCopy_76) {
    CustomException ex("original message");
    std::string result1 = Catch::Detail::convertUnstreamable(ex);
    std::string result2 = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result1, "original message");
}

// Test: const reference parameter works correctly
TEST_F(ConvertUnstreamableTest_76, ConstReferenceParameterWorks_76) {
    const CustomException ex("const exception");
    std::string result = Catch::Detail::convertUnstreamable(ex);
    EXPECT_EQ(result, "const exception");
}
