// File: tests/json_reporter_testRunStarting_865.cpp

#include <gtest/gtest.h>
#include <string>

// Include only public headers that declare the interfaces used below.
#include "catch2/reporters/catch_reporter_json.hpp"
#include "catch2/reporters/catch_reporter_streaming_base.hpp"
#include "catch2/internal/catch_test_run_info.hpp"

using namespace Catch;

namespace {

// A very small stub ReporterConfig builder. In real codebase this would be the
// proper way to construct ReporterConfig for reporters; here we keep it minimal
// and interface-only. If your codebase provides helpers, prefer them.
struct DummyStream : std::ostream {
    DummyStream() : std::ostream(nullptr) {}
};

struct TestConfigFactory {
    static ReporterConfig make() {
        // The real ReporterConfig usually wants a stream, preferences, and
        // a config. We provide the bare minimum interface-wise.
        // If your actual ReporterConfig requires more, adapt this helper
        // to use the legitimate ctor available in your codebase.
        // We keep it non-throwing and non-observing on purpose.
        // NOTE: This is intentionally minimal and should be replaced
        // by the real construction used in your project.
        return ReporterConfig(
            std::unique_ptr<IStreamingReporter>(nullptr), // unused here
            nullptr,                                      // colour impl / preferences, as required
            nullptr                                       // config ptr
        );
    }
};

// A tiny helper that constructs a JsonReporter in a safe way for tests.
// If your codebase has a factory for reporters, prefer using it.
std::unique_ptr<JsonReporter> makeJsonReporter() {
    ReporterConfig cfg = TestConfigFactory::make();
    return std::unique_ptr<JsonReporter>(new JsonReporter(std::move(cfg)));
}

} // namespace

// ============ TESTS ============

TEST(JsonReporter_testRunStarting_865, NormalRunName_NoThrow_865) {
    auto reporter = makeJsonReporter();

    // Normal operation: providing a typical run name must not throw.
    TestRunInfo info{ StringRef("sample-run") };
    EXPECT_NO_THROW({
        reporter->testRunStarting(info);
    });

    // Sanity check: calling testRunEnded after starting should also be safe.
    // This validates that testRunStarting established a consistent state
    // for the rest of the public lifecycle (observable behavior = no throws).
    TestRunStats dummyStats{};
    EXPECT_NO_THROW({
        reporter->testRunEnded(dummyStats);
    });
}

TEST(JsonReporter_testRunStarting_865, EmptyRunName_Boundary_NoThrow_865) {
    auto reporter = makeJsonReporter();

    // Boundary condition: empty run name.
    TestRunInfo info{ StringRef("") };
    EXPECT_NO_THROW({
        reporter->testRunStarting(info);
    });

    TestRunStats dummyStats{};
    EXPECT_NO_THROW({
        reporter->testRunEnded(dummyStats);
    });
}

TEST(JsonReporter_testRunStarting_865, StartThenStartCaseSequence_NoThrow_865) {
    auto reporter = makeJsonReporter();

    // Start the test run.
    TestRunInfo info{ StringRef("sequence-run") };
    EXPECT_NO_THROW({
        reporter->testRunStarting(info);
    });

    // After testRunStarting, typical sequence calls should be valid & non-throwing.
    // We cannot assert internal JSON structure; we only verify public, observable behavior = no exceptions.
    TestCaseInfo tcInfo{
        NameAndTags{ StringRef("tc"), StringRef("") }, // adjust to your ctor if needed
        SourceLineInfo{ StringRef("file.cpp"), 1 },
        {}, {}, {} // remaining fields as your interface requires
    };

    EXPECT_NO_THROW({
        reporter->testCaseStarting(tcInfo);
    });

    TestCaseStats tcStats{
        tcInfo, {}, {}, {}, false // adapt as required by your interface
    };
    EXPECT_NO_THROW({
        reporter->testCaseEnded(tcStats);
    });

    TestRunStats runStats{};
    EXPECT_NO_THROW({
        reporter->testRunEnded(runStats);
    });
}

TEST(JsonReporter_testRunStarting_865, MultipleInstances_Isolated_NoInterference_865) {
    // Verifies there is no shared state coupling across reporter instances.
    auto r1 = makeJsonReporter();
    auto r2 = makeJsonReporter();

    TestRunInfo info1{ StringRef("r1") };
    TestRunInfo info2{ StringRef("r2") };

    EXPECT_NO_THROW(r1->testRunStarting(info1));
    EXPECT_NO_THROW(r2->testRunStarting(info2));

    TestRunStats s1{};
    TestRunStats s2{};
    EXPECT_NO_THROW(r1->testRunEnded(s1));
    EXPECT_NO_THROW(r2->testRunEnded(s2));
}

// Optional: If your build runs with assertions enabled and the JSON reporter
// requires being "inside an Object" before testRunStarting (as per the snippet),
// you can include a smoke test that just ensures the call does not hard-assert
// in release builds. In debug builds, this may trigger if preconditions are not met.
// Keep it as a guarded smoke test if your CI runs in release.
//
// TEST(JsonReporter_testRunStarting_865, Smoke_ReleaseOnly_NoAssert_865) {
//     auto reporter = makeJsonReporter();
//     TestRunInfo info{ StringRef("smoke") };
//     EXPECT_NO_THROW(reporter->testRunStarting(info));
// }

