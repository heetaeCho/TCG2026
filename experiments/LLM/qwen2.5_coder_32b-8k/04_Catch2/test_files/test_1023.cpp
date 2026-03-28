#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const));

    MOCK_METHOD(bool, isOpen, (), (const));

    MOCK_METHOD(bool, hasStarted, (), (const));

    MOCK_METHOD(void, close, (), ());

    MOCK_METHOD(void, fail, (), ());

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), ());

    MOCK_METHOD(void, addChild, (ITrackerPtr&&), ());

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef&), ());

    MOCK_METHOD(void, openChild, (), ());

    MOCK_METHOD(bool, isSectionTracker, (), (const));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const));

    MOCK_METHOD(NameAndLocation const&, nameAndLocation, (), (const));

    MOCK_METHOD(ITracker*, parent, (), (const));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const));

    MOCK_METHOD(bool, hasChildren, (), (const));



    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent) 

        : ITracker(std::move(nameAndLoc), parent) {}

};



class ITrackerTest_1023 : public ::testing::Test {

protected:

    NameAndLocation nameAndLocationMock;

    MockITracker tracker{std::move(nameAndLocationMock), nullptr};

};



TEST_F(ITrackerTest_1023, IsSectionTracker_ReturnsFalse_1023) {

    EXPECT_CALL(tracker, isSectionTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest_1023, IsGeneratorTracker_ReturnsFalse_1023) {

    EXPECT_CALL(tracker, isGeneratorTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isGeneratorTracker());

}



TEST_F(ITrackerTest_1023, NameAndLocation_ReturnsNameAndLocationRef_1023) {

    EXPECT_CALL(tracker, nameAndLocation()).Times(1);

    tracker.nameAndLocation();

}



TEST_F(ITrackerTest_1023, Parent_ReturnsParentPointer_1023) {

    EXPECT_CALL(tracker, parent()).Times(1);

    tracker.parent();

}



TEST_F(ITrackerTest_1023, MarkAsNeedingAnotherRun_DoesNotThrow_1023) {

    EXPECT_NO_THROW(tracker.markAsNeedingAnotherRun());

}



TEST_F(ITrackerTest_1023, AddChild_AddsChildSuccessfully_1023) {

    MockITracker mockChild{nameAndLocationMock, &tracker};

    EXPECT_CALL(tracker, addChild(::testing::_)).Times(1);

    tracker.addChild(std::make_unique<MockITracker>(nameAndLocationMock, &tracker));

}



TEST_F(ITrackerTest_1023, FindChild_ReturnsNullptrForNonexistentChild_1023) {

    NameAndLocationRef childNameAndLocation;

    EXPECT_CALL(tracker, findChild(childNameAndLocation)).WillOnce(::testing::Return(nullptr));

    EXPECT_EQ(tracker.findChild(childNameAndLocation), nullptr);

}



TEST_F(ITrackerTest_1023, OpenChild_DoesNotThrow_1023) {

    EXPECT_NO_THROW(tracker.openChild());

}
