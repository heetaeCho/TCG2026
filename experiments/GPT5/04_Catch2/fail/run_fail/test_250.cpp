// File: capturer_dtor_tests_250.cpp
#include <gtest/gtest.h>
#include <gmock/gmock.h>

using ::testing::_;
using ::testing::InSequence;
using ::testing::Exactly;
using ::testing::AtLeast;
using ::testing::NiceMock;

// ===== Minimal scaffolding (non-behavioral) to satisfy the interface =====
namespace Catch {

struct StringRef {
  const char* s{};
  StringRef() = default;
  StringRef(const char* str) : s(str) {}
  operator const char*() const { return s; }
};

struct SourceLineInfo {
  const char* file;
  int line;
};

namespace ResultWas { enum OfType { Ok = 0 }; }

// Forward decl per header snippets
struct MessageInfo {
  // Content not needed for interaction verification
  // Only the type is required for mock signatures
};

// IResultCapture interface (as provided)
class IResultCapture {
public:
  virtual ~IResultCapture() = default;
  virtual void notifyAssertionStarted(const int&) {}
  virtual bool sectionStarted(StringRef, const SourceLineInfo&, int&) { return true; }
  virtual void sectionEnded(int&&) {}
  virtual void sectionEndedEarly(int&&) {}
  virtual void* acquireGeneratorTracker(StringRef, const SourceLineInfo&) { return nullptr; }
  virtual void* createGeneratorTracker(StringRef, SourceLineInfo, void*&&) { return nullptr; }
  virtual void benchmarkPreparing(StringRef) {}
  virtual void benchmarkStarting(const int&) {}
  virtual void benchmarkEnded(const int&) {}
  virtual void benchmarkFailed(StringRef) {}
  virtual void pushScopedMessage(const MessageInfo&) {}
  virtual void popScopedMessage(const MessageInfo&) {}
  virtual void emplaceUnscopedMessage(int&&) {}
  virtual void handleFatalErrorCondition(StringRef) {}
  virtual void handleExpr(const int&, const int&, int&) {}
  virtual void handleMessage(const int&, ResultWas::OfType, std::string&&, int&) {}
  virtual void handleUnexpectedExceptionNotThrown(const int&, int&) {}
  virtual void handleUnexpectedInflightException(const int&, std::string&&, int&) {}
  virtual void handleIncomplete(const int&) {}
  virtual void handleNonExpr(const int&, ResultWas::OfType, int&) {}
  virtual bool lastAssertionPassed() { return true; }
  virtual void assertionPassed() {}
  virtual const std::string getCurrentTestName() { return "dummy"; }
  virtual const void* getLastResult() { return nullptr; }
  virtual void exceptionEarlyReported() {}
};

// getResultCapture is used by Capturer's ctor; we’ll provide it in tests
IResultCapture& getResultCapture();

class Capturer {
public:
  // Ctor signature from the header
  Capturer(StringRef macroName,
           SourceLineInfo const& lineInfo,
           ResultWas::OfType resultType,
           StringRef names);
  // Public API we are allowed to use
  void captureValue(size_t index, const std::string& value);
  // Dtor under test
  ~Capturer();
};

} // namespace Catch

// ===== Test doubles and linkage glue =====
namespace {
Catch::IResultCapture* g_resultCaptureMock = nullptr;
}

namespace Catch {
IResultCapture& getResultCapture() {
  // The CUT calls this; route to our test mock
  return *g_resultCaptureMock;
}
} // namespace Catch

// A strict mock only for interactions we verify (others defaulted)
class MockResultCapture : public Catch::IResultCapture {
public:
  MOCK_METHOD(void, popScopedMessage, (const Catch::MessageInfo&), (override));
  // We do not assert on push or others here; they’re not part of this test’s contract
};

// ===== Helper to construct a Capturer with dummy args =====
static Catch::Capturer MakeCapturer() {
  static const Catch::SourceLineInfo kLine{"file.cpp", 123};
  return Catch::Capturer{"MACRO", kLine, Catch::ResultWas::Ok, "x,y"};
}

// ===== Test Fixture =====
class CapturerDtorTest_250 : public ::testing::Test {
protected:
  NiceMock<MockResultCapture> mock_; // Nice to ignore unrelated calls
  void SetUp() override { g_resultCaptureMock = &mock_; }
  void TearDown() override { g_resultCaptureMock = nullptr; }
};

// --- TESTS ---

// 1) Normal path: when no exception is active, the destructor must pop
//    previously captured messages. We treat captureValue as a public, observable
//    way to record messages; we do NOT assume internal counts, just that
//    pops occur on dtor with no active exceptions.
TEST_F(CapturerDtorTest_250, DtorWithoutActiveException_PopsScopedMessages_250) {
  InSequence seq; // Ensure pops happen in a deterministic sequence (any order is acceptable here)
  // We don’t know exact number a priori, but we can relate it to our usage.
  // Capture two values; expect at least two pops on destruction.
  {
    Catch::Capturer c = MakeCapturer();
    c.captureValue(0, "first");
    c.captureValue(1, "second");

    EXPECT_CALL(mock_, popScopedMessage(_)).Times(AtLeast(2));
    // Destruction at scope exit triggers expectations
  }
}

// 2) Boundary: if no values captured, dtor should not pop any messages.
TEST_F(CapturerDtorTest_250, DtorWithNoCapturedValues_NoPops_250) {
  {
    Catch::Capturer c = MakeCapturer();
    EXPECT_CALL(mock_, popScopedMessage(_)).Times(0);
    // No captureValue calls
  }
}

// 3) Exceptional flow: when a destructor runs during stack unwinding
//    (i.e., there are active uncaught exceptions), it must NOT pop.
TEST_F(CapturerDtorTest_250, DtorDuringActiveException_DoesNotPop_250) {
  try {
    EXPECT_CALL(mock_, popScopedMessage(_)).Times(0);
    // Create a scope so Capturer is destroyed during exception unwinding
    struct Scope {
      Catch::Capturer c{MakeCapturer()};
      Scope() {
        c.captureValue(0, "will_not_be_popped");
        throw std::runtime_error("boom");
      }
    };

    Scope s; // will throw in ctor
    (void)s;
  } catch (const std::runtime_error&) {
    // swallow for test continuity
  }
}

// 4) Sanity on multiple captures: more inputs should imply at least as many pops.
//    We do not depend on internal counters; we only assert a monotonic relation
//    between captured values and pops on destruction.
TEST_F(CapturerDtorTest_250, DtorPopCountMonotonicWithCapturedValues_250) {
  {
    Catch::Capturer c = MakeCapturer();
    for (size_t i = 0; i < 5; ++i) {
      c.captureValue(i, std::to_string(i));
    }
    EXPECT_CALL(mock_, popScopedMessage(_)).Times(AtLeast(5));
  }
}

