#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/internal/catch_test_case_tracker.hpp"



using namespace Catch;

using namespace Generators;



class RunContextTest_498 : public ::testing::Test {

protected:

    MockIGeneratorTracker* mockGenerator = new MockIGeneratorTracker();

    GeneratorBasePtr generatorMock = std::unique_ptr<IGenerator>(mockGenerator);

    SourceLineInfo lineInfo{"test_file.cpp", 10};

    StringRef generatorName{"generator_name"};

    TrackerContext trackerContext;

    RunContext runContext{nullptr, nullptr};



    void SetUp() override {

        // Setting up the necessary context

        trackerContext.startRun();

        auto& currentTracker = trackerContext.currentTracker();

        currentTracker.addChild(Catch::Detail::make_unique<TrackerBase>(TestCaseTracking::NameAndLocation{"parent_tracker", lineInfo}, trackerContext, &currentTracker));

        trackerContext.setCurrentTracker(currentTracker.findChild(TestCaseTracking::NameAndLocationRef{"parent_tracker", lineInfo}));

    }

};



TEST_F(RunContextTest_498, CreateGeneratorTracker_ReturnsNonNullPointer_498) {

    auto result = runContext.createGeneratorTracker(generatorName, lineInfo, std::move(generatorMock));

    EXPECT_NE(result, nullptr);

}



TEST_F(RunContextTest_498, CreateGeneratorTracker_SetsGeneratorCorrectly_498) {

    auto tracker = runContext.createGeneratorTracker(generatorName, lineInfo, std::move(generatorMock));

    EXPECT_EQ(tracker->getGenerator().get(), mockGenerator);

}



TEST_F(RunContextTest_498, CreateGeneratorTracker_AddsChildToCurrentTracker_498) {

    auto initialCount = trackerContext.currentTracker().hasChildren();

    runContext.createGeneratorTracker(generatorName, lineInfo, std::move(generatorMock));

    EXPECT_TRUE(trackerContext.currentTracker().hasChildren());

}



TEST_F(RunContextTest_498, CreateGeneratorTracker_SetsTrackerOpen_498) {

    auto tracker = runContext.createGeneratorTracker(generatorName, lineInfo, std::move(generatorMock));

    EXPECT_TRUE(tracker->isOpen());

}



TEST_F(RunContextTest_498, CreateGeneratorTracker_ThrowsOnDuplicateGeneratorName_498) {

    runContext.createGeneratorTracker(generatorName, lineInfo, std::move(generatorMock));

    generatorMock = Catch::Detail::make_unique<MockIGeneratorTracker>();

    EXPECT_THROW(runContext.createGeneratorTracker(generatorName, lineInfo, std::move(generatorMock)), std::runtime_error);

}
