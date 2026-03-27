#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "real_command_runner.cc"

#include "jobserver.h"

#include "graph.h"



using namespace ::testing;



class MockJobserverClient : public Jobserver::Client {

public:

    MOCK_METHOD(Jobserver::Slot, TryAcquire, (), (override));

    MOCK_METHOD(void, Release, (Jobserver::Slot), (override));

};



class RealCommandRunnerTest_94 : public ::testing::Test {

protected:

    BuildConfig config_;

    std::unique_ptr<MockJobserverClient> jobserver_mock_;

    RealCommandRunner runner_;



    RealCommandRunnerTest_94()

        : jobserver_mock_(new MockJobserverClient()),

          runner_(config_, jobserver_mock_.get()) {}



    void SetUp() override {

        // Additional setup if needed

    }



    void TearDown() override {

        // Cleanup if necessary

    }

};



TEST_F(RealCommandRunnerTest_94, ClearJobTokens_NoActiveEdges_94) {

    EXPECT_CALL(*jobserver_mock_, Release(_)).Times(0);

    runner_.ClearJobTokens();

}



TEST_F(RealCommandRunnerTest_94, ClearJobTokens_OneActiveEdge_94) {

    Edge edge;

    Jobserver::Slot slot;

    ON_CALL(*jobserver_mock_, TryAcquire()).WillByDefault(Return(slot));

    EXPECT_CALL(*jobserver_mock_, Release(slot)).Times(1);

    

    runner_.subproc_to_edge_[nullptr] = &edge;  // Simulating one active edge

    runner_.ClearJobTokens();

}



TEST_F(RealCommandRunnerTest_94, ClearJobTokens_MultipleActiveEdges_94) {

    Edge edge1, edge2;

    Jobserver::Slot slot1, slot2;

    ON_CALL(*jobserver_mock_, TryAcquire()).WillByDefault(Return(slot1));

    EXPECT_CALL(*jobserver_mock_, Release(slot1)).Times(1);

    

    ON_CALL(*jobserver_mock_, TryAcquire()).WillByDefault(Return(slot2));

    EXPECT_CALL(*jobserver_mock_, Release(slot2)).Times(1);



    runner_.subproc_to_edge_[nullptr] = &edge1;  // Simulating first active edge

    runner_.subproc_to_edge_[nullptr] = &edge2;  // Simulating second active edge

    runner_.ClearJobTokens();

}



TEST_F(RealCommandRunnerTest_94, ClearJobTokens_JobserverNull_94) {

    runner_.jobserver_ = nullptr;

    EXPECT_NO_THROW(runner_.ClearJobTokens());

}
