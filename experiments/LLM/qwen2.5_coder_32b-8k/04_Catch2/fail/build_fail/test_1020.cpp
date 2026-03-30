#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class ITrackerMock : public ITracker {

public:

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(bool, isComplete, (), (const, override));

    MOCK_METHOD(bool, isOpen, (), (const));

    MOCK_METHOD(bool, hasStarted, (), (const));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr&& child), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

    MOCK_CONST_METHOD0(nameAndLocation, NameAndLocation&());

    MOCK_CONST_METHOD0(parent, ITracker*());

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const));

    MOCK_METHOD(bool, hasChildren, (), (const));



    ITrackerMock(NameAndLocation&& nameAndLoc, ITracker* parent)

        : ITracker(std::move(nameAndLoc), parent) {}

};



class ITrackerTest : public ::testing::Test {

protected:

    NameAndLocation nameAndLocation;

    ITrackerMock tracker;



    ITrackerTest() : nameAndLocation("test_name", "file.cpp:1"), tracker(std::move(nameAndLocation), nullptr) {}



    ~ITrackerTest() override = default;

};



TEST_F(ITrackerTest, MarkAsNeedingAnotherRun_SetsStateCorrectly_1020) {

    EXPECT_CALL(tracker, markAsNeedingAnotherRun()).Times(1);

    tracker.markAsNeedingAnotherRun();

}



TEST_F(ITrackerTest, IsComplete_ReturnsFalseInitially_1020) {

    EXPECT_FALSE(tracker.isComplete());

}



TEST_F(ITrackerTest, IsOpen_ReturnsTrueInitially_1020) {

    EXPECT_TRUE(tracker.isOpen());

}



TEST_F(ITrackerTest, HasStarted_ReturnsFalseInitially_1020) {

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest, AddChild_DoesNotThrow_1020) {

    auto child = std::make_unique<ITrackerMock>(NameAndLocation("child_test", "file.cpp:2"), &tracker);

    EXPECT_NO_THROW(tracker.addChild(std::move(child)));

}



TEST_F(ITrackerTest, FindChild_ReturnsNullptrWhenNotFound_1020) {

    NameAndLocationRef childNameAndLocation("nonexistent_child", "file.cpp:3");

    EXPECT_EQ(tracker.findChild(childNameAndLocation), nullptr);

}



TEST_F(ITrackerTest, IsSectionTracker_ReturnsFalseByDefault_1020) {

    EXPECT_FALSE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest, IsGeneratorTracker_ReturnsFalseByDefault_1020) {

    EXPECT_FALSE(tracker.isGeneratorTracker());

}



TEST_F(ITrackerTest, NameAndLocation_ReturnsCorrectNameAndLocation_1020) {

    EXPECT_EQ(tracker.nameAndLocation().name(), "test_name");

    EXPECT_EQ(tracker.nameAndLocation().location(), "file.cpp:1");

}



TEST_F(ITrackerTest, Parent_ReturnsParentPointer_1020) {

    ITrackerMock parent(NameAndLocation("parent_test", "file.cpp:4"), nullptr);

    ITrackerMock child(NameAndLocation("child_test", "file.cpp:5"), &parent);



    EXPECT_EQ(child.parent(), &parent);

}



TEST_F(ITrackerTest, IsSuccessfullyCompleted_ReturnsFalseInitially_1020) {

    EXPECT_FALSE(tracker.isSuccessfullyCompleted());

}



TEST_F(ITrackerTest, HasChildren_ReturnsFalseInitially_1020) {

    EXPECT_FALSE(tracker.hasChildren());

}
