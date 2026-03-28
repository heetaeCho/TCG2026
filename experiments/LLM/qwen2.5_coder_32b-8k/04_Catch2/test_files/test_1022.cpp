#include <gtest/gtest.h>

#include "catch_test_case_tracker.hpp"



using namespace Catch;

using namespace TestCaseTracking;



class ITrackerTest_1022 : public ::testing::Test {

protected:

    SourceLineInfo location = {"test_file.cpp", 42};

    NameAndLocation nameAndLoc = {"TestName", location};

    ITracker tracker = ITracker(std::move(nameAndLoc), nullptr);



    std::unique_ptr<ITracker> createChildTracker() {

        return std::make_unique<ITracker>(NameAndLocation{"ChildTestName", location}, &tracker);

    }

};



TEST_F(ITrackerTest_1022, FindChild_ReturnsNullptrWhenNoChildren_1022) {

    NameAndLocationRef childRef = {"NonExistentChild", location};

    EXPECT_EQ(tracker.findChild(childRef), nullptr);

}



TEST_F(ITrackerTest_1022, FindChild_ReturnsCorrectChild_1022) {

    auto childTracker = createChildTracker();

    tracker.addChild(std::move(childTracker));



    NameAndLocationRef childRef = {"ChildTestName", location};

    EXPECT_NE(tracker.findChild(childRef), nullptr);

}



TEST_F(ITrackerTest_1022, FindChild_ReturnsNullptrForDifferentLine_1022) {

    auto childTracker = createChildTracker();

    tracker.addChild(std::move(childTracker));



    SourceLineInfo differentLocation = {"test_file.cpp", 43};

    NameAndLocationRef childRef = {"ChildTestName", differentLocation};

    EXPECT_EQ(tracker.findChild(childRef), nullptr);

}



TEST_F(ITrackerTest_1022, AddChild_IncreasesChildrenCount_1022) {

    size_t initialSize = tracker.hasChildren() ? tracker.m_children.size() : 0;

    auto childTracker = createChildTracker();

    tracker.addChild(std::move(childTracker));

    EXPECT_EQ(tracker.m_children.size(), initialSize + 1);

}



TEST_F(ITrackerTest_1022, OpenChild_CallsOpenOnNewChild_1022) {

    // This test assumes that openChild creates and adds a new child

    // We cannot verify internal state changes, so we rely on observable behavior

    size_t initialSize = tracker.hasChildren() ? tracker.m_children.size() : 0;

    tracker.openChild();

    EXPECT_EQ(tracker.m_children.size(), initialSize + 1);

}



TEST_F(ITrackerTest_1022, IsComplete_ReturnsFalseInitially_1022) {

    EXPECT_FALSE(tracker.isComplete());

}



TEST_F(ITrackerTest_1022, HasStarted_ReturnsFalseInitially_1022) {

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest_1022, IsOpen_ReturnsTrueAfterOpeningChild_1022) {

    tracker.openChild();

    EXPECT_TRUE(tracker.isOpen());

}
