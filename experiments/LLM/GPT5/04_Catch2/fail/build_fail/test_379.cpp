// File: lambda_invoker_test_379.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

// Forward declare ParserResult in the correct namespace so the header can be parsed.
// (We provide a minimal stub after the include. This is a test-only stand-in.)
namespace Catch { namespace Clara { struct ParserResult; }}

// Include the header under test.
#include "Catch2/src/catch2/internal/catch_clara.hpp"

// Provide a minimal, test-only stub for ParserResult so we can observe return values.
// This does NOT re-implement internal logic; it just allows constructing/inspecting
// a value returned by the black-box function.
namespace Catch { namespace Clara {
struct ParserResult {
    int code;
    explicit ParserResult(int c = 0) : code(c) {}
    bool operator==(const ParserResult& other) const { return code == other.code; }
};
}} // namespace Catch::Clara

using ::testing::Eq;
using ::testing::Return;

class LambdaInvokerTest_379 : public ::testing::Test {};

// A mock functor to verify external interaction (that operator() is called with the right arg).
struct MockCallableInt {
    MOCK_METHOD(Catch::Clara::ParserResult, Call, (const int&), (const));
    Catch::Clara::ParserResult operator()(const int& x) const { return Call(x); }
};

// [Normal operation] Invokes the lambda and returns its result.
TEST_F(LambdaInvokerTest_379, InvokeCallsLambdaAndReturnsResult_379) {
    using Catch::Clara::Detail::LambdaInvoker;
    using Catch::Clara::ParserResult;

    int seen = -1;
    auto lambda = [&seen](int const& x) -> ParserResult {
        seen = x;                  // observable side effect to confirm forwarding
        return ParserResult{123};  // observable return value
    };

    const int arg = 7;
    ParserResult res = LambdaInvoker::invoke(lambda, arg);

    EXPECT_EQ(seen, arg);
    EXPECT_EQ(res, ParserResult{123});
}

// [Boundary-ish] Works with zero/empty-like values (int 0).
TEST_F(LambdaInvokerTest_379, InvokePassesZeroInt_379) {
    using Catch::Clara::Detail::LambdaInvoker;
    using Catch::Clara::ParserResult;

    auto lambda = [](int const& x) -> ParserResult {
        // Return code mirrors the input to make it observable.
        return ParserResult{x};
    };

    const int arg = 0;
    ParserResult res = LambdaInvoker::invoke(lambda, arg);
    EXPECT_EQ(res, ParserResult{0});
}

// [Type coverage + boundary] Works with std::string and empty string argument.
TEST_F(LambdaInvokerTest_379, InvokeWithStringAndEmpty_379) {
    using Catch::Clara::Detail::LambdaInvoker;
    using Catch::Clara::ParserResult;

    auto lambda = [](std::string const& s) -> ParserResult {
        // Return the length so we can observe what was passed in.
        return ParserResult{static_cast<int>(s.size())};
    };

    ParserResult res1 = LambdaInvoker::invoke(lambda, std::string{"hello"});
    EXPECT_EQ(res1, ParserResult{5});

    ParserResult res2 = LambdaInvoker::invoke(lambda, std::string{});
    EXPECT_EQ(res2, ParserResult{0});
}

// [Exceptional case] Exceptions thrown by the callable propagate out of invoke.
TEST_F(LambdaInvokerTest_379, InvokePropagatesExceptions_379) {
    using Catch::Clara::Detail::LambdaInvoker;

    auto throwing = [](int const&) -> Catch::Clara::ParserResult {
        throw std::runtime_error("boom");
    };

    EXPECT_THROW((void)LambdaInvoker::invoke(throwing, 1), std::runtime_error);
}

// [External interaction verification] Using a mock functor to ensure operator() is called once with the correct parameter.
TEST_F(LambdaInvokerTest_379, InvokeCallsMockFunctorOnceWithCorrectArg_379) {
    using Catch::Clara::Detail::LambdaInvoker;
    using Catch::Clara::ParserResult;

    MockCallableInt mock;
    const int arg = 7;

    EXPECT_CALL(mock, Call(Eq(arg)))
        .Times(1)
        .WillOnce(Return(ParserResult{321}));

    ParserResult res = LambdaInvoker::invoke(mock, arg);
    EXPECT_EQ(res, ParserResult{321});
}
