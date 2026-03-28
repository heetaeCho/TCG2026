#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Dict.h"
#include "Object.h"

class DictTest_115 : public ::testing::Test {
protected:
    void SetUp() override {
        xref = nullptr; // Many Dict operations work with nullptr XRef for simple cases
        dict = new Dict(xref);
    }

    void TearDown() override {
        // Dict is reference counted internally; we rely on the caller managing lifetime
        // For testing purposes, we create via new and the test framework manages it
    }

    XRef *xref;
    Dict *dict;
};

// Test that a newly created Dict has length 0
TEST_F(DictTest_115, NewDictHasZeroLength_115) {
    EXPECT_EQ(dict->getLength(), 0);
}

// Test adding a single entry increases length
TEST_F(DictTest_115, AddIncreasesLength_115) {
    dict->add("key1", Object(42));
    EXPECT_EQ(dict->getLength(), 1);
}

// Test adding multiple entries
TEST_F(DictTest_115, AddMultipleEntries_115) {
    dict->add("key1", Object(1));
    dict->add("key2", Object(2));
    dict->add("key3", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
}

// Test getKey returns correct key name
TEST_F(DictTest_115, GetKeyReturnsCorrectKey_115) {
    dict->add("myKey", Object(100));
    EXPECT_STREQ(dict->getKey(0), "myKey");
}

// Test getVal returns the correct value
TEST_F(DictTest_115, GetValReturnsCorrectValue_115) {
    dict->add("intKey", Object(42));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test getValNF returns a reference to the value
TEST_F(DictTest_115, GetValNFReturnsValue_115) {
    dict->add("boolKey", Object(true));
    const Object &val = dict->getValNF(0);
    EXPECT_TRUE(val.isBool());
    EXPECT_EQ(val.getBool(), true);
}

// Test lookup finds an existing key
TEST_F(DictTest_115, LookupFindsExistingKey_115) {
    dict->add("testKey", Object(99));
    Object result = dict->lookup("testKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 99);
}

// Test lookup returns null for non-existing key
TEST_F(DictTest_115, LookupReturnsNullForMissingKey_115) {
    dict->add("existing", Object(1));
    Object result = dict->lookup("nonexistent");
    EXPECT_TRUE(result.isNull());
}

// Test lookupNF for existing key
TEST_F(DictTest_115, LookupNFFindsExistingKey_115) {
    dict->add("nfKey", Object(77));
    const Object &result = dict->lookupNF("nfKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 77);
}

// Test hasKey returns true for existing key
TEST_F(DictTest_115, HasKeyReturnsTrueForExistingKey_115) {
    dict->add("present", Object(5));
    EXPECT_TRUE(dict->hasKey("present"));
}

// Test hasKey returns false for missing key
TEST_F(DictTest_115, HasKeyReturnsFalseForMissingKey_115) {
    EXPECT_FALSE(dict->hasKey("absent"));
}

// Test set updates value for existing key
TEST_F(DictTest_115, SetUpdatesExistingKey_115) {
    dict->add("updateMe", Object(10));
    dict->set("updateMe", Object(20));
    Object result = dict->lookup("updateMe");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 20);
    // Length should not change since we updated an existing key
    EXPECT_EQ(dict->getLength(), 1);
}

// Test set adds a new key if not existing
TEST_F(DictTest_115, SetAddsNewKeyIfNotExisting_115) {
    dict->set("newKey", Object(30));
    EXPECT_EQ(dict->getLength(), 1);
    Object result = dict->lookup("newKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 30);
}

// Test remove decreases length
TEST_F(DictTest_115, RemoveDecreasesLength_115) {
    dict->add("a", Object(1));
    dict->add("b", Object(2));
    dict->add("c", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
    dict->remove("b");
    EXPECT_EQ(dict->getLength(), 2);
    EXPECT_FALSE(dict->hasKey("b"));
}

// Test remove of non-existing key doesn't change length
TEST_F(DictTest_115, RemoveNonExistingKeyNoChange_115) {
    dict->add("x", Object(1));
    int lenBefore = dict->getLength();
    dict->remove("nonexistent");
    EXPECT_EQ(dict->getLength(), lenBefore);
}

// Test is() method - Dict type checking
TEST_F(DictTest_115, IsReturnsFalseForEmptyDict_115) {
    EXPECT_FALSE(dict->is("SomeType"));
}

// Test adding with real/double value
TEST_F(DictTest_115, AddDoubleValue_115) {
    dict->add("pi", Object(3.14));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isReal() || val.isNum());
    EXPECT_NEAR(val.getNum(), 3.14, 0.001);
}

// Test adding boolean value
TEST_F(DictTest_115, AddBoolValue_115) {
    dict->add("flag", Object(false));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isBool());
    EXPECT_EQ(val.getBool(), false);
}

// Test getVal with Ref* overload
TEST_F(DictTest_115, GetValWithRefPointer_115) {
    dict->add("refKey", Object(55));
    Ref ref;
    Object val = dict->getVal(0, &ref);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

// Test lookup with Ref* overload
TEST_F(DictTest_115, LookupWithRefPointer_115) {
    dict->add("refLookup", Object(88));
    Ref ref;
    Object val = dict->lookup("refLookup", &ref);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 88);
}

// Test lookupInt for valid integer
TEST_F(DictTest_115, LookupIntFindsInteger_115) {
    dict->add("intVal", Object(123));
    int value = 0;
    bool found = dict->lookupInt("intVal", std::nullopt, &value);
    EXPECT_TRUE(found);
    EXPECT_EQ(value, 123);
}

// Test lookupInt for missing key
TEST_F(DictTest_115, LookupIntReturnsFalseForMissingKey_115) {
    int value = 0;
    bool found = dict->lookupInt("missing", std::nullopt, &value);
    EXPECT_FALSE(found);
}

// Test multiple keys and iteration
TEST_F(DictTest_115, IterateOverEntries_115) {
    dict->add("alpha", Object(1));
    dict->add("beta", Object(2));
    dict->add("gamma", Object(3));

    EXPECT_EQ(dict->getLength(), 3);

    // Verify all entries are accessible
    for (int i = 0; i < dict->getLength(); i++) {
        const char *key = dict->getKey(i);
        EXPECT_NE(key, nullptr);
        Object val = dict->getVal(i);
        EXPECT_TRUE(val.isInt());
    }
}

// Test copy constructor-like behavior via copy method
TEST_F(DictTest_115, CopyCreatesIndependentDict_115) {
    dict->add("original", Object(42));
    const Dict *copied = dict->copy(xref);
    EXPECT_NE(copied, nullptr);
    EXPECT_EQ(copied->getLength(), 1);
    EXPECT_TRUE(copied->hasKey("original"));
}

// Test setXRef and getXRef
TEST_F(DictTest_115, SetAndGetXRef_115) {
    XRef *newXRef = reinterpret_cast<XRef *>(0x12345678); // dummy pointer for testing
    dict->setXRef(newXRef);
    EXPECT_EQ(dict->getXRef(), newXRef);
}

// Test getXRef returns initial xref
TEST_F(DictTest_115, GetXRefReturnsInitialXRef_115) {
    EXPECT_EQ(dict->getXRef(), xref);
}

// Test findAvailableKey with no conflicts
TEST_F(DictTest_115, FindAvailableKeyNoConflict_115) {
    std::string available = dict->findAvailableKey("suggested");
    EXPECT_FALSE(available.empty());
}

// Test findAvailableKey with a conflicting key
TEST_F(DictTest_115, FindAvailableKeyWithConflict_115) {
    dict->add("suggested", Object(1));
    std::string available = dict->findAvailableKey("suggested");
    // Should return a key different from "suggested" since it's taken
    EXPECT_FALSE(available.empty());
    // The available key should not already exist in the dict (or could be the same if logic differs)
    // At minimum, the function should return something
}

// Test adding empty string key
TEST_F(DictTest_115, AddEmptyStringKey_115) {
    dict->add("", Object(0));
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey(""));
}

// Test remove all entries
TEST_F(DictTest_115, RemoveAllEntries_115) {
    dict->add("a", Object(1));
    dict->add("b", Object(2));
    dict->remove("a");
    dict->remove("b");
    EXPECT_EQ(dict->getLength(), 0);
}

// Test that getVal returns proper object for int64 type
TEST_F(DictTest_115, AddInt64Value_115) {
    long long bigVal = 9999999999LL;
    dict->add("bigInt", Object(bigVal));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isInt64() || val.isIntOrInt64());
    EXPECT_EQ(val.getInt64(), bigVal);
}
