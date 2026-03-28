#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"

#include "catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class SectionTrackerTest_1040 : public ::testing::Test {

protected:

    SectionTrackerTest_1040() : tracker(NameAndLocation{"test", SourceLineInfo{}}, context, nullptr) {}



    TrackerContext context;

    SectionTracker tracker;

};



TEST_F(SectionTrackerTest_1040, AddInitialFilters_EmptyList_DoesNotChangeFilters_1040) {

    tracker.addInitialFilters({});

    EXPECT_EQ(tracker.getFilters().size(), 2); // Root and Test Case filters

}



TEST_F(SectionTrackerTest_1040, AddInitialFilters_SingleFilter_AddsToFilters_1040) {

    tracker.addInitialFilters({"filter1"});

    EXPECT_EQ(tracker.getFilters().size(), 3);

    EXPECT_EQ(tracker.getFilters()[2], "filter1");

}



TEST_F(SectionTrackerTest_1040, AddInitialFilters_MultipleFilters_AddsAllToFilters_1040) {

    tracker.addInitialFilters({"filter1", "filter2"});

    EXPECT_EQ(tracker.getFilters().size(), 4);

    EXPECT_EQ(tracker.getFilters()[2], "filter1");

    EXPECT_EQ(tracker.getFilters()[3], "filter2");

}



TEST_F(SectionTrackerTest_1040, GetFilters_ReturnsCorrectInitialFilters_1040) {

    tracker.addInitialFilters({"filter1", "filter2"});

    auto filters = tracker.getFilters();

    EXPECT_EQ(filters.size(), 4);

    EXPECT_EQ(filters[2], "filter1");

    EXPECT_EQ(filters[3], "filter2");

}



TEST_F(SectionTrackerTest_1040, TrimmedName_ReturnsTrimmedName_1040) {

    std::string name = tracker.trimmedName().toString();

    EXPECT_EQ(name, "test");

}
