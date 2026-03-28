#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

// Test fixture for Dict tests
class DictTest_118 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a Dict with nullptr XRef for basic tests
        dict = new Dict(nullptr);
    }

    void TearDown() override {
        // Dict is reference counted, but we created it with new
        // We need to be careful about cleanup
        delete dict;
    }

    Dict *dict;
};

// Test: Newly created Dict has zero length
TEST_F(DictTest_118, NewDictHasZeroLength_118) {
    EXPECT_EQ(dict->getLength(), 0);
}

// Test: getXRef returns the XRef passed during construction
TEST_F(DictTest_118, GetXRefReturnsConstructorValue_118) {
    EXPECT_EQ(dict->getXRef(), nullptr);
}

// Test: setXRef changes the XRef pointer
TEST_F(DictTest_118, SetXRefChangesXRef_118) {
    XRef *dummyXRef = reinterpret_cast<XRef *>(0x1234);
    dict->setXRef(dummyXRef);
    EXPECT_EQ(dict->getXRef(), dummyXRef);
}

// Test: Adding an entry increases length
TEST_F(DictTest_118, AddIncreasesLength_118) {
    dict->add("Key1", Object(42));
    EXPECT_EQ(dict->getLength(), 1);
}

// Test: Adding multiple entries increases length correctly
TEST_F(DictTest_118, AddMultipleEntriesIncreasesLength_118) {
    dict->add("Key1", Object(1));
    dict->add("Key2", Object(2));
    dict->add("Key3", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
}

// Test: hasKey returns true for existing key
TEST_F(DictTest_118, HasKeyReturnsTrueForExistingKey_118) {
    dict->add("TestKey", Object(100));
    EXPECT_TRUE(dict->hasKey("TestKey"));
}

// Test: hasKey returns false for non-existing key
TEST_F(DictTest_118, HasKeyReturnsFalseForNonExistingKey_118) {
    EXPECT_FALSE(dict->hasKey("NonExistent"));
}

// Test: lookup returns the correct value for an existing key
TEST_F(DictTest_118, LookupReturnsCorrectValue_118) {
    dict->add("IntKey", Object(42));
    Object result = dict->lookup("IntKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 42);
}

// Test: lookup returns null object for non-existing key
TEST_F(DictTest_118, LookupReturnsNullForNonExistingKey_118) {
    Object result = dict->lookup("Missing");
    EXPECT_TRUE(result.isNull());
}

// Test: lookupNF returns value without fetching
TEST_F(DictTest_118, LookupNFReturnsValue_118) {
    dict->add("NFKey", Object(99));
    const Object &result = dict->lookupNF("NFKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 99);
}

// Test: set overwrites an existing key's value
TEST_F(DictTest_118, SetOverwritesExistingKey_118) {
    dict->add("Key", Object(10));
    dict->set("Key", Object(20));
    EXPECT_EQ(dict->getLength(), 1);
    Object result = dict->lookup("Key");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 20);
}

// Test: set adds a new key if it doesn't exist
TEST_F(DictTest_118, SetAddsNewKeyIfNotExist_118) {
    dict->set("NewKey", Object(55));
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey("NewKey"));
    Object result = dict->lookup("NewKey");
    EXPECT_EQ(result.getInt(), 55);
}

// Test: remove decreases length
TEST_F(DictTest_118, RemoveDecreasesLength_118) {
    dict->add("Key1", Object(1));
    dict->add("Key2", Object(2));
    EXPECT_EQ(dict->getLength(), 2);
    dict->remove("Key1");
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_FALSE(dict->hasKey("Key1"));
    EXPECT_TRUE(dict->hasKey("Key2"));
}

// Test: remove non-existing key does not change length
TEST_F(DictTest_118, RemoveNonExistingKeyNoChange_118) {
    dict->add("Key1", Object(1));
    dict->remove("NonExistent");
    EXPECT_EQ(dict->getLength(), 1);
}

// Test: getKey returns correct key name by index
TEST_F(DictTest_118, GetKeyByIndex_118) {
    dict->add("Alpha", Object(1));
    const char *key = dict->getKey(0);
    EXPECT_STREQ(key, "Alpha");
}

// Test: getVal by index returns correct value
TEST_F(DictTest_118, GetValByIndex_118) {
    dict->add("Num", Object(77));
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// Test: getValNF by index returns correct reference
TEST_F(DictTest_118, GetValNFByIndex_118) {
    dict->add("Val", Object(33));
    const Object &val = dict->getValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 33);
}

// Test: is() checks the /Type entry
TEST_F(DictTest_118, IsChecksTypeEntry_118) {
    dict->add("Type", Object(objName, "Page"));
    EXPECT_TRUE(dict->is("Page"));
    EXPECT_FALSE(dict->is("Font"));
}

// Test: is() returns false when no Type entry
TEST_F(DictTest_118, IsReturnsFalseWhenNoType_118) {
    EXPECT_FALSE(dict->is("Anything"));
}

// Test: lookupInt returns true and sets value for existing int key
TEST_F(DictTest_118, LookupIntReturnsValueForExistingKey_118) {
    dict->add("Width", Object(800));
    int value = 0;
    bool result = dict->lookupInt("Width", std::nullopt, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 800);
}

// Test: lookupInt returns false for non-existing key
TEST_F(DictTest_118, LookupIntReturnsFalseForNonExistingKey_118) {
    int value = -1;
    bool result = dict->lookupInt("Missing", std::nullopt, &value);
    EXPECT_FALSE(result);
}

// Test: lookupInt uses alt_key when primary key not found
TEST_F(DictTest_118, LookupIntUsesAltKey_118) {
    dict->add("AltWidth", Object(600));
    int value = 0;
    bool result = dict->lookupInt("Width", std::string_view("AltWidth"), &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 600);
}

// Test: copy creates a valid copy
TEST_F(DictTest_118, CopyCreatesValidCopy_118) {
    dict->add("CopyKey", Object(123));
    const Dict *copied = dict->copy(nullptr);
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getLength(), 1);
    EXPECT_TRUE(copied->hasKey("CopyKey"));
    delete copied;
}

// Test: Adding string value
TEST_F(DictTest_118, AddStringValue_118) {
    dict->add("StrKey", Object(objString, "hello"));
    Object result = dict->lookup("StrKey");
    EXPECT_TRUE(result.isString());
}

// Test: Adding bool value
TEST_F(DictTest_118, AddBoolValue_118) {
    dict->add("BoolKey", Object(true));
    Object result = dict->lookup("BoolKey");
    EXPECT_TRUE(result.isBool());
    EXPECT_TRUE(result.getBool());
}

// Test: Adding real (double) value
TEST_F(DictTest_118, AddRealValue_118) {
    dict->add("RealKey", Object(3.14));
    Object result = dict->lookup("RealKey");
    EXPECT_TRUE(result.isReal());
}

// Test: Empty dict hasKey always returns false
TEST_F(DictTest_118, EmptyDictHasKeyAlwaysFalse_118) {
    EXPECT_FALSE(dict->hasKey(""));
    EXPECT_FALSE(dict->hasKey("any"));
    EXPECT_FALSE(dict->hasKey("key"));
}

// Test: findAvailableKey returns a key not in the dictionary
TEST_F(DictTest_118, FindAvailableKeyReturnsUniqueKey_118) {
    dict->add("Suggested", Object(1));
    std::string available = dict->findAvailableKey("Suggested");
    EXPECT_FALSE(available.empty());
    // The returned key should not already exist in the dict (or be different from existing)
    // If it's the same as suggested, it means suggested was available - but we added it, so it shouldn't be
    EXPECT_NE(available, "Suggested");
}

// Test: findAvailableKey with non-existing suggested key returns it
TEST_F(DictTest_118, FindAvailableKeyReturnsSuggestedIfAvailable_118) {
    std::string available = dict->findAvailableKey("FreeName");
    EXPECT_EQ(available, "FreeName");
}

// Test: Multiple removes until empty
TEST_F(DictTest_118, MultipleRemovesUntilEmpty_118) {
    dict->add("A", Object(1));
    dict->add("B", Object(2));
    dict->add("C", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
    dict->remove("A");
    dict->remove("B");
    dict->remove("C");
    EXPECT_EQ(dict->getLength(), 0);
}

// Test: getVal with Ref parameter
TEST_F(DictTest_118, GetValWithRef_118) {
    dict->add("RefKey", Object(42));
    Ref ref;
    Object val = dict->getVal(0, &ref);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test: lookup with Ref parameter
TEST_F(DictTest_118, LookupWithRef_118) {
    dict->add("RefLookup", Object(88));
    Ref ref;
    Object result = dict->lookup("RefLookup", &ref);
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 88);
}

// Test: Dict constructed from another Dict (copy constructor alternative)
TEST_F(DictTest_118, ConstructFromOtherDict_118) {
    dict->add("Source", Object(999));
    Dict *dictCopy = new Dict(dict);
    EXPECT_EQ(dictCopy->getLength(), 1);
    EXPECT_TRUE(dictCopy->hasKey("Source"));
    Object val = dictCopy->lookup("Source");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 999);
    delete dictCopy;
}
