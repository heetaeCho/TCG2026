// File: tests/value_getArray_test.cpp

#include <gtest/gtest.h>
#include "JsonBox/Value.h"
#include <type_traits>

namespace JsonBox {
// Make EMPTY_ARRAY visible so we can verify whether getArray() returns it.
extern const Array EMPTY_ARRAY;
}

using namespace JsonBox;

class ValueGetArrayTest_56 : public ::testing::Test {};

// Normal operation: when the Value is constructed with an Array, getArray()
// returns that array (same contents) and NOT the global EMPTY_ARRAY.
TEST_F(ValueGetArrayTest_56, ReturnsInternalArrayWhenTypeIsArray_56) {
    Array input;
    input.push_back(Value(1));
    input.push_back(Value("x"));

    Value v(input);

    const Array& out = v.getArray();
    ASSERT_EQ(out.size(), 2u);
    EXPECT_NE(&out, &EMPTY_ARRAY) << "Array Value should not alias EMPTY_ARRAY";
    EXPECT_TRUE(out[0].isInteger());
    EXPECT_EQ(out[0].getInteger(), 1);
    EXPECT_TRUE(out[1].isString());
    EXPECT_EQ(out[1].getString(), "x");
}

// Boundary: when constructed with an EMPTY array, getArray() should still
// return a distinct array (not EMPTY_ARRAY), but of size 0.
TEST_F(ValueGetArrayTest_56, EmptyArrayIsDistinctFromEMPTY_ARRAY_56) {
    Array empty_input;
    Value v(empty_input);

    const Array& out = v.getArray();
    EXPECT_TRUE(out.empty());
    EXPECT_NE(&out, &EMPTY_ARRAY) << "Even empty array Values should not alias EMPTY_ARRAY";
}

// Non-array types should return a reference to the global EMPTY_ARRAY, and
// it should be empty.
TEST_F(ValueGetArrayTest_56, NonArrayTypesReturnEMPTY_ARRAY_56) {
    Value v_null;                 // default: NULL
    Value v_int(123);
    Value v_double(3.14);
    Value v_bool(true);
    Value v_str(std::string("hello"));
    Object obj; obj["k"] = Value(7);
    Value v_obj(obj);

    const Array* outs[] = {
        &v_null.getArray(),
        &v_int.getArray(),
        &v_double.getArray(),
        &v_bool.getArray(),
        &v_str.getArray(),
        &v_obj.getArray()
    };

    for (const Array* p : outs) {
        ASSERT_NE(p, nullptr);
        EXPECT_EQ(p, &EMPTY_ARRAY) << "Non-array Value must return EMPTY_ARRAY";
        EXPECT_TRUE(p->empty());
    }
}

// Repeated calls should return the same reference each time (no new temporaries).
TEST_F(ValueGetArrayTest_56, RepeatedCallsReturnSameReference_56) {
    // For array Value
    Array a; a.push_back(Value(false));
    Value v_arr(a);
    const Array* first_arr = &v_arr.getArray();
    const Array* second_arr = &v_arr.getArray();
    EXPECT_EQ(first_arr, second_arr);

    // For non-array Value (should be the EMPTY_ARRAY address repeatedly)
    Value v_non_array(42);
    const Array* first_non = &v_non_array.getArray();
    const Array* second_non = &v_non_array.getArray();
    EXPECT_EQ(first_non, second_non);
    EXPECT_EQ(first_non, &EMPTY_ARRAY);
}

// Using the public mutator: setArray() should make getArray() reflect the new value
// and not alias EMPTY_ARRAY (even when set to an empty array).
TEST_F(ValueGetArrayTest_56, SetArrayUpdatesObservableArray_56) {
    Value v; // start as null
    {
        Array a; a.push_back(Value("a")); a.push_back(Value("b"));
        v.setArray(a);
        const Array& out1 = v.getArray();
        ASSERT_EQ(out1.size(), 2u);
        EXPECT_NE(&out1, &EMPTY_ARRAY);
        EXPECT_TRUE(out1[0].isString());
        EXPECT_TRUE(out1[1].isString());
        EXPECT_EQ(out1[0].getString(), "a");
        EXPECT_EQ(out1[1].getString(), "b");
    }
    {
        Array empty;
        v.setArray(empty);
        const Array& out2 = v.getArray();
        EXPECT_TRUE(out2.empty());
        EXPECT_NE(&out2, &EMPTY_ARRAY) << "After setArray(empty), should still be a real array Value";
    }
}
