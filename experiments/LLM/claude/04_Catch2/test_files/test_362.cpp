#include <gtest/gtest.h>
#include <string>
#include <utility>

#include "catch2/internal/catch_clara.hpp"

using namespace Catch::Clara::Detail;

// Test helper to access protected constructors of ResultValueBase<T>
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

class ResultValueBaseTest_362 : public ::testing::Test {};

// Test: Constructing with Ok type and a value allows retrieving the value
TEST_F(ResultValueBaseTest_362, ConstructWithOkAndValue_ReturnsValue_362) {
    TestableResultValue<int> result(ResultType::Ok, 42);
    EXPECT_EQ(result.value(), 42);
}

// Test: Constructing with Ok type and string value
TEST_F(ResultValueBaseTest_362, ConstructWithOkAndStringValue_ReturnsValue_362) {
    std::string str = "hello";
    TestableResultValue<std::string> result(ResultType::Ok, str);
    EXPECT_EQ(result.value(), "hello");
}

// Test: Constructing with Ok type and rvalue
TEST_F(ResultValueBaseTest_362, ConstructWithOkAndRvalue_ReturnsValue_362) {
    std::string str = "world";
    TestableResultValue<std::string> result(ResultType::Ok, std::move(str));
    EXPECT_EQ(result.value(), "world");
}

// Test: Copy construction preserves value
TEST_F(ResultValueBaseTest_362, CopyConstruction_PreservesValue_362) {
    TestableResultValue<int> original(ResultType::Ok, 99);
    TestableResultValue<int> copy(original);
    EXPECT_EQ(copy.value(), 99);
    EXPECT_EQ(original.value(), 99);
}

// Test: Move construction transfers value
TEST_F(ResultValueBaseTest_362, MoveConstruction_TransfersValue_362) {
    TestableResultValue<int> original(ResultType::Ok, 77);
    TestableResultValue<int> moved(std::move(original));
    EXPECT_EQ(moved.value(), 77);
}

// Test: Move assignment from Ok to Ok updates value
TEST_F(ResultValueBaseTest_362, MoveAssignment_OkToOk_UpdatesValue_362) {
    TestableResultValue<int> a(ResultType::Ok, 10);
    TestableResultValue<int> b(ResultType::Ok, 20);
    a = std::move(b);
    EXPECT_EQ(a.value(), 20);
}

// Test: Copy assignment from Ok to Ok updates value
TEST_F(ResultValueBaseTest_362, CopyAssignment_OkToOk_UpdatesValue_362) {
    TestableResultValue<int> a(ResultType::Ok, 10);
    TestableResultValue<int> b(ResultType::Ok, 30);
    a = b;
    EXPECT_EQ(a.value(), 30);
    EXPECT_EQ(b.value(), 30);
}

// Test: Move assignment with string type
TEST_F(ResultValueBaseTest_362, MoveAssignment_StringType_UpdatesValue_362) {
    TestableResultValue<std::string> a(ResultType::Ok, std::string("first"));
    TestableResultValue<std::string> b(ResultType::Ok, std::string("second"));
    a = std::move(b);
    EXPECT_EQ(a.value(), "second");
}

// Test: Constructing with LogicError type (no value)
TEST_F(ResultValueBaseTest_362, ConstructWithLogicError_362) {
    TestableResultValue<int> result(ResultType::LogicError);
    // Accessing value on a non-Ok result should throw or enforce
    EXPECT_ANY_THROW(result.value());
}

// Test: Constructing with RuntimeError type (no value)
TEST_F(ResultValueBaseTest_362, ConstructWithRuntimeError_362) {
    TestableResultValue<int> result(ResultType::RuntimeError);
    EXPECT_ANY_THROW(result.value());
}

// Test: Move assignment from Ok to error state
TEST_F(ResultValueBaseTest_362, MoveAssignment_ErrorToOk_362) {
    TestableResultValue<int> error(ResultType::LogicError);
    TestableResultValue<int> ok(ResultType::Ok, 55);
    error = std::move(ok);
    EXPECT_EQ(error.value(), 55);
}

// Test: Move assignment from error to Ok state
TEST_F(ResultValueBaseTest_362, MoveAssignment_OkToError_362) {
    TestableResultValue<int> ok(ResultType::Ok, 55);
    TestableResultValue<int> error(ResultType::LogicError);
    ok = std::move(error);
    EXPECT_ANY_THROW(ok.value());
}

// Test: Value with zero
TEST_F(ResultValueBaseTest_362, ConstructWithZeroValue_362) {
    TestableResultValue<int> result(ResultType::Ok, 0);
    EXPECT_EQ(result.value(), 0);
}

// Test: Value with negative number
TEST_F(ResultValueBaseTest_362, ConstructWithNegativeValue_362) {
    TestableResultValue<int> result(ResultType::Ok, -42);
    EXPECT_EQ(result.value(), -42);
}

// Test: Value with empty string
TEST_F(ResultValueBaseTest_362, ConstructWithEmptyString_362) {
    TestableResultValue<std::string> result(ResultType::Ok, std::string(""));
    EXPECT_EQ(result.value(), "");
}

// Test: Multiple assignments chain correctly
TEST_F(ResultValueBaseTest_362, MultipleAssignments_362) {
    TestableResultValue<int> a(ResultType::Ok, 1);
    TestableResultValue<int> b(ResultType::Ok, 2);
    TestableResultValue<int> c(ResultType::Ok, 3);
    a = std::move(b);
    EXPECT_EQ(a.value(), 2);
    a = std::move(c);
    EXPECT_EQ(a.value(), 3);
}

// Test: Copy preserves original after copy assignment
TEST_F(ResultValueBaseTest_362, CopyAssignment_OriginalUnchanged_362) {
    TestableResultValue<std::string> a(ResultType::Ok, std::string("original"));
    TestableResultValue<std::string> b(ResultType::Ok, std::string("replacement"));
    a = b;
    EXPECT_EQ(a.value(), "replacement");
    EXPECT_EQ(b.value(), "replacement");
}
