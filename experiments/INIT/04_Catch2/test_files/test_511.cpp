// File: tests/run_context_handle_fatal_error_condition_511_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_result_type.hpp"
#include "catch2/internal/catch_stringref.hpp"

// If your build exposes IConfig, include it; otherwise provide a thin stub
// that satisfies RunContext's constructor requirements (only name()).
#include "catch2/interfaces/catch_interfaces_config.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;
using ::testing::Return;
using ::testing::StrictMock;
using ::testing::StrEq;

namespace Catch {

namespace {

class MockEventListener : public IEventListener {
public:
    explicit MockEventListener(const IConfig* cfg) : IEventListener(cfg) {}

    MOCK_METHOD(void, fatalErrorEncountered, (StringRef), (override));
    MOCK_METHOD(void, sectionEnded, (const SectionStats&), (override));
    MOCK_METHOD(void, testCaseEnded, (const TestCaseStats&), (override));
    MOCK_METHOD(void, testRunEnded, (const TestRunStats&), (override));

    // Keep default no-op for the rest to avoid surprises
    // (Google Mock will ignore them unless you need them)
};

class DummyInvoker : public ITestInvoker {
public:
    void invoke() const override {/* no-op */}
    void prepareTestCase() const override {/* no-op */}
    void tearDownTestCase() const override {/* no-op */}
};

// Minimal IConfig stub: only the bits RunContext’s ctor uses (name()).
class StubConfig : public IConfig {
public:
    explicit StubConfig(StringRef n) : m_name(static_cast<std::string>(n)) {}
    StringRef name() const override { return m_name; }

    // Everything else can be defaulted or return safe defaults;
    // they are not exercised by these tests.
    bool shouldDebugBreak() const override { return false; }
    bool abortAfter(size_t) const override { return false; }
    // ... leave other virtuals with trivial returns if your interface requires ...

private:
    std::string m_name;
};

// Helpers to build a trivial active test case handle.
// Only getTestCaseInfo() is used by handleFatalErrorCondition via RunContext.
static TestCaseHandle makeTestCaseHandle(const char* name, const SourceLineInfo& li) {
    // Construct a TestCaseInfo with a simple NameAndTags (name only).
    NameAndTags nt;
    nt.name = name;
    // Fill minimal fields needed by the partial headers provided.
    auto* info = new TestCaseInfo(StringRef{}, nt, li);
    static DummyInvoker invoker;
    return TestCaseHandle(info, &invoker);
}

// Fixture wires RunContext with a strict mock reporter so we can
// verify *only* the observable calls made by handleFatalErrorCondition.
class RunContextFatal_511 : public ::testing::Test {
protected:
    void SetUp() override {
        config = std::make_unique<StubConfig>("fatal-run");
        reporter = std::make_unique<StrictMock<MockEventListener>>(config.get());
        // The RunContext takes ownership via unique_ptr-like wrapper; move in.
        ctx = std::make_unique<RunContext>(config.get(), IEventListenerPtr(reporter.get()));
        // Keep raw pointer for expectations while letting RunContext own lifetime.
        // NOTE: If your IEventListenerPtr actually owns, ensure reporter outlives ctx usage.
        // Prepare an "active" test case so handleFatalErrorCondition can reference it.
        SourceLineInfo li{ "dummy.cpp", 123 };
        activeTc = std::make_unique<TestCaseHandle>(makeTestCaseHandle("DummyCase", li));

        // Start test run with this test case so m_activeTestCase is set.
        // We cannot access private members, so we invoke through the public API.
        // This relies on the existing RunContext implementation in your repo.
        (void)ctx->runTest(*activeTc);
    }

    std::unique_ptr<StubConfig> config;
    // reporter remains owned externally; RunContext stores a pointer-like wrapper
    std::unique_ptr<StrictMock<MockEventListener>> reporter;
    std::unique_ptr<RunContext> ctx;
    std::unique_ptr<TestCaseHandle> activeTc;
};

} // namespace

// 1) Reports the fatal error to the reporter and ends current run.
//    Key observable effects in provided implementation:
//    - reporter->fatalErrorEncountered(message)
//    - reporter->sectionEnded(...) for the test case "section" with failed=1
//    - reporter->testCaseEnded(...), with deltaTotals.{testCases,assertions}.failed == 1
//    - reporter->testRunEnded(...), and overall totals reflect one failed test
TEST_F(RunContextFatal_511, ReportsAndEndsRunOnFatalError_511) {
    using ::testing::Matcher;

    // We only match the fields we know from the snippet (assertions.failed == 1).
    auto HasOneFailedAssertion =
        Field(&SectionStats::assertions,
              Field(&Counts::failed, 1ULL));

    // For end-of-run, ensure at least one test case failed and one assertion failed.
    // Match via TestRunStats::totals (structure used in snippet).
    auto TotalsShowOneFailure =
        Field(&TestRunStats::totals,
              AllOf(
                Field(&Totals::testCases, Field(&Counts::failed, 1ULL)),
                Field(&Totals::assertions, Field(&Counts::failed, 1ULL))
              ));

    // Also ensure testCaseEnded's deltaTotals contains the single failure.
    auto CaseDeltaShowsOneFailure =
        Property(&TestCaseStats::totals, // or Field if public
                 AllOf(
                   Field(&Totals::testCases, Field(&Counts::failed, 1ULL)),
                   Field(&Totals::assertions, Field(&Counts::failed, 1ULL))
                 ));

    // Expectations -> order matters; use InSequence for the main flow
    ::testing::InSequence seq;

    EXPECT_CALL(*reporter, fatalErrorEncountered(StrEq("🔥 boom")));
    EXPECT_CALL(*reporter, sectionEnded(HasOneFailedAssertion));
    EXPECT_CALL(*reporter, testCaseEnded(CaseDeltaShowsOneFailure));
    EXPECT_CALL(*reporter, testRunEnded(TotalsShowOneFailure));

    // Act
    ctx->handleFatalErrorCondition(StringRef("🔥 boom"));
}

// 2) When sections are open, they should be closed early before finishing.
//    We cannot reach into internals, but we can open sections via the public API,
//    then trigger the fatal error and observe multiple sectionEnded calls.
//    One call is for each open section (ended early) + one for the test-case section.
TEST_F(RunContextFatal_511, ClosesOpenSectionsBeforeFinishing_511) {
    Counts assertionsA{}, assertionsB{};
    SourceLineInfo liA{ "fileA.cpp", 10 };
    SourceLineInfo liB{ "fileB.cpp", 20 };

    // Open two sections via the public interface
    ASSERT_TRUE(ctx->sectionStarted(StringRef("A"), liA, assertionsA));
    ASSERT_TRUE(ctx->sectionStarted(StringRef("B"), liB, assertionsB));

    // We expect at least 3 sectionEnded calls:
    // - one for B (ended early)
    // - one for A (ended early)
    // - one for the test case "section" from the snippet with failed=1
    // We do not assert exact names here to avoid relying on internal mapping,
    // only that they are invoked.
    EXPECT_CALL(*reporter, fatalErrorEncountered(StrEq("FATAL!")));
    EXPECT_CALL(*reporter, sectionEnded(_)).Times(::testing::AtLeast(3));
    EXPECT_CALL(*reporter, testCaseEnded(_));
    EXPECT_CALL(*reporter, testRunEnded(_));

    ctx->handleFatalErrorCondition(StringRef("FATAL!"));
}

// 3) The message should be propagated into the fatal error callback unmodified.
TEST_F(RunContextFatal_511, PropagatesExactErrorMessage_511) {
    EXPECT_CALL(*reporter, fatalErrorEncountered(StrEq("exact message 123")));
    // The rest of the flow is not the focus of this test; allow them but do not over-specify.
    EXPECT_CALL(*reporter, sectionEnded(_));
    EXPECT_CALL(*reporter, testCaseEnded(_));
    EXPECT_CALL(*reporter, testRunEnded(_));

    ctx->handleFatalErrorCondition(StringRef("exact message 123"));
}

} // namespace Catch
