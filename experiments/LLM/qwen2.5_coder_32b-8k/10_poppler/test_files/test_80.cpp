#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_80 : public ::testing::Test {

protected:

    Object objDict;

    Object objNotDict;



    ObjectTest_80() : objDict(Object(objDict)), objNotDict(Object(objInt)) {}

};



TEST_F(ObjectTest_80, IsDict_ReturnsTrueForDict_80) {

    EXPECT_TRUE(objDict.isDict());

}



TEST_F(ObjectTest_80, IsDict_ReturnsFalseForNonDict_80) {

    EXPECT_FALSE(objNotDict.isDict());

}
