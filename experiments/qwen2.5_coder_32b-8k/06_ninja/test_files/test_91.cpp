#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build.h"

#include "build_log.h"



using ::testing::StrictMock;

using ::testing::_;



class MockBuildLog : public BuildLog {

public:

    MOCK_METHOD(bool, OpenForWrite, (const std::string &, const BuildLogUser &, std::string *), (override));

    MOCK_METHOD(void, Close, (), (override));

    MOCK_METHOD(LoadStatus, Load, (const std::string &, std::string *), (override));

    MOCK_METHOD(LogEntry *, LookupByOutput, (const std::string &), (override));

    MOCK_METHOD(bool, RecordCommand, (Edge *, int, int, TimeStamp), (override));

    MOCK_METHOD(bool, WriteEntry, (FILE *, const LogEntry &), (override));

    MOCK_METHOD(bool, Recompact, (const std::string &, const BuildLogUser &, std::string *), (override));

    MOCK_METHOD(bool, Restat, (StringPiece, const DiskInterface &, int, char **, std::string *), (override));

};



class BuilderTest_91 : public ::testing::Test {

protected:

    StrictMock<MockBuildLog> mock_build_log_;

    BuildConfig config_;

    DepsLog deps_log_;

    DiskInterface disk_interface_;

    Status status_;

    int64_t start_time_millis_ = 0;

    std::unique_ptr<State> state_;

    Builder builder_;



    BuilderTest_91() : state_(std::make_unique<State>()),

                       builder_(state_.get(), config_, &mock_build_log_, &deps_log_, &disk_interface_, &status_, start_time_millis_) {}

};



TEST_F(BuilderTest_91, SetBuildLog_NormalOperation_91) {

    Builder builder(state_.get(), config_, nullptr, &deps_log_, &disk_interface_, &status_, start_time_millis_);

    builder.SetBuildLog(&mock_build_log_);



    EXPECT_EQ(builder.scan_.build_log(), &mock_build_log_);

}



TEST_F(BuilderTest_91, SetBuildLog_BoundaryCondition_Nullptr_91) {

    Builder builder(state_.get(), config_, &mock_build_log_, &deps_log_, &disk_interface_, &status_, start_time_millis_);

    builder.SetBuildLog(nullptr);



    EXPECT_EQ(builder.scan_.build_log(), nullptr);

}
