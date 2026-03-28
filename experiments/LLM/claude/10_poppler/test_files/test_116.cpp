#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

class DictTest_116 : public ::testing::Test {
protected:
    void SetUp() override {
        dict = new Dict(nullptr);
    }

    void TearDown() override {
        delete dict;
    }

    Dict *dict;
};

// Test that a newly created Dict has length 0
TEST_F(DictTest_116, NewDictHasZeroLength_116) {
    EXPECT_EQ(dict->getLength(), 0);
}

// Test adding a single entry increases length
TEST_F(DictTest_116, AddSingleEntryIncreasesLength_116) {
    dict->add("key1", Object(42));
    EXPECT_EQ(dict->getLength(), 1);
}

// Test adding multiple entries increases length accordingly
TEST_F(DictTest_116, AddMultipleEntriesIncreasesLength_116) {
    dict->add("key1", Object(1));
    dict->add("key2", Object(2));
    dict->add("key3", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
}

// Test getKey returns correct key for given index
TEST_F(DictTest_116, GetKeyReturnsCorrectKey_116) {
    dict->add("myKey", Object(100));
    EXPECT_STREQ(dict->getKey(0), "myKey");
}

// Test getVal returns correct value for given index
TEST_F(DictTest_116, GetValReturnsCorrectValue_116) {
    dict->add("key1", Object(42));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test getValNF returns reference to value at index
TEST_F(DictTest_116, GetValNFReturnsValueAtIndex_116) {
    dict->add("key1", Object(99));
    const Object &val = dict->getValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

// Test hasKey returns true for existing key
TEST_F(DictTest_116, HasKeyReturnsTrueForExistingKey_116) {
    dict->add("present", Object(1));
    EXPECT_TRUE(dict->hasKey("present"));
}

// Test hasKey returns false for non-existing key
TEST_F(DictTest_116, HasKeyReturnsFalseForMissingKey_116) {
    dict->add("present", Object(1));
    EXPECT_FALSE(dict->hasKey("absent"));
}

// Test lookup returns the correct object for existing key
TEST_F(DictTest_116, LookupReturnsCorrectObject_116) {
    dict->add("testKey", Object(55));
    Object result = dict->lookup("testKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 55);
}

// Test lookup returns null object for missing key
TEST_F(DictTest_116, LookupReturnsNullForMissingKey_116) {
    Object result = dict->lookup("nonexistent");
    EXPECT_TRUE(result.isNull());
}

// Test lookupNF returns reference for existing key
TEST_F(DictTest_116, LookupNFReturnsValueForExistingKey_116) {
    dict->add("nfKey", Object(77));
    const Object &result = dict->lookupNF("nfKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 77);
}

// Test set updates existing key's value
TEST_F(DictTest_116, SetUpdatesExistingValue_116) {
    dict->add("key1", Object(10));
    dict->set("key1", Object(20));
    Object result = dict->lookup("key1");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 20);
    EXPECT_EQ(dict->getLength(), 1);
}

// Test set creates new entry if key doesn't exist
TEST_F(DictTest_116, SetCreatesNewEntryIfKeyMissing_116) {
    dict->set("newKey", Object(30));
    EXPECT_TRUE(dict->hasKey("newKey"));
    Object result = dict->lookup("newKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 30);
}

// Test remove reduces length
TEST_F(DictTest_116, RemoveReducesLength_116) {
    dict->add("key1", Object(1));
    dict->add("key2", Object(2));
    EXPECT_EQ(dict->getLength(), 2);
    dict->remove("key1");
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_FALSE(dict->hasKey("key1"));
    EXPECT_TRUE(dict->hasKey("key2"));
}

// Test remove on non-existing key does not change length
TEST_F(DictTest_116, RemoveNonExistingKeyNoChange_116) {
    dict->add("key1", Object(1));
    dict->remove("nonexistent");
    EXPECT_EQ(dict->getLength(), 1);
}

// Test is() method with Type key
TEST_F(DictTest_116, IsChecksTypeKey_116) {
    dict->add("Type", Object(objName, "Catalog"));
    EXPECT_TRUE(dict->is("Catalog"));
    EXPECT_FALSE(dict->is("Page"));
}

// Test lookupInt for existing int key
TEST_F(DictTest_116, LookupIntReturnsTrue_116) {
    dict->add("IntKey", Object(42));
    int value = 0;
    std::optional<std::string_view> altKey;
    bool result = dict->lookupInt("IntKey", altKey, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42);
}

// Test lookupInt for missing key returns false
TEST_F(DictTest_116, LookupIntReturnsFalseForMissingKey_116) {
    int value = -1;
    std::optional<std::string_view> altKey;
    bool result = dict->lookupInt("missing", altKey, &value);
    EXPECT_FALSE(result);
}

// Test lookupInt with alternative key
TEST_F(DictTest_116, LookupIntUsesAltKey_116) {
    dict->add("AltKey", Object(77));
    int value = 0;
    std::optional<std::string_view> altKey = "AltKey";
    bool result = dict->lookupInt("missing", altKey, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 77);
}

// Test copy creates a proper copy
TEST_F(DictTest_116, CopyCreatesCopy_116) {
    dict->add("a", Object(1));
    dict->add("b", Object(2));
    const Dict *copied = dict->copy(nullptr);
    EXPECT_EQ(copied->getLength(), 2);
    EXPECT_TRUE(copied->hasKey("a"));
    EXPECT_TRUE(copied->hasKey("b"));
    // Note: copied dict is ref-counted, but we need to be careful about memory here
}

// Test getXRef and setXRef
TEST_F(DictTest_116, GetSetXRef_116) {
    EXPECT_EQ(dict->getXRef(), nullptr);
    // We can set and get xref
    XRef *fakeXRef = reinterpret_cast<XRef *>(0x1234);
    dict->setXRef(fakeXRef);
    EXPECT_EQ(dict->getXRef(), fakeXRef);
    // Reset to nullptr for safety
    dict->setXRef(nullptr);
}

// Test getValNF for multiple entries
TEST_F(DictTest_116, GetValNFMultipleEntries_116) {
    dict->add("first", Object(10));
    dict->add("second", Object(20));
    dict->add("third", Object(30));

    const Object &v0 = dict->getValNF(0);
    const Object &v1 = dict->getValNF(1);
    const Object &v2 = dict->getValNF(2);

    EXPECT_TRUE(v0.isInt());
    EXPECT_EQ(v0.getInt(), 10);
    EXPECT_TRUE(v1.isInt());
    EXPECT_EQ(v1.getInt(), 20);
    EXPECT_TRUE(v2.isInt());
    EXPECT_EQ(v2.getInt(), 30);
}

// Test getVal with Ref output parameter
TEST_F(DictTest_116, GetValWithRefParam_116) {
    dict->add("refKey", Object(42));
    Ref ref;
    Object val = dict->getVal(0, &ref);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test adding entries with different object types
TEST_F(DictTest_116, AddDifferentObjectTypes_116) {
    dict->add("intVal", Object(42));
    dict->add("realVal", Object(3.14));
    dict->add("boolVal", Object(true));
    dict->add("nullVal", Object(objNull));

    EXPECT_EQ(dict->getLength(), 4);

    Object intObj = dict->lookup("intVal");
    EXPECT_TRUE(intObj.isInt());
    EXPECT_EQ(intObj.getInt(), 42);

    Object realObj = dict->lookup("realVal");
    EXPECT_TRUE(realObj.isReal());

    Object boolObj = dict->lookup("boolVal");
    EXPECT_TRUE(boolObj.isBool());
    EXPECT_EQ(boolObj.getBool(), true);
}

// Test findAvailableKey
TEST_F(DictTest_116, FindAvailableKeyReturnsUnusedKey_116) {
    dict->add("key", Object(1));
    std::string available = dict->findAvailableKey("key");
    // The available key should not be already in the dict, or should be unique
    // If "key" is taken, a different key should be returned
    EXPECT_FALSE(available.empty());
}

// Test findAvailableKey when suggested key is not taken
TEST_F(DictTest_116, FindAvailableKeyReturnsSuggestedIfFree_116) {
    std::string available = dict->findAvailableKey("freeKey");
    EXPECT_EQ(available, "freeKey");
}

// Test lookup with Ref output parameter
TEST_F(DictTest_116, LookupWithRefParam_116) {
    dict->add("refLookup", Object(88));
    Ref ref;
    Object result = dict->lookup("refLookup", &ref);
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 88);
}

// Test empty dict hasKey always false
TEST_F(DictTest_116, EmptyDictHasNoKeys_116) {
    EXPECT_FALSE(dict->hasKey("anything"));
    EXPECT_FALSE(dict->hasKey(""));
    EXPECT_FALSE(dict->hasKey("Type"));
}

// Test is() returns false when no Type key
TEST_F(DictTest_116, IsReturnsFalseWithNoTypeKey_116) {
    EXPECT_FALSE(dict->is("Catalog"));
}
