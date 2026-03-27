#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <cstdio>

#include <cstring>



// Mocking stderr to capture printUsage output

class StderrMock {

public:

    virtual ~StderrMock() = default;

    MOCK_METHOD1(Print, void(const std::string&));

};



StderrMock* g_stderr_mock = nullptr;



extern "C" {

    int fprintf(FILE *stream, const char *format, ...) {

        if (stream == stderr) {

            va_list args;

            va_start(args, format);

            char buffer[1024];

            vsnprintf(buffer, sizeof(buffer), format, args);

            va_end(args);

            g_stderr_mock->Print(buffer);

            return strlen(buffer);

        }

        return ::fprintf(stream, format, args);

    }

}



#include "parseargs.h"



TEST_F(ParseArgsTest_2738, PrintUsage_NoOtherArgs_2738) {

    ArgDesc args[] = {

        {"-a", argInt, nullptr, "argument a"},

        {"-b", argFP, nullptr, "argument b"},

        {nullptr, argFlag, nullptr, nullptr}

    };



    testing::StrictMock<StderrMock> mock;

    g_stderr_mock = &mock;



    EXPECT_CALL(mock, Print("Usage: program [options]\n")).Times(1);

    EXPECT_CALL(mock, Print(" -a <int>: argument a\n")).Times(1);

    EXPECT_CALL(mock, Print(" -b <fp>: argument b\n")).Times(1);



    printUsage("program", nullptr, args);

}



TEST_F(ParseArgsTest_2738, PrintUsage_WithOtherArgs_2738) {

    ArgDesc args[] = {

        {"-a", argInt, nullptr, "argument a"},

        {"-b", argFP, nullptr, "argument b"},

        {nullptr, argFlag, nullptr, nullptr}

    };



    testing::StrictMock<StderrMock> mock;

    g_stderr_mock = &mock;



    EXPECT_CALL(mock, Print("Usage: program [options] other\n")).Times(1);

    EXPECT_CALL(mock, Print(" -a <int>: argument a\n")).Times(1);

    EXPECT_CALL(mock, Print(" -b <fp>: argument b\n")).Times(1);



    printUsage("program", "other", args);

}



TEST_F(ParseArgsTest_2738, PrintUsage_EmptyArgs_2738) {

    ArgDesc args[] = {

        {nullptr, argFlag, nullptr, nullptr}

    };



    testing::StrictMock<StderrMock> mock;

    g_stderr_mock = &mock;



    EXPECT_CALL(mock, Print("Usage: program [options]\n")).Times(1);



    printUsage("program", nullptr, args);

}



TEST_F(ParseArgsTest_2738, PrintUsage_ArgKindString_2738) {

    ArgDesc args[] = {

        {"-s", argString, nullptr, "string argument"},

        {nullptr, argFlag, nullptr, nullptr}

    };



    testing::StrictMock<StderrMock> mock;

    g_stderr_mock = &mock;



    EXPECT_CALL(mock, Print("Usage: program [options]\n")).Times(1);

    EXPECT_CALL(mock, Print(" -s <string>: string argument\n")).Times(1);



    printUsage("program", nullptr, args);

}



TEST_F(ParseArgsTest_2738, PrintUsage_ArgKindFlag_2738) {

    ArgDesc args[] = {

        {"-f", argFlag, nullptr, "flag argument"},

        {nullptr, argFlag, nullptr, nullptr}

    };



    testing::StrictMock<StderrMock> mock;

    g_stderr_mock = &mock;



    EXPECT_CALL(mock, Print("Usage: program [options]\n")).Times(1);

    EXPECT_CALL(mock, Print(" -f : flag argument\n")).Times(1);



    printUsage("program", nullptr, args);

}
