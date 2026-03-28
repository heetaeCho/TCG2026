// TEST_ID: 78
//
// Unit tests for poppler::Object::isNull()
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// Constraints honored:
// - Black-box testing via public interface only
// - No access to private state (e.g., internal ObjType)
// - No re-implementation of internal logic
// - Boundary / error-ish cases are exercised via observable interface behavior
//
// Note: Object has no explicit external collaborators for isNull(), so no mocks are needed.

#include <gtest/gtest.h>

#include <memory>
#include <string>
#include <utility>

#include "poppler/Object.h"

// If poppler headers use GooString, include it when available in the project.
// Some builds may already pull it via Object.h; this include is harmless if present.
// (If your build complains, you can remove it.)
#include "goo/GooString.h"

namespace {

// A small fixture just to keep naming consistent.
class ObjectIsNullTest_78 : public ::testing::Test {};

TEST_F(ObjectIsNullTest_78, NullFactoryIsNull_78)
{
    // Normal operation: static constructor for null should report null.
    auto o = Object::null();
    EXPECT_TRUE(o.isNull());
}

TEST_F(ObjectIsNullTest_78, EofFactoryIsNotNull_78)
{
    // Non-null special object: EOF should not be null.
    auto o = Object::eof();
    EXPECT_FALSE(o.isNull());
}

TEST_F(ObjectIsNullTest_78, ErrorFactoryIsNotNull_78)
{
    // Non-null special object: error should not be null.
    auto o = Object::error();
    EXPECT_FALSE(o.isNull());
}

TEST_F(ObjectIsNullTest_78, DefaultConstructedIsNotNull_78)
{
    // Boundary-ish: default-constructed object is a valid state (often "none");
    // observable expectation: it is not null (distinct from Object::null()).
    Object o;
    EXPECT_FALSE(o.isNull());
}

TEST_F(ObjectIsNullTest_78, SetToNullMakesObjectNull_78)
{
    // Normal operation: mutation to null should make isNull true.
    Object o(true);
    EXPECT_FALSE(o.isNull()); // sanity: bool object isn't null
    o.setToNull();
    EXPECT_TRUE(o.isNull());
}

TEST_F(ObjectIsNullTest_78, PrimitiveConstructorsAreNotNull_78)
{
    // Boundary coverage across different constructor overloads.
    EXPECT_FALSE(Object(false).isNull());
    EXPECT_FALSE(Object(true).isNull());

    EXPECT_FALSE(Object(0).isNull());
    EXPECT_FALSE(Object(42).isNull());
    EXPECT_FALSE(Object(-1).isNull());

    EXPECT_FALSE(Object(0.0).isNull());
    EXPECT_FALSE(Object(3.14159).isNull());

    EXPECT_FALSE(Object(0LL).isNull());
    EXPECT_FALSE(Object(9223372036854775807LL).isNull());
    EXPECT_FALSE(Object(-9223372036854775807LL).isNull()); // avoid literal -LLONG_MIN issues
}

TEST_F(ObjectIsNullTest_78, StringConstructorsAreNotNull_78)
{
    // Normal operation: string-like objects should not be null.
    EXPECT_FALSE(Object(std::string{}).isNull());
    EXPECT_FALSE(Object(std::string{"hello"}).isNull());

    // unique_ptr<GooString> overload
    auto gs = std::make_unique<GooString>("abc");
    Object o(std::move(gs));
    EXPECT_FALSE(o.isNull());
}

TEST_F(ObjectIsNullTest_78, MoveConstructionPreservesNullness_78)
{
    // Boundary: move operations should preserve the observable nullness of the destination.
    Object src = Object::null();
    ASSERT_TRUE(src.isNull());

    Object moved(std::move(src));
    EXPECT_TRUE(moved.isNull());
}

TEST_F(ObjectIsNullTest_78, MoveAssignmentPreservesNullness_78)
{
    // Boundary: move assignment into an existing object.
    Object dst(false);
    ASSERT_FALSE(dst.isNull());

    Object src = Object::null();
    ASSERT_TRUE(src.isNull());

    dst = std::move(src);
    EXPECT_TRUE(dst.isNull());
}

TEST_F(ObjectIsNullTest_78, CopyCreatesIndependentObjectWithSameNullness_78)
{
    // Normal operation: copy() returns an Object by value and should match nullness.
    Object n = Object::null();
    Object c = n.copy();
    EXPECT_TRUE(c.isNull());

    Object b(true);
    Object bc = b.copy();
    EXPECT_FALSE(bc.isNull());
}

TEST_F(ObjectIsNullTest_78, DeepCopyCreatesIndependentObjectWithSameNullness_78)
{
    // Normal operation: deepCopy() should preserve nullness for simple types.
    Object n = Object::null();
    Object dn = n.deepCopy();
    EXPECT_TRUE(dn.isNull());

    Object i(123);
    Object di = i.deepCopy();
    EXPECT_FALSE(di.isNull());
}

} // namespace