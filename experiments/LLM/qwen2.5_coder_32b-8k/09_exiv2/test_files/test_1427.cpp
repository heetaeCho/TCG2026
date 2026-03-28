#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "makernote_int.cpp"

#include <filesystem>

#include <string>



namespace fs = std::filesystem;

using namespace Exiv2::Internal;



class GetExiv2ConfigPathTest_1427 : public ::testing::Test {

protected:

    void SetUp() override {

        // Set up any necessary state before each test.

    }



    void TearDown() override {

        // Clean up any necessary state after each test.

    }

};



TEST_F(GetExiv2ConfigPathTest_1427, NormalOperationInCurrentDirectory_1427) {

    fs::path originalPath = fs::current_path();

    fs::create_directory("testdir");

    fs::current_path("testdir");



    std::ofstream file("exiv2.ini");

    file.close();



    EXPECT_EQ(getExiv2ConfigPath(), (fs::current_path() / "exiv2.ini").string());



    fs::remove("exiv2.ini");

    fs::current_path(originalPath);

    fs::remove("testdir");

}



TEST_F(GetExiv2ConfigPathTest_1427, NormalOperationInUserProfileDirectory_1427) {

    // This test is more complex to simulate as it depends on the user profile directory.

    // We assume that if the file exists in the current directory, it will be returned.

    fs::path originalPath = fs::current_path();

    fs::create_directory("testdir");

    fs::current_path("testdir");



    std::ofstream file(".exiv2");

    file.close();



    EXPECT_EQ(getExiv2ConfigPath(), (fs::current_path() / ".exiv2").string());



    fs::remove(".exiv2");

    fs::current_path(originalPath);

    fs::remove("testdir");

}



TEST_F(GetExiv2ConfigPathTest_1427, FileNotFoundInCurrentDirectory_1427) {

    fs::path originalPath = fs::current_path();

    fs::create_directory("testdir");

    fs::current_path("testdir");



    EXPECT_EQ(getExiv2ConfigPath(), (fs::current_path() / ".exiv2").string());



    fs::current_path(originalPath);

    fs::remove("testdir");

}



TEST_F(GetExiv2ConfigPathTest_1427, FileNotFoundInUserProfileDirectory_1427) {

    // This test assumes that if no file is found in the current directory,

    // it will attempt to find it in the user profile directory.

    fs::path originalPath = fs::current_path();

    fs::create_directory("testdir");

    fs::current_path("testdir");



    EXPECT_EQ(getExiv2ConfigPath(), (fs::current_path() / ".exiv2").string());



    fs::current_path(originalPath);

    fs::remove("testdir");

}



TEST_F(GetExiv2ConfigPathTest_1427, FilesystemDisabled_1427) {

    // Assuming EXV_ENABLE_FILESYSTEM is not defined, the function should return an empty string.

    EXPECT_EQ(getExiv2ConfigPath(), "");

}

```


