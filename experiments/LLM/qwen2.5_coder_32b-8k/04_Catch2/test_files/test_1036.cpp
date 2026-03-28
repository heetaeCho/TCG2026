#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"

#include "catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;

using namespace testing;



class SectionTrackerTest : public Test {

protected:

    NiceMock<MockTrackerContext> mockCtx;

    NameAndLocation nameAndLocation{"test_name", "file.cpp", 10};

    std::unique_ptr<SectionTracker> sectionTracker;



    void SetUp() override {

        sectionTracker = std::make_unique<SectionTracker>(std::move(nameAndLocation), mockCtx, nullptr);

    }

};



TEST_F(SectionTrackerTest_1036, IsComplete_NoFilters_1036) {

    EXPECT_TRUE(sectionTracker->isComplete());

}



TEST_F(SectionTrackerTest_1036, IsComplete_WithMatchingFilter_1036) {

    sectionTracker->addInitialFilters({"test_name"});

    EXPECT_TRUE(sectionTracker->isComplete());

}



TEST_F(SectionTrackerTest_1036, IsComplete_WithNonMatchingFilter_1036) {

    sectionTracker->addInitialFilters({"non_matching_filter"});

    EXPECT_FALSE(sectionTracker->isComplete());

}



TEST_F(SectionTrackerTest_1036, AddInitialFilters_EmptyList_1036) {

    sectionTracker->addInitialFilters({});

    EXPECT_TRUE(sectionTracker->getFilters().empty());

}



TEST_F(SectionTrackerTest_1036, AddInitialFilters_NonEmptyList_1036) {

    std::vector<std::string> filters = {"filter1", "filter2"};

    sectionTracker->addInitialFilters(filters);

    EXPECT_EQ(sectionTracker->getFilters().size(), 2);

}



TEST_F(SectionTrackerTest_1036, AddNextFilters_EmptyList_1036) {

    std::vector<StringRef> filters = {};

    sectionTracker->addNextFilters(filters);

    EXPECT_TRUE(sectionTracker->getFilters().empty());

}



TEST_F(SectionTrackerTest_1036, AddNextFilters_NonEmptyList_1036) {

    std::vector<StringRef> filters = {StringRef("filter1"), StringRef("filter2")};

    sectionTracker->addNextFilters(filters);

    EXPECT_EQ(sectionTracker->getFilters().size(), 2);

}



TEST_F(SectionTrackerTest_1036, TrimmedName_Default_1036) {

    EXPECT_STREQ(sectionTracker->trimmedName().data(), "test_name");

}



TEST_F(SectionTrackerTest_1036, IsSectionTracker_ReturnsTrue_1036) {

    EXPECT_TRUE(sectionTracker->isSectionTracker());

}
