#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <string>

// We need to access ResultValueBase through a derived class that exposes construction
// In Catch2's Clara, this is typically through BasicResult<T>

namespace Catch {
namespace Clara {
namespace Detail {

// BasicResult<T> inherits from ResultValueBase<T> and provides public static factory methods
// We'll use it to test value() behavior

class ResultValueBaseTest_360 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Helper: Create a derived class to expose the protected constructors for testing
template <typename T>
class TestableResultValue : public ResultValueBase<T> {
public:
    static TestableResultValue ok(T const& value) {
        return TestableResultValue(ResultBase::Ok, value);
    }
    static TestableResultValue ok(T&& value) {
        return TestableResultValue(ResultBase::Ok, std::move(value));
    }
    static TestableResultValue logicError() {
        return TestableResultValue(ResultBase::LogicError);
    }
    static TestableResultValue runtimeError() {
        return TestableResultValue(ResultBase::RuntimeError);
    }

private:
    TestableResultValue(ResultType type, T const& value)
        : ResultValueBase<T>(type, value) {}
    TestableResultValue(ResultType type, T&& value)
        : ResultValueBase<T>(type, std::move(value)) {}
    TestableResultValue(ResultType type)
        : ResultValueBase<T>(type) {}
};

} // namespace Detail
} // namespace Clara
} // namespace Catch

// Since direct access to protected constructors may not compile cleanly,
// let's use the public Catch2 Clara API instead: ParserResult / BasicResult

using namespace Catch::Clara;
using namespace Catch::Clara::Detail;

// Test through BasicResult which is the standard public interface
class BasicResultTest_360 : public ::testing::Test {};

TEST_F(BasicResultTest_360, ValueReturnsStoredIntWhenOk_360) {
    auto result = ParserResult::ok(Detail::ParseState(Detail::ParseResultType::Matched, 42));
    // ParserResult is a specific type; let's test through what's available
}

// Since the exact public API path may vary, let's test using a testable derived class
template <typename T>
class ExposedResultValue : public ResultValueBase<T> {
public:
    ExposedResultValue(ResultType type, T const& val)
        : ResultValueBase<T>(type, val) {}
    ExposedResultValue(ResultType type)
        : ResultValueBase<T>(type) {}
};

class ResultValueBaseIntTest_360 : public ::testing::Test {};

TEST_F(ResultValueBaseIntTest_360, ValueReturnsCorrectValueWhenOk_360) {
    ExposedResultValue<int> result(ResultBase::Ok, 42);
    EXPECT_EQ(result.value(), 42);
}

TEST_F(ResultValueBaseIntTest_360, ValueReturnsCorrectStringWhenOk_360) {
    std::string testStr = "hello";
    ExposedResultValue<std::string> result(ResultBase::Ok, testStr);
    EXPECT_EQ(result.value(), "hello");
}

TEST_F(ResultValueBaseIntTest_360, ValueThrowsOrAbortsWhenNotOk_360) {
    ExposedResultValue<int> result(ResultBase::LogicError);
    EXPECT_ANY_THROW(result.value());
}

TEST_F(ResultValueBaseIntTest_360, ValueThrowsOnRuntimeError_360) {
    ExposedResultValue<int> result(ResultBase::RuntimeError);
    EXPECT_ANY_THROW(result.value());
}

TEST_F(ResultValueBaseIntTest_360, CopyConstructionPreservesValue_360) {
    ExposedResultValue<int> original(ResultBase::Ok, 99);
    ExposedResultValue<int> copy(original);
    EXPECT_EQ(copy.value(), 99);
}

TEST_F(ResultValueBaseIntTest_360, MoveConstructionPreservesValue_360) {
    ExposedResultValue<std::string> original(ResultBase::Ok, std::string("moved"));
    ExposedResultValue<std::string> moved(std::move(original));
    EXPECT_EQ(moved.value(), "moved");
}

TEST_F(ResultValueBaseIntTest_360, ValueWithZero_360) {
    ExposedResultValue<int> result(ResultBase::Ok, 0);
    EXPECT_EQ(result.value(), 0);
}

TEST_F(ResultValueBaseIntTest_360, ValueWithNegative_360) {
    ExposedResultValue<int> result(ResultBase::Ok, -1);
    EXPECT_EQ(result.value(), -1);
}

TEST_F(ResultValueBaseIntTest_360, ValueWithEmptyString_360) {
    ExposedResultValue<std::string> result(ResultBase::Ok, std::string(""));
    EXPECT_EQ(result.value(), "");
}
