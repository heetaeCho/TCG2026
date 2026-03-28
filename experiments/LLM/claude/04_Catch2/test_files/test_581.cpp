#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_section.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_timer.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;

class MockResultCapture : public IResultCapture {
public:
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted, (StringRef, const SourceLineInfo&, Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (SectionEndInfo&&), (override));
    MOCK_METHOD(IGeneratorTracker*, acquireGeneratorTracker, (StringRef, const SourceLineInfo&), (override));
    MOCK_METHOD(IGeneratorTracker*, createGeneratorTracker, (StringRef, SourceLineInfo, Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, (const BenchmarkStats<>&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    MOCK_METHOD(void, pushScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, popScopedMessage, (const MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (MessageBuilder&&), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (StringRef), (override));
    MOCK_METHOD(void, handleExpr, (const AssertionInfo&, const ITransientExpression&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage, (const AssertionInfo&, ResultWas::OfType, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo&, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo&, ResultWas::OfType, AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// We need to be able to inject the mock as the result capture.
// In Catch2, getResultCapture() returns IResultCapture&.
// We assume there's a way to set it up for testing. If Catch2 uses
// a global/context pattern, we need to set up a context with our mock.

class SectionTest_581 : public ::testing::Test {
protected:
    MockResultCapture mockCapture;

    void SetUp() override {
        // Set the mock as the current result capture
        // This depends on Catch2 internals for injecting the mock
        // Typically Catch2 uses IContext/IMutableContext
    }

    void TearDown() override {
    }

    SectionInfo makeSectionInfo(const std::string& name = "test section") {
        return SectionInfo(SourceLineInfo("test_file.cpp", 42), name);
    }
};

// Test: When sectionStarted returns true, Section is included (operator bool returns true)
TEST_F(SectionTest_581, SectionIncludedWhenStartedReturnsTrue_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        Section section(makeSectionInfo("included section"));
        EXPECT_TRUE(static_cast<bool>(section));
    }
}

// Test: When sectionStarted returns false, Section is not included (operator bool returns false)
TEST_F(SectionTest_581, SectionNotIncludedWhenStartedReturnsFalse_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(false));
    // Neither sectionEnded nor sectionEndedEarly should be called
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(0);
    EXPECT_CALL(mockCapture, sectionEndedEarly(_)).Times(0);

    {
        Section section(makeSectionInfo("excluded section"));
        EXPECT_FALSE(static_cast<bool>(section));
    }
}

// Test: Destructor calls sectionEnded when included and no uncaught exceptions
TEST_F(SectionTest_581, DestructorCallsSectionEndedNormally_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);
    EXPECT_CALL(mockCapture, sectionEndedEarly(_)).Times(0);

    {
        Section section(makeSectionInfo("normal end"));
    }
}

// Test: Destructor does not call sectionEnded or sectionEndedEarly when not included
TEST_F(SectionTest_581, DestructorDoesNothingWhenNotIncluded_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(false));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(0);
    EXPECT_CALL(mockCapture, sectionEndedEarly(_)).Times(0);

    {
        Section section(makeSectionInfo("not included"));
    }
}

// Test: SectionEndInfo contains the correct section name
TEST_F(SectionTest_581, SectionEndInfoContainsCorrectName_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_))
        .WillOnce(Invoke([](SectionEndInfo&& endInfo) {
            EXPECT_EQ(endInfo.sectionInfo.name, "my named section");
        }));

    {
        Section section(makeSectionInfo("my named section"));
    }
}

// Test: SectionEndInfo duration is non-negative
TEST_F(SectionTest_581, SectionEndInfoHasNonNegativeDuration_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_))
        .WillOnce(Invoke([](SectionEndInfo&& endInfo) {
            EXPECT_GE(endInfo.durationInSeconds, 0.0);
        }));

    {
        Section section(makeSectionInfo("duration check"));
    }
}

// Test: Section constructed with SourceLineInfo and name
TEST_F(SectionTest_581, ConstructWithSourceLineInfoAndName_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(1);

    {
        SourceLineInfo lineInfo("file.cpp", 100);
        Section section(lineInfo, "alternate constructor"_catch_sr, nullptr);
        EXPECT_TRUE(static_cast<bool>(section));
    }
}

// Test: Section constructed with SourceLineInfo and name, not included
TEST_F(SectionTest_581, ConstructWithSourceLineInfoNotIncluded_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(false));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(0);

    {
        SourceLineInfo lineInfo("file.cpp", 200);
        Section section(lineInfo, "not included alt"_catch_sr, nullptr);
        EXPECT_FALSE(static_cast<bool>(section));
    }
}

// Test: SectionEndInfo contains line info from construction
TEST_F(SectionTest_581, SectionEndInfoContainsLineInfo_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_))
        .WillOnce(Invoke([](SectionEndInfo&& endInfo) {
            EXPECT_EQ(endInfo.sectionInfo.lineInfo.line, 42u);
            EXPECT_STREQ(endInfo.sectionInfo.lineInfo.file, "test_file.cpp");
        }));

    {
        Section section(makeSectionInfo("line info check"));
    }
}

// Test: Multiple sections can be created sequentially
TEST_F(SectionTest_581, MultipleSequentialSections_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_)).Times(2);

    {
        Section section1(makeSectionInfo("section 1"));
    }
    {
        Section section2(makeSectionInfo("section 2"));
    }
}

// Test: Section with empty name
TEST_F(SectionTest_581, SectionWithEmptyName_581) {
    EXPECT_CALL(mockCapture, sectionStarted(_, _, _))
        .WillOnce(Return(true));
    EXPECT_CALL(mockCapture, sectionEnded(_))
        .WillOnce(Invoke([](SectionEndInfo&& endInfo) {
            EXPECT_TRUE(endInfo.sectionInfo.name.empty());
        }));

    {
        Section section(makeSectionInfo(""));
    }
}
