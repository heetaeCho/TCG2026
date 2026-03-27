#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "yaml-cpp/util/parse.cpp"

#include "yaml-cpp/node/node.h"



using ::testing::HasSubstr;

using ::testing::Ref;



TEST(ParseTest_676, NormalOperation_ValidYaml_676) {

    std::istringstream input("key: value\n");

    testing::internal::CaptureStdout();

    parse(input);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("key: value"));

}



TEST(ParseTest_676, BoundaryCondition_EmptyInput_676) {

    std::istringstream input("");

    testing::internal::CaptureStderr();

    parse(input);

    std::string error = testing::internal::GetCapturedStderr();

    EXPECT_THAT(error, HasSubstr("Parser exception"));

}



TEST(ParseTest_676, ExceptionalCase_MalformedYaml_676) {

    std::istringstream input("key: value\ninvalid_yaml");

    testing::internal::CaptureStderr();

    parse(input);

    std::string error = testing::internal::GetCapturedStderr();

    EXPECT_THAT(error, HasSubstr("Parser exception"));

}



TEST(ParseTest_676, NormalOperation_ComplexYaml_676) {

    std::istringstream input("parent:\n  child1: value1\n  child2: value2");

    testing::internal::CaptureStdout();

    parse(input);

    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_THAT(output, HasSubstr("parent"));

    EXPECT_THAT(output, HasSubstr("child1: value1"));

    EXPECT_THAT(output, HasSubstr("child2: value2"));

}
