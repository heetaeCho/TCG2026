// File: Object_null_test_64.cpp
// Unit tests for poppler::Object::null()
// TEST_ID: 64

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectNullTest_64 : public ::testing::Test {};

TEST_F(ObjectNullTest_64, NullFactoryReturnsNullObject_64)
{
    Object o = Object::null();
    EXPECT_TRUE(o.isNull());
    EXPECT_EQ(o.getType(), objNull);
    EXPECT_FALSE(o.isBool());
    EXPECT_FALSE(o.isInt());
    EXPECT_FALSE(o.isReal());
    EXPECT_FALSE(o.isNum());
    EXPECT_FALSE(o.isString());
    EXPECT_FALSE(o.isName());
    EXPECT_FALSE(o.isArray());
    EXPECT_FALSE(o.isDict());
    EXPECT_FALSE(o.isStream());
    EXPECT_FALSE(o.isRef());
    EXPECT_FALSE(o.isCmd());
    EXPECT_FALSE(o.isError());
    EXPECT_FALSE(o.isEOF());
    EXPECT_FALSE(o.isNone());
    EXPECT_FALSE(o.isInt64());
    EXPECT_FALSE(o.isHexString());
    EXPECT_FALSE(o.isIntOrInt64());
}

TEST_F(ObjectNullTest_64, NullFactoryProducesIndependentObjects_64)
{
    Object a = Object::null();
    Object b = Object::null();

    EXPECT_TRUE(a.isNull());
    EXPECT_TRUE(b.isNull());
    EXPECT_EQ(a.getType(), objNull);
    EXPECT_EQ(b.getType(), objNull);

    // Mutating one instance should not affect the other.
    a.setToNull();
    EXPECT_TRUE(a.isNull());
    EXPECT_TRUE(b.isNull());
}

TEST_F(ObjectNullTest_64, NullObjectCanBeMoved_64)
{
    Object src = Object::null();
    ASSERT_TRUE(src.isNull());

    Object dst(std::move(src));
    EXPECT_TRUE(dst.isNull());
    EXPECT_EQ(dst.getType(), objNull);

    // Moved-from object must remain valid enough to be destructed; we can still
    // call setToNull() without assuming internal state details.
    src.setToNull();
    EXPECT_TRUE(src.isNull());
}

TEST_F(ObjectNullTest_64, NullObjectMoveAssignment_64)
{
    Object lhs = Object::null();
    Object rhs = Object::null();

    lhs = std::move(rhs);
    EXPECT_TRUE(lhs.isNull());
    EXPECT_EQ(lhs.getType(), objNull);

    // Moved-from rhs should remain safe to use minimally.
    rhs.setToNull();
    EXPECT_TRUE(rhs.isNull());
}

TEST_F(ObjectNullTest_64, NullObjectCopyAndDeepCopyReturnNull_64)
{
    Object o = Object::null();

    Object c = o.copy();
    EXPECT_TRUE(c.isNull());
    EXPECT_EQ(c.getType(), objNull);

    Object d = o.deepCopy();
    EXPECT_TRUE(d.isNull());
    EXPECT_EQ(d.getType(), objNull);
}

TEST_F(ObjectNullTest_64, NullObjectReportsTypeNameNonNull_64)
{
    Object o = Object::null();

    const char *name = o.getTypeName();
    // We don't assume the exact string (localization/build options may vary),
    // only that a type name is available.
    EXPECT_NE(name, nullptr);
    EXPECT_NE(name[0], '\0');
}

TEST_F(ObjectNullTest_64, NullObjectPrintDoesNotCrash_64)
{
    Object o = Object::null();

    // Observable behavior: should be callable without throwing/crashing.
    // We avoid asserting on exact output formatting.
    ASSERT_NO_FATAL_FAILURE(o.print(stdout));
}

TEST_F(ObjectNullTest_64, BoundaryRepeatedConstructionAndMove_64)
{
    // Stress-ish boundary: repeated use should keep producing valid null objects.
    for (int i = 0; i < 1000; ++i) {
        Object o = Object::null();
        EXPECT_TRUE(o.isNull());
        EXPECT_EQ(o.getType(), objNull);

        Object moved(std::move(o));
        EXPECT_TRUE(moved.isNull());
        EXPECT_EQ(moved.getType(), objNull);

        // Ensure moved-from is still usable in a minimal, black-box-safe way.
        o.setToNull();
        EXPECT_TRUE(o.isNull());
    }
}

} // namespace