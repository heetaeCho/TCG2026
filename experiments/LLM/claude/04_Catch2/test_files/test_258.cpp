#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>

#include "catch2/catch_tostring.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/interfaces/catch_interfaces_config.hpp"
#include "catch2/internal/catch_context.hpp"

using namespace Catch;

// Mock IConfig to control showInvisibles() behavior
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

class ConvertIntoStringTest_258 : public ::testing::Test {
protected:
    MockConfig mockConfig;

    void SetUp() override {
        getCurrentMutableContext().setConfig(&mockConfig);
    }

    void TearDown() override {
        getCurrentMutableContext().setConfig(nullptr);
    }
};

// Test with a normal string and showInvisibles = false
TEST_F(ConvertIntoStringTest_258, NormalStringShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string result = Detail::convertIntoString(StringRef("hello world"));
    EXPECT_EQ(result, "hello world");
}

// Test with a normal string and showInvisibles = true
TEST_F(ConvertIntoStringTest_258, NormalStringShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("hello world"));
    // The result should contain "hello world" — invisible chars might be decorated
    // but "hello world" has no invisible chars beyond the space
    EXPECT_FALSE(result.empty());
}

// Test with an empty string
TEST_F(ConvertIntoStringTest_258, EmptyStringShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string result = Detail::convertIntoString(StringRef(""));
    EXPECT_EQ(result, "");
}

// Test with an empty string and showInvisibles = true
TEST_F(ConvertIntoStringTest_258, EmptyStringShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef(""));
    EXPECT_EQ(result, "");
}

// Test with string containing tab character and showInvisibles = false
TEST_F(ConvertIntoStringTest_258, StringWithTabShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string result = Detail::convertIntoString(StringRef("hello\tworld"));
    // With showInvisibles false, the tab should appear as-is
    EXPECT_EQ(result, "hello\tworld");
}

// Test with string containing tab character and showInvisibles = true
TEST_F(ConvertIntoStringTest_258, StringWithTabShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("hello\tworld"));
    // With showInvisibles true, the tab should be replaced/decorated
    // The exact representation depends on implementation, but it should differ
    // from the raw string
    EXPECT_NE(result, "hello\tworld");
}

// Test with string containing newline and showInvisibles = false
TEST_F(ConvertIntoStringTest_258, StringWithNewlineShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string result = Detail::convertIntoString(StringRef("hello\nworld"));
    EXPECT_EQ(result, "hello\nworld");
}

// Test with string containing newline and showInvisibles = true
TEST_F(ConvertIntoStringTest_258, StringWithNewlineShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("hello\nworld"));
    // With showInvisibles true, newline should be made visible
    EXPECT_NE(result, "hello\nworld");
}

// Test with string containing carriage return and showInvisibles = true
TEST_F(ConvertIntoStringTest_258, StringWithCarriageReturnShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("hello\rworld"));
    // With showInvisibles true, carriage return should be made visible
    EXPECT_NE(result, "hello\rworld");
}

// Test with string containing only spaces - showInvisibles false
TEST_F(ConvertIntoStringTest_258, StringWithSpacesShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string result = Detail::convertIntoString(StringRef("   "));
    EXPECT_EQ(result, "   ");
}

// Test with string containing only spaces - showInvisibles true
TEST_F(ConvertIntoStringTest_258, StringWithSpacesShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("   "));
    // Spaces might be made visible or left as-is depending on implementation
    EXPECT_FALSE(result.empty());
}

// Test with a long string
TEST_F(ConvertIntoStringTest_258, LongStringShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string longStr(1000, 'a');
    std::string result = Detail::convertIntoString(StringRef(longStr));
    EXPECT_EQ(result, longStr);
}

// Test with a single character string
TEST_F(ConvertIntoStringTest_258, SingleCharStringShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string result = Detail::convertIntoString(StringRef("x"));
    EXPECT_EQ(result, "x");
}

// Test that showInvisibles is actually queried from config
TEST_F(ConvertIntoStringTest_258, ConfigShowInvisiblesIsCalled_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .Times(::testing::AtLeast(1))
        .WillRepeatedly(::testing::Return(false));

    Detail::convertIntoString(StringRef("test"));
}

// Test with multiple invisible characters
TEST_F(ConvertIntoStringTest_258, MultipleInvisibleCharsShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("\t\n\r"));
    // All invisible chars should be made visible
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "\t\n\r");
}

// Test with mixed visible and invisible chars, showInvisibles true
TEST_F(ConvertIntoStringTest_258, MixedVisibleInvisibleShowInvisiblesTrue_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(true));

    std::string result = Detail::convertIntoString(StringRef("a\tb\nc"));
    // Result should not be empty and should differ from raw
    EXPECT_FALSE(result.empty());
    EXPECT_NE(result, "a\tb\nc");
}

// Test with StringRef constructed from std::string
TEST_F(ConvertIntoStringTest_258, StdStringInputShowInvisiblesFalse_258) {
    EXPECT_CALL(mockConfig, showInvisibles())
        .WillRepeatedly(::testing::Return(false));

    std::string input = "hello from std::string";
    std::string result = Detail::convertIntoString(StringRef(input));
    EXPECT_EQ(result, input);
}
