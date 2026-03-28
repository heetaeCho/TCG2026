#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <chrono>

// Include necessary Catch2 headers
#include "catch2/catch_test_case_info.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"

// We need to declare the function under test
namespace Catch {
    bool isThrowSafe(TestCaseHandle const& testCase, IConfig const& config);
}

// Mock for IConfig
class MockIConfig : public Catch::IConfig {
public:
    ~MockIConfig() override = default;

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

// Mock for ITestInvoker
class MockTestInvoker : public Catch::ITestInvoker {
public:
    ~MockTestInvoker() override = default;
    MOCK_METHOD(void, invoke, (), (const, override));
    MOCK_METHOD(void, prepareTestCase, (), (override));
    MOCK_METHOD(void, tearDownTestCase, (), (override));
};

class IsThrowSafeTest_1013 : public ::testing::Test {
protected:
    MockIConfig mockConfig;
    MockTestInvoker mockInvoker;
};

// Test: When test case does NOT throw, isThrowSafe should return true regardless of allowThrows
TEST_F(IsThrowSafeTest_1013, NonThrowingTestCase_AllowThrowsTrue_ReturnsTrue_1013) {
    // Create a TestCaseInfo that does NOT have the "throws" property
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"NonThrowingTest", ""},
        Catch::SourceLineInfo("file.cpp", 1)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(true));

    // !throws() is true, so result should be true
    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_TRUE(result);
}

TEST_F(IsThrowSafeTest_1013, NonThrowingTestCase_AllowThrowsFalse_ReturnsTrue_1013) {
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"NonThrowingTest", ""},
        Catch::SourceLineInfo("file.cpp", 1)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(false));

    // !throws() is true, so result should be true
    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_TRUE(result);
}

// Test: When test case DOES throw and config allows throws, isThrowSafe should return true
TEST_F(IsThrowSafeTest_1013, ThrowingTestCase_AllowThrowsTrue_ReturnsTrue_1013) {
    // Create a TestCaseInfo with the !throws tag (or [!throws] tag) to set the throws property
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"ThrowingTest", "[!throws]"},
        Catch::SourceLineInfo("file.cpp", 1)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(true));

    // throws() is true, but allowThrows() is also true, so result should be true
    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_TRUE(result);
}

// Test: When test case DOES throw and config does NOT allow throws, isThrowSafe should return false
TEST_F(IsThrowSafeTest_1013, ThrowingTestCase_AllowThrowsFalse_ReturnsFalse_1013) {
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"ThrowingTest", "[!throws]"},
        Catch::SourceLineInfo("file.cpp", 1)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(false));

    // throws() is true and allowThrows() is false, so !throws() || allowThrows() = false || false = false
    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_FALSE(result);
}

// Test: Verify that allowThrows is actually queried from the config
TEST_F(IsThrowSafeTest_1013, AllowThrowsIsQueriedFromConfig_1013) {
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"ThrowingTest", "[!throws]"},
        Catch::SourceLineInfo("file.cpp", 1)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    // Since the test case throws, allowThrows should be called
    EXPECT_CALL(mockConfig, allowThrows()).WillOnce(::testing::Return(true));

    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_TRUE(result);
}

// Test: Verify logical OR short-circuit — if test doesn't throw, allowThrows may or may not be called
// The function uses: !throws() || allowThrows()
// When !throws() is true, allowThrows() might not be evaluated (short-circuit)
TEST_F(IsThrowSafeTest_1013, NonThrowingTestCase_ShortCircuit_1013) {
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"NonThrowingTest", ""},
        Catch::SourceLineInfo("file.cpp", 1)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    // allowThrows may or may not be called due to short-circuit evaluation
    // We just verify the result is true
    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(false));

    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_TRUE(result);
}

// Test: Multiple tags including throws
TEST_F(IsThrowSafeTest_1013, ThrowingTestWithMultipleTags_AllowThrowsFalse_ReturnsFalse_1013) {
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"TaggedThrowingTest", "[tag1][!throws][tag2]"},
        Catch::SourceLineInfo("file.cpp", 42)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(false));

    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_FALSE(result);
}

TEST_F(IsThrowSafeTest_1013, ThrowingTestWithMultipleTags_AllowThrowsTrue_ReturnsTrue_1013) {
    Catch::TestCaseInfo info(
        "TestClass"_catch_sr,
        Catch::NameAndTags{"TaggedThrowingTest", "[tag1][!throws][tag2]"},
        Catch::SourceLineInfo("file.cpp", 42)
    );

    Catch::TestCaseHandle handle(&info, &mockInvoker);

    ON_CALL(mockConfig, allowThrows()).WillByDefault(::testing::Return(true));

    bool result = Catch::isThrowSafe(handle, mockConfig);
    EXPECT_TRUE(result);
}
