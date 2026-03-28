#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "parseargs.h"



// Mocking ArgDesc for testing purposes

struct ArgDesc {

    const char * arg;

    ArgKind kind;

    void * val;

    const char * usage;

};



TEST(findArgTest_2739, NormalOperation_2739) {

    const ArgDesc args[] = {

        {"--help", argFlagHelp, nullptr, "Show help"},

        {"--version", argFlagVersion, nullptr, "Show version"},

        {nullptr, argFlagDummy, nullptr, ""}

    };

    EXPECT_EQ(findArg(args, (char*)"--help"), &args[0]);

    EXPECT_EQ(findArg(args, (char*)"--version"), &args[1]);

}



TEST(findArgTest_2739, BoundaryConditions_2739) {

    const ArgDesc args[] = {

        {nullptr, argFlagDummy, nullptr, ""}

    };

    EXPECT_EQ(findArg(args, (char*)"--anything"), nullptr);

}



TEST(findArgTest_2739, ExceptionalOrErrorCases_2739) {

    const ArgDesc args[] = {

        {"--help", argFlagHelp, nullptr, "Show help"},

        {nullptr, argFlagDummy, nullptr, ""}

    };

    EXPECT_EQ(findArg(args, nullptr), nullptr);

}



TEST(findArgTest_2739, NonExistentArgument_2739) {

    const ArgDesc args[] = {

        {"--help", argFlagHelp, nullptr, "Show help"},

        {"--version", argFlagVersion, nullptr, "Show version"},

        {nullptr, argFlagDummy, nullptr, ""}

    };

    EXPECT_EQ(findArg(args, (char*)"--nonexistent"), nullptr);

}



TEST(findArgTest_2739, KindBoundaryCondition_2739) {

    const ArgDesc args[] = {

        {"--help", static_cast<ArgKind>(argFlagDummy - 1), nullptr, "Show help"},

        {nullptr, argFlagDummy, nullptr, ""}

    };

    EXPECT_EQ(findArg(args, (char*)"--help"), &args[0]);

}



TEST(findArgTest_2739, KindAboveBoundaryCondition_2739) {

    const ArgDesc args[] = {

        {"--help", static_cast<ArgKind>(argFlagDummy), nullptr, "Show help"},

        {nullptr, argFlagDummy, nullptr, ""}

    };

    EXPECT_EQ(findArg(args, (char*)"--help"), nullptr);

}
