#include <gtest/gtest.h>

#include "StructElement.h"



class AttributeTest_1684 : public ::testing::Test {

protected:

    Object* mockObject = nullptr; // Assuming Object is a known type in your system



    void SetUp() override {

        mockObject = new Object(); // Initialize mockObject if needed

    }



    void TearDown() override {

        delete mockObject; // Clean up mockObject

    }

};



TEST_F(AttributeTest_1684, ConstructorWithTypeName_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_EQ(attr.getType(), Type::UserProperty);

}



TEST_F(AttributeTest_1684, ConstructorWithName_1684) {

    GooString name("testName");

    Attribute attr(std::move(name), mockObject);

    EXPECT_STREQ(attr.getName(), "testName");

}



TEST_F(AttributeTest_1684, IsOk_ReturnsTrue_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_TRUE(attr.isOk());

}



TEST_F(AttributeTest_1684, GetType_ReturnsCorrectType_1684) {

    Attribute attr(Type::Author, mockObject);

    EXPECT_EQ(attr.getType(), Type::Author);

}



TEST_F(AttributeTest_1684, GetOwner_ReturnsDefaultOwner_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_EQ(attr.getOwner(), Owner::None); // Assuming default owner is None

}



TEST_F(AttributeTest_1684, GetValue_ReturnsProvidedValue_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_EQ(attr.getValue(), mockObject);

}



TEST_F(AttributeTest_1684, GetName_UserPropertyReturnsName_1684) {

    GooString name("testName");

    Attribute attr(std::move(name), mockObject);

    EXPECT_STREQ(attr.getName(), "testName");

}



TEST_F(AttributeTest_1684, GetRevision_DefaultIsZero_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_EQ(attr.getRevision(), 0u);

}



TEST_F(AttributeTest_1684, SetRevision_ChangesRevision_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    attr.setRevision(5);

    EXPECT_EQ(attr.getRevision(), 5u);

}



TEST_F(AttributeTest_1684, IsHidden_DefaultIsFalse_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_FALSE(attr.isHidden());

}



TEST_F(AttributeTest_1684, SetHidden_ChangesHiddenState_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    attr.setHidden(true);

    EXPECT_TRUE(attr.isHidden());

}



TEST_F(AttributeTest_1684, GetFormattedValue_DefaultIsNull_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    EXPECT_EQ(attr.getFormattedValue(), nullptr);

}



TEST_F(AttributeTest_1684, SetFormattedValue_ChangesFormattedValue_1684) {

    Attribute attr(Type::UserProperty, mockObject);

    GooString formatted("formattedText");

    attr.setFormattedValue(&formatted);

    EXPECT_STREQ(attr.getFormattedValue(), "formattedText");

}
