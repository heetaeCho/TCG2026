#include <gtest/gtest.h>

#include "StructElement.h"



class AttributeTest_1688 : public ::testing::Test {

protected:

    AttributeTest_1688() : attr(Type::UnknownType, nullptr) {}



    Attribute attr;

};



TEST_F(AttributeTest_1688, setHiddenSetsHiddenValue_1688) {

    EXPECT_FALSE(attr.isHidden());

    attr.setHidden(true);

    EXPECT_TRUE(attr.isHidden());

    attr.setHidden(false);

    EXPECT_FALSE(attr.isHidden());

}



TEST_F(AttributeTest_1688, isOkReturnsTrueByDefault_1688) {

    EXPECT_TRUE(attr.isOk());

}



TEST_F(AttributeTest_1688, getTypeReturnsUnknownTypeByDefault_1688) {

    EXPECT_EQ(attr.getType(), Type::UnknownType);

}



TEST_F(AttributeTest_1688, getOwnerReturnsDefaultOwner_1688) {

    // Assuming a default owner value, if any specific value is expected, it should be defined.

    EXPECT_EQ(attr.getOwner(), Owner::Undefined); 

}



TEST_F(AttributeTest_1688, getValueReturnsNullptrByDefault_1688) {

    EXPECT_EQ(attr.getValue(), nullptr);

}



TEST_F(AttributeTest_1688, getNameReturnsEmptyStringByDefault_1688) {

    EXPECT_STREQ(attr.getName(), "");

}



TEST_F(AttributeTest_1688, getRevisionReturnsZeroByDefault_1688) {

    EXPECT_EQ(attr.getRevision(), 0);

}



TEST_F(AttributeTest_1688, setRevisionUpdatesRevisionValue_1688) {

    attr.setRevision(42);

    EXPECT_EQ(attr.getRevision(), 42);

}



TEST_F(AttributeTest_1688, isHiddenReturnsFalseByDefault_1688) {

    EXPECT_FALSE(attr.isHidden());

}



TEST_F(AttributeTest_1688, getFormattedValueReturnsNullptrByDefault_1688) {

    EXPECT_EQ(attr.getFormattedValue(), nullptr);

}
