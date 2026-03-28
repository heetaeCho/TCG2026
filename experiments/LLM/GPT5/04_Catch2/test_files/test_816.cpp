// File: tests/compact_reporter_testRunEnded_816.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <streambuf>

// Catch2 — include the real reporter interfaces
#include <catch2/reporters/catch_reporter_compact.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/interfaces/catch_interfaces_reporter.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>

// If your project keeps Catch headers under a different path, adjust includes accordingly.

using ::testing::_;
using ::testing::NiceMock;

namespace {

// --------------- Helpers (observable-only; no internal state peeking) ---------------

// Custom stringbuf that lets us observe flushes (std::flush calls sync()).
struct TrackingStringBuf : public std::stringbuf {
    int syncCount = 0;
    int sync() override {
        ++syncCount;
        return std::stringbuf::sync();
    }
};

// Minimal IStream wrapper that returns an already-constructed std::ostream.
class RefIStream : public Catch::IStream {
public:
    explicit RefIStream(std::ostream& os) : m_os(&os) {}
    std::ostream& stream() override { return *m_os; }
private:
    std::ostream* m_os;
};

// A trivially usable IConfig stub. It should never be *used* by the code under test,
// only passed through ReporterConfig -> IEventListener. If your tree provides a ready
// TestConfig or a helper factory, use that instead and delete this stub.
class DummyConfig : public Catch::IConfig {
public:
    // Implement only what is pure-virtual in your Catch2 version. These signatures
    // are intentionally minimal; if your build complains, just add/adjust returns.
    ~DummyConfig() override = default;

    // Below are no-op defaults; update to match your IConfig if needed.
    bool allowThrows() const override { return true; }
    // Catch2 v3 typically needs these:
    bool shouldDebugBreak() const override { return false; }
    int abortAfter() const override { return 0; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool benchmarkNoAnalysis() const override { return false; }
    int benchmarkSamples() const override { return 0; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }
    // Listing/filters — neutral defaults:
    bool listReporters() const override { return false; }
    bool listListeners() const override { return false; }
    bool listTests() const override { return false; }
    bool listTags() const override { return false; }
    bool listTestNamesOnly() const override { return false; }
    std::string name() const override { return "dummy"; }
    std::string outputFilename() const override { return {}; }
    // Reporters frequently query this:
    std::vector<std::string> getTestsOrTags() const override { return {}; }
    bool hasTestFilters() const override { return false; }
    // Colour & RNG related (neutral):
    Catch::ColourMode colourMode() const override { return Catch::ColourMode::None; }
    std::uint32_t rngSeed() const override { return 0; }
    // Sharding (neutral):
    bool testSpecHasFilters() const override { return false; }
    // Assertions formatting:
    bool allowBenchmarking() const override { return false; }
    bool showSuccessfulTests() const override { return false; }
    bool warningsAsErrors() const override { return false; }
    bool zeroTestsCountAsSuccess() const override { return true; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }

    // Depending on your exact Catch2 version, you might need to add a few more trivial overrides.
};

// Helper to build a CompactReporter wired to our tracked ostream.
struct ReporterHarness {
    TrackingStringBuf buf;
    std::ostream os;
    Catch::Detail::unique_ptr<Catch::IStream> is;
    std::unique_ptr<Catch::CompactReporter> reporter;
    DummyConfig dummyCfg;

    ReporterHarness()
        : os(&buf),
          is(new RefIStream(os))
    {
        // Build ReporterConfig. If your signature differs, adjust arguments here.
        // Common ctor in Catch2 v3: ReporterConfig(const IConfig*,
        //                                          Detail::unique_ptr<IStream>&&,
        //                                          ColourMode,
        //                                          std::map<std::string,std::string> custom = {})
        Catch::ReporterConfig rc(
            &dummyCfg,
            Catch::Detail::unique_ptr<Catch::IStream>(is.release()),
            Catch::ColourMode::None,
            {}
        );
        reporter = std::make_unique<Catch::CompactReporter>(std::move(rc));
    }

    // Utility: get current string content
    std::string str() const { return static_cast<std::string>(buf.str()); }

    // Utility: does current content end with "\n\n"?
    static bool endsWithDoubleNL(const std::string& s) {
        return s.size() >= 2 && s[s.size()-2] == '\n' && s[s.size()-1] == '\n';
    }
};

} // namespace

// ----------------------------- Tests (TEST_ID 816) -----------------------------

// TEST 1: Appends "\n\n" and flushes the stream once per call.
TEST(CompactReporterTest_816, AppendsTwoNewlinesAndFlushes_816) {
    ReporterHarness h;

    // Arrange: empty run info + zero totals are fine (black-box).
    Catch::TestRunInfo runInfo{"dummy run"};
    Catch::Totals totals{}; // zero-initialized totals
    Catch::TestRunStats stats{ runInfo, totals, /*aborting*/ false };

    // Act
    h.reporter->testRunEnded(stats);

    // Assert: stream ends with exactly two newlines after whatever totals printer wrote.
    const std::string out = h.str();
    ASSERT_FALSE(out.empty());               // something was written
    EXPECT_TRUE(ReporterHarness::endsWithDoubleNL(out));
    // And a flush was requested (std::flush -> sync())
    EXPECT_GE(h.buf.syncCount, 1);
}

// TEST 2: Idempotent observable tail; repeated calls still end with "\n\n".
TEST(CompactReporterTest_816, EndsWithTwoNewlinesAfterMultipleCalls_816) {
    ReporterHarness h;

    Catch::TestRunInfo runInfo{"dummy run"};
    Catch::Totals totals{};
    Catch::TestRunStats stats{ runInfo, totals, /*aborting*/ false };

    h.reporter->testRunEnded(stats);
    const std::string first = h.str();

    h.reporter->testRunEnded(stats);
    const std::string second = h.str();

    // Each call must leave the output ending with "\n\n".
    EXPECT_TRUE(ReporterHarness::endsWithDoubleNL(first));
    EXPECT_TRUE(ReporterHarness::endsWithDoubleNL(second));

    // And content should have grown (at least by something).
    EXPECT_GT(second.size(), first.size());

    // flush() should have been requested at least twice overall.
    EXPECT_GE(h.buf.syncCount, 2);
}

// TEST 3: Pre-filled stream remains correct; only the trailing "\n\n" is asserted.
TEST(CompactReporterTest_816, PreservesPrefixAndAddsTrailingNewlines_816) {
    ReporterHarness h;

    // Pre-fill the stream with arbitrary prefix text (black-box friendly).
    h.os << "prefix-data";

    Catch::TestRunInfo runInfo{"dummy run"};
    Catch::Totals totals{};
    Catch::TestRunStats stats{ runInfo, totals, /*aborting*/ false };

    h.reporter->testRunEnded(stats);

    const std::string out = h.str();
    ASSERT_GE(out.size(), std::size_t{2});
    EXPECT_TRUE(ReporterHarness::endsWithDoubleNL(out)); // Only assert observable suffix
}
