#include <gtest/gtest.h>

#include "TestProjects/poppler/poppler/Object.h"



class ObjectTest_75 : public ::testing::Test {

protected:

    ObjectTest_75() {}

    virtual ~ObjectTest_75() {}



    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_75, IsString_ReturnsTrueForStringType_75) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("test");

    Object obj(std::move(testString));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_75, IsString_ReturnsFalseForNonStringType_75) {

    Object obj(10);

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_75, IsString_BoundaryConditionEmptyString_75) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("");

    Object obj(std::move(testString));

    EXPECT_TRUE(obj.isString());

}



TEST_F(ObjectTest_75, IsString_ErrorCaseInvalidType_75) {

    Object obj(static_cast<ObjType>(99)); // Invalid type

    EXPECT_FALSE(obj.isString());

}



TEST_F(ObjectTest_75, GetType_ReturnsCorrectTypeForString_75) {

    std::unique_ptr<GooString> testString = std::make_unique<GooString>("test");

    Object obj(std::move(testString));

    EXPECT_EQ(obj.getType(), objString);

}



TEST_F(ObjectTest_75, GetType_ReturnsCorrectTypeForInt_75) {

    Object obj(10);

    EXPECT_EQ(obj.getType(), objInt);

}
