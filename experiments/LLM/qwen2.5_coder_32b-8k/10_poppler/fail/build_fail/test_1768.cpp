#include <gtest/gtest.h>

#include "./TestProjects/poppler/poppler/Object.h"



using namespace poppler;



class ObjectTest_1768 : public ::testing::Test {

protected:

    Object *obj;

    

    void SetUp() override {

        obj = nullptr;

    }



    void TearDown() override {

        delete obj;

    }

};



TEST_F(ObjectTest_1768, IsFieldCheckedName_ReturnsTrueForOn_1768) {

    obj = new Object("on");

    EXPECT_TRUE(isFieldCheckedName(obj));

}



TEST_F(ObjectTest_1768, IsFieldCheckedName_ReturnsTrueForOff_1768) {

    obj = new Object("off");

    EXPECT_TRUE(isFieldCheckedName(obj));

}



TEST_F(ObjectTest_1768, IsFieldCheckedName_ReturnsTrueForNeutral_1768) {

    obj = new Object("neutral");

    EXPECT_TRUE(isFieldCheckedName(obj));

}



TEST_F(ObjectTest_1768, IsFieldCheckedName_ReturnsFalseForOtherNames_1768) {

    obj = new Object("other");

    EXPECT_FALSE(isFieldCheckedName(obj));

}



TEST_F(ObjectTest_1768, IsFieldCheckedName_ReturnsFalseForNonNameType_1768) {

    obj = new Object(42);

    EXPECT_FALSE(isFieldCheckedName(obj));

}
