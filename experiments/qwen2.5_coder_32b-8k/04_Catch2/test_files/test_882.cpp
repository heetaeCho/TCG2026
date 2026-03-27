#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <stdexcept>

#include <string>



// Assuming parse_log_file_arg is in a namespace or header file, include it here.

// For this example, we'll assume it's in the global namespace.



const std::string logfile_prefix = "--log-file=";



TEST(parse_log_file_arg_Test_882, NormalOperation_882) {

    EXPECT_EQ(parse_log_file_arg("--log-file=MemoryChecker.123.log"), 123);

}



TEST(parse_log_file_arg_Test_882, BoundaryCondition_EmptyNumber_882) {

    EXPECT_THROW(parse_log_file_arg("--log-file=MemoryChecker..log"), std::domain_error);

}



TEST(parse_log_file_arg_Test_882, BoundaryCondition_NoPrefix_882) {

    EXPECT_THROW(parse_log_file_arg("MemoryChecker.123.log"), std::logic_error); // This will fail the assert in the function.

}



TEST(parse_log_file_arg_Test_882, BoundaryCondition_WrongFileName_882) {

    EXPECT_THROW(parse_log_file_arg("--log-file=WrongName.123.log"), std::domain_error);

}



TEST(parse_log_file_arg_Test_882, ExceptionalCase_NoNumber_882) {

    EXPECT_THROW(parse_log_file_arg("--log-file=MemoryChecker.file.log"), std::domain_error);

}



TEST(parse_log_file_arg_Test_882, ExceptionalCase_MultipleNumbers_882) {

    EXPECT_THROW(parse_log_file_arg("--log-file=MemoryChecker.123.456.log"), std::domain_error);

}
