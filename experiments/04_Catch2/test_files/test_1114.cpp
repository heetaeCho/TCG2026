#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch;

using namespace TestCaseTracking;



class MockTracker : public ITracker {

public:

    MOCK_METHOD(bool, isComplete, (), (const override));

    MOCK_METHOD(bool, isOpen, (), (const override));

    MOCK_METHOD(bool, hasStarted, (), (const override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(void, fail, (), (override));

    MOCK_METHOD(void, markAsNeedingAnotherRun, (), (override));

    MOCK_METHOD(void, addChild, (ITrackerPtr && child), (override));

    MOCK_METHOD(ITracker *, findChild, (const NameAndLocationRef & nameAndLocation), (override));

    MOCK_METHOD(void, openChild, (), (override));

    MOCK_METHOD(bool, isSectionTracker, (), (const override));

    MOCK_METHOD(bool, isGeneratorTracker, (), (const override));

    MOCK_METHOD(NameAndLocation const&, nameAndLocation, (), (const override));

    MOCK_METHOD(ITracker*, parent, (), (const override));

    MOCK_METHOD(bool, isSuccessfullyCompleted, (), (const override));

    MOCK_METHOD(bool, hasChildren, (), (const override));

};



class SectionTrackerTest_1114 : public ::testing::Test {

protected:

    NameAndLocation nameAndLocation;

    TrackerContext context;

    MockTracker* parentMock;



    void SetUp() override {

        nameAndLocation = NameAndLocation("testSection", SourceLineInfo(__FILE__, __LINE__));

        parentMock = new MockTracker();

        tracker = std::make_unique<SectionTracker>(CATCH_MOVE(nameAndLocation), context, parentMock);

    }



    void TearDown() override {

        delete parentMock;

    }



    std::unique_ptr<SectionTracker> tracker;

};



TEST_F(SectionTrackerTest_1114, ConstructorInitializesParentAndNameAndLocation_1114) {

    EXPECT_EQ(tracker->nameAndLocation().name, "testSection");

    EXPECT_EQ(tracker->parent(), parentMock);

}



TEST_F(SectionTrackerTest_1114, IsSectionTrackerReturnsTrue_1114) {

    EXPECT_TRUE(tracker->isSectionTracker());

}



TEST_F(SectionTrackerTest_1114, AddInitialFiltersSetsFilters_1114) {

    std::vector<std::string> filters = {"filter1", "filter2"};

    tracker->addInitialFilters(filters);

    auto actualFilters = tracker->getFilters();

    EXPECT_EQ(actualFilters.size(), 2);

    EXPECT_EQ(actualFilters[0], "filter1");

    EXPECT_EQ(actualFilters[1], "filter2");

}



TEST_F(SectionTrackerTest_1114, AddNextFiltersAppendsFilters_1114) {

    std::vector<StringRef> initialFilters = {"filter1"};

    tracker->addInitialFilters({"filter1"});

    tracker->addNextFilters(initialFilters);

    auto actualFilters = tracker->getFilters();

    EXPECT_EQ(actualFilters.size(), 2);

    EXPECT_EQ(actualFilters[0], "filter1");

    EXPECT_EQ(actualFilters[1], "filter1");

}



TEST_F(SectionTrackerTest_1114, TrimmedNameReturnsTrimmedName_1114) {

    std::string expected = tracker->nameAndLocation().name;

    auto trimmed = tracker->trimmedName();

    EXPECT_EQ(trimmed, expected);

}



TEST_F(SectionTrackerTest_1114, TryOpenCallsParentIfNotSectionTracker_1114) {

    ON_CALL(*parentMock, isSectionTracker()).WillByDefault(::testing::Return(false));

    EXPECT_CALL(*parentMock, openChild());

    tracker->tryOpen();

}
