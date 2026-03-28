#include <catch2/internal/catch_clara.hpp>
#include <gtest/gtest.h>
#include <string>
#include <type_traits>

// In Catch2's Clara, ParserResult and related types use ResultValueBase internally.
// We access ResultValueBase behavior through the public Result types.

namespace {

using Catch::Clara::Detail::ResultType;

// We need a concrete type that exposes ResultValueBase. In Clara, 
// BasicResult<T> is such a type. Let's use the parser result infrastructure.
// If BasicResult isn't directly accessible, we use the available public API.

// Helper: Create a result-like object. In Catch2 Clara, `Detail::Result<T>` or 
// `Detail::BasicResult<T>` wraps ResultValueBase<T>.

// Since ResultValueBase has protected constructors, we create a test subclass
// to exercise the copy assignment operator which is public.
template <typename T>
class TestableResult : public Catch::Clara::Detail::ResultValueBase<T> {
public:
    using Base = Catch::Clara::Detail::ResultValueBase<T>;
    
    // Expose constructors
    static TestableResult ok(T const& value) {
        TestableResult r(ResultType::Ok, value);
        return r;
    }
    
    static TestableResult ok(T&& value) {
        TestableResult r(ResultType::Ok, std::move(value));
        return r;
    }
    
    static TestableResult error(ResultType type) {
        TestableResult r(type);
        return r;
    }
    
    // Use the public operator=
    TestableResult& operator=(TestableResult const& other) {
        Base::operator=(other);
        return *this;
    }
    
    TestableResult& operator=(TestableResult&& other) {
        Base::operator=(std::move(other));
        return *this;
    }
    
    // Copy/move constructors
    TestableResult(TestableResult const& other) : Base(other) {}
    TestableResult(TestableResult&& other) : Base(std::move(other)) {}
    
    using Base::value;
    
    ResultType type() const { return this->m_type; }

private:
    TestableResult(ResultType type) : Base(type) {}
    TestableResult(ResultType type, T const& val) : Base(type, val) {}
    TestableResult(ResultType type, T&& val) : Base(type, std::move(val)) {}
};

} // anonymous namespace

class ResultValueBaseTest_361 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Copy assignment from Ok result to Ok result preserves value
TEST_F(ResultValueBaseTest_361, CopyAssignOkToOk_PreservesValue_361) {
    auto r1 = TestableResult<int>::ok(42);
    auto r2 = TestableResult<int>::ok(99);
    
    r2 = r1;
    
    EXPECT_EQ(r2.value(), 42);
}

// Test: Copy assignment from Ok result with string type
TEST_F(ResultValueBaseTest_361, CopyAssignOkToOk_StringValue_361) {
    auto r1 = TestableResult<std::string>::ok(std::string("hello"));
    auto r2 = TestableResult<std::string>::ok(std::string("world"));
    
    r2 = r1;
    
    EXPECT_EQ(r2.value(), "hello");
}

// Test: Copy assignment from error to Ok result
TEST_F(ResultValueBaseTest_361, CopyAssignErrorToOk_361) {
    auto r1 = TestableResult<int>::error(ResultType::LogicError);
    auto r2 = TestableResult<int>::ok(42);
    
    r2 = r1;
    
    EXPECT_EQ(r2.type(), ResultType::LogicError);
}

// Test: Copy assignment from Ok to error result
TEST_F(ResultValueBaseTest_361, CopyAssignOkToError_361) {
    auto r1 = TestableResult<int>::ok(42);
    auto r2 = TestableResult<int>::error(ResultType::RuntimeError);
    
    r2 = r1;
    
    EXPECT_EQ(r2.value(), 42);
    EXPECT_EQ(r2.type(), ResultType::Ok);
}

// Test: Copy assignment from error to error
TEST_F(ResultValueBaseTest_361, CopyAssignErrorToError_361) {
    auto r1 = TestableResult<int>::error(ResultType::LogicError);
    auto r2 = TestableResult<int>::error(ResultType::RuntimeError);
    
    r2 = r1;
    
    EXPECT_EQ(r2.type(), ResultType::LogicError);
}

// Test: Self assignment of Ok result
TEST_F(ResultValueBaseTest_361, SelfAssignmentOk_361) {
    auto r1 = TestableResult<int>::ok(42);
    
    r1 = r1;
    
    EXPECT_EQ(r1.value(), 42);
    EXPECT_EQ(r1.type(), ResultType::Ok);
}

// Test: Self assignment of error result
TEST_F(ResultValueBaseTest_361, SelfAssignmentError_361) {
    auto r1 = TestableResult<int>::error(ResultType::RuntimeError);
    
    r1 = r1;
    
    EXPECT_EQ(r1.type(), ResultType::RuntimeError);
}

// Test: Copy assignment does not affect source
TEST_F(ResultValueBaseTest_361, CopyAssignDoesNotAffectSource_361) {
    auto r1 = TestableResult<int>::ok(42);
    auto r2 = TestableResult<int>::ok(99);
    
    r2 = r1;
    
    EXPECT_EQ(r1.value(), 42);
    EXPECT_EQ(r2.value(), 42);
}

// Test: Multiple sequential assignments
TEST_F(ResultValueBaseTest_361, MultipleSequentialAssignments_361) {
    auto r1 = TestableResult<int>::ok(1);
    auto r2 = TestableResult<int>::ok(2);
    auto r3 = TestableResult<int>::ok(3);
    
    r3 = r2;
    EXPECT_EQ(r3.value(), 2);
    
    r3 = r1;
    EXPECT_EQ(r3.value(), 1);
}

// Test: Copy construction preserves value
TEST_F(ResultValueBaseTest_361, CopyConstructionPreservesValue_361) {
    auto r1 = TestableResult<int>::ok(42);
    TestableResult<int> r2(r1);
    
    EXPECT_EQ(r2.value(), 42);
    EXPECT_EQ(r2.type(), ResultType::Ok);
}

// Test: Move construction works
TEST_F(ResultValueBaseTest_361, MoveConstructionWorks_361) {
    auto r1 = TestableResult<std::string>::ok(std::string("hello"));
    TestableResult<std::string> r2(std::move(r1));
    
    EXPECT_EQ(r2.value(), "hello");
}

// Test: Copy assign with complex type
TEST_F(ResultValueBaseTest_361, CopyAssignComplexType_361) {
    std::vector<int> vec1 = {1, 2, 3};
    std::vector<int> vec2 = {4, 5};
    
    auto r1 = TestableResult<std::vector<int>>::ok(vec1);
    auto r2 = TestableResult<std::vector<int>>::ok(vec2);
    
    r2 = r1;
    
    EXPECT_EQ(r2.value(), (std::vector<int>{1, 2, 3}));
}

// Test: value() on Ok result returns correct value
TEST_F(ResultValueBaseTest_361, ValueOnOkReturnsCorrect_361) {
    auto r = TestableResult<double>::ok(3.14);
    EXPECT_DOUBLE_EQ(r.value(), 3.14);
}

// Test: RuntimeError type preserved through copy assignment
TEST_F(ResultValueBaseTest_361, RuntimeErrorPreservedThroughCopy_361) {
    auto r1 = TestableResult<int>::error(ResultType::RuntimeError);
    auto r2 = TestableResult<int>::ok(0);
    
    r2 = r1;
    
    EXPECT_EQ(r2.type(), ResultType::RuntimeError);
}

// Test: LogicError type preserved through copy assignment
TEST_F(ResultValueBaseTest_361, LogicErrorPreservedThroughCopy_361) {
    auto r1 = TestableResult<int>::error(ResultType::LogicError);
    auto r2 = TestableResult<int>::ok(0);
    
    r2 = r1;
    
    EXPECT_EQ(r2.type(), ResultType::LogicError);
}

// Test: Assign Ok over previously-error then over another Ok
TEST_F(ResultValueBaseTest_361, ChainedAssignment_361) {
    auto rErr = TestableResult<int>::error(ResultType::LogicError);
    auto rOk1 = TestableResult<int>::ok(10);
    auto rOk2 = TestableResult<int>::ok(20);
    
    rErr = rOk1;
    EXPECT_EQ(rErr.value(), 10);
    EXPECT_EQ(rErr.type(), ResultType::Ok);
    
    rErr = rOk2;
    EXPECT_EQ(rErr.value(), 20);
}
