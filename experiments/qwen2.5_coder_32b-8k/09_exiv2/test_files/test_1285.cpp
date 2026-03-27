#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/properties.hpp"



namespace {



using namespace Exiv2;



class XmpdatumTest_1285 : public ::testing::Test {

protected:

    XmpKey key;

    Value* value;

    Xmpdatum xmpDatum;



    XmpdatumTest_1285() 

        : key("Xmp.dc.title"), value(new StringValue("Sample Title")), xmpDatum(key, value) {}

    

    ~XmpdatumTest_1285() override {

        delete value;

    }

};



TEST_F(XmpdatumTest_1285, TagReturnsCorrectValue_1285) {

    EXPECT_EQ(xmpDatum.tag(), key.tag());

}



TEST_F(XmpdatumTest_1285, KeyReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.key(), key.key());

}



TEST_F(XmpdatumTest_1285, FamilyNameReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.familyName(), key.familyName());

}



TEST_F(XmpdatumTest_1285, GroupNameReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.groupName(), key.groupName());

}



TEST_F(XmpdatumTest_1285, TagNameReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.tagName(), key.tagName());

}



TEST_F(XmpdatumTest_1285, TagLabelReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.tagLabel(), key.tagLabel());

}



TEST_F(XmpdatumTest_1285, TagDescReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.tagDesc(), key.tagDesc());

}



TEST_F(XmpdatumTest_1285, TypeIdIsDefaultConstructed_1285) {

    EXPECT_NE(xmpDatum.typeId(), 0);

}



TEST_F(XmpdatumTest_1285, TypeNameIsCorrect_1285) {

    EXPECT_EQ(xmpDatum.typeName(), "String");

}



TEST_F(XmpdatumTest_1285, TypeSizeReturnsDefaultValue_1285) {

    EXPECT_GT(xmpDatum.typeSize(), 0);

}



TEST_F(XmpdatumTest_1285, CountReturnsDefaultValue_1285) {

    EXPECT_EQ(xmpDatum.count(), 1);

}



TEST_F(XmpdatumTest_1285, SizeReturnsExpectedValue_1285) {

    EXPECT_GT(xmpDatum.size(), 0);

}



TEST_F(XmpdatumTest_1285, ToStringReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.toString(), "Sample Title");

}



TEST_F(XmpdatumTest_1285, ToStringWithIndexReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.toString(0), "Sample Title");

}



TEST_F(XmpdatumTest_1285, ToInt64ThrowsForInvalidType_1285) {

    EXPECT_THROW(xmpDatum.toInt64(0), Error);

}



TEST_F(XmpdatumTest_1285, ToFloatThrowsForInvalidType_1285) {

    EXPECT_THROW(xmpDatum.toFloat(0), Error);

}



TEST_F(XmpdatumTest_1285, ToRationalThrowsForInvalidType_1285) {

    EXPECT_THROW(xmpDatum.toRational(0), Error);

}



TEST_F(XmpdatumTest_1285, GetValueReturnsNonNull_1285) {

    EXPECT_NE(xmpDatum.getValue(), nullptr);

}



TEST_F(XmpdatumTest_1285, ConstValueReturnsCorrectString_1285) {

    EXPECT_EQ(xmpDatum.value().toString(), "Sample Title");

}



TEST_F(XmpdatumTest_1285, CopyFunctionWorksForValidBuffer_1285) {

    byte buffer[100];

    ByteOrder byteOrder = littleEndian;

    size_t copiedSize = xmpDatum.copy(buffer, byteOrder);

    EXPECT_GT(copiedSize, 0);

}



TEST_F(XmpdatumTest_1285, WriteFunctionWritesToStream_1285) {

    std::ostringstream oss;

    const ExifData* metadata = nullptr; // Assuming no metadata context is needed for the test

    xmpDatum.write(oss, metadata);

    EXPECT_FALSE(oss.str().empty());

}



TEST_F(XmpdatumTest_1285, SetNewValueWithString_1285) {

    std::string newValue = "Updated Title";

    int result = xmpDatum.setValue(newValue);

    EXPECT_EQ(result, 0); // Assuming successful set returns 0

    EXPECT_EQ(xmpDatum.toString(), newValue);

}



TEST_F(XmpdatumTest_1285, SetNewValueWithPointer_1285) {

    Value* newValue = new StringValue("Another Title");

    xmpDatum.setValue(newValue);

    delete newValue; // The Xmpdatum should manage the memory after this point

    EXPECT_EQ(xmpDatum.toString(), "Another Title");

}



TEST_F(XmpdatumTest_1285, AssignmentOperatorWithString_1285) {

    std::string newValue = "Assignment Test";

    xmpDatum = newValue;

    EXPECT_EQ(xmpDatum.toString(), newValue);

}



TEST_F(XmpdatumTest_1285, CopyConstructorCreatesEqualObject_1285) {

    Xmpdatum copiedXmpDatum = xmpDatum;

    EXPECT_EQ(copiedXmpDatum.tag(), xmpDatum.tag());

    EXPECT_EQ(copiedXmpDatum.toString(), xmpDatum.toString());

}



TEST_F(XmpdatumTest_1285, AssignmentOperatorCreatesEqualObject_1285) {

    Xmpdatum newDatum(key, value);

    newDatum = xmpDatum;

    EXPECT_EQ(newDatum.tag(), xmpDatum.tag());

    EXPECT_EQ(newDatum.toString(), xmpDatum.toString());

}



} // namespace
