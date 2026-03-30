#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr&& child), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(const bool, isComplete, (), (const, override));

    MOCK_METHOD(const bool, isOpen, (), (const, override));

    MOCK_METHOD(const bool, hasStarted, (), (const, override));

    MOCK_METHOD(bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

    MOCK_METHOD(NameAndLocation const&, nameAndLocation, (), (const, override));

    MOCK_METHOD(ITracker*, parent, (), (const, override));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const, override));

    MOCK_METHOD(bool, hasChildren, (), (const, override));



    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent = nullptr) : ITracker(std::move(nameAndLoc), parent) {}

};



class ITrackerTest : public ::testing::Test {

protected:

    NameAndLocation loc{"test_case", "file.cpp", 1};

    std::unique_ptr<MockITracker> tracker;

    

    void SetUp() override {

        tracker = std::make_unique<MockITracker>(std::move(loc));

    }

};



TEST_F(ITrackerTest_1027, OpenChildSetsStateToExecutingChildren_1027) {

    EXPECT_CALL(*tracker.get(), hasStarted()).WillOnce(::testing::Return(true));

    tracker->openChild();

    EXPECT_EQ(tracker->m_runState, ExecutingChildren);

}



TEST_F(ITrackerTest_1027, OpenChildCallsParentOpenChildIfNotExecutingChildren_1027) {

    MockITracker parentTracker(NameAndLocation{"parent_case", "file.cpp", 2});

    tracker = std::make_unique<MockITracker>(std::move(loc), &parentTracker);

    

    EXPECT_CALL(*tracker.get(), hasStarted()).WillOnce(::testing::Return(true));

    EXPECT_CALL(parentTracker, openChild());

    

    tracker->openChild();

}



TEST_F(ITrackerTest_1027, OpenChildDoesNotCallParentIfAlreadyExecutingChildren_1027) {

    MockITracker parentTracker(NameAndLocation{"parent_case", "file.cpp", 2});

    tracker = std::make_unique<MockITracker>(std::move(loc), &parentTracker);

    

    tracker->m_runState = ExecutingChildren;

    EXPECT_CALL(parentTracker, openChild()).Times(0);

    

    tracker->openChild();

}



TEST_F(ITrackerTest_1027, OpenChildDoesNothingIfNotStarted_1027) {

    EXPECT_CALL(*tracker.get(), hasStarted()).WillOnce(::testing::Return(false));

    EXPECT_CALL(*tracker.get(), parent()).Times(0);

    

    tracker->openChild();

}



TEST_F(ITrackerTest_1027, IsOpenReturnsTrueWhenExecutingChildren_1027) {

    tracker->m_runState = ExecutingChildren;

    EXPECT_TRUE(tracker->isOpen());

}



TEST_F(ITrackerTest_1027, IsOpenReturnsFalseOtherwise_1027) {

    tracker->m_runState = NotStarted;

    EXPECT_FALSE(tracker->isOpen());

}



TEST_F(ITrackerTest_1027, HasStartedReturnsTrueWhenExecutingChildren_1027) {

    tracker->m_runState = ExecutingChildren;

    EXPECT_TRUE(tracker->hasStarted());

}



TEST_F(ITrackerTest_1027, HasStartedReturnsFalseOtherwise_1027) {

    tracker->m_runState = NotStarted;

    EXPECT_FALSE(tracker->hasStarted());

}
