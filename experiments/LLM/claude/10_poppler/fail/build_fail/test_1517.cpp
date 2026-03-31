#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>

// Include necessary headers
#include "poppler/Object.h"
#include "poppler/Dict.h"
#include "poppler/XRef.h"

// Include the .cc file to access the static function
// This is a standard technique for testing file-static functions
#include "poppler/Form.cc"

class FieldLookupTest_1517 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test: Key found directly in the field dictionary
TEST_F(FieldLookupTest_1517, KeyFoundDirectlyInField_1517) {
    // Create a Dict with a known key
    Dict *dict = new Dict(nullptr);
    dict->add("TestKey", Object(42));

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "TestKey", &checker);

    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 42);

    dict->decRef();
}

// Test: Key not found in field and no Parent exists
TEST_F(FieldLookupTest_1517, KeyNotFoundNoParent_1517) {
    Dict *dict = new Dict(nullptr);
    dict->add("OtherKey", Object(10));

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "TestKey", &checker);

    EXPECT_TRUE(result.isNull());

    dict->decRef();
}

// Test: Key not found in field but found in parent (inline dict parent)
TEST_F(FieldLookupTest_1517, KeyFoundInInlineDictParent_1517) {
    Dict *parentDict = new Dict(nullptr);
    parentDict->add("TestKey", Object(99));

    Dict *childDict = new Dict(nullptr);
    childDict->add("OtherKey", Object(10));
    childDict->add("Parent", Object(parentDict));

    RefRecursionChecker checker;
    Object result = fieldLookup(childDict, "TestKey", &checker);

    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 99);

    childDict->decRef();
}

// Test: Key not found anywhere in hierarchy
TEST_F(FieldLookupTest_1517, KeyNotFoundInEntireHierarchy_1517) {
    Dict *parentDict = new Dict(nullptr);
    parentDict->add("SomeOtherKey", Object(55));

    Dict *childDict = new Dict(nullptr);
    childDict->add("AnotherKey", Object(10));
    childDict->add("Parent", Object(parentDict));

    RefRecursionChecker checker;
    Object result = fieldLookup(childDict, "TestKey", &checker);

    EXPECT_TRUE(result.isNull());

    childDict->decRef();
}

// Test: Empty dictionary returns null
TEST_F(FieldLookupTest_1517, EmptyDictReturnsNull_1517) {
    Dict *dict = new Dict(nullptr);

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "TestKey", &checker);

    EXPECT_TRUE(result.isNull());

    dict->decRef();
}

// Test: Key found in field overrides parent value
TEST_F(FieldLookupTest_1517, KeyInFieldOverridesParent_1517) {
    Dict *parentDict = new Dict(nullptr);
    parentDict->add("TestKey", Object(100));

    Dict *childDict = new Dict(nullptr);
    childDict->add("TestKey", Object(42));
    childDict->add("Parent", Object(parentDict));

    RefRecursionChecker checker;
    Object result = fieldLookup(childDict, "TestKey", &checker);

    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 42);

    childDict->decRef();
}

// Test: Multi-level parent hierarchy with inline dicts
TEST_F(FieldLookupTest_1517, KeyFoundInGrandparentInlineDict_1517) {
    Dict *grandparentDict = new Dict(nullptr);
    grandparentDict->add("TestKey", Object(200));

    Dict *parentDict = new Dict(nullptr);
    parentDict->add("OtherKey", Object(150));
    parentDict->add("Parent", Object(grandparentDict));

    Dict *childDict = new Dict(nullptr);
    childDict->add("AnotherKey", Object(10));
    childDict->add("Parent", Object(parentDict));

    RefRecursionChecker checker;
    Object result = fieldLookup(childDict, "TestKey", &checker);

    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 200);

    childDict->decRef();
}

// Test: Key is a string value
TEST_F(FieldLookupTest_1517, KeyWithStringValue_1517) {
    Dict *dict = new Dict(nullptr);
    dict->add("TestKey", Object(ObjType::objName, "TestValue"));

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "TestKey", &checker);

    EXPECT_TRUE(result.isName());
    EXPECT_STREQ(result.getName(), "TestValue");

    dict->decRef();
}

// Test: Key with boolean value
TEST_F(FieldLookupTest_1517, KeyWithBooleanValue_1517) {
    Dict *dict = new Dict(nullptr);
    dict->add("TestKey", Object(true));

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "TestKey", &checker);

    EXPECT_TRUE(result.isBool());
    EXPECT_TRUE(result.getBool());

    dict->decRef();
}

// Test: Key with real/double value
TEST_F(FieldLookupTest_1517, KeyWithRealValue_1517) {
    Dict *dict = new Dict(nullptr);
    dict->add("TestKey", Object(3.14));

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "TestKey", &checker);

    EXPECT_TRUE(result.isReal());
    EXPECT_DOUBLE_EQ(result.getReal(), 3.14);

    dict->decRef();
}

// Test: Looking up different keys from same dict
TEST_F(FieldLookupTest_1517, DifferentKeysFromSameDict_1517) {
    Dict *dict = new Dict(nullptr);
    dict->add("Key1", Object(1));
    dict->add("Key2", Object(2));
    dict->add("Key3", Object(3));

    RefRecursionChecker checker1;
    Object result1 = fieldLookup(dict, "Key1", &checker1);
    EXPECT_TRUE(result1.isInt());
    EXPECT_EQ(result1.getInt(), 1);

    RefRecursionChecker checker2;
    Object result2 = fieldLookup(dict, "Key2", &checker2);
    EXPECT_TRUE(result2.isInt());
    EXPECT_EQ(result2.getInt(), 2);

    RefRecursionChecker checker3;
    Object result3 = fieldLookup(dict, "Key3", &checker3);
    EXPECT_TRUE(result3.isInt());
    EXPECT_EQ(result3.getInt(), 3);

    dict->decRef();
}

// Test: Nonexistent key with no parent returns null object
TEST_F(FieldLookupTest_1517, NonexistentKeyReturnsNullObject_1517) {
    Dict *dict = new Dict(nullptr);
    dict->add("ExistingKey", Object(42));

    RefRecursionChecker checker;
    Object result = fieldLookup(dict, "NonExistentKey", &checker);

    EXPECT_TRUE(result.isNull());

    dict->decRef();
}
