#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "Object.h"



using namespace ::testing;



class ObjectTest_89 : public ::testing::Test {

protected:

    Object objNone;

    Object objNameA{ObjType::objName, std::string_view("example")};

};



TEST_F(ObjectTest_89, IsName_ReturnsTrueForMatchingName_89) {

    EXPECT_TRUE(objNameA.isName("example"));

}



TEST_F(ObjectTest_89, IsName_ReturnsFalseForNonMatchingName_89) {

    EXPECT_FALSE(objNameA.isName("non_example"));

}



TEST_F(ObjectTest_89, IsName_ReturnsFalseForNoneType_89) {

    EXPECT_FALSE(objNone.isName("example"));

}



TEST_F(ObjectTest_89, IsName_BoundaryConditionEmptyString_89) {

    Object objEmptyName{ObjType::objName, std::string_view("")};

    EXPECT_TRUE(objEmptyName.isName(""));

    EXPECT_FALSE(objEmptyName.isName("non_empty"));

}
