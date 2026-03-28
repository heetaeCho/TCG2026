#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_87 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForNonInt64Type_87) {

    Object obj(ObjType::objInt);

    EXPECT_FALSE(obj.isInt64());

}



TEST_F(ObjectTest_87, IsInt64_ReturnsTrueForInt64Type_87) {

    Object obj(123LL); // Using long long constructor

    EXPECT_TRUE(obj.isInt64());

}



TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForNullObject_87) {

    Object obj = Object::null();

    EXPECT_FALSE(obj.isInt64());

}



TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForErrorObject_87) {

    Object obj = Object::error();

    EXPECT_FALSE(obj.isInt64());

}



TEST_F(ObjectTest_87, IsInt64_ReturnsFalseForEofObject_87) {

    Object obj = Object::eof();

    EXPECT_FALSE(obj.isInt64());

}
