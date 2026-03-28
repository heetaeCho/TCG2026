// File: scoped_message_tests_1053.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include the public Catch2 interfaces we interact with
#include "Catch2/src/catch2/catch_message.hpp"
#include "Catch2/src/catch2/catch_message.cpp"            // for the constructor behavior under test
#include "Catch2/src/catch2/interfaces/catch_interfaces_capture.hpp"
#include "Catch2/src/catch2/internal/catch_message_info.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;
using ::testing::Truly;

namespace {

// ---- Test double wiring for getResultCapture() ----
// We provide a definition of getResultCapture() that returns our mock.
// This is the sole seam we use to observe interactions.
class MockResultCapture : public Catch::IResultCapture {
public:
    // We only care about pushScopedMessage for these tests.
    MOCK_METHOD(void, pushScopedMessage, (const Catch::MessageInfo&), (override));

    // Provide no-op overrides for the rest to satisfy the interface
    // (they are virtual, not pure, in the provided snippet, but overriding a few
    // avoids link surprises across different builds).
    MOCK_METHOD(void, popScopedMessage, (const Catch::MessageInfo&), (override));
    MOCK_METHOD(void, emplaceUnscopedMessage, (Catch::MessageBuilder&&), (override));
    MOCK_METHOD(void, notifyAssertionStarted, (const Catch::AssertionInfo&), (override));
    MOCK_METHOD(bool, sectionStarted,
                (Catch::StringRef, const Catch::SourceLineInfo&, Catch::Counts&), (override));
    MOCK_METHOD(void, sectionEnded, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(void, sectionEndedEarly, (Catch::SectionEndInfo&&), (override));
    MOCK_METHOD(Catch::IGeneratorTracker*, acquireGeneratorTracker,
                (Catch::StringRef, const Catch::SourceLineInfo&), (override));
    MOCK_METHOD(Catch::IGeneratorTracker*, createGeneratorTracker,
                (Catch::StringRef, Catch::SourceLineInfo, Catch::Generators::GeneratorBasePtr&&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (Catch::StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (const Catch::BenchmarkInfo&), (override));
    MOCK_METHOD(void, benchmarkEnded, ((const Catch::BenchmarkStats<> &)), (override));
    MOCK_METHOD(void, benchmarkFailed, (Catch::StringRef), (override));
    MOCK_METHOD(void, handleFatalErrorCondition, (Catch::StringRef), (override));
    MOCK_METHOD(void, handleExpr,
                (const Catch::AssertionInfo&, const Catch::ITransientExpression&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleMessage,
                (const Catch::AssertionInfo&, Catch::ResultWas::OfType, std::string&&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown,
                (const Catch::AssertionInfo&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException,
                (const Catch::AssertionInfo&, std::string&&, Catch::AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const Catch::AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr,
                (const Catch::AssertionInfo&, Catch::ResultWas::OfType, Catch::AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const Catch::AssertionResult*, getLastResult, (), (override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

// Global pointer used by our getResultCapture definition.
static MockResultCapture* g_mockCapture = nullptr;

} // namespace

// Provide the function used by ScopedMessage's constructor.
namespace Catch {
    IResultCapture& getResultCapture() {
        // We expect tests to set g_mockCapture before creating ScopedMessage.
        return *g_mockCapture;
    }
}

class ScopedMessageTest_1053 : public ::testing::Test {
protected:
    MockResultCapture mock_;
    void SetUp() override { g_mockCapture = &mock_; }
    void TearDown() override { g_mockCapture = nullptr; }
};

// Helper to build a MessageBuilder with typical inputs
static Catch::MessageBuilder MakeBuilder(const char* macro,
                                         const char* file,
                                         std::size_t line,
                                         Catch::ResultWas::OfType type) {
    return Catch::MessageBuilder(Catch::StringRef(macro),
                                 Catch::SourceLineInfo(file, line),
                                 type);
}

// --- TESTS ---

// Verifies: constructing ScopedMessage from MessageBuilder pushes exactly once,
// and the pushed MessageInfo carries the streamed message text.
TEST_F(ScopedMessageTest_1053, PushesMessageOnConstruction_1053) {
    using Catch::ResultWas;

    auto builder = MakeBuilder("MY_MACRO", "file.cpp", 123, ResultWas::Info);
    // Stream some content into the builder (observable via message string)
    std::move(builder) << "hello " << 42;

    // Expect a single push with message == "hello 42"
    EXPECT_CALL(mock_, pushScopedMessage(testing::Property(
        &Catch::MessageInfo::message, testing::Eq(std::string("hello 42")))
    )).Times(1);

    // Act: constructing the ScopedMessage should trigger the push
    Catch::ScopedMessage sm(MakeBuilder("MY_MACRO", "file.cpp", 123, ResultWas::Info) << "hello " << 42);
}

// Verifies: if nothing is streamed, an empty message is pushed.
TEST_F(ScopedMessageTest_1053, EmptyMessageIsPushed_1053) {
    using Catch::ResultWas;

    auto builder = MakeBuilder("EMPTY_MACRO", "empty.cpp", 10, ResultWas::Info);

    EXPECT_CALL(mock_, pushScopedMessage(testing::Property(
        &Catch::MessageInfo::message, testing::Eq(std::string()))
    )).Times(1);

    Catch::ScopedMessage sm(std::move(builder));
}

// Verifies: multiple insertions concatenate as usual ostream semantics.
TEST_F(ScopedMessageTest_1053, MultipleInsertionsConcatenate_1053) {
    using Catch::ResultWas;

    auto builder = MakeBuilder("CAT", "c.cpp", 7, ResultWas::Info);
    std::move(builder) << "foo" << ' ' << 123;

    EXPECT_CALL(mock_, pushScopedMessage(testing::Property(
        &Catch::MessageInfo::message, testing::Eq(std::string("foo 123")))
    )).Times(1);

    Catch::ScopedMessage sm(MakeBuilder("CAT", "c.cpp", 7, ResultWas::Info) << "foo" << ' ' << 123);
}

// Verifies: moving a ScopedMessage does NOT cause another push (constructor only).
TEST_F(ScopedMessageTest_1053, MoveCtorDoesNotPushAgain_1053) {
    using Catch::ResultWas;

    // First construction -> expect exactly one push
    EXPECT_CALL(mock_, pushScopedMessage(_)).Times(1);

    Catch::ScopedMessage sm(MakeBuilder("MOVE", "m.cpp", 1, ResultWas::Info) << "m1");
    // Move-construct a new instance. No new push should happen.
    Catch::ScopedMessage sm2(std::move(sm));
}

