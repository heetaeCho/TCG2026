#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "catch2/internal/catch_run_context.hpp"

#include "catch2/internal/catch_generator_tracker.hpp"



using namespace Catch;

using namespace Generators;



class MockIGeneratorTracker : public IGeneratorTracker {

public:

    MOCK_METHOD(bool, isGeneratorTracker, (), (const, override));

    MOCK_METHOD(bool, hasGenerator, (), (const, override));

    MOCK_METHOD(void, close, (), (override));

    MOCK_METHOD(GeneratorBasePtr const&, getGenerator, (), (const, override));

    MOCK_METHOD(void, setGenerator, (GeneratorBasePtr&& generator), (override));

};



class RunContextTest_497 : public ::testing::Test {

protected:

    SourceLineInfo lineInfo = {"test_file.cpp", 10};

    StringRef generatorName = "test_generator";

    MockIGeneratorTracker* mockTracker;

    IGeneratorTracker* realTracker;



    void SetUp() override {

        mockTracker = new MockIGeneratorTracker();

        realTracker = GeneratorTracker::acquire(m_trackerContext, TestCaseTracking::NameAndLocationRef(generatorName, lineInfo));

    }



    void TearDown() override {

        delete mockTracker;

        delete realTracker;

    }



    TrackerContext m_trackerContext;

};



TEST_F(RunContextTest_497, AcquireGeneratorTracker_ReturnsNonNullPointer_497) {

    RunContext context(nullptr, nullptr);

    IGeneratorTracker* tracker = context.acquireGeneratorTracker(generatorName, lineInfo);

    EXPECT_NE(tracker, nullptr);

}



TEST_F(RunContextTest_497, AcquireGeneratorTracker_SetsLineInfoCorrectly_497) {

    RunContext context(nullptr, nullptr);

    context.acquireGeneratorTracker(generatorName, lineInfo);

    EXPECT_EQ(context.m_lastAssertionInfo.lineInfo.file, lineInfo.file);

    EXPECT_EQ(context.m_lastAssertionInfo.lineInfo.line, lineInfo.line);

}



TEST_F(RunContextTest_497, AcquireGeneratorTracker_DoesNotThrowExceptionForValidInput_497) {

    RunContext context(nullptr, nullptr);

    EXPECT_NO_THROW(context.acquireGeneratorTracker(generatorName, lineInfo));

}
