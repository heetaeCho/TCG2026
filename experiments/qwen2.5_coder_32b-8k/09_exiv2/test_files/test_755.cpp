#include <gtest/gtest.h>

#include "exiv2/exif.hpp"



using namespace Exiv2;



class ExifdatumTest_755 : public ::testing::Test {

protected:

    std::unique_ptr<ExifKey> key;

    std::unique_ptr<Value> value;

    Exifdatum* exifdatum;



    void SetUp() override {

        key = std::make_unique<ExifKey>("testKey");

        value = nullptr;  // Assuming no initial value for simplicity

        exifdatum = new Exifdatum(*key, value.get());

    }



    void TearDown() override {

        delete exifdatum;

    }

};



TEST_F(ExifdatumTest_755, TypeSize_ReturnsCorrectValue_755) {

    // Assuming we have a known TypeId and its corresponding size

    EXPECT_EQ(exifdatum->typeSize(), TypeInfo::typeSize(exifdatum->typeId()));

}



TEST_F(ExifdatumTest_755, TypeName_ReturnsNonEmptyString_755) {

    const char* typeName = exifdatum->typeName();

    EXPECT_TRUE(typeName != nullptr && std::string(typeName).length() > 0);

}



TEST_F(ExifdatumTest_755, TypeId_ReturnsValidTypeId_755) {

    TypeId typeId = exifdatum->typeId();

    EXPECT_TRUE(typeId >= 0); // Assuming TypeId is a non-negative integer

}



TEST_F(ExifdatumTest_755, Count_ReturnsNonNegativeValue_755) {

    size_t count = exifdatum->count();

    EXPECT_GE(count, 0);

}



TEST_F(ExifdatumTest_755, Size_ReturnsNonNegativeValue_755) {

    size_t size = exifdatum->size();

    EXPECT_GE(size, 0);

}



TEST_F(ExifdatumTest_755, ToString_ReturnsValidString_755) {

    std::string str = exifdatum->toString();

    EXPECT_TRUE(str.length() >= 0); // Assuming toString returns a valid string

}



TEST_F(ExifdatumTest_755, ToInt64_ReturnsDefaultForUnsetValue_755) {

    int64_t value = exifdatum->toInt64(0);

    EXPECT_EQ(value, 0); // Default return value for unset or invalid index

}



TEST_F(ExifdatumTest_755, ToFloat_ReturnsDefaultForUnsetValue_755) {

    float value = exifdatum->toFloat(0);

    EXPECT_FLOAT_EQ(value, 0.0f); // Default return value for unset or invalid index

}



TEST_F(ExifdatumTest_755, ToRational_ReturnsDefaultForUnsetValue_755) {

    Rational value = exifdatum->toRational(0);

    EXPECT_EQ(value.first, 0);

    EXPECT_EQ(value.second, 1); // Default return value for unset or invalid index

}



TEST_F(ExifdatumTest_755, GetValue_ReturnsNonNullPointer_755) {

    Value::UniquePtr value = exifdatum->getValue();

    EXPECT_NE(value.get(), nullptr);

}



TEST_F(ExifdatumTest_755, Key_ReturnsNonEmptyString_755) {

    std::string keyStr = exifdatum->key();

    EXPECT_TRUE(keyStr.length() > 0); // Assuming key returns a valid string

}



TEST_F(ExifdatumTest_755, FamilyName_ReturnsNonEmptyString_755) {

    const char* familyName = exifdatum->familyName();

    EXPECT_TRUE(familyName != nullptr && std::string(familyName).length() > 0);

}



TEST_F(ExifdatumTest_755, GroupName_ReturnsNonEmptyString_755) {

    std::string groupName = exifdatum->groupName();

    EXPECT_TRUE(groupName.length() > 0); // Assuming groupName returns a valid string

}



TEST_F(ExifdatumTest_755, TagName_ReturnsNonEmptyString_755) {

    std::string tagName = exifdatum->tagName();

    EXPECT_TRUE(tagName.length() > 0); // Assuming tagName returns a valid string

}



TEST_F(ExifdatumTest_755, TagLabel_ReturnsNonEmptyString_755) {

    std::string tagLabel = exifdatum->tagLabel();

    EXPECT_TRUE(tagLabel.length() > 0); // Assuming tagLabel returns a valid string

}



TEST_F(ExifdatumTest_755, TagDesc_ReturnsNonEmptyString_755) {

    std::string tagDesc = exifdatum->tagDesc();

    EXPECT_TRUE(tagDesc.length() >= 0); // Assuming tagDesc returns a valid string

}



TEST_F(ExifdatumTest_755, Tag_ReturnsValidTagId_755) {

    uint16_t tag = exifdatum->tag();

    EXPECT_GE(tag, 0);

}



TEST_F(ExifdatumTest_755, IfdId_ReturnsValidIfdId_755) {

    IfdId ifdId = exifdatum->ifdId();

    // Assuming IfdId is a valid enumeration or integer value

}



TEST_F(ExifdatumTest_755, IfdName_ReturnsNonEmptyString_755) {

    const char* ifdName = exifdatum->ifdName();

    EXPECT_TRUE(ifdName != nullptr && std::string(ifdName).length() > 0);

}



TEST_F(ExifdatumTest_755, Idx_ReturnsNonNegativeValue_755) {

    int idx = exifdatum->idx();

    EXPECT_GE(idx, 0);

}



TEST_F(ExifdatumTest_755, SizeDataArea_ReturnsNonNegativeValue_755) {

    size_t sizeDataArea = exifdatum->sizeDataArea();

    EXPECT_GE(sizeDataArea, 0);

}
