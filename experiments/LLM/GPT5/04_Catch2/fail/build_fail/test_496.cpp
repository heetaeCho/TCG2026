// File: tests/run_context_sectionStarted_496_tests.cpp

#include <gtest/gtest.h>
#include <gmock/gmock.h>

// ---- Minimal includes for the SUT's public surface ----
#include "catch2/internal/catch_run_context.hpp"
#include "catch2/catch_section_info.hpp"
#include "catch2/catch_totals.hpp"
#include "catch2/internal/catch_test_case_tracker.hpp"
#include "catch2/interfaces/catch_interfaces_reporter.hpp"
#include "catch2/internal/catch_stringref.hpp"
#include "catch2/internal/catch_source_line_info.hpp"

using ::testing::_;
using ::testing::AllOf;
using ::testing::Field;
using ::testing::Property;
using ::testing::Truly;

namespace Catch {

// ---- Test seams for external collaborators used by sectionStarted ----

// 1) Make SectionTracker::acquire controllable.
//    We return a singleton SectionTracker that answers isOpen() from a flag
//    we can flip from tests.
namespace TestCaseTracking {

class TestOpenFlagTracker : public SectionTracker {
public:
    // We do not depend on internal behaviour; just override isOpen().
    explicit TestOpenFlagTracker(TrackerContext& ctx)
        : SectionTracker(NameAndLocation{"<test>", SourceLineInfo{"<file>", 0}}, ctx, nullptr) {}

    bool isOpenFlag = false;

    bool isOpen() const override { return isOpenFlag; }
};

// Global seam storage (lifetime spans tests)
static TrackerContext g_ctx_for_seam;
static TestOpenFlagTracker* g_tracker_singleton = nullptr;

// Overwrite the acquire call to return our singleton
SectionTracker& SectionTracker::acquire(TrackerContext& ctx,
                                        NameAndLocationRef const&) {
    if (!g_tracker_singleton) {
        // Create once, tie to provided ctx so RunContext can pass the same
        g_tracker_singleton = new TestOpenFlagTracker(ctx);
    }
    return *g_tracker_singleton;
}

} // namespace TestCaseTracking

// 2) Provide a no-op OutputRedirect + scopedDeactivate RAII so dereference is safe.
struct OutputRedirect {};
struct ScopedDeactivateGuard {
    explicit ScopedDeactivateGuard(OutputRedirect&) {}
    ~ScopedDeactivateGuard() = default;
};
inline ScopedDeactivateGuard scopedDeactivate(OutputRedirect& r) { return ScopedDeactivateGuard{r}; }

// 3) Minimal IConfig stub so RunContext can be constructed.
class IConfig {
public:
    virtual ~IConfig() = default;
    virtual StringRef name() const { return StringRef("run"); }
};

} // namespace Catch

// ---- Mock reporter (IEventListener) ----
namespace Catch {

class MockReporter : public IEventListener {
public:
    // Forward base ctor
    explicit MockReporter(IConfig const* cfg) : IEventListener(cfg) {}
    MOCK_METHOD(void, sectionStarting, (const SectionInfo&), (override));
};

} // namespace Catch

// Helper: build a RunContext with a mock reporter
static std::unique_ptr<Catch::MockReporter> makeMockReporter(const Catch::IConfig* cfg,
                                                             Catch::IEventListenerPtr& outPtr) {
    auto rep = std::make_unique<Catch::MockReporter>(cfg);
    outPtr.reset(rep.get()); // transfer raw into the unique_ptr-like alias
    return rep;
}

// ---- Test fixture ----
class RunContextSectionStartedTest_496 : public ::testing::Test {
protected:
    // Own the config; reporter is owned through IEventListenerPtr inside RunContext
    std::unique_ptr<Catch::IConfig> cfg;
    std::unique_ptr<Catch::MockReporter> reporterOwned;
    Catch::IEventListenerPtr reporterPtr; // moved into RunContext
    std::unique_ptr<Catch::RunContext> ctx;

    void SetUp() override {
        cfg = std::make_unique<Catch::IConfig>();
        reporterOwned = makeMockReporter(cfg.get(), reporterPtr);
        // Construct SUT
        ctx = std::make_unique<Catch::RunContext>(cfg.get(), std::move(reporterPtr));

        // Ensure the singleton test tracker exists & is tied to the same internal TrackerContext
        // The seam's acquire will lazily create it when sectionStarted is first called.
    }

    void TearDown() override {
        // Leave seam singleton around; tests do not depend on deletion between runs.
    }
};

// --- Tests ---

// Closed tracker path: should return false, not notify, and must not modify output 'assertions'.
TEST_F(RunContextSectionStartedTest_496, ReturnsFalseAndDoesNotNotify_WhenTrackerNotOpen_496) {
    using namespace Catch;
    using namespace Catch::TestCaseTracking;

    // Make the seam tracker closed
    SectionNameAndLocation dummyNameLoc;
    // Force creation and flip flag before call
    auto& tr = SectionTracker::acquire(*reinterpret_cast<TrackerContext*>(nullptr),
                                       NameAndLocationRef{StringRef("ignored"),
                                                          SourceLineInfo{"ignored.cpp", 1}});
    static_cast<TestOpenFlagTracker&>(tr).isOpenFlag = false;

    // Expect no notification
    EXPECT_CALL(*reporterOwned, sectionStarting(_)).Times(0);

    Counts outAssertions{};
    // Seed with sentinel values to detect modification
    outAssertions.passed = 13;
    outAssertions.failed = 99;

    const bool started = ctx->sectionStarted(StringRef("sec"),
                                             SourceLineInfo{"file.cpp", 42},
                                             outAssertions);

    EXPECT_FALSE(started);
    // Output param should be untouched in the "closed" branch
    EXPECT_EQ(outAssertions.passed, 13u);
    EXPECT_EQ(outAssertions.failed, 99u);
}

// Open tracker path: should return true, notify reporter with the same name/line,
// and overwrite the output 'assertions' value (we only assert that it changed).
TEST_F(RunContextSectionStartedTest_496, ReturnsTrue_ReportsStartAndCopiesTotals_496) {
    using namespace Catch;
    using namespace Catch::TestCaseTracking;

    // Make seam tracker open
    auto& tr = SectionTracker::acquire(*reinterpret_cast<TrackerContext*>(nullptr),
                                       NameAndLocationRef{StringRef("ignored"),
                                                          SourceLineInfo{"ignored.cpp", 1}});
    static_cast<TestOpenFlagTracker&>(tr).isOpenFlag = true;

    // Expect one notification with matching name & line
    EXPECT_CALL(*reporterOwned, sectionStarting(
        AllOf(
            Field(&SectionInfo::name, std::string("My/Section")),
            Field(&SectionInfo::lineInfo,
                  AllOf(Field(&SourceLineInfo::file, "unit.cpp"),
                        Field(&SourceLineInfo::line, 777u)))
        )
    )).Times(1);

    Counts outAssertions{};
    // Sentinel that should be overwritten by SUT
    outAssertions.passed = 777;
    outAssertions.failed = 888;

    const bool started = ctx->sectionStarted(StringRef("My/Section"),
                                             SourceLineInfo{"unit.cpp", 777},
                                             outAssertions);

    EXPECT_TRUE(started);
    // We cannot rely on internal totals, but we can assert the SUT overwrote the output param.
    // So at least one field should differ from our sentinel seed.
    bool changed = !(outAssertions.passed == 777u && outAssertions.failed == 888u);
    EXPECT_TRUE(changed);
}

// Boundary: empty section name is still forwarded to reporter with correct line info when open.
TEST_F(RunContextSectionStartedTest_496, EmptySectionNameStillReported_WhenOpen_496) {
    using namespace Catch;
    using namespace Catch::TestCaseTracking;

    auto& tr = SectionTracker::acquire(*reinterpret_cast<TrackerContext*>(nullptr),
                                       NameAndLocationRef{StringRef("ignored"),
                                                          SourceLineInfo{"ignored.cpp", 1}});
    static_cast<TestOpenFlagTracker&>(tr).isOpenFlag = true;

    EXPECT_CALL(*reporterOwned, sectionStarting(
        AllOf(
            Field(&SectionInfo::name, std::string("")), // empty name
            Field(&SectionInfo::lineInfo,
                  AllOf(Field(&SourceLineInfo::file, "b.cpp"),
                        Field(&SourceLineInfo::line, 1u)))
        )
    )).Times(1);

    Counts outAssertions{};
    const bool started = ctx->sectionStarted(StringRef(""),
                                             SourceLineInfo{"b.cpp", 1},
                                             outAssertions);

    EXPECT_TRUE(started);
}
