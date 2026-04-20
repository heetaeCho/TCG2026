#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <sstream>

#include "JsonBox/Value.h"



using namespace JsonBox;

using ::testing::_;

using ::testing::Eq;



class ValueTest_67 : public ::testing::Test {

protected:

    std::ostringstream oss;

};



TEST_F(ValueTest_67, StringOutput_67) {

    Value value("testString");

    oss << value;

    EXPECT_EQ(oss.str(), "\"testString\"");

}



TEST_F(ValueTest_67, IntegerOutput_67) {

    Value value(123);

    oss << value;

    EXPECT_EQ(oss.str(), "123");

}



TEST_F(ValueTest_67, DoubleOutputPrecision_67) {

    double testValue = 1.234567890123456789;

    Value value(testValue);

    oss << value;

    EXPECT_EQ(oss.str(), "1.2345678901234568");

}



TEST_F(ValueTest_67, ObjectOutputEmpty_67) {

    Value::Object obj;

    Value value(obj);

    oss << value;

    EXPECT_EQ(oss.str(), "{}");

}



TEST_F(ValueTest_67, ArrayOutputEmpty_67) {

    Value::Array arr;

    Value value(arr);

    oss << value;

    EXPECT_EQ(oss.str(), "[]");

}



TEST_F(ValueTest_67, BooleanTrueOutput_67) {

    Value value(true);

    oss << value;

    EXPECT_EQ(oss.str(), "true");

}



TEST_F(ValueTest_67, BooleanFalseOutput_67) {

    Value value(false);

    oss << value;

    EXPECT_EQ(oss.str(), "false");

}



TEST_F(ValueTest_67, NullValueOutput_67) {

    Value value;

    oss << value;

    EXPECT_EQ(oss.str(), "null");

}



TEST_F(ValueTest_67, StringWithEscapeCharacters_67) {

    std::string input = "\"\\/\b\f\n\r\t";

    std::string expected = "\\\"\\\\/\\b\\f\\n\\r\\t";

    Value value(input);

    oss << value;

    EXPECT_EQ(oss.str(), "\"" + expected + "\"");

}



TEST_F(ValueTest_67, DoubleBoundaryConditionPositiveInfinity_67) {

    double positiveInfinity = std::numeric_limits<double>::infinity();

    Value value(positiveInfinity);

    oss << value;

    EXPECT_TRUE(oss.str() == "inf" || oss.str() == "1.#INF");

}



TEST_F(ValueTest_67, DoubleBoundaryConditionNegativeInfinity_67) {

    double negativeInfinity = -std::numeric_limits<double>::infinity();

    Value value(negativeInfinity);

    oss << value;

    EXPECT_TRUE(oss.str() == "-inf" || oss.str() == "-1.#INF");

}



TEST_F(ValueTest_67, DoubleBoundaryConditionNaN_67) {

    double nanValue = std::numeric_limits<double>::quiet_NaN();

    Value value(nanValue);

    oss << value;

    EXPECT_TRUE(oss.str() == "nan" || oss.str() == "-1.#IND");

}



TEST_F(ValueTest_67, StringBoundaryConditionEmptyString_67) {

    std::string input = "";

    Value value(input);

    oss << value;

    EXPECT_EQ(oss.str(), "\"\"");

}
