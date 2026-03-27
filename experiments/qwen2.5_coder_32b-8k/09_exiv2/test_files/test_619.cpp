#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/src/basicio.cpp"

#include "exiv2/types.hpp"

#include "exiv2/error.hpp"

#include <filesystem>



namespace fs = std::filesystem;



class ReadFileTest_619 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a temporary directory for test files

        temp_dir = fs::temp_directory_path() / "exiv2_read_file_test";

        fs::create_directories(temp_dir);

    }



    void TearDown() override {

        // Remove the temporary directory and all its contents

        fs::remove_all(temp_dir);

    }



    std::string createTestFile(const std::string& content) {

        auto testFilePath = temp_dir / "testfile.bin";

        std::ofstream(testFilePath.string(), std::ios::binary).write(content.data(), content.size());

        return testFilePath.string();

    }



    fs::path temp_dir;

};



TEST_F(ReadFileTest_619, ReadNormalFile_619) {

    auto path = createTestFile("Hello, World!");

    Exiv2::DataBuf buf = Exiv2::readFile(path);

    EXPECT_EQ(buf.size(), 13);

    EXPECT_STREQ(reinterpret_cast<const char*>(buf.c_data()), "Hello, World!");

}



TEST_F(ReadFileTest_619, ReadEmptyFile_619) {

    auto path = createTestFile("");

    Exiv2::DataBuf buf = Exiv2::readFile(path);

    EXPECT_EQ(buf.size(), 0);

}



TEST_F(ReadFileTest_619, FileDoesNotExist_619) {

    try {

        Exiv2::readFile("non_existent_file");

        FAIL() << "Expected an exception to be thrown";

    } catch (const Exiv2::Error& e) {

        EXPECT_EQ(e.code(), Exiv2::ErrorCode::kerFileOpenFailed);

    }

}



TEST_F(ReadFileTest_619, FileWithLargeContent_619) {

    std::string large_content(1024 * 1024, 'A'); // 1 MB of 'A's

    auto path = createTestFile(large_content);

    Exiv2::DataBuf buf = Exiv2::readFile(path);

    EXPECT_EQ(buf.size(), large_content.size());

    EXPECT_TRUE(std::equal(large_content.begin(), large_content.end(), reinterpret_cast<const char*>(buf.c_data())));

}



TEST_F(ReadFileTest_619, FileWithSpecialCharacters_619) {

    std::string special_content = "\x00\x01\xfe\xff";

    auto path = createTestFile(special_content);

    Exiv2::DataBuf buf = Exiv2::readFile(path);

    EXPECT_EQ(buf.size(), special_content.size());

    EXPECT_TRUE(std::equal(special_content.begin(), special_content.end(), reinterpret_cast<const char*>(buf.c_data())));

}



TEST_F(ReadFileTest_619, ReadFileWithZeroSize_619) {

    auto path = createTestFile("");

    Exiv2::DataBuf buf = Exiv2::readFile(path);

    EXPECT_EQ(buf.size(), 0);

}
