#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "tinyxml2.cpp"



using namespace tinyxml2;



class CallFopenTest_277 : public ::testing::Test {

protected:

    const char* validFilePath = "valid_file_path.txt";

    const char* validMode = "r";

    const char* invalidFilePath = "";

    const char* invalidMode = "";



    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(CallFopenTest_277, OpenValidFileInReadMode_277) {

    FILE* fp = callfopen(validFilePath, validMode);

    EXPECT_NE(fp, nullptr);

    if (fp != nullptr) {

        fclose(fp);

    }

}



TEST_F(CallFopenTest_277, OpenInvalidFilePath_277) {

    FILE* fp = callfopen(invalidFilePath, validMode);

    EXPECT_EQ(fp, nullptr);

}



TEST_F(CallFopenTest_277, OpenValidFileWithInvalidMode_277) {

    FILE* fp = callfopen(validFilePath, invalidMode);

    EXPECT_EQ(fp, nullptr);

}



TEST_F(CallFopenTest_277, OpenNonExistentFileInReadMode_277) {

    FILE* fp = callfopen("non_existent_file.txt", validMode);

    EXPECT_EQ(fp, nullptr);

}
