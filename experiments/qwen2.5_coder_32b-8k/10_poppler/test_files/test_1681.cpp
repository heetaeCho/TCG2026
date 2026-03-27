#include <gtest/gtest.h>

#include "StructElement.h"



class AttributeTest : public ::testing::Test {

protected:

    Object mockObject;

};



TEST_F(AttributeTest_1681, GetType_ReturnsCorrectType_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_EQ(attr.getType(), Type::Color);

}



TEST_F(AttributeTest_1681, GetOwner_ReturnsDefaultOwner_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_EQ(static_cast<int>(attr.getOwner()), static_cast<int>(Attribute::Owner::Default));

}



TEST_F(AttributeTest_1681, IsOk_ReturnsTrueForValidAttribute_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_TRUE(attr.isOk());

}



TEST_F(AttributeTest_1681, GetValue_ReturnsCorrectValuePointer_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_EQ(attr.getValue(), &mockObject);

}



TEST_F(AttributeTest_1681, GetName_ReturnsEmptyStringForTypeConstructor_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_STREQ(attr.getName(), "");

}



TEST_F(AttributeTest_1681, GetRevision_ReturnsDefaultRevision_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_EQ(attr.getRevision(), 0u);

}



TEST_F(AttributeTest_1681, SetRevision_ChangesRevisionValue_1681) {

    Attribute attr(Type::Color, &mockObject);

    attr.setRevision(42u);

    EXPECT_EQ(attr.getRevision(), 42u);

}



TEST_F(AttributeTest_1681, IsHidden_ReturnsFalseByDefault_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_FALSE(attr.isHidden());

}



TEST_F(AttributeTest_1681, SetHidden_ChangesHiddenStatus_1681) {

    Attribute attr(Type::Color, &mockObject);

    attr.setHidden(true);

    EXPECT_TRUE(attr.isHidden());

}



TEST_F(AttributeTest_1681, GetFormattedValue_ReturnsNullByDefault_1681) {

    Attribute attr(Type::Color, &mockObject);

    EXPECT_EQ(attr.getFormattedValue(), nullptr);

}



TEST_F(AttributeTest_1681, SetFormattedValue_ChangesFormattedValue_1681) {

    Attribute attr(Type::Color, &mockObject);

    GooString formatted("test");

    attr.setFormattedValue(&formatted);

    EXPECT_STREQ(attr.getFormattedValue(), "test");

}
