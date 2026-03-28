#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <cstdint>

// Include necessary Catch2 headers
#include "catch2/internal/catch_section.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/catch_timer.hpp"
#include "catch2/internal/catch_context.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::NiceMock;

// Mock for IResultCapture
class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo& info), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef sectionName, const SourceLineInfo& sectionLineInfo, Counts& assertions), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&& endInfo), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&& endInfo), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef generatorName, const SourceLineInfo& lineInfo), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef generatorName, SourceLineInfo lineInfo, Generators::GeneratorBasePtr&& generator), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef name), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo& info), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>& stats), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef error), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo& message), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo& message), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&& builder), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef message), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo& info, const ITransientExpression& expr, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo& info, ResultWas::OfType resultType, std::string&& message, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo& info, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo& info, std::string&& message, AssertionReaction& reaction), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo& info), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo& info, ResultWas::OfType resultType, AssertionReaction& reaction), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Helper to set and restore result capture context
class SectionTestFixture_1089 : public ::testing::Test {
protected:
    NiceMock<MockResultCapture> mockCapture;

    void SetUp() override {
        // We need to install our mock as the result capture.
        // In Catch2, getResultCapture() returns the current IResultCapture from the context.
        // We need to set it via the context mechanism.
        Catch::IContext* ctx = &Catch::getCurrentMutableContext();
        ctx->setResultCapture(&mockCapture);
    }

    void TearDown() override {
        // Reset to avoid dangling pointer
        Catch::IContext* ctx = &Catch::getCurrentMutableContext();
        ctx->setResultCapture(nullptr);
    }
};

// Test: Section constructor calls sectionStarted and when it returns true, section is included
TEST_F(SectionTestFixture_1089, SectionIncludedWhenSectionStartedReturnsTrue_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("test_file.cpp", 10), "TestSection"));
        // Section should be truthy when included
        EXPECT_TRUE(static_cast<bool>(section));
    }
}

// Test: Section constructor calls sectionStarted and when it returns false, section is not included
TEST_F(SectionTestFixture_1089, SectionNotIncludedWhenSectionStartedReturnsFalse_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(false));
    // sectionEnded should NOT be called when section was not included
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(0);

    {
        Section section(SectionInfo(SourceLineInfo("test_file.cpp", 20), "SkippedSection"));
        // Section should be falsy when not included
        EXPECT_FALSE(static_cast<bool>(section));
    }
}

// Test: Section constructor passes correct section name to sectionStarted
TEST_F(SectionTestFixture_1089, SectionPassesCorrectNameToSectionStarted_1089) {
    std::string capturedName;
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Invoke([&capturedName](StringRef sectionName, const SourceLineInfo&, Counts&) -> bool {
            capturedName = std::string(sectionName);
            return true;
        }));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("file.cpp", 5), "MySpecificSection"));
    }

    EXPECT_EQ(capturedName, "MySpecificSection");
}

// Test: Section constructor passes correct line info to sectionStarted
TEST_F(SectionTestFixture_1089, SectionPassesCorrectLineInfoToSectionStarted_1089) {
    SourceLineInfo capturedLineInfo("", 0);
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Invoke([&capturedLineInfo](StringRef, const SourceLineInfo& lineInfo, Counts&) -> bool {
            capturedLineInfo = lineInfo;
            return true;
        }));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("myfile.cpp", 42), "SectionName"));
    }

    EXPECT_EQ(capturedLineInfo.line, 42u);
}

// Test: Section with empty name
TEST_F(SectionTestFixture_1089, SectionWithEmptyName_1089) {
    std::string capturedName;
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Invoke([&capturedName](StringRef sectionName, const SourceLineInfo&, Counts&) -> bool {
            capturedName = std::string(sectionName);
            return true;
        }));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("file.cpp", 1), ""));
    }

    EXPECT_EQ(capturedName, "");
}

// Test: Section destructor calls sectionEnded when section was included
TEST_F(SectionTestFixture_1089, DestructorCallsSectionEndedWhenIncluded_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("test.cpp", 100), "EndedSection"));
        // destructor should trigger sectionEnded
    }
}

// Test: Section destructor does not call sectionEnded when section was not included
TEST_F(SectionTestFixture_1089, DestructorDoesNotCallSectionEndedWhenNotIncluded_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(false));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(0);

    {
        Section section(SectionInfo(SourceLineInfo("test.cpp", 200), "NotEndedSection"));
    }
}

// Test: Section constructed with SourceLineInfo and StringRef overload
TEST_F(SectionTestFixture_1089, SectionConstructedWithSourceLineInfoAndStringRef_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SourceLineInfo("alt_file.cpp", 77), "AlternateConstructor", nullptr);
        EXPECT_TRUE(static_cast<bool>(section));
    }
}

// Test: Multiple sections sequentially, first included, second not
TEST_F(SectionTestFixture_1089, MultipleSectionsSequentially_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true))
        .WillOnce(Return(false));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section1(SectionInfo(SourceLineInfo("file.cpp", 1), "First"));
        EXPECT_TRUE(static_cast<bool>(section1));
    }
    {
        Section section2(SectionInfo(SourceLineInfo("file.cpp", 2), "Second"));
        EXPECT_FALSE(static_cast<bool>(section2));
    }
}

// Test: Section with very long name
TEST_F(SectionTestFixture_1089, SectionWithVeryLongName_1089) {
    std::string longName(10000, 'x');
    std::string capturedName;

    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Invoke([&capturedName](StringRef sectionName, const SourceLineInfo&, Counts&) -> bool {
            capturedName = std::string(sectionName);
            return true;
        }));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("file.cpp", 1), longName));
    }

    EXPECT_EQ(capturedName, longName);
}

// Test: operator bool consistency - calling it multiple times returns same value
TEST_F(SectionTestFixture_1089, OperatorBoolIsConsistent_1089) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(SectionInfo(SourceLineInfo("file.cpp", 1), "ConsistentSection"));
        bool first = static_cast<bool>(section);
        bool second = static_cast<bool>(section);
        EXPECT_EQ(first, second);
        EXPECT_TRUE(first);
    }
}
