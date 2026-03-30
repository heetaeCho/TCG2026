#include <gtest/gtest.h>

#include "Function.h"



class PostScriptFunctionTest_385 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(PostScriptFunctionTest_385, GetCodeString_ReturnsValidPointer_385) {

    PostScriptFunction function(nullptr, nullptr);

    EXPECT_NE(function.getCodeString(), nullptr);

}



TEST_F(PostScriptFunctionTest_385, GetCodeString_ConsistentAcrossCalls_385) {

    PostScriptFunction function(nullptr, nullptr);

    const GooString* codeString1 = function.getCodeString();

    const GooString* codeString2 = function.getCodeString();

    EXPECT_EQ(codeString1, codeString2);

}



// Assuming isOk() can be used to check if the object is in a valid state

TEST_F(PostScriptFunctionTest_385, ObjectIsValidAfterConstruction_385) {

    PostScriptFunction function(nullptr, nullptr);

    EXPECT_TRUE(function.isOk());

}



// Boundary condition test for codeString length or content would require more context,

// but we can assume that if the object is valid, then getCodeString should return non-empty string

TEST_F(PostScriptFunctionTest_385, CodeStringIsNotEmptyIfValid_385) {

    PostScriptFunction function(nullptr, nullptr);

    if (function.isOk()) {

        EXPECT_FALSE(function.getCodeString()->isEmpty());

    }

}



// Assuming getType() returns an enum or specific value, we can test it

TEST_F(PostScriptFunctionTest_385, GetType_ReturnsExpectedType_385) {

    PostScriptFunction function(nullptr, nullptr);

    EXPECT_EQ(function.getType(), Function::type3); // Hypothetical type for PostScriptFunction

}



// Exceptional or error cases would require more context on how the class handles errors

// Since we cannot infer internal logic, we assume there are no observable exceptional cases through public interface



// Verification of external interactions is not possible without mockable dependencies
