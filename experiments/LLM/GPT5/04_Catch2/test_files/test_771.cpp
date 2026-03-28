// File: tests/console_reporter_benchmarkFailed_771.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>

// Catch2 reporter & deps
#include "catch2/reporters/catch_reporter_console.hpp"
#include "catch2/reporters/catch_reporter_common_base.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_console_colour.hpp"
#include "catch2/internal/catch_unique_ptr.hpp"

// If your project keeps these headers under a different path (e.g. <catch2/...>),
// adjust the includes accordingly.

using ::testing::HasSubstr;

namespace {

/// Minimal IStream wrapper that lets us observe what the reporter prints.
struct OStringIStream : Catch::IStream {
    std::ostringstream oss;
    std::ostream& stream() override { return oss; }
    ~OStringIStream() override = default;
};

// Helper to create a reporter bound to our observable stream,
// with colour disabled (so we don't have to assert on ANSI codes).
static std::unique_ptr<Catch::ConsoleReporter>
makeConsoleReporterWithStream_771(OStringIStream*& outOwnerRef, Catch::Colour::Code colour = Catch::Colour::None) {
    // Create the owned stream and keep a raw pointer to read it later
    auto raw = new OStringIStream();
    outOwnerRef = raw;

    // Build ReporterConfig:
    // NOTE: Passing nullptr for fullConfig is acceptable here because our tests
    // only exercise output-writing behavior (no reads from IConfig).
    // If your local Catch2 requires a non-null IConfig, replace with a trivial stub.
    Catch::ReporterConfig cfg(
        /*fullConfig*/ static_cast<Catch::IConfig const*>(nullptr),
        Catch::Detail::unique_ptr<Catch::IStream>(raw),   // takes ownership
        /*colourMode*/ Catch::Colour::None,               // ensure no ANSI escapes
        /*customOptions*/ {}
    );

    // Construct the reporter
    return std::make_unique<Catch::ConsoleReporter>(std::move(cfg));
}

class ConsoleReporter_BenchmarkFailed_771 : public ::testing::Test {
protected:
    OStringIStream* outStream_ = nullptr; // non-owning; reporter owns it
    std::unique_ptr<Catch::ConsoleReporter> reporter_;

    void SetUp() override {
        reporter_ = makeConsoleReporterWithStream_771(outStream_, Catch::Colour::None);
        ASSERT_NE(outStream_, nullptr);
    }

    std::string out() const { return outStream_->oss.str(); }
};

} // namespace

// --- Tests ---

// Normal operation: prints the expected prefix + message + ')'
TEST_F(ConsoleReporter_BenchmarkFailed_771, PrintsMessageWithPrefixAndParen_771) {
    EXPECT_NO_THROW(reporter_->benchmarkFailed(Catch::StringRef("division by zero")));
    const std::string s = out();
    EXPECT_THAT(s, HasSubstr("Benchmark failed (division by zero)"));
}

// Boundary: empty StringRef -> still prints the wrapper "Benchmark failed ()"
TEST_F(ConsoleReporter_BenchmarkFailed_771, PrintsEmptyMessageCleanly_771) {
    EXPECT_NO_THROW(reporter_->benchmarkFailed(Catch::StringRef("")));
    const std::string s = out();
    EXPECT_THAT(s, HasSubstr("Benchmark failed ()"));
}

// Unicode / special characters: should pass through unmodified
TEST_F(ConsoleReporter_BenchmarkFailed_771, PrintsUnicodeAndSpecials_771) {
    const std::string msg = u8"에러: Δt<0, 한글👍, x\t=\n42";
    EXPECT_NO_THROW(reporter_->benchmarkFailed(Catch::StringRef(msg)));
    const std::string s = out();
    EXPECT_THAT(s, HasSubstr("Benchmark failed (" + msg + ")"));
}

// Long string boundary: large message should be emitted without truncation
TEST_F(ConsoleReporter_BenchmarkFailed_771, PrintsVeryLongMessage_771) {
    std::string big(8192, 'A'); // 8KB of 'A'
    EXPECT_NO_THROW(reporter_->benchmarkFailed(Catch::StringRef(big)));
    const std::string s = out();

    // Check both prefix and that the trailing ')' arrives after the content
    EXPECT_THAT(s, HasSubstr("Benchmark failed (" + big + ")"));
}

// Idempotence across multiple calls: messages append (table printer emits rows)
TEST_F(ConsoleReporter_BenchmarkFailed_771, MultipleCallsAppendRows_771) {
    reporter_->benchmarkFailed(Catch::StringRef("first"));
    reporter_->benchmarkFailed(Catch::StringRef("second"));
    const std::string s = out();
    EXPECT_THAT(s, HasSubstr("Benchmark failed (first)"));
    EXPECT_THAT(s, HasSubstr("Benchmark failed (second)"));
}
