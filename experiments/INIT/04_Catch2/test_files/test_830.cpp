// File: tests/sonarqube_writeSection_830_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <sstream>
#include <string>
#include <vector>
#include <memory>

// ---- Minimal stubs for external collaborators (ONLY to allow construction) ----
namespace Catch {

// Very small SourceLineInfo stub, enough to construct SectionInfo
struct SourceLineInfo {
    const char* file;
    std::size_t line;
    SourceLineInfo(const char* f = "dummy.cpp", std::size_t l = 1) : file(f), line(l) {}
};

// StringRef is used by XmlWriter internally; tests do not touch it.
// Provide a light stub to keep headers happy if needed by includes.
struct StringRef {
    const char* data_;
    size_t size_;
    StringRef(const char* d = "", size_t s = 0) : data_(d), size_(s) {}
    StringRef(std::string const& s) : data_(s.c_str()), size_(s.size()) {}
    operator std::string() const { return std::string(data_, size_); }
};

// Counts (observable via total())
struct Counts {
    std::uint64_t passed = 0;
    std::uint64_t failed = 0;
    std::uint64_t failedButOk = 0;
    std::uint64_t skipped = 0;
    std::uint64_t total() const { return passed + failed + failedButOk + skipped; }
};

// SectionInfo: we only need the name
struct SectionInfo {
    std::string name;
    SourceLineInfo lineInfo;
    SectionInfo(SourceLineInfo const& sli, std::string n, const char* = nullptr)
        : name(std::move(n)), lineInfo(sli) {}
};

// SectionStats (subset needed by SonarQubeReporter::writeSection)
struct SectionStats {
    SectionInfo sectionInfo;
    Counts assertions;
    double durationInSeconds = 0.0;
    bool missingAssertions = false;

    SectionStats(SectionInfo&& si, Counts const& a, double d, bool m)
        : sectionInfo(std::move(si)), assertions(a), durationInSeconds(d), missingAssertions(m) {}
};

// Forward declare to match real hierarchy
struct CumulativeReporterBase {
    struct SectionNode {
        SectionStats stats;
        std::vector<std::unique_ptr<SectionNode>> childSections;

        explicit SectionNode(SectionStats const& s) : stats(s) {}
    };
};

// A super-minimal ReporterConfig compatible wrapper exposing a stream.
// In Catch2, reporters receive a config that yields the stream they write to.
// Here we just provide that stream reference so the reporter writes into our ostringstream.
struct ReporterConfig {
    std::ostream& stream;
    explicit ReporterConfig(std::ostream& os) : stream(os) {}
};

} // namespace Catch

// ---- Include the SUT public header AFTER stubs so it picks up compatible types ----
#include "catch2/reporters/catch_reporter_sonarqube.hpp"

// Helper: create a SectionNode with given name, totals, duration
static std::unique_ptr<Catch::CumulativeReporterBase::SectionNode>
makeSectionNode(const std::string& name, std::uint64_t totalAssertions, double durationSeconds) {
    Catch::Counts c{};
    // Place all into 'passed' to keep semantics simple; only total() matters here
    c.passed = totalAssertions;
    Catch::SectionInfo si{ Catch::SourceLineInfo{"dummy.cpp", 1}, name };
    Catch::SectionStats stats{ std::move(si), c, durationSeconds, false };
    return std::make_unique<Catch::CumulativeReporterBase::SectionNode>(stats);
}

// Minimal shim reporter that lets us construct SonarQubeReporter with our stream.
// We rely on the real SonarQubeReporter from Catch2; no overrides or re-implementations.
namespace {
struct TestFixture_SonarQube_830 : ::testing::Test {
    std::ostringstream os;
    std::unique_ptr<Catch::SonarQubeReporter> reporter;

    void SetUp() override {
        Catch::ReporterConfig cfg{ os };
        reporter = std::make_unique<Catch::SonarQubeReporter>(std::move(cfg));
    }

    // Extract all values of an XML attribute `name="..."` from the emitted XML
    static std::vector<std::string> extractAttr(const std::string& xml, const std::string& attr) {
        std::vector<std::string> out;
        std::string key = attr + "=\"";
        std::size_t pos = 0;
        while ((pos = xml.find(key, pos)) != std::string::npos) {
            pos += key.size();
            auto end = xml.find('"', pos);
            if (end == std::string::npos) break;
            out.emplace_back(xml.substr(pos, end - pos));
            pos = end + 1;
        }
        return out;
    }

    static int countTag(const std::string& xml, const std::string& tag) {
        int cnt = 0;
        std::string open = "<" + tag;
        std::size_t pos = 0;
        while ((pos = xml.find(open, pos)) != std::string::npos) {
            ++cnt;
            ++pos;
        }
        return cnt;
    }
};
} // anonymous namespace

// ========== Tests ==========

// 1) Emits <testCase> with trimmed section name when assertions > 0 and no rootName
TEST_F(TestFixture_SonarQube_830, EmitsTestCase_WithTrimmedName_NoRoot_830) {
    auto node = makeSectionNode("   Parent Name   ", /*total*/1, /*secs*/1.0);

    reporter->writeSection(/*rootName*/"", *node, /*okToFail*/false);

    const std::string xml = os.str();
    EXPECT_GT(countTag(xml, "testCase"), 0) << "Should emit a <testCase> for non-zero assertions";
    auto names = extractAttr(xml, "name");
    ASSERT_FALSE(names.empty());
    EXPECT_EQ(names.front(), "Parent Name") << "Name should be trimmed (no leading/trailing spaces)";
}

// 2) Prepends rootName and writes duration in milliseconds as integer
TEST_F(TestFixture_SonarQube_830, PrependsRoot_And_WritesDurationMs_830) {
    auto node = makeSectionNode("Leaf", /*total*/2, /*secs*/2.5); // 2500 ms expected

    reporter->writeSection(/*rootName*/"ROOT", *node, /*okToFail*/false);

    const std::string xml = os.str();
    ASSERT_GT(countTag(xml, "testCase"), 0);

    auto names = extractAttr(xml, "name");
    ASSERT_FALSE(names.empty());
    EXPECT_EQ(names.front(), "ROOT/Leaf");

    auto durations = extractAttr(xml, "duration");
    ASSERT_FALSE(durations.empty());
    EXPECT_THAT(durations.front(), ::testing::AnyOf("2500", "2500.0"))
        << "Duration should be seconds * 1000 (ms)";
}

// 3) Does not emit <testCase> when no assertions and (implicitly) no stdOut/stdErr
TEST_F(TestFixture_SonarQube_830, SkipsWhenNoAssertionsAndNoOutput_830) {
    auto node = makeSectionNode("Empty", /*total*/0, /*secs*/0.0);

    reporter->writeSection(/*rootName*/"", *node, /*okToFail*/false);

    const std::string xml = os.str();
    EXPECT_EQ(countTag(xml, "testCase"), 0) << "No <testCase> should be written";
}

// 4) Recurses into child sections and composes hierarchical names with slashes
TEST_F(TestFixture_SonarQube_830, RecursesAndBuildsHierarchicalNames_830) {
    auto parent = makeSectionNode("Parent", /*total*/1, /*secs*/0.1);
    auto child  = makeSectionNode("Child",  /*total*/3, /*secs*/0.2);
    auto grand  = makeSectionNode("Grand",  /*total*/1, /*secs*/0.3);

    // Build tree: Parent -> Child -> Grand
    child->childSections.emplace_back(std::move(grand));
    parent->childSections.emplace_back(std::move(child));

    reporter->writeSection(/*rootName*/"ROOT", *parent, /*okToFail*/false);

    const std::string xml = os.str();
    ASSERT_EQ(countTag(xml, "testCase"), 3) << "Parent, child, and grandchild all have assertions";

    auto names = extractAttr(xml, "name");
    // Order corresponds to pre-order traversal (parent before children)
    EXPECT_THAT(names, ::testing::Contains(std::string("ROOT/Parent")));
    EXPECT_THAT(names, ::testing::Contains(std::string("ROOT/Parent/Child")));
    EXPECT_THAT(names, ::testing::Contains(std::string("ROOT/Parent/Child/Grand")));
}

// 5) Changing okToFail must NOT affect name/duration attributes emission for the same stats
//    (writeAssertions behavior itself is tested elsewhere)
TEST_F(TestFixture_SonarQube_830, OkToFailDoesNotChangeNameOrDuration_830) {
    auto nodeA = makeSectionNode("Case", /*total*/1, /*secs*/1.234); // 1234 ms
    reporter->writeSection(/*rootName*/"R", *nodeA, /*okToFail*/false);
    const std::string xmlFalse = os.str();

    os.str(""); os.clear();

    auto nodeB = makeSectionNode("Case", /*total*/1, /*secs*/1.234);
    reporter->writeSection(/*rootName*/"R", *nodeB, /*okToFail*/true);
    const std::string xmlTrue = os.str();

    // Compare only the attributes we observe from writeSection itself
    auto namesF = TestFixture_SonarQube_830::extractAttr(xmlFalse, "name");
    auto namesT = TestFixture_SonarQube_830::extractAttr(xmlTrue,  "name");
    ASSERT_FALSE(namesF.empty());
    ASSERT_FALSE(namesT.empty());
    EXPECT_EQ(namesF.front(), namesT.front());

    auto dursF = TestFixture_SonarQube_830::extractAttr(xmlFalse, "duration");
    auto dursT = TestFixture_SonarQube_830::extractAttr(xmlTrue,  "duration");
    ASSERT_FALSE(dursF.empty());
    ASSERT_FALSE(dursT.empty());
    EXPECT_EQ(dursF.front(), dursT.front());
}
