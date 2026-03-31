#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers
#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// We need to mock IConfig to control the behavior of allowThrows()
// Since we're testing AssertionHandler::allowThrows() which delegates to
// getCurrentContext().getConfig()->allowThrows(), we need to set up the context
// with a mock config.

namespace Catch {

// Mock for IConfig
class MockConfig : public IConfig {
public:
    ~MockConfig() override = default;

    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

} // namespace Catch

class AssertionHandlerTest_553 : public ::testing::Test {
protected:
    void SetUp() override {
        // Get the mutable context and set our mock config
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setConfig(&mockConfig_);
    }

    void TearDown() override {
        // Reset config to nullptr to avoid dangling pointer
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setConfig(nullptr);
    }

    Catch::MockConfig mockConfig_;
};

// Test that allowThrows returns true when config says throws are allowed
TEST_F(AssertionHandlerTest_553, AllowThrowsReturnsTrue_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillOnce(::testing::Return(true));

    Catch::AssertionHandler handler(
        "REQUIRE"_catch_sr,
        Catch::SourceLineInfo("test_file.cpp", 42),
        "expression"_catch_sr,
        Catch::ResultDisposition::Normal
    );

    EXPECT_TRUE(handler.allowThrows());
    handler.complete();
}

// Test that allowThrows returns false when config says throws are not allowed
TEST_F(AssertionHandlerTest_553, AllowThrowsReturnsFalse_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillOnce(::testing::Return(false));

    Catch::AssertionHandler handler(
        "REQUIRE"_catch_sr,
        Catch::SourceLineInfo("test_file.cpp", 42),
        "expression"_catch_sr,
        Catch::ResultDisposition::Normal
    );

    EXPECT_FALSE(handler.allowThrows());
    handler.complete();
}

// Test that allowThrows delegates to config consistently (multiple calls)
TEST_F(AssertionHandlerTest_553, AllowThrowsDelegatesToConfig_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(true));

    Catch::AssertionHandler handler(
        "CHECK"_catch_sr,
        Catch::SourceLineInfo("another_file.cpp", 100),
        "some_expr"_catch_sr,
        Catch::ResultDisposition::Normal
    );

    // Call allowThrows twice to verify it delegates each time
    EXPECT_TRUE(handler.allowThrows());
    EXPECT_TRUE(handler.allowThrows());
    handler.complete();
}

// Test that allowThrows reflects changing config state
TEST_F(AssertionHandlerTest_553, AllowThrowsReflectsConfigChange_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));

    Catch::AssertionHandler handler(
        "REQUIRE"_catch_sr,
        Catch::SourceLineInfo("file.cpp", 1),
        "expr"_catch_sr,
        Catch::ResultDisposition::Normal
    );

    EXPECT_TRUE(handler.allowThrows());
    EXPECT_FALSE(handler.allowThrows());
    handler.complete();
}
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

namespace {

class MockConfig : public Catch::IConfig {
public:
    ~MockConfig() override = default;

    MOCK_METHOD(bool, allowThrows, (), (const, override));
    MOCK_METHOD(Catch::StringRef, name, (), (const, override));
    MOCK_METHOD(bool, includeSuccessfulResults, (), (const, override));
    MOCK_METHOD(bool, shouldDebugBreak, (), (const, override));
    MOCK_METHOD(bool, warnAboutMissingAssertions, (), (const, override));
    MOCK_METHOD(bool, warnAboutUnmatchedTestSpecs, (), (const, override));
    MOCK_METHOD(bool, zeroTestsCountAsSuccess, (), (const, override));
    MOCK_METHOD(int, abortAfter, (), (const, override));
    MOCK_METHOD(bool, showInvisibles, (), (const, override));
    MOCK_METHOD(Catch::ShowDurations, showDurations, (), (const, override));
    MOCK_METHOD(double, minDuration, (), (const, override));
    MOCK_METHOD(const Catch::TestSpec&, testSpec, (), (const, override));
    MOCK_METHOD(bool, hasTestFilters, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getTestsOrTags, (), (const, override));
    MOCK_METHOD(Catch::TestRunOrder, runOrder, (), (const, override));
    MOCK_METHOD(uint32_t, rngSeed, (), (const, override));
    MOCK_METHOD(unsigned int, shardCount, (), (const, override));
    MOCK_METHOD(unsigned int, shardIndex, (), (const, override));
    MOCK_METHOD(Catch::ColourMode, defaultColourMode, (), (const, override));
    MOCK_METHOD(const std::vector<std::string>&, getSectionsToRun, (), (const, override));
    MOCK_METHOD(Catch::Verbosity, verbosity, (), (const, override));
    MOCK_METHOD(bool, skipBenchmarks, (), (const, override));
    MOCK_METHOD(bool, benchmarkNoAnalysis, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkSamples, (), (const, override));
    MOCK_METHOD(double, benchmarkConfidenceInterval, (), (const, override));
    MOCK_METHOD(unsigned int, benchmarkResamples, (), (const, override));
    MOCK_METHOD(std::chrono::milliseconds, benchmarkWarmupTime, (), (const, override));
};

class MockResultCapture : public Catch::IResultCapture {
public:
    ~MockResultCapture() override = default;

    MOCK_METHOD(void, handleExpr,
                (Catch::AssertionInfo const&, Catch::ITransientExpression const&, Catch::AssertionReaction&),
                (override));
    MOCK_METHOD(void, handleMessage,
                (Catch::AssertionInfo const&, Catch::ResultWas::OfType, Catch::StringRef, Catch::AssertionReaction&),
                (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown,
                (Catch::AssertionInfo const&, Catch::AssertionReaction&),
                (override));
    MOCK_METHOD(void, handleUnexpectedInflightException,
                (Catch::AssertionInfo const&, Catch::StringRef, Catch::AssertionReaction&),
                (override));
    MOCK_METHOD(void, handleIncomplete,
                (Catch::AssertionInfo const&, Catch::AssertionReaction&),
                (override));
    MOCK_METHOD(void, handleNonExpr,
                (Catch::AssertionInfo const&, Catch::ResultWas::OfType, Catch::AssertionReaction&),
                (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(auto, acquireGeneratorTracker,
                (Catch::StringRef, Catch::SourceLineInfo const&),
                (override));
    MOCK_METHOD(auto, createGeneratorTracker,
                (Catch::StringRef, Catch::SourceLineInfo const&, Catch::Generators::GeneratorBasePtr&&),
                (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (Catch::BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (Catch::BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (Catch::MessageInfo const&), (override));
    MOCK_METHOD(void, popScopedMessage, (Catch::MessageInfo const&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (Catch::MessageBuilder&&), (override));
    MOCK_METHOD(std::string, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const Catch::AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (Catch::StringRef), (override));
    MOCK_METHOD(bool, sectionStarted,
                (Catch::StringRef, Catch::SourceLineInfo const&, Catch::Counts&),
                (override));
};

class AssertionHandlerTest_553 : public ::testing::Test {
protected:
    void SetUp() override {
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setConfig(&mockConfig_);
        ctx.setResultCapture(&mockResultCapture_);
    }

    void TearDown() override {
        auto& ctx = Catch::getCurrentMutableContext();
        ctx.setConfig(nullptr);
        ctx.setResultCapture(nullptr);
    }

    MockConfig mockConfig_;
    MockResultCapture mockResultCapture_;
};

// Test: allowThrows returns true when config allows throws
TEST_F(AssertionHandlerTest_553, AllowThrowsReturnsTrue_WhenConfigAllows_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillRepeatedly(::testing::Return(true));

    Catch::AssertionHandler handler(
        "REQUIRE",
        Catch::SourceLineInfo("test.cpp", 10),
        "expr",
        Catch::ResultDisposition::Normal
    );

    EXPECT_TRUE(handler.allowThrows());
}

// Test: allowThrows returns false when config disallows throws
TEST_F(AssertionHandlerTest_553, AllowThrowsReturnsFalse_WhenConfigDisallows_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillRepeatedly(::testing::Return(false));

    Catch::AssertionHandler handler(
        "REQUIRE",
        Catch::SourceLineInfo("test.cpp", 20),
        "some_expression",
        Catch::ResultDisposition::Normal
    );

    EXPECT_FALSE(handler.allowThrows());
}

// Test: allowThrows delegates to config each call
TEST_F(AssertionHandlerTest_553, AllowThrowsDelegatesToConfigEachCall_553) {
    EXPECT_CALL(mockConfig_, allowThrows())
        .WillOnce(::testing::Return(true))
        .WillOnce(::testing::Return(false));

    Catch::AssertionHandler handler(
        "CHECK",
        Catch::SourceLineInfo("file.cpp", 5),
        "x == y",
        Catch::ResultDisposition::Normal
    );

    EXPECT_TRUE(handler.allowThrows());
    EXPECT_FALSE(handler.allowThrows());
}

} // anonymous namespace
