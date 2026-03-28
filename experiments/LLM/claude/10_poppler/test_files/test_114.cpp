#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

class DictTest_114 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a Dict with nullptr XRef for testing purposes
        dict = new Dict(static_cast<XRef*>(nullptr));
    }

    void TearDown() override {
        delete dict;
        dict = nullptr;
    }

    Dict *dict = nullptr;
};

// Test that a newly created Dict has length 0
TEST_F(DictTest_114, NewDictHasZeroLength_114) {
    EXPECT_EQ(dict->getLength(), 0);
}

// Test adding a single entry increases length
TEST_F(DictTest_114, AddSingleEntryIncreasesLength_114) {
    dict->add("key1", Object(1));
    EXPECT_EQ(dict->getLength(), 1);
}

// Test adding multiple entries increases length accordingly
TEST_F(DictTest_114, AddMultipleEntriesIncreasesLength_114) {
    dict->add("key1", Object(1));
    dict->add("key2", Object(2));
    dict->add("key3", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
}

// Test getKey returns the correct key for a given index
TEST_F(DictTest_114, GetKeyReturnsCorrectKey_114) {
    dict->add("alpha", Object(10));
    dict->add("beta", Object(20));
    
    // Keys should be accessible by index
    std::string key0 = dict->getKey(0);
    std::string key1 = dict->getKey(1);
    
    // We expect the keys to be "alpha" and "beta" (order may depend on implementation)
    EXPECT_TRUE((key0 == "alpha" && key1 == "beta") || (key0 == "beta" && key1 == "alpha"));
}

// Test getVal returns the correct value for a given index
TEST_F(DictTest_114, GetValReturnsCorrectValue_114) {
    dict->add("key1", Object(42));
    EXPECT_EQ(dict->getLength(), 1);
    Object val = dict->getVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

// Test hasKey returns true for existing key
TEST_F(DictTest_114, HasKeyReturnsTrueForExistingKey_114) {
    dict->add("mykey", Object(5));
    EXPECT_TRUE(dict->hasKey("mykey"));
}

// Test hasKey returns false for non-existing key
TEST_F(DictTest_114, HasKeyReturnsFalseForNonExistingKey_114) {
    dict->add("mykey", Object(5));
    EXPECT_FALSE(dict->hasKey("otherkey"));
}

// Test hasKey on empty dict
TEST_F(DictTest_114, HasKeyOnEmptyDictReturnsFalse_114) {
    EXPECT_FALSE(dict->hasKey("anykey"));
}

// Test lookup returns the correct object for existing key
TEST_F(DictTest_114, LookupReturnsCorrectObjectForExistingKey_114) {
    dict->add("testkey", Object(100));
    Object result = dict->lookup("testkey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 100);
}

// Test lookup returns null object for non-existing key
TEST_F(DictTest_114, LookupReturnsNullForNonExistingKey_114) {
    Object result = dict->lookup("nonexistent");
    EXPECT_TRUE(result.isNull());
}

// Test lookupNF returns the correct object for existing key
TEST_F(DictTest_114, LookupNFReturnsCorrectObjectForExistingKey_114) {
    dict->add("nfkey", Object(200));
    const Object &result = dict->lookupNF("nfkey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 200);
}

// Test set updates value for existing key
TEST_F(DictTest_114, SetUpdatesValueForExistingKey_114) {
    dict->add("setkey", Object(10));
    dict->set("setkey", Object(20));
    EXPECT_EQ(dict->getLength(), 1);
    Object result = dict->lookup("setkey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 20);
}

// Test set adds new entry if key does not exist
TEST_F(DictTest_114, SetAddsNewEntryIfKeyDoesNotExist_114) {
    dict->set("newkey", Object(30));
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey("newkey"));
    Object result = dict->lookup("newkey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 30);
}

// Test remove removes an existing key
TEST_F(DictTest_114, RemoveDeletesExistingKey_114) {
    dict->add("removekey", Object(50));
    EXPECT_EQ(dict->getLength(), 1);
    dict->remove("removekey");
    EXPECT_EQ(dict->getLength(), 0);
    EXPECT_FALSE(dict->hasKey("removekey"));
}

// Test remove on non-existing key does not change length
TEST_F(DictTest_114, RemoveNonExistingKeyDoesNotChangeLength_114) {
    dict->add("key1", Object(1));
    int lengthBefore = dict->getLength();
    dict->remove("nonexistent");
    EXPECT_EQ(dict->getLength(), lengthBefore);
}

// Test is() method with type matching
TEST_F(DictTest_114, IsReturnsTrueForMatchingType_114) {
    dict->add("Type", Object(objName, "Catalog"));
    EXPECT_TRUE(dict->is("Catalog"));
}

// Test is() method returns false for non-matching type
TEST_F(DictTest_114, IsReturnsFalseForNonMatchingType_114) {
    dict->add("Type", Object(objName, "Catalog"));
    EXPECT_FALSE(dict->is("Page"));
}

// Test is() on dict without Type key
TEST_F(DictTest_114, IsReturnsFalseWhenNoTypeKey_114) {
    EXPECT_FALSE(dict->is("Catalog"));
}

// Test lookupInt with existing integer value
TEST_F(DictTest_114, LookupIntReturnsTrueForExistingIntKey_114) {
    dict->add("intkey", Object(42));
    int value = 0;
    bool result = dict->lookupInt("intkey", std::nullopt, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 42);
}

// Test lookupInt with non-existing key
TEST_F(DictTest_114, LookupIntReturnsFalseForNonExistingKey_114) {
    int value = -1;
    bool result = dict->lookupInt("nonexistent", std::nullopt, &value);
    EXPECT_FALSE(result);
}

// Test getXRef and setXRef
TEST_F(DictTest_114, SetXRefAndGetXRef_114) {
    XRef *xref = reinterpret_cast<XRef*>(0x12345678);
    dict->setXRef(xref);
    EXPECT_EQ(dict->getXRef(), xref);
}

// Test getXRef returns nullptr for dict created with nullptr
TEST_F(DictTest_114, GetXRefReturnsNullForNullInit_114) {
    EXPECT_EQ(dict->getXRef(), nullptr);
}

// Test copy creates a proper copy
TEST_F(DictTest_114, CopyCreatesDictWithSameEntries_114) {
    dict->add("a", Object(1));
    dict->add("b", Object(2));
    
    const Dict *copied = dict->copy(nullptr);
    EXPECT_EQ(copied->getLength(), 2);
    EXPECT_TRUE(copied->hasKey("a"));
    EXPECT_TRUE(copied->hasKey("b"));
    delete copied;
}

// Test getValNF returns the correct reference for a given index
TEST_F(DictTest_114, GetValNFReturnsCorrectValue_114) {
    dict->add("nfval", Object(77));
    const Object &val = dict->getValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// Test adding entries with empty string key
TEST_F(DictTest_114, AddEmptyStringKey_114) {
    dict->add("", Object(99));
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey(""));
    Object result = dict->lookup("");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 99);
}

// Test getVal with Ref output parameter
TEST_F(DictTest_114, GetValWithRefParam_114) {
    dict->add("refkey", Object(55));
    Ref ref;
    Object val = dict->getVal(0, &ref);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 55);
}

// Test findAvailableKey returns a key not already in dict
TEST_F(DictTest_114, FindAvailableKeyReturnsUnusedKey_114) {
    dict->add("suggested", Object(1));
    std::string available = dict->findAvailableKey("suggested");
    EXPECT_FALSE(available.empty());
    EXPECT_FALSE(dict->hasKey(available));
}

// Test findAvailableKey on empty dict returns suggested key
TEST_F(DictTest_114, FindAvailableKeyOnEmptyDictReturnsSuggested_114) {
    std::string available = dict->findAvailableKey("mykey");
    EXPECT_EQ(available, "mykey");
}

// Test multiple adds and removes
TEST_F(DictTest_114, MultipleAddsAndRemoves_114) {
    dict->add("a", Object(1));
    dict->add("b", Object(2));
    dict->add("c", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
    
    dict->remove("b");
    EXPECT_EQ(dict->getLength(), 2);
    EXPECT_FALSE(dict->hasKey("b"));
    EXPECT_TRUE(dict->hasKey("a"));
    EXPECT_TRUE(dict->hasKey("c"));
    
    dict->remove("a");
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey("c"));
    
    dict->remove("c");
    EXPECT_EQ(dict->getLength(), 0);
}

// Test lookup with Ref parameter
TEST_F(DictTest_114, LookupWithRefParam_114) {
    dict->add("reftest", Object(88));
    Ref ref;
    Object result = dict->lookup("reftest", &ref);
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 88);
}

// Test adding different object types
TEST_F(DictTest_114, AddDifferentObjectTypes_114) {
    dict->add("intval", Object(42));
    dict->add("realval", Object(3.14));
    dict->add("boolval", Object(true));
    
    EXPECT_EQ(dict->getLength(), 3);
    
    Object intResult = dict->lookup("intval");
    EXPECT_TRUE(intResult.isInt());
    EXPECT_EQ(intResult.getInt(), 42);
    
    Object realResult = dict->lookup("realval");
    EXPECT_TRUE(realResult.isReal());
    
    Object boolResult = dict->lookup("boolval");
    EXPECT_TRUE(boolResult.isBool());
    EXPECT_EQ(boolResult.getBool(), true);
}
