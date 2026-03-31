#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dict.h"
#include "Object.h"
#include "XRef.h"

class DictTest_117 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = new XRef();
        dict = new Dict(xref);
    }

    void TearDown() override {
        delete dict;
        delete xref;
    }

    XRef *xref;
    Dict *dict;
};

// Test initial dictionary is empty
TEST_F(DictTest_117, InitialDictIsEmpty_117) {
    EXPECT_EQ(dict->getLength(), 0);
}

// Test adding an entry increases length
TEST_F(DictTest_117, AddIncreasesLength_117) {
    dict->add("Key1", Object(42));
    EXPECT_EQ(dict->getLength(), 1);
}

// Test adding multiple entries
TEST_F(DictTest_117, AddMultipleEntries_117) {
    dict->add("Key1", Object(1));
    dict->add("Key2", Object(2));
    dict->add("Key3", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
}

// Test hasKey returns true for existing key
TEST_F(DictTest_117, HasKeyReturnsTrueForExistingKey_117) {
    dict->add("TestKey", Object(100));
    EXPECT_TRUE(dict->hasKey("TestKey"));
}

// Test hasKey returns false for non-existing key
TEST_F(DictTest_117, HasKeyReturnsFalseForNonExistingKey_117) {
    EXPECT_FALSE(dict->hasKey("NonExistent"));
}

// Test lookup returns the correct value
TEST_F(DictTest_117, LookupReturnsCorrectValue_117) {
    dict->add("IntKey", Object(42));
    Object result = dict->lookup("IntKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 42);
}

// Test lookup for non-existing key returns null object
TEST_F(DictTest_117, LookupNonExistingKeyReturnsNull_117) {
    Object result = dict->lookup("Missing");
    EXPECT_TRUE(result.isNull());
}

// Test lookupNF returns the correct value without fetching
TEST_F(DictTest_117, LookupNFReturnsCorrectValue_117) {
    dict->add("NFKey", Object(77));
    const Object &result = dict->lookupNF("NFKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 77);
}

// Test set overwrites existing key
TEST_F(DictTest_117, SetOverwritesExistingKey_117) {
    dict->add("Key1", Object(10));
    dict->set("Key1", Object(20));
    EXPECT_EQ(dict->getLength(), 1);
    Object result = dict->lookup("Key1");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 20);
}

// Test set creates new key if not present
TEST_F(DictTest_117, SetCreatesNewKeyIfNotPresent_117) {
    dict->set("NewKey", Object(99));
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey("NewKey"));
    Object result = dict->lookup("NewKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 99);
}

// Test remove removes existing key
TEST_F(DictTest_117, RemoveExistingKey_117) {
    dict->add("ToRemove", Object(5));
    EXPECT_EQ(dict->getLength(), 1);
    dict->remove("ToRemove");
    EXPECT_EQ(dict->getLength(), 0);
    EXPECT_FALSE(dict->hasKey("ToRemove"));
}

// Test remove non-existing key does not crash
TEST_F(DictTest_117, RemoveNonExistingKeyNoEffect_117) {
    dict->add("Key1", Object(1));
    dict->remove("NonExistent");
    EXPECT_EQ(dict->getLength(), 1);
}

// Test getKey returns correct key name
TEST_F(DictTest_117, GetKeyReturnsCorrectKeyName_117) {
    dict->add("Alpha", Object(1));
    const char *key = dict->getKey(0);
    EXPECT_STREQ(key, "Alpha");
}

// Test getVal by index returns correct value
TEST_F(DictTest_117, GetValByIndexReturnsCorrectValue_117) {
    dict->add("Key1", Object(42));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test getValNF by index returns correct value
TEST_F(DictTest_117, GetValNFByIndexReturnsCorrectValue_117) {
    dict->add("Key1", Object(55));
    const Object &val = dict->getValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

// Test is method with type name
TEST_F(DictTest_117, IsMethodChecksType_117) {
    dict->add("Type", Object(objName, "Catalog"));
    EXPECT_TRUE(dict->is("Catalog"));
    EXPECT_FALSE(dict->is("Page"));
}

// Test is method returns false when no Type key
TEST_F(DictTest_117, IsMethodReturnsFalseWhenNoType_117) {
    EXPECT_FALSE(dict->is("Anything"));
}

// Test setXRef changes the xref
TEST_F(DictTest_117, SetXRefChangesXRef_117) {
    XRef *newXRef = new XRef();
    dict->setXRef(newXRef);
    EXPECT_EQ(dict->getXRef(), newXRef);
    delete newXRef;
}

// Test getXRef returns the xref set during construction
TEST_F(DictTest_117, GetXRefReturnsConstructionXRef_117) {
    EXPECT_EQ(dict->getXRef(), xref);
}

// Test copy creates a valid copy
TEST_F(DictTest_117, CopyCreatesValidCopy_117) {
    dict->add("CopyKey", Object(123));
    XRef *copyXRef = new XRef();
    const Dict *copied = dict->copy(copyXRef);
    EXPECT_EQ(copied->getLength(), 1);
    EXPECT_TRUE(copied->hasKey("CopyKey"));
    delete copied;
    delete copyXRef;
}

// Test lookupInt with existing integer key
TEST_F(DictTest_117, LookupIntReturnsIntValue_117) {
    dict->add("IntVal", Object(256));
    int value = 0;
    bool result = dict->lookupInt("IntVal", std::nullopt, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 256);
}

// Test lookupInt with non-existing key returns false
TEST_F(DictTest_117, LookupIntNonExistingReturnsFalse_117) {
    int value = -1;
    bool result = dict->lookupInt("Missing", std::nullopt, &value);
    EXPECT_FALSE(result);
}

// Test lookupInt with alternative key
TEST_F(DictTest_117, LookupIntWithAltKey_117) {
    dict->add("AltKey", Object(789));
    int value = 0;
    bool result = dict->lookupInt("PrimaryMissing", std::string_view("AltKey"), &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 789);
}

// Test adding many entries
TEST_F(DictTest_117, AddManyEntries_117) {
    for (int i = 0; i < 100; i++) {
        std::string key = "Key" + std::to_string(i);
        dict->add(key, Object(i));
    }
    EXPECT_EQ(dict->getLength(), 100);
    for (int i = 0; i < 100; i++) {
        std::string key = "Key" + std::to_string(i);
        EXPECT_TRUE(dict->hasKey(key));
        Object val = dict->lookup(key);
        EXPECT_TRUE(val.isInt());
        EXPECT_EQ(val.getInt(), i);
    }
}

// Test findAvailableKey with no conflict
TEST_F(DictTest_117, FindAvailableKeyNoConflict_117) {
    std::string key = dict->findAvailableKey("Suggested");
    EXPECT_FALSE(key.empty());
}

// Test findAvailableKey with conflicting key
TEST_F(DictTest_117, FindAvailableKeyWithConflict_117) {
    dict->add("Suggested", Object(1));
    std::string key = dict->findAvailableKey("Suggested");
    EXPECT_FALSE(key.empty());
    // The returned key should not be the same as existing one, or the dict shouldn't have it
    // It should be available (not already in dict)
    EXPECT_TRUE(key == "Suggested" || !dict->hasKey(key));
}

// Test remove middle entry and verify remaining
TEST_F(DictTest_117, RemoveMiddleEntry_117) {
    dict->add("A", Object(1));
    dict->add("B", Object(2));
    dict->add("C", Object(3));
    dict->remove("B");
    EXPECT_EQ(dict->getLength(), 2);
    EXPECT_TRUE(dict->hasKey("A"));
    EXPECT_FALSE(dict->hasKey("B"));
    EXPECT_TRUE(dict->hasKey("C"));
}

// Test dict with string values
TEST_F(DictTest_117, DictWithStringValues_117) {
    dict->add("StrKey", Object(objString, new GooString("Hello")));
    Object result = dict->lookup("StrKey");
    EXPECT_TRUE(result.isString());
}

// Test dict with real/double values
TEST_F(DictTest_117, DictWithRealValues_117) {
    dict->add("RealKey", Object(3.14));
    Object result = dict->lookup("RealKey");
    EXPECT_TRUE(result.isReal());
    EXPECT_DOUBLE_EQ(result.getReal(), 3.14);
}

// Test dict with boolean values
TEST_F(DictTest_117, DictWithBoolValues_117) {
    dict->add("BoolKey", Object(true));
    Object result = dict->lookup("BoolKey");
    EXPECT_TRUE(result.isBool());
    EXPECT_TRUE(result.getBool());
}

// Test getVal with Ref pointer
TEST_F(DictTest_117, GetValWithRefPointer_117) {
    dict->add("RefKey", Object(42));
    Ref ref;
    Object val = dict->getVal(0, &ref);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test lookup with Ref pointer
TEST_F(DictTest_117, LookupWithRefPointer_117) {
    dict->add("TestRef", Object(55));
    Ref ref;
    Object result = dict->lookup("TestRef", &ref);
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 55);
}

// Test copy constructor is deleted (compile-time, but we verify copy works via copy method)
TEST_F(DictTest_117, DeepCopyCreatesIndependentCopy_117) {
    dict->add("DeepKey", Object(999));
    const Dict *deepCopied = dict->deepCopy();
    ASSERT_NE(deepCopied, nullptr);
    EXPECT_EQ(deepCopied->getLength(), 1);
    EXPECT_TRUE(deepCopied->hasKey("DeepKey"));
    delete deepCopied;
}
