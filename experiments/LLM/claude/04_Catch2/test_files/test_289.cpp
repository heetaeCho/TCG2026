#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

// Include necessary Catch2 headers
#include "catch2/catch_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_registry_hub.hpp"
#include "catch2/interfaces/catch_interfaces_exception.hpp"

// Since we're testing translateActiveException() which is a free function in the Catch namespace,
// and it relies on getRegistryHub() which is a global/singleton, we need to test it through
// the public interface.

namespace {

// Test that translateActiveException returns a non-empty string when an exception is active
TEST(TranslateActiveExceptionTest_289, ReturnsStringWhenStdExceptionIsActive_289) {
    try {
        throw std::runtime_error("test exception");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        // The result should contain some meaningful translation of the exception
        EXPECT_FALSE(result.empty());
    }
}

TEST(TranslateActiveExceptionTest_289, ReturnsStringWhenStringExceptionIsActive_289) {
    try {
        throw std::string("string exception");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        EXPECT_FALSE(result.empty());
    }
}

TEST(TranslateActiveExceptionTest_289, ReturnsStringWhenCStringExceptionIsActive_289) {
    try {
        throw "c-string exception";
    } catch (...) {
        std::string result = Catch::translateActiveException();
        EXPECT_FALSE(result.empty());
    }
}

TEST(TranslateActiveExceptionTest_289, ReturnsStringWhenIntExceptionIsActive_289) {
    try {
        throw 42;
    } catch (...) {
        std::string result = Catch::translateActiveException();
        EXPECT_FALSE(result.empty());
    }
}

TEST(TranslateActiveExceptionTest_289, TranslatesStdRuntimeError_289) {
    try {
        throw std::runtime_error("specific runtime error message");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        // Should contain the exception message
        EXPECT_THAT(result, ::testing::HasSubstr("specific runtime error message"));
    }
}

TEST(TranslateActiveExceptionTest_289, TranslatesStdLogicError_289) {
    try {
        throw std::logic_error("logic error message");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        EXPECT_THAT(result, ::testing::HasSubstr("logic error message"));
    }
}

TEST(TranslateActiveExceptionTest_289, TranslatesStdOutOfRange_289) {
    try {
        throw std::out_of_range("out of range message");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        EXPECT_THAT(result, ::testing::HasSubstr("out of range message"));
    }
}

TEST(TranslateActiveExceptionTest_289, TranslatesStdInvalidArgument_289) {
    try {
        throw std::invalid_argument("invalid argument message");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        EXPECT_THAT(result, ::testing::HasSubstr("invalid argument message"));
    }
}

TEST(TranslateActiveExceptionTest_289, ReturnsStringType_289) {
    try {
        throw std::runtime_error("type check");
    } catch (...) {
        auto result = Catch::translateActiveException();
        // Verify the return type is std::string
        static_assert(std::is_same<decltype(result), std::string>::value,
                      "translateActiveException should return std::string");
    }
}

TEST(TranslateActiveExceptionTest_289, TranslatesEmptyMessageException_289) {
    try {
        throw std::runtime_error("");
    } catch (...) {
        std::string result = Catch::translateActiveException();
        // Even with empty message, should return something (at minimum the empty what() string)
        // The function should not crash
        SUCCEED();
    }
}

// Test the registry hub interface accessibility
TEST(RegistryHubTest_289, GetRegistryHubReturnsValidReference_289) {
    const Catch::IRegistryHub& hub = Catch::getRegistryHub();
    // Should be able to get the exception translator registry
    const Catch::IExceptionTranslatorRegistry& reg = hub.getExceptionTranslatorRegistry();
    // If we got here without crashing, the registry is accessible
    SUCCEED();
}

TEST(RegistryHubTest_289, ExceptionTranslatorRegistryIsConsistent_289) {
    const Catch::IRegistryHub& hub1 = Catch::getRegistryHub();
    const Catch::IRegistryHub& hub2 = Catch::getRegistryHub();
    // Both calls should return the same hub (singleton pattern)
    EXPECT_EQ(&hub1, &hub2);
}

TEST(RegistryHubTest_289, ExceptionTranslatorRegistryTranslatesDirectly_289) {
    try {
        throw std::runtime_error("direct translation test");
    } catch (...) {
        const auto& registry = Catch::getRegistryHub().getExceptionTranslatorRegistry();
        std::string result = registry.translateActiveException();
        EXPECT_THAT(result, ::testing::HasSubstr("direct translation test"));
    }
}

// Test that translateActiveException and direct registry call give same result
TEST(TranslateActiveExceptionTest_289, ConsistentWithDirectRegistryCall_289) {
    try {
        throw std::runtime_error("consistency test");
    } catch (...) {
        std::string freeFunc = Catch::translateActiveException();
        std::string directCall = Catch::getRegistryHub().getExceptionTranslatorRegistry().translateActiveException();
        EXPECT_EQ(freeFunc, directCall);
    }
}

} // namespace
