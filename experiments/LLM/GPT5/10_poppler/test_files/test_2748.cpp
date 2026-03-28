// Object_2748_test.cc
#include <gtest/gtest.h>

#include "Object.h"

// NOTE:
// This test targets the constructor:
//   Object(ObjType typeA, std::string&& stringA)
// which (per provided snippet) asserts: typeA == objHexString.
//
// We treat Object as a black box and only validate observable behavior
// through the public interface (getType/isHexString/getHexString, etc).

namespace {

class ObjectTest_2748 : public ::testing::Test {};

static std::string GooStringToStdString_2748(const GooString *s) {
  if (!s) {
    return std::string();
  }
  // Avoid depending on any specific helper beyond common GooString accessors.
  // GooString typically provides c_str() and getLength().
  return std::string(s->c_str(), static_cast<size_t>(s->getLength()));
}

TEST_F(ObjectTest_2748, ConstructHexStringSetsTypeAndContent_2748) {
  std::string payload = "4E6F742061207265616C206865782070617273652074657374"; // arbitrary bytes
  Object obj(objHexString, std::move(payload));

  EXPECT_EQ(obj.getType(), objHexString);
  EXPECT_TRUE(obj.isHexString());
  EXPECT_FALSE(obj.isString());  // observable distinction in API

  const GooString *gs = obj.getHexString();
  ASSERT_NE(gs, nullptr);
  EXPECT_EQ(GooStringToStdString_2748(gs),
            std::string("4E6F742061207265616C206865782070617273652074657374"));
}

TEST_F(ObjectTest_2748, ConstructHexStringWithEmptyPayload_2748) {
  std::string payload;
  Object obj(objHexString, std::move(payload));

  EXPECT_TRUE(obj.isHexString());
  const GooString *gs = obj.getHexString();
  ASSERT_NE(gs, nullptr);
  EXPECT_EQ(gs->getLength(), 0);
  EXPECT_EQ(GooStringToStdString_2748(gs), std::string());
}

TEST_F(ObjectTest_2748, ConstructHexStringPreservesEmbeddedNulBytes_2748) {
  // std::string can contain embedded '\0'. Verify length/content is preserved
  // through the public GooString accessor.
  std::string payload;
  payload.push_back('A');
  payload.push_back('\0');
  payload.push_back('B');
  payload.push_back('\0');
  payload.push_back('C');

  Object obj(objHexString, std::move(payload));

  EXPECT_TRUE(obj.isHexString());
  const GooString *gs = obj.getHexString();
  ASSERT_NE(gs, nullptr);

  EXPECT_EQ(gs->getLength(), 5);

  const std::string roundtrip = GooStringToStdString_2748(gs);
  ASSERT_EQ(roundtrip.size(), 5u);
  EXPECT_EQ(roundtrip[0], 'A');
  EXPECT_EQ(roundtrip[1], '\0');
  EXPECT_EQ(roundtrip[2], 'B');
  EXPECT_EQ(roundtrip[3], '\0');
  EXPECT_EQ(roundtrip[4], 'C');
}

TEST_F(ObjectTest_2748, ConstructHexStringWithLargePayload_2748) {
  // Boundary-ish: large string. Keep it reasonable for unit tests.
  std::string payload(1 << 16, 'x');  // 65536 bytes
  Object obj(objHexString, std::move(payload));

  EXPECT_TRUE(obj.isHexString());
  const GooString *gs = obj.getHexString();
  ASSERT_NE(gs, nullptr);
  EXPECT_EQ(gs->getLength(), (1 << 16));

  // Spot-check content at a few positions without assuming internal details.
  const std::string roundtrip = GooStringToStdString_2748(gs);
  ASSERT_EQ(roundtrip.size(), static_cast<size_t>(1 << 16));
  EXPECT_EQ(roundtrip.front(), 'x');
  EXPECT_EQ(roundtrip[12345], 'x');
  EXPECT_EQ(roundtrip.back(), 'x');
}

#if !defined(NDEBUG)
TEST_F(ObjectTest_2748, ConstructWithNonHexTypeDiesInDebug_2748) {
  // The provided implementation uses assert(typeA == objHexString).
  // In Debug builds, assert should terminate. In Release (NDEBUG), it may not.
  EXPECT_DEATH(
      {
        std::string payload = "abc";
        Object obj(objString, std::move(payload));
        (void)obj;
      },
      ".*");
}
#else
TEST_F(ObjectTest_2748, ConstructWithNonHexTypeSkippedInRelease_2748) {
  GTEST_SKIP() << "Death test depends on assert(); skipped because NDEBUG is defined.";
}
#endif

}  // namespace