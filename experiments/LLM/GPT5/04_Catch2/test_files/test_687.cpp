// File: tests/exception_translator_registry_translateActiveException_687.cpp

#include <gtest/gtest.h>
#include <stdexcept>
#include <string>

// Catch2 headers (interfaces only; no peeking at internals)
#include <catch2/internal/catch_exception_translator_registry.hpp>

// These headers provide the exception marker types that should be rethrown.
// If your tree uses different paths, adjust includes accordingly.
#include <catch2/internal/catch_test_failure_exception.hpp>
#include <catch2/internal/catch_test_skip_exception.hpp>

namespace {

using Catch::ExceptionTranslatorRegistry;

class ExceptionTranslatorRegistryTest_687 : public ::testing::Test {
protected:
    ExceptionTranslatorRegistry reg_;
};

} // namespace

// Normal case: no active C++ exception -> returns the documented message.
TEST_F(ExceptionTranslatorRegistryTest_687, NoActiveExceptionReturnsClrNotice_687) {
    // Call outside of any catch block / without any active exception.
    const std::string translated = reg_.translateActiveException();
    EXPECT_EQ(translated, "Non C++ exception. Possibly a CLR exception.");
}

// std::exception is active -> returns ex.what()
TEST_F(ExceptionTranslatorRegistryTest_687, StdExceptionReturnsWhat_687) {
    try {
        throw std::runtime_error("boom");
    } catch (...) {
        const std::string translated = reg_.translateActiveException();
        EXPECT_EQ(translated, "boom");
    }
}

// std::string exception -> returns the string
TEST_F(ExceptionTranslatorRegistryTest_687, StringExceptionReturnsString_687) {
    try {
        throw std::string("string-msg");
    } catch (...) {
        const std::string translated = reg_.translateActiveException();
        EXPECT_EQ(translated, "string-msg");
    }
}

// const char* exception -> returns the message
TEST_F(ExceptionTranslatorRegistryTest_687, ConstCharExceptionReturnsMessage_687) {
    try {
        throw "c-msg";
    } catch (...) {
        const std::string translated = reg_.translateActiveException();
        EXPECT_EQ(translated, "c-msg");
    }
}

// Unknown non-standard exception type -> returns "Unknown exception"
TEST_F(ExceptionTranslatorRegistryTest_687, UnknownExceptionReturnsFallback_687) {
    try {
        throw 42; // some non-standard, non-string exception type
    } catch (...) {
        const std::string translated = reg_.translateActiveException();
        EXPECT_EQ(translated, "Unknown exception");
    }
}

// TestFailureException active -> translateActiveException rethrows the same exception
TEST_F(ExceptionTranslatorRegistryTest_687, TestFailureExceptionIsRethrown_687) {
    try {
        throw Catch::TestFailureException{};
    } catch (...) {
        // The function should rethrow the *current* exception.
        EXPECT_THROW(reg_.translateActiveException(), Catch::TestFailureException);
    }
}

// TestSkipException active -> translateActiveException rethrows the same exception
TEST_F(ExceptionTranslatorRegistryTest_687, TestSkipExceptionIsRethrown_687) {
    try {
        throw Catch::TestSkipException{};
    } catch (...) {
        // The function should rethrow the *current* exception.
        EXPECT_THROW(reg_.translateActiveException(), Catch::TestSkipException);
    }
}
