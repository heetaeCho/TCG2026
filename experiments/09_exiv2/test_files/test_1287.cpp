#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/types.hpp"



using namespace Exiv2;



class XmpdatumTest_1287 : public ::testing::Test {

protected:

    XmpKey key;

    const Value* pValue;

    Xmpdatum xmpDatum;



    XmpdatumTest_1287()

        : key("Xmp.dc.title"), 

          pValue(nullptr), 

          xmpDatum(key, pValue) {}

};



TEST_F(XmpdatumTest_1287, TypeName_ReturnsValidString_1287) {

    const char* typeName = xmpDatum.typeName();

    EXPECT_TRUE(typeName != nullptr);

}



TEST_F(XmpdatumTest_1287, Key_ReturnsCorrectKey_1287) {

    std::string keyStr = xmpDatum.key();

    EXPECT_EQ(keyStr, "Xmp.dc.title");

}



TEST_F(XmpdatumTest_1287, FamilyName_ReturnsValidString_1287) {

    const char* familyName = xmpDatum.familyName();

    EXPECT_TRUE(familyName != nullptr);

}



TEST_F(XmpdatumTest_1287, GroupName_ReturnsValidString_1287) {

    std::string groupName = xmpDatum.groupName();

    EXPECT_TRUE(!groupName.empty());

}



TEST_F(XmpdatumTest_1287, TagName_ReturnsValidString_1287) {

    std::string tagName = xmpDatum.tagName();

    EXPECT_TRUE(!tagName.empty());

}



TEST_F(XmpdatumTest_1287, TagLabel_ReturnsValidString_1287) {

    std::string tagLabel = xmpDatum.tagLabel();

    EXPECT_TRUE(!tagLabel.empty());

}



TEST_F(XmpdatumTest_1287, TagDesc_ReturnsValidString_1287) {

    std::string tagDesc = xmpDatum.tagDesc();

    EXPECT_TRUE(!tagDesc.empty());

}



TEST_F(XmpdatumTest_1287, Tag_ReturnsNonZeroValue_1287) {

    uint16_t tag = xmpDatum.tag();

    EXPECT_NE(tag, 0);

}



TEST_F(XmpdatumTest_1287, TypeId_ReturnsValidTypeId_1287) {

    TypeId typeId = xmpDatum.typeId();

    EXPECT_NE(typeId, static_cast<TypeId>(-1));

}



TEST_F(XmpdatumTest_1287, TypeSize_ReturnsNonZeroValue_1287) {

    size_t typeSize = xmpDatum.typeSize();

    EXPECT_GT(typeSize, 0);

}



TEST_F(XmpdatumTest_1287, Count_ReturnsNonNegativeValue_1287) {

    size_t count = xmpDatum.count();

    EXPECT_GE(count, 0);

}



TEST_F(XmpdatumTest_1287, Size_ReturnsNonNegativeValue_1287) {

    size_t size = xmpDatum.size();

    EXPECT_GE(size, 0);

}



TEST_F(XmpdatumTest_1287, ToString_ReturnsValidString_1287) {

    std::string toStringResult = xmpDatum.toString();

    EXPECT_TRUE(!toStringResult.empty());

}



TEST_F(XmpdatumTest_1287, ToInt64_ReturnsZeroForDefault_1287) {

    int64_t toInt64Result = xmpDatum.toInt64(0);

    EXPECT_EQ(toInt64Result, 0);

}



TEST_F(XmpdatumTest_1287, ToFloat_ReturnsZeroForDefault_1287) {

    float toFloatResult = xmpDatum.toFloat(0);

    EXPECT_FLOAT_EQ(toFloatResult, 0.0f);

}



TEST_F(XmpdatumTest_1287, ToRational_ReturnsZeroNumeratorAndDenominator_1287) {

    Rational toRationalResult = xmpDatum.toRational(0);

    EXPECT_EQ(toRationalResult.first, 0);

    EXPECT_EQ(toRationalResult.second, 0);

}



TEST_F(XmpdatumTest_1287, GetValue_ReturnsNonNullPointer_1287) {

    Value::UniquePtr value = xmpDatum.getValue();

    EXPECT_TRUE(value != nullptr);

}



TEST_F(XmpdatumTest_1287, Value_ReturnsValidReference_1287) {

    const Value& valueRef = xmpDatum.value();

    EXPECT_TRUE(&valueRef != nullptr);

}
