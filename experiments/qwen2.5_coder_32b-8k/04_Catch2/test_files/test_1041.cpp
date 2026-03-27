#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class SectionTrackerTest_1041 : public ::testing::Test {

protected:

    TrackerContext ctx;

    NameAndLocation nameAndLocation{"test", SourceLineInfo("", 0)};

    ITracker* parent = nullptr;

    SectionTracker tracker{nameAndLocation, ctx, parent};



    std::vector<StringRef> createStringRefs(const std::vector<std::string>& strings) {

        std::vector<StringRef> stringRefs;

        for (const auto& str : strings) {

            stringRefs.emplace_back(str);

        }

        return stringRefs;

    }

};



TEST_F(SectionTrackerTest_1041, AddNextFilters_EmptyList_NoChange_1041) {

    std::vector<StringRef> filters = createStringRefs({});

    tracker.addNextFilters(filters);



    EXPECT_EQ(tracker.getFilters().size(), 0);

}



TEST_F(SectionTrackerTest_1041, AddNextFilters_SingleElement_Added_1041) {

    std::vector<StringRef> filters = createStringRefs({"filter1"});

    tracker.addNextFilters(filters);



    EXPECT_EQ(tracker.getFilters().size(), 1);

    EXPECT_EQ(tracker.getFilters()[0], "filter1");

}



TEST_F(SectionTrackerTest_1041, AddNextFilters_MultipleElements_AddedCorrectly_1041) {

    std::vector<StringRef> filters = createStringRefs({"filter1", "filter2", "filter3"});

    tracker.addNextFilters(filters);



    EXPECT_EQ(tracker.getFilters().size(), 3);

    EXPECT_EQ(tracker.getFilters()[0], "filter1");

    EXPECT_EQ(tracker.getFilters()[1], "filter2");

    EXPECT_EQ(tracker.getFilters()[2], "filter3");

}



TEST_F(SectionTrackerTest_1041, AddNextFilters_PartiallyOverlapping_AddedCorrectly_1041) {

    std::vector<StringRef> filters1 = createStringRefs({"filter1", "filter2"});

    tracker.addNextFilters(filters1);



    std::vector<StringRef> filters2 = createStringRefs({"filter2", "filter3"});

    tracker.addNextFilters(filters2);



    EXPECT_EQ(tracker.getFilters().size(), 4);

    EXPECT_EQ(tracker.getFilters()[0], "filter1");

    EXPECT_EQ(tracker.getFilters()[1], "filter2");

    EXPECT_EQ(tracker.getFilters()[2], "filter2");

    EXPECT_EQ(tracker.getFilters()[3], "filter3");

}



TEST_F(SectionTrackerTest_1041, AddNextFilters_BoundaryCondition_EmptyAfterSingleAddition_1041) {

    std::vector<StringRef> filters = createStringRefs({});

    tracker.addNextFilters(createStringRefs({"initial"}));

    tracker.addNextFilters(filters);



    EXPECT_EQ(tracker.getFilters().size(), 1);

    EXPECT_EQ(tracker.getFilters()[0], "initial");

}
