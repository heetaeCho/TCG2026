// File: capturer_capture_value_tests_251.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/catch_message.hpp"
#include "catch2/interfaces/catch_interfaces_capture.hpp"

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrictMock;

namespace Catch {

// ---- Test double for IResultCapture (external collaborator) ----
class MockResultCapture : public IResultCapture {
public:
  // We only care about pushScopedMessage for these tests.
  MOCK_METHOD(void, pushScopedMessage, (const MessageInfo& message), (override));

  // Provide no-op overrides to satisfy the vtable if needed.
  // (Signatures follow the provided interface; all are no-ops.)
  void popScopedMessage (const MessageInfo&) override {}
  void notifyAssertionStarted (const AssertionInfo&) override {}
  bool sectionStarted (StringRef, const SourceLineInfo&, Counts&) override { return true; }
  void sectionEnded (SectionEndInfo&&) override {}
  void sectionEndedEarly (SectionEndInfo&&) override {}
  IGeneratorTracker* acquireGeneratorTracker (StringRef, const SourceLineInfo&) override { return nullptr; }
  IGeneratorTracker* createGeneratorTracker (StringRef, SourceLineInfo, Generators::GeneratorBasePtr&&) override { return nullptr; }
  void benchmarkPreparing (StringRef) override {}
  void benchmarkStarting (const BenchmarkInfo&) override {}
  void benchmarkEnded (const BenchmarkStats<>&) override {}
  void benchmarkFailed (StringRef) override {}
  void emplaceUnscopedMessage (MessageBuilder&&) override {}
  void handleFatalErrorCondition (StringRef) override {}
  void handleExpr (const AssertionInfo&, const ITransientExpression&, AssertionReaction&) override {}
  void handleMessage (const AssertionInfo&, ResultWas::OfType, std::string&&, AssertionReaction&) override {}
  void handleUnexpectedExceptionNotThrown (const AssertionInfo&, AssertionReaction&) override {}
  void handleUnexpectedInflightException (const AssertionInfo&, std::string&&, AssertionReaction&) override {}
  void handleIncomplete (const AssertionInfo&) override {}
  void handleNonExpr (const AssertionInfo&, ResultWas::OfType, AssertionReaction&) override {}
  bool lastAssertionPassed () override { return true; }
  void assertionPassed () override {}
  const std::string getCurrentTestName () override { return "test"; }
  const AssertionResult* getLastResult () override { return nullptr; }
  void exceptionEarlyReported () override {}
};

// ---- Test-side provider for the dependency that Capturer uses ----
// The production code calls getResultCapture(); for the unit test
// we provide a test implementation that returns our mock.
static StrictMock<MockResultCapture>* g_mockCapture = nullptr;

IResultCapture& getResultCapture() {
  assert(g_mockCapture && "Test mock must be installed before constructing Capturer");
  return *g_mockCapture;
}

} // namespace Catch

// ---- Test fixture ----
class CapturerCaptureValueTest_251 : public ::testing::Test {
protected:
  void SetUp() override {
    // Install the mock instance for this test.
    mockInstance = std::make_unique<::testing::StrictMock<Catch::MockResultCapture>>();
    Catch::g_mockCapture = mockInstance.get();
  }
  void TearDown() override {
    Catch::g_mockCapture = nullptr;
  }

  // Helpers to create constructor arguments without depending on internals
  static Catch::StringRef Str(const char* s) { return Catch::StringRef{s}; }
  static Catch::SourceLineInfo Line(const char* file, std::size_t line) { return Catch::SourceLineInfo{file, line}; }

  std::unique_ptr<::testing::StrictMock<Catch::MockResultCapture>> mockInstance;
};

// --- Normal operation: pushes a scoped message exactly once for valid index ---
TEST_F(CapturerCaptureValueTest_251, PushesScopedMessageOnceOnValidIndex_251) {
  using namespace Catch;

  // Expect a single push for a single capture
  EXPECT_CALL(*mockInstance, pushScopedMessage(_)).Times(1);

  // names with two entries so index 0 is valid (treating constructor as black box)
  Capturer cap(Str("MACRO"), Line("file.cpp", 123), ResultWas::OfType::Info, Str("a,b"));
  cap.captureValue(/*index=*/0, std::string{"first"});
}

// --- Multiple captures on same index: each call pushes a scoped message ---
TEST_F(CapturerCaptureValueTest_251, MultipleCapturesTriggerMultiplePushes_251) {
  using namespace Catch;

  InSequence seq;
  EXPECT_CALL(*mockInstance, pushScopedMessage(_));
  EXPECT_CALL(*mockInstance, pushScopedMessage(_));

  Capturer cap(Str("MACRO"), Line("file.cpp", 10), ResultWas::OfType::Info, Str("x"));
  cap.captureValue(0, std::string{"alpha"});
  cap.captureValue(0, std::string{"beta"});
}

// --- Capturing to different indices: pushes for each valid index ---
TEST_F(CapturerCaptureValueTest_251, CapturingOnDifferentValidIndicesEachPushes_251) {
  using namespace Catch;

  InSequence seq;
  EXPECT_CALL(*mockInstance, pushScopedMessage(_));
  EXPECT_CALL(*mockInstance, pushScopedMessage(_));

  Capturer cap(Str("MACRO"), Line("file.cpp", 77), ResultWas::OfType::Info, Str("left,right"));
  cap.captureValue(0, std::string{"L"});
  cap.captureValue(1, std::string{"R"});
}

// --- Boundary: out-of-range index must assert (death test) ---
#if !defined(NDEBUG)
TEST_F(CapturerCaptureValueTest_251, CaptureValueWithOutOfRangeIndexAsserts_251) {
  using namespace Catch;

  // No push expected because we assert before any interaction
  // Create with a single capture slot (names "only")
  Capturer cap(Str("MACRO"), Line("t.cpp", 1), ResultWas::OfType::Info, Str("only"));

  // index 1 is out of range if there is a single slot at index 0
  EXPECT_DEATH({ cap.captureValue(1, std::string{"boom"}); }, "");
}
#endif
