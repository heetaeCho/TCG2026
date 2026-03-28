// File: tests/reporter_compact_noMatchingTestCases_813.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <string>

// The production headers (interfaces only)
#include "catch2/reporters/catch_reporter_compact.hpp"
#include "catch2/internal/catch_stringref.hpp"

// Minimal test helpers to provide an injectable ostream to the reporter.
// These are *collaborator* test doubles (not reimplementations of reporter logic).
// They should match only the bits of interface CompactReporter/ReporterBase use.

namespace Catch {
    // Minimal IStream-like wrapper that exposes std::ostream& stream()
    struct TestOStreamWrapper : IStream {
        explicit TestOStreamWrapper(std::ostream& os) : m_os(os) {}
        std::ostream& stream() override { return m_os; }
        std::ostream& m_os;
    };

    // Minimal ReporterConfig-like object that hands ownership of our stream wrapper
    // and provides the small surface used by ReporterBase/StreamingReporterBase.
    struct TestReporterConfig : ReporterConfig {
        // Forward to real ReporterConfig constructor surface if available in your tree;
        // otherwise provide a minimal shim for the parts ReporterBase consumes.
        explicit TestReporterConfig(std::unique_ptr<IStream> s)
        : ReporterConfig( /* fullConfig = */ nullptr,
                          /* stream = */ std::move(s),
                          /* colourMode = */ ColourMode::PlatformDefault,
                          /* customOptions = */ {} ) {}
    };
} // namespace Catch

using ::testing::StrEq;

class CompactReporter_NoMatch_813 : public ::testing::Test {
protected:
    std::ostringstream os;

    std::unique_ptr<Catch::CompactReporter> makeReporter() {
        // Wrap our ostringstream into Catch's IStream and hand it via ReporterConfig
        auto wrap = std::make_unique<Catch::TestOStreamWrapper>(os);
        Catch::TestReporterConfig cfg(std::move(wrap));
        return std::make_unique<Catch::CompactReporter>(std::move(cfg));
    }
};

TEST_F(CompactReporter_NoMatch_813, WritesExpectedMessageForSimpleSpec_813) {
    auto reporter = makeReporter();

    reporter->noMatchingTestCases(Catch::StringRef("math*"));

    EXPECT_THAT(os.str(), StrEq("No test cases matched 'math*'\n"));
}

TEST_F(CompactReporter_NoMatch_813, WritesExpectedMessageForEmptySpec_813) {
    auto reporter = makeReporter();

    reporter->noMatchingTestCases(Catch::StringRef(""));

    EXPECT_THAT(os.str(), StrEq("No test cases matched ''\n"));
}

TEST_F(CompactReporter_NoMatch_813, PreservesInnerQuotesAndCharacters_813) {
    auto reporter = makeReporter();

    // Contains a single quote and punctuation; should be wrapped as-is in single quotes
    reporter->noMatchingTestCases(Catch::StringRef("tag'weird?!"));

    EXPECT_THAT(os.str(), StrEq("No test cases matched 'tag'weird?!'\n"));
}

TEST_F(CompactReporter_NoMatch_813, AcceptsStdStringAndCharPtrViaStringRef_Conversions_813) {
    auto reporter = makeReporter();

    std::string s = "suite::case";
    reporter->noMatchingTestCases(Catch::StringRef(s));
    EXPECT_THAT(os.str(), StrEq("No test cases matched 'suite::case'\n"));

    os.str(""); os.clear();
    reporter->noMatchingTestCases(Catch::StringRef("alpha[fast]"));
    EXPECT_THAT(os.str(), StrEq("No test cases matched 'alpha[fast]'\n"));
}
