#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/Catch2/src/catch2/internal/catch_clara.hpp"



using namespace Catch::Clara;



class ExeNameTest : public ::testing::Test {

protected:

    std::string testString;

    ExeName exeNameRef;

    ExeName exeNameLambda;



    ExeNameTest() 

        : testString("test_executable"), 

          exeNameRef(testString), 

          exeNameLambda([](std::string& ref) { ref = "lambda_executable"; }) {}

};



TEST_F(ExeNameTest_1098, ConstructorWithReference_ShouldStoreReference_1098) {

    EXPECT_EQ(exeNameRef.name(), testString);

}



TEST_F(ExeNameTest_1098, ConstructorWithLambda_ShouldSetCorrectValue_1098) {

    std::string lambdaString;

    ExeName exeNameLambda([&lambdaString](std::string& ref) { ref = "lambda_executable"; });

    EXPECT_EQ(exeNameLambda.name(), "lambda_executable");

}



TEST_F(ExeNameTest_1098, SetMethod_ShouldUpdateName_1098) {

    std::string newName = "new_name";

    exeNameRef.set(newName);

    EXPECT_EQ(exeNameRef.name(), newName);

}



TEST_F(ExeNameTest_1098, NameMethod_DefaultConstructor_ShouldReturnDefaultExecutableName_1098) {

    ExeName defaultExeName;

    EXPECT_EQ(defaultExeName.name(), "<executable>");

}



TEST_F(ExeNameTest_1098, ParseMethod_UnusedParameters_ShouldReturnSuccess_1098) {

    Detail::TokenStream tokens; // Assuming TokenStream is default-constructible and doesn't affect the test

    auto result = exeNameRef.parse("unused", tokens);

    EXPECT_TRUE(result.ok());

}



TEST_F(ExeNameTest_1098, ParseMethod_ModifiedReference_ShouldNotAffectStoredName_1098) {

    Detail::TokenStream tokens;

    std::string originalName = testString;

    exeNameRef.parse("modified", tokens);

    EXPECT_EQ(exeNameRef.name(), originalName);

}
