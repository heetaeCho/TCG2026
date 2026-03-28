// File: Value_GetObject_Test_54.cpp
#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <map>
#include <string>
#include <vector>

using namespace JsonBox;

class ValueGetObjectTest_54 : public ::testing::Test {};

// Normal operation: when the Value holds an object, getObject() returns that object.
TEST_F(ValueGetObjectTest_54, ReturnsObjectWhenTypeIsObject_54) {
    Object obj;
    obj["a"] = Value(1);
    obj["b"] = Value(std::string("x"));

    Value v(obj);
    const Object& got = v.getObject();

    ASSERT_EQ(2u, got.size());
    ASSERT_TRUE(got.at("a").isInteger());
    EXPECT_EQ(1, got.at("a").getInteger());
    ASSERT_TRUE(got.at("b").isString());
    EXPECT_EQ(std::string("x"), got.at("b").getString());
}

// Boundary: an empty object should be returned intact.
TEST_F(ValueGetObjectTest_54, ReturnsEmptyUserObjectIntact_54) {
    Object empty;
    Value v(empty);

    const Object& got = v.getObject();
    EXPECT_TRUE(got.empty());
}

// Exceptional/other types: when the Value is NOT an object, getObject() should
// return an empty object (by contract: no observable entries).
TEST_F(ValueGetObjectTest_54, ReturnsEmptyObjectForNonObjectTypes_54) {
    Value vStr(std::string("s"));
    Value vInt(42);
    Value vDbl(3.14);
    Value vBool(true);
    Array arr; arr.push_back(Value(7));
    Value vArr(arr);
    Value vNull; // default-constructed

    EXPECT_TRUE(vStr.getObject().empty());
    EXPECT_TRUE(vInt.getObject().empty());
    EXPECT_TRUE(vDbl.getObject().empty());
    EXPECT_TRUE(vBool.getObject().empty());
    EXPECT_TRUE(vArr.getObject().empty());
    EXPECT_TRUE(vNull.getObject().empty());
}

// Stability: calling getObject() repeatedly on the same instance should be stable.
// (We only check that the address of the returned reference is consistent for that instance.)
TEST_F(ValueGetObjectTest_54, SameReferenceOnRepeatedCalls_54) {
    Value vInt(123); // non-object
    auto* addr1 = &vInt.getObject();
    auto* addr2 = &vInt.getObject();
    EXPECT_EQ(addr1, addr2);

    Object obj; obj["k"] = Value(false);
    Value vObj(obj);
    auto* addr3 = &vObj.getObject();
    auto* addr4 = &vObj.getObject();
    EXPECT_EQ(addr3, addr4);
}

// Mutation via API: setObject should make getObject() reflect the provided object.
TEST_F(ValueGetObjectTest_54, SetObjectThenGetObjectMatches_54) {
    Value v(0); // start as non-object
    Object obj;
    obj["num"] = Value(10);
    obj["txt"] = Value("hi");

    v.setObject(obj);

    const Object& got = v.getObject();
    ASSERT_EQ(2u, got.size());
    ASSERT_TRUE(got.at("num").isInteger());
    EXPECT_EQ(10, got.at("num").getInteger());
    ASSERT_TRUE(got.at("txt").isString());
    EXPECT_EQ(std::string("hi"), got.at("txt").getString());
}

// Copy behavior: copying a Value that holds an object preserves observable object contents.
TEST_F(ValueGetObjectTest_54, CopyConstructedPreservesObject_54) {
    Object obj;
    obj["x"] = Value(1);
    obj["y"] = Value(2);

    Value original(obj);
    Value copy(original);

    const Object& got = copy.getObject();
    ASSERT_EQ(2u, got.size());
    EXPECT_TRUE(got.at("x").isInteger());
    EXPECT_EQ(1, got.at("x").getInteger());
    EXPECT_TRUE(got.at("y").isInteger());
    EXPECT_EQ(2, got.at("y").getInteger());
}
