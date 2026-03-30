// File: tests/assertion_handler_ctor_1081.tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 interfaces we exercise
#include "catch2/internal/catch_assertion_handler.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_stringref.hpp"
// Common Catch2 interfaces/types used by AssertionHandler
#include "catch2/interfaces/catch_interfaces_capture.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::ByRef;
using ::testing::Field;
using ::testing::Truly;

namespace Catch {

// Forward declare types that are part of Catch2 but not explicitly shown
// (These are pulled in by included Catch2 headers in a real build.)
struct AssertionInfo;

// ---- Test seam for global accessor used by AssertionHandler ----
// We provide a test-time definition that returns our mock.
static ::testing::NiceMock<class MockResultCapture>* g_mockCapture = nullptr;
IResultCapture& getResultCapture() {
    // This function is called from AssertionHandler's ctor.
    // We require it to be initialized in each test's SetUp.
    assert(g_mockCapture && "g_mockCapture must be set before use");
    return *g_mockCapture;
}

// ---- Mock of IResultCapture ----
class MockResultCapture : public IResultCapture {
public:
    // We only need to mock what is observed by the constructor.
    MOCK_METHOD(void, notifyAssertionStarted, (const AssertionInfo& info), (override));

    // Provide harmless defaults for all other pure virtuals to keep linker happy.
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
    MOCK_METHOD(void, handleMessage, (const AssertionInfo&, struct ResultWas::OfType, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedExceptionNotThrown, (const AssertionInfo&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleUnexpectedInflightException, (const AssertionInfo&, std::string&&, AssertionReaction&), (override));
    MOCK_METHOD(void, handleIncomplete, (const AssertionInfo&), (override));
    MOCK_METHOD(void, handleNonExpr, (const AssertionInfo&, struct ResultWas::OfType, AssertionReaction&), (override));
    MOCK_METHOD(bool, lastAssertionPassed, (), (override));
    MOCK_METHOD(void, assertionPassed, (), (override));
    MOCK_METHOD(const std::string, getCurrentTestName, (), (override));
    MOCK_METHOD(const AssertionResult*, getLastResult, (), (override));
    MOCK_METHOD(void, exceptionEarlyReported, (), (override));
};

} // namespace Catch

// --------- Custom matcher for AssertionInfo fields ---------
namespace {
using namespace Catch;

// We match by reading the publicly accessible fields of AssertionInfo.
// In Catch2, AssertionInfo contains: macroName, lineInfo, capturedExpression, resultDisposition.
MATCHER_P4(AssertionInfoMatches,
           expectedMacro, expectedLine, expectedCaptured, expectedFlags,
           "AssertionInfo matches ctor args") {
    // Access fields via their public names; this is interface-level observation.
    // If names differ in your tree, adjust here without touching CUT.
    return arg.macroName == static_cast<std::string>(expectedMacro) &&
           arg.capturedExpression == static_cast<std::string>(expectedCaptured) &&
           arg.lineInfo.file == expectedLine.file &&
           arg.lineInfo.line == expectedLine.line &&
           arg.resultDisposition == expectedFlags;
}

class AssertionHandlerCtorTest : public ::testing::Test {
protected:
    ::testing::NiceMock<Catch::MockResultCapture> mock_;
    void SetUp() override { Catch::g_mockCapture = &mock_; }
    void TearDown() override { Catch::g_mockCapture = nullptr; }
};

} // namespace

// ---------- Tests ----------

TEST_F(AssertionHandlerCtorTest, NotifiesResultCaptureOnConstruction_1081) {
    using namespace Catch;

    const StringRef macroName = "REQUIRE";
    const SourceLineInfo lineInfo{"file.cpp", 123};
    const StringRef captured = "x == 42";
    const auto flags = static_cast<ResultDisposition::Flags>(0);

    EXPECT_CALL(mock_, notifyAssertionStarted(_)).Times(1);

    // Constructor should be noexcept in practice, but we only assert no throw.
    ASSERT_NO_THROW(AssertionHandler(macroName, lineInfo, captured, flags));
}

TEST_F(AssertionHandlerCtorTest, PassesThroughAllFieldsToAssertionInfo_1081) {
    using namespace Catch;

    const StringRef macroName = "CHECK_THROWS";
    const SourceLineInfo lineInfo{"some/dir/test.cc", 777};
    const StringRef captured = "mayThrow()";
    const auto flags = static_cast<ResultDisposition::Flags>(0x55AA); // arbitrary non-zero mask

    EXPECT_CALL(mock_, notifyAssertionStarted(AssertionInfoMatches(macroName, lineInfo, captured, flags)))
        .Times(1);

    AssertionHandler handler(macroName, lineInfo, captured, flags);
    (void)handler; // unused
}

TEST_F(AssertionHandlerCtorTest, HandlesEmptyStringsAndZeroLine_1081) {
    using namespace Catch;

    const StringRef macroName = "";            // boundary: empty macro
    const SourceLineInfo lineInfo{"", 0};      // boundary: empty file, line 0
    const StringRef captured = "";             // boundary: empty expression
    const auto flags = static_cast<ResultDisposition::Flags>(0);

    EXPECT_CALL(mock_, notifyAssertionStarted(AssertionInfoMatches(macroName, lineInfo, captured, flags)))
        .Times(1);

    ASSERT_NO_THROW(AssertionHandler(macroName, lineInfo, captured, flags));
}

TEST_F(AssertionHandlerCtorTest, MultipleConstructionsTriggerMultipleNotifications_1081) {
    using namespace Catch;

    const StringRef macro1 = "REQUIRE";
    const SourceLineInfo line1{"a.cpp", 1};
    const StringRef expr1 = "a == b";
    const auto flags1 = static_cast<ResultDisposition::Flags>(0);

    const StringRef macro2 = "CHECK";
    const SourceLineInfo line2{"b.cpp", 2};
    const StringRef expr2 = "x < y";
    const auto flags2 = static_cast<ResultDisposition::Flags>(3);

    // We don't force call order; just that we get both with correct params.
    EXPECT_CALL(mock_, notifyAssertionStarted(AssertionInfoMatches(macro1, line1, expr1, flags1))).Times(1);
    EXPECT_CALL(mock_, notifyAssertionStarted(AssertionInfoMatches(macro2, line2, expr2, flags2))).Times(1);

    AssertionHandler h1(macro1, line1, expr1, flags1);
    AssertionHandler h2(macro2, line2, expr2, flags2);
    (void)h1; (void)h2;
}
