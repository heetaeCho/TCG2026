// File: tests/json_reporter_listTests_876.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <vector>
#include <regex>

// Catch2 public headers we need for constructing inputs and the reporter.
#include <catch2/reporters/catch_reporter_json.hpp>
#include <catch2/internal/catch_stringref.hpp>
#include <catch2/catch_test_case_info.hpp>
#include <catch2/catch_source_line_info.hpp>
#include <catch2/reporters/catch_reporter_registrars.hpp>
#include <catch2/reporters/catch_reporter_helpers.hpp>
#include <catch2/interfaces/catch_interfaces_config.hpp>

using ::testing::HasSubstr;
using ::testing::MatchesRegex;

namespace {

class DummyConfig : public Catch::IConfig {
public:
    // Minimal surface required by ReporterConfig/IConfig usage in reporters.
    // We keep everything default/benign so it does not affect observable output.
    bool allowThrows() const override { return true; }
    std::ostream& stream() const override { return *m_os; }
    std::string name() const override { return "run"; }
    bool includeSuccessfulResults() const override { return true; }
    bool shouldDebugBreak() const override { return false; }
    bool warnAboutMissingAssertions() const override { return false; }
    bool warnAboutNoTests() const override { return false; }
    bool abortAfter() const override { return false; }
    bool showHelp() const override { return false; }
    bool showInvisibles() const override { return false; }
    bool filenamesAsTags() const override { return false; }
    bool listTests() const override { return false; }
    bool listTags() const override { return false; }
    bool listReporters() const override { return false; }
    bool listListeners() const override { return false; }
    bool benchmarks() const override { return false; }
    const std::vector<std::string>& getTestsOrTags() const override { static std::vector<std::string> v; return v; }
    Catch::Verbosity verbosity() const override { return Catch::Verbosity::Normal; }

    // Set output stream for the reporter to write to.
    explicit DummyConfig(std::ostream& os) : m_os(&os) {}

private:
    std::ostream* m_os;
};

// Helper to build a TestCaseHandle from simple inputs
static Catch::TestCaseHandle makeHandle(
    Catch::StringRef testName,
    Catch::StringRef className,
    Catch::StringRef file,
    std::size_t line,
    std::vector<Catch::StringRef> tagStrings
) {
    // Build NameAndTags
    Catch::NameAndTags nt;
    nt.name = std::string(testName);
    for (auto t : tagStrings) {
        nt.tags.emplace_back(std::string(t));
    }

    Catch::SourceLineInfo sli{ std::string(file), static_cast<std::size_t>(line) };

    auto* info = new Catch::TestCaseInfo{ className, nt, sli };
    // Preserve tag order by pushing tags as provided
    info->tags.clear();
    info->tags.reserve(tagStrings.size());
    for (auto t : tagStrings) {
        info->tags.emplace_back(Catch::StringRef{t});
    }

    // The invoker is irrelevant for listTests; nullptr is fine.
    return Catch::TestCaseHandle{ info, nullptr };
}

// A small fixture that wires JsonReporter to a stringstream.
class JsonReporterListTests_876 : public ::testing::Test {
protected:
    std::ostringstream os;
    std::unique_ptr<DummyConfig> cfg;
    std::unique_ptr<Catch::JsonReporter> reporter;

    void SetUp() override {
        cfg = std::make_unique<DummyConfig>(os);
        Catch::ReporterConfig rc{ *cfg, os };
        reporter = std::make_unique<Catch::JsonReporter>(std::move(rc));
    }

    void TearDown() override {
        reporter.reset();
        cfg.reset();
    }
};

} // namespace

// ============ Tests ============

// Normal operation: two tests with names, class-names, and tags appear in the JSON.
// TEST_ID: 876
TEST_F(JsonReporterListTests_876, ListsTwoTestsWithNamesClassAndTags_876) {
    auto h1 = makeHandle("Alpha", "SuiteA", "alpha.cpp", 42, { "[fast]" , "[db]" });
    auto h2 = makeHandle("Beta",  "SuiteB", "beta.cpp",  7,  { "[slow]" });

    std::vector<Catch::TestCaseHandle> tests{ h1, h2 };

    reporter->listTests(tests);

    const std::string out = os.str();

    // Top-level key "tests" exists (do not assume whitespace/formatting)
    EXPECT_THAT(out, HasSubstr("\"tests\""));

    // Each test object contains expected fields
    EXPECT_THAT(out, MatchesRegex(".*\"name\"\\s*:\\s*\"Alpha\".*\"class-name\"\\s*:\\s*\"SuiteA\".*"));
    EXPECT_THAT(out, MatchesRegex(".*\"name\"\\s*:\\s*\"Beta\".*\"class-name\"\\s*:\\s*\"SuiteB\".*"));

    // Tag arrays include provided tags
    EXPECT_THAT(out, MatchesRegex(".*\"tags\"\\s*:\\s*\\[\\s*\"\\[fast\\]\"\\s*,\\s*\"\\[db\\]\"\\s*\\].*"));
    EXPECT_THAT(out, MatchesRegex(".*\"tags\"\\s*:\\s*\\[\\s*\"\\[slow\\]\"\\s*\\].*"));
}

// Boundary: empty test list should still create/mention the "tests" array (possibly empty).
// TEST_ID: 876
TEST_F(JsonReporterListTests_876, HandlesEmptyTestList_ProducesEmptyTestsArrayOrKey_876) {
    std::vector<Catch::TestCaseHandle> tests;
    reporter->listTests(tests);

    const std::string out = os.str();

    // We expect the "tests" key to appear; the array should be empty or begin an array.
    // Being flexible about whitespace/format.
    EXPECT_THAT(out, MatchesRegex(".*\"tests\"\\s*:\\s*\\[\\s*\\].*|.*\"tests\"\\s*:\\s*\\[.*"));
}

// Boundary/ordering: multiple tags preserve insertion order in serialized output.
// TEST_ID: 876
TEST_F(JsonReporterListTests_876, PreservesTagOrder_876) {
    auto h = makeHandle("Gamma", "SuiteC", "gamma.cpp", 100,
                        { "[first]", "[second]", "[third]" });
    std::vector<Catch::TestCaseHandle> tests{ h };

    reporter->listTests(tests);

    const std::string out = os.str();

    // Check the order [first], [second], [third] is preserved
    EXPECT_THAT(
        out,
        MatchesRegex(".*\"tags\"\\s*:\\s*\\[\\s*\"\\[first\\]\"\\s*,\\s*\"\\[second\\]\"\\s*,\\s*\"\\[third\\]\"\\s*\\].*")
    );
}

// Special characters in names/class-names are correctly JSON-quoted (observable via presence of quotes/backslashes).
// We do NOT re-implement escaping logic; we just check the output includes a properly quoted field.
// TEST_ID: 876
TEST_F(JsonReporterListTests_876, QuotesSpecialCharactersInNames_876) {
    auto h = makeHandle("Quote\"Name\n", "Class\\X", "q.cpp", 1, { "[t]" });
    std::vector<Catch::TestCaseHandle> tests{ h };

    reporter->listTests(tests);
    const std::string out = os.str();

    // "name": "<quoted...>"  — ensure there are quotes around and at least a backslash appears somewhere (escape)
    EXPECT_THAT(out, MatchesRegex(".*\"name\"\\s*:\\s*\".*\".*"));
    EXPECT_THAT(out, HasSubstr("\\"));
}

// Minimal tags behavior: no tags provided -> tags array exists and is empty.
// TEST_ID: 876
TEST_F(JsonReporterListTests_876, WritesEmptyTagsArrayWhenNoTags_876) {
    auto h = makeHandle("NoTags", "SuiteEmpty", "empty.cpp", 2, { /* none */ });
    std::vector<Catch::TestCaseHandle> tests{ h };

    reporter->listTests(tests);
    const std::string out = os.str();

    EXPECT_THAT(out, MatchesRegex(".*\"name\"\\s*:\\s*\"NoTags\".*"));
    EXPECT_THAT(out, MatchesRegex(".*\"class-name\"\\s*:\\s*\"SuiteEmpty\".*"));
    // tags: []
    EXPECT_THAT(out, MatchesRegex(".*\"tags\"\\s*:\\s*\\[\\s*\\].*"));
}
