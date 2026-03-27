// File: test_teamcity_reporter_testCaseStarting_784.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <catch2/reporters/catch_reporter_teamcity.hpp>
#include <catch2/reporters/catch_reporter_streaming_base.hpp>
#include <catch2/reporters/catch_reporter_common_base.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/internal/catch_source_line_info.hpp>
#include <catch2/internal/catch_stream.hpp>

#include <ostream>
#include <sstream>
#include <string>

using namespace Catch;

// --- Test doubles for stream capturing (external collaborator mocking is allowed) ---

// A stringbuf that records whether a flush/sync occurred.
struct SyncingStringBuf : std::stringbuf {
    bool flushed = false;
    int sync() override {
        flushed = true;
        return std::stringbuf::sync();
    }
};

// std::ostream that uses our syncing buffer.
struct CapturingOStream : std::ostream {
    SyncingStringBuf buf;
    CapturingOStream() : std::ostream(&buf) {}
    std::string str() {
        // std::stringbuf::str() is non-const, so expose a non-const accessor.
        return buf.str();
    }
};

// Minimal IStream wrapper returning our capturing ostream.
struct CapturingIStream : IStream {
    CapturingOStream out;
    std::ostream& stream() override { return out; }
    std::string content() { return out.str(); }
    bool wasFlushed() const { return out.buf.flushed; }
};

// Helper: build a TestCaseInfo with a given name.
static TestCaseInfo makeTestCaseInfo(const std::string& name) {
    // NameAndTags in Catch2 carries name + raw tags. Using empty tags here.
    NameAndTags nt{ StringRef(name), StringRef() };
    SourceLineInfo sli{ StringRef("dummy.cpp"), 123 };
    return TestCaseInfo(StringRef("DummyClass"), nt, sli);
}

// Test fixture keeps the capturing stream alive for inspection.
class TeamCityReporterTest_784 : public ::testing::Test {
protected:
    // Owned by ReporterConfig via unique_ptr, but we keep a raw pointer to inspect later.
    CapturingIStream* capStreamPtr = nullptr;

    // Constructs a TeamCityReporter configured to write into our capturing stream.
    TeamCityReporter makeReporter() {
        Detail::unique_ptr<IStream> streamUP{ new CapturingIStream() };
        capStreamPtr = static_cast<CapturingIStream*>(streamUP.get());

        // Build ReporterConfig:
        // - fullConfig = nullptr (not used by testCaseStarting path)
        // - stream = our capturing stream
        // - colour mode = None (arbitrary; not relevant here)
        ReporterConfig cfg{
            /* fullConfig */ nullptr,
            std::move(streamUP),
            ColourMode::None,
            /* customOptions */ {}
        };

        return TeamCityReporter(std::move(cfg));
    }
};

// Normal case: writes the correct TeamCity "testStarted" line and flushes.
TEST_F(TeamCityReporterTest_784, WritesTestStartedLine_784) {
    auto reporter = makeReporter();

    auto info = makeTestCaseInfo("SimpleCase");
    reporter.testCaseStarting(info);

    ASSERT_NE(capStreamPtr, nullptr);
    const std::string out = capStreamPtr->content();

    // Observable behavior: exact TeamCity line with newline.
    EXPECT_EQ(out, "##teamcity[testStarted name='SimpleCase']\n");
    // Observable behavior: stream was flushed.
    EXPECT_TRUE(capStreamPtr->wasFlushed());
}

// Escaping: names with special characters are escaped in the emitted message.
TEST_F(TeamCityReporterTest_784, EscapesSpecialCharactersInName_784) {
    auto reporter = makeReporter();

    // Include characters that require TeamCity escaping per service message rules.
    // ']' -> '|]' and '\'' -> '|''
    auto info = makeTestCaseInfo("a]b'c");
    reporter.testCaseStarting(info);

    ASSERT_NE(capStreamPtr, nullptr);
    const std::string out = capStreamPtr->content();

    // Expect the escaped name inside the service message.
    // a]b'c -> a|]b|'c
    EXPECT_EQ(out, "##teamcity[testStarted name='a|]b|'c']\n");
    EXPECT_TRUE(capStreamPtr->wasFlushed());
}
