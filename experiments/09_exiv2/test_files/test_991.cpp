#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include <regex>

#include <sstream>

#include <string>



// Mock class to simulate behavior of shouldOutput function

class MockShouldOutput {

public:

    MOCK_CONST_METHOD3(shouldOutput, bool(const std::vector<std::regex>& greps, const char* name, const std::string& value));

};



// Extern the shouldOutput function to be able to override it with a mock implementation

extern "C" bool shouldOutput(const std::vector<std::regex>& greps, const char* name, const std::string& value);



// Global variable to hold the mock object

MockShouldOutput* g_mockShouldOutput = nullptr;



// Override the shouldOutput function to call the mock object

extern "C" bool shouldOutput(const std::vector<std::regex>& greps, const char* name, const std::string& value) {

    return g_mockShouldOutput->shouldOutput(greps, name, value);

}



// Partial implementation of the class under test (version.cpp)

static void output(std::ostream& os, const std::vector<std::regex>& greps, const char* name, const std::string& value) {

    if (shouldOutput(greps, name, value)) os << name << "=" << value << '\n';

}



// Test fixture for the output function

class OutputTest_991 : public ::testing::Test {

protected:

    MockShouldOutput mockShouldOutput;

    std::ostringstream oss;



    void SetUp() override {

        g_mockShouldOutput = &mockShouldOutput;

    }



    void TearDown() override {

        g_mockShouldOutput = nullptr;

    }

};



// Test normal operation where shouldOutput returns true

TEST_F(OutputTest_991, NormalOperation_ShouldOutputTrue_991) {

    std::vector<std::regex> greps;

    const char* name = "VERSION";

    const std::string value = "1.2.3";



    EXPECT_CALL(mockShouldOutput, shouldOutput(::testing::Ref(greps), ::testing::StrEq(name), ::testing::StrEq(value)))

        .WillOnce(::testing::Return(true));



    output(oss, greps, name, value);

    EXPECT_EQ("VERSION=1.2.3\n", oss.str());

}



// Test normal operation where shouldOutput returns false

TEST_F(OutputTest_991, NormalOperation_ShouldOutputFalse_991) {

    std::vector<std::regex> greps;

    const char* name = "VERSION";

    const std::string value = "1.2.3";



    EXPECT_CALL(mockShouldOutput, shouldOutput(::testing::Ref(greps), ::testing::StrEq(name), ::testing::StrEq(value)))

        .WillOnce(::testing::Return(false));



    output(oss, greps, name, value);

    EXPECT_EQ("", oss.str());

}



// Test boundary condition with empty name and value

TEST_F(OutputTest_991, BoundaryCondition_EmptyNameAndValue_991) {

    std::vector<std::regex> greps;

    const char* name = "";

    const std::string value = "";



    EXPECT_CALL(mockShouldOutput, shouldOutput(::testing::Ref(greps), ::testing::StrEq(name), ::testing::StrEq(value)))

        .WillOnce(::testing::Return(true));



    output(oss, greps, name, value);

    EXPECT_EQ("=\n", oss.str());

}



// Test boundary condition with maximum length name and value

TEST_F(OutputTest_991, BoundaryCondition_MaxLengthNameAndValue_991) {

    std::vector<std::regex> greps;

    std::string name(512, 'a');

    std::string value(512, 'b');



    EXPECT_CALL(mockShouldOutput, shouldOutput(::testing::Ref(greps), ::testing::StrEq(name.c_str()), ::testing::StrEq(value)))

        .WillOnce(::testing::Return(true));



    output(oss, greps, name.c_str(), value);

    std::string expected = name + "=" + value + "\n";

    EXPECT_EQ(expected, oss.str());

}
