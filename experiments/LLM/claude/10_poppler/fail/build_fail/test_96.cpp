#include <gtest/gtest.h>
#include <memory>
#include <string>
#include "Object.h"
#include "GooString.h"
#include "Array.h"
#include "Dict.h"

// Helper to create a minimal XRef-less Dict for testing
// We need to be careful about ownership and lifecycle

class ObjectTest_96 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// ============================================================
// Tests for default constructor and special static constructors
// ============================================================

TEST_F(ObjectTest_96, DefaultConstructorIsNone_96) {
    Object obj;
    EXPECT_TRUE(obj.isNone());
    EXPECT_EQ(obj.getType(), objNone);
}

TEST_F(ObjectTest_96, NullStaticConstructor_96) {
    Object obj = Object::null();
    EXPECT_TRUE(obj.isNull());
    EXPECT_EQ(obj.getType(), objNull);
}

TEST_F(ObjectTest_96, EofStaticConstructor_96) {
    Object obj = Object::eof();
    EXPECT_TRUE(obj.isEOF());
    EXPECT_EQ(obj.getType(), objEOF);
}

TEST_F(ObjectTest_96, ErrorStaticConstructor_96) {
    Object obj = Object::error();
    EXPECT_TRUE(obj.isError());
    EXPECT_EQ(obj.getType(), objError);
}

// ============================================================
// Tests for bool type
// ============================================================

TEST_F(ObjectTest_96, BoolConstructorTrue_96) {
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getType(), objBool);
    EXPECT_TRUE(obj.getBool());
}

TEST_F(ObjectTest_96, BoolConstructorFalse_96) {
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
    EXPECT_FALSE(obj.getBool());
}

TEST_F(ObjectTest_96, GetBoolWithDefaultValueWhenBool_96) {
    Object obj(true);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(false));
}

TEST_F(ObjectTest_96, GetBoolWithDefaultValueWhenNotBool_96) {
    Object obj(42);
    EXPECT_TRUE(obj.getBoolWithDefaultValue(true));
    EXPECT_FALSE(obj.getBoolWithDefaultValue(false));
}

// ============================================================
// Tests for int type
// ============================================================

TEST_F(ObjectTest_96, IntConstructor_96) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getType(), objInt);
    EXPECT_EQ(obj.getInt(), 42);
}

TEST_F(ObjectTest_96, IntConstructorZero_96) {
    Object obj(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 0);
}

TEST_F(ObjectTest_96, IntConstructorNegative_96) {
    Object obj(-100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), -100);
}

TEST_F(ObjectTest_96, IntIsNum_96) {
    Object obj(5);
    EXPECT_TRUE(obj.isNum());
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_96, IntGetNum_96) {
    Object obj(7);
    EXPECT_DOUBLE_EQ(obj.getNum(), 7.0);
}

TEST_F(ObjectTest_96, IntGetIntOrInt64_96) {
    Object obj(123);
    EXPECT_EQ(obj.getIntOrInt64(), 123LL);
}

// ============================================================
// Tests for real (double) type
// ============================================================

TEST_F(ObjectTest_96, RealConstructor_96) {
    Object obj(3.14);
    EXPECT_TRUE(obj.isReal());
    EXPECT_EQ(obj.getType(), objReal);
    EXPECT_DOUBLE_EQ(obj.getReal(), 3.14);
}

TEST_F(ObjectTest_96, RealIsNum_96) {
    Object obj(2.5);
    EXPECT_TRUE(obj.isNum());
}

TEST_F(ObjectTest_96, RealGetNum_96) {
    Object obj(2.718);
    EXPECT_DOUBLE_EQ(obj.getNum(), 2.718);
}

TEST_F(ObjectTest_96, RealZero_96) {
    Object obj(0.0);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), 0.0);
}

TEST_F(ObjectTest_96, RealNegative_96) {
    Object obj(-1.5);
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), -1.5);
}

TEST_F(ObjectTest_96, GetNumWithDefaultValueWhenNum_96) {
    Object obj(42.0);
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(0.0), 42.0);
}

TEST_F(ObjectTest_96, GetNumWithDefaultValueWhenNotNum_96) {
    Object obj = Object::null();
    EXPECT_DOUBLE_EQ(obj.getNumWithDefaultValue(99.0), 99.0);
}

// ============================================================
// Tests for int64 type
// ============================================================

TEST_F(ObjectTest_96, Int64Constructor_96) {
    long long val = 9999999999LL;
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getType(), objInt64);
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_96, Int64IsIntOrInt64_96) {
    long long val = 100LL;
    Object obj(val);
    EXPECT_TRUE(obj.isIntOrInt64());
}

TEST_F(ObjectTest_96, Int64GetIntOrInt64_96) {
    long long val = 5000000000LL;
    Object obj(val);
    EXPECT_EQ(obj.getIntOrInt64(), val);
}

TEST_F(ObjectTest_96, Int64IsNum_96) {
    long long val = 42LL;
    Object obj(val);
    EXPECT_TRUE(obj.isNum());
}

// ============================================================
// Tests for string type
// ============================================================

TEST_F(ObjectTest_96, StringConstructorFromGooString_96) {
    auto gs = std::make_unique<GooString>("hello");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getType(), objString);
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "hello");
}

TEST_F(ObjectTest_96, StringConstructorFromStdString_96) {
    std::string s = "world";
    Object obj(std::move(s));
    EXPECT_TRUE(obj.isString());
    ASSERT_NE(obj.getString(), nullptr);
    EXPECT_EQ(obj.getString()->toStr(), "world");
}

TEST_F(ObjectTest_96, StringTakeString_96) {
    auto gs = std::make_unique<GooString>("take me");
    Object obj(std::move(gs));
    auto taken = obj.takeString();
    ASSERT_NE(taken, nullptr);
    EXPECT_EQ(taken->toStr(), "take me");
}

TEST_F(ObjectTest_96, EmptyStringConstructor_96) {
    auto gs = std::make_unique<GooString>("");
    Object obj(std::move(gs));
    EXPECT_TRUE(obj.isString());
    EXPECT_EQ(obj.getString()->toStr(), "");
}

// ============================================================
// Tests for hex string type
// ============================================================

TEST_F(ObjectTest_96, HexStringConstructor_96) {
    Object obj(objHexString, std::string_view("ABCDEF"));
    EXPECT_TRUE(obj.isHexString());
    EXPECT_EQ(obj.getType(), objHexString);
    ASSERT_NE(obj.getHexString(), nullptr);
    EXPECT_EQ(obj.getHexString()->toStr(), "ABCDEF");
}

// ============================================================
// Tests for name type
// ============================================================

TEST_F(ObjectTest_96, NameConstructor_96) {
    Object obj(objName, std::string_view("MyName"));
    EXPECT_TRUE(obj.isName());
    EXPECT_EQ(obj.getType(), objName);
    ASSERT_NE(obj.getName(), nullptr);
    EXPECT_STREQ(obj.getName(), "MyName");
}

TEST_F(ObjectTest_96, NameIsNameMatching_96) {
    Object obj(objName, std::string_view("Type"));
    EXPECT_TRUE(obj.isName("Type"));
    EXPECT_FALSE(obj.isName("Other"));
}

TEST_F(ObjectTest_96, NameGetNameString_96) {
    Object obj(objName, std::string_view("TestName"));
    EXPECT_EQ(obj.getNameString(), "TestName");
}

// ============================================================
// Tests for cmd type
// ============================================================

TEST_F(ObjectTest_96, CmdConstructor_96) {
    Object obj(objCmd, std::string_view("BT"));
    EXPECT_TRUE(obj.isCmd());
    EXPECT_EQ(obj.getType(), objCmd);
    ASSERT_NE(obj.getCmd(), nullptr);
    EXPECT_STREQ(obj.getCmd(), "BT");
}

TEST_F(ObjectTest_96, CmdIsCmdMatching_96) {
    Object obj(objCmd, std::string_view("ET"));
    EXPECT_TRUE(obj.isCmd("ET"));
    EXPECT_FALSE(obj.isCmd("BT"));
}

// ============================================================
// Tests for type checking negative cases
// ============================================================

TEST_F(ObjectTest_96, IntIsNotBool_96) {
    Object obj(42);
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
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
    EXPECT_FALSE(obj.isHexString());
}

TEST_F(ObjectTest_96, NullIsNotOtherTypes_96) {
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
    EXPECT_FALSE(obj.isInt());
    EXPECT_FALSE(obj.isReal());
    EXPECT_FALSE(obj.isString());
    EXPECT_FALSE(obj.isName());
    EXPECT_FALSE(obj.isArray());
    EXPECT_FALSE(obj.isDict());
    EXPECT_FALSE(obj.isStream());
    EXPECT_FALSE(obj.isRef());
    EXPECT_FALSE(obj.isCmd());
    EXPECT_FALSE(obj.isError());
    EXPECT_FALSE(obj.isEOF());
    EXPECT_FALSE(obj.isNone());
}

// ============================================================
// Tests for move semantics
// ============================================================

TEST_F(ObjectTest_96, MoveConstructor_96) {
    Object obj1(42);
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_96, MoveAssignment_96) {
    Object obj1(42);
    Object obj2;
    obj2 = std::move(obj1);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 42);
}

TEST_F(ObjectTest_96, MoveStringObject_96) {
    auto gs = std::make_unique<GooString>("moved");
    Object obj1(std::move(gs));
    Object obj2(std::move(obj1));
    EXPECT_TRUE(obj2.isString());
    EXPECT_EQ(obj2.getString()->toStr(), "moved");
}

// ============================================================
// Tests for setToNull
// ============================================================

TEST_F(ObjectTest_96, SetToNull_96) {
    Object obj(42);
    EXPECT_TRUE(obj.isInt());
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
}

// ============================================================
// Tests for copy
// ============================================================

TEST_F(ObjectTest_96, CopyInt_96) {
    Object obj(42);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_96, CopyBool_96) {
    Object obj(true);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isBool());
    EXPECT_TRUE(copied.getBool());
}

TEST_F(ObjectTest_96, CopyReal_96) {
    Object obj(3.14);
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isReal());
    EXPECT_DOUBLE_EQ(copied.getReal(), 3.14);
}

TEST_F(ObjectTest_96, CopyString_96) {
    auto gs = std::make_unique<GooString>("copytest");
    Object obj(std::move(gs));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isString());
    EXPECT_EQ(copied.getString()->toStr(), "copytest");
}

TEST_F(ObjectTest_96, CopyNull_96) {
    Object obj = Object::null();
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isNull());
}

TEST_F(ObjectTest_96, CopyName_96) {
    Object obj(objName, std::string_view("CopyName"));
    Object copied = obj.copy();
    EXPECT_TRUE(copied.isName());
    EXPECT_STREQ(copied.getName(), "CopyName");
}

// ============================================================
// Tests for array operations
// ============================================================

TEST_F(ObjectTest_96, ArrayConstructorAndBasicOps_96) {
    // Create a Dict for the XRef (nullptr should work for basic array ops)
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_TRUE(obj.isArray());
    EXPECT_EQ(obj.getType(), objArray);
    EXPECT_EQ(obj.arrayGetLength(), 0);
}

TEST_F(ObjectTest_96, ArrayAddAndGet_96) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    EXPECT_EQ(obj.arrayGetLength(), 1);
    Object elem = obj.arrayGet(0, 0);
    EXPECT_TRUE(elem.isInt());
    EXPECT_EQ(elem.getInt(), 42);
}

TEST_F(ObjectTest_96, ArrayAddMultipleElements_96) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(1));
    obj.arrayAdd(Object(2));
    obj.arrayAdd(Object(3));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    Object e0 = obj.arrayGet(0, 0);
    EXPECT_EQ(e0.getInt(), 1);
    Object e1 = obj.arrayGet(1, 0);
    EXPECT_EQ(e1.getInt(), 2);
    Object e2 = obj.arrayGet(2, 0);
    EXPECT_EQ(e2.getInt(), 3);
}

TEST_F(ObjectTest_96, ArrayRemove_96) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(10));
    obj.arrayAdd(Object(20));
    obj.arrayAdd(Object(30));
    EXPECT_EQ(obj.arrayGetLength(), 3);

    obj.arrayRemove(1);
    EXPECT_EQ(obj.arrayGetLength(), 2);
    Object e0 = obj.arrayGet(0, 0);
    EXPECT_EQ(e0.getInt(), 10);
    Object e1 = obj.arrayGet(1, 0);
    EXPECT_EQ(e1.getInt(), 30);
}

TEST_F(ObjectTest_96, ArrayGetNF_96) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(99));
    const Object &ref = obj.arrayGetNF(0);
    EXPECT_TRUE(ref.isInt());
    EXPECT_EQ(ref.getInt(), 99);
}

TEST_F(ObjectTest_96, ArrayGetArray_96) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    EXPECT_EQ(obj.getArray(), arr);
}

// ============================================================
// Tests for dict operations
// ============================================================

TEST_F(ObjectTest_96, DictConstructorAndBasicOps_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_TRUE(obj.isDict());
    EXPECT_EQ(obj.getType(), objDict);
    EXPECT_EQ(obj.dictGetLength(), 0);
}

TEST_F(ObjectTest_96, DictAddAndLookup_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("Key1", 0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 42);
}

TEST_F(ObjectTest_96, DictSetOverwrite_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Key1", Object(42));
    obj.dictSet("Key1", Object(99));
    Object val = obj.dictLookup("Key1", 0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 99);
    EXPECT_EQ(obj.dictGetLength(), 1);
}

TEST_F(ObjectTest_96, DictRemove_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2));
    EXPECT_EQ(obj.dictGetLength(), 2);
    obj.dictRemove("A");
    EXPECT_EQ(obj.dictGetLength(), 1);
    Object val = obj.dictLookup("A", 0);
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_96, DictGetKey_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("MyKey", Object(10));
    EXPECT_STREQ(obj.dictGetKey(0), "MyKey");
}

TEST_F(ObjectTest_96, DictGetVal_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(77));
    Object val = obj.dictGetVal(0);
    EXPECT_TRUE(val.isInt());
    EXPECT_EQ(val.getInt(), 77);
}

TEST_F(ObjectTest_96, DictGetValNF_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("K", Object(88));
    const Object &ref = obj.dictGetValNF(0);
    EXPECT_TRUE(ref.isInt());
    EXPECT_EQ(ref.getInt(), 88);
}

TEST_F(ObjectTest_96, DictLookupNF_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("Test", Object(55));
    const Object &ref = obj.dictLookupNF("Test");
    EXPECT_TRUE(ref.isInt());
    EXPECT_EQ(ref.getInt(), 55);
}

TEST_F(ObjectTest_96, DictLookupMissing_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    Object val = obj.dictLookup("NonExistent", 0);
    EXPECT_TRUE(val.isNull());
}

TEST_F(ObjectTest_96, DictGetDict_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    EXPECT_EQ(obj.getDict(), dict);
}

// ============================================================
// Tests for getTypeName
// ============================================================

TEST_F(ObjectTest_96, GetTypeNameBool_96) {
    Object obj(true);
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "boolean");
}

TEST_F(ObjectTest_96, GetTypeNameInt_96) {
    Object obj(42);
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "integer");
}

TEST_F(ObjectTest_96, GetTypeNameReal_96) {
    Object obj(1.5);
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "real");
}

TEST_F(ObjectTest_96, GetTypeNameString_96) {
    auto gs = std::make_unique<GooString>("s");
    Object obj(std::move(gs));
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "string");
}

TEST_F(ObjectTest_96, GetTypeNameNull_96) {
    Object obj = Object::null();
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "null");
}

TEST_F(ObjectTest_96, GetTypeNameError_96) {
    Object obj = Object::error();
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "error");
}

TEST_F(ObjectTest_96, GetTypeNameEOF_96) {
    Object obj = Object::eof();
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "eof");
}

TEST_F(ObjectTest_96, GetTypeNameNone_96) {
    Object obj;
    EXPECT_NE(obj.getTypeName(), nullptr);
    EXPECT_STREQ(obj.getTypeName(), "none");
}

// ============================================================
// Tests for getNum with ok parameter
// ============================================================

TEST_F(ObjectTest_96, GetNumWithOkParameterInt_96) {
    Object obj(42);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 42.0);
}

TEST_F(ObjectTest_96, GetNumWithOkParameterReal_96) {
    Object obj(3.14);
    bool ok = false;
    double val = obj.getNum(&ok);
    EXPECT_TRUE(ok);
    EXPECT_DOUBLE_EQ(val, 3.14);
}

// ============================================================
// Tests for deepCopy
// ============================================================

TEST_F(ObjectTest_96, DeepCopyInt_96) {
    Object obj(42);
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isInt());
    EXPECT_EQ(copied.getInt(), 42);
}

TEST_F(ObjectTest_96, DeepCopyString_96) {
    auto gs = std::make_unique<GooString>("deep");
    Object obj(std::move(gs));
    Object copied = obj.deepCopy();
    EXPECT_TRUE(copied.isString());
    EXPECT_EQ(copied.getString()->toStr(), "deep");
}

// ============================================================
// Tests for boundary conditions
// ============================================================

TEST_F(ObjectTest_96, IntMaxValue_96) {
    Object obj(std::numeric_limits<int>::max());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::max());
}

TEST_F(ObjectTest_96, IntMinValue_96) {
    Object obj(std::numeric_limits<int>::min());
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), std::numeric_limits<int>::min());
}

TEST_F(ObjectTest_96, Int64MaxValue_96) {
    long long val = std::numeric_limits<long long>::max();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_96, Int64MinValue_96) {
    long long val = std::numeric_limits<long long>::min();
    Object obj(val);
    EXPECT_TRUE(obj.isInt64());
    EXPECT_EQ(obj.getInt64(), val);
}

TEST_F(ObjectTest_96, RealVerySmall_96) {
    Object obj(std::numeric_limits<double>::min());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::min());
}

TEST_F(ObjectTest_96, RealVeryLarge_96) {
    Object obj(std::numeric_limits<double>::max());
    EXPECT_TRUE(obj.isReal());
    EXPECT_DOUBLE_EQ(obj.getReal(), std::numeric_limits<double>::max());
}

// ============================================================
// Tests for Object constructor with char* 
// ============================================================

TEST_F(ObjectTest_96, NameFromCharPtr_96) {
    Object obj(objName, "TestCharPtr");
    EXPECT_TRUE(obj.isName());
    EXPECT_STREQ(obj.getName(), "TestCharPtr");
}

TEST_F(ObjectTest_96, CmdFromCharPtr_96) {
    Object obj(objCmd, "q");
    EXPECT_TRUE(obj.isCmd());
    EXPECT_STREQ(obj.getCmd(), "q");
}

// ============================================================
// Tests for print (just ensure it doesn't crash)
// ============================================================

TEST_F(ObjectTest_96, PrintIntDoesNotCrash_96) {
    Object obj(42);
    // Print to /dev/null or suppress output
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    obj.print(f);
    fclose(f);
}

TEST_F(ObjectTest_96, PrintStringDoesNotCrash_96) {
    auto gs = std::make_unique<GooString>("printtest");
    Object obj(std::move(gs));
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    obj.print(f);
    fclose(f);
}

TEST_F(ObjectTest_96, PrintNullDoesNotCrash_96) {
    Object obj = Object::null();
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    obj.print(f);
    fclose(f);
}

TEST_F(ObjectTest_96, PrintBoolDoesNotCrash_96) {
    Object obj(true);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    obj.print(f);
    fclose(f);
}

TEST_F(ObjectTest_96, PrintRealDoesNotCrash_96) {
    Object obj(3.14);
    FILE *f = tmpfile();
    ASSERT_NE(f, nullptr);
    obj.print(f);
    fclose(f);
}

// ============================================================
// Tests for destructor and ownership (no leaks with ASAN)
// ============================================================

TEST_F(ObjectTest_96, DestructorString_96) {
    {
        auto gs = std::make_unique<GooString>("destructor test");
        Object obj(std::move(gs));
    }
    // If ASAN is enabled, a leak would be caught here
    SUCCEED();
}

TEST_F(ObjectTest_96, DestructorArray_96) {
    {
        Array *arr = new Array(nullptr);
        Object obj(arr);
        obj.arrayAdd(Object(1));
        obj.arrayAdd(Object(2));
    }
    SUCCEED();
}

TEST_F(ObjectTest_96, DestructorDict_96) {
    {
        Dict *dict = new Dict(nullptr);
        Object obj(dict);
        obj.dictAdd("key", Object(42));
    }
    SUCCEED();
}

// ============================================================
// Tests for multiple operations sequence
// ============================================================

TEST_F(ObjectTest_96, MoveAssignmentOverwritesExisting_96) {
    Object obj1(42);
    Object obj2(3.14);
    obj1 = std::move(obj2);
    EXPECT_TRUE(obj1.isReal());
    EXPECT_DOUBLE_EQ(obj1.getReal(), 3.14);
}

TEST_F(ObjectTest_96, SetToNullThenReassign_96) {
    Object obj(42);
    obj.setToNull();
    EXPECT_TRUE(obj.isNull());
    obj = Object(100);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 100);
}

// ============================================================
// Tests for isName and isCmd with non-matching types
// ============================================================

TEST_F(ObjectTest_96, IsNameOnNonNameReturnsFalse_96) {
    Object obj(42);
    EXPECT_FALSE(obj.isName("anything"));
}

TEST_F(ObjectTest_96, IsCmdOnNonCmdReturnsFalse_96) {
    Object obj(42);
    EXPECT_FALSE(obj.isCmd("anything"));
}

// ============================================================
// Tests for array with mixed types
// ============================================================

TEST_F(ObjectTest_96, ArrayMixedTypes_96) {
    Array *arr = new Array(nullptr);
    Object obj(arr);
    obj.arrayAdd(Object(42));
    obj.arrayAdd(Object(3.14));
    obj.arrayAdd(Object(true));
    auto gs = std::make_unique<GooString>("mixed");
    obj.arrayAdd(Object(std::move(gs)));
    obj.arrayAdd(Object::null());

    EXPECT_EQ(obj.arrayGetLength(), 5);

    Object e0 = obj.arrayGet(0, 0);
    EXPECT_TRUE(e0.isInt());
    EXPECT_EQ(e0.getInt(), 42);

    Object e1 = obj.arrayGet(1, 0);
    EXPECT_TRUE(e1.isReal());
    EXPECT_DOUBLE_EQ(e1.getReal(), 3.14);

    Object e2 = obj.arrayGet(2, 0);
    EXPECT_TRUE(e2.isBool());
    EXPECT_TRUE(e2.getBool());

    Object e3 = obj.arrayGet(3, 0);
    EXPECT_TRUE(e3.isString());
    EXPECT_EQ(e3.getString()->toStr(), "mixed");

    Object e4 = obj.arrayGet(4, 0);
    EXPECT_TRUE(e4.isNull());
}

// ============================================================
// Tests for dict with multiple entries
// ============================================================

TEST_F(ObjectTest_96, DictMultipleEntries_96) {
    Dict *dict = new Dict(nullptr);
    Object obj(dict);
    obj.dictAdd("A", Object(1));
    obj.dictAdd("B", Object(2.0));
    obj.dictAdd("C", Object(true));
    EXPECT_EQ(obj.dictGetLength(), 3);

    Object valA = obj.dictLookup("A", 0);
    EXPECT_TRUE(valA.isInt());
    EXPECT_EQ(valA.getInt(), 1);

    Object valB = obj.dictLookup("B", 0);
    EXPECT_TRUE(valB.isReal());
    EXPECT_DOUBLE_EQ(valB.getReal(), 2.0);

    Object valC = obj.dictLookup("C", 0);
    EXPECT_TRUE(valC.isBool());
    EXPECT_TRUE(valC.getBool());
}
