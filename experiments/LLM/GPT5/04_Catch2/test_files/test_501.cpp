// File: tests/runcontext_benchmarkPreparing_tests_501.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/internal/catch_run_context.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp> // For IConfig (implementation details not used)

using ::testing::_;
using ::testing::InSequence;
using ::testing::StrictMock;
using ::testing::Truly;

namespace Catch {

// ---------------------------
// Minimal test doubles
// ---------------------------

// A minimal config implementation that satisfies construction needs of RunContext.
// If your IConfig in this repo has additional pure virtuals, add trivial overrides.
class DummyConfig_501 : public IConfig {
public:
    // ---- Required interface bits used by RunContext's ctor ----
    StringRef name() const override { return m_name; }

    // ---- Trivial defaults for common IConfig pure virtuals ----
    // If your local IConfig differs, add/adjust overrides as needed.
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override { return std::cout; }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutUnmatchedTestSpecs() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return false; }
    ShowDurations::OrNot showDurations() const override { return ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }
    TestSpec const& testSpec() const override { return m_testSpec; }
    bool hasTestFilters() const override { return false; }
    std::vector<StringRef> const& getTestsOrTags() const override { return m_empty; }
    ContextOptions const& getContextOptions() const override { return m_ctxOpts; }
    int abortAfter() const override { return 0; }
    bool benchmarkNoAnalysis() const override { return false; }
    int benchmarkSamples() const override { return 100; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 1000u; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    ColourMode colourMode() const override { return ColourMode::PlatformDefault; }
    bool shmStartup() const override { return false; }
    bool shmCleanup() const override { return false; }

private:
    StringRef m_name = StringRef("dummy-run-501");
    TestSpec m_testSpec;                  // default-constructed OK for tests
    std::vector<StringRef> m_empty;       // empty by default
    ContextOptions m_ctxOpts{};           // default-constructed
};

// Mock reporter that lets us verify the observable interaction.
class MockEventListener_501 : public IEventListener {
public:
    explicit MockEventListener_501(IConfig const* cfg) : IEventListener(cfg) {}
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
};

} // namespace Catch

// ---------------------------
// Test fixture
// ---------------------------
class RunContext_BenchmarkPreparing_Test_501 : public ::testing::Test {
protected:
    Catch::DummyConfig_501 cfg_;
};

// ---------------------------
// Tests
// ---------------------------

TEST_F(RunContext_BenchmarkPreparing_Test_501, ForwardsToReporterWithSameName_501) {
    using namespace Catch;

    // Arrange
    auto mockPtr = Detail::unique_ptr<MockEventListener_501>(new StrictMock<MockEventListener_501>(&cfg_));
    auto* mockRaw = mockPtr.get();

    RunContext ctx(&cfg_, std::move(mockPtr));

    const std::string expected = "hot-loop";

    EXPECT_CALL(*mockRaw,
        benchmarkPreparing(Truly([&](const StringRef& s) {
            return static_cast<std::string>(s) == expected;
        }))
    ).Times(1);

    // Act
    ctx.benchmarkPreparing(StringRef(expected));
}

TEST_F(RunContext_BenchmarkPreparing_Test_501, ForwardsEmptyName_501) {
    using namespace Catch;

    auto mockPtr = Detail::unique_ptr<MockEventListener_501>(new StrictMock<MockEventListener_501>(&cfg_));
    auto* mockRaw = mockPtr.get();

    RunContext ctx(&cfg_, std::move(mockPtr));

    EXPECT_CALL(*mockRaw,
        benchmarkPreparing(Truly([](const StringRef& s) {
            return s.size() == 0 && static_cast<std::string>(s) == "";
        }))
    ).Times(1);

    ctx.benchmarkPreparing(StringRef(""));
}

TEST_F(RunContext_BenchmarkPreparing_Test_501, ForwardsLongName_501) {
    using namespace Catch;

    auto mockPtr = Detail::unique_ptr<MockEventListener_501>(new StrictMock<MockEventListener_501>(&cfg_));
    auto* mockRaw = mockPtr.get();

    RunContext ctx(&cfg_, std::move(mockPtr));

    // Long-ish name to exercise boundary-like conditions on StringRef passing
    std::string longName(4096, 'X');

    EXPECT_CALL(*mockRaw,
        benchmarkPreparing(Truly([&](const StringRef& s) {
            return s.size() == longName.size() &&
                   static_cast<std::string>(s) == longName;
        }))
    ).Times(1);

    ctx.benchmarkPreparing(StringRef(longName));
}

TEST_F(RunContext_BenchmarkPreparing_Test_501, MultipleCallsAreForwardedInOrder_501) {
    using namespace Catch;

    auto mockPtr = Detail::unique_ptr<MockEventListener_501>(new StrictMock<MockEventListener_501>(&cfg_));
    auto* mockRaw = mockPtr.get();

    RunContext ctx(&cfg_, std::move(mockPtr));

    InSequence seq;

    EXPECT_CALL(*mockRaw,
        benchmarkPreparing(Truly([](const StringRef& s) {
            return static_cast<std::string>(s) == "first";
        }))
    ).Times(1);

    EXPECT_CALL(*mockRaw,
        benchmarkPreparing(Truly([](const StringRef& s) {
            return static_cast<std::string>(s) == "second";
        }))
    ).Times(1);

    // Act
    ctx.benchmarkPreparing(StringRef("first"));
    ctx.benchmarkPreparing(StringRef("second"));
}
