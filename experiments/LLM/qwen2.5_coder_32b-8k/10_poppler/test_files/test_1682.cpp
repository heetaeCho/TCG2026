#include <gtest/gtest.h>

#include "StructElement.h"

#include <memory>



using namespace std;



class AttributeTest : public ::testing::Test {

protected:

    void SetUp() override {

        // Setup if needed

    }



    void TearDown() override {

        // Teardown if needed

    }

};



TEST_F(AttributeTest_1682, GetOwner_ReturnsCorrectValue_1682) {

    Owner expectedOwner = static_cast<Owner>(0); // Assuming default constructor sets some value

    Attribute attr(static_cast<Type>(0), nullptr);

    EXPECT_EQ(expectedOwner, attr.getOwner());

}



TEST_F(AttributeTest_1682, IsOk_ReturnsTrueForValidAttribute_1682) {

    Attribute attr(static_cast<Type>(0), nullptr);

    EXPECT_TRUE(attr.isOk());

}



TEST_F(AttributeTest_1682, GetType_ReturnsCorrectType_1682) {

    Type expectedType = static_cast<Type>(1); // Assuming we have a specific type

    Attribute attr(expectedType, nullptr);

    EXPECT_EQ(expectedType, attr.getType());

}



TEST_F(AttributeTest_1682, GetRevision_ReturnsZeroInitially_1682) {

    Attribute attr(static_cast<Type>(0), nullptr);

    EXPECT_EQ(0u, attr.getRevision());

}



TEST_F(AttributeTest_1682, SetRevision_SetsCorrectValue_1682) {

    unsigned int newRevision = 5;

    Attribute attr(static_cast<Type>(0), nullptr);

    attr.setRevision(newRevision);

    EXPECT_EQ(newRevision, attr.getRevision());

}



TEST_F(AttributeTest_1682, IsHidden_ReturnsFalseInitially_1682) {

    Attribute attr(static_cast<Type>(0), nullptr);

    EXPECT_FALSE(attr.isHidden());

}



TEST_F(AttributeTest_1682, SetHidden_SetsCorrectValue_1682) {

    bool newHidden = true;

    Attribute attr(static_cast<Type>(0), nullptr);

    attr.setHidden(newHidden);

    EXPECT_EQ(newHidden, attr.isHidden());

}



TEST_F(AttributeTest_1682, GetFormattedValue_ReturnsNullInitially_1682) {

    Attribute attr(static_cast<Type>(0), nullptr);

    EXPECT_EQ(nullptr, attr.getFormattedValue());

}



TEST_F(AttributeTest_1682, SetFormattedValue_SetsCorrectValue_1682) {

    unique_ptr<GooString> formattedStr = make_unique<GooString>("test");

    Attribute attr(static_cast<Type>(0), nullptr);

    attr.setFormattedValue(formattedStr.get());

    EXPECT_STREQ("test", attr.getFormattedValue());

}
