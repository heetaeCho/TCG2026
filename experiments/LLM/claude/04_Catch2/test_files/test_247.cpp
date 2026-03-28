#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <stdexcept>
#include <exception>

// Include necessary Catch2 headers
#include "catch2/catch_translate_exception.hpp"
#include "catch2/interfaces/catch_interfaces_exception.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

using namespace Catch;

// A custom exception type for testing
struct CustomException {
    std::string message;
    CustomException(const std::string& msg) : message(msg) {}
};

// Another custom exception type
struct AnotherException {
    int code;
    AnotherException(int c) : code(c) {}
};

// Translation functions
static std::string translateCustomException(CustomException const& ex) {
    return "CustomException: " + ex.message;
}

static std::string translateAnotherException(AnotherException const& ex) {
    return "AnotherException: code=" + std::to_string(ex.code);
}

static std::string translateRuntimeError(std::runtime_error const& ex) {
    return std::string("RuntimeError: ") + ex.what();
}

// Type alias for convenience
using ExceptionTranslators = std::vector<Detail::unique_ptr<IExceptionTranslator>>;

class ExceptionTranslatorTest_247 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

#if !defined(CATCH_CONFIG_DISABLE_EXCEPTIONS)

// Test: ExceptionTranslator translates a matching exception when it == itEnd
TEST_F(ExceptionTranslatorTest_247, TranslatesMatchingException_WhenIteratorsEqual_247) {
    // Create the translator for CustomException
    using TranslatorClass = ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>;
    // Note: ExceptionTranslator is a nested class template. We need to instantiate it properly.
    // Based on the interface, ExceptionTranslator takes a function pointer in its constructor.
    
    // We'll use the registrar's inner class directly
    // Since ExceptionTranslator inherits from IExceptionTranslator, we can use it via that interface.
    
    ExceptionTranslators translators;
    
    // Create a translator for CustomException
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>>(
        translateCustomException
    );
    
    // We'll throw a CustomException and then call translate with it==itEnd
    std::string result;
    try {
        throw CustomException("test error");
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = translator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "CustomException: test error");
}

// Test: ExceptionTranslator delegates to next translator when it != itEnd and exception doesn't match
TEST_F(ExceptionTranslatorTest_247, DelegatesToNextTranslator_WhenIteratorNotAtEnd_247) {
    // Create two translators: first for AnotherException, second for CustomException
    ExceptionTranslators translators;
    
    auto customTranslator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>>(
        translateCustomException
    );
    
    translators.push_back(std::move(customTranslator));
    
    // Create a translator for AnotherException that will delegate
    auto anotherTranslator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<AnotherException>>(
        translateAnotherException
    );
    
    // Throw a CustomException - the AnotherException translator should delegate to the next one
    std::string result;
    try {
        throw CustomException("delegated");
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = anotherTranslator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "CustomException: delegated");
}

// Test: ExceptionTranslator catches the correct exception type with it == itEnd (rethrow path)
TEST_F(ExceptionTranslatorTest_247, TranslatesRuntimeError_247) {
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<std::runtime_error>>(
        translateRuntimeError
    );
    
    std::string result;
    try {
        throw std::runtime_error("something went wrong");
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = translator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "RuntimeError: something went wrong");
}

// Test: When exception doesn't match and no further translators, exception propagates
TEST_F(ExceptionTranslatorTest_247, ThrowsWhenExceptionDoesNotMatch_247) {
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<AnotherException>>(
        translateAnotherException
    );
    
    // Throw a CustomException but translator is for AnotherException, with empty chain
    bool exceptionPropagated = false;
    try {
        try {
            throw CustomException("unmatched");
        } catch (...) {
            ExceptionTranslators::const_iterator it = translators.cbegin();
            ExceptionTranslators::const_iterator itEnd = translators.cend();
            translator->translate(it, itEnd);
        }
    } catch (const CustomException& ex) {
        exceptionPropagated = true;
        EXPECT_EQ(ex.message, "unmatched");
    }
    
    EXPECT_TRUE(exceptionPropagated);
}

// Test: Chain of translators where the matching one is in the middle
TEST_F(ExceptionTranslatorTest_247, ChainOfTranslators_MatchInMiddle_247) {
    ExceptionTranslators translators;
    
    // Add a translator for AnotherException
    translators.push_back(
        Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<AnotherException>>(
            translateAnotherException
        )
    );
    
    // Add a translator for CustomException
    translators.push_back(
        Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>>(
            translateCustomException
        )
    );
    
    // Create a first translator for std::runtime_error that starts the chain
    auto firstTranslator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<std::runtime_error>>(
        translateRuntimeError
    );
    
    // Throw AnotherException - should be caught by the first translator in the chain
    std::string result;
    try {
        throw AnotherException(42);
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = firstTranslator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "AnotherException: code=42");
}

// Test: Translation function is correctly called with the exception object
TEST_F(ExceptionTranslatorTest_247, TranslateFunctionReceivesCorrectExceptionObject_247) {
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>>(
        translateCustomException
    );
    
    std::string result;
    try {
        throw CustomException("specific message 12345");
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = translator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "CustomException: specific message 12345");
}

// Test: Empty message exception
TEST_F(ExceptionTranslatorTest_247, TranslatesExceptionWithEmptyMessage_247) {
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>>(
        translateCustomException
    );
    
    std::string result;
    try {
        throw CustomException("");
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = translator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "CustomException: ");
}

// Test: Translator with integer exception type
TEST_F(ExceptionTranslatorTest_247, TranslatesIntegerException_247) {
    static auto translateInt = [](int const& val) -> std::string {
        return "int: " + std::to_string(val);
    };
    
    // We need a function pointer, not a lambda with captures. Use a static function.
    struct Helper {
        static std::string translateIntFunc(int const& val) {
            return "int: " + std::to_string(val);
        }
    };
    
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<int>>(
        Helper::translateIntFunc
    );
    
    std::string result;
    try {
        throw 42;
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = translator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "int: 42");
}

// Test: Translator with string exception type
TEST_F(ExceptionTranslatorTest_247, TranslatesStringException_247) {
    struct Helper {
        static std::string translateStr(std::string const& val) {
            return "string: " + val;
        }
    };
    
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<std::string>>(
        Helper::translateStr
    );
    
    std::string result;
    try {
        throw std::string("hello world");
    } catch (...) {
        ExceptionTranslators::const_iterator it = translators.cbegin();
        ExceptionTranslators::const_iterator itEnd = translators.cend();
        result = translator->translate(it, itEnd);
    }
    
    EXPECT_EQ(result, "string: hello world");
}

#else

// Test: When exceptions are disabled, translate returns the fallback message
TEST_F(ExceptionTranslatorTest_247, ReturnsDisabledMessage_WhenExceptionsDisabled_247) {
    ExceptionTranslators translators;
    
    auto translator = Detail::make_unique<ExceptionTranslatorRegistrar::ExceptionTranslator<CustomException>>(
        translateCustomException
    );
    
    ExceptionTranslators::const_iterator it = translators.cbegin();
    ExceptionTranslators::const_iterator itEnd = translators.cend();
    std::string result = translator->translate(it, itEnd);
    
    EXPECT_EQ(result, "You should never get here!");
}

#endif
