#include "catch2/internal/catch_clara.hpp"
#include <gtest/gtest.h>
#include <string>
#include <vector>

using namespace Catch::Clara;

// Test fixture for Args class
class ArgsTest_401 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test: Construction from argc/argv with a single argument (just the exe name)
TEST_F(ArgsTest_401, ConstructFromArgcArgv_SingleArg_ExeNameCorrect_401) {
    const char* argv[] = {"myprogram"};
    int argc = 1;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef("myprogram"));
}

// Test: Construction from argc/argv with multiple arguments
TEST_F(ArgsTest_401, ConstructFromArgcArgv_MultipleArgs_ExeNameCorrect_401) {
    const char* argv[] = {"myprogram", "--flag", "value"};
    int argc = 3;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef("myprogram"));
}

// Test: Construction from initializer list with a single element
TEST_F(ArgsTest_401, ConstructFromInitializerList_SingleElement_ExeNameCorrect_401) {
    Args args({"myapp"});
    EXPECT_EQ(args.exeName(), Catch::StringRef("myapp"));
}

// Test: Construction from initializer list with multiple elements
TEST_F(ArgsTest_401, ConstructFromInitializerList_MultipleElements_ExeNameCorrect_401) {
    Args args({"myapp", "--verbose", "--output", "file.txt"});
    EXPECT_EQ(args.exeName(), Catch::StringRef("myapp"));
}

// Test: exeName returns the first argument from argv
TEST_F(ArgsTest_401, ExeNameReturnsFirstArgvElement_401) {
    const char* argv[] = {"/usr/bin/test_app", "-h"};
    int argc = 2;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef("/usr/bin/test_app"));
}

// Test: Construction with empty string as exe name
TEST_F(ArgsTest_401, ConstructWithEmptyExeName_401) {
    const char* argv[] = {""};
    int argc = 1;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef(""));
}

// Test: exeName from initializer list with empty string
TEST_F(ArgsTest_401, InitializerListEmptyExeName_401) {
    Args args({""});
    EXPECT_EQ(args.exeName(), Catch::StringRef(""));
}

// Test: Construction with path containing spaces
TEST_F(ArgsTest_401, ExeNameWithSpaces_401) {
    const char* argv[] = {"C:\\Program Files\\my app.exe", "--run"};
    int argc = 2;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef("C:\\Program Files\\my app.exe"));
}

// Test: exeName consistency - calling multiple times returns same value
TEST_F(ArgsTest_401, ExeNameConsistentAcrossMultipleCalls_401) {
    const char* argv[] = {"test_exe", "arg1"};
    int argc = 2;
    Args args(argc, argv);
    auto name1 = args.exeName();
    auto name2 = args.exeName();
    EXPECT_EQ(name1, name2);
}

// Test: Construction from initializer list - exe name is first element regardless of content
TEST_F(ArgsTest_401, InitializerListExeNameIsFirstElement_401) {
    Args args({"--not-an-exe", "real_arg"});
    EXPECT_EQ(args.exeName(), Catch::StringRef("--not-an-exe"));
}

// Test: Long exe name path
TEST_F(ArgsTest_401, LongExeNamePath_401) {
    const char* longPath = "/very/long/path/to/some/deeply/nested/directory/structure/executable";
    const char* argv[] = {longPath};
    int argc = 1;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef(longPath));
}

// Test: Many arguments, exeName still correct
TEST_F(ArgsTest_401, ManyArguments_ExeNameStillCorrect_401) {
    const char* argv[] = {"prog", "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8", "a9", "a10"};
    int argc = 11;
    Args args(argc, argv);
    EXPECT_EQ(args.exeName(), Catch::StringRef("prog"));
}
