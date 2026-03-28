#include <gtest/gtest.h>

#include "Object.h"



class ObjectTest_93 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_93, GetReal_TypeIsReal_93) {

    Object obj(1.23);

    EXPECT_EQ(obj.getReal(), 1.23);

}



TEST_F(ObjectTest_93, GetReal_TypeIsNotReal_93) {

    Object obj("some_string");

    EXPECT_DEATH(obj.getReal(), ".*OBJECT_TYPE_CHECK\\(objReal\\).*");

}



TEST_F(ObjectTest_93, IsReal_ReturnsTrueForReal_93) {

    Object obj(1.23);

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_93, IsReal_ReturnsFalseForNonReal_93) {

    Object obj("some_string");

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_93, GetNum_TypeIsReal_93) {

    Object obj(1.23);

    bool ok = false;

    double result = obj.getNum(&ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 1.23);

}



TEST_F(ObjectTest_93, GetNum_TypeIsInt_93) {

    Object obj(42);

    bool ok = false;

    double result = obj.getNum(&ok);

    EXPECT_TRUE(ok);

    EXPECT_EQ(result, 42);

}



TEST_F(ObjectTest_93, GetNum_TypeIsNotNumber_93) {

    Object obj("some_string");

    bool ok = false;

    double result = obj.getNum(&ok);

    EXPECT_FALSE(ok);

    EXPECT_EQ(result, 0.0);

}
