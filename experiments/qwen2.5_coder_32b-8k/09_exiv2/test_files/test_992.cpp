#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <vector>

#include <regex>

#include <sstream>



// Mocking the std::ostream to verify interactions

class MockOStream : public std::ostream {

public:

    using std::ostream::ostream;

    MOCK_METHOD(void, write, (const char*, std::streamsize), (override));

};



extern void output(std::ostream& os, const std::vector<std::regex>& greps, const char* name, int value);



TEST_F(OutputTest_992, NormalOperation_NoGrepMatch_992) {

    MockOStream mockOs;

    EXPECT_CALL(mockOs, write(_, _))

        .Times(1)

        .WillOnce([](const char* s, std::streamsize n) {

            EXPECT_EQ(std::string(s, n), "name=42");

        });



    output(mockOs, {}, "name", 42);

}



TEST_F(OutputTest_992, NormalOperation_GrepMatch_992) {

    MockOStream mockOs;

    std::vector<std::regex> greps = {std::regex("name=42")};

    EXPECT_CALL(mockOs, write(_, _))

        .Times(1)

        .WillOnce([](const char* s, std::streamsize n) {

            EXPECT_EQ(std::string(s, n), "name=42");

        });



    output(mockOs, greps, "name", 42);

}



TEST_F(OutputTest_992, BoundaryCondition_EmptyName_992) {

    MockOStream mockOs;

    EXPECT_CALL(mockOs, write(_, _))

        .Times(1)

        .WillOnce([](const char* s, std::streamsize n) {

            EXPECT_EQ(std::string(s, n), "=42");

        });



    output(mockOs, {}, "", 42);

}



TEST_F(OutputTest_992, BoundaryCondition_ZeroValue_992) {

    MockOStream mockOs;

    EXPECT_CALL(mockOs, write(_, _))

        .Times(1)

        .WillOnce([](const char* s, std::streamsize n) {

            EXPECT_EQ(std::string(s, n), "name=0");

        });



    output(mockOs, {}, "name", 0);

}



TEST_F(OutputTest_992, BoundaryCondition_MaxPathNameLength_992) {

    MockOStream mockOs;

    std::string longName(_MAX_PATH - 1, 'a'); // _MAX_PATH includes the null terminator

    EXPECT_CALL(mockOs, write(_, _))

        .Times(1)

        .WillOnce([longName](const char* s, std::streamsize n) {

            EXPECT_EQ(std::string(s, n), longName + "=42");

        });



    output(mockOs, {}, longName.c_str(), 42);

}



TEST_F(OutputTest_992, BoundaryCondition_MaxPathNameLengthExceeded_992) {

    MockOStream mockOs;

    std::string longName(_MAX_PATH, 'a'); // This should be truncated to _MAX_PATH - 1

    EXPECT_CALL(mockOs, write(_, _))

        .Times(1)

        .WillOnce([longName](const char* s, std::streamsize n) {

            EXPECT_EQ(std::string(s, n), longName.substr(0, _MAX_PATH - 2) + "=42"); // Truncated to fit within _MAX_PATH including null terminator

        });



    output(mockOs, {}, longName.c_str(), 42);

}
