#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "poppler/Dict.h"
#include "poppler/Object.h"
#include "poppler/XRef.h"

class DictTest_113 : public ::testing::Test {
protected:
    void SetUp() override {
        // XRef can be nullptr for basic Dict operations in many implementations
        dict = new Dict(nullptr);
    }

    void TearDown() override {
        delete dict;
        dict = nullptr;
    }

    Dict *dict = nullptr;
};

// Test that a newly created Dict has length 0
TEST_F(DictTest_113, NewDictHasZeroLength_113) {
    EXPECT_EQ(dict->getLength(), 0);
}

// Test that adding an entry increases the length
TEST_F(DictTest_113, AddIncreasesLength_113) {
    dict->add("key1", Object(1));
    EXPECT_EQ(dict->getLength(), 1);
}

// Test that adding multiple entries increases the length accordingly
TEST_F(DictTest_113, AddMultipleEntriesIncreasesLength_113) {
    dict->add("key1", Object(1));
    dict->add("key2", Object(2));
    dict->add("key3", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
}

// Test that removing an entry decreases the length
TEST_F(DictTest_113, RemoveDecreasesLength_113) {
    dict->add("key1", Object(1));
    dict->add("key2", Object(2));
    EXPECT_EQ(dict->getLength(), 2);
    dict->remove("key1");
    EXPECT_EQ(dict->getLength(), 1);
}

// Test hasKey returns true for existing key
TEST_F(DictTest_113, HasKeyReturnsTrueForExistingKey_113) {
    dict->add("mykey", Object(42));
    EXPECT_TRUE(dict->hasKey("mykey"));
}

// Test hasKey returns false for non-existing key
TEST_F(DictTest_113, HasKeyReturnsFalseForNonExistingKey_113) {
    dict->add("mykey", Object(42));
    EXPECT_FALSE(dict->hasKey("otherkey"));
}

// Test hasKey on empty dict
TEST_F(DictTest_113, HasKeyOnEmptyDict_113) {
    EXPECT_FALSE(dict->hasKey("anykey"));
}

// Test lookup returns the correct value for an existing key
TEST_F(DictTest_113, LookupReturnsCorrectValue_113) {
    dict->add("intkey", Object(123));
    Object obj = dict->lookup("intkey");
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 123);
}

// Test lookup returns null object for non-existing key
TEST_F(DictTest_113, LookupReturnsNullForNonExistingKey_113) {
    Object obj = dict->lookup("nokey");
    EXPECT_TRUE(obj.isNull());
}

// Test set overwrites an existing key's value
TEST_F(DictTest_113, SetOverwritesExistingValue_113) {
    dict->add("key1", Object(100));
    dict->set("key1", Object(200));
    Object obj = dict->lookup("key1");
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 200);
    // Length should remain the same
    EXPECT_EQ(dict->getLength(), 1);
}

// Test set adds entry if key doesn't exist
TEST_F(DictTest_113, SetAddsIfKeyDoesNotExist_113) {
    dict->set("newkey", Object(999));
    EXPECT_TRUE(dict->hasKey("newkey"));
    Object obj = dict->lookup("newkey");
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 999);
}

// Test getKey returns the correct key name
TEST_F(DictTest_113, GetKeyReturnsCorrectKeyName_113) {
    dict->add("alpha", Object(1));
    dict->add("beta", Object(2));
    // At least we can check that the keys are among what we added
    bool foundAlpha = false, foundBeta = false;
    for (int i = 0; i < dict->getLength(); i++) {
        std::string key = dict->getKey(i);
        if (key == "alpha") foundAlpha = true;
        if (key == "beta") foundBeta = true;
    }
    EXPECT_TRUE(foundAlpha);
    EXPECT_TRUE(foundBeta);
}

// Test getVal by index
TEST_F(DictTest_113, GetValByIndex_113) {
    dict->add("only", Object(77));
    Object obj = dict->getVal(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 77);
}

// Test lookupNF returns reference to object without resolving
TEST_F(DictTest_113, LookupNFReturnsObject_113) {
    dict->add("nfkey", Object(55));
    const Object &obj = dict->lookupNF("nfkey");
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 55);
}

// Test remove on non-existing key doesn't crash and length stays same
TEST_F(DictTest_113, RemoveNonExistingKeyNoEffect_113) {
    dict->add("existing", Object(1));
    int lenBefore = dict->getLength();
    dict->remove("nonexisting");
    EXPECT_EQ(dict->getLength(), lenBefore);
}

// Test is() for type checking
TEST_F(DictTest_113, IsChecksType_113) {
    dict->add("Type", Object(objName, "Catalog"));
    // is() checks if the "Type" entry matches the given string
    EXPECT_TRUE(dict->is("Catalog"));
    EXPECT_FALSE(dict->is("Page"));
}

// Test lookupInt for integer values
TEST_F(DictTest_113, LookupIntReturnsIntValue_113) {
    dict->add("Width", Object(640));
    int value = 0;
    bool result = dict->lookupInt("Width", std::nullopt, &value);
    EXPECT_TRUE(result);
    EXPECT_EQ(value, 640);
}

// Test lookupInt with non-existing key returns false
TEST_F(DictTest_113, LookupIntReturnsFalseForMissingKey_113) {
    int value = -1;
    bool result = dict->lookupInt("Missing", std::nullopt, &value);
    EXPECT_FALSE(result);
}

// Test getXRef and setXRef
TEST_F(DictTest_113, GetSetXRef_113) {
    EXPECT_EQ(dict->getXRef(), nullptr);
    // We can't easily create a real XRef, but we can test the setter/getter
    XRef *fakeXRef = reinterpret_cast<XRef *>(0x12345678);
    dict->setXRef(fakeXRef);
    EXPECT_EQ(dict->getXRef(), fakeXRef);
    // Reset to nullptr to avoid issues on teardown
    dict->setXRef(nullptr);
}

// Test copy constructor creates independent copy
TEST_F(DictTest_113, CopyCreatesDictWithSameEntries_113) {
    dict->add("a", Object(10));
    dict->add("b", Object(20));
    const Dict *copied = dict->copy(nullptr);
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getLength(), 2);
    EXPECT_TRUE(copied->hasKey("a"));
    EXPECT_TRUE(copied->hasKey("b"));
    delete copied;
}

// Test getLength on dict with entries added and removed
TEST_F(DictTest_113, GetLengthAfterAddAndRemove_113) {
    dict->add("x", Object(1));
    dict->add("y", Object(2));
    dict->add("z", Object(3));
    EXPECT_EQ(dict->getLength(), 3);
    dict->remove("y");
    EXPECT_EQ(dict->getLength(), 2);
    dict->remove("x");
    EXPECT_EQ(dict->getLength(), 1);
    dict->remove("z");
    EXPECT_EQ(dict->getLength(), 0);
}

// Test adding entries with empty string key
TEST_F(DictTest_113, AddEmptyStringKey_113) {
    dict->add("", Object(0));
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_TRUE(dict->hasKey(""));
    Object obj = dict->lookup("");
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

// Test getValNF by index
TEST_F(DictTest_113, GetValNFByIndex_113) {
    dict->add("val", Object(33));
    const Object &obj = dict->getValNF(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 33);
}

// Test findAvailableKey returns a key not in the dict
TEST_F(DictTest_113, FindAvailableKeyReturnsUnusedKey_113) {
    dict->add("suggested", Object(1));
    std::string available = dict->findAvailableKey("suggested");
    EXPECT_FALSE(dict->hasKey(available));
    EXPECT_FALSE(available.empty());
}

// Test findAvailableKey when suggested key is not in dict
TEST_F(DictTest_113, FindAvailableKeyReturnsSuggestedIfFree_113) {
    std::string available = dict->findAvailableKey("freekey");
    // The suggested key should be available since dict is empty
    EXPECT_EQ(available, "freekey");
}

// Test lookup with Ref parameter
TEST_F(DictTest_113, LookupWithRefParam_113) {
    dict->add("refkey", Object(42));
    Ref ref;
    Object obj = dict->lookup("refkey", &ref);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}
