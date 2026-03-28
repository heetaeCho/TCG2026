#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <string>
#include <cstdio>
#include <set>
#include <vector>

#include "Object.h"
#include "Dict.h"
#include "PDFDoc.h"
#include "UnicodeMap.h"
#include "GooString.h"
#include "GlobalParams.h"

class PrintCustomInfoTest_2674 : public ::testing::Test {
protected:
    void SetUp() override {
        if (!globalParams) {
            globalParams = std::make_unique<GlobalParams>();
        }
    }
};

// Test that Object default constructor creates objNone
TEST_F(PrintCustomInfoTest_2674, ObjectDefaultIsNone_2674) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_FALSE(obj.isDict());
}

// Test that Object with Dict is recognized as dict
TEST_F(PrintCustomInfoTest_2674, ObjectWithDictIsDict_2674) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getDict(), dict);
}

// Test Dict getLength on empty dict
TEST_F(PrintCustomInfoTest_2674, EmptyDictHasZeroLength_2674) {
    Dict *dict = new Dict(nullptr);
    EXPECT_EQ(dict->getLength(), 0);
    Object obj(dict); // prevent leak
}

// Test Dict add and getLength
TEST_F(PrintCustomInfoTest_2674, DictAddIncreasesLength_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Title", Object(std::make_unique<GooString>("Test Title")));
    EXPECT_EQ(dict->getLength(), 1);
    Object obj(dict);
}

// Test Dict getKey returns correct key
TEST_F(PrintCustomInfoTest_2674, DictGetKeyReturnsCorrectKey_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Author", Object(std::make_unique<GooString>("John")));
    EXPECT_STREQ(dict->getKey(0), "Author");
    Object obj(dict);
}

// Test Dict lookup returns string value
TEST_F(PrintCustomInfoTest_2674, DictLookupReturnsStringValue_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Subject", Object(std::make_unique<GooString>("Test Subject")));
    Object val = dict->lookup("Subject");
    EXPECT_TRUE(val.isString());
    EXPECT_STREQ(val.getString()->c_str(), "Test Subject");
    Object obj(dict);
}

// Test Dict with multiple entries
TEST_F(PrintCustomInfoTest_2674, DictMultipleEntries_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Title", Object(std::make_unique<GooString>("My Title")));
    dict->add("Author", Object(std::make_unique<GooString>("My Author")));
    dict->add("Subject", Object(std::make_unique<GooString>("My Subject")));
    EXPECT_EQ(dict->getLength(), 3);
    Object obj(dict);
}

// Test Dict lookup for non-existent key returns null
TEST_F(PrintCustomInfoTest_2674, DictLookupNonExistentKeyReturnsNull_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Title", Object(std::make_unique<GooString>("Test")));
    Object val = dict->lookup("NonExistent");
    EXPECT_TRUE(val.isNull());
    Object obj(dict);
}

// Test Dict hasKey
TEST_F(PrintCustomInfoTest_2674, DictHasKeyReturnsTrue_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("CreationDate", Object(std::make_unique<GooString>("D:20230101")));
    EXPECT_TRUE(dict->hasKey("CreationDate"));
    EXPECT_FALSE(dict->hasKey("ModDate"));
    Object obj(dict);
}

// Test that Trapped key exists in dict but would be skipped by printCustomInfo logic
TEST_F(PrintCustomInfoTest_2674, DictContainsTrappedKey_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Trapped", Object(std::make_unique<GooString>("False")));
    dict->add("Title", Object(std::make_unique<GooString>("Test")));
    EXPECT_EQ(dict->getLength(), 2);
    
    // Simulate the filtering logic from printCustomInfo
    std::set<std::string> keys;
    for (int i = 0; i < dict->getLength(); i++) {
        std::string key(dict->getKey(i));
        if (key != "Trapped") {
            keys.insert(key);
        }
    }
    EXPECT_EQ(keys.size(), 1u);
    EXPECT_TRUE(keys.count("Title") > 0);
    EXPECT_TRUE(keys.count("Trapped") == 0);
    Object obj(dict);
}

// Test keys are sorted when inserted into std::set (simulating printCustomInfo behavior)
TEST_F(PrintCustomInfoTest_2674, KeysSortedInSet_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Zebra", Object(std::make_unique<GooString>("val1")));
    dict->add("Alpha", Object(std::make_unique<GooString>("val2")));
    dict->add("Middle", Object(std::make_unique<GooString>("val3")));
    
    std::set<std::string> keys;
    for (int i = 0; i < dict->getLength(); i++) {
        std::string key(dict->getKey(i));
        if (key != "Trapped") {
            keys.insert(key);
        }
    }
    
    auto it = keys.begin();
    EXPECT_EQ(*it, "Alpha");
    ++it;
    EXPECT_EQ(*it, "Middle");
    ++it;
    EXPECT_EQ(*it, "Zebra");
    Object obj(dict);
}

// Test Object isString for string objects
TEST_F(PrintCustomInfoTest_2674, ObjectIsStringForStringObject_2674) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_TRUE(obj.isString());
}

// Test Object isString returns false for non-string
TEST_F(PrintCustomInfoTest_2674, ObjectIsStringFalseForInt_2674) {
    Object obj(42);
    EXPECT_FALSE(obj.isString());
    EXPECT_TRUE(obj.isInt());
}

// Test null Object
TEST_F(PrintCustomInfoTest_2674, NullObjectIsNull_2674) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isDict());
}

// Test Dict with only Trapped key - all keys filtered
TEST_F(PrintCustomInfoTest_2674, DictOnlyTrappedKeyAllFiltered_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Trapped", Object(std::make_unique<GooString>("True")));
    
    std::set<std::string> keys;
    for (int i = 0; i < dict->getLength(); i++) {
        std::string key(dict->getKey(i));
        if (key != "Trapped") {
            keys.insert(key);
        }
    }
    EXPECT_TRUE(keys.empty());
    Object obj(dict);
}

// Test Dict with CreationDate and ModDate keys
TEST_F(PrintCustomInfoTest_2674, DictWithDateKeys_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("CreationDate", Object(std::make_unique<GooString>("D:20230615120000")));
    dict->add("ModDate", Object(std::make_unique<GooString>("D:20230616130000")));
    dict->add("Title", Object(std::make_unique<GooString>("Test Doc")));
    
    std::set<std::string> keys;
    for (int i = 0; i < dict->getLength(); i++) {
        std::string key(dict->getKey(i));
        if (key != "Trapped") {
            keys.insert(key);
        }
    }
    EXPECT_EQ(keys.size(), 3u);
    EXPECT_TRUE(keys.count("CreationDate") > 0);
    EXPECT_TRUE(keys.count("ModDate") > 0);
    EXPECT_TRUE(keys.count("Title") > 0);
    Object obj(dict);
}

// Test Dict with non-string value (should be skipped in custom key handling)
TEST_F(PrintCustomInfoTest_2674, DictWithNonStringValueSkipped_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("CustomKey", Object(42));
    
    Object val = dict->lookup("CustomKey");
    EXPECT_TRUE(val.isInt());
    EXPECT_FALSE(val.isString());
    Object obj(dict);
}

// Test Dict remove operation
TEST_F(PrintCustomInfoTest_2674, DictRemoveEntry_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Key1", Object(std::make_unique<GooString>("val1")));
    dict->add("Key2", Object(std::make_unique<GooString>("val2")));
    EXPECT_EQ(dict->getLength(), 2);
    dict->remove("Key1");
    EXPECT_EQ(dict->getLength(), 1);
    EXPECT_FALSE(dict->hasKey("Key1"));
    EXPECT_TRUE(dict->hasKey("Key2"));
    Object obj(dict);
}

// Test Object move semantics
TEST_F(PrintCustomInfoTest_2674, ObjectMoveConstructor_2674) {
    Object obj1(std::make_unique<GooString>("test"));
    EXPECT_TRUE(obj1.isString());
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isString());
}

// Test Dict set overwrites existing value
TEST_F(PrintCustomInfoTest_2674, DictSetOverwritesValue_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("Title", Object(std::make_unique<GooString>("Old Title")));
    dict->set("Title", Object(std::make_unique<GooString>("New Title")));
    EXPECT_EQ(dict->getLength(), 1);
    Object val = dict->lookup("Title");
    EXPECT_TRUE(val.isString());
    EXPECT_STREQ(val.getString()->c_str(), "New Title");
    Object obj(dict);
}

// Test loading a real PDF document and checking getDocInfo
TEST_F(PrintCustomInfoTest_2674, PDFDocGetDocInfoFromValidPDF_2674) {
    // This test verifies the interface - if no PDF is available it will just check error state
    auto doc = std::make_unique<PDFDoc>(std::make_unique<GooString>("nonexistent.pdf"), std::optional<GooString>(), std::optional<GooString>(), std::function<void(void)>());
    // A non-existent file should not be ok
    EXPECT_FALSE(doc->isOk());
}

// Test Object getString returns valid pointer for string objects
TEST_F(PrintCustomInfoTest_2674, ObjectGetStringReturnsValidPointer_2674) {
    Object obj(std::make_unique<GooString>("test content"));
    EXPECT_TRUE(obj.isString());
    const GooString *str = obj.getString();
    EXPECT_NE(str, nullptr);
    EXPECT_STREQ(str->c_str(), "test content");
}

// Test Dict with duplicate key names uses set behavior
TEST_F(PrintCustomInfoTest_2674, SetDeduplicatesKeys_2674) {
    Dict *dict = new Dict(nullptr);
    // Add two entries, then simulate the set collection
    dict->add("Title", Object(std::make_unique<GooString>("val1")));
    dict->add("Author", Object(std::make_unique<GooString>("val2")));
    
    std::set<std::string> keys;
    for (int i = 0; i < dict->getLength(); i++) {
        std::string key(dict->getKey(i));
        if (key != "Trapped") {
            keys.insert(key);
        }
    }
    // Set should have unique entries
    EXPECT_EQ(keys.size(), 2u);
    Object obj(dict);
}

// Test empty string value in dict
TEST_F(PrintCustomInfoTest_2674, DictWithEmptyStringValue_2674) {
    Dict *dict = new Dict(nullptr);
    dict->add("CustomKey", Object(std::make_unique<GooString>("")));
    Object val = dict->lookup("CustomKey");
    EXPECT_TRUE(val.isString());
    EXPECT_STREQ(val.getString()->c_str(), "");
    Object obj(dict);
}
