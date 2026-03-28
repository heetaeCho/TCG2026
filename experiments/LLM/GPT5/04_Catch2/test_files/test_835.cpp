// File: tests/XmlReporter_writeSourceInfo_835.tests.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// Catch2 headers from your tree
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

// If your project exposes ReporterConfig and StreamingReporterBase in a header
// included by catch_reporter_xml.hpp, no extra includes are needed.
// The tests assume XmlReporter writes to the stream provided via ReporterConfig.

using namespace Catch;

namespace {

// Small helper to build an XmlReporter wired to an ostringstream.
// Adjust construction if your ReporterConfig initialization differs.
struct ReporterUnderTest {
    std::ostringstream os;
    std::unique_ptr<XmlReporter> reporter;

    ReporterUnderTest() {
        // NOTE: Depending on your actual ReporterConfig, you may need to adapt this.
        // Typical Catch2 pattern: ReporterConfig takes a stream and configuration data.
        // Here we only rely on the fact that XmlReporter writes to the provided stream.
        ReporterConfig cfg{/* config fields as required by your codebase */};
        // If ReporterConfig requires a stream, set it to os:
        // cfg.stream = &os;  // <-- adapt if your type differs

        reporter = std::make_unique<XmlReporter>(std::move(cfg));
    }

    std::string str() const { return os.str(); }
};

} // namespace

// --- Tests ---

// Normal operation: verifies that calling writeSourceInfo writes both filename and line.
TEST(XmlReporter_WriteSourceInfo_835, WritesFilenameAndLine_835) {
    ReporterUnderTest ctx;

    const char* file = "src/module/foo.cpp";
    std::size_t line = 42;
    SourceLineInfo sli{file, line};

    // Act
    ctx.reporter->writeSourceInfo(sli);

    // Assert (observable behavior via output stream content)
    const std::string out = ctx.str();
    // We do NOT assert on exact XML formatting; we only check presence
    // of attribute names and values as observable text.
    EXPECT_NE(out.find("filename"), std::string::npos);
    EXPECT_NE(out.find("foo.cpp"),  std::string::npos);
    EXPECT_NE(out.find("line"),     std::string::npos);
    EXPECT_NE(out.find("42"),       std::string::npos);
}

// Boundary-ish inputs: empty filename and line=0 should not crash and should be reflected.
TEST(XmlReporter_WriteSourceInfo_835, HandlesEmptyFilenameAndZeroLine_835) {
    ReporterUnderTest ctx;

    const char* file = "";
    std::size_t line = 0;
    SourceLineInfo sli{file, line};

    ctx.reporter->writeSourceInfo(sli);

    const std::string out = ctx.str();
    EXPECT_NE(out.find("filename"), std::string::npos);
    // Empty filename still results in an attribute being written; we only check that the
    // attribute name appears (do not rely on exact formatting).
    EXPECT_NE(out.find("line"), std::string::npos);
    EXPECT_NE(out.find("0"),    std::string::npos);
}

// Non-ASCII path: ensure the filename text is carried through as observable output.
TEST(XmlReporter_WriteSourceInfo_835, WritesNonAsciiFilename_835) {
    ReporterUnderTest ctx;

    const char* file = "경로/테스트.cpp";
    std::size_t line = 7;
    SourceLineInfo sli{file, line};

    ctx.reporter->writeSourceInfo(sli);

    const std::string out = ctx.str();
    EXPECT_NE(out.find("filename"), std::string::npos);
    EXPECT_NE(out.find("경로/테스트.cpp"), std::string::npos);
    EXPECT_NE(out.find("line"), std::string::npos);
    EXPECT_NE(out.find("7"),    std::string::npos);
}
