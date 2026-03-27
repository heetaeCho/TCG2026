#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup code if needed

    }



    void TearDown() override {

        // Teardown code if needed

    }

};



TEST_F(ObjectTest_2750, Constructor_Int64_NormalOperation_2750) {

    Object obj(12345LL);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), 12345LL);

}



TEST_F(ObjectTest_2750, Constructor_Int64_BoundaryCondition_MinValue_2750) {

    Object obj(LLONG_MIN);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), LLONG_MIN);

}



TEST_F(ObjectTest_2750, Constructor_Int64_BoundaryCondition_MaxValue_2750) {

    Object obj(LLONG_MAX);

    EXPECT_TRUE(obj.isInt64());

    EXPECT_EQ(obj.getInt64(), LLONG_MAX);

}



TEST_F(ObjectTest_2750, IsType_Functions_ForInt64_2750) {

    Object obj(12345LL);

    EXPECT_FALSE(obj.isBool());

    EXPECT_FALSE(obj.isInt());

    EXPECT_TRUE(obj.isInt64());

    EXPECT_FALSE(obj.isReal());

    EXPECT_FALSE(obj.isNum());

    EXPECT_FALSE(obj.isString());

    EXPECT_FALSE(obj.isHexString());

    EXPECT_FALSE(obj.isName());

    EXPECT_FALSE(obj.isNull());

    EXPECT_FALSE(obj.isArray());

    EXPECT_FALSE(obj.isDict());

    EXPECT_FALSE(obj.isStream());

    EXPECT_FALSE(obj.isRef());

    EXPECT_FALSE(obj.isCmd());

    EXPECT_FALSE(obj.isError());

    EXPECT_FALSE(obj.isEOF());

    EXPECT_FALSE(obj.isNone());

}



TEST_F(ObjectTest_2750, GetType_Function_ReturnsCorrectTypeForInt64_2750) {

    Object obj(12345LL);

    EXPECT_EQ(obj.getType(), objInt64);

}
