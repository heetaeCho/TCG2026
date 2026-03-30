#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "parseargs.h"



// Mocking GooString for testing purposes

class MockGooString : public GooString {

public:

    MOCK_METHOD1(assign, void(const char*));

};



TEST_F(ParseArgsTest_2740, GrabArg_Flag_SetsTrueAndReturnsTrue_2740) {

    ArgDesc arg = {"-flag", argFlag, new bool(false), ""};

    int argc = 2;

    char *argv[] = {(char*)"program", (char*)"-flag"};

    

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

    EXPECT_TRUE(*((bool*)arg.val));

}



TEST_F(ParseArgsTest_2740, GrabArg_Int_ValidInput_SetsIntAndReturnsTrue_2740) {

    ArgDesc arg = {"-int", argInt, new int(0), ""};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-int", (char*)"123"};

    

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

    EXPECT_EQ(*((int*)arg.val), 123);

}



TEST_F(ParseArgsTest_2740, GrabArg_Int_InvalidInput_ReturnsFalse_2740) {

    ArgDesc arg = {"-int", argInt, new int(0), ""};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-int", (char*)"abc"};

    

    EXPECT_FALSE(grabArg(&arg, 1, &argc, argv));

}



TEST_F(ParseArgsTest_2740, GrabArg_FP_ValidInput_SetsFPAndReturnsTrue_2740) {

    ArgDesc arg = {"-fp", argFP, new double(0.0), ""};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-fp", (char*)"123.45"};

    

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

    EXPECT_DOUBLE_EQ(*((double*)arg.val), 123.45);

}



TEST_F(ParseArgsTest_2740, GrabArg_FP_InvalidInput_ReturnsFalse_2740) {

    ArgDesc arg = {"-fp", argFP, new double(0.0), ""};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-fp", (char*)"abc"};

    

    EXPECT_FALSE(grabArg(&arg, 1, &argc, argv));

}



TEST_F(ParseArgsTest_2740, GrabArg_String_ValidInput_SetsStringAndReturnsTrue_2740) {

    ArgDesc arg = {"-string", argString, new char[6], "", 6};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-string", (char*)"hello"};

    

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

    EXPECT_STREQ((const char*)arg.val, "hello");

}



TEST_F(ParseArgsTest_2740, GrabArg_String_OutOfBoundsInput_TruncatesAndReturnsTrue_2740) {

    ArgDesc arg = {"-string", argString, new char[6], "", 6};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-string", (char*)"hello_world"};

    

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

    EXPECT_STREQ((const char*)arg.val, "hell");

}



TEST_F(ParseArgsTest_2740, GrabArg_GooString_ValidInput_SetsGooStringAndReturnsTrue_2740) {

    MockGooString mockGooString;

    ArgDesc arg = {"-goostring", argGooString, &mockGooString, ""};

    int argc = 3;

    char *argv[] = {(char*)"program", (char*)"-goostring", (char*)"hello"};

    

    EXPECT_CALL(mockGooString, assign("hello")).Times(1);

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

}



TEST_F(ParseArgsTest_2740, GrabArg_Default_CallsFprintf_ReturnsTrue_2740) {

    ArgDesc arg = {"-default", (ArgKind)999, new bool(false), ""};

    int argc = 2;

    char *argv[] = {(char*)"program", (char*)"-default"};

    

    EXPECT_TRUE(grabArg(&arg, 1, &argc, argv));

}
