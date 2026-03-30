#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch_amalgamated.cpp"



using namespace Catch::TestCaseTracking;



class MockITracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const, override));

    MOCK_METHOD(bool, isOpen, (), (const, override));

    MOCK_METHOD(bool, hasStarted, (), (const, override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr&&), (override));

    MOCK_METHOD(ITracker*, findChild, (const NameAndLocationRef&), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const, override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

    MOCK_METHOD(NameAndLocation const&, nameAndLocation, (), (const, override));

    MOCK_METHOD(ITracker*, parent, (), (const, override));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const, override));

    MOCK_METHOD(bool, hasChildren, (), (const, override));



    MockITracker(NameAndLocation&& nameAndLoc, ITracker* parent)

        : ITracker(std::move(nameAndLoc), parent) {}

};



class ITrackerTest_1024 : public ::testing::Test {

protected:

    NameAndLocation nameAndLoc{"test_name", "file.cpp", 0};

    MockITracker tracker{nameAndLoc, nullptr};

};



TEST_F(ITrackerTest_1024, IsGeneratorTracker_ReturnsFalse_1024) {

    EXPECT_EQ(tracker.isGeneratorTracker(), false);

}



TEST_F(ITrackerTest_1024, IsComplete_NormalOperation_1024) {

    EXPECT_CALL(tracker, isComplete()).WillOnce(::testing::Return(false));

    EXPECT_EQ(tracker.isComplete(), false);

}



TEST_F(ITrackerTest_1024, IsOpen_NormalOperation_1024) {

    EXPECT_CALL(tracker, isOpen()).WillOnce(::testing::Return(true));

    EXPECT_EQ(tracker.isOpen(), true);

}



TEST_F(ITrackerTest_1024, HasStarted_NormalOperation_1024) {

    EXPECT_CALL(tracker, hasStarted()).WillOnce(::testing::Return(false));

    EXPECT_EQ(tracker.hasStarted(), false);

}



TEST_F(ITrackerTest_1024, Close_NormalOperation_1024) {

    EXPECT_CALL(tracker, close());

    tracker.close();

}



TEST_F(ITrackerTest_1024, Fail_NormalOperation_1024) {

    EXPECT_CALL(tracker, fail());

    tracker.fail();

}



TEST_F(ITrackerTest_1024, MarkAsNeedingAnotherRun_NormalOperation_1024) {

    EXPECT_CALL(tracker, markAsNeedingAnotherRun());

    tracker.markAsNeedingAnotherRun();

}



TEST_F(ITrackerTest_1024, AddChild_NormalOperation_1024) {

    auto child = std::make_unique<MockITracker>(nameAndLoc, &tracker);

    EXPECT_CALL(tracker, addChild(::testing::_));

    tracker.addChild(std::move(child));

}



TEST_F(ITrackerTest_1024, FindChild_NormalOperation_1024) {

    NameAndLocationRef nameAndLocRef{"test_name", "file.cpp", 0};

    EXPECT_CALL(tracker, findChild(nameAndLocRef)).WillOnce(::testing::Return(nullptr));

    EXPECT_EQ(tracker.findChild(nameAndLocRef), nullptr);

}



TEST_F(ITrackerTest_1024, OpenChild_NormalOperation_1024) {

    EXPECT_CALL(tracker, openChild());

    tracker.openChild();

}



TEST_F(ITrackerTest_1024, IsSectionTracker_NormalOperation_1024) {

    EXPECT_CALL(tracker, isSectionTracker()).WillOnce(::testing::Return(false));

    EXPECT_EQ(tracker.isSectionTracker(), false);

}



TEST_F(ITrackerTest_1024, NameAndLocation_NormalOperation_1024) {

    EXPECT_CALL(tracker, nameAndLocation()).WillOnce(::testing::ReturnRef(nameAndLoc));

    EXPECT_EQ(&tracker.nameAndLocation(), &nameAndLoc);

}



TEST_F(ITrackerTest_1024, Parent_NormalOperation_1024) {

    EXPECT_CALL(tracker, parent()).WillOnce(::testing::Return(nullptr));

    EXPECT_EQ(tracker.parent(), nullptr);

}



TEST_F(ITrackerTest_1024, IsSuccessfullyCompleted_NormalOperation_1024) {

    EXPECT_CALL(tracker, isSuccessfullyCompleted()).WillOnce(::testing::Return(true));

    EXPECT_EQ(tracker.isSuccessfullyCompleted(), true);

}



TEST_F(ITrackerTest_1024, HasChildren_NormalOperation_1024) {

    EXPECT_CALL(tracker, hasChildren()).WillOnce(::testing::Return(false));

    EXPECT_EQ(tracker.hasChildren(), false);

}
