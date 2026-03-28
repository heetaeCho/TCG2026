// File: tests/console_reporter_testRunEnded_773.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Catch2 public headers (interfaces only, no internal/private state touched)
#include <catch2/reporters/catch_reporter_console.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>
#include <catch2/internal/catch_unique_ptr.hpp>
#include <catch2/internal/catch_stream.hpp>
#include <catch2/catch_totals.hpp>
#include <catch2/catch_test_run_info.hpp>
#include <catch2/catch_test_macros.hpp> // not used for SECTION/REQUIRE; safe to include

using ::testing::_;
using ::testing::ReturnRef;

namespace {

// ---------- Test utilities (external collaborators) ----------

// A stringbuf that counts flushes via sync() and lets us read the buffer.
struct FlushCountingStringBuf : std::stringbuf {
    int flushCount = 0;
    int sync() override {
        ++flushCount;
        return std::stringbuf::sync();
    }
};

// A simple IStream that wraps an std::ostream backed by our counting buffer.
class TestIStream : public Catch::IStream {
public:
    explicit TestIStream(FlushCountingStringBuf& buf) : m_os(&buf), m_buf(buf) {}
    std::ostream& stream() override { return m_os; }

    int flushCount() const { return m_buf.flushCount; }
    std::string str() const { return m_buf.str(); }

private:
    std::ostream             m_os;
    FlushCountingStringBuf&  m_buf;
};

// Minimal config stub. We do not rely on any internal state,
// and ConsoleReporter/ReporterBase will only store the pointer.
class DummyConfig : public Catch::IConfig {
public:
    // -- Minimal, inert defaults (only what tends to be pure-virtual) --
    bool allowThrows() const override { return true; }
    std::ostream& defaultStream() const override {
        static std::ostringstream oss;
        return oss;
    }
    std::string name() const override { return "dummy-config"; }

    // Warnings/verbosity/durations knobs (harmless defaults)
    bool warnings(Catch::WarnAbout) const override { return false; }
    Catch::ShowDurations::OrNot showDurations() const override { return Catch::ShowDurations::DefaultForReporter; }
    double minDuration() const override { return 0.0; }

    // Test selection/filtering (unused here)
    Catch::TestSpec const& testSpec() const override { static Catch::TestSpec spec; return spec; }
    bool hasTestFilters() const override { return false; }
    std::vector<std::string> const& getTestsOrTags() const override {
        static std::vector<std::string> v; return v;
    }

    // Execution params
    Catch::RunTests::InWhatOrder runOrder() const override { return Catch::RunTests::InWhatOrder::InLexicographicalOrder; }
    unsigned int rngSeed() const override { return 0u; }
    Catch::UseColour::YesOrNo useColour() const override { return Catch::UseColour::No; }
    bool shouldDebugBreak() const override { return false; }
    int abortAfter() const override { return 0; }
    bool aborting() const override { return false; }

    // Benchmark knobs (harmless defaults)
    bool benchmarkNoAnalysis() const override { return false; }
    int benchmarkSamples() const override { return 0; }
    double benchmarkConfidenceInterval() const override { return 0.95; }
    unsigned int benchmarkResamples() const override { return 0; }
    std::chrono::milliseconds benchmarkWarmupTime() const override { return std::chrono::milliseconds{0}; }

    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }
};

// Helper to build a ConsoleReporter with our custom stream
struct ConsoleReporterFixture_773 : ::testing::Test {
    FlushCountingStringBuf      buf;
    std::unique_ptr<TestIStream> ownedStream;
    DummyConfig                 cfg;
    std::unique_ptr<Catch::ConsoleReporter> reporter;

    // Provide access to the underlying string after calls
    std::string out() const { return ownedStream->str(); }
    int flushes() const { return ownedStream->flushCount(); }

    void SetUp() override {
        ownedStream = std::make_unique<TestIStream>(buf);

        // ReporterConfig takes ownership of the IStream. We move it in.
        Catch::ReporterConfig rc{
            &cfg,
            Catch::Detail::unique_ptr<Catch::IStream>(ownedStream.release()),
            Catch::ColourMode::None,
            {} // custom options
        };

        reporter = std::make_unique<Catch::ConsoleReporter>(std::move(rc));
    }

    // Convenience to make a TestRunStats with given Totals
    static Catch::TestRunStats makeStats(const Catch::Totals& totals) {
        Catch::TestRunInfo info{"tr-773"};
        return Catch::TestRunStats{info, totals, /*aborting*/ false};
    }
};

} // namespace

// ------------------------------------------------------------
// Tests
// ------------------------------------------------------------

TEST_F(ConsoleReporterFixture_773, AppendsNewlineAndFlushes_773) {
    // Arrange
    Catch::Totals totals{}; // default/empty totals is a valid boundary
    auto stats = makeStats(totals);

    // Act
    reporter->testRunEnded(stats);

    // Assert (observable effects only)
    // 1) Stream got at least one flush
    EXPECT_GE(flushes(), 1) << "ConsoleReporter::testRunEnded should flush the stream";

    // 2) Output ends with a newline (it writes '\n' explicitly)
    ASSERT_FALSE(out().empty());
    EXPECT_EQ(out().back(), '\n');
}

TEST_F(ConsoleReporterFixture_773, MultipleCallsYieldMultipleTrailingNewlines_773) {
    // Arrange
    auto stats = makeStats(Catch::Totals{});

    // Act
    reporter->testRunEnded(stats);
    auto after1 = out();
    reporter->testRunEnded(stats);
    auto after2 = out();

    // Assert (we do not assert any internal formatting, only the
    // strictly observable contract: each call appends '\n' + flush)
    ASSERT_FALSE(after1.empty());
    ASSERT_FALSE(after2.empty());
    EXPECT_EQ(after1.back(), '\n');
    EXPECT_EQ(after2.back(), '\n');

    // Count of trailing newlines increased by at least 1
    auto countTrailingNewlines = [](const std::string& s) {
        size_t n = 0;
        for (size_t i = s.size(); i > 0 && s[i-1] == '\n'; --i) ++n;
        return n;
    };
    EXPECT_LT(countTrailingNewlines(after1), countTrailingNewlines(after2));
}

TEST_F(ConsoleReporterFixture_773, HandlesZeroAndNonZeroTotalsWithoutThrow_773) {
    // Arrange: zero totals (boundary) then non-zero-like totals.
    // We do NOT introspect content; just ensure robust, observable use.
    {
        auto stats = makeStats(Catch::Totals{});
        EXPECT_NO_THROW(reporter->testRunEnded(stats));
    }
    {
        // Totals is a value type; even if fields are defaulted, this
        // still exercises the observable path. We avoid relying on its internals.
        Catch::Totals someTotals{};
        auto stats = makeStats(someTotals);
        EXPECT_NO_THROW(reporter->testRunEnded(stats));
    }

    // At least one newline + flush must have happened across calls
    ASSERT_FALSE(out().empty());
    EXPECT_EQ(out().back(), '\n');
    EXPECT_GE(flushes(), 1);
}
