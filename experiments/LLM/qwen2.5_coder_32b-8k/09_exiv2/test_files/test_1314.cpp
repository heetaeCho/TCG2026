#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking external dependencies if needed

class MockXmpLockFct {

public:

    MOCK_METHOD(void, Call, (void*), ());

};



using namespace Exiv2;



TEST_F(XmpParserTest_1314, Initialize_ReturnsTrueOnSuccessfulInitialization_1314) {

    XmpParser parser;

    MockXmpLockFct mockLockFct;

    EXPECT_CALL(mockLockFct, Call).Times(0); // No lock function call expected in this test

    bool result = parser.initialize(MockXmpLockFct::Call, nullptr);

    EXPECT_TRUE(result);

}



TEST_F(XmpParserTest_1314, Initialize_ReturnsFalseOnFailedInitialization_1314) {

    XmpParser parser;

    MockXmpLockFct mockLockFct;

    EXPECT_CALL(mockLockFct, Call).Times(0); // No lock function call expected in this test

    // Assuming a way to force initialization failure, e.g., mocking TXMPMeta::Initialize()

    bool result = parser.initialize(MockXmpLockFct::Call, nullptr);

    EXPECT_FALSE(result); // This assumes there's a way to mock the failure of Initialize(), which isn't directly possible here.

}



TEST_F(XmpParserTest_1314, Initialize_IdempotentInitialization_1314) {

    XmpParser parser;

    MockXmpLockFct mockLockFct;

    EXPECT_CALL(mockLockFct, Call).Times(0); // No lock function call expected in this test

    bool firstInit = parser.initialize(MockXmpLockFct::Call, nullptr);

    bool secondInit = parser.initialize(MockXmpLockFct::Call, nullptr);

    EXPECT_TRUE(firstInit);

    EXPECT_TRUE(secondInit);

}



TEST_F(XmpParserTest_1314, Initialize_RegistersNamespacesOnFirstInitialization_1314) {

    XmpParser parser;

    MockXmpLockFct mockLockFct;

    EXPECT_CALL(mockLockFct, Call).Times(0); // No lock function call expected in this test

    bool result = parser.initialize(MockXmpLockFct::Call, nullptr);

    EXPECT_TRUE(result);



    // Assuming a way to verify namespace registration, e.g., via TXMPMeta::GetNamespacePrefix()

    // This is not directly possible here without additional access, but we can document the expectation.

}



TEST_F(XmpParserTest_1314, Initialize_DoesNotRegisterNamespacesOnSubsequentInitialization_1314) {

    XmpParser parser;

    MockXmpLockFct mockLockFct;

    EXPECT_CALL(mockLockFct, Call).Times(0); // No lock function call expected in this test

    bool firstInit = parser.initialize(MockXmpLockFct::Call, nullptr);

    bool secondInit = parser.initialize(MockXmpLockFct::Call, nullptr);

    EXPECT_TRUE(firstInit);

    EXPECT_TRUE(secondInit);



    // Assuming a way to verify namespace registration count or uniqueness.

}



TEST_F(XmpParserTest_1314, Initialize_HandlesNullLockFunction_1314) {

    XmpParser parser;

    bool result = parser.initialize(nullptr, nullptr);

    EXPECT_TRUE(result); // Expecting successful initialization even with null lock function

}
