#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Object.h"
#include "Array.h"
#include "Dict.h"

// Helper to create a minimal XRef-free Dict
// We need to work with the public interface of Object

class ObjectGetDictTest_102 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that getDict() returns the correct Dict pointer when Object holds a Dict
TEST_F(ObjectGetDictTest_102, GetDictReturnsCorrectPointer_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    ASSERT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getDict(), d);
}

// Test that isDict() returns true for a dict object
TEST_F(ObjectGetDictTest_102, IsDictReturnsTrueForDictObject_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
}

// Test that isDict() returns false for non-dict objects
TEST_F(ObjectGetDictTest_102, IsDictReturnsFalseForNonDictObjects_102) {
    Object boolObj(true);
    EXPECT_FALSE(boolObj.isDict());
    
    Object intObj(42);
    EXPECT_FALSE(intObj.isDict());
    
    Object realObj(3.14);
    EXPECT_FALSE(realObj.isDict());
    
    Object nullObj = Object::null();
    EXPECT_FALSE(nullObj.isDict());
    
    Object noneObj;
    EXPECT_FALSE(noneObj.isDict());
}

// Test that getType() returns objDict for a dict object
TEST_F(ObjectGetDictTest_102, GetTypeReturnsObjDictForDictObject_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    EXPECT_EQ(obj.getType(), objDict);
}

// Test creating Object with various types and verifying they are not Dict
TEST_F(ObjectGetDictTest_102, BoolObjectIsNotDict_102) {
    Object obj(false);
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectGetDictTest_102, IntObjectIsNotDict_102) {
    Object obj(100);
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isInt());
}

TEST_F(ObjectGetDictTest_102, RealObjectIsNotDict_102) {
    Object obj(2.718);
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isReal());
}

TEST_F(ObjectGetDictTest_102, NullObjectIsNotDict_102) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectGetDictTest_102, ErrorObjectIsNotDict_102) {
    Object obj = Object::error();
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isError());
}

TEST_F(ObjectGetDictTest_102, EofObjectIsNotDict_102) {
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isEOF());
}

// Test move constructor preserves dict
TEST_F(ObjectGetDictTest_102, MoveConstructorPreservesDict_102) {
    Dict *d = new Dict(nullptr);
    Object obj1(d);
    
    ASSERT_TRUE(obj1.isDict());
    ASSERT_EQ(obj1.getDict(), d);
    
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isDict());
    EXPECT_EQ(obj2.getDict(), d);
}

// Test move assignment preserves dict
TEST_F(ObjectGetDictTest_102, MoveAssignmentPreservesDict_102) {
    Dict *d = new Dict(nullptr);
    Object obj1(d);
    
    Object obj2;
    obj2 = std::move(obj1);
    
    EXPECT_TRUE(obj2.isDict());
    EXPECT_EQ(obj2.getDict(), d);
}

// Test dictGetLength on an empty dict
TEST_F(ObjectGetDictTest_102, DictGetLengthOnEmptyDict_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    EXPECT_EQ(obj.dictGetLength(), 0);
}

// Test dictAdd and dictGetLength
TEST_F(ObjectGetDictTest_102, DictAddIncreasesLength_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    obj.dictAdd("key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    obj.dictAdd("key2", Object(3.14));
    EXPECT_EQ(obj.dictGetLength(), 2);
}

// Test dictLookup returns correct value
TEST_F(ObjectGetDictTest_102, DictLookupReturnsCorrectValue_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    obj.dictAdd("myKey", Object(99));
    
    Object result = obj.dictLookup("myKey");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 99);
}

// Test dictLookup for non-existent key returns null
TEST_F(ObjectGetDictTest_102, DictLookupNonExistentKeyReturnsNull_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    Object result = obj.dictLookup("nonExistent");
    EXPECT_TRUE(result.isNull());
}

// Test dictSet overwrites value
TEST_F(ObjectGetDictTest_102, DictSetOverwritesExistingValue_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    obj.dictAdd("key", Object(10));
    obj.dictSet("key", Object(20));
    
    Object result = obj.dictLookup("key");
    EXPECT_TRUE(result.isInt());
    EXPECT_EQ(result.getInt(), 20);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

// Test dictRemove
TEST_F(ObjectGetDictTest_102, DictRemoveReducesLength_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    obj.dictAdd("key1", Object(1));
    obj.dictAdd("key2", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object result = obj.dictLookup("key1");
    EXPECT_TRUE(result.isNull());
}

// Test dictGetKey
TEST_F(ObjectGetDictTest_102, DictGetKeyReturnsCorrectKey_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    obj.dictAdd("testKey", Object(42));
    
    const char *key = obj.dictGetKey(0);
    ASSERT_NE(key, nullptr);
    EXPECT_STREQ(key, "testKey");
}

// Test dictGetVal
TEST_F(ObjectGetDictTest_102, DictGetValReturnsCorrectValue_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    obj.dictAdd("a", Object(77));
    
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

// Test copy of dict object
TEST_F(ObjectGetDictTest_102, CopyOfDictObject_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    obj.dictAdd("x", Object(5));
    
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isDict());
    EXPECT_EQ(copied.getDict(), d);
}

// Test setToNull changes dict object to null
TEST_F(ObjectGetDictTest_102, SetToNullChangesDictToNull_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    EXPECT_TRUE(obj.isDict());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_FALSE(obj.isDict());
}

// Test getTypeName for dict object
TEST_F(ObjectGetDictTest_102, GetTypeNameForDictObject_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    const char *name = obj.getTypeName();
    ASSERT_NE(name, nullptr);
    EXPECT_STREQ(name, "dictionary");
}

// Test Int64 object is not dict
TEST_F(ObjectGetDictTest_102, Int64ObjectIsNotDict_102) {
    Object obj(static_cast<long long>(123456789LL));
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isInt64());
}

// Test Array object is not Dict
TEST_F(ObjectGetDictTest_102, ArrayObjectIsNotDict_102) {
    Array *a = new Array(nullptr);
    Object obj(a);
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isArray());
}

// Test Name object is not Dict
TEST_F(ObjectGetDictTest_102, NameObjectIsNotDict_102) {
    Object obj(objName, "SomeName");
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isName());
}

// Test String object is not Dict
TEST_F(ObjectGetDictTest_102, StringObjectIsNotDict_102) {
    Object obj(std::make_unique<GooString>("hello"));
    EXPECT_FALSE(obj.isDict());
    EXPECT_TRUE(obj.isString());
}

// Test dictIs with a typed dict
TEST_F(ObjectGetDictTest_102, DictIsWithType_102) {
    Dict *d = new Dict(nullptr);
    d->add("Type", Object(objName, "Page"));
    Object obj(d);
    
    EXPECT_TRUE(obj.isDict("Page"));
    EXPECT_FALSE(obj.isDict("Catalog"));
}

// Test dictIs with no type set
TEST_F(ObjectGetDictTest_102, DictIsWithNoTypeSet_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    // With no "Type" entry, dictIs with empty string should return true for any
    // but with a specific type should return false
    EXPECT_FALSE(obj.isDict("Page"));
}

// Test multiple dict operations in sequence
TEST_F(ObjectGetDictTest_102, MultipleDictOperations_102) {
    Dict *d = new Dict(nullptr);
    Object obj(d);
    
    // Add multiple entries
    obj.dictAdd("a", Object(1));
    obj.dictAdd("b", Object(2));
    obj.dictAdd("c", Object(3));
    EXPECT_EQ(obj.dictGetLength(), 3);
    
    // Lookup all
    Object a = obj.dictLookup("a");
    EXPECT_EQ(a.getInt(), 1);
    Object b = obj.dictLookup("b");
    EXPECT_EQ(b.getInt(), 2);
    Object c = obj.dictLookup("c");
    EXPECT_EQ(c.getInt(), 3);
    
    // Remove middle
    obj.dictRemove("b");
    EXPECT_EQ(obj.dictGetLength(), 2);
    
    Object bAfter = obj.dictLookup("b");
    EXPECT_TRUE(bAfter.isNull());
    
    // Set new value
    obj.dictSet("a", Object(100));
    Object aNew = obj.dictLookup("a");
    EXPECT_EQ(aNew.getInt(), 100);
}
