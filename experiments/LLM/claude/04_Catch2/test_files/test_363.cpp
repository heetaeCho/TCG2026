#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// Since ResultValueBase has mostly protected members, we need a derived class
// to test its behavior through the public interface.
// In Catch2's Clara, ParserResult and similar types expose this functionality.

namespace Catch {
namespace Clara {
namespace Detail {

// Helper derived class to expose protected functionality for testing
template <typename T>
class TestableResultValue : public ResultValueBase<T> {
public:
    // Construct with Ok type and a value
    TestableResultValue(T const& value)
        : ResultValueBase<T>(ResultType::Ok, value) {}

    // Construct with Ok type and an rvalue
    TestableResultValue(T&& value)
        : ResultValueBase<T>(ResultType::Ok, std::move(value)) {}

    // Construct with just a type (no value)
    explicit TestableResultValue(ResultType type)
        : ResultValueBase<T>(type) {}

    // Copy constructor
    TestableResultValue(TestableResultValue const& other)
        : ResultValueBase<T>(other) {}

    // Move constructor
    TestableResultValue(TestableResultValue&& other)
        : ResultValueBase<T>(std::move(other)) {}

    // Copy assignment
    TestableResultValue& operator=(TestableResultValue const& other) {
        ResultValueBase<T>::operator=(other);
        return *this;
    }

    // Move assignment
    TestableResultValue& operator=(TestableResultValue&& other) {
        ResultValueBase<T>::operator=(std::move(other));
        return *this;
    }

    using ResultValueBase<T>::value;
};

} // namespace Detail
} // namespace Clara
} // namespace Catch

using namespace Catch::Clara::Detail;

class ResultValueBaseTest_363 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that constructing with a value and Ok type stores the value correctly
TEST_F(ResultValueBaseTest_363, ConstructWithLvalueStoresValue_363) {
    int val = 42;
    TestableResultValue<int> result(val);
    EXPECT_EQ(result.value(), 42);
}

// Test construction with rvalue
TEST_F(ResultValueBaseTest_363, ConstructWithRvalueStoresValue_363) {
    TestableResultValue<int> result(42);
    EXPECT_EQ(result.value(), 42);
}

// Test with string type
TEST_F(ResultValueBaseTest_363, ConstructWithStringValue_363) {
    std::string s = "hello";
    TestableResultValue<std::string> result(s);
    EXPECT_EQ(result.value(), "hello");
}

// Test with string rvalue
TEST_F(ResultValueBaseTest_363, ConstructWithStringRvalue_363) {
    TestableResultValue<std::string> result(std::string("world"));
    EXPECT_EQ(result.value(), "world");
}

// Test copy construction preserves value
TEST_F(ResultValueBaseTest_363, CopyConstructionPreservesValue_363) {
    TestableResultValue<int> original(99);
    TestableResultValue<int> copy(original);
    EXPECT_EQ(copy.value(), 99);
    EXPECT_EQ(original.value(), 99);
}

// Test move construction
TEST_F(ResultValueBaseTest_363, MoveConstructionPreservesValue_363) {
    TestableResultValue<std::string> original(std::string("moved"));
    TestableResultValue<std::string> moved(std::move(original));
    EXPECT_EQ(moved.value(), "moved");
}

// Test copy assignment
TEST_F(ResultValueBaseTest_363, CopyAssignmentPreservesValue_363) {
    TestableResultValue<int> a(10);
    TestableResultValue<int> b(20);
    b = a;
    EXPECT_EQ(b.value(), 10);
    EXPECT_EQ(a.value(), 10);
}

// Test move assignment
TEST_F(ResultValueBaseTest_363, MoveAssignmentPreservesValue_363) {
    TestableResultValue<std::string> a(std::string("source"));
    TestableResultValue<std::string> b(std::string("dest"));
    b = std::move(a);
    EXPECT_EQ(b.value(), "source");
}

// Test with zero value (boundary)
TEST_F(ResultValueBaseTest_363, ConstructWithZeroValue_363) {
    TestableResultValue<int> result(0);
    EXPECT_EQ(result.value(), 0);
}

// Test with negative value
TEST_F(ResultValueBaseTest_363, ConstructWithNegativeValue_363) {
    TestableResultValue<int> result(-1);
    EXPECT_EQ(result.value(), -1);
}

// Test with empty string (boundary)
TEST_F(ResultValueBaseTest_363, ConstructWithEmptyString_363) {
    TestableResultValue<std::string> result(std::string(""));
    EXPECT_EQ(result.value(), "");
}

// Test destruction of Ok result with complex type doesn't leak
TEST_F(ResultValueBaseTest_363, DestructionOfOkResultWithComplexType_363) {
    // This should not leak or crash
    {
        TestableResultValue<std::string> result(std::string("temporary"));
        EXPECT_EQ(result.value(), "temporary");
    }
    // If we reach here, destructor worked fine
    SUCCEED();
}

// Test construction with error type (no value)
TEST_F(ResultValueBaseTest_363, ConstructWithErrorType_363) {
    // Constructing with LogicError type - no value should be stored
    TestableResultValue<int> result(ResultType::LogicError);
    // Accessing value on a non-Ok result should trigger enforceOk
    // which typically throws or asserts
    EXPECT_ANY_THROW(result.value());
}

// Test construction with RuntimeError type
TEST_F(ResultValueBaseTest_363, ConstructWithRuntimeErrorType_363) {
    TestableResultValue<std::string> result(ResultType::RuntimeError);
    EXPECT_ANY_THROW(result.value());
}

// Test with double type
TEST_F(ResultValueBaseTest_363, ConstructWithDoubleValue_363) {
    TestableResultValue<double> result(3.14);
    EXPECT_DOUBLE_EQ(result.value(), 3.14);
}

// Test value() returns const reference
TEST_F(ResultValueBaseTest_363, ValueReturnsConstReference_363) {
    TestableResultValue<std::string> result(std::string("test"));
    const std::string& ref = result.value();
    EXPECT_EQ(ref, "test");
    // Verify it's the same object (address check)
    EXPECT_EQ(&ref, &result.value());
}

// Test self-assignment with copy
TEST_F(ResultValueBaseTest_363, SelfCopyAssignment_363) {
    TestableResultValue<int> result(42);
    result = result;
    EXPECT_EQ(result.value(), 42);
}

// Test assigning from Ok to Error and vice versa
TEST_F(ResultValueBaseTest_363, AssignOkToOkDifferentValues_363) {
    TestableResultValue<int> a(100);
    TestableResultValue<int> b(200);
    a = b;
    EXPECT_EQ(a.value(), 200);
}

// Test with large string
TEST_F(ResultValueBaseTest_363, ConstructWithLargeString_363) {
    std::string large(10000, 'x');
    TestableResultValue<std::string> result(large);
    EXPECT_EQ(result.value(), large);
    EXPECT_EQ(result.value().size(), 10000u);
}
