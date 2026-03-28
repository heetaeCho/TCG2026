#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



namespace Catch {

    namespace TestCaseTracking {



        class SectionTrackerTest_1042 : public ::testing::Test {

        protected:

            NameAndLocationRef nameAndLocation;

            TrackerContext ctx;

            ITracker* parent = nullptr;

            SectionTracker tracker;



            SectionTrackerTest_1042() : tracker(NameAndLocation("", ""), ctx, parent) {}

        };



        TEST_F(SectionTrackerTest_1042, TrimmedName_ReturnsTrimmedName_1042) {

            // Arrange

            std::string expected = "trimmed_name";

            nameAndLocation.name = "  trimmed_name   ";



            // Act

            SectionTracker tracker(NameAndLocation(nameAndLocation), ctx, parent);

            StringRef result = tracker.trimmedName();



            // Assert

            EXPECT_EQ(result, expected);

        }



        TEST_F(SectionTrackerTest_1042, AddInitialFilters_AddsFiltersToVector_1042) {

            // Arrange

            std::vector<std::string> filters = {"filter1", "filter2"};



            // Act

            tracker.addInitialFilters(filters);



            // Assert

            EXPECT_EQ(tracker.getFilters().size(), 2);

            EXPECT_EQ(tracker.getFilters()[0], "filter1");

            EXPECT_EQ(tracker.getFilters()[1], "filter2");

        }



        TEST_F(SectionTrackerTest_1042, AddNextFilters_AddsFiltersToVector_1042) {

            // Arrange

            std::vector<StringRef> filters = {"filter3", "filter4"};



            // Act

            tracker.addNextFilters(filters);



            // Assert

            EXPECT_EQ(tracker.getFilters().size(), 2);

            EXPECT_EQ(tracker.getFilters()[0], "filter3");

            EXPECT_EQ(tracker.getFilters()[1], "filter4");

        }



        TEST_F(SectionTrackerTest_1042, IsComplete_ReturnsFalseByDefault_1042) {

            // Act

            bool result = tracker.isComplete();



            // Assert

            EXPECT_FALSE(result);

        }



        TEST_F(SectionTrackerTest_1042, IsSectionTracker_ReturnsTrue_1042) {

            // Act

            bool result = tracker.isSectionTracker();



            // Assert

            EXPECT_TRUE(result);

        }



    }

}
