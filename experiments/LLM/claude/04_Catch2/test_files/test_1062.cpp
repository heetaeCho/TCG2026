#include <gtest/gtest.h>
#include <string>

// Include the header under test
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Test helper: a derived class to expose protected constructors for testing
template <typename T>
class TestableResultValue : public ResultValueBase<T> {
public:
    // Expose constructors
    TestableResultValue(ResultType type) : ResultValueBase<T>(type) {}
    TestableResultValue(ResultType type, T const& value) : ResultValueBase<T>(type, value) {}
    TestableResultValue(ResultType type, T&& value) : ResultValueBase<T>(type, std::move(value)) {}
    
    // Use default copy/move
    TestableResultValue(TestableResultValue const& other) = default;
    TestableResultValue(TestableResultValue&& other) = default;
    TestableResultValue& operator=(TestableResultValue const& other) = default;
    TestableResultValue& operator=(TestableResultValue&& other) = default;
    
    ~TestableResultValue() override = default;
};

// Test fixture
class ResultValueBaseTest_1062 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Constructing with Ok type and a value, then reading value back
TEST_F(ResultValueBaseTest_1062, ConstructWithOkAndValue_ReturnsValue_1062) {
    TestableResultValue<int> result(ResultType::Ok, 42);
    EXPECT_EQ(result.value(), 42);
}

// Test: Copy constructor with Ok type preserves the value
TEST_F(ResultValueBaseTest_1062, CopyConstructorOk_CopiesValue_1062) {
    TestableResultValue<int> original(ResultType::Ok, 99);
    TestableResultValue<int> copy(original);
    EXPECT_EQ(copy.value(), 99);
}

// Test: Copy constructor with string value
TEST_F(ResultValueBaseTest_1062, CopyConstructorOk_CopiesStringValue_1062) {
    TestableResultValue<std::string> original(ResultType::Ok, std::string("hello"));
    TestableResultValue<std::string> copy(original);
    EXPECT_EQ(copy.value(), "hello");
}

// Test: Move constructor with Ok type preserves the value
TEST_F(ResultValueBaseTest_1062, MoveConstructorOk_MovesValue_1062) {
    TestableResultValue<std::string> original(ResultType::Ok, std::string("world"));
    TestableResultValue<std::string> moved(std::move(original));
    EXPECT_EQ(moved.value(), "world");
}

// Test: Constructing with Ok type and rvalue reference
TEST_F(ResultValueBaseTest_1062, ConstructWithOkAndRvalue_ReturnsValue_1062) {
    std::string s = "test_string";
    TestableResultValue<std::string> result(ResultType::Ok, std::move(s));
    EXPECT_EQ(result.value(), "test_string");
}

// Test: Constructing with LogicError type (no value stored)
TEST_F(ResultValueBaseTest_1062, ConstructWithLogicError_NoValue_1062) {
    TestableResultValue<int> result(ResultType::LogicError);
    // Accessing value() on an error result should not return a valid value
    // or might throw/enforce - we just verify construction doesn't crash
    SUCCEED();
}

// Test: Constructing with RuntimeError type
TEST_F(ResultValueBaseTest_1062, ConstructWithRuntimeError_NoValue_1062) {
    TestableResultValue<int> result(ResultType::RuntimeError);
    SUCCEED();
}

// Test: Copy constructor with error type does not attempt to copy a value
TEST_F(ResultValueBaseTest_1062, CopyConstructorError_DoesNotCopyValue_1062) {
    TestableResultValue<int> original(ResultType::LogicError);
    TestableResultValue<int> copy(original);
    // Should not crash - value was never constructed
    SUCCEED();
}

// Test: Copy assignment with Ok type
TEST_F(ResultValueBaseTest_1062, CopyAssignmentOk_CopiesValue_1062) {
    TestableResultValue<int> original(ResultType::Ok, 55);
    TestableResultValue<int> target(ResultType::Ok, 0);
    target = original;
    EXPECT_EQ(target.value(), 55);
}

// Test: Move assignment with Ok type
TEST_F(ResultValueBaseTest_1062, MoveAssignmentOk_MovesValue_1062) {
    TestableResultValue<std::string> original(ResultType::Ok, std::string("moved"));
    TestableResultValue<std::string> target(ResultType::Ok, std::string("initial"));
    target = std::move(original);
    EXPECT_EQ(target.value(), "moved");
}

// Test: Value with complex type
TEST_F(ResultValueBaseTest_1062, ConstructWithComplexType_ReturnsCorrectValue_1062) {
    std::vector<int> vec = {1, 2, 3, 4, 5};
    TestableResultValue<std::vector<int>> result(ResultType::Ok, vec);
    EXPECT_EQ(result.value().size(), 5u);
    EXPECT_EQ(result.value()[0], 1);
    EXPECT_EQ(result.value()[4], 5);
}

// Test: Copy of complex type preserves all elements
TEST_F(ResultValueBaseTest_1062, CopyConstructorComplexType_PreservesAllElements_1062) {
    std::vector<int> vec = {10, 20, 30};
    TestableResultValue<std::vector<int>> original(ResultType::Ok, vec);
    TestableResultValue<std::vector<int>> copy(original);
    EXPECT_EQ(copy.value(), vec);
}

// Test: Boundary - empty string value
TEST_F(ResultValueBaseTest_1062, ConstructWithEmptyString_ReturnsEmptyString_1062) {
    TestableResultValue<std::string> result(ResultType::Ok, std::string(""));
    EXPECT_EQ(result.value(), "");
}

// Test: Boundary - zero integer value
TEST_F(ResultValueBaseTest_1062, ConstructWithZeroInt_ReturnsZero_1062) {
    TestableResultValue<int> result(ResultType::Ok, 0);
    EXPECT_EQ(result.value(), 0);
}

// Test: Boundary - negative integer value
TEST_F(ResultValueBaseTest_1062, ConstructWithNegativeInt_ReturnsNegative_1062) {
    TestableResultValue<int> result(ResultType::Ok, -1);
    EXPECT_EQ(result.value(), -1);
}

// Test: value() returns const reference
TEST_F(ResultValueBaseTest_1062, ValueReturnsConstRef_1062) {
    TestableResultValue<int> result(ResultType::Ok, 42);
    const int& ref = result.value();
    EXPECT_EQ(ref, 42);
}

// Test: Multiple copies maintain independent values
TEST_F(ResultValueBaseTest_1062, MultipleCopiesAreIndependent_1062) {
    TestableResultValue<int> original(ResultType::Ok, 100);
    TestableResultValue<int> copy1(original);
    TestableResultValue<int> copy2(original);
    EXPECT_EQ(copy1.value(), 100);
    EXPECT_EQ(copy2.value(), 100);
}
