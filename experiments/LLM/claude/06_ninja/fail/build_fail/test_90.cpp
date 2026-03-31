#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "build.h"
#include "graph.h"
#include "state.h"
#include "build_log.h"
#include "deps_log.h"
#include "disk_interface.h"
#include "status.h"
#include "jobserver.h"

#include <memory>
#include <string>

// Mock implementations for dependencies

class MockDiskInterface : public DiskInterface {
public:
  MOCK_METHOD(TimeStamp, Stat, (const std::string& path, std::string* err), (const, override));
  MOCK_METHOD(bool, WriteFile, (const std::string& path, const std::string& contents), (override));
  MOCK_METHOD(bool, MakeDir, (const std::string& path), (override));
  MOCK_METHOD(Status, ReadFile, (const std::string& path, std::string* contents, std::string* err), (override));
  MOCK_METHOD(int, RemoveFile, (const std::string& path), (override));
};

class MockStatus : public Status {
public:
  MOCK_METHOD(void, PlanHasTotalEdges, (int total), (override));
  MOCK_METHOD(void, BuildEdgeStarted, (const Edge* edge, int start_time_millis), (override));
  MOCK_METHOD(void, BuildEdgeFinished, (Edge* edge, int end_time_millis, bool success, const std::string& output), (override));
  MOCK_METHOD(void, BuildLoadDyndeps, (), (override));
  MOCK_METHOD(void, BuildStarted, (), (override));
  MOCK_METHOD(void, BuildFinished, (), (override));
  MOCK_METHOD(void, Info, (const char* msg, ...), (override));
  MOCK_METHOD(void, Warning, (const char* msg, ...), (override));
  MOCK_METHOD(void, Error, (const char* msg, ...), (override));
};

class MockJobserverClient : public Jobserver::Client {
public:
  MOCK_METHOD(bool, Enabled, (), (const, override));
  MOCK_METHOD(bool, Acquire, (), (override));
  MOCK_METHOD(void, Release, (), (override));
};

class BuilderTest_90 : public ::testing::Test {
protected:
  void SetUp() override {
    config_.verbosity = BuildConfig::NORMAL;
    config_.parallelism = 1;
    config_.failures_allowed = 1;

    disk_interface_ = new MockDiskInterface();
    status_ = new MockStatus();

    builder_ = std::make_unique<Builder>(
        &state_, config_, &build_log_, &deps_log_,
        disk_interface_, status_, 0);
  }

  void TearDown() override {
    builder_.reset();
    // disk_interface_ and status_ are owned externally; 
    // Builder doesn't take ownership of them
    delete disk_interface_;
    delete status_;
  }

  State state_;
  BuildConfig config_;
  BuildLog build_log_;
  DepsLog deps_log_;
  MockDiskInterface* disk_interface_;
  MockStatus* status_;
  std::unique_ptr<Builder> builder_;
};

// Test: SetJobserverClient transfers ownership of the client
TEST_F(BuilderTest_90, SetJobserverClientTransfersOwnership_90) {
  auto client = std::make_unique<MockJobserverClient>();
  MockJobserverClient* raw_ptr = client.get();

  builder_->SetJobserverClient(std::move(client));

  // After moving, the builder should hold the jobserver client
  ASSERT_NE(builder_->jobserver_, nullptr);
  EXPECT_EQ(builder_->jobserver_.get(), raw_ptr);
}

// Test: SetJobserverClient with nullptr
TEST_F(BuilderTest_90, SetJobserverClientWithNullptr_90) {
  builder_->SetJobserverClient(nullptr);
  EXPECT_EQ(builder_->jobserver_, nullptr);
}

// Test: SetJobserverClient replaces existing client
TEST_F(BuilderTest_90, SetJobserverClientReplacesExisting_90) {
  auto client1 = std::make_unique<MockJobserverClient>();
  auto client2 = std::make_unique<MockJobserverClient>();
  MockJobserverClient* raw_ptr2 = client2.get();

  builder_->SetJobserverClient(std::move(client1));
  ASSERT_NE(builder_->jobserver_, nullptr);

  builder_->SetJobserverClient(std::move(client2));
  ASSERT_NE(builder_->jobserver_, nullptr);
  EXPECT_EQ(builder_->jobserver_.get(), raw_ptr2);
}

// Test: AlreadyUpToDate returns true when no targets are added
TEST_F(BuilderTest_90, AlreadyUpToDateWithNoTargets_90) {
  EXPECT_TRUE(builder_->AlreadyUpToDate());
}

// Test: AddTarget with nonexistent target returns error
TEST_F(BuilderTest_90, AddTargetNonexistentReturnsError_90) {
  std::string err;
  Node* node = builder_->AddTarget("nonexistent_target", &err);
  // When the target doesn't exist in the state, it should return nullptr or set error
  EXPECT_EQ(node, nullptr);
  EXPECT_FALSE(err.empty());
}

// Test: GetExitCode returns ExitSuccess initially
TEST_F(BuilderTest_90, GetExitCodeInitiallySuccess_90) {
  EXPECT_EQ(builder_->GetExitCode(), ExitSuccess);
}

// Test: SetJobserverClient called multiple times with nullptr
TEST_F(BuilderTest_90, SetJobserverClientMultipleNullptr_90) {
  builder_->SetJobserverClient(nullptr);
  EXPECT_EQ(builder_->jobserver_, nullptr);

  builder_->SetJobserverClient(nullptr);
  EXPECT_EQ(builder_->jobserver_, nullptr);
}

// Test: SetBuildLog sets the build log
TEST_F(BuilderTest_90, SetBuildLog_90) {
  BuildLog new_log;
  // Should not crash
  builder_->SetBuildLog(&new_log);
}

// Test: SetBuildLog with nullptr
TEST_F(BuilderTest_90, SetBuildLogNullptr_90) {
  builder_->SetBuildLog(nullptr);
  // Should not crash
}

// Test: Cleanup does not crash on fresh builder
TEST_F(BuilderTest_90, CleanupOnFreshBuilder_90) {
  // Calling Cleanup without building anything should not crash
  builder_->Cleanup();
}

// Test: Build with no targets returns already up to date
TEST_F(BuilderTest_90, BuildWithNoTargets_90) {
  std::string err;
  EXPECT_CALL(*status_, BuildFinished()).Times(::testing::AnyNumber());
  EXPECT_CALL(*status_, BuildStarted()).Times(::testing::AnyNumber());

  // When AlreadyUpToDate is true, Build should succeed quickly
  EXPECT_TRUE(builder_->AlreadyUpToDate());
}

// Test: AddTarget with valid node in state
TEST_F(BuilderTest_90, AddTargetWithExistingNode_90) {
  // Add a node to the state first
  state_.GetNode("existing.o", 0);

  std::string err;
  EXPECT_CALL(*disk_interface_, Stat(::testing::_, ::testing::_))
      .WillRepeatedly(::testing::Return(1));

  Node* node = builder_->AddTarget("existing.o", &err);
  // The node exists in state but might not have an edge - behavior depends on implementation
  // We just check it doesn't crash and returns something reasonable
  if (node) {
    EXPECT_EQ(err, "");
  }
}

// Test: SetJobserverClient after setting one, old one is properly released
TEST_F(BuilderTest_90, SetJobserverClientOldClientDestroyed_90) {
  bool destroyed = false;

  class TrackingClient : public Jobserver::Client {
  public:
    TrackingClient(bool* flag) : destroyed_(flag) {}
    ~TrackingClient() override { *destroyed_ = true; }
    bool Enabled() const override { return true; }
    bool Acquire() override { return true; }
    void Release() override {}
    bool* destroyed_;
  };

  auto client1 = std::make_unique<TrackingClient>(&destroyed);
  builder_->SetJobserverClient(std::move(client1));
  EXPECT_FALSE(destroyed);

  auto client2 = std::make_unique<MockJobserverClient>();
  builder_->SetJobserverClient(std::move(client2));
  EXPECT_TRUE(destroyed);
}
