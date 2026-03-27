#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "util/windows_logger.h"

#include <fstream>



using ::testing::_;

using ::testing::InSequence;

using ::testing::Return;



namespace leveldb {



class WindowsLoggerTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a temporary file for logging

        temp_file_.open("temp_log.txt", std::ios::out | std::ios::trunc);

        ASSERT_TRUE(temp_file_.is_open());

        logger_ = new WindowsLogger(temp_file_.rdbuf()->file_pointer_);

    }



    void TearDown() override {

        delete logger_;

        temp_file_.close();

        std::remove("temp_log.txt");

    }



protected:

    std::ofstream temp_file_;

    WindowsLogger* logger_;

};



TEST_F(WindowsLoggerTest_Logv_453, LogvWritesFormattedString_453) {

    const char* format = "Log entry: %d";

    int value = 123;

    va_list args;

    va_start(args, value);

    logger_->Logv(format, args);

    va_end(args);



    temp_file_.flush();

    std::ifstream log_file("temp_log.txt");

    std::string line;

    std::getline(log_file, line);



    EXPECT_TRUE(line.find("Log entry: 123") != std::string::npos);

}



TEST_F(WindowsLoggerTest_Logv_453, LogvHandlesLongThreadId_453) {

    const char* format = "Test";

    va_list args;

    va_start(args, format);

    logger_->Logv(format, args);

    va_end(args);



    temp_file_.flush();

    std::ifstream log_file("temp_log.txt");

    std::string line;

    std::getline(log_file, line);



    // Check if thread id is correctly truncated to 32 characters

    size_t pos = line.find(' ');

    EXPECT_TRUE(pos != std::string::npos);

    std::string thread_id = line.substr(0, pos);

    EXPECT_LE(thread_id.size(), 32);

}



TEST_F(WindowsLoggerTest_Logv_453, LogvAddsNewlineIfMissing_453) {

    const char* format = "No newline";

    va_list args;

    va_start(args, format);

    logger_->Logv(format, args);

    va_end(args);



    temp_file_.flush();

    std::ifstream log_file("temp_log.txt");

    std::string line;

    std::getline(log_file, line);



    EXPECT_EQ(line.back(), '\n');

}



TEST_F(WindowsLoggerTest_Logv_453, LogvHandlesLongMessage_453) {

    const char* format = "This is a very long message that exceeds the initial buffer size and requires dynamic allocation.";

    va_list args;

    va_start(args, format);

    logger_->Logv(format, args);

    va_end(args);



    temp_file_.flush();

    std::ifstream log_file("temp_log.txt");

    std::string line;

    std::getline(log_file, line);



    EXPECT_TRUE(line.find("This is a very long message that exceeds the initial buffer size and requires dynamic allocation.") != std::string::npos);

}



TEST_F(WindowsLoggerTest_Logv_453, LogvWritesToCorrectFile_453) {

    const char* format = "Another log entry";

    va_list args;

    va_start(args, format);

    logger_->Logv(format, args);

    va_end(args);



    temp_file_.flush();

    std::ifstream log_file("temp_log.txt");

    std::string line;

    std::getline(log_file, line);



    EXPECT_TRUE(line.find("Another log entry") != std::string::npos);

}



}  // namespace leveldb
