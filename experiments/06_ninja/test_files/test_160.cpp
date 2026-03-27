#include <gtest/gtest.h>

#include <gmock/gmock.h>



extern "C" {

    int platformAwareUnlink(const char* filename);

}



class PlatformAwareUnlinkTest_160 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code, if necessary

    }



    void TearDown() override {

        // Teardown code, if necessary

    }

};



TEST_F(PlatformAwareUnlinkTest_160, ValidFileDeletion_160) {

    const char* testFileName = "testfile.txt";

    FILE* file = fopen(testFileName, "w");

    fclose(file);



    int result = platformAwareUnlink(testFileName);

    EXPECT_EQ(result, 0); // Assuming the file is successfully deleted

}



TEST_F(PlatformAwareUnlinkTest_160, NonExistentFileDeletion_160) {

    const char* nonExistentFileName = "nonexistentfile.txt";

    int result = platformAwareUnlink(nonExistentFileName);

    EXPECT_NE(result, 0); // Assuming the file does not exist

}



TEST_F(PlatformAwareUnlinkTest_160, NullFilename_160) {

    const char* nullFileName = nullptr;

    int result = platformAwareUnlink(nullFileName);

    EXPECT_NE(result, 0); // Assuming a null filename is invalid

}
