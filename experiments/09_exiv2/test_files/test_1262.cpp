#include <gtest/gtest.h>

#include "exiv2/properties.hpp"



using namespace Exiv2;



class XmpKeyTest_1262 : public ::testing::Test {

protected:

    XmpKey key1;

    XmpKey key2;

    XmpKey key3;



    XmpKeyTest_1262()

        : key1("Xmp.dc.title"),

          key2("Xmp", "dc:title"),

          key3(key1) {}

};



TEST_F(XmpKeyTest_1262, FamilyName_ReturnsCorrectValue_1262) {

    EXPECT_STREQ(key1.familyName(), "Iptc");

    EXPECT_STREQ(key2.familyName(), "Iptc");

    EXPECT_STREQ(key3.familyName(), "Iptc");

}



TEST_F(XmpKeyTest_1262, Key_ReturnsCorrectValue_1262) {

    EXPECT_EQ(key1.key(), "Xmp.dc.title");

    EXPECT_EQ(key2.key(), "Xmp.dc:title");

    EXPECT_EQ(key3.key(), "Xmp.dc.title");

}



TEST_F(XmpKeyTest_1262, CopyConstructor_CreatesEqualObjects_1262) {

    EXPECT_EQ(key1.key(), key3.key());

    EXPECT_STREQ(key1.familyName(), key3.familyName());

}



TEST_F(XmpKeyTest_1262, AssignmentOperator_AssignsCorrectly_1262) {

    XmpKey key4;

    key4 = key1;

    EXPECT_EQ(key4.key(), "Xmp.dc.title");

    EXPECT_STREQ(key4.familyName(), "Iptc");

}



TEST_F(XmpKeyTest_1262, Clone_ReturnsEqualObject_1262) {

    XmpKey::UniquePtr clonedKey = key1.clone();

    EXPECT_EQ(clonedKey->key(), key1.key());

    EXPECT_STREQ(clonedKey->familyName(), key1.familyName());

}



TEST_F(XmpKeyTest_1262, GroupName_ReturnsEmptyString_1262) {

    EXPECT_TRUE(key1.groupName().empty());

    EXPECT_TRUE(key2.groupName().empty());

    EXPECT_TRUE(key3.groupName().empty());

}



TEST_F(XmpKeyTest_1262, TagName_ReturnsCorrectValue_1262) {

    EXPECT_EQ(key1.tagName(), "title");

    EXPECT_EQ(key2.tagName(), "title");

    EXPECT_EQ(key3.tagName(), "title");

}



TEST_F(XmpKeyTest_1262, TagLabel_ReturnsEmptyString_1262) {

    EXPECT_TRUE(key1.tagLabel().empty());

    EXPECT_TRUE(key2.tagLabel().empty());

    EXPECT_TRUE(key3.tagLabel().empty());

}



TEST_F(XmpKeyTest_1262, TagDesc_ReturnsEmptyString_1262) {

    EXPECT_TRUE(key1.tagDesc().empty());

    EXPECT_TRUE(key2.tagDesc().empty());

    EXPECT_TRUE(key3.tagDesc().empty());

}



TEST_F(XmpKeyTest_1262, Tag_ReturnsZero_1262) {

    EXPECT_EQ(key1.tag(), 0);

    EXPECT_EQ(key2.tag(), 0);

    EXPECT_EQ(key3.tag(), 0);

}



TEST_F(XmpKeyTest_1262, Namespace_ReturnsEmptyString_1262) {

    EXPECT_TRUE(key1.ns().empty());

    EXPECT_TRUE(key2.ns().empty());

    EXPECT_TRUE(key3.ns().empty());

}
