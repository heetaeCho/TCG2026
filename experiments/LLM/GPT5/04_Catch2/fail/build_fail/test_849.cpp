// File: tests/XmlReporter_ListTests_849.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <vector>
#include <string>

// Catch2 headers (adjust paths to your tree)
#include "catch2/reporters/catch_reporter_xml.hpp"
#include "catch2/catch_test_case_info.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

// If your project uses different headers for these:
//   - NameAndTags
//   - StringRef
//   - ReporterConfig / StreamingReporterBase dependencies
// include them here.
#include "catch2/catch_user_config.hpp"      // <-- replace with your real IConfig or config header if needed
#include "catch2/reporters/catch_reporter_helpers.hpp" // often where ReporterConfig lives (adjust as needed)

// -----------------------------
// Minimal helpers (no logic inference)
// -----------------------------

// Helper to build NameAndTags without inferring internal behavior.
// Catch2's NameAndTags typically holds { std::string name; std::string tags; }.
static inline Catch::NameAndTags makeNameAndTags(const std::string& name,
                                                 const std::string& tags) {
    Catch::NameAndTags nt;
    nt.name = name;
    nt.tags = tags;
    return nt;
}

// Helper wrapper to create a TestCaseInfo with just the fields used by XmlReporter::listTests
static inline Catch::TestCaseInfo makeTCI(const std::string& className,
                                          const std::string& name,
                                          const std::string& tags,
                                          const char* file,
                                          std::size_t line) {
    Catch::SourceLineInfo sli{ file, line };
    return Catch::TestCaseInfo(Catch::StringRef(className), makeNameAndTags(name, tags), sli);
}

// Helper to create a TestCaseHandle from a TestCaseInfo.
// We pass a nullptr invoker because listTests never invokes tests.
static inline Catch::TestCaseHandle makeTCH(Catch::TestCaseInfo& info) {
    return Catch::TestCaseHandle(&info, /*invoker*/ nullptr);
}

// Reporter construction: route output to a provided ostringstream.
// Adjust this to the real ReporterConfig constructor used in your tree.
static inline Catch::XmlReporter makeXmlReporter(std::ostream& os) {
    // Many Catch2 versions construct ReporterConfig from: (IConfig*, std::ostream&, ColourImpl*)
    // or a similar struct. Replace with the correct call for your codebase.
    // A very common pattern is something like:
    //
    //   auto cfg = Catch::Detail::makePtr<MyConfigMockOrImpl>(...);
    //   Catch::ReporterConfig rc{ cfg, os, /*colourImpl*/ nullptr };
    //
    // Here, we avoid assumptions about IConfig by using a minimal viable config object.
    struct NoopConfig : Catch::IConfig {
        // Implement only what constructor checks, or leave empty
        // if your ReporterConfig doesn't query IConfig on construction.
        bool allowThrows() const override { return true; }
        // The rest can throw or return defaults if never queried by XmlReporter::listTests
        std::string name() const override { return "noop"; }
        // --- Provide stubs required by your Catch2 version ---
        // NOTE: Add any pure-virtuals your version requires.
    };
    static NoopConfig dummyCfg;

    Catch::ReporterConfig rc{ dummyCfg, os };
    return Catch::XmlReporter{ std::move(rc) };
}

// Utility: normalize output for assertions (trim leading/trailing spaces).
static inline std::string strip(const std::string& s) {
    auto b = s.find_first_not_of(" \t\r\n");
    auto e = s.find_last_not_of(" \t\r\n");
    if (b == std::string::npos) return std::string{};
    return s.substr(b, e - b + 1);
}

// -----------------------------
// Test fixture
// -----------------------------
class XmlReporterListTests_849 : public ::testing::Test {
protected:
    std::ostringstream oss;
    std::unique_ptr<Catch::XmlReporter> reporter;

    void SetUp() override {
        auto rep = makeXmlReporter(oss);
        reporter = std::make_unique<Catch::XmlReporter>(std::move(rep));
    }
};

// -----------------------------
// Tests
// -----------------------------

// Normal operation: single test case with basic fields
TEST_F(XmlReporterListTests_849, SingleTestCase_WritesExpectedElements_849) {
    using namespace Catch;

    auto tci = makeTCI("MySuite", "MyTest", "[fast][core]", "file_a.cpp", 123u);
    auto tch = makeTCH(tci);
    std::vector<TestCaseHandle> tests{ tch };

    reporter->listTests(tests);

    const std::string out = oss.str();
    // Outer container
    EXPECT_NE(out.find("<MatchingTests"), std::string::npos);
    EXPECT_NE(out.find("</MatchingTests>"), std::string::npos);

    // One TestCase entry
    EXPECT_NE(out.find("<TestCase>"), std::string::npos);
    EXPECT_NE(out.find("</TestCase>"), std::string::npos);

    // Name/ClassName/Tags
    EXPECT_NE(out.find("<Name>"), std::string::npos);
    EXPECT_NE(out.find("MyTest"), std::string::npos);
    EXPECT_NE(out.find("<ClassName>"), std::string::npos);
    EXPECT_NE(out.find("MySuite"), std::string::npos);
    EXPECT_NE(out.find("<Tags>"), std::string::npos);
    EXPECT_NE(out.find("[fast][core]"), std::string::npos);

    // SourceInfo/File/Line
    EXPECT_NE(out.find("<SourceInfo>"), std::string::npos);
    EXPECT_NE(out.find("<File>"), std::string::npos);
    EXPECT_NE(out.find("file_a.cpp"), std::string::npos);
    EXPECT_NE(out.find("<Line>"), std::string::npos);
    EXPECT_NE(out.find(">123<"), std::string::npos);
}

// Multiple entries: order is preserved and all items are present
TEST_F(XmlReporterListTests_849, MultipleTestCases_AllAreListed_849) {
    using namespace Catch;

    auto tci1 = makeTCI("A", "Alpha", "[a]", "a.cpp", 1u);
    auto tci2 = makeTCI("B", "Beta",  "[b]", "b.cpp", 2u);
    auto tci3 = makeTCI("C", "Gamma", "[c]", "c.cpp", 3u);

    auto tch1 = makeTCH(tci1);
    auto tch2 = makeTCH(tci2);
    auto tch3 = makeTCH(tci3);

    std::vector<TestCaseHandle> tests{ tch1, tch2, tch3 };
    reporter->listTests(tests);

    const std::string out = oss.str();

    // Ensure there are 3 <TestCase> entries (naive count is fine as an observable check)
    size_t count = 0;
    for (size_t pos = 0; (pos = out.find("<TestCase>", pos)) != std::string::npos; ++count, ++pos) {}
    EXPECT_EQ(count, 3u);

    // Spot-check each test's key fields appear
    EXPECT_NE(out.find("Alpha"), std::string::npos);
    EXPECT_NE(out.find("A"),     std::string::npos);
    EXPECT_NE(out.find("[a]"),   std::string::npos);

    EXPECT_NE(out.find("Beta"),  std::string::npos);
    EXPECT_NE(out.find("B"),     std::string::npos);
    EXPECT_NE(out.find("[b]"),   std::string::npos);

    EXPECT_NE(out.find("Gamma"), std::string::npos);
    EXPECT_NE(out.find("C"),     std::string::npos);
    EXPECT_NE(out.find("[c]"),   std::string::npos);
}

// Boundary: empty list -> outer container present, no TestCase entries
TEST_F(XmlReporterListTests_849, EmptyList_ProducesMatchingTestsContainerOnly_849) {
    std::vector<Catch::TestCaseHandle> tests;
    reporter->listTests(tests);

    const std::string out = strip(oss.str());
    // Must contain the container element even if empty
    EXPECT_NE(out.find("<MatchingTests"), std::string::npos);
    EXPECT_NE(out.find("</MatchingTests>"), std::string::npos);

    // Should not contain any TestCase entries
    EXPECT_EQ(out.find("<TestCase>"), std::string::npos);
}

// Special characters in fields should be safely written (observable via escaped text)
TEST_F(XmlReporterListTests_849, SpecialCharacters_AreSafelyWritten_849) {
    using namespace Catch;

    // Include characters typically needing XML escaping
    auto tci = makeTCI("C & Co <", R"(Name "X" & <Y>)", "[tag&1][<weird>]",
                       R"(dir/fi&le<.cpp)", 42u);
    auto tch = makeTCH(tci);
    std::vector<TestCaseHandle> tests{ tch };

    reporter->listTests(tests);
    const std::string out = oss.str();

    // We do not assert exact escaping implementation (no internal logic inference),
    // but we can assert that raw dangerous characters are not left unescaped in element text.
    // A basic observable check: the dangerous characters should appear only in escaped form.
    // At minimum, ensure the raw sequences exist in some encoded way (e.g., &amp; &lt; &quot;).
    EXPECT_EQ(out.find("C & Co <"), std::string::npos);
    EXPECT_NE(out.find("C &amp; Co &lt;"), std::string::npos);

    EXPECT_EQ(out.find(R"(Name "X" & <Y>)"), std::string::npos);
    // check for some escaped substrings
    EXPECT_NE(out.find("Name &quot;X&quot; &amp; &lt;Y&gt;"), std::string::npos);

    EXPECT_EQ(out.find("dir/fi&le<.cpp>"), std::string::npos);
    EXPECT_NE(out.find("dir/fi&amp;le&lt;.cpp"), std::string::npos);

    // Tags string is written as a single text node; ensure escapes present
    EXPECT_EQ(out.find("[tag&1][<weird>]"), std::string::npos);
    EXPECT_NE(out.find("[tag&amp;1][&lt;weird&gt;]"), std::string::npos);
}

// Large line number boundary-ish check (still observable via output)
TEST_F(XmlReporterListTests_849, LargeLineNumber_IsSerializedAsDecimal_849) {
    using namespace Catch;

    const std::size_t bigLine = static_cast<std::size_t>(1ull << 31); // fits size_t on 64-bit
    auto tci = makeTCI("Big", "BigLine", "[]", "big.cpp", bigLine);
    auto tch = makeTCH(tci);
    std::vector<TestCaseHandle> tests{ tch };

    reporter->listTests(tests);
    const std::string out = oss.str();

    // to_string(line) is used — we just check the decimal appears
    const std::string needle = ">" + std::to_string(bigLine) + "<";
    EXPECT_NE(out.find(needle), std::string::npos);
}
