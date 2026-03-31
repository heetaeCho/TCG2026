#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <stdexcept>

// We need to provide minimal infrastructure to test ExceptionTranslatorRegistrar
// Since it calls Detail::registerTranslatorImpl internally, we need to mock/stub that.

// Forward declarations and minimal stubs to make the code compile
namespace Catch {
namespace Detail {
    class IExceptionTranslator {
    public:
        virtual ~IExceptionTranslator() = default;
        virtual std::string translate(Catch::Detail::IExceptionTranslator const* prev) const = 0;
    };

    // Track registration calls for testing
    static int g_registrationCount = 0;
    static bool g_lastRegistrationWasValid = false;

    template<typename T>
    using unique_ptr = std::unique_ptr<T>;

    template<typename T, typename... Args>
    unique_ptr<T> make_unique(Args&&... args) {
        return unique_ptr<T>(new T(std::forward<Args>(args)...));
    }

    inline void registerTranslatorImpl(std::unique_ptr<IExceptionTranslator> translator) {
        g_registrationCount++;
        g_lastRegistrationWasValid = (translator != nullptr);
    }
} // namespace Detail

template<typename T>
class ExceptionTranslator : public Detail::IExceptionTranslator {
    std::string(*m_translateFunction)(T const&);
public:
    ExceptionTranslator(std::string(*translateFunction)(T const&))
        : m_translateFunction(translateFunction) {}

    std::string translate(Detail::IExceptionTranslator const*) const override {
        try {
            throw;
        } catch(T const& ex) {
            return m_translateFunction(ex);
        }
    }
};

class ExceptionTranslatorRegistrar {
public:
    template<typename T>
    ExceptionTranslatorRegistrar(std::string(*translateFunction)(T const&)) {
        Detail::registerTranslatorImpl(
            Detail::make_unique<ExceptionTranslator<T>>(translateFunction)
        );
    }
};

} // namespace Catch

// --- Test helper exception types and translator functions ---

class CustomException {
public:
    std::string message;
    CustomException(const std::string& msg) : message(msg) {}
};

class AnotherException {
public:
    int code;
    AnotherException(int c) : code(c) {}
};

std::string translateRuntimeError(std::runtime_error const& ex) {
    return std::string("runtime_error: ") + ex.what();
}

std::string translateCustomException(CustomException const& ex) {
    return std::string("custom: ") + ex.message;
}

std::string translateAnotherException(AnotherException const& ex) {
    return std::string("another: ") + std::to_string(ex.code);
}

std::string translateLogicError(std::logic_error const& ex) {
    return std::string("logic_error: ") + ex.what();
}

std::string translateInt(int const& val) {
    return std::string("int: ") + std::to_string(val);
}

std::string translateString(std::string const& val) {
    return std::string("string: ") + val;
}

// --- Tests ---

class ExceptionTranslatorRegistrarTest_1052 : public ::testing::Test {
protected:
    void SetUp() override {
        Catch::Detail::g_registrationCount = 0;
        Catch::Detail::g_lastRegistrationWasValid = false;
    }
};

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersRuntimeErrorTranslator_1052) {
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(&translateRuntimeError);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersCustomExceptionTranslator_1052) {
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(&translateCustomException);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersAnotherExceptionTranslator_1052) {
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(&translateAnotherException);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersLogicErrorTranslator_1052) {
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(&translateLogicError);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersIntTranslator_1052) {
    // Test with a non-exception type (int)
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(&translateInt);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistersStringTranslator_1052) {
    // Test with std::string as exception type
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(&translateString);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, MultipleRegistrationsIncrementCount_1052) {
    EXPECT_EQ(Catch::Detail::g_registrationCount, 0);
    Catch::ExceptionTranslatorRegistrar r1(&translateRuntimeError);
    EXPECT_EQ(Catch::Detail::g_registrationCount, 1);
    Catch::ExceptionTranslatorRegistrar r2(&translateCustomException);
    EXPECT_EQ(Catch::Detail::g_registrationCount, 2);
    Catch::ExceptionTranslatorRegistrar r3(&translateAnotherException);
    EXPECT_EQ(Catch::Detail::g_registrationCount, 3);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, TranslatorCorrectlyTranslatesException_1052) {
    // Verify the ExceptionTranslator created actually works
    auto translator = Catch::Detail::make_unique<Catch::ExceptionTranslator<std::runtime_error>>(&translateRuntimeError);
    
    std::string result;
    try {
        throw std::runtime_error("test error");
    } catch (...) {
        result = translator->translate(nullptr);
    }
    EXPECT_EQ(result, "runtime_error: test error");
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, TranslatorCorrectlyTranslatesCustomException_1052) {
    auto translator = Catch::Detail::make_unique<Catch::ExceptionTranslator<CustomException>>(&translateCustomException);
    
    std::string result;
    try {
        throw CustomException("hello world");
    } catch (...) {
        result = translator->translate(nullptr);
    }
    EXPECT_EQ(result, "custom: hello world");
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, TranslatorCorrectlyTranslatesAnotherException_1052) {
    auto translator = Catch::Detail::make_unique<Catch::ExceptionTranslator<AnotherException>>(&translateAnotherException);
    
    std::string result;
    try {
        throw AnotherException(42);
    } catch (...) {
        result = translator->translate(nullptr);
    }
    EXPECT_EQ(result, "another: 42");
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, TranslatorWithPrimitiveType_1052) {
    auto translator = Catch::Detail::make_unique<Catch::ExceptionTranslator<int>>(&translateInt);
    
    std::string result;
    try {
        throw 99;
    } catch (...) {
        result = translator->translate(nullptr);
    }
    EXPECT_EQ(result, "int: 99");
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, TranslatorWithEmptyStringException_1052) {
    auto translator = Catch::Detail::make_unique<Catch::ExceptionTranslator<std::string>>(&translateString);
    
    std::string result;
    try {
        throw std::string("");
    } catch (...) {
        result = translator->translate(nullptr);
    }
    EXPECT_EQ(result, "string: ");
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, TranslatorWithLongStringException_1052) {
    auto translator = Catch::Detail::make_unique<Catch::ExceptionTranslator<std::string>>(&translateString);
    
    std::string longStr(10000, 'x');
    std::string result;
    try {
        throw longStr;
    } catch (...) {
        result = translator->translate(nullptr);
    }
    EXPECT_EQ(result, "string: " + longStr);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, RegistrarWithLambdaStyleFunctionPointer_1052) {
    // Using a static function that acts like what a macro-generated translator would produce
    static auto fn = [](std::runtime_error const& e) -> std::string {
        return std::string("lambda: ") + e.what();
    };
    // Note: lambdas without capture can be converted to function pointers
    std::string(*fptr)(std::runtime_error const&) = +fn;
    
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar registrar(fptr);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 1);
    EXPECT_TRUE(Catch::Detail::g_lastRegistrationWasValid);
}

TEST_F(ExceptionTranslatorRegistrarTest_1052, SameTranslatorFunctionRegisteredTwice_1052) {
    int countBefore = Catch::Detail::g_registrationCount;
    Catch::ExceptionTranslatorRegistrar r1(&translateRuntimeError);
    Catch::ExceptionTranslatorRegistrar r2(&translateRuntimeError);
    EXPECT_EQ(Catch::Detail::g_registrationCount, countBefore + 2);
}
