#include <gtest/gtest.h>

#include "catch2/internal/catch_clara.hpp"

#include <string>



using namespace Catch::Clara;



TEST_F(ArgsTest_401, ConstructorWithArgcArgv_ExeNameSetCorrectly_401) {

    int argc = 3;

    const char* argv[] = {"test_exe", "arg1", "arg2"};

    Args args(argc, argv);

    EXPECT_EQ(args.exeName(), StringRef("test_exe"));

}



TEST_F(ArgsTest_401, ConstructorWithInitializerList_ExeNameSetCorrectly_401) {

    std::initializer_list<StringRef> args = {"test_exe", "arg1", "arg2"};

    Args argsList(args);

    EXPECT_EQ(argsList.exeName(), StringRef("test_exe"));

}



TEST_F(ArgsTest_401, ConstructorWithSingleArgument_ExeNameSetCorrectly_401) {

    std::initializer_list<StringRef> singleArg = {"single_arg"};

    Args singleArgList(singleArg);

    EXPECT_EQ(singleArgList.exeName(), StringRef("single_arg"));

}



TEST_F(ArgsTest_401, ConstructorWithEmptyInitializerList_ExeNameEmpty_401) {

    std::initializer_list<StringRef> emptyArgs;

    Args emptyArgsList(emptyArgs);

    EXPECT_EQ(emptyArgsList.exeName(), StringRef(""));

}
