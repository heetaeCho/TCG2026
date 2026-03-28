#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mock dependencies if needed

class MockDiskInterface : public DiskInterface {

public:

    MOCK_METHOD(bool, FileExists, (const std::string& path), (override));

    MOCK_METHOD(int, RemoveFile, (const std::string& path), (override));

};



class CleanerTest_161 : public ::testing::Test {

protected:

    MockDiskInterface mock_disk_interface;

    BuildConfig build_config;

    State state;



    Cleaner* cleaner;



    void SetUp() override {

        cleaner = new Cleaner(&state, build_config, &mock_disk_interface);

    }



    void TearDown() override {

        delete cleaner;

    }

};



TEST_F(CleanerTest_161, CleanTarget_Node_Successful_161) {

    Node target_node;  // Assuming Node is a defined type

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(1).WillOnce(::testing::Return(0));

    int result = cleaner->CleanTarget(&target_node);

    EXPECT_EQ(result, 0);

}



TEST_F(CleanerTest_161, CleanTarget_Node_FileNotFound_161) {

    Node target_node;  // Assuming Node is a defined type

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(0);

    int result = cleaner->CleanTarget(&target_node);

    EXPECT_EQ(result, 0);  // Assuming no error if file not found

}



TEST_F(CleanerTest_161, CleanTarget_String_Successful_161) {

    const char* target_path = "test_file.txt";

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::StrEq(target_path))).Times(1).WillOnce(::testing::Return(0));

    int result = cleaner->CleanTarget(target_path);

    EXPECT_EQ(result, 0);

}



TEST_F(CleanerTest_161, CleanTarget_String_FileNotFound_161) {

    const char* target_path = "non_existent_file.txt";

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::StrEq(target_path))).Times(0);

    int result = cleaner->CleanTarget(target_path);

    EXPECT_EQ(result, 0);  // Assuming no error if file not found

}



TEST_F(CleanerTest_161, CleanAll_Successful_161) {

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(2).WillRepeatedly(::testing::Return(0));

    int result = cleaner->CleanAll(false);

    EXPECT_EQ(result, 0);

}



TEST_F(CleanerTest_161, CleanRule_String_Successful_161) {

    const char* rule_name = "test_rule";

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(2).WillRepeatedly(::testing::Return(0));

    int result = cleaner->CleanRule(rule_name);

    EXPECT_EQ(result, 0);

}



TEST_F(CleanerTest_161, CleanDead_Successful_161) {

    BuildLog::Entries entries;  // Assuming BuildLog::Entries is a defined type

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(2).WillRepeatedly(::testing::Return(0));

    int result = cleaner->CleanDead(entries);

    EXPECT_EQ(result, 0);

}



TEST_F(CleanerTest_161, CleanedFilesCount_AfterCleanTarget_161) {

    Node target_node;  // Assuming Node is a defined type

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(1).WillOnce(::testing::Return(0));

    cleaner->CleanTarget(&target_node);

    EXPECT_EQ(cleaner->cleaned_files_count(), 1);

}



TEST_F(CleanerTest_161, CleanedFilesCount_AfterMultipleCleans_161) {

    Node target_node;  // Assuming Node is a defined type

    EXPECT_CALL(mock_disk_interface, RemoveFile(::testing::_)).Times(2).WillRepeatedly(::testing::Return(0));

    cleaner->CleanTarget(&target_node);

    cleaner->CleanAll(false);

    EXPECT_EQ(cleaner->cleaned_files_count(), 3);  // Assuming CleanAll cleans 2 files

}
