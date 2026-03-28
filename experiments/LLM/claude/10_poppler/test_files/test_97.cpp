#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"
#include "GooString.h"
#include "Array.h"
#include "Dict.h"

// Helper to create a minimal XRef-free Dict for testing
// We need to be careful about ownership and lifecycle

class ObjectTest_97 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// =============================================================================
// Default Constructor Tests
// =============================================================================

TEST_F(ObjectTest_97, DefaultConstructor_CreatesNoneType_97) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

// =============================================================================
// Bool Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, BoolConstructor_True_97) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_97, BoolConstructor_False_97) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

// =============================================================================
// Int Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, IntConstructor_PositiveValue_97) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_97, IntConstructor_Zero_97) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_97, IntConstructor_NegativeValue_97) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_97, IntIsNum_97) {
    Object obj(42);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 42.0);
}

TEST_F(ObjectTest_97, IntIsIntOrInt64_97) {
    Object obj(42);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), 42LL);
}

// =============================================================================
// Real (double) Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, RealConstructor_PositiveValue_97) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_97, RealConstructor_Zero_97) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_97, RealConstructor_Negative_97) {
    Object obj(-2.718);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -2.718);
}

TEST_F(ObjectTest_97, RealIsNum_97) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isNum());
    EXPECT_DOUBLE_EQ(obj.getNum(), 3.14);
}

// =============================================================================
// Int64 Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, Int64Constructor_97) {
    long long val = 1234567890123LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_97, Int64IsIntOrInt64_97) {
    long long val = 9876543210LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

// =============================================================================
// String Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, StringConstructor_GooString_97) {
    auto str = std::make_unique<GooString>("hello");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "hello");
}

TEST_F(ObjectTest_97, StringConstructor_StdString_97) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_STREQ(obj.getString()->c_str(), "world");
}

// =============================================================================
// takeString Tests
// =============================================================================

TEST_F(ObjectTest_97, TakeString_ReturnsStringAndNullifiesObject_97) {
    auto str = std::make_unique<GooString>("takeMe");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());

    std::unique_ptr<GooString> taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "takeMe");

    // After takeString, object should become null
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_97, TakeString_EmptyString_97) {
    auto str = std::make_unique<GooString>("");
    Object obj(std::move(str));
    EXPECT_TRUE(obj.isString());

    std::unique_ptr<GooString> taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
    EXPECT_STREQ(taken->c_str(), "");

    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// HexString Constructor Tests
// =============================================================================

TEST_F(ObjectTest_97, HexStringConstructor_97) {
    Object obj(ObjType::objHexString, std::string_view("DEADBEEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
    EXPECT_STREQ(obj.getHexString()->c_str(), "DEADBEEF");
}

// =============================================================================
// Name Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, NameConstructor_97) {
    Object obj(ObjType::objName, "TestName");
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    ASSERT_NE(obj.getName(), nullptr);
    EXPECT_STREQ(obj.getName(), "TestName");
}

TEST_F(ObjectTest_97, NameIsNameWithMatch_97) {
    Object obj(ObjType::objName, "Catalog");
    EXPECT_TRUE(obj.isName("Catalog"));
    EXPECT_FALSE(obj.isName("Pages"));
}

TEST_F(ObjectTest_97, GetNameString_97) {
    Object obj(ObjType::objName, "SomeName");
    std::string nameStr = obj.getNameString();
    EXPECT_EQ(nameStr, "SomeName");
}

// =============================================================================
// Cmd Constructor and Accessor Tests
// =============================================================================

TEST_F(ObjectTest_97, CmdConstructor_97) {
    Object obj(ObjType::objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    ASSERT_NE(obj.getCmd(), nullptr);
    EXPECT_STREQ(obj.getCmd(), "q");
}

TEST_F(ObjectTest_97, CmdIsCmd_WithMatch_97) {
    Object obj(ObjType::objCmd, "BT");
    EXPECT_TRUE(obj.isCmd("BT"));
    EXPECT_FALSE(obj.isCmd("ET"));
}

// =============================================================================
// Null Object Tests
// =============================================================================

TEST_F(ObjectTest_97, NullStaticFactory_97) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

// =============================================================================
// EOF Object Tests
// =============================================================================

TEST_F(ObjectTest_97, EofStaticFactory_97) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

// =============================================================================
// Error Object Tests
// =============================================================================

TEST_F(ObjectTest_97, ErrorStaticFactory_97) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// =============================================================================
// setToNull Tests
// =============================================================================

TEST_F(ObjectTest_97, SetToNull_FromInt_97) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_97, SetToNull_FromBool_97) {
    Object obj(true);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

TEST_F(ObjectTest_97, SetToNull_FromString_97) {
    Object obj(std::make_unique<GooString>("test"));
    EXPECT_TRUE(obj.isString());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// =============================================================================
// Move Constructor Tests
// =============================================================================

TEST_F(ObjectTest_97, MoveConstructor_Int_97) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
    // After move, obj1 should be in a valid but unspecified state (typically objNone)
    EXPECT_TRUE(obj1.isNone());
}

TEST_F(ObjectTest_97, MoveConstructor_String_97) {
    Object obj1(std::make_unique<GooString>("moved"));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isString());
    EXPECT_STREQ(obj2.getString()->c_str(), "moved");
    EXPECT_TRUE(obj1.isNone());
}

// =============================================================================
// Move Assignment Tests
// =============================================================================

TEST_F(ObjectTest_97, MoveAssignment_97) {
    Object obj1(100);
    Object obj2(3.14);
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 100);
    EXPECT_TRUE(obj1.isNone());
}

// =============================================================================
// Type Check Negative Tests
// =============================================================================

TEST_F(ObjectTest_97, IntIsNotBool_97) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
    EXPECT_FALSE(obj.isInt64());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_97, BoolIsNotInt_97) {
    Object obj(true);
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isNull());
    EXPECT_FALSE(obj.isNum());
}

// =============================================================================
// Copy Tests
// =============================================================================

TEST_F(ObjectTest_97, Copy_IntObject_97) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_97, Copy_BoolObject_97) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_97, Copy_RealObject_97) {
    Object obj(2.5);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 2.5);
}

TEST_F(ObjectTest_97, Copy_StringObject_97) {
    Object obj(std::make_unique<GooString>("copyMe"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_STREQ(copied.getString()->c_str(), "copyMe");
    // Original should still be valid
    EXPECT_TRUE(obj.isString());
    EXPECT_STREQ(obj.getString()->c_str(), "copyMe");
}

TEST_F(ObjectTest_97, Copy_NullObject_97) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

// =============================================================================
// getNumWithDefaultValue Tests
// =============================================================================

TEST_F(ObjectTest_97, GetNumWithDefaultValue_IntObject_97) {
    Object obj(10);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 10.0);
}

TEST_F(ObjectTest_97, GetNumWithDefaultValue_RealObject_97) {
    Object obj(3.14);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 3.14);
}

TEST_F(ObjectTest_97, GetNumWithDefaultValue_NonNumericReturnsDefault_97) {
    Object obj(true);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

TEST_F(ObjectTest_97, GetNumWithDefaultValue_NullReturnsDefault_97) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(42.0), 42.0);
}

// =============================================================================
// getBoolWithDefaultValue Tests
// =============================================================================

TEST_F(ObjectTest_97, GetBoolWithDefaultValue_BoolTrue_97) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_97, GetBoolWithDefaultValue_BoolFalse_97) {
    Object obj(false);
    EXPECT_FALSE(obj.getBoolWithDefaultValue(true));
}

TEST_F(ObjectTest_97, GetBoolWithDefaultValue_NonBoolReturnsDefault_97) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// =============================================================================
// getTypeName Tests
// =============================================================================

TEST_F(ObjectTest_97, GetTypeName_Bool_97) {
    Object obj(true);
    ASSERT_NE(obj.getTypeName(), nullptr);
    // Just verify it returns something non-null for different types
}

TEST_F(ObjectTest_97, GetTypeName_Int_97) {
    Object obj(42);
    ASSERT_NE(obj.getTypeName(), nullptr);
}

TEST_F(ObjectTest_97, GetTypeName_Null_97) {
    Object obj = Object::null();
    ASSERT_NE(obj.getTypeName(), nullptr);
}

// =============================================================================
// Array Tests
// =============================================================================

TEST_F(ObjectTest_97, ArrayConstructor_97) {
    // Create a simple array-based Object using Array
    // Array requires an XRef pointer; passing nullptr for minimal testing
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_97, ArrayAdd_97) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_97, ArrayAddMultiple_97) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    
    Object e0 = obj.arrayGet(0);
    Object e1 = obj.arrayGet(1);
    Object e2 = obj.arrayGet(2);
    EXPECT_EQ(e0.getInt(), 1);
    EXPECT_EQ(e1.getInt(), 2);
    EXPECT_EQ(e2.getInt(), 3);
}

TEST_F(ObjectTest_97, ArrayRemove_97) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);
    
    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    
    Object e0 = obj.arrayGet(0);
    Object e1 = obj.arrayGet(1);
    EXPECT_EQ(e0.getInt(), 10);
    EXPECT_EQ(e1.getInt(), 30);
}

TEST_F(ObjectTest_97, ArrayGetNF_97) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    
    const Object &nf = obj.arrayGetNF(0);
    EXPECT_TRUE(nf.isInt());
    EXPECT_EQ(nf.getInt(), 42);
}

// =============================================================================
// Dict Tests
// =============================================================================

TEST_F(ObjectTest_97, DictConstructor_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_97, DictAdd_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(100));
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 100);
}

TEST_F(ObjectTest_97, DictSet_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(100));
    obj.dictSet("key1", Object(200));
    
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 200);
}

TEST_F(ObjectTest_97, DictRemove_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key1", Object(100));
    obj.dictAdd("key2", Object(200));
    EXPECT_EQ(obj.dictGetLength(), 2);
    
    obj.dictRemove("key1");
    EXPECT_EQ(obj.dictGetLength(), 1);
    
    Object val = obj.dictLookup("key1");
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_97, DictGetKey_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("alpha", Object(1));
    
    const char *key = obj.dictGetKey(0);
    ASSERT_NE(key, nullptr);
    EXPECT_STREQ(key, "alpha");
}

TEST_F(ObjectTest_97, DictGetVal_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key", Object(42));
    
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_97, DictGetValNF_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("key", Object(42));
    
    const Object &val = obj.dictGetValNF(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_97, DictLookupNF_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("mykey", Object(99));
    
    const Object &val = obj.dictLookupNF("mykey");
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
}

TEST_F(ObjectTest_97, DictLookup_NonExistentKey_97) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("existing", Object(1));
    
    Object val = obj.dictLookup("nonexistent");
    EXPECT_TRUE(val.isNull());
}

// =============================================================================
// getNum with ok parameter Tests
// =============================================================================

TEST_F(ObjectTest_97, GetNumWithOk_ValidInt_97) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_97, GetNumWithOk_ValidReal_97) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// =============================================================================
// Destructor / Lifetime Tests (no leaks)
// =============================================================================

TEST_F(ObjectTest_97, DestructorHandlesString_97) {
    // Just ensure no crash/leak
    {
        Object obj(std::make_unique<GooString>("destructMe"));
        EXPECT_TRUE(obj.isString());
    }
}

TEST_F(ObjectTest_97, DestructorHandlesArray_97) {
    {
        Array *arr = new Array(nullptr);
        Object obj(arr);
        obj.arrayAdd(Object(1));
        obj.arrayAdd(Object(2));
    }
}

TEST_F(ObjectTest_97, DestructorHandlesDict_97) {
    {
        Dict *dict = new Dict(nullptr);
        Object obj(dict);
        obj.dictAdd("k", Object(1));
    }
}

// =============================================================================
// Boundary / Edge Cases
// =============================================================================

TEST_F(ObjectTest_97, IntMaxValue_97) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_97, IntMinValue_97) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_97, Int64MaxValue_97) {
    long long maxVal = std::numeric_limits<long long>::max();
    Object obj(maxVal);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), maxVal);
}

TEST_F(ObjectTest_97, RealVerySmall_97) {
    Object obj(1e-300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e-300);
}

TEST_F(ObjectTest_97, RealVeryLarge_97) {
    Object obj(1e300);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 1e300);
}

TEST_F(ObjectTest_97, EmptyNameString_97) {
    Object obj(ObjType::objName, "");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "");
}

TEST_F(ObjectTest_97, MoveAssignmentSelfType_97) {
    Object obj(42);
    Object obj2(99);
    obj = std::move(obj2);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 99);
}

// =============================================================================
// DeepCopy Tests
// =============================================================================

TEST_F(ObjectTest_97, DeepCopy_Int_97) {
    Object obj(42);
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isInt());
    EXPECT_EQ(deep.getInt(), 42);
}

TEST_F(ObjectTest_97, DeepCopy_String_97) {
    Object obj(std::make_unique<GooString>("deepCopy"));
    Object deep = obj.deepCopy();
    EXPECT_TRUE(deep.isString());
    EXPECT_STREQ(deep.getString()->c_str(), "deepCopy");
    // Ensure original is still valid
    EXPECT_TRUE(obj.isString());
    EXPECT_STREQ(obj.getString()->c_str(), "deepCopy");
}
