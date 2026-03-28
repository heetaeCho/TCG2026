// tests/translate_active_exception_tests_289.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <stdexcept>
#include <string>

using ::testing::Return;
using ::testing::Throw;
using ::testing::InSequence;
using ::testing::Exactly;

namespace Catch {

// --- Minimal interfaces as per provided headers (only what we need) ---
struct IExceptionTranslatorRegistry {
    virtual ~IExceptionTranslatorRegistry() = default;
    virtual std::string translateActiveException() = 0;
};

struct IRegistryHub {
    virtual ~IRegistryHub() = default;
    // We only expose the collaborator used by the function under test.
    virtual IExceptionTranslatorRegistry& getExceptionTranslatorRegistry() = 0;
};

// Production has this free function. We provide a test seam that our tests can control.
static IRegistryHub* g_registryHubForTest = nullptr;
IRegistryHub& getRegistryHub() {
    // In real code this would return the actual hub; in tests we inject our mock.
    return *g_registryHubForTest;
}

// Forward declaration of the function under test (implemented in production).
std::string translateActiveException();

} // namespace Catch

// ------------------- Google Mock types -------------------
namespace {

struct MockExceptionTranslatorRegistry : public Catch::IExceptionTranslatorRegistry {
    MOCK_METHOD(std::string, translateActiveException, (), (override));
};

struct MockRegistryHub : public Catch::IRegistryHub {
    MOCK_METHOD(Catch::IExceptionTranslatorRegistry&, getExceptionTranslatorRegistry, (), (override));
};

class TranslateActiveExceptionTest_289 : public ::testing::Test {
protected:
    MockRegistryHub hub_;
    MockExceptionTranslatorRegistry translator_;

    void SetUp() override {
        Catch::g_registryHubForTest = &hub_;
    }

    void TearDown() override {
        Catch::g_registryHubForTest = nullptr;
    }
};

} // namespace

// ------------------- Test cases -------------------

// Normal operation: delegates to the registry and returns the translator's string.
TEST_F(TranslateActiveExceptionTest_289, ReturnsTranslatorResult_289) {
    EXPECT_CALL(hub_, getExceptionTranslatorRegistry())
        .Times(Exactly(1))
        .WillOnce(Return(std::ref(translator_)));
    EXPECT_CALL(translator_, translateActiveException())
        .Times(Exactly(1))
        .WillOnce(Return(std::string("TranslatedError")));

    const std::string s = Catch::translateActiveException();
    EXPECT_EQ(s, "TranslatedError");
}

// Boundary: returns an empty string if the translator returns empty.
TEST_F(TranslateActiveExceptionTest_289, ReturnsEmptyStringWhenTranslatorDoes_289) {
    EXPECT_CALL(hub_, getExceptionTranslatorRegistry())
        .Times(Exactly(1))
        .WillOnce(Return(std::ref(translator_)));
    EXPECT_CALL(translator_, translateActiveException())
        .Times(Exactly(1))
        .WillOnce(Return(std::string{}));

    const std::string s = Catch::translateActiveException();
    EXPECT_TRUE(s.empty());
}

// Error/exceptional path: if the translator throws, the exception bubbles up.
TEST_F(TranslateActiveExceptionTest_289, PropagatesExceptionFromTranslator_289) {
    EXPECT_CALL(hub_, getExceptionTranslatorRegistry())
        .Times(Exactly(1))
        .WillOnce(Return(std::ref(translator_)));
    EXPECT_CALL(translator_, translateActiveException())
        .Times(Exactly(1))
        .WillOnce(Throw(std::runtime_error("boom")));

    EXPECT_THROW({
        (void)Catch::translateActiveException();
    }, std::runtime_error);
}

// Interaction: multiple calls delegate each time (no caching implied by interface).
TEST_F(TranslateActiveExceptionTest_289, MultipleCallsDelegateEachTime_289) {
    InSequence seq;

    EXPECT_CALL(hub_, getExceptionTranslatorRegistry())
        .WillOnce(Return(std::ref(translator_)));
    EXPECT_CALL(translator_, translateActiveException())
        .WillOnce(Return(std::string("first")));

    EXPECT_CALL(hub_, getExceptionTranslatorRegistry())
        .WillOnce(Return(std::ref(translator_)));
    EXPECT_CALL(translator_, translateActiveException())
        .WillOnce(Return(std::string("second")));

    EXPECT_EQ(Catch::translateActiveException(), "first");
    EXPECT_EQ(Catch::translateActiveException(), "second");
}
