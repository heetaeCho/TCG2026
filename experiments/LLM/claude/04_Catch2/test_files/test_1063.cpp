#include <gtest/gtest.h>
#include <string>
#include <utility>

// Include the Catch2 Clara header
#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Test helper: a derived class to expose protected constructors
template <typename T>
class TestableResultValue : public ResultValueBase<T> {
public:
    TestableResultValue(ResultType type) : ResultValueBase<T>(type) {}
    TestableResultValue(ResultType type, T const& value) : ResultValueBase<T>(type, value) {}
    TestableResultValue(ResultType type, T&& value) : ResultValueBase<T>(type, std::move(value)) {}
    TestableResultValue(TestableResultValue const& other) : ResultValueBase<T>(other) {}
    TestableResultValue(TestableResultValue&& other) : ResultValueBase<T>(std::move(other)) {}

    TestableResultValue& operator=(TestableResultValue const& other) {
        ResultValueBase<T>::operator=(other);
        return *this;
    }
    TestableResultValue& operator=(TestableResultValue&& other) {
        ResultValueBase<T>::operator=(std::move(other));
        return *this;
    }

    using ResultValueBase<T>::value;
};

class ResultValueBaseTest_1063 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction with Ok type and a value, then retrieve the value
TEST_F(ResultValueBaseTest_1063, ConstructWithOkAndValue_ReturnsValue_1063) {
    TestableResultValue<int> result(ResultType::Ok, 42);
    EXPECT_EQ(result.value(), 42);
}

// Test: Construction with Ok type and string value
TEST_F(ResultValueBaseTest_1063, ConstructWithOkAndStringValue_ReturnsString_1063) {
    std::string val = "hello";
    TestableResultValue<std::string> result(ResultType::Ok, val);
    EXPECT_EQ(result.value(), "hello");
}

// Test: Construction with Ok type and rvalue string
TEST_F(ResultValueBaseTest_1063, ConstructWithOkAndRvalueString_ReturnsString_1063) {
    TestableResultValue<std::string> result(ResultType::Ok, std::string("world"));
    EXPECT_EQ(result.value(), "world");
}

// Test: Move constructor preserves value when Ok
TEST_F(ResultValueBaseTest_1063, MoveConstructorPreservesValue_1063) {
    TestableResultValue<int> original(ResultType::Ok, 99);
    TestableResultValue<int> moved(std::move(original));
    EXPECT_EQ(moved.value(), 99);
}

// Test: Move constructor with string value
TEST_F(ResultValueBaseTest_1063, MoveConstructorWithString_1063) {
    TestableResultValue<std::string> original(ResultType::Ok, std::string("test_move"));
    TestableResultValue<std::string> moved(std::move(original));
    EXPECT_EQ(moved.value(), "test_move");
}

// Test: Copy constructor preserves value when Ok
TEST_F(ResultValueBaseTest_1063, CopyConstructorPreservesValue_1063) {
    TestableResultValue<int> original(ResultType::Ok, 55);
    TestableResultValue<int> copied(original);
    EXPECT_EQ(copied.value(), 55);
    EXPECT_EQ(original.value(), 55);
}

// Test: Copy assignment preserves value
TEST_F(ResultValueBaseTest_1063, CopyAssignmentPreservesValue_1063) {
    TestableResultValue<int> original(ResultType::Ok, 77);
    TestableResultValue<int> target(ResultType::Ok, 0);
    target = original;
    EXPECT_EQ(target.value(), 77);
    EXPECT_EQ(original.value(), 77);
}

// Test: Move assignment transfers value
TEST_F(ResultValueBaseTest_1063, MoveAssignmentTransfersValue_1063) {
    TestableResultValue<int> original(ResultType::Ok, 88);
    TestableResultValue<int> target(ResultType::Ok, 0);
    target = std::move(original);
    EXPECT_EQ(target.value(), 88);
}

// Test: Construction with LogicError type (no value stored)
TEST_F(ResultValueBaseTest_1063, ConstructWithLogicError_1063) {
    TestableResultValue<int> result(ResultType::LogicError);
    // Accessing value on a non-Ok result should throw or enforce error
    EXPECT_ANY_THROW(result.value());
}

// Test: Construction with RuntimeError type (no value stored)
TEST_F(ResultValueBaseTest_1063, ConstructWithRuntimeError_1063) {
    TestableResultValue<int> result(ResultType::RuntimeError);
    EXPECT_ANY_THROW(result.value());
}

// Test: Move from LogicError result
TEST_F(ResultValueBaseTest_1063, MoveConstructorFromLogicError_1063) {
    TestableResultValue<int> original(ResultType::LogicError);
    TestableResultValue<int> moved(std::move(original));
    EXPECT_ANY_THROW(moved.value());
}

// Test: Value with complex type (double)
TEST_F(ResultValueBaseTest_1063, ConstructWithDoubleValue_1063) {
    TestableResultValue<double> result(ResultType::Ok, 3.14);
    EXPECT_DOUBLE_EQ(result.value(), 3.14);
}

// Test: Value with zero
TEST_F(ResultValueBaseTest_1063, ConstructWithZeroValue_1063) {
    TestableResultValue<int> result(ResultType::Ok, 0);
    EXPECT_EQ(result.value(), 0);
}

// Test: Value with negative number
TEST_F(ResultValueBaseTest_1063, ConstructWithNegativeValue_1063) {
    TestableResultValue<int> result(ResultType::Ok, -42);
    EXPECT_EQ(result.value(), -42);
}

// Test: Value with empty string
TEST_F(ResultValueBaseTest_1063, ConstructWithEmptyString_1063) {
    TestableResultValue<std::string> result(ResultType::Ok, std::string(""));
    EXPECT_EQ(result.value(), "");
}

// Test: Multiple copies maintain independent values
TEST_F(ResultValueBaseTest_1063, MultipleCopiesIndependent_1063) {
    TestableResultValue<std::string> original(ResultType::Ok, std::string("original"));
    TestableResultValue<std::string> copy1(original);
    TestableResultValue<std::string> copy2(original);
    EXPECT_EQ(copy1.value(), "original");
    EXPECT_EQ(copy2.value(), "original");
    EXPECT_EQ(original.value(), "original");
}

// Test: Assign from Ok to Ok overwrites value
TEST_F(ResultValueBaseTest_1063, AssignOkToOkOverwritesValue_1063) {
    TestableResultValue<int> a(ResultType::Ok, 10);
    TestableResultValue<int> b(ResultType::Ok, 20);
    a = b;
    EXPECT_EQ(a.value(), 20);
}
