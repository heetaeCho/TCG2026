// TEST_ID: 283
#include <gtest/gtest.h>

#include "Link.h"
#include "Object.h"

namespace {

namespace detail {

template <typename, typename = void>
struct has_setToNull : std::false_type {};
template <typename T>
struct has_setToNull<T, std::void_t<decltype(std::declval<T&>().setToNull())>> : std::true_type {};

template <typename, typename = void>
struct has_initInt : std::false_type {};
template <typename T>
struct has_initInt<T, std::void_t<decltype(std::declval<T&>().initInt(0))>> : std::true_type {};

inline Object makeNullObject()
{
  Object obj;
  if constexpr (has_setToNull<Object>::value) {
    obj.setToNull();
  } else {
    // Many Poppler versions support this constructor.
    obj = Object(objNull);
  }
  return obj;
}

inline Object makeIntObject(int v)
{
  Object obj;
  if constexpr (has_initInt<Object>::value) {
    obj.initInt(v);
  } else {
    // Fallback: still provide a valid Object value in a common way.
    obj = Object(v);
  }
  return obj;
}

} // namespace detail

class LinkGoToTest_283 : public ::testing::Test {};

TEST_F(LinkGoToTest_283, GetKindReturnsActionGoToWithNullObject_283)
{
  Object destObj = detail::makeNullObject();
  LinkGoTo sut(&destObj);

  EXPECT_EQ(sut.getKind(), actionGoTo);
}

TEST_F(LinkGoToTest_283, GetKindReturnsActionGoToOnConstObjectAndIsStable_283)
{
  Object destObj = detail::makeNullObject();
  const LinkGoTo sut(&destObj);

  const auto k1 = sut.getKind();
  const auto k2 = sut.getKind();

  EXPECT_EQ(k1, actionGoTo);
  EXPECT_EQ(k2, actionGoTo);
  EXPECT_EQ(k1, k2);
}

TEST_F(LinkGoToTest_283, GetKindReturnsActionGoToForDifferentDestObjectShapes_283)
{
  // Boundary-ish check: different input object "shape" should not affect kind.
  // (No assumptions about isOk()/dest parsing; only observable getKind()).
  Object intObj = detail::makeIntObject(42);
  LinkGoTo sut(&intObj);

  EXPECT_EQ(sut.getKind(), actionGoTo);
}

} // namespace