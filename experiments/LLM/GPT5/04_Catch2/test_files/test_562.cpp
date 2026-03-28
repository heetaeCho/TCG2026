// File: streaming_reporter_base_test_562.cpp
#include <gtest/gtest.h>

//
// Minimal forward declarations to keep the test focused on observable behavior.
// We do NOT rely on internal fields of TestCaseInfo.
//
namespace Catch {
    struct TestCaseInfo { /* opaque for these tests */ };

    class ReporterBase {
    public:
        virtual ~ReporterBase() = default;
    };

    class StreamingReporterBase : public ReporterBase {
    protected:
        // This is what the code under test updates.
        const TestCaseInfo* currentTestCaseInfo = nullptr;

    public:
        // Function under test:
        virtual void testCaseStarting(TestCaseInfo const& _testInfo) {
            currentTestCaseInfo = &_testInfo;
        }
    };
} // namespace Catch

// A tiny spy that exposes ONLY observable facts about the base’s behavior.
class StreamingReporterSpy : public Catch::StreamingReporterBase {
public:
    bool IsCurrentNull() const { return currentTestCaseInfo == nullptr; }
    bool PointsTo(const Catch::TestCaseInfo& info) const {
        return currentTestCaseInfo == &info;
    }
};

// ----------------------------------------------------------------------------
// Tests (TEST_ID = 562)
// ----------------------------------------------------------------------------

TEST(StreamingReporterBase_562, PointerIsNullBeforeAnyTestCaseStarts_562) {
    StreamingReporterSpy reporter;
    EXPECT_TRUE(reporter.IsCurrentNull());
}

TEST(StreamingReporterBase_562, testCaseStartingStoresAddressOfGivenInfo_Once_562) {
    StreamingReporterSpy reporter;
    Catch::TestCaseInfo tci;

    // Act
    reporter.testCaseStarting(tci);

    // Assert (observable through spy API)
    EXPECT_TRUE(reporter.PointsTo(tci));
    EXPECT_FALSE(reporter.IsCurrentNull());
}

TEST(StreamingReporterBase_562, testCaseStartingOverwritesWithLatestTestInfo_562) {
    StreamingReporterSpy reporter;
    Catch::TestCaseInfo first;
    Catch::TestCaseInfo second;

    // Act 1
    reporter.testCaseStarting(first);
    ASSERT_TRUE(reporter.PointsTo(first));

    // Act 2
    reporter.testCaseStarting(second);

    // Assert: should now point to 'second', not 'first'
    EXPECT_TRUE(reporter.PointsTo(second));
    EXPECT_FALSE(reporter.PointsTo(first));
}

TEST(StreamingReporterBase_562, CallingWithSameObjectTwiceRemainsPointingToThatObject_562) {
    StreamingReporterSpy reporter;
    Catch::TestCaseInfo same;

    reporter.testCaseStarting(same);
    ASSERT_TRUE(reporter.PointsTo(same));

    // Call again with the same reference
    reporter.testCaseStarting(same);

    // Still points to the same object
    EXPECT_TRUE(reporter.PointsTo(same));
}
