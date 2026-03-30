#include <gmock/gmock.h>

#include <gtest/gtest.h>

#include "catch2/reporters/catch_reporter_console.hpp"

#include "catch2/internal/catch_stringref.hpp"

#include <sstream>



using namespace Catch;

using namespace testing;



class MockStream : public IStream {

public:

    MOCK_METHOD(void, write, (std::string const&), (override));

};



class ConsoleReporterTest_763 : public Test {

protected:

    NiceMock<MockStream> mockStream;

    ReporterConfig config{CATCH_MOVE(mockStream)};

    ConsoleReporter reporter{CATCH_MOVE(config)};



    void SetUp() override {

        ON_CALL(mockStream, write(_)).WillByDefault(Invoke([](std::string const& str){

            std::cout << str; // For debugging purposes

        }));

    }

};



TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_NormalOperation_763) {

    StringRef unmatchedSpec("test_case");

    EXPECT_CALL(mockStream, write(StrEq("No test cases matched 'test_case'\n")));

    reporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_EmptyString_763) {

    StringRef unmatchedSpec("");

    EXPECT_CALL(mockStream, write(StrEq("No test cases matched ''\n")));

    reporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_LongString_763) {

    std::string longString(1024, 'a');

    StringRef unmatchedSpec(longString.c_str());

    EXPECT_CALL(mockStream, write(StrEq("No test cases matched '" + longString + "'\n")));

    reporter.noMatchingTestCases(unmatchedSpec);

}



TEST_F(ConsoleReporterTest_763, NoMatchingTestCases_SpecialCharacters_763) {

    StringRef unmatchedSpec("!@#$%^&*()_+");

    EXPECT_CALL(mockStream, write(StrEq("No test cases matched '!@#$%^&*()_+'\n")));

    reporter.noMatchingTestCases(unmatchedSpec);

}
