#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "clean.h"

#include "build.h"



using ::testing::_;

using ::testing::Return;

using ::testing::NiceMock;



class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD(bool, FileExists, (const std::string& path), (override));

    MOCK_METHOD(void, RemoveFile, (const std::string& path), (override));

};



class CleanerTest_162 : public ::testing::Test {

protected:

    MockDiskInterface mock_disk_interface;

    BuildConfig config_;

    Node node_;

    Rule rule_;



    CleanerTest_162() : cleaner_(&state_, config_, &mock_disk_interface) {}



    State state_;

    Cleaner cleaner_;

};



TEST_F(CleanerTest_162, IsVerbose_VerbosityNormal_DryRunFalse_162) {

    config_.verbosity = BuildConfig::NORMAL;

    config_.dry_run = false;

    EXPECT_FALSE(cleaner_.IsVerbose());

}



TEST_F(CleanerTest_162, IsVerbose_VerbosityQuiet_DryRunTrue_162) {

    config_.verbosity = BuildConfig::QUIET;

    config_.dry_run = true;

    EXPECT_FALSE(cleaner_.IsVerbose());

}



TEST_F(CleanerTest_162, IsVerbose_VerbosityNormal_DryRunTrue_162) {

    config_.verbosity = BuildConfig::NORMAL;

    config_.dry_run = true;

    EXPECT_TRUE(cleaner_.IsVerbose());

}



TEST_F(CleanerTest_162, IsVerbose_VerbosityVerbose_DryRunFalse_162) {

    config_.verbosity = BuildConfig::VERBOSE;

    config_.dry_run = false;

    EXPECT_TRUE(cleaner_.IsVerbose());

}



TEST_F(CleanerTest_162, CleanTarget_Node_Success_162) {

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(true));

    EXPECT_CALL(mock_disk_interface, RemoveFile(_)).Times(1);

    int result = cleaner_.CleanTarget(&node_);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(CleanerTest_162, CleanTarget_Node_NoFilesToRemove_162) {

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(false));

    int result = cleaner_.CleanTarget(&node_);

    EXPECT_EQ(result, 0); // Assuming no files to remove is also success

}



TEST_F(CleanerTest_162, CleanTarget_CharPtr_Success_162) {

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(true));

    EXPECT_CALL(mock_disk_interface, RemoveFile(_)).Times(1);

    int result = cleaner_.CleanTarget("some_target");

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(CleanerTest_162, CleanAll_GeneratorFalse_Success_162) {

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(true));

    EXPECT_CALL(mock_disk_interface, RemoveFile(_)).Times(1);

    int result = cleaner_.CleanAll(false);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(CleanerTest_162, CleanRule_Rule_Success_162) {

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(true));

    EXPECT_CALL(mock_disk_interface, RemoveFile(_)).Times(1);

    int result = cleaner_.CleanRule(&rule_);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(CleanerTest_162, CleanRules_CharPtrArray_Success_162) {

    char* rules[] = { "rule1", "rule2" };

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(true));

    EXPECT_CALL(mock_disk_interface, RemoveFile(_)).Times(2);

    int result = cleaner_.CleanRules(2, rules);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}



TEST_F(CleanerTest_162, CleanDead_Success_162) {

    BuildLog::Entries entries;

    ON_CALL(mock_disk_interface, FileExists(_)).WillByDefault(Return(true));

    EXPECT_CALL(mock_disk_interface, RemoveFile(_)).Times(1);

    int result = cleaner_.CleanDead(entries);

    EXPECT_EQ(result, 0); // Assuming success is indicated by 0

}
