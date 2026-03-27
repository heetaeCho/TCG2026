// TEST_ID: 71
// File: test_object_isBool_71.cpp

#include <gtest/gtest.h>

#include "poppler/Object.h"

// The implementation is treated as a black box. These tests only verify observable
// behavior via the public interface (Object constructors + isBool()).

namespace {

class ObjectIsBoolTest_71 : public ::testing::Test {};

TEST_F(ObjectIsBoolTest_71, DefaultConstructedIsNotBool_71)
{
    Object obj;
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectIsBoolTest_71, BoolConstructedTrueIsBool_71)
{
    Object obj(true);
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectIsBoolTest_71, BoolConstructedFalseIsBool_71)
{
    Object obj(false);
    EXPECT_TRUE(obj.isBool());
}

TEST_F(ObjectIsBoolTest_71, IntConstructedIsNotBool_71)
{
    Object obj(0);
    EXPECT_FALSE(obj.isBool());

    Object obj2(123);
    EXPECT_FALSE(obj2.isBool());
}

TEST_F(ObjectIsBoolTest_71, RealConstructedIsNotBool_71)
{
    Object obj(0.0);
    EXPECT_FALSE(obj.isBool());

    Object obj2(3.14159);
    EXPECT_FALSE(obj2.isBool());
}

TEST_F(ObjectIsBoolTest_71, Int64ConstructedIsNotBool_71)
{
    Object obj(static_cast<long long>(0));
    EXPECT_FALSE(obj.isBool());

    Object obj2(static_cast<long long>(1234567890123LL));
    EXPECT_FALSE(obj2.isBool());
}

TEST_F(ObjectIsBoolTest_71, StaticNullIsNotBool_71)
{
    Object obj = Object::null();
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectIsBoolTest_71, StaticErrorIsNotBool_71)
{
    Object obj = Object::error();
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectIsBoolTest_71, StaticEofIsNotBool_71)
{
    Object obj = Object::eof();
    EXPECT_FALSE(obj.isBool());
}

TEST_F(ObjectIsBoolTest_71, MoveConstructedPreservesBoolType_71)
{
    Object src(true);
    ASSERT_TRUE(src.isBool()); // sanity check via public API

    Object moved(std::move(src));
    EXPECT_TRUE(moved.isBool());
}

TEST_F(ObjectIsBoolTest_71, MoveAssignedPreservesBoolType_71)
{
    Object src(false);
    ASSERT_TRUE(src.isBool()); // sanity check via public API

    Object dst; // starts as objNone per header snippet; should not be bool
    EXPECT_FALSE(dst.isBool());

    dst = std::move(src);
    EXPECT_TRUE(dst.isBool());
}

} // namespace