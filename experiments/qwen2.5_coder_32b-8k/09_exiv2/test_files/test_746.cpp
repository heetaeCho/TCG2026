#include <gtest/gtest.h>

#include "exiv2/exif.hpp"

#include "exiv2/tags.hpp"



using namespace Exiv2;



class ExifdatumTest_746 : public ::testing::Test {

protected:

    void SetUp() override {

        // Create a mock key for testing

        tagInfo_.tag_ = 0x9003; // Example tag value

        tagInfo_.name_ = "Exif.Image.Artist";

        tagInfo_.title_ = "Artist";

        tagInfo_.description_ = "The name of the person who created the image.";

        tagInfo_.typeName_ = "Ascii";

        tagInfo_.typeId_ = asciiString;

        tagInfo_.isShort_ = false;

        tagInfo_.isIfdPointer_ = false;

        key_ = std::make_unique<ExifKey>(tagInfo_);

        value_ = std::make_unique<Value>("Sample Artist");

        exifdatum_ = std::make_unique<Exifdatum>(*key_, value_.get());

    }



    TagInfo tagInfo_;

    std::unique_ptr<ExifKey> key_;

    std::unique_ptr<Value> value_;

    std::unique_ptr<Exifdatum> exifdatum_;

};



TEST_F(ExifdatumTest_746, TagLabel_ReturnsCorrectLabel_746) {

    EXPECT_EQ(exifdatum_->tagLabel(), "Artist");

}



TEST_F(ExifdatumTest_746, Key_ReturnsCorrectKey_746) {

    EXPECT_EQ(exifdatum_->key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_746, GroupName_ReturnsCorrectGroupName_746) {

    EXPECT_EQ(exifdatum_->groupName(), "Image");

}



TEST_F(ExifdatumTest_746, TagName_ReturnsCorrectTagName_746) {

    EXPECT_EQ(exifdatum_->tagName(), "Artist");

}



TEST_F(ExifdatumTest_746, FamilyName_ReturnsCorrectFamilyName_746) {

    EXPECT_EQ(exifdatum_->familyName(), "Exif");

}



TEST_F(ExifdatumTest_746, TagDesc_ReturnsCorrectTagDescription_746) {

    EXPECT_EQ(exifdatum_->tagDesc(), "The name of the person who created the image.");

}



TEST_F(ExifdatumTest_746, Tag_ReturnsCorrectTagValue_746) {

    EXPECT_EQ(exifdatum_->tag(), 0x9003);

}



TEST_F(ExifdatumTest_746, TypeId_ReturnsCorrectTypeId_746) {

    EXPECT_EQ(exifdatum_->typeId(), asciiString);

}



TEST_F(ExifdatumTest_746, TypeName_ReturnsCorrectTypeName_746) {

    EXPECT_EQ(exifdatum_->typeName(), "Ascii");

}



TEST_F(ExifdatumTest_746, ToString_ReturnsCorrectValueAsString_746) {

    EXPECT_EQ(exifdatum_->toString(), "Sample Artist");

}



TEST_F(ExifdatumTest_746, Value_ReturnsCorrectValue_746) {

    const Value& value = exifdatum_->value();

    std::string strValue;

    value.toString(strValue);

    EXPECT_EQ(strValue, "Sample Artist");

}



TEST_F(ExifdatumTest_746, SetValue_String_SetsNewValue_746) {

    exifdatum_->setValue("New Artist");

    const Value& value = exifdatum_->value();

    std::string strValue;

    value.toString(strValue);

    EXPECT_EQ(strValue, "New Artist");

}



TEST_F(ExifdatumTest_746, SetValue_ValuePointer_SetsNewValue_746) {

    auto newValue = std::make_unique<Value>("Another Artist");

    exifdatum_->setValue(newValue.get());

    const Value& value = exifdatum_->value();

    std::string strValue;

    value.toString(strValue);

    EXPECT_EQ(strValue, "Another Artist");

}



TEST_F(ExifdatumTest_746, Exifdatum_DefaultConstructor_ShouldInitializeCorrectly_746) {

    Exifdatum defaultExifdatum(*key_, value_.get());

    EXPECT_EQ(defaultExifdatum.tagLabel(), "Artist");

    EXPECT_EQ(defaultExifdatum.key(), "Exif.Image.Artist");

}



TEST_F(ExifdatumTest_746, Exifdatum_CopyConstructor_ShouldCopyCorrectly_746) {

    Exifdatum copyExifdatum(*exifdatum_);

    EXPECT_EQ(copyExifdatum.tagLabel(), exifdatum_->tagLabel());

    EXPECT_EQ(copyExifdatum.key(), exifdatum_->key());

}



TEST_F(ExifdatumTest_746, AssignmentOperator_ShouldAssignCorrectly_746) {

    Exifdatum other(*key_, value_.get());

    other = *exifdatum_;

    EXPECT_EQ(other.tagLabel(), exifdatum_->tagLabel());

    EXPECT_EQ(other.key(), exifdatum_->key());

}
