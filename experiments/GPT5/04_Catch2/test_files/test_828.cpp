// File: tests/SonarQubeReporter_writeTestFile_828.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <sstream>
#include <vector>
#include <string>

// ---- Minimal forward decls to avoid depending on private state ----
namespace Catch {
    struct TestCaseNode;   // Incomplete; we never inspect its contents.

    // Forward decls frequently needed by reporter constructors.
    struct TestRunInfo;
    struct TestRunNode;
    struct SectionNode;
    struct AssertionStats;

    // Reporter infra forward decls (constructor arg types)
    class IConfig;

    // ReporterConfig as declared in Catch2; we only need the ctor that accepts a stream.
    // In real Catch2, ReporterConfig has more fields; this matches the common signature.
    class ReporterConfig {
    public:
        explicit ReporterConfig(std::ostream& os, IConfig const* cfg = nullptr)
        : m_os(os), m_cfg(cfg) {}
        std::ostream& stream() const { return m_os; }
        IConfig const* fullConfig() const { return m_cfg; }
    private:
        std::ostream& m_os;
        IConfig const* m_cfg;
    };

    // CumulativeReporterBase forward decl
    class CumulativeReporterBase {
    public:
        explicit CumulativeReporterBase(ReporterConfig&&) {}
        virtual ~CumulativeReporterBase() = default;
    };

    // Public API we are testing
    class SonarQubeReporter : public CumulativeReporterBase {
    public:
        explicit SonarQubeReporter(ReporterConfig&& cfg)
        : CumulativeReporterBase(std::move(cfg)) {}

        // Interface under test (from prompt)
        void writeTestFile(StringRef filename,
                           const std::vector<const TestCaseNode*>& testCaseNodes);

        // Collaborator called by writeTestFile (we only observe that it is invoked)
        virtual void writeTestCase(const TestCaseNode& testCaseNode);

        // Usually reporters also expose lifecycle hooks; not needed here.
    };

    // StringRef as declared publicly; we only need construction from const char*
    // and conversion to std::string for convenience in assertions if used.
    class StringRef {
    public:
        StringRef(const char* s) : m_ptr(s ? s : ""), m_size(std::strlen(m_ptr)) {}
        const char* data() const noexcept { return m_ptr; }
        size_t size() const noexcept { return m_size; }
    private:
        const char* m_ptr;
        size_t m_size;
    };
} // namespace Catch

using ::testing::_;
using ::testing::ElementsAre;
using ::testing::StrNe;
using ::testing::IsEmpty;

// ---- Test double: spy reporter that records writeTestCase calls ----
namespace {
    class SpySonarQubeReporter_828 : public Catch::SonarQubeReporter {
    public:
        explicit SpySonarQubeReporter_828(Catch::ReporterConfig&& cfg, std::ostream& sink)
        : Catch::SonarQubeReporter(std::move(cfg)), m_sink(sink) {}

        void writeTestCase(const Catch::TestCaseNode& node) override {
            (void)node; // We do not inspect internals (black box)
            ++call_count;
        }

        // Helper to access produced output (observable)
        std::string output() const { return static_cast<std::ostringstream const&>(m_sink).str(); }

        int call_count = 0;

    private:
        std::ostream& m_sink;
    };

    // Helper that fabricates N dummy TestCaseNode pointers
    // We never dereference or inspect; writeTestFile passes reference to our override.
    // To keep well-defined behavior, we provide storage with proper (opaque) type.
    struct DummyTCNStorage {
        // Create N dummy objects of an empty type compatible with TestCaseNode name.
        // We declare an empty struct with the same name in the Catch namespace to
        // provide an object to reference without touching internals.
        struct Opaque {};
        std::vector<Opaque> storage;
        std::vector<const Catch::TestCaseNode*> asPtrs;

        explicit DummyTCNStorage(size_t n) : storage(n) {
            asPtrs.reserve(n);
            for (size_t i = 0; i < n; ++i) {
                // Reinterpret the address of our Opaque instance as TestCaseNode.
                // We never read/write through it; it only satisfies the reference.
                asPtrs.push_back(reinterpret_cast<const Catch::TestCaseNode*>(&storage[i]));
            }
        }
    };
} // namespace

// ---------- Tests ----------

TEST(SonarQubeReporter_writeTestFile_828, WritesPathAttributeAndCallsWriteTestCase_ForEachNode_828) {
    // Arrange
    std::ostringstream os;
    Catch::ReporterConfig rc(os, /*cfg*/ nullptr);
    SpySonarQubeReporter_828 reporter(std::move(rc), os);

    const char* filename = "src/foo/bar.cpp";
    DummyTCNStorage dummy(3); // three test cases

    // Act
    reporter.writeTestFile(Catch::StringRef(filename), dummy.asPtrs);

    // Assert (observable output)
    const std::string out = os.str();
    // Must open a <file ...> element (we only check a stable substring).
    EXPECT_NE(out.find("<file"), std::string::npos);               // element started
    // Must contain the path attribute written by writeTestFile
    EXPECT_NE(out.find(std::string("path=\"") + filename + "\""), std::string::npos);

    // Assert (external interaction): writeTestCase called exactly once per node
    EXPECT_EQ(reporter.call_count, 3);
}

TEST(SonarQubeReporter_writeTestFile_828, HandlesEmptyList_NoWriteTestCaseCalls_StillWritesFileElement_828) {
    // Arrange
    std::ostringstream os;
    Catch::ReporterConfig rc(os, nullptr);
    SpySonarQubeReporter_828 reporter(std::move(rc), os);

    const char* filename = "only/attributes/no-tests.cpp";
    std::vector<const Catch::TestCaseNode*> none;

    // Act
    reporter.writeTestFile(Catch::StringRef(filename), none);

    // Assert: still emits a <file ...> with path attribute
    const std::string out = os.str();
    EXPECT_NE(out.find("<file"), std::string::npos);
    EXPECT_NE(out.find(std::string("path=\"") + filename + "\""), std::string::npos);

    // No test cases => no calls to writeTestCase
    EXPECT_EQ(reporter.call_count, 0);
}

TEST(SonarQubeReporter_writeTestFile_828, AcceptsEmptyFilename_WritesEmptyPathAttribute_828) {
    // Arrange
    std::ostringstream os;
    Catch::ReporterConfig rc(os, nullptr);
    SpySonarQubeReporter_828 reporter(std::move(rc), os);

    const char* emptyName = "";
    DummyTCNStorage dummy(1);

    // Act
    reporter.writeTestFile(Catch::StringRef(emptyName), dummy.asPtrs);

    // Assert
    const std::string out = os.str();
    EXPECT_NE(out.find("<file"), std::string::npos);
    // Expect path="" to be present (empty path propagated as given)
    EXPECT_NE(out.find("path=\"\""), std::string::npos);

    // One node -> one writeTestCase call
    EXPECT_EQ(reporter.call_count, 1);
}
