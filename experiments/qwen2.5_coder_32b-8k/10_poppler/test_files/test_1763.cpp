#include <gtest/gtest.h>

#include "Object.h"



// Assuming the function to be tested is in a namespace or class, we'll wrap it for testing purposes.

class StructElement {

public:

    static bool isRubyAlignName(Object *value) { 

        return ::isRubyAlignName(value); 

    }

};



TEST_F(StructElementTest_1763, IsRubyAlignName_Start_1763) {

    Object obj("Start");

    EXPECT_TRUE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_End_1763) {

    Object obj("End");

    EXPECT_TRUE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_Center_1763) {

    Object obj("Center");

    EXPECT_TRUE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_Justify_1763) {

    Object obj("Justify");

    EXPECT_TRUE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_Distribute_1763) {

    Object obj("Distribute");

    EXPECT_TRUE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_Other_1763) {

    Object obj("Other");

    EXPECT_FALSE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_EmptyString_1763) {

    Object obj("");

    EXPECT_FALSE(StructElement::isRubyAlignName(&obj));

}



TEST_F(StructElementTest_1763, IsRubyAlignName_NullObject_1763) {

    Object obj;

    EXPECT_FALSE(StructElement::isRubyAlignName(&obj));

}
