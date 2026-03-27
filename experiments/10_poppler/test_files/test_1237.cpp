#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_1237 : public ::testing::Test {

protected:

    Object objectWithName;

    Object objectWithDifferentName;



    ObjectTest_1237() : objectWithName(Object(objName, "testName")), 

                        objectWithDifferentName(Object(objName, "anotherName")) {}

};



TEST_F(ObjectTest_1237, IsName_ReturnsTrueForMatchingName_1237) {

    EXPECT_TRUE(objectWithName.isName("testName"));

}



TEST_F(ObjectTest_1237, IsName_ReturnsFalseForNonMatchingName_1237) {

    EXPECT_FALSE(objectWithName.isName("anotherName"));

}



TEST_F(ObjectTest_1237, IsName_CaseSensitiveComparison_1237) {

    EXPECT_FALSE(objectWithName.isName("TESTNAME"));

}



TEST_F(ObjectTest_1237, IsName_ReturnsFalseForDifferentType_1237) {

    Object objectNotAName(Object(objInt, 42));

    EXPECT_FALSE(objectNotAName.isName("testName"));

}



TEST_F(ObjectTest_1237, IsName_BoundaryCondition_EmptyString_1237) {

    Object emptyNameObject(Object(objName, ""));

    EXPECT_TRUE(emptyNameObject.isName(""));

}



TEST_F(ObjectTest_1237, IsName_BoundaryCondition_LongString_1237) {

    std::string longName(1024, 'a');

    Object longNameObject(Object(objName, longName));

    EXPECT_TRUE(longNameObject.isName(longName));

}
