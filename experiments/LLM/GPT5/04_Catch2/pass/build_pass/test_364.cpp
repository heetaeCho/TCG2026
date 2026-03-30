// File: tests/BasicResult_ok_364_tests.cpp

#include <gtest/gtest.h>
#include <memory>
#include <string>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace {
namespace CC = Catch::Clara::Detail;

template <typename T>
using BR = CC::BasicResult<T>;

using CC::ResultType;

// -------------------------
// Normal operation (value)
// -------------------------

TEST(BasicResultOkTest_364, OkWithInt_SetsTypeOkAndTruthiness_364) {
    auto r = BR<int>::ok(42);
    EXPECT_TRUE(static_cast<bool>(r)) << "Ok result should be truthy";
    EXPECT_EQ(r.type(), ResultType::Ok) << "type() should report Ok";
    // Observable behavior: contained value accessible via public API
    EXPECT_EQ(r.value(), 42) << "Contained value should match provided input";
    // Error message should be empty for Ok results (observable via errorMessage())
    EXPECT_TRUE(r.errorMessage().empty()) << "Ok result should not have an error message";
}

TEST(BasicResultOkTest_364, OkWithStringLValue_PreservesContent_364) {
    std::string s = "hello";
    auto r = BR<std::string>::ok(s); // pass lvalue
    EXPECT_TRUE(r);
    EXPECT_EQ(r.type(), ResultType::Ok);
    EXPECT_EQ(r.value(), "hello");
    EXPECT_TRUE(r.errorMessage().empty());
}

// -------------------------
// Boundary & type coverage
// -------------------------

TEST(BasicResultOkTest_364, OkWithConstLValue_CompilesAndStores_364) {
    const int x = 7;
    auto r = BR<int>::ok(x); // const lvalue
    EXPECT_TRUE(r);
    EXPECT_EQ(r.type(), ResultType::Ok);
    EXPECT_EQ(r.value(), 7);
}

TEST(BasicResultOkTest_364, OkWithMoveOnlyType_AcceptsRValue_364) {
    auto r = BR<std::unique_ptr<int>>::ok(std::make_unique<int>(99)); // rvalue move-only
    EXPECT_TRUE(r);
    EXPECT_EQ(r.type(), ResultType::Ok);
    ASSERT_NE(r.value(), nullptr) << "Contained unique_ptr should be non-null";
    EXPECT_EQ(*r.value(), 99);
    EXPECT_TRUE(r.errorMessage().empty());
}

// -------------------------
// Void specialization path
// -------------------------

TEST(BasicResultOkTest_364, OkWithoutValue_VoidSpecializationTruthiness_364) {
    // Verify that the no-arg ok() constructs a truthy Ok for void specialization
    auto r = BR<void>::ok();
    EXPECT_TRUE(r);
    EXPECT_EQ(r.type(), ResultType::Ok);
    EXPECT_TRUE(r.errorMessage().empty());
}

// -------------------------
// Forwarding semantics (observable only)
// -------------------------

TEST(BasicResultOkTest_364, OkWithStringRValue_AcceptsRValue_364) {
    auto r = BR<std::string>::ok(std::string{"moved"});
    EXPECT_TRUE(r);
    EXPECT_EQ(r.type(), ResultType::Ok);
    EXPECT_EQ(r.value(), "moved");
    EXPECT_TRUE(r.errorMessage().empty());
}

} // namespace
