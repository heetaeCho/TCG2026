#include <gtest/gtest.h>
#include "JsonBox/Value.h"
using namespace JsonBox;

class ValueTest_29 : public ::testing::Test {
protected:
    Value value;
};

TEST_F(ValueTest_29, InitialTypeIsNull_29) {
    EXPECT_EQ(value.getType(), Value::NULL_VALUE);
}

TEST_F(ValueTest_29, OperatorBracketSetsObjectType_29) {
    value["key"] = "value";
    EXPECT_EQ(value.getType(), Value::OBJECT);
}

TEST_F(ValueTest_29, OperatorBracketReturnsReferenceToObjectValue_29) {
    Value& nestedValue = value["key"];
    nestedValue = 42;
    EXPECT_EQ(value.getObject().at("key").getInteger(), 42);
}

TEST_F(ValueTest_29, AccessingDifferentKeysCreatesMultipleEntries_29) {
    value["key1"] = "value1";
    value["key2"] = "value2";
    const auto& object = value.getObject();
    EXPECT_EQ(object.at("key1").getString(), "value1");
    EXPECT_EQ(object.at("key2").getString(), "value2");
}

TEST_F(ValueTest_29, AccessingSameKeyUpdatesExistingEntry_29) {
    value["key"] = "initial";
    value["key"] = "updated";
    EXPECT_EQ(value.getObject().at("key").getString(), "updated");
}