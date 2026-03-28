#include <gtest/gtest.h>

#include "Object.h"

#include <string>



class ObjectTest : public ::testing::Test {

protected:

    void SetUp() override {}

    void TearDown() override {}

};



TEST_F(ObjectTest_100, GetNameString_NameType_ReturnsCorrectName_100) {

    std::unique_ptr<GooString> name(new GooString("testName"));

    Object obj(objName, std::move(name));

    EXPECT_EQ(obj.getNameString(), "testName");

}



TEST_F(ObjectTest_100, GetNameString_StringType_ReturnsEmptyString_100) {

    std::unique_ptr<GooString> str(new GooString("testString"));

    Object obj(std::move(str));

    EXPECT_EQ(obj.getNameString(), "");

}



TEST_F(ObjectTest_100, GetNameString_EmptyName_ReturnsEmptyString_100) {

    std::unique_ptr<GooString> emptyName(new GooString(""));

    Object obj(objName, std::move(emptyName));

    EXPECT_EQ(obj.getNameString(), "");

}



TEST_F(ObjectTest_100, GetNameString_DefaultConstructor_ReturnsEmptyString_100) {

    Object obj;

    EXPECT_EQ(obj.getNameString(), "");

}



TEST_F(ObjectTest_100, IsName_MatchingName_ReturnsTrue_100) {

    std::unique_ptr<GooString> name(new GooString("testName"));

    Object obj(objName, std::move(name));

    EXPECT_TRUE(obj.isName("testName"));

}



TEST_F(ObjectTest_100, IsName_NonMatchingName_ReturnsFalse_100) {

    std::unique_ptr<GooString> name(new GooString("testName"));

    Object obj(objName, std::move(name));

    EXPECT_FALSE(obj.isName("otherName"));

}



TEST_F(ObjectTest_100, IsName_StringType_ReturnsFalse_100) {

    std::unique_ptr<GooString> str(new GooString("testString"));

    Object obj(std::move(str));

    EXPECT_FALSE(obj.isName("testString"));

}
