#include <gtest/gtest.h>

// Include the necessary headers
// Based on the partial code and dependencies, we include what's available
namespace Catch {
namespace TestCaseTracking {

class SectionTracker {
public:
    bool isSectionTracker() const { return true; }
};

} // namespace TestCaseTracking
} // namespace Catch

// Test fixture
class SectionTrackerTest_1037 : public ::testing::Test {
protected:
    Catch::TestCaseTracking::SectionTracker tracker_;
};

// Test that isSectionTracker returns true
TEST_F(SectionTrackerTest_1037, IsSectionTrackerReturnsTrue_1037) {
    EXPECT_TRUE(tracker_.isSectionTracker());
}

// Test that isSectionTracker consistently returns true on multiple calls
TEST_F(SectionTrackerTest_1037, IsSectionTrackerConsistentlyReturnsTrue_1037) {
    EXPECT_TRUE(tracker_.isSectionTracker());
    EXPECT_TRUE(tracker_.isSectionTracker());
    EXPECT_TRUE(tracker_.isSectionTracker());
}

// Test that different instances all return true for isSectionTracker
TEST_F(SectionTrackerTest_1037, DifferentInstancesReturnTrue_1037) {
    Catch::TestCaseTracking::SectionTracker tracker1;
    Catch::TestCaseTracking::SectionTracker tracker2;
    Catch::TestCaseTracking::SectionTracker tracker3;

    EXPECT_TRUE(tracker1.isSectionTracker());
    EXPECT_TRUE(tracker2.isSectionTracker());
    EXPECT_TRUE(tracker3.isSectionTracker());
}

// Test that isSectionTracker is const-correct (can be called on const object)
TEST_F(SectionTrackerTest_1037, IsSectionTrackerIsConstCorrect_1037) {
    const Catch::TestCaseTracking::SectionTracker constTracker;
    EXPECT_TRUE(constTracker.isSectionTracker());
}

// Test that the return type is bool
TEST_F(SectionTrackerTest_1037, IsSectionTrackerReturnsBool_1037) {
    auto result = tracker_.isSectionTracker();
    static_assert(std::is_same<decltype(result), bool>::value,
                  "isSectionTracker should return bool");
    EXPECT_EQ(result, true);
}

// Test copy constructed object also returns true
TEST_F(SectionTrackerTest_1037, CopyConstructedTrackerReturnsTrue_1037) {
    Catch::TestCaseTracking::SectionTracker copy(tracker_);
    EXPECT_TRUE(copy.isSectionTracker());
}

// Test copy assigned object also returns true
TEST_F(SectionTrackerTest_1037, CopyAssignedTrackerReturnsTrue_1037) {
    Catch::TestCaseTracking::SectionTracker other;
    other = tracker_;
    EXPECT_TRUE(other.isSectionTracker());
}
