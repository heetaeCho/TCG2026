// File: bound_lambda_setvalue_tests_382.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

// Use the path given in the prompt
#include "Catch2/src/catch2/internal/catch_clara.hpp"

using ::testing::_;
using ::testing::Times;

namespace {

using Catch::Clara::Detail::BoundLambda;

class BoundLambdaTest_382 : public ::testing::Test {};

// --- Normal operation: string argument is forwarded and succeeds
TEST_F(BoundLambdaTest_382, SetValue_CallsStringLambdaAndSucceeds_382) {
    std::string seen;
    int calls = 0;
    auto lam = [&](const std::string& s) { ++calls; seen = s; };

    BoundLambda<decltype(lam)> bound(lam);

    auto res = bound.setValue("hello");
    EXPECT_TRUE(res);
    EXPECT_EQ(calls, 1);
    EXPECT_EQ(seen, "hello");
}

// --- Boundary condition: empty string is forwarded exactly
TEST_F(BoundLambdaTest_382, SetValue_EmptyStringPassedThrough_382) {
    std::string seen = "preset";
    int calls = 0;
    auto lam = [&](const std::string& s) { ++calls; seen = s; };

    BoundLambda<decltype(lam)> bound(lam);

    auto res = bound.setValue("");
    EXPECT_TRUE(res);
    EXPECT_EQ(calls, 1);
    EXPECT_EQ(seen, "");
}

// --- Normal operation: numeric conversion path (observable by lambda receiving int)
TEST_F(BoundLambdaTest_382, SetValue_ConvertsToIntAndInvokes_382) {
    int seen = -1;
    int calls = 0;
    auto lam = [&](int v) { ++calls; seen = v; };

    BoundLambda<decltype(lam)> bound(lam);

    auto res = bound.setValue("42");
    EXPECT_TRUE(res);
    EXPECT_EQ(calls, 1);
    EXPECT_EQ(seen, 42);
}

// --- Exceptional/error case (observable): bad numeric input should fail and not call lambda
TEST_F(BoundLambdaTest_382, SetValue_InvalidIntInputFailsAndSkipsInvocation_382) {
    int calls = 0;
    auto lam = [&](int) { ++calls; };

    BoundLambda<decltype(lam)> bound(lam);

    auto res = bound.setValue("not-an-int");
    EXPECT_FALSE(res);
    EXPECT_EQ(calls, 0);
}

// --- Multiple calls: ensure subsequent invocations work and last value is seen
TEST_F(BoundLambdaTest_382, SetValue_MultipleInvocations_382) {
    std::string seen;
    int calls = 0;
    auto lam = [&](const std::string& s) { ++calls; seen = s; };

    BoundLambda<decltype(lam)> bound(lam);

    EXPECT_TRUE(bound.setValue("first"));
    EXPECT_TRUE(bound.setValue("second"));
    EXPECT_EQ(calls, 2);
    EXPECT_EQ(seen, "second");
}

// --- Verification of external interactions: use Google Mock to assert parameter forwarding
struct MockHandler {
    MOCK_METHOD(void, Call, (int), ());
};

TEST_F(BoundLambdaTest_382, SetValue_InvokesMockWithConvertedInt_382) {
    MockHandler mock;
    auto lam = [&](int v) { mock.Call(v); };

    BoundLambda<decltype(lam)> bound(lam);

    EXPECT_CALL(mock, Call(42)).Times(1);
    auto res = bound.setValue("42");
    EXPECT_TRUE(res);
}

TEST_F(BoundLambdaTest_382, SetValue_DoesNotInvokeMockOnBadInt_382) {
    MockHandler mock;
    auto lam = [&](int v) { mock.Call(v); };

    BoundLambda<decltype(lam)> bound(lam);

    EXPECT_CALL(mock, Call(_)).Times(0);
    auto res = bound.setValue("oops");
    EXPECT_FALSE(res);
}

} // namespace
