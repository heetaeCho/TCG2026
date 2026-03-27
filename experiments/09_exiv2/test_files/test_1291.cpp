#include <gtest/gtest.h>

#include "exiv2/xmp_exiv2.hpp"

#include "exiv2/value.hpp"



namespace Exiv2 {

    class MockXmpKey : public XmpKey {

    public:

        MOCK_CONST_METHOD0(clone, XmpKey::UniquePtr());

        MOCK_CONST_METHOD0(familyName, const char*());

        MOCK_CONST_METHOD0(groupName, std::string());

        MOCK_CONST_METHOD0(tagName, std::string());

        MOCK_CONST_METHOD0(tagLabel, std::string());

        MOCK_CONST_METHOD0(tagDesc, std::string());

    };



    class MockValue : public Value {

    public:

        using Value::Value;

        MOCK_METHOD1(read, int(const byte*, size_t));

        MOCK_METHOD1(read, int(const std::string&));

        MOCK_METHOD2(setDataArea, int(const byte*, size_t));

        MOCK_METHOD1(copy, size_t(byte*, ByteOrder));

        MOCK_METHOD0(count, size_t());

        MOCK_METHOD0(size, size_t());

        MOCK_METHOD1(write, const std::ostream&(std::ostream&));

        MOCK_CONST_METHOD0(toString, std::string());

        MOCK_CONST_METHOD1(toString, std::string(size_t));

        MOCK_CONST_METHOD1(toInt64, int64_t(size_t));

        MOCK_CONST_METHOD1(toUint32, uint32_t(size_t));

        MOCK_CONST_METHOD1(toFloat, float(size_t));

        MOCK_CONST_METHOD1(toRational, Rational(size_t));

        MOCK_CONST_METHOD0(sizeDataArea, size_t());

        MOCK_CONST_METHOD0(dataArea, DataBuf());

        MOCK_METHOD0(clone_, const Value*());

    };

}



using namespace Exiv2;



class XmpdatumTest : public ::testing::Test {

protected:

    MockXmpKey mock_key;

    MockValue mock_value;



    Xmpdatum xmpDatumUnderTest;



    XmpdatumTest() : xmpDatumUnderTest(mock_key, &mock_value) {}

};



TEST_F(XmpdatumTest_1291, ToString_ReturnsEmptyStringWhenNoValueSet_1291) {

    EXPECT_CALL(mock_value, toString()).WillOnce(::testing::Return(""));

    EXPECT_EQ(xmpDatumUnderTest.toString(), "");

}



TEST_F(XmpdatumTest_1291, ToString_ReturnsStringValueFromValue_1291) {

    EXPECT_CALL(mock_value, toString()).WillOnce(::testing::Return("test_value"));

    EXPECT_EQ(xmpDatumUnderTest.toString(), "test_value");

}



TEST_F(XmpdatumTest_1291, SetStringValue_SetsNewValue_1291) {

    EXPECT_CALL(mock_value, read("new_value")).WillOnce(::testing::Return(0));

    xmpDatumUnderTest.setValue("new_value");

    // No direct verification since internal state is not accessible.

}



TEST_F(XmpdatumTest_1291, SetPointerValue_SetsNewValue_1291) {

    MockValue new_mock_value(TypeId::invalid);

    EXPECT_CALL(new_mock_value, clone()).WillOnce(::testing::Return(nullptr));

    xmpDatumUnderTest.setValue(&new_mock_value);

    // No direct verification since internal state is not accessible.

}



TEST_F(XmpdatumTest_1291, Key_ReturnsKeyFromImpl_1291) {

    EXPECT_CALL(mock_key, clone()).WillOnce(::testing::Return(nullptr));

    xmpDatumUnderTest.key();

    // Verification through mock call expectation

}



TEST_F(XmpdatumTest_1291, FamilyName_ReturnsFamilyNameFromKey_1291) {

    EXPECT_CALL(mock_key, familyName()).WillOnce(::testing::Return("XMP"));

    EXPECT_EQ(xmpDatumUnderTest.familyName(), "XMP");

}



TEST_F(XmpdatumTest_1291, GroupName_ReturnsGroupNameFromKey_1291) {

    EXPECT_CALL(mock_key, groupName()).WillOnce(::testing::Return("XMP.Group"));

    EXPECT_EQ(xmpDatumUnderTest.groupName(), "XMP.Group");

}



TEST_F(XmpdatumTest_1291, TagName_ReturnsTagNameFromKey_1291) {

    EXPECT_CALL(mock_key, tagName()).WillOnce(::testing::Return("Tag"));

    EXPECT_EQ(xmpDatumUnderTest.tagName(), "Tag");

}



TEST_F(XmpdatumTest_1291, TagLabel_ReturnsTagLabelFromKey_1291) {

    EXPECT_CALL(mock_key, tagLabel()).WillOnce(::testing::Return("Tag Label"));

    EXPECT_EQ(xmpDatumUnderTest.tagLabel(), "Tag Label");

}



TEST_F(XmpdatumTest_1291, TagDesc_ReturnsTagDescriptionFromKey_1291) {

    EXPECT_CALL(mock_key, tagDesc()).WillOnce(::testing::Return("Tag Description"));

    EXPECT_EQ(xmpDatumUnderTest.tagDesc(), "Tag Description");

}
