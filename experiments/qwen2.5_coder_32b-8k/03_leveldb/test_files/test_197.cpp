#include "gtest/gtest.h"

#include "gmock/gmock.h"

#include "db/dumpfile.cc"

#include "leveldb/status.h"

#include "leveldb/env.h"

#include "leveldb/filename.h"



using namespace leveldb;

using ::testing::_;

using ::testing::Return;



class DumpFileTest_197 : public ::testing::Test {

protected:

    std::unique_ptr<Env> mock_env = Env::Default();

    std::unique_ptr<WritableFile> mock_dst;

};



TEST_F(DumpFileTest_197, PutIncreasesCount_LogFileType_197) {

    EXPECT_CALL(*mock_env, NewSequentialFile("logfile.log", _))

        .WillOnce(Return(Status::OK()));

    Status status = DumpFile(mock_env.get(), "logfile.log", mock_dst.get());

    EXPECT_TRUE(status.ok());

}



TEST_F(DumpFileTest_197, PutIncreasesCount_DescriptorFileType_197) {

    EXPECT_CALL(*mock_env, NewSequentialFile("descriptor.descriptor", _))

        .WillOnce(Return(Status::OK()));

    Status status = DumpFile(mock_env.get(), "descriptor.descriptor", mock_dst.get());

    EXPECT_TRUE(status.ok());

}



TEST_F(DumpFileTest_197, PutIncreasesCount_TableFileType_197) {

    EXPECT_CALL(*mock_env, NewSequentialFile("table.table", _))

        .WillOnce(Return(Status::OK()));

    Status status = DumpFile(mock_env.get(), "table.table", mock_dst.get());

    EXPECT_TRUE(status.ok());

}



TEST_F(DumpFileTest_197, InvalidFileType_197) {

    Status status = DumpFile(mock_env.get(), "unknownfile.unknown", mock_dst.get());

    EXPECT_EQ(status.code(), kInvalidArgument);

}



TEST_F(DumpFileTest_197, EmptyFileName_197) {

    Status status = DumpFile(mock_env.get(), "", mock_dst.get());

    EXPECT_EQ(status.code(), kInvalidArgument);

}



TEST_F(DumpFileTest_197, EnvFailure_LogFileType_197) {

    EXPECT_CALL(*mock_env, NewSequentialFile("logfile.log", _))

        .WillOnce(Return(Status::IOError("")));

    Status status = DumpFile(mock_env.get(), "logfile.log", mock_dst.get());

    EXPECT_EQ(status.code(), kIOError);

}



TEST_F(DumpFileTest_197, EnvFailure_DescriptorFileType_197) {

    EXPECT_CALL(*mock_env, NewSequentialFile("descriptor.descriptor", _))

        .WillOnce(Return(Status::NotFound("")));

    Status status = DumpFile(mock_env.get(), "descriptor.descriptor", mock_dst.get());

    EXPECT_EQ(status.code(), kNotFound);

}



TEST_F(DumpFileTest_197, EnvFailure_TableFileType_197) {

    EXPECT_CALL(*mock_env, NewSequentialFile("table.table", _))

        .WillOnce(Return(Status::Corruption("")));

    Status status = DumpFile(mock_env.get(), "table.table", mock_dst.get());

    EXPECT_EQ(status.code(), kCorruption);

}
