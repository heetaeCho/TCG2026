#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



using namespace Exiv2;



class XmpdatumTest_1289 : public ::testing::Test {

protected:

    XmpKey::UniquePtr key;

    Value::UniquePtr value;

    Xmpdatum xmpDatum;



    void SetUp() override {

        key = std::make_unique<XmpKey>("Xmp.dc.title");

        value = std::make_unique<StringValue>(stringType);

        xmpDatum = Xmpdatum(*key, value.get());

    }

};



TEST_F(XmpdatumTest_1289, CountReturnsZeroWhenNoValueSet_1289) {

    Xmpdatum xmpDatumWithoutValue(*key, nullptr);

    EXPECT_EQ(xmpDatumWithoutValue.count(), 0U);

}



TEST_F(XmpdatumTest_1289, CountReturnsCorrectCountAfterSetValue_1289) {

    value->read("Sample Value");

    EXPECT_EQ(xmpDatum.count(), 1U);

}



TEST_F(XmpdatumTest_1289, CountDoesNotChangeWithInvalidValue_1289) {

    value->setDataArea(nullptr, 0);

    EXPECT_EQ(xmpDatum.count(), 0U);

}



TEST_F(XmpdatumTest_1289, CopyFunctionReturnsCorrectSize_1289) {

    byte buffer[10];

    value->read("Sample Value");

    size_t copied = xmpDatum.copy(buffer, littleEndian);

    EXPECT_EQ(copied, 12U); // "Sample Value" is 12 bytes long

}



TEST_F(XmpdatumTest_1289, WriteFunctionDoesNotThrow_1289) {

    std::ostringstream os;

    EXPECT_NO_THROW(xmpDatum.write(os, nullptr));

}



TEST_F(XmpdatumTest_1289, KeyReturnsCorrectValue_1289) {

    EXPECT_EQ(xmpDatum.key(), "Xmp.dc.title");

}



TEST_F(XmpdatumTest_1289, FamilyNameReturnsCorrectValue_1289) {

    EXPECT_STREQ(xmpDatum.familyName(), "Xmp");

}



TEST_F(XmpdatumTest_1289, GroupNameReturnsCorrectValue_1289) {

    EXPECT_EQ(xmpDatum.groupName(), "dc");

}



TEST_F(XmpdatumTest_1289, TagNameReturnsCorrectValue_1289) {

    EXPECT_EQ(xmpDatum.tagName(), "title");

}



TEST_F(XmpdatumTest_1289, TypeIdReturnsCorrectType_1289) {

    EXPECT_EQ(xmpDatum.typeId(), stringType);

}



TEST_F(XmpdatumTest_1289, TypeNameReturnsCorrectTypeName_1289) {

    EXPECT_STREQ(xmpDatum.typeName(), "String");

}



TEST_F(XmpdatumTest_1289, ToStringReturnsStringValue_1289) {

    value->read("Sample Value");

    EXPECT_EQ(xmpDatum.toString(), "Sample Value");

}
