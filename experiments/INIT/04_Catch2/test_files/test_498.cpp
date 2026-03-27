// File: tests/runcontext_createGeneratorTracker_498_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Headers under test (as provided)
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"
#include "catch2/internal/catch_test_case_tracker.hpp"

using ::testing::_;
using ::testing::Return;
using ::testing::StrictMock;

namespace Catch {

// --- Minimal mocks for RunContext’s ctor deps -------------------------------

struct MockConfig : IConfig {
    MOCK_METHOD(std::string, name, (), (const, override));
    // Provide no-op/benign defaults for other pure virtuals if needed in your build
    // Add stubs/mocks here to satisfy your environment’s IConfig interface.
};

struct MockEventListener : IEventListener {
    MOCK_METHOD(void, testRunStarting, (TestRunInfo const&), (override));
    MOCK_METHOD(void, testRunEnded, (TestRunStats const&), (override));
    MOCK_METHOD(void, testCaseStarting, (TestCaseInfo const&), (override));
    MOCK_METHOD(void, testCaseEnded, (TestCaseStats const&), (override));
    MOCK_METHOD(void, sectionStarting, (SectionInfo const&), (override));
    MOCK_METHOD(void, sectionEnded, (SectionStats const&), (override));
    MOCK_METHOD(void, assertionStarting, (AssertionInfo const&), (override));
    MOCK_METHOD(void, assertionEnded, (AssertionStats const&), (override));
    MOCK_METHOD(void, benchmarkPreparing, (StringRef), (override));
    MOCK_METHOD(void, benchmarkStarting, (BenchmarkInfo const&), (override));
    MOCK_METHOD(void, benchmarkEnded, (BenchmarkStats<> const&), (override));
    MOCK_METHOD(void, benchmarkFailed, (StringRef), (override));
    // Add stubs/mocks for any additional pure-virtuals present in your version.
};

// Helper to build a RunContext with mocks
static std::unique_ptr<RunContext> makeRunContext() {
    auto cfg = std::make_unique<StrictMock<MockConfig>>();
    EXPECT_CALL(*cfg, name()).WillRepeatedly(Return(std::string{"RunCtx-UT"}));

    IEventListenerPtr reporter{std::make_unique<StrictMock<MockEventListener>>()};
    auto* cfgRaw = cfg.release(); // RunContext takes raw IConfig*
    return std::unique_ptr<RunContext>(new RunContext(cfgRaw, std::move(reporter)));
}

// --- Test fixture ------------------------------------------------------------

class CreateGeneratorTrackerTest_498 : public ::testing::Test {
protected:
    std::unique_ptr<RunContext> ctx;

    void SetUp() override {
        ctx = makeRunContext();

        // IMPORTANT:
        // createGeneratorTracker() requires that m_trackerContext.currentTracker()
        // is a valid “current” node (typically set up by starting a run/section).
        //
        // In the provided partials, there’s no public way to seed that state.
        // If your test env exposes a bootstrap (e.g., startRun/startCycle or similar),
        // call it here to initialize the current tracker.
        //
        // Example (pseudo):
        //   ctx->/* something like */ startRunBootstrap();
        //
        // TODO(init tracker): initialize m_trackerContext.currentTracker()
    }
};

// --- Tests ------------------------------------------------------------------

// Normal operation: returns non-null and accepts generator
TEST_F(CreateGeneratorTrackerTest_498, ReturnsNonNullAndInstallsGenerator_498) {
    // Without a way to initialize m_trackerContext.currentTracker(),
    // calling into createGeneratorTracker would access an uninitialized “current” tracker.
    // Skip until the bootstrap is wired.
    GTEST_SKIP() << "Seed m_trackerContext.currentTracker() before enabling this test.";

    SourceLineInfo line{ "gen.cpp", 42 };
    StringRef genName{"MyGen"};

    // A null generator pointer is still a valid rvalue for move; behavior of hasGenerator()
    // depends on the concrete tracker. We only assert non-null return here to avoid
    // inferring internal logic.
    Generators::GeneratorBasePtr genPtr{}; // nullptr

    IGeneratorTracker* ret =
        ctx->createGeneratorTracker(genName, line, std::move(genPtr));

    ASSERT_NE(ret, nullptr) << "Returned tracker must not be null";
}

// Boundary: distinct name/location should yield a (logically) distinct tracker
TEST_F(CreateGeneratorTrackerTest_498, DifferentNameOrLocationYieldsNewTracker_498) {
    GTEST_SKIP() << "Seed m_trackerContext.currentTracker() before enabling this test.";

    SourceLineInfo A{ "a.cpp", 10 };
    SourceLineInfo B{ "a.cpp", 11 };

    Generators::GeneratorBasePtr p1{};
    Generators::GeneratorBasePtr p2{};

    IGeneratorTracker* t1 = ctx->createGeneratorTracker(StringRef{"G"}, A, std::move(p1));
    IGeneratorTracker* t2 = ctx->createGeneratorTracker(StringRef{"G"}, B, std::move(p2));

    ASSERT_NE(t1, nullptr);
    ASSERT_NE(t2, nullptr);
    EXPECT_NE(t1, t2) << "Different NameAndLocation should produce distinct trackers";
}

// Error case (observable via assert death in debug builds):
// Attempt to create a generator with the *same* NameAndLocation as the current tracker.
// NOTE: This requires making currentTracker().nameAndLocation() equal to the requested one.
// When you can set that up, enable this death test.
TEST_F(CreateGeneratorTrackerTest_498, AssertsWhenCreatingTrackerForExistingNameAndLoc_498) {
#if GTEST_HAS_DEATH_TEST
    GTEST_SKIP() << "Requires currentTracker().nameAndLocation() == requested NameAndLocation.";

    // Arrange current tracker’s NameAndLocation == ("Dup", line)
    const SourceLineInfo loc{ "dup.cpp", 7 };
    // TODO(init tracker): seed current tracker with name='Dup' and location=loc

    Generators::GeneratorBasePtr gen{};

    // Act + Assert
    EXPECT_DEATH(
        (void)ctx->createGeneratorTracker(StringRef{"Dup"}, loc, std::move(gen)),
        "Trying to create tracker for a generator that already has one");
#else
    GTEST_SKIP() << "Death tests not supported on this platform/configuration.";
#endif
}

// Interaction: the newly created tracker should be opened.
// We cannot observe internals, but an open tracker typically changes its state;
// if your environment exposes an observable (e.g., isOpen()), you can assert it here.
TEST_F(CreateGeneratorTrackerTest_498, OpensNewTracker_498) {
    GTEST_SKIP() << "Enable once an observable 'open' effect is available (e.g., isOpen()).";

    SourceLineInfo line{ "open.cpp", 1 };
    Generators::GeneratorBasePtr gen{};
    IGeneratorTracker* t =
        ctx->createGeneratorTracker(StringRef{"Opener"}, line, std::move(gen));

    ASSERT_NE(t, nullptr);
    // If IGeneratorTracker exposes an observable, assert it here, e.g.:
    // EXPECT_TRUE(t->isOpen());
}

} // namespace Catch
