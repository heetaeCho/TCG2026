#include <gtest/gtest.h>
#include "Array.h"
#include "Object.h"
#include "XRef.h"

// We need to create a minimal test fixture that can construct Array objects.
// Array requires an XRef pointer, so we'll work with that.

class ArrayTest_112 : public ::testing::Test {
protected:
    void SetUp() override {
        // XRef may need a valid or null pointer depending on implementation
        // We'll try with nullptr first, as many poppler tests do
        xref = nullptr;
    }

    void TearDown() override {
    }

    XRef *xref;
};

// Test that a newly created array has length 0
TEST_F(ArrayTest_112, NewArrayHasZeroLength_112) {
    Array arr(xref);
    EXPECT_EQ(arr.getLength(), 0);
}

// Test that adding one element increases length to 1
TEST_F(ArrayTest_112, AddOneElementIncreasesLength_112) {
    Array arr(xref);
    arr.add(Object(1));
    EXPECT_EQ(arr.getLength(), 1);
}

// Test that adding multiple elements increases length correctly
TEST_F(ArrayTest_112, AddMultipleElementsIncreasesLength_112) {
    Array arr(xref);
    arr.add(Object(1));
    arr.add(Object(2));
    arr.add(Object(3));
    EXPECT_EQ(arr.getLength(), 3);
}

// Test that removing an element decreases length
TEST_F(ArrayTest_112, RemoveElementDecreasesLength_112) {
    Array arr(xref);
    arr.add(Object(1));
    arr.add(Object(2));
    arr.add(Object(3));
    EXPECT_EQ(arr.getLength(), 3);
    arr.remove(1);
    EXPECT_EQ(arr.getLength(), 2);
}

// Test removing the first element
TEST_F(ArrayTest_112, RemoveFirstElement_112) {
    Array arr(xref);
    arr.add(Object(10));
    arr.add(Object(20));
    arr.remove(0);
    EXPECT_EQ(arr.getLength(), 1);
}

// Test removing the last element
TEST_F(ArrayTest_112, RemoveLastElement_112) {
    Array arr(xref);
    arr.add(Object(10));
    arr.add(Object(20));
    arr.remove(1);
    EXPECT_EQ(arr.getLength(), 1);
}

// Test that get returns the correct integer value
TEST_F(ArrayTest_112, GetReturnsCorrectIntValue_112) {
    Array arr(xref);
    arr.add(Object(42));
    Object obj = arr.get(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 42);
}

// Test that get returns correct values for multiple elements
TEST_F(ArrayTest_112, GetReturnsCorrectValuesForMultipleElements_112) {
    Array arr(xref);
    arr.add(Object(10));
    arr.add(Object(20));
    arr.add(Object(30));
    
    Object obj0 = arr.get(0);
    Object obj1 = arr.get(1);
    Object obj2 = arr.get(2);
    
    EXPECT_TRUE(obj0.isInt());
    EXPECT_EQ(obj0.getInt(), 10);
    EXPECT_TRUE(obj1.isInt());
    EXPECT_EQ(obj1.getInt(), 20);
    EXPECT_TRUE(obj2.isInt());
    EXPECT_EQ(obj2.getInt(), 30);
}

// Test getNF returns correct non-fetched object
TEST_F(ArrayTest_112, GetNFReturnsCorrectObject_112) {
    Array arr(xref);
    arr.add(Object(99));
    const Object &obj = arr.getNF(0);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 99);
}

// Test adding different object types
TEST_F(ArrayTest_112, AddBooleanObject_112) {
    Array arr(xref);
    arr.add(Object(true));
    EXPECT_EQ(arr.getLength(), 1);
    Object obj = arr.get(0);
    EXPECT_TRUE(obj.isBool());
    EXPECT_EQ(obj.getBool(), true);
}

// Test adding a real/double value
TEST_F(ArrayTest_112, AddRealObject_112) {
    Array arr(xref);
    arr.add(Object(3.14));
    EXPECT_EQ(arr.getLength(), 1);
    Object obj = arr.get(0);
    EXPECT_TRUE(obj.isReal());
}

// Test that copy creates an array with the same length
TEST_F(ArrayTest_112, CopyPreservesLength_112) {
    Array arr(xref);
    arr.add(Object(1));
    arr.add(Object(2));
    arr.add(Object(3));
    
    const Array *copied = arr.copy(xref);
    ASSERT_NE(copied, nullptr);
    EXPECT_EQ(copied->getLength(), 3);
    delete copied;
}

// Test that deepCopy creates an array with the same length
TEST_F(ArrayTest_112, DeepCopyPreservesLength_112) {
    Array arr(xref);
    arr.add(Object(1));
    arr.add(Object(2));
    
    const Array *deepCopied = arr.deepCopy();
    ASSERT_NE(deepCopied, nullptr);
    EXPECT_EQ(deepCopied->getLength(), 2);
    delete deepCopied;
}

// Test adding and removing all elements results in empty array
TEST_F(ArrayTest_112, AddAndRemoveAllElementsResultsInEmptyArray_112) {
    Array arr(xref);
    arr.add(Object(1));
    arr.add(Object(2));
    arr.remove(1);
    arr.remove(0);
    EXPECT_EQ(arr.getLength(), 0);
}

// Test that removing from middle shifts elements correctly
TEST_F(ArrayTest_112, RemoveFromMiddleShiftsElements_112) {
    Array arr(xref);
    arr.add(Object(10));
    arr.add(Object(20));
    arr.add(Object(30));
    
    arr.remove(1); // remove the element with value 20
    
    EXPECT_EQ(arr.getLength(), 2);
    Object obj0 = arr.get(0);
    Object obj1 = arr.get(1);
    EXPECT_EQ(obj0.getInt(), 10);
    EXPECT_EQ(obj1.getInt(), 30);
}

// Test adding a null object
TEST_F(ArrayTest_112, AddNullObject_112) {
    Array arr(xref);
    arr.add(Object(objNull));
    EXPECT_EQ(arr.getLength(), 1);
    Object obj = arr.get(0);
    EXPECT_TRUE(obj.isNull());
}

// Test adding a large number of elements
TEST_F(ArrayTest_112, AddManyElements_112) {
    Array arr(xref);
    const int count = 100;
    for (int i = 0; i < count; i++) {
        arr.add(Object(i));
    }
    EXPECT_EQ(arr.getLength(), count);
    
    // Verify first and last
    Object first = arr.get(0);
    Object last = arr.get(count - 1);
    EXPECT_EQ(first.getInt(), 0);
    EXPECT_EQ(last.getInt(), count - 1);
}

// Test get with Ref overload
TEST_F(ArrayTest_112, GetWithRefOverload_112) {
    Array arr(xref);
    arr.add(Object(55));
    
    Ref returnRef;
    Object obj = arr.get(0, &returnRef);
    EXPECT_TRUE(obj.isInt());
    EXPECT_EQ(obj.getInt(), 55);
}
