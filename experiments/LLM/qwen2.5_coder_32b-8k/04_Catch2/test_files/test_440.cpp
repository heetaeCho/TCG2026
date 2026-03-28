#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch;

using namespace TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const));

    MOCK_METHOD(void, close, (), ());

    MOCK_METHOD(void, fail, (), ());

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), ());

    MOCK_METHOD(void, addChild, (ITrackerPtr&&), ());

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef&), (const));

    MOCK_METHOD(void, openChild, (), ());

    MOCK_METHOD(bool, isSectionTracker, (), (const));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const));

    MOCK_METHOD(bool, isOpen, (), (const));

    MOCK_METHOD(bool, hasStarted, (), (const));

    MOCK_METHOD(ITracker*, parent, (), (const));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const));

    MOCK_METHOD(bool, hasChildren, (), (const));



    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent)

        : ITracker(std::move(nameAndLoc), parent) {}

};



class ITrackerTest_440 : public ::testing::Test {

protected:

    NameAndLocation nameAndLoc{"test_case", "file.cpp", 10};

    MockITracker tracker{nameAndLoc, nullptr};

};



TEST_F(ITrackerTest_440, NameAndLocation_ReturnsCorrectValue_440) {

    EXPECT_EQ(tracker.nameAndLocation().name, "test_case");

    EXPECT_EQ(tracker.nameAndLocation().filename, "file.cpp");

    EXPECT_EQ(tracker.nameAndLocation().lineNumber, 10);

}



TEST_F(ITrackerTest_440, IsComplete_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, isComplete()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isComplete());

}



TEST_F(ITrackerTest_440, Close_DoesNotThrow_440) {

    EXPECT_CALL(tracker, close());

    tracker.close();

}



TEST_F(ITrackerTest_440, Fail_DoesNotThrow_440) {

    EXPECT_CALL(tracker, fail());

    tracker.fail();

}



TEST_F(ITrackerTest_440, MarkAsNeedingAnotherRun_DoesNotThrow_440) {

    EXPECT_CALL(tracker, markAsNeedingAnotherRun());

    tracker.markAsNeedingAnotherRun();

}



TEST_F(ITrackerTest_440, AddChild_DoesNotThrow_440) {

    MockITracker child{NameAndLocation{"child_case", "file.cpp", 20}, &tracker};

    EXPECT_CALL(tracker, addChild(::testing::_));

    tracker.addChild(std::make_unique<MockITracker>(std::move(child)));

}



TEST_F(ITrackerTest_440, FindChild_ReturnsNullptrByDefault_440) {

    NameAndLocationRef childNameAndLoc{"child_case", "file.cpp", 20};

    EXPECT_CALL(tracker, findChild(::testing::_)).WillOnce(::testing::Return(nullptr));

    EXPECT_EQ(tracker.findChild(childNameAndLoc), nullptr);

}



TEST_F(ITrackerTest_440, OpenChild_DoesNotThrow_440) {

    EXPECT_CALL(tracker, openChild());

    tracker.openChild();

}



TEST_F(ITrackerTest_440, IsSectionTracker_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, isSectionTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isSectionTracker());

}



TEST_F(ITrackerTest_440, IsGeneratorTracker_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, isGeneratorTracker()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isGeneratorTracker());

}



TEST_F(ITrackerTest_440, IsOpen_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, isOpen()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isOpen());

}



TEST_F(ITrackerTest_440, HasStarted_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, hasStarted()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.hasStarted());

}



TEST_F(ITrackerTest_440, Parent_ReturnsNullptrByDefault_440) {

    EXPECT_EQ(tracker.parent(), nullptr);

}



TEST_F(ITrackerTest_440, IsSuccessfullyCompleted_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, isSuccessfullyCompleted()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.isSuccessfullyCompleted());

}



TEST_F(ITrackerTest_440, HasChildren_ReturnsFalseByDefault_440) {

    EXPECT_CALL(tracker, hasChildren()).WillOnce(::testing::Return(false));

    EXPECT_FALSE(tracker.hasChildren());

}
