#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "build_log.h"

#include "disk_interface.h"

#include "string_piece.h"



using ::testing::_;

using ::testing::Return;

using ::testing::NotNull;



class BuildLogTest_118 : public ::testing::Test {

protected:

    BuildLog build_log_;

    std::string error_;

};



TEST_F(BuildLogTest_118, OpenForWrite_Successful_118) {

    bool result = build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    EXPECT_TRUE(result);

    EXPECT_EQ(error_, "");

}



TEST_F(BuildLogTest_118, OpenForWrite_Failure_118) {

    bool result = build_log_.OpenForWrite("/nonexistent/path/test.log", BuildLogUser(), &error_);

    EXPECT_FALSE(result);

    EXPECT_NE(error_, "");

}



TEST_F(BuildLogTest_118, RecordCommand_Successful_118) {

    Edge edge;

    int start_time = 100;

    int end_time = 200;

    TimeStamp mtime = 300;



    build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    bool result = build_log_.RecordCommand(&edge, start_time, end_time, mtime);

    EXPECT_TRUE(result);

}



TEST_F(BuildLogTest_118, RecordCommand_UnopenedLog_118) {

    Edge edge;

    int start_time = 100;

    int end_time = 200;

    TimeStamp mtime = 300;



    bool result = build_log_.RecordCommand(&edge, start_time, end_time, mtime);

    EXPECT_FALSE(result);

}



TEST_F(BuildLogTest_118, Close_UnopenedLog_118) {

    build_log_.Close();

    // No observable behavior expected for this test case

}



TEST_F(BuildLogTest_118, Load_Successful_118) {

    build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    build_log_.Close();



    BuildLog load_build_log;

    auto result = load_build_log.Load("test.log", &error_);

    EXPECT_EQ(result, BuildLog::kLoadSuccess);

    EXPECT_EQ(error_, "");

}



TEST_F(BuildLogTest_118, Load_NonexistentFile_118) {

    BuildLog load_build_log;

    auto result = load_build_log.Load("/nonexistent/path/test.log", &error_);

    EXPECT_EQ(result, BuildLog::kCannotOpen);

    EXPECT_NE(error_, "");

}



TEST_F(BuildLogTest_118, LookupByOutput_Found_118) {

    build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    Edge edge;

    int start_time = 100;

    int end_time = 200;

    TimeStamp mtime = 300;



    build_log_.RecordCommand(&edge, start_time, end_time, mtime);

    build_log_.Close();



    BuildLog load_build_log;

    load_build_log.Load("test.log", &error_);

    LogEntry* entry = load_build_log.LookupByOutput(edge.GetOutputs()[0]);

    EXPECT_NE(entry, nullptr);

}



TEST_F(BuildLogTest_118, LookupByOutput_NotFound_118) {

    build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    build_log_.Close();



    BuildLog load_build_log;

    load_build_log.Load("test.log", &error_);

    LogEntry* entry = load_build_log.LookupByOutput("nonexistent_output");

    EXPECT_EQ(entry, nullptr);

}



TEST_F(BuildLogTest_118, Recompact_Successful_118) {

    build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    build_log_.Close();



    bool result = build_log_.Recompact("test.log", BuildLogUser(), &error_);

    EXPECT_TRUE(result);

    EXPECT_EQ(error_, "");

}



TEST_F(BuildLogTest_118, Recompact_NonexistentFile_118) {

    bool result = build_log_.Recompact("/nonexistent/path/test.log", BuildLogUser(), &error_);

    EXPECT_FALSE(result);

    EXPECT_NE(error_, "");

}



TEST_F(BuildLogTest_118, Restat_Successful_118) {

    MockDiskInterface mock_disk;

    StringPiece path("test_output");

    int output_count = 1;

    char* outputs[] = { const_cast<char*>(path.data()) };

    build_log_.OpenForWrite("test.log", BuildLogUser(), &error_);

    build_log_.Close();



    EXPECT_CALL(mock_disk, Stat(_, NotNull()))

        .WillOnce(Return(true));



    bool result = build_log_.Restat(path, mock_disk, output_count, outputs, &error_);

    EXPECT_TRUE(result);

}



TEST_F(BuildLogTest_118, Restat_UnopenedLog_118) {

    MockDiskInterface mock_disk;

    StringPiece path("test_output");

    int output_count = 1;

    char* outputs[] = { const_cast<char*>(path.data()) };



    EXPECT_CALL(mock_disk, Stat(_, NotNull()))

        .WillOnce(Return(true));



    bool result = build_log_.Restat(path, mock_disk, output_count, outputs, &error_);

    EXPECT_FALSE(result);

}
