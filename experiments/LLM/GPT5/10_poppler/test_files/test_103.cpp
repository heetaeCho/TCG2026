// Object_getStream_103_test.cpp
// Unit tests for Object::getStream() in poppler/Object.h
//
// Constraints honored:
// - Treat Object implementation as a black box
// - Use only public interface / observable behavior
// - No access to private state

#include <gtest/gtest.h>

#include "poppler/Object.h"

// SFINAE helper: detect whether Object is constructible from Stream*
template <typename T, typename = void>
struct HasStreamPtrCtor : std::false_type
{
};

template <typename T>
struct HasStreamPtrCtor<T, std::void_t<decltype(T(std::declval<Stream *>()))>> : std::true_type
{
};

class ObjectGetStreamTest_103 : public ::testing::Test
{
};

TEST_F(ObjectGetStreamTest_103, NonStreamObjectTriggersTypeCheckOrReturnsNull_103)
{
  // Use a clearly non-stream object (default is typically objNone).
  const Object o;

#if defined(NDEBUG)
  // In release builds, type checks are often compiled out; verify it behaves safely.
  EXPECT_EQ(o.getStream(), nullptr);
#else
  // In debug builds, OBJECT_TYPE_CHECK commonly aborts on type mismatch.
  EXPECT_DEATH_IF_SUPPORTED(
      {
        (void)o.getStream();
      },
      "");
#endif
}

TEST_F(ObjectGetStreamTest_103, NonStreamVariantsTriggerTypeCheckOrReturnNull_103)
{
  // A few representative non-stream constructions (covering boundary-ish variety).
  const Object oBool(true);
  const Object oInt(0);
  const Object oReal(0.0);
  const Object oNull = Object::null();
  const Object oErr = Object::error();
  const Object oEof = Object::eof();
  const Object oInt64(static_cast<long long>(0));

  const Object *objs[] = {&oBool, &oInt, &oReal, &oNull, &oErr, &oEof, &oInt64};

#if defined(NDEBUG)
  for (const Object *p : objs) {
    EXPECT_EQ(p->getStream(), nullptr);
  }
#else
  // In debug builds, any non-stream should trip the type check.
  for (const Object *p : objs) {
    EXPECT_DEATH_IF_SUPPORTED(
        {
          (void)p->getStream();
        },
        "");
  }
#endif
}

TEST_F(ObjectGetStreamTest_103, StreamObjectReturnsSamePointerWhenStreamCtorExists_103)
{
  // Some poppler versions expose Object(Stream*) ctor; others do not.
  // If it exists, we can validate "normal operation" of getStream().
  if constexpr (HasStreamPtrCtor<Object>::value) {
    Stream *const s = reinterpret_cast<Stream *>(static_cast<uintptr_t>(0x1));
    const Object o(s);

    EXPECT_TRUE(o.isStream());
    EXPECT_EQ(o.getStream(), s);
  } else {
    GTEST_SKIP() << "Object(Stream*) constructor not available in this build; "
                    "cannot construct a stream-typed Object via public API.";
  }
}

TEST_F(ObjectGetStreamTest_103, StreamObjectWithNullPointerIsHandledWhenStreamCtorExists_103)
{
  if constexpr (HasStreamPtrCtor<Object>::value) {
    Stream *const s = nullptr;
    const Object o(s);

    EXPECT_TRUE(o.isStream());
    EXPECT_EQ(o.getStream(), nullptr);
  } else {
    GTEST_SKIP() << "Object(Stream*) constructor not available in this build.";
  }
}