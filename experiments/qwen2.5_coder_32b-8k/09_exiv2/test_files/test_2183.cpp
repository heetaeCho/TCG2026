#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "exiv2/tags.hpp"

#include "exiv2/metadatum.hpp"



using namespace Exiv2;



// Fixture for ExifKey tests

class ExifKeyTest_2183 : public ::testing::Test {

protected:

    ExifKey key;

};



TEST_F(ExifKeyTest_2183, ConstructorWithString_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.key(), "SomeKey");

}



TEST_F(ExifKeyTest_2183, CopyConstructor_2183) {

    ExifKey original("OriginalKey");

    ExifKey copy(original);

    EXPECT_EQ(copy.key(), "OriginalKey");

}



TEST_F(ExifKeyTest_2183, AssignmentOperator_2183) {

    ExifKey key1("Key1");

    ExifKey key2("Key2");

    key2 = key1;

    EXPECT_EQ(key2.key(), "Key1");

}



TEST_F(ExifKeyTest_2183, FamilyName_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_STREQ(key.familyName(), "Exif");

}



TEST_F(ExifKeyTest_2183, GroupName_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.groupName(), "");

}



TEST_F(ExifKeyTest_2183, TagName_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.tagName(), "");

}



TEST_F(ExifKeyTest_2183, TagLabel_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.tagLabel(), "");

}



TEST_F(ExifKeyTest_2183, TagDesc_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.tagDesc(), "");

}



TEST_F(ExifKeyTest_2183, Tag_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.tag(), 0);

}



TEST_F(ExifKeyTest_2183, DefaultTypeId_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.defaultTypeId(), undefined);

}



TEST_F(ExifKeyTest_2183, IfdId_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.ifdId(), ifdIdNotSet);

}



TEST_F(ExifKeyTest_2183, Index_Default_2183) {

    ExifKey key("SomeKey");

    EXPECT_EQ(key.idx(), 0);

}



TEST_F(ExifKeyTest_2183, SetIndex_Positive_2183) {

    ExifKey key("SomeKey");

    key.setIdx(5);

    EXPECT_EQ(key.idx(), 5);

}



TEST_F(ExifKeyTest_2183, Clone_ReturnsNewInstance_2183) {

    ExifKey original("OriginalKey");

    auto clone = original.clone();

    EXPECT_NE(&original, clone.get());

    EXPECT_EQ(clone->key(), "OriginalKey");

}
