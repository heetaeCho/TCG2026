#include <gtest/gtest.h>

#include "Function.h"

#include <memory>



using namespace ::testing;



// Mock Stream class if needed for parsing code or getting tokens

class MockStream : public Stream {

public:

    MOCK_METHOD(int, getChar, (), (override));

    MOCK_METHOD(void, ungetChar, (int), (override));

    // Add more methods as necessary

};



TEST_F(PostScriptFunctionTest_383, GetTypeReturnsPostScript_383) {

    PostScriptFunction function(nullptr, nullptr);

    EXPECT_EQ(function.getType(), Type::PostScript);

}



TEST_F(PostScriptFunctionTest_383, CopyCreatesNewInstance_383) {

    PostScriptFunction original(nullptr, nullptr);

    std::unique_ptr<Function> copy = original.copy();

    EXPECT_NE(&original, copy.get());

    EXPECT_EQ(copy->getType(), Type::PostScript);

}



TEST_F(PostScriptFunctionTest_383, IsOkReturnsTrueForValidFunction_383) {

    PostScriptFunction function(nullptr, nullptr);

    EXPECT_TRUE(function.isOk()); // Assuming a newly created instance is valid

}



TEST_F(PostScriptFunctionTest_383, GetCodeStringReturnsNonNullPointer_383) {

    PostScriptFunction function(nullptr, nullptr);

    const GooString* codeString = function.getCodeString();

    EXPECT_NE(codeString, nullptr); // Assuming getCodeString always returns a non-null pointer

}



// Boundary conditions and exceptional cases are not directly testable without more information

// about the expected behavior or error states. The provided interface does not specify these.

```


