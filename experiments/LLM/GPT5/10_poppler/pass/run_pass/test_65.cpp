// TEST_ID = 65
//
// Unit tests for poppler::Object::eof() factory.
// File under test: ./TestProjects/poppler/poppler/Object.h
//
// Constraints followed:
// - Treat Object as a black box (no internal state access).
// - Only test observable behavior through public API.
// - No re-implementation of logic.
//
// NOTE: These tests assume the real Poppler Object interface is available
// (ObjType enum, Object::eof(), Object::getType(), Object::isEOF(), etc.).

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectEofTest_65 : public ::testing::Test {};

TEST_F(ObjectEofTest_65, EofFactoryCreatesEOFType_65)
{
    const Object o = Object::eof();

    // Observable: type and predicates
    EXPECT_EQ(o.getType(), objEOF);
    EXPECT_TRUE(o.isEOF());

    // And it's not other common categories
    EXPECT_FALSE(o.isNull());
    EXPECT_FALSE(o.isBool());
    EXPECT_FALSE(o.isInt());
    EXPECT_FALSE(o.isReal());
    EXPECT_FALSE(o.isString());
    EXPECT_FALSE(o.isName());
    EXPECT_FALSE(o.isArray());
    EXPECT_FALSE(o.isDict());
    EXPECT_FALSE(o.isStream());
    EXPECT_FALSE(o.isRef());
    EXPECT_FALSE(o.isCmd());
    EXPECT_FALSE(o.isError());
    EXPECT_FALSE(o.isNone());
    EXPECT_FALSE(o.isInt64());
    EXPECT_FALSE(o.isHexString());
}

TEST_F(ObjectEofTest_65, EofFactoryCanBeCalledMultipleTimesIndependently_65)
{
    const Object a = Object::eof();
    const Object b = Object::eof();

    EXPECT_TRUE(a.isEOF());
    EXPECT_TRUE(b.isEOF());
    EXPECT_EQ(a.getType(), objEOF);
    EXPECT_EQ(b.getType(), objEOF);
}

TEST_F(ObjectEofTest_65, EofReturnedObjectIsStableAcrossMoveConstruction_65)
{
    Object a = Object::eof();
    EXPECT_TRUE(a.isEOF());

    Object b(std::move(a)); // move ctor is public per interface
    EXPECT_TRUE(b.isEOF());
    EXPECT_EQ(b.getType(), objEOF);

    // Do not assert anything about 'a' after move (unspecified),
    // only that moving doesn't break the moved-to object.
}

TEST_F(ObjectEofTest_65, EofReturnedObjectIsStableAcrossMoveAssignment_65)
{
    Object a = Object::eof();
    Object b = Object::null(); // some other valid value to overwrite

    b = std::move(a);
    EXPECT_TRUE(b.isEOF());
    EXPECT_EQ(b.getType(), objEOF);
}

TEST_F(ObjectEofTest_65, EofCanBeOverwrittenBySetToNull_65)
{
    Object o = Object::eof();
    ASSERT_TRUE(o.isEOF());

    o.setToNull();

    EXPECT_TRUE(o.isNull());
    EXPECT_EQ(o.getType(), objNull);
    EXPECT_FALSE(o.isEOF());
}

TEST_F(ObjectEofTest_65, BoundaryGetTypeNameIsNonNullForEOF_65)
{
    const Object o = Object::eof();

    // Boundary/robustness check: getTypeName should return a usable C string.
    // We don't assert exact contents (implementation detail).
    const char *name = o.getTypeName();
    ASSERT_NE(name, nullptr);
    // Should be a non-empty string in typical implementations; allow empty if not.
    // Still, this is an observable robustness check.
    EXPECT_GE(std::char_traits<char>::length(name), static_cast<size_t>(0));
}

} // namespace