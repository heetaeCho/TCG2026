#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_message.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"
#include "catch2/internal/catch_context.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/internal/catch_move_and_forward.hpp"
#include "catch2/benchmark/catch_benchmark_stats.hpp"
#include "catch2/generators/catch_generator_exception.hpp"

using namespace Catch;
using ::testing::_;
using ::testing::NiceMock;

class MockResultCapture : public IResultCapture {
public:
    ~MockResultCapture() override = default;

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
    MOCK_METHOD(const std::string, getCurrentTestName, (), (const, override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (const, override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Helper to set up mock as the current result capture
class ScopedMessageTest_249 : public ::testing::Test {
protected:
    NiceMock<MockResultCapture> mockCapture;

    void SetUp() override {
        // We need to register our mock as the current result capture
        // This depends on Catch2's internal context mechanism
    }
};

// Test that destructor calls popScopedMessage when not moved
TEST_F(ScopedMessageTest_249, DestructorCallsPopScopedMessage_249) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    // Create a ScopedMessage and let it go out of scope
    {
        MessageBuilder builder("test_macro", SourceLineInfo("file", 1), ResultWas::Info);
        builder << "test message";
        // The constructor should call pushScopedMessage
        ScopedMessage msg(CATCH_MOVE(builder));
        // Destructor should call popScopedMessage
    }
}

// Test that moved-from ScopedMessage does NOT call popScopedMessage
TEST_F(ScopedMessageTest_249, MovedMessageDoesNotPopOnDestruction_249) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    // popScopedMessage should be called exactly once (by the moved-to object, not the moved-from)
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        MessageBuilder builder("test_macro", SourceLineInfo("file", 2), ResultWas::Info);
        builder << "move test";
        ScopedMessage original(CATCH_MOVE(builder));

        // Move construct - old should be marked as moved
        ScopedMessage moved(std::move(original));
        // original.m_moved should now be true
        EXPECT_TRUE(original.m_moved);
    }
}

// Test that m_moved is initially false
TEST_F(ScopedMessageTest_249, InitialMovedIsFalse_249) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    MessageBuilder builder("test_macro", SourceLineInfo("file", 3), ResultWas::Info);
    builder << "initial state test";
    ScopedMessage msg(CATCH_MOVE(builder));
    EXPECT_FALSE(msg.m_moved);
}

// Test that move constructor sets m_moved on source
TEST_F(ScopedMessageTest_249, MoveConstructorSetsMovedFlag_249) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    MessageBuilder builder("test_macro", SourceLineInfo("file", 4), ResultWas::Info);
    builder << "flag test";
    ScopedMessage original(CATCH_MOVE(builder));

    EXPECT_FALSE(original.m_moved);
    ScopedMessage moved(std::move(original));
    EXPECT_TRUE(original.m_moved);
    EXPECT_FALSE(moved.m_moved);
}

// Test that copy constructor is deleted (compile-time check - we verify it doesn't compile)
// This is a static assertion test - we just document that ScopedMessage is not copyable
TEST_F(ScopedMessageTest_249, ScopedMessageIsNotCopyable_249) {
    EXPECT_FALSE(std::is_copy_constructible<ScopedMessage>::value);
}

// Test that ScopedMessage is move constructible
TEST_F(ScopedMessageTest_249, ScopedMessageIsMoveConstructible_249) {
    EXPECT_TRUE(std::is_move_constructible<ScopedMessage>::value);
}

// Test multiple scoped messages - each should push and pop
TEST_F(ScopedMessageTest_249, MultipleScopedMessagesEachPopOnDestruction_249) {
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(2);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(2);

    {
        MessageBuilder builder1("macro1", SourceLineInfo("file", 10), ResultWas::Info);
        builder1 << "message 1";
        ScopedMessage msg1(CATCH_MOVE(builder1));

        MessageBuilder builder2("macro2", SourceLineInfo("file", 11), ResultWas::Info);
        builder2 << "message 2";
        ScopedMessage msg2(CATCH_MOVE(builder2));
    }
}

// Test nested scope behavior - LIFO order of destruction
TEST_F(ScopedMessageTest_249, NestedScopesPopInReverseOrder_249) {
    ::testing::InSequence seq;

    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, pushScopedMessage(_)).Times(1);
    // Inner scope destroyed first
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);
    EXPECT_CALL(mockCapture, popScopedMessage(_)).Times(1);

    {
        MessageBuilder builder1("macro1", SourceLineInfo("file", 20), ResultWas::Info);
        builder1 << "outer";
        ScopedMessage outer(CATCH_MOVE(builder1));

        {
            MessageBuilder builder2("macro2", SourceLineInfo("file", 21), ResultWas::Info);
            builder2 << "inner";
            ScopedMessage inner(CATCH_MOVE(builder2));
        }
    }
}
