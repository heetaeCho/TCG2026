#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build.h"



using namespace testing;



class BuilderTest_92 : public Test {

protected:

    State state;

    BuildConfig config;

    BuildLog build_log;

    DepsLog deps_log;

    DiskInterface disk_interface;

    Status status;

    int64_t start_time_millis = 0;

    std::unique_ptr<Builder> builder;



    void SetUp() override {

        builder = std::make_unique<Builder>(&state, config, &build_log, &deps_log, &disk_interface, &status, start_time_millis);

    }

};



TEST_F(BuilderTest_92, AddTargetByName_ReturnsNodePtr_92) {

    std::string err;

    Node* node = builder->AddTarget("test_target", &err);

    EXPECT_NE(node, nullptr);

}



TEST_F(BuilderTest_92, AddTargetByNode_ReturnsTrueForValidNode_92) {

    Node target_node;

    std::string err;

    bool result = builder->AddTarget(&target_node, &err);

    EXPECT_TRUE(result);

}



TEST_F(BuilderTest_92, AlreadyUpToDate_ReturnsFalseInitially_92) {

    EXPECT_FALSE(builder->AlreadyUpToDate());

}



TEST_F(BuilderTest_92, Build_ReturnsExitSuccessOnNoErrors_92) {

    std::string err;

    ExitStatus result = builder->Build(&err);

    EXPECT_EQ(result, ExitSuccess);

}



TEST_F(BuilderTest_92, StartEdge_ReturnsTrueForValidEdge_92) {

    Edge edge;

    std::string err;

    bool result = builder->StartEdge(&edge, &err);

    EXPECT_TRUE(result);

}



TEST_F(BuilderTest_92, FinishCommand_ReturnsTrueOnSuccess_92) {

    CommandRunner::Result result;

    std::string err;

    bool finish_result = builder->FinishCommand(&result, &err);

    EXPECT_TRUE(finish_result);

}



TEST_F(BuilderTest_92, LoadDyndeps_ReturnsTrueForValidNode_92) {

    Node node;

    std::string err;

    bool load_result = builder->LoadDyndeps(&node, &err);

    EXPECT_TRUE(load_result);

}



TEST_F(BuilderTest_92, SetJobserverClient_SetsClientSuccessfully_92) {

    auto jobserver_client = std::make_unique<Jobserver::Client>();

    builder->SetJobserverClient(std::move(jobserver_client));

    // No direct observable behavior to test here except for absence of exceptions

}



TEST_F(BuilderTest_92, SetBuildLog_SetsLogSuccessfully_92) {

    BuildLog log;

    builder->SetBuildLog(&log);

    // No direct observable behavior to test here except for absence of exceptions

}



TEST_F(BuilderTest_92, GetExitCode_ReturnsInitialExitSuccess_92) {

    ExitStatus exit_code = builder->GetExitCode();

    EXPECT_EQ(exit_code, ExitSuccess);

}
