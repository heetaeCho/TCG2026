// File: tests/XmlReporter_Listeners_848.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>
#include <vector>

// Catch2 — use your real includes/paths as in your repo
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/internal/catch_xmlwriter.hpp"
#include "catch2/internal/catch_list.hpp"
// If ReporterConfig lives in a different header in your tree, include it here.
#include "catch2/reporters/catch_reporter_helpers.hpp" // adjust if needed

using ::testing::HasSubstr;
using ::testing::Not;

namespace {

using Catch::XmlReporter;
using Catch::ListenerDescription;

// --- Helper to count non-overlapping occurrences of a substring (observable check only)
static int countOccurrences(const std::string& haystack, const std::string& needle) {
    if (needle.empty()) return 0;
    int count = 0;
    std::string::size_type pos = 0;
    while ((pos = haystack.find(needle, pos)) != std::string::npos) {
        ++count;
        pos += needle.size();
    }
    return count;
}

// Minimal helper to build ReporterConfig with a custom ostream.
// If your project has a canonical factory, prefer that and remove this.
static Catch::ReporterConfig makeConfig(std::ostream& os) {
    // In most Catch2 setups, ReporterConfig takes (IConfig const&, std::ostream&, ColourMode)
    // or similar; adjust as needed to your exact signature.
    // The goal is only to route XmlReporter’s output into `os` so we can assert on it.
    auto cfg = Catch::Detail::make_unique<Catch::ConfigData>(); // replace with your IConfig if required
    // If you have an IConfigImpl handy, use it instead of ConfigData.
    // Fallback: many repos provide a convenience ctor (IConfig&, std::ostream&).
    return Catch::ReporterConfig{ Catch::getCurrentContext().getConfig(), os };
    // NOTE: If the above line does not match your codebase, replace with your local ReporterConfig builder.
}

struct XmlReporter_ListListeners_Fixture_848 : ::testing::Test {
    std::ostringstream out;
    std::unique_ptr<XmlReporter> reporter;

    void SetUp() override {
        auto rc = makeConfig(out);
        reporter = std::make_unique<XmlReporter>(std::move(rc));
    }
};

} // namespace

// ===========================
// Tests
// ===========================

// Normal: empty input -> only container element, no Listener entries.
TEST_F(XmlReporter_ListListeners_Fixture_848, EmptyList_WritesOnlyContainer_848) {
    std::vector<ListenerDescription> descriptions; // empty

    reporter->listListeners(descriptions);
    const std::string s = out.str();

    EXPECT_THAT(s, HasSubstr("RegisteredListeners")) << "Should open the listeners container";
    EXPECT_THAT(s, Not(HasSubstr("<Listener"))) << "No individual <Listener> entries expected for empty input";
}

// Normal: single listener -> writes Name and Description under a Listener element.
TEST_F(XmlReporter_ListListeners_Fixture_848, SingleListener_WritesNameAndDescription_848) {
    ListenerDescription ld;
    // These fields exist in the real codebase; set them here.
    ld.name = "TeamHook";
    ld.description = "Fires before/after tests";

    reporter->listListeners({ld});
    const std::string s = out.str();

    // Observable structure checks without assuming exact whitespace/indentation.
    EXPECT_THAT(s, HasSubstr("RegisteredListeners"));
    EXPECT_THAT(s, HasSubstr("Listener"));
    EXPECT_THAT(s, HasSubstr("Name"));
    EXPECT_THAT(s, HasSubstr("Description"));

    // Values should appear (XmlWriter applies escaping/formatting internally).
    EXPECT_THAT(s, HasSubstr("TeamHook"));
    EXPECT_THAT(s, HasSubstr("Fires before/after tests"));
}

// Normal: multiple listeners -> all are emitted.
TEST_F(XmlReporter_ListListeners_Fixture_848, MultipleListeners_AllEmitted_848) {
    ListenerDescription a; a.name = "A"; a.description = "alpha";
    ListenerDescription b; b.name = "B"; b.description = "beta";

    reporter->listListeners({a, b});
    const std::string s = out.str();

    // Both names and descriptions present
    EXPECT_THAT(s, HasSubstr("A"));
    EXPECT_THAT(s, HasSubstr("alpha"));
    EXPECT_THAT(s, HasSubstr("B"));
    EXPECT_THAT(s, HasSubstr("beta"));

    // At least 2 <Listener> occurrences (robust to whitespace/self-closing differences)
    EXPECT_GE(countOccurrences(s, "Listener"), 2);
}

// Boundary: empty strings -> tags still present (observable by tag names), no crash.
TEST_F(XmlReporter_ListListeners_Fixture_848, EmptyStrings_TagsStillPresent_848) {
    ListenerDescription ld; ld.name = ""; ld.description = "";

    reporter->listListeners({ld});
    const std::string s = out.str();

    // We don’t assert exact serialization of empty text; just that the elements are written.
    EXPECT_THAT(s, HasSubstr("Listener"));
    EXPECT_THAT(s, HasSubstr("Name"));
    EXPECT_THAT(s, HasSubstr("Description"));
}

// Edge/escaping: special XML characters are escaped by XmlWriter (observable in output).
TEST_F(XmlReporter_ListListeners_Fixture_848, SpecialCharacters_AreEscapedByXmlWriter_848) {
    ListenerDescription ld;
    ld.name = "A&B <X>";
    ld.description = "Use 1 < 2 & 3 > 2";

    reporter->listListeners({ld});
    const std::string s = out.str();

    // We do not reimplement escaping rules; we assert presence of safe forms rather than raw unsafe text.
    EXPECT_THAT(s, Not(HasSubstr("A&B <X>")));
    EXPECT_THAT(s, Not(HasSubstr("1 < 2 & 3 > 2")));

    // Typical XML escaping artifacts; tolerate either full escaping or entity usage.
    // These checks are lenient (any one suffices) to avoid coupling to exact XmlWriter formatting.
    bool looksEscaped =
        s.find("A&amp;B") != std::string::npos ||
        s.find("&lt;X&gt;") != std::string::npos ||
        s.find("1 &lt; 2 &amp; 3 &gt; 2") != std::string::npos;
    EXPECT_TRUE(looksEscaped) << "Expected special characters to be XML-escaped by XmlWriter";
}
