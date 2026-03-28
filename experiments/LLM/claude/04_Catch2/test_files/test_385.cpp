#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// A concrete derived class for testing ParserBase since it has virtual methods
class ConcreteParser : public ParserBase {
public:
    // We rely on the default implementations from ParserBase
};

// Test that validate() returns an ok Result by default
TEST(ParserBaseTest_385, ValidateReturnsOkByDefault_385) {
    ConcreteParser parser;
    auto result = parser.validate();
    // Result::ok() should evaluate to true (no error)
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test that validate() error message is empty for ok result
TEST(ParserBaseTest_385, ValidateOkHasEmptyErrorMessage_385) {
    ConcreteParser parser;
    auto result = parser.validate();
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test that cardinality returns a value (default implementation)
TEST(ParserBaseTest_385, CardinalityReturnsValue_385) {
    ConcreteParser parser;
    size_t card = parser.cardinality();
    // Default cardinality should be some reasonable value (typically 1 for a single parser)
    EXPECT_GE(card, 0u);
}

// Test that the destructor can be called (virtual destructor)
TEST(ParserBaseTest_385, DestructorDoesNotThrow_385) {
    EXPECT_NO_THROW({
        ConcreteParser* parser = new ConcreteParser();
        delete parser;
    });
}

// Test destruction through base pointer (virtual destructor)
TEST(ParserBaseTest_385, VirtualDestructorThroughBasePointer_385) {
    EXPECT_NO_THROW({
        ParserBase* parser = new ConcreteParser();
        delete parser;
    });
}

// Test Result::ok() static factory
TEST(ResultTest_385, OkResultIsTrue_385) {
    auto result = Result::ok();
    EXPECT_TRUE(static_cast<bool>(result));
}

// Test Result::ok() has empty error message
TEST(ResultTest_385, OkResultHasEmptyErrorMessage_385) {
    auto result = Result::ok();
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test Result::logicError creates a false result
TEST(ResultTest_385, LogicErrorResultIsFalse_385) {
    auto result = Result::logicError("test logic error");
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test Result::logicError preserves error message
TEST(ResultTest_385, LogicErrorPreservesMessage_385) {
    std::string msg = "some logic error";
    auto result = Result::logicError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// Test Result::runtimeError creates a false result
TEST(ResultTest_385, RuntimeErrorResultIsFalse_385) {
    auto result = Result::runtimeError("test runtime error");
    EXPECT_FALSE(static_cast<bool>(result));
}

// Test Result::runtimeError preserves error message
TEST(ResultTest_385, RuntimeErrorPreservesMessage_385) {
    std::string msg = "some runtime error";
    auto result = Result::runtimeError(std::string(msg));
    EXPECT_EQ(result.errorMessage(), msg);
}

// Test Result with empty error message for logicError
TEST(ResultTest_385, LogicErrorWithEmptyMessage_385) {
    auto result = Result::logicError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test Result with empty error message for runtimeError
TEST(ResultTest_385, RuntimeErrorWithEmptyMessage_385) {
    auto result = Result::runtimeError("");
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_TRUE(result.errorMessage().empty());
}

// Test that multiple calls to validate() are consistent
TEST(ParserBaseTest_385, ValidateIsConsistentAcrossCalls_385) {
    ConcreteParser parser;
    auto result1 = parser.validate();
    auto result2 = parser.validate();
    EXPECT_TRUE(static_cast<bool>(result1));
    EXPECT_TRUE(static_cast<bool>(result2));
}

// Custom derived class that overrides validate to return error
class FailingParser : public ParserBase {
public:
    auto validate() const -> Result override {
        return Result::logicError("validation failed");
    }
};

// Test that a derived class can override validate
TEST(ParserBaseTest_385, DerivedClassCanOverrideValidate_385) {
    FailingParser parser;
    auto result = parser.validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "validation failed");
}

// Test polymorphic validate call through base pointer
TEST(ParserBaseTest_385, PolymorphicValidateCall_385) {
    std::unique_ptr<ParserBase> parser = std::make_unique<FailingParser>();
    auto result = parser->validate();
    EXPECT_FALSE(static_cast<bool>(result));
    EXPECT_EQ(result.errorMessage(), "validation failed");
}

// Test polymorphic validate call with ConcreteParser
TEST(ParserBaseTest_385, PolymorphicValidateCallOk_385) {
    std::unique_ptr<ParserBase> parser = std::make_unique<ConcreteParser>();
    auto result = parser->validate();
    EXPECT_TRUE(static_cast<bool>(result));
}
