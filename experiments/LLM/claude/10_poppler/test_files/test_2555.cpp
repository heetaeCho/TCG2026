static inline void convert_doubles_array(const Object *object, gdouble **values, guint *n_values)
#include <gtest/gtest.h>
#include <glib.h>
#include "poppler/Object.h"
#include "poppler/Array.h"

// We need to access the static inline function. Since it's in a .cc file,
// we include it or replicate the declaration for testing purposes.
// The function is static inline in poppler-structure-element.cc
// For testing, we'll include the relevant portion or redefine access.

// Forward declare or include the function
#include "glib/poppler-structure-element.cc"

class ConvertDoublesArray_2555 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

TEST_F(ConvertDoublesArray_2555, EmptyArray_2555) {
    // Create an empty array Object
    auto *arr = new Array(nullptr);
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 999;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 0u);
}

TEST_F(ConvertDoublesArray_2555, SingleElement_2555) {
    auto *arr = new Array(nullptr);
    arr->add(Object(3.14));
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 0;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 1u);
    // Note: Due to the bug in the implementation (values = &doubles instead of *values = doubles),
    // the caller's `values` pointer is NOT updated. This tests the observable behavior.
    // The original values pointer remains nullptr.
    EXPECT_EQ(values, nullptr);
}

TEST_F(ConvertDoublesArray_2555, MultipleElements_2555) {
    auto *arr = new Array(nullptr);
    arr->add(Object(1.0));
    arr->add(Object(2.5));
    arr->add(Object(3.7));
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 0;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 3u);
    // Due to bug, values is still nullptr
    EXPECT_EQ(values, nullptr);
}

TEST_F(ConvertDoublesArray_2555, IntegerValuesInArray_2555) {
    auto *arr = new Array(nullptr);
    arr->add(Object(1));
    arr->add(Object(2));
    arr->add(Object(3));
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 0;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 3u);
}

TEST_F(ConvertDoublesArray_2555, NValuesSetCorrectly_2555) {
    auto *arr = new Array(nullptr);
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    arr->add(Object(0.0));
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 0;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 5u);
}

TEST_F(ConvertDoublesArray_2555, NegativeDoubleValues_2555) {
    auto *arr = new Array(nullptr);
    arr->add(Object(-1.5));
    arr->add(Object(-99.99));
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 0;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 2u);
}

TEST_F(ConvertDoublesArray_2555, LargeArray_2555) {
    auto *arr = new Array(nullptr);
    for (int i = 0; i < 100; i++) {
        arr->add(Object(static_cast<double>(i)));
    }
    Object obj(arr);

    gdouble *values = nullptr;
    guint n_values = 0;

    convert_doubles_array(&obj, &values, &n_values);

    EXPECT_EQ(n_values, 100u);
}
