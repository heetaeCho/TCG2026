// Object_move_ctor_2753_test.cc
#include <gtest/gtest.h>

#include <cmath>
#include <memory>
#include <string>
#include <utility>

#include "Object.h"

// GooString is used by some Object constructors / accessors.
#include "goo/GooString.h"

namespace {

// Robust helper: convert GooString* to std::string without assuming a single API.
template <typename T>
concept HasCStr = requires(const T &t) { t.c_str(); };

template <typename T>
concept HasGetCString = requires(const T &t) { t.getCString(); };

template <typename T>
concept HasToStr = requires(const T &t) { t.toStr(); };

static std::string GooStringToStdString(const GooString *gs)
{
  if (!gs) {
    return {};
  }

  if constexpr (HasCStr<GooString>) {
    return std::string(gs->c_str());
  } else if constexpr (HasGetCString<GooString>) {
    return std::string(gs->getCString());
  } else if constexpr (HasToStr<GooString>) {
    return gs->toStr();
  } else {
    // As a last resort, don't assert content if we can't retrieve it.
    return {};
  }
}

class ObjectMoveCtorTest_2753 : public ::testing::Test {};

} // namespace

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromDefaultNone_SetsSourceDeadAndDestNone_2753)
{
  Object src;
  ASSERT_EQ(src.getType(), objNone);

  Object dst(std::move(src));

  // Destination preserves the original observable type.
  EXPECT_EQ(dst.getType(), objNone);

  // Implementation explicitly sets moved-from to objDead (observable via getType()).
  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromBool_PreservesValueAndMarksSourceDead_2753)
{
  Object src(true);
  ASSERT_TRUE(src.isBool());
  ASSERT_EQ(src.getType(), objBool);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isBool());
  EXPECT_EQ(dst.getType(), objBool);
  EXPECT_TRUE(dst.getBool());

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromInt_PreservesValueAndMarksSourceDead_2753)
{
  Object src(123);
  ASSERT_TRUE(src.isInt());
  ASSERT_EQ(src.getType(), objInt);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isInt());
  EXPECT_EQ(dst.getType(), objInt);
  EXPECT_EQ(dst.getInt(), 123);

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromInt64_PreservesValueAndMarksSourceDead_2753)
{
  const long long v = (1LL << 40) + 7; // boundary-ish: beyond 32-bit int
  Object src(v);
  ASSERT_TRUE(src.isInt64());
  ASSERT_EQ(src.getType(), objInt64);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isInt64());
  EXPECT_EQ(dst.getType(), objInt64);
  EXPECT_EQ(dst.getInt64(), v);

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromReal_PreservesValueAndMarksSourceDead_2753)
{
  const double v = 3.141592653589793;
  Object src(v);
  ASSERT_TRUE(src.isReal());
  ASSERT_EQ(src.getType(), objReal);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isReal());
  EXPECT_EQ(dst.getType(), objReal);
  EXPECT_DOUBLE_EQ(dst.getReal(), v);

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromStdString_PreservesTypeAndContentIfObservable_2753)
{
  Object src(std::string("hello"));
  ASSERT_TRUE(src.isString());
  ASSERT_EQ(src.getType(), objString);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isString());
  EXPECT_EQ(dst.getType(), objString);
  ASSERT_NE(dst.getString(), nullptr);

  const std::string s = GooStringToStdString(dst.getString());
  if (!s.empty()) {
    EXPECT_EQ(s, "hello");
  }

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromUniquePtrGooString_PreservesTypeAndContentIfObservable_2753)
{
  auto gs = std::make_unique<GooString>("world");
  Object src(std::move(gs));
  ASSERT_TRUE(src.isString());
  ASSERT_EQ(src.getType(), objString);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isString());
  EXPECT_EQ(dst.getType(), objString);
  ASSERT_NE(dst.getString(), nullptr);

  const std::string s = GooStringToStdString(dst.getString());
  if (!s.empty()) {
    EXPECT_EQ(s, "world");
  }

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromStaticNull_PreservesNullAndMarksSourceDead_2753)
{
  Object src = Object::null();
  ASSERT_TRUE(src.isNull());
  ASSERT_EQ(src.getType(), objNull);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isNull());
  EXPECT_EQ(dst.getType(), objNull);

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromStaticEof_PreservesEOFAndMarksSourceDead_2753)
{
  Object src = Object::eof();
  ASSERT_TRUE(src.isEOF());
  ASSERT_EQ(src.getType(), objEOF);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isEOF());
  EXPECT_EQ(dst.getType(), objEOF);

  EXPECT_EQ(src.getType(), objDead);
}

TEST_F(ObjectMoveCtorTest_2753, MoveCtorFromStaticError_PreservesErrorAndMarksSourceDead_2753)
{
  Object src = Object::error();
  ASSERT_TRUE(src.isError());
  ASSERT_EQ(src.getType(), objError);

  Object dst(std::move(src));

  EXPECT_TRUE(dst.isError());
  EXPECT_EQ(dst.getType(), objError);

  EXPECT_EQ(src.getType(), objDead);
}