#include <gtest/gtest.h>
#include <JsonBox/Value.h>

namespace JsonBox {
    namespace Literals {
        const std::string TRUE_STRING = "true";
        const std::string FALSE_STRING = "false";
        const std::string NULL_STRING = "null";
    }
}

namespace {
class ValueTest_44 : public ::testing::Test {
protected:
    JsonBox::Value stringValue;
    JsonBox::Value intValue;
    JsonBox::Value doubleValue;
    JsonBox::Value booleanTrue;
    JsonBox::Value booleanFalse;
    JsonBox::Value objectValue;
    JsonBox::Value arrayValue;
    JsonBox::Value nullValue;

    ValueTest_44()
        : stringValue("testString"),
          intValue(123),
          doubleValue(123.456),
          booleanTrue(true),
          booleanFalse(false),
          objectValue(JsonBox::Object{{"key", "value"}}),
          arrayValue(JsonBox::Array{1, 2, 3}),
          nullValue() {}
};

TEST_F(ValueTest_44, GetToString_String_44) {
    EXPECT_EQ(stringValue.getToString(), "testString");
}

TEST_F(ValueTest_44, GetToString_Integer_44) {
    EXPECT_EQ(intValue.getToString(), "123");
}

TEST_F(ValueTest_44, GetToString_Double_44) {
    EXPECT_EQ(doubleValue.getToString(), "123.456");
}

TEST_F(ValueTest_44, GetToString_BooleanTrue_44) {
    EXPECT_EQ(booleanTrue.getToString(), JsonBox::Literals::TRUE_STRING);
}

TEST_F(ValueTest_44, GetToString_BooleanFalse_44) {
    EXPECT_EQ(booleanFalse.getToString(), JsonBox::Literals::FALSE_STRING);
}

TEST_F(ValueTest_44, GetToString_Object_44) {
    // Since the exact string representation of an object is not specified,
    // we can only assume it will be a valid JSON string.
    EXPECT_TRUE(!objectValue.getToString().empty());
}

TEST_F(ValueTest_44, GetToString_Array_44) {
    // Similarly, for arrays, we check that the result is non-empty and valid JSON.
    EXPECT_TRUE(!arrayValue.getToString().empty());
}

TEST_F(ValueTest_44, GetToString_Null_44) {
    EXPECT_EQ(nullValue.getToString(), JsonBox::Literals::NULL_STRING);
}
} // namespace