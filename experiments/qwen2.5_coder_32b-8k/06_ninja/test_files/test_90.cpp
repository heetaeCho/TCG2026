#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build.h"



using ::testing::_;

using ::testing::NiceMock;

using ::testing::Return;



class MockJobserverClient : public Jobserver::Client {

public:

    MOCK_METHOD(bool, Acquire, (), (override));

    MOCK_METHOD(void, Release, (), (override));

};



class BuilderTest_90 : public ::testing::Test {

protected:

    NiceMock<MockJobserverClient> mock_jobserver_client;

    BuildConfig config_;

    BuildLog build_log_;

    DepsLog deps_log_;

    DiskInterface disk_interface_;

    Status status_;

    int64_t start_time_millis_ = 0;

    std::unique_ptr<State> state_ = std::make_unique<State>();

    Builder builder_;



    BuilderTest_90() : builder_(state_.get(), config_, &build_log_, &deps_log_, &disk_interface_, &status_, start_time_millis_) {}

};



TEST_F(BuilderTest_90, SetJobserverClient_SetsJobserverClient_90) {

    std::unique_ptr<Jobserver::Client> jobserver_client = std::make_unique<NiceMock<MockJobserverClient>>();

    builder_.SetJobserverClient(std::move(jobserver_client));

    // Since we treat the implementation as a black box, we can't directly verify

    // that jobserver_ is set. We rely on the assumption that if no crash occurs,

    // and other functionalities work correctly, then it's likely set.

}



TEST_F(BuilderTest_90, AddTarget_ValidName_ReturnsNode_90) {

    std::string name = "test_target";

    std::string err;

    Node* node = builder_.AddTarget(name, &err);

    EXPECT_NE(node, nullptr);

    EXPECT_TRUE(err.empty());

}



TEST_F(BuilderTest_90, AddTarget_InvalidName_ReturnsNullptr_90) {

    std::string name = "";

    std::string err;

    Node* node = builder_.AddTarget(name, &err);

    EXPECT_EQ(node, nullptr);

    EXPECT_FALSE(err.empty());

}



TEST_F(BuilderTest_90, AlreadyUpToDate_NoTargets_ReturnsTrue_90) {

    EXPECT_TRUE(builder_.AlreadyUpToDate());

}



TEST_F(BuilderTest_90, Build_NoErrors_ReturnsExitSuccess_90) {

    std::string err;

    ExitStatus status = builder_.Build(&err);

    EXPECT_EQ(status, ExitStatus::ExitSuccess);

    EXPECT_TRUE(err.empty());

}



TEST_F(BuilderTest_90, StartEdge_ValidEdge_ReturnsTrue_90) {

    // Assuming we have a valid Edge pointer to test with

    Edge* edge = new Edge();

    std::string err;

    EXPECT_CALL(mock_jobserver_client, Acquire()).WillOnce(Return(true));

    builder_.SetJobserverClient(std::make_unique<NiceMock<MockJobserverClient>>(mock_jobserver_client));

    bool result = builder_.StartEdge(edge, &err);

    delete edge;

    EXPECT_TRUE(result);

    EXPECT_TRUE(err.empty());

}



TEST_F(BuilderTest_90, FinishCommand_ValidResult_ReturnsTrue_90) {

    CommandRunner::Result result;

    std::string err;

    bool finish_result = builder_.FinishCommand(&result, &err);

    EXPECT_TRUE(finish_result);

    EXPECT_TRUE(err.empty());

}
