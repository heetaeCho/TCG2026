#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_CONST_METHOD0(isComplete, bool());

    MOCK_CONST_METHOD0(isOpen, bool());

    MOCK_CONST_METHOD0(hasStarted, bool());

    MOCK_METHOD0(close, void());

    MOCK_METHOD0(fail, void());

    MOCK_METHOD0(markAsNeedingAnotherRun, void());

    MOCK_METHOD1(addChild, void(ITrackerPtr&&));

    MOCK_METHOD1(findChild, ITracker*(const NameAndLocationRef&));

    MOCK_METHOD0(openChild, void());

    MOCK_CONST_METHOD0(isSectionTracker, bool());

    MOCK_CONST_METHOD0(isGeneratorTracker, bool());

    MOCK_CONST_METHOD0(nameAndLocation, NameAndLocation const&());

    MOCK_CONST_METHOD0(parent, ITracker*());

    MOCK_CONST_METHOD0(hasChildren, bool());



    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent)

        : ITracker(std::move(nameAndLoc), parent) {}

};



class TrackerTest_442 : public ::testing::Test {

protected:

    MockITracker tracker{NameAndLocation("test", "file.cpp"), nullptr};

};



TEST_F(TrackerTest_442, IsSuccessfullyCompleted_ReturnsTrueWhenStateIsCompletedSuccessfully_442) {

    tracker.m_runState = CycleState::CompletedSuccessfully;

    EXPECT_TRUE(tracker.isSuccessfullyCompleted());

}



TEST_F(TrackerTest_442, IsSuccessfullyCompleted_ReturnsFalseWhenStateIsNotCompletedSuccessfully_442) {

    tracker.m_runState = CycleState::Failed;

    EXPECT_FALSE(tracker.isSuccessfullyCompleted());

}



TEST_F(TrackerTest_442, IsComplete_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, isComplete()).Times(1);

    tracker.isComplete();

}



TEST_F(TrackerTest_442, IsOpen_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, isOpen()).Times(1);

    tracker.isOpen();

}



TEST_F(TrackerTest_442, HasStarted_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, hasStarted()).Times(1);

    tracker.hasStarted();

}



TEST_F(TrackerTest_442, Close_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, close()).Times(1);

    tracker.close();

}



TEST_F(TrackerTest_442, Fail_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, fail()).Times(1);

    tracker.fail();

}



TEST_F(TrackerTest_442, MarkAsNeedingAnotherRun_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, markAsNeedingAnotherRun()).Times(1);

    tracker.markAsNeedingAnotherRun();

}



TEST_F(TrackerTest_442, AddChild_CallsVirtualMethod_442) {

    ITrackerPtr child = nullptr;

    EXPECT_CALL(tracker, addChild(::testing::_)).Times(1);

    tracker.addChild(std::move(child));

}



TEST_F(TrackerTest_442, FindChild_CallsVirtualMethod_442) {

    NameAndLocationRef nameAndLocation;

    EXPECT_CALL(tracker, findChild(nameAndLocation)).Times(1);

    tracker.findChild(nameAndLocation);

}



TEST_F(TrackerTest_442, OpenChild_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, openChild()).Times(1);

    tracker.openChild();

}



TEST_F(TrackerTest_442, IsSectionTracker_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, isSectionTracker()).Times(1);

    tracker.isSectionTracker();

}



TEST_F(TrackerTest_442, IsGeneratorTracker_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, isGeneratorTracker()).Times(1);

    tracker.isGeneratorTracker();

}



TEST_F(TrackerTest_442, NameAndLocation_ReturnsReferenceToNameAndLocation_442) {

    const auto& result = tracker.nameAndLocation();

    EXPECT_EQ(result, tracker.m_nameAndLocation);

}



TEST_F(TrackerTest_442, Parent_ReturnsParentPointer_442) {

    EXPECT_EQ(tracker.parent(), nullptr);

}



TEST_F(TrackerTest_442, HasChildren_CallsVirtualMethod_442) {

    EXPECT_CALL(tracker, hasChildren()).Times(1);

    tracker.hasChildren();

}
