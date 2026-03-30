#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_88 : public ::testing::Test {

protected:

    Object objBool{true};

    Object objInt{42};

    Object objInt64{9223372036854775807LL};

    Object objNone{};

};



TEST_F(ObjectTest_88, IsIntOrInt64_ReturnsTrueForInt_88) {

    EXPECT_TRUE(objInt.isIntOrInt64());

}



TEST_F(ObjectTest_88, IsIntOrInt64_ReturnsTrueForInt64_88) {

    EXPECT_TRUE(objInt64.isIntOrInt64());

}



TEST_F(ObjectTest_88, IsIntOrInt64_ReturnsFalseForNone_88) {

    EXPECT_FALSE(objNone.isIntOrInt64());

}



TEST_F(ObjectTest_88, IsIntOrInt64_ReturnsFalseForBool_88) {

    EXPECT_FALSE(objBool.isIntOrInt64());

}
