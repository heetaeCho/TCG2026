// TEST_ID: 838
// File: tests/XmlReporter_sectionStarting_838.cpp

#include <gtest/gtest.h>

#include <sstream>
#include <string>

// Catch2 public headers we interact with (interfaces only)
#include <catch2/reporters/catch_reporter_xml.hpp>
#include <catch2/catch_section_info.hpp>
#include <catch2/internal/catch_source_line_info.hpp>

// If ReporterConfig header is separate in your tree, include it as well.
// (Common in Catch2 v3 trees: <catch2/reporters/catch_reporter_helpers.hpp>)
// #include <catch2/reporters/catch_reporter_helpers.hpp>

using namespace Catch;

namespace {

// Minimal helper to build a SectionInfo from file + line + name
inline SectionInfo makeSection(const char* file,
                               std::size_t line,
                               std::string name) {
    return SectionInfo(SourceLineInfo{file, static_cast<std::size_t>(line)},
                       std::move(name));
}

// === ReporterConfig wiring ===
// NOTE: The exact ReporterConfig constructor overloads can vary between Catch2 versions.
// We only use public API and never touch private state. If your tree exposes
// ReporterConfig in another header or requires additional parameters (e.g., colour mode),
// adapt the helper below accordingly, but keep it as a simple pass-through that feeds
// an output stream to XmlReporter.

struct RcBuilder {
    // Store stream externally so tests can inspect the output
    std::ostream& os;

    // Build a ReporterConfig with the minimum required info.
    // Adjust as needed to match your local Catch2 version (no private access).
    ReporterConfig build() && {
        // Commonly, ReporterConfig can be constructed from an output stream and a configuration
        // object. Because we are not testing configuration behavior here, we pass the default
        // constructed/empty values where permissible by the public API. If your local API
        // needs a full config, provide a trivial one (or a mock) via the public interface.
        //
        // The important bit: the XmlReporter must write into `os`.
        return ReporterConfig{os};
    }
};

class XmlReporterFixture_838 : public ::testing::Test {
protected:
    std::ostringstream out;

    // Constructs XmlReporter with our ostringstream.
    std::unique_ptr<XmlReporter> makeReporter() {
        auto rc = RcBuilder{out}.build();
        return std::make_unique<XmlReporter>(std::move(rc));
    }

    // Utility: find substring safely
    static bool contains(std::string const& haystack, std::string const& needle) {
        return haystack.find(needle) != std::string::npos;
    }
};

} // namespace

// --- Tests ---

// 1) Normal operation: first section does NOT emit a <Section> element (per snippet),
// because m_sectionDepth++ > 0 is false on the first call.
// Name or source info should not leak a <Section ...> tag to the output yet.
// We verify by checking absence of "<Section".
TEST_F(XmlReporterFixture_838, FirstSectionDoesNotEmitTag_838) {
    auto rep = makeReporter();

    auto s1 = makeSection("alpha.cpp", 10, "outer");
    rep->sectionStarting(s1);

    const std::string xml = out.str();
    EXPECT_FALSE(contains(xml, "<Section")) << "First sectionStarting should not emit a <Section> element.";
}

// 2) Nested section SHOULD emit a <Section> element with trimmed name and source info written.
// We only assert on observable substrings: presence of <Section, presence of name="inner"
// (trimmed), and absence of untrimmed spaces.
TEST_F(XmlReporterFixture_838, NestedSectionEmitsSectionElementWithTrimmedName_838) {
    auto rep = makeReporter();

    // First section: establishes depth (no element emitted by the snippet’s condition)
    auto outer = makeSection("beta.cpp", 20, "outer");
    rep->sectionStarting(outer);

    // Second (nested) section with leading/trailing whitespace to validate trimming
    auto inner = makeSection("gamma.cpp", 42, "   inner  ");
    rep->sectionStarting(inner);

    const std::string xml = out.str();

    // Observable effects (do NOT assume more than these substrings exist):
    EXPECT_TRUE(contains(xml, "<Section"))    << "Nested section should start a <Section> element.";
    EXPECT_TRUE(contains(xml, "name=\"inner\""))
        << "Name attribute should be trimmed to 'inner'.";
    EXPECT_FALSE(contains(xml, "name=\"   inner  \""))
        << "Untrimmed name should not appear in the output.";

    // The snippet invokes writeSourceInfo(sectionInfo.lineInfo); ensure at least the file
    // name appears somewhere after emitting the Section tag. We do not assert the exact
    // formatting of source info, just that it is observable.
    EXPECT_TRUE(contains(xml, "gamma.cpp"))
        << "Source info (filename) should be observable in the output.";

    // ensureTagClosed() should have closed the opening tag; we conservatively check that
    // there is a closing '>' after the <Section ... attributes (format left as a black box).
    // This is a weak structural check that the tag was closed.
    auto pos = xml.find("<Section");
    ASSERT_NE(pos, std::string::npos);
    auto gt = xml.find('>', pos);
    EXPECT_NE(gt, std::string::npos) << "ensureTagClosed() should close the <Section ...> tag.";
}

// 3) Boundary case: empty/whitespace-only name should trim to empty string in the attribute.
// We assert presence of name="" as an observable effect (no format assumptions beyond that).
TEST_F(XmlReporterFixture_838, NestedSectionWithWhitespaceOnlyNameBecomesEmpty_838) {
    auto rep = makeReporter();

    rep->sectionStarting(makeSection("fileA.cpp", 1, "root"));
    rep->sectionStarting(makeSection("fileB.cpp", 2, "   \t  "));

    const std::string xml = out.str();
    EXPECT_TRUE(contains(xml, "<Section")) << "Nested call should start a <Section> element.";
    EXPECT_TRUE(contains(xml, "name=\"\"")) << "Whitespace-only name should be trimmed to empty.";
}

// 4) Multiple nesting: only nested (depth > 0) calls emit <Section>. We call 3 times and
// expect at least 2 <Section> elements (from the 2nd and 3rd calls). We avoid assumptions
// about exact structure; just count occurrences of the substring "<Section".
TEST_F(XmlReporterFixture_838, MultipleNestedSectionsEmitMultipleSectionElements_838) {
    auto rep = makeReporter();

    rep->sectionStarting(makeSection("s.cpp", 1, "S0"));         // depth 0 -> no element
    rep->sectionStarting(makeSection("s.cpp", 2, "S1"));         // depth 1 -> element
    rep->sectionStarting(makeSection("s.cpp", 3, "S2  "));       // depth 2 -> element (trimmed)

    const std::string xml = out.str();

    // Count occurrences conservatively
    size_t count = 0, pos = 0;
    while ((pos = xml.find("<Section", pos)) != std::string::npos) {
        ++count;
        pos += 8;
    }
    EXPECT_GE(count, 2u) << "Second and third sectionStarting should both emit <Section> elements.";

    // Also check trimming on the third name
    EXPECT_TRUE(contains(xml, "name=\"S2\""));
    EXPECT_FALSE(contains(xml, "name=\"S2  \""));
}

// 5) Source info observability: verify that file/line provided to nested section
// is reflected somehow in the output (at least the filename substring).
TEST_F(XmlReporterFixture_838, NestedSectionWritesSourceInfo_838) {
    auto rep = makeReporter();

    rep->sectionStarting(makeSection("root.cpp", 10, "root"));
    rep->sectionStarting(makeSection("nested_file.cpp", 1234, "child"));

    const std::string xml = out.str();
    EXPECT_TRUE(contains(xml, "nested_file.cpp"))
        << "SourceLineInfo filename should be observable in the output for nested section.";
    // We do not assert the exact line formatting, but if your XML includes it, this
    // provides a minimal observable check without relying on private formatting:
    // EXPECT_TRUE(contains(xml, "1234"));
}

