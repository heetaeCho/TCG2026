#include <gtest/gtest.h>

#include "Object.h"



using namespace std;



// Mock Object class if needed for external collaborators

class MockObject : public Object {

public:

    MOCK_METHOD(bool, isName, (std::string_view nameA), (const, override));

};



TEST(isBorderStyleNameTest_1756, ValidBorderStyles_1756) {

    MockObject obj;

    EXPECT_CALL(obj, isName("None")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Hidden")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Dotted")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Dashed")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Solid")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Double")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Groove")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Ridge")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Inset")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Outset")).WillOnce(testing::Return(true));



    EXPECT_TRUE(isBorderStyleName(&obj));

}



TEST(isBorderStyleNameTest_1756, InvalidBorderStyles_1756) {

    MockObject obj;

    EXPECT_CALL(obj, isName("None")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Hidden")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Dotted")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Dashed")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Solid")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Double")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Groove")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Ridge")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Inset")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Outset")).WillOnce(testing::Return(false));



    EXPECT_FALSE(isBorderStyleName(&obj));

}



TEST(isBorderStyleNameTest_1756, MixedBorderStyles_1756) {

    MockObject obj;

    EXPECT_CALL(obj, isName("None")).WillOnce(testing::Return(true));

    EXPECT_CALL(obj, isName("Hidden")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Dotted")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Dashed")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Solid")).WillOnce(testing::Return(true));



    EXPECT_TRUE(isBorderStyleName(&obj));

}



TEST(isBorderStyleNameTest_1756, SingleValidBorderStyle_1756) {

    MockObject obj;

    EXPECT_CALL(obj, isName("None")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Hidden")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Dotted")).WillOnce(testing::Return(true));



    EXPECT_TRUE(isBorderStyleName(&obj));

}



TEST(isBorderStyleNameTest_1756, SingleInvalidBorderStyle_1756) {

    MockObject obj;

    EXPECT_CALL(obj, isName("None")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Hidden")).WillOnce(testing::Return(false));

    EXPECT_CALL(obj, isName("Dotted")).WillOnce(testing::Return(false));



    EXPECT_FALSE(isBorderStyleName(&obj));

}
