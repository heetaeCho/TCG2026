// File: tests/TeamCityReporter_testRunEnded_782.cpp

#include <gtest/gtest.h>
#include <sstream>
#include <string>

// ===== Minimal stubs to satisfy the provided partial interfaces =====
namespace Catch {

// Minimal stand-ins for external types used in the partial snippet
using StringRef = std::string;

struct Totals { // not used by the tested function
    // leave empty
};

struct TestRunInfo {
    StringRef name;
    constexpr TestRunInfo(StringRef _name) : name(_name) {}
};

struct TestRunStats {
    TestRunInfo runInfo;
    Totals totals;
    bool aborting;
    TestRunStats(TestRunInfo const& _runInfo, Totals const& _totals, bool _aborting)
        : runInfo(_runInfo), totals(_totals), aborting(_aborting) {}
};

// The tested implementation uses `escape(...)`. We provide a no-op stub
// because the tests below do not rely on any escaping semantics.
static inline std::string escape(const StringRef& s) { return s; }

// A minimal reporter that contains exactly the method under test and the stream
class TeamCityReporter {
public:
    explicit TeamCityReporter(std::ostream& os) : m_stream(os) {}

    void testRunEnded(TestRunStats const& runStats) {
        // From the provided partial code:
        // m_stream << "##teamcity[testSuiteFinished name='" << escape( runStats.runInfo.name ) << "']\n";
        m_stream << "##teamcity[testSuiteFinished name='"
                 << escape(runStats.runInfo.name) << "']\n";
    }

private:
    std::ostream& m_stream;
};

} // namespace Catch

// ===== Test fixture =====
class TeamCityReporter_TestRunEnded_782 : public ::testing::Test {
protected:
    std::ostringstream oss;
    Catch::TeamCityReporter reporter{oss};
    Catch::Totals totals{}; // unused, but required by TestRunStats
};

// ===== Tests =====

// Normal operation: writes a single well-formed TeamCity "testSuiteFinished" line
TEST_F(TeamCityReporter_TestRunEnded_782, WritesFinishedLineWithRunName_782) {
    Catch::TestRunInfo info{"AllTests"};
    Catch::TestRunStats stats{info, totals, false};

    reporter.testRunEnded(stats);

    EXPECT_EQ(oss.str(), "##teamcity[testSuiteFinished name='AllTests']\n");
}

// Boundary: empty run name should still produce the correct line with empty name
TEST_F(TeamCityReporter_TestRunEnded_782, HandlesEmptyRunName_782) {
    Catch::TestRunInfo info{""};
    Catch::TestRunStats stats{info, totals, false};

    reporter.testRunEnded(stats);

    EXPECT_EQ(oss.str(), "##teamcity[testSuiteFinished name='']\n");
}

// Normal: name containing spaces should be preserved verbatim in the output
TEST_F(TeamCityReporter_TestRunEnded_782, PreservesSpacesInRunName_782) {
    Catch::TestRunInfo info{"My Suite 1"};
    Catch::TestRunStats stats{info, totals, false};

    reporter.testRunEnded(stats);

    EXPECT_EQ(oss.str(), "##teamcity[testSuiteFinished name='My Suite 1']\n");
}

// Interaction/ordering: multiple calls append multiple lines in the same order
TEST_F(TeamCityReporter_TestRunEnded_782, MultipleRunsAppendInOrder_782) {
    Catch::TestRunInfo info1{"SuiteA"};
    Catch::TestRunInfo info2{"SuiteB"};

    reporter.testRunEnded(Catch::TestRunStats{info1, totals, false});
    reporter.testRunEnded(Catch::TestRunStats{info2, totals, false});

    const std::string expected =
        "##teamcity[testSuiteFinished name='SuiteA']\n"
        "##teamcity[testSuiteFinished name='SuiteB']\n";
    EXPECT_EQ(oss.str(), expected);
}
