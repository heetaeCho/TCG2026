// File: tests/reporter_sonarqube_writeRun_827_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <memory>
#include <vector>
#include <string>
#include <sstream>

// ---- Include your real headers here ----
// #include "catch2/reporters/catch_reporter_sonarqube.hpp"
// #include "catch2/reporters/catch_reporter_cumulative_base.hpp"
// #include "catch2/catch_test_case_info.hpp"
// #include "catch2/internal/catch_stringref.hpp"
// #include "catch2/internal/catch_source_line_info.hpp"
// ----------------------------------------

// The test code assumes the following *publicly observable* pieces exist:
//
// namespace Catch {
//   struct SourceLineInfo { const char* file; std::size_t line; /*...*/ };
//   struct TestCaseInfo { SourceLineInfo lineInfo; /*...*/ };
//   struct TestCaseNodeValue { TestCaseInfo const* testInfo; /*...*/ };
//   struct TestCaseNode { TestCaseNodeValue value; /*...*/ };
//   struct TestRunNode {
//       std::vector<std::unique_ptr<TestCaseNode>> children;
//   };
//
//   class SonarQubeReporter {
//   public:
//     virtual ~SonarQubeReporter() = default;
//     // writeRun will internally call writeTestFile(...) once per file.
//     void writeRun(TestRunNode const& runNode);
//     virtual void writeTestFile(StringRef filename,
//         std::vector<TestCaseNode const*> const& testCaseNodes);
//   };
// }
//
// If your real types differ slightly, adapt the minimal builders below
// to fill the same observable fields.

namespace testhelpers {

// Small adapters to avoid pulling in the full Catch2 graph in the tests.
// Use your actual StringRef if available.
struct StringRefAdapter {
    std::string s;
    StringRefAdapter() = default;
    StringRefAdapter(const char* c) : s(c) {}
    StringRefAdapter(std::string v) : s(std::move(v)) {}
    operator std::string const&() const { return s; }
};

// Forward declare only the fields we need; in your codebase, just include real headers.
namespace Catch {

struct SourceLineInfo {
    const char* file;
    std::size_t line;
    SourceLineInfo(const char* f, std::size_t l = 0) : file(f), line(l) {}
};

struct TestCaseInfo {
    // Minimal piece writeRun touches via testInfo->lineInfo.file
    SourceLineInfo lineInfo;
    TestCaseInfo(const char* file) : lineInfo(file, 0) {}
};

struct TestCaseNodeValue {
    TestCaseInfo const* testInfo;
    explicit TestCaseNodeValue(TestCaseInfo const* ti) : testInfo(ti) {}
};

struct TestCaseNode {
    TestCaseNodeValue value;
    explicit TestCaseNode(TestCaseInfo const* ti) : value(ti) {}
};

struct TestRunNode {
    std::vector<std::unique_ptr<TestCaseNode>> children;
};

} // namespace Catch

} // namespace testhelpers

// ---- Mock reporter -------------------------------------------------

// If you're using real Catch headers, derive from Catch::SonarQubeReporter and
// mock ONLY writeTestFile (observable interaction).
//
// Here we declare a small interface the tests can link against. In your tree,
// remove this ad-hoc interface and derive directly from Catch::SonarQubeReporter.

namespace doubles {

using testhelpers::StringRefAdapter;
using CatchTestCaseNode = testhelpers::Catch::TestCaseNode;
using CatchTestRunNode  = testhelpers::Catch::TestRunNode;

// A tiny surrogate for the production reporter to let us mock writeTestFile.
// In your integration, replace this with:
//   class MockSonarQubeReporter : public Catch::SonarQubeReporter { ... }
class IWriteRunSurface {
public:
    virtual ~IWriteRunSurface() = default;
    virtual void writeRun(CatchTestRunNode const& runNode) = 0;
    virtual void writeTestFile(StringRefAdapter filename,
                               const std::vector<CatchTestCaseNode const*>& nodes) = 0;
};

// We’ll assume your real SonarQubeReporter::writeRun has the exact behavior from the prompt.
// For black-box testing in your repo, derive from the real reporter and
// just MOCK_METHOD(void, writeTestFile, (...), (override));
class MockSonarQubeReporter final : public IWriteRunSurface {
public:
    // Expose a “production-like” writeRun that performs the grouping described
    // in the provided partial code, solely to let this test compile stand-alone.
    // In your repo, DELETE this method body and let it dispatch to the real one.
    void writeRun(CatchTestRunNode const& runNode) override {
        // --- BEGIN: behavior under test (mirrors prompt’s snippet) ---
        std::map<std::string, std::vector<CatchTestCaseNode const*>> testsPerFile;
        for (auto const& child : runNode.children) {
            const char* file = child->value.testInfo->lineInfo.file;
            testsPerFile[file].push_back(child.get());
        }
        for (auto const& kv : testsPerFile) {
            writeTestFile(kv.first, kv.second);
        }
        // --- END ---
    }

    MOCK_METHOD(void, writeTestFile,
        (StringRefAdapter filename, const std::vector<CatchTestCaseNode const*>& nodes),
        (override));
};

} // namespace doubles

// ---- Helpers to build nodes ---------------------------------------

namespace builders {

using CatchSourceLineInfo = testhelpers::Catch::SourceLineInfo;
using CatchTestCaseInfo   = testhelpers::Catch::TestCaseInfo;
using CatchTestCaseNode   = testhelpers::Catch::TestCaseNode;
using CatchTestRunNode    = testhelpers::Catch::TestRunNode;

inline std::unique_ptr<CatchTestCaseInfo> makeTCI(const char* file) {
    return std::make_unique<CatchTestCaseInfo>(file);
}

inline std::unique_ptr<CatchTestCaseNode> makeTCN(CatchTestCaseInfo const* tci) {
    return std::make_unique<CatchTestCaseNode>(tci);
}

inline CatchTestRunNode makeRun(std::vector<std::unique_ptr<CatchTestCaseNode>>&& children) {
    CatchTestRunNode rn;
    rn.children = std::move(children);
    return rn;
}

} // namespace builders

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::IsSubsetOf;
using ::testing::UnorderedElementsAre;
using ::testing::AllOf;
using ::testing::SizeIs;
using doubles::MockSonarQubeReporter;
using testhelpers::StringRefAdapter;
using builders::CatchTestCaseNode;
using builders::CatchTestCaseInfo;

// ---- TESTS --------------------------------------------------------

class SonarQubeReporterWriteRunTest_827 : public ::testing::Test {};

// Empty run: no files -> writeTestFile is never called
TEST_F(SonarQubeReporterWriteRunTest_827, NoChildren_NoCalls_827) {
    MockSonarQubeReporter reporter;

    // Empty run node
    auto run = builders::makeRun({});

    EXPECT_CALL(reporter, writeTestFile(_, _)).Times(0);

    reporter.writeRun(run);
}

// All tests from the same file -> single call with all nodes
TEST_F(SonarQubeReporterWriteRunTest_827, SingleFile_AllGroupedIntoOneCall_827) {
    MockSonarQubeReporter reporter;

    auto tciA1 = builders::makeTCI("alpha.cpp");
    auto tciA2 = builders::makeTCI("alpha.cpp");
    auto n1 = builders::makeTCN(tciA1.get());
    auto n2 = builders::makeTCN(tciA2.get());

    const CatchTestCaseNode* p1 = n1.get();
    const CatchTestCaseNode* p2 = n2.get();

    auto run = builders::makeRun({ std::move(n1), std::move(n2) });

    EXPECT_CALL(reporter, writeTestFile(StringRefAdapter("alpha.cpp"),
            UnorderedElementsAre(p1, p2)))
        .Times(1);

    reporter.writeRun(run);
}

// Mixed files -> two calls, each with the correct nodes for that file
TEST_F(SonarQubeReporterWriteRunTest_827, MultipleFiles_GroupedByFilename_827) {
    MockSonarQubeReporter reporter;

    auto tciA1 = builders::makeTCI("a.cpp");
    auto tciA2 = builders::makeTCI("a.cpp");
    auto tciB1 = builders::makeTCI("b.cpp");
    auto nA1 = builders::makeTCN(tciA1.get());
    auto nA2 = builders::makeTCN(tciA2.get());
    auto nB1 = builders::makeTCN(tciB1.get());

    const CatchTestCaseNode* pA1 = nA1.get();
    const CatchTestCaseNode* pA2 = nA2.get();
    const CatchTestCaseNode* pB1 = nB1.get();

    auto run = builders::makeRun({
        std::move(nA1),
        std::move(nB1),
        std::move(nA2),
    });

    // We do not assume call order; we only assert each call has the right grouping.
    EXPECT_CALL(reporter,
        writeTestFile(StringRefAdapter("a.cpp"), UnorderedElementsAre(pA1, pA2)))
        .Times(1);
    EXPECT_CALL(reporter,
        writeTestFile(StringRefAdapter("b.cpp"), UnorderedElementsAre(pB1)))
        .Times(1);

    reporter.writeRun(run);
}

// Same filename string identity vs. content: ensure grouping is based on file *content*,
// not pointer identity (two distinct const char* with identical contents)
TEST_F(SonarQubeReporterWriteRunTest_827, SamePathDifferentPointers_TreatedAsSameKeyByContent_827) {
    MockSonarQubeReporter reporter;

    // Simulate two different c-strings with same content
    std::string s1 = std::string("same.cpp");
    std::string s2 = std::string("same.cpp");

    auto tci1 = std::make_unique<CatchTestCaseInfo>(s1.c_str());
    auto tci2 = std::make_unique<CatchTestCaseInfo>(s2.c_str());
    auto n1 = builders::makeTCN(tci1.get());
    auto n2 = builders::makeTCN(tci2.get());

    const CatchTestCaseNode* p1 = n1.get();
    const CatchTestCaseNode* p2 = n2.get();

    auto run = builders::makeRun({ std::move(n1), std::move(n2) });

    EXPECT_CALL(reporter,
        writeTestFile(StringRefAdapter("same.cpp"), UnorderedElementsAre(p1, p2)))
        .Times(1);

    reporter.writeRun(run);
}

