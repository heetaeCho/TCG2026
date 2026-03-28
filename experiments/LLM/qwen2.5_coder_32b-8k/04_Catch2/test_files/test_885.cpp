#include <gtest/gtest.h>

#include <gmock/gmock.h>



using ::testing::_;

using ::testing::HasSubstr;

using ::testing::Return;



extern int exec_cmd(std::string const& cmd, int log_num, std::string const& path);



// Mock class to capture cout output for verification

class MockCout {

public:

    MOCK_METHOD(void, print, (const std::string&), ());

};



MockCout* mock_cout = nullptr;



void test_exec_cmd(std::string const& cmd, int log_num, std::string const& path) {

    auto real_cmd = "OpenCppCoverage --export_type binary:cov-report" + std::to_string(log_num) + ".bin --quiet " + "--sources " + escape_arg(path) + "\\src" + " --cover_children -- " + cmd;

    mock_cout->print(real_cmd);

    exec_cmd(cmd, log_num, path);

}



TEST(exec_cmd_Test_885, NormalOperation_885) {

    EXPECT_CALL(*mock_cout, print(HasSubstr("OpenCppCoverage")));

    EXPECT_NO_THROW(test_exec_cmd("some_command", 1, "test_path"));

}



TEST(exec_cmd_Test_885, BoundaryLogNumZero_885) {

    EXPECT_CALL(*mock_cout, print(HasSubstr("cov-report0.bin")));

    EXPECT_NO_THROW(test_exec_cmd("some_command", 0, "test_path"));

}



TEST(exec_cmd_Test_885, BoundaryLogNumNegative_885) {

    EXPECT_CALL(*mock_cout, print(HasSubstr("cov-report-1.bin")));

    EXPECT_NO_THROW(test_exec_cmd("some_command", -1, "test_path"));

}



TEST(exec_cmd_Test_885, EmptyCmd_885) {

    EXPECT_CALL(*mock_cout, print(HasSubstr("-- ")));

    EXPECT_NO_THROW(test_exec_cmd("", 1, "test_path"));

}



TEST(exec_cmd_Test_885, EmptyPath_885) {

    EXPECT_CALL(*mock_cout, print(HasSubstr("--sources .\\src")));

    EXPECT_NO_THROW(test_exec_cmd("some_command", 1, ""));

}



TEST(exec_cmd_Test_885, PopenFailure_885) {

    // Simulate popen failure by mocking a failing function

    EXPECT_CALL(*mock_cout, print(_)).WillOnce([](const std::string& str) {

        throw std::runtime_error("popen() failed!");

    });

    EXPECT_THROW(test_exec_cmd("some_command", 1, "test_path"), std::runtime_error);

}



TEST(exec_cmd_Test_885, PcloseFailure_885) {

    // Simulate pclose failure by mocking a failing function

    EXPECT_CALL(*mock_cout, print(_)).WillOnce([](const std::string& str) {

        _pclose(nullptr);  // This will simulate the underlying error

        throw std::runtime_error("underlying error in pclose()");

    });

    EXPECT_THROW(test_exec_cmd("some_command", 1, "test_path"), std::runtime_error);

}

```


