// File: test_invoke_380.cpp
#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Include the header under test
#include "Catch2/src/catch2/internal/catch_clara.hpp"

namespace C = Catch::Clara;
namespace D = Catch::Clara::Detail;

// --- Test 1: Calls the lambda exactly once with the given int argument
TEST(ClaraInvokeTest_380, InvokesLambdaOnceWithInt_380) {
    int call_count = 0;
    int received = 0;

    auto lambda = [&](const int& x) {
        ++call_count;
        received = x;
    };

    const int arg = 42;
    auto result = D::invoke(lambda, arg);

    EXPECT_EQ(call_count, 1);
    EXPECT_EQ(received, arg);
    EXPECT_TRUE(static_cast<bool>(result)); // result is "ok" per interface’s observable bool conversion
}

// --- Test 2: Returns a truthy ParserResult (no assumptions beyond operator bool)
TEST(ClaraInvokeTest_380, ReturnsOkResult_380) {
    auto lambda = [](const int&) { /* no-op */ };

    auto result = D::invoke(lambda, 7);

    EXPECT_TRUE(static_cast<bool>(result));
}

// --- Test 3: Propagates exceptions thrown by the callable (no catching inside invoke)
TEST(ClaraInvokeTest_380, PropagatesExceptionFromCallable_380) {
    auto throwing = [](const int&) -> void {
        throw std::runtime_error("boom");
    };

    EXPECT_THROW(
        (void)D::invoke(throwing, 1),
        std::runtime_error
    );
}

// --- Test 4: Works with non-primitive ArgType (e.g., const std::string&)
TEST(ClaraInvokeTest_380, InvokesWithConstStringArg_380) {
    int call_count = 0;
    std::string received;

    auto lambda = [&](const std::string& s) {
        ++call_count;
        received = s; // observe the value passed in
    };

    const std::string arg = "hello";
    auto result = D::invoke(lambda, arg);

    EXPECT_EQ(call_count, 1);
    EXPECT_EQ(received, arg);
    EXPECT_TRUE(static_cast<bool>(result));
}

// --- (Optional) Test 5: Works with a functor object (non-lambda callable)
struct Recorder380 {
    int* count;
    std::string* out;
    void operator()(const std::string& s) const {
        if (count) ++(*count);
        if (out) *out = s;
    }
};

TEST(ClaraInvokeTest_380, InvokesFunctorObject_380) {
    int call_count = 0;
    std::string received;

    Recorder380 rec{&call_count, &received};
    const std::string arg = "functor-ok";

    auto result = D::invoke(rec, arg);

    EXPECT_EQ(call_count, 1);
    EXPECT_EQ(received, arg);
    EXPECT_TRUE(static_cast<bool>(result));
}
