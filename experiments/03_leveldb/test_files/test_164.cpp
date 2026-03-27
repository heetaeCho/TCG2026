#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "db/version_set.h"

#include "leveldb/env.h"

#include "leveldb/status.h"



using namespace leveldb;

using namespace log;

using ::testing::_;

using ::testing::Return;

using ::testing::SetArgReferee0To;



class MockEnv : public Env {

public:

    MOCK_METHOD3(NewSequentialFile, Status(const std::string&, SequentialFile**, const char*));

    MOCK_METHOD4(ReadFileToString, Status(const std::string&, std::string*, const char*, int));

};



class VersionSetTest_164 : public ::testing::Test {

protected:

    MockEnv mock_env;

    Options options;

    TableCache table_cache{nullptr, 0};

    InternalKeyComparator icmp{BytewiseComparator()};

    bool save_manifest;



    VersionSet version_set{"db_name", &options, &table_cache, &icmp};



    void SetUp() override {

        ON_CALL(mock_env, ReadFileToString(_, _, nullptr, -1))

            .WillByDefault(Return(Status::OK()));

    }

};



TEST_F(VersionSetTest_164, Recover_SuccessfulRecovery_164) {

    std::string current_content = "MANIFEST-000002\n";

    EXPECT_CALL(mock_env, ReadFileToString("db_name/CURRENT", _))

        .WillOnce(SetArgReferee1To(current_content));

    

    SequentialFile* seq_file = new SequentialFile();

    EXPECT_CALL(mock_env, NewSequentialFile("db_name/MANIFEST-000002", _, nullptr))

        .WillOnce(DoAll(SetArgPointee<1>(seq_file), Return(Status::OK())));

    

    Status s = version_set.Recover(&save_manifest);

    ASSERT_TRUE(s.ok());

}



TEST_F(VersionSetTest_164, Recover_CurrentFileNotFound_164) {

    EXPECT_CALL(mock_env, ReadFileToString("db_name/CURRENT", _))

        .WillOnce(Return(Status::NotFound()));

    

    Status s = version_set.Recover(&save_manifest);

    ASSERT_TRUE(s.IsCorruption());

}



TEST_F(VersionSetTest_164, Recover_CurrentFileDoesNotEndWithNewline_164) {

    std::string current_content = "MANIFEST-000002";

    EXPECT_CALL(mock_env, ReadFileToString("db_name/CURRENT", _))

        .WillOnce(SetArgReferee1To(current_content));

    

    Status s = version_set.Recover(&save_manifest);

    ASSERT_TRUE(s.IsCorruption());

}



TEST_F(VersionSetTest_164, Recover_DescriptorFileNotFound_164) {

    std::string current_content = "MANIFEST-000002\n";

    EXPECT_CALL(mock_env, ReadFileToString("db_name/CURRENT", _))

        .WillOnce(SetArgReferee1To(current_content));

    

    EXPECT_CALL(mock_env, NewSequentialFile("db_name/MANIFEST-000002", _, nullptr))

        .WillOnce(Return(Status::NotFound()));

    

    Status s = version_set.Recover(&save_manifest);

    ASSERT_TRUE(s.IsCorruption());

}



TEST_F(VersionSetTest_164, Recover_ManifestHasMissingEntries_164) {

    std::string current_content = "MANIFEST-000002\n";

    EXPECT_CALL(mock_env, ReadFileToString("db_name/CURRENT", _))

        .WillOnce(SetArgReferee1To(current_content));

    

    SequentialFile* seq_file = new SequentialFile();

    EXPECT_CALL(mock_env, NewSequentialFile("db_name/MANIFEST-000002", _, nullptr))

        .WillOnce(DoAll(SetArgPointee<1>(seq_file), Return(Status::OK())));

    

    // Simulate reading a manifest with missing required entries

    Status s = version_set.Recover(&save_manifest);

    ASSERT_TRUE(s.IsCorruption());

}
