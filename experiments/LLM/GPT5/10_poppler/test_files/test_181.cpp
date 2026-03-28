// ASCII85Stream_getKind_181_test.cpp
// Unit tests for ASCII85Stream::getKind()
// The TEST_ID is 181

#include <gtest/gtest.h>

#include <memory>

#include "./TestProjects/poppler/poppler/Stream.h"

namespace {

class ASCII85StreamTest_181 : public ::testing::Test {
protected:
  static std::unique_ptr<ASCII85Stream> makeStream() {
    // Use the public explicit constructor that takes an int, as declared in Stream.h.
    // Treat as a black box: we only rely on successful construction for observable getKind().
    return std::make_unique<ASCII85Stream>(0);
  }
};

TEST_F(ASCII85StreamTest_181, GetKindReturnsASCII85_181) {
  auto s = makeStream();
  EXPECT_EQ(s->getKind(), strASCII85);
}

TEST_F(ASCII85StreamTest_181, GetKindIsStableAcrossCalls_181) {
  auto s = makeStream();
  const StreamKind k1 = s->getKind();
  const StreamKind k2 = s->getKind();
  const StreamKind k3 = s->getKind();
  EXPECT_EQ(k1, strASCII85);
  EXPECT_EQ(k2, strASCII85);
  EXPECT_EQ(k3, strASCII85);
}

TEST_F(ASCII85StreamTest_181, GetKindWorksThroughBasePointer_181) {
  // Verify polymorphic behavior: getKind() should still report strASCII85 via a base pointer.
  std::unique_ptr<Stream> base;
  ASSERT_NO_THROW(base = std::unique_ptr<Stream>(new ASCII85Stream(0)));
  ASSERT_NE(base, nullptr);
  EXPECT_EQ(base->getKind(), strASCII85);
}

TEST_F(ASCII85StreamTest_181, GetKindOnConstObject_181) {
  auto s = makeStream();
  const ASCII85Stream &cs = *s;
  EXPECT_EQ(cs.getKind(), strASCII85);
}

TEST_F(ASCII85StreamTest_181, MultipleInstancesAllReportASCII85_181) {
  auto a = makeStream();
  auto b = makeStream();
  auto c = makeStream();

  EXPECT_EQ(a->getKind(), strASCII85);
  EXPECT_EQ(b->getKind(), strASCII85);
  EXPECT_EQ(c->getKind(), strASCII85);
}

}  // namespace