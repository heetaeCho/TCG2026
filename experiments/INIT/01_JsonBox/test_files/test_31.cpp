#include <gtest/gtest.h>
#include "JsonBox/Value.h"

using namespace JsonBox;

class ValueOperatorArrayIndexTest_31 : public ::testing::Test {
protected:
    Value val; // fresh Value for each test
};

// Creates an array from a non-array (NULL_VALUE) and returns a reference to a default element.
TEST_F(ValueOperatorArrayIndexTest_31, CreatesArrayWhenNotArray_31) {
    Value &element = val[0];
    EXPECT_TRUE(val.isArray());
    EXPECT_TRUE(element.isNull()); // Newly materialized element should be default/null
}

// Accessing index > 0 on a non-array creates an array sized index+1.
TEST_F(ValueOperatorArrayIndexTest_31, CreatesArrayWithSizeIndexPlusOne_31) {
    size_t index = 3;
    Value &element = val[index];
    EXPECT_TRUE(val.isArray());
    const Array &arr = val.getArray();
    EXPECT_EQ(arr.size(), index + 1);
    EXPECT_TRUE(element.isNull());
}

// Accessing an in-bounds index on an existing array returns that element by reference.
TEST_F(ValueOperatorArrayIndexTest_31, ReturnsReferenceToExistingElement_31) {
    Array arr(2);
    arr[0] = 42;
    arr[1] = "test";
    val = arr;

    Value &element = val[1];
    EXPECT_TRUE(element.isString());
    EXPECT_EQ(element.getString(), "test");
}

// Out-of-bounds access on an existing array resizes it to index+1 and returns a default element.
TEST_F(ValueOperatorArrayIndexTest_31, ResizesArrayWhenIndexOutOfBounds_31) {
    Array arr(2);
    arr[0] = 1;
    arr[1] = 2;
    val = arr;

    size_t index = 5;
    Value &element = val[index];
    EXPECT_TRUE(val.isArray());
    EXPECT_EQ(val.getArray().size(), index + 1);
    EXPECT_TRUE(element.isNull()); // Newly added slot should be default/null

    // Existing elements remain intact after resize.
    EXPECT_TRUE(val[0].isInteger());
    EXPECT_EQ(val[0].getInteger(), 1);
    EXPECT_TRUE(val[1].isInteger());
    EXPECT_EQ(val[1].getInteger(), 2);
}

// The returned reference is writable; assignment through it updates the array.
TEST_F(ValueOperatorArrayIndexTest_31, ReturnedReferenceIsWritable_31) {
    Value &ref = val[2]; // forces array creation and resize
    EXPECT_TRUE(val.isArray());
    EXPECT_EQ(val.getArray().size(), 3u);
    EXPECT_TRUE(ref.isNull());

    ref = 99; // write through returned reference
    EXPECT_TRUE(val[2].isInteger());
    EXPECT_EQ(val[2].getInteger(), 99);
}

// Converting from another non-array type (e.g., OBJECT) to ARRAY via operator[].
TEST_F(ValueOperatorArrayIndexTest_31, ConvertsFromOtherTypeToArray_31) {
    // Start as object
    Object obj;
    obj["k"] = "v";
    val = obj;
    EXPECT_TRUE(val.isObject());

    // Indexing should convert to array and make space
    Value &e = val[1];
    EXPECT_TRUE(val.isArray());
    EXPECT_EQ(val.getArray().size(), 2u);
    EXPECT_TRUE(e.isNull());
}

// Repeated indexing grows but never shrinks; existing values persist.
TEST_F(ValueOperatorArrayIndexTest_31, MultipleIndexingGrowsAndPreserves_31) {
    val[0] = "a";
    EXPECT_TRUE(val.isArray());
    EXPECT_EQ(val.getArray().size(), 1u);

    // Grow to 4
    (void)val[3];
    EXPECT_EQ(val.getArray().size(), 4u);

    // Original value still present
    EXPECT_TRUE(val[0].isString());
    EXPECT_EQ(val[0].getString(), "a");

    // Grow again
    (void)val[7];
    EXPECT_EQ(val.getArray().size(), 8u);
    EXPECT_TRUE(val[7].isNull());
}

// Index 0 on a pre-sized array returns the same element without changing size.
TEST_F(ValueOperatorArrayIndexTest_31, IndexZeroOnExistingArray_NoResize_31) {
    Array arr(3);
    arr[0] = "first";
    val = arr;

    Value &e0 = val[0];
    EXPECT_EQ(val.getArray().size(), 3u);
    EXPECT_TRUE(e0.isString());
    EXPECT_EQ(e0.getString(), "first");
}
