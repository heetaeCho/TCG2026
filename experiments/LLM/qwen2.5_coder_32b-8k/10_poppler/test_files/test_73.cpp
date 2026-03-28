#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_73 : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup can be done here if necessary

    }



    void TearDown() override {

        // Cleanup can be done here if necessary

    }

};



TEST_F(ObjectTest_73, IsReal_ReturnsFalse_ForNonRealObject_73) {

    Object obj(1);  // Assuming objInt corresponds to integer type

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_73, IsReal_ReturnsTrue_ForRealObject_73) {

    Object obj(2.0);  // Using double constructor which should set type to objReal

    EXPECT_TRUE(obj.isReal());

}



TEST_F(ObjectTest_73, IsReal_ReturnsFalse_ForNullObject_73) {

    Object obj = Object::null();

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_73, IsReal_ReturnsFalse_ForEOFObject_73) {

    Object obj = Object::eof();

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_73, IsReal_ReturnsFalse_ForErrorObject_73) {

    Object obj = Object::error();

    EXPECT_FALSE(obj.isReal());

}



TEST_F(ObjectTest_73, IsReal_ReturnsFalse_ForNoneObject_73) {

    Object obj;  // Default constructor should set type to objNone

    EXPECT_FALSE(obj.isReal());

}
