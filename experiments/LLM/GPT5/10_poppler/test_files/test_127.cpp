// BaseStream_getUndecodedStream_tests_127.cpp
// File: ./TestProjects/poppler/poppler/Stream.h

#include <gtest/gtest.h>

#include "poppler/Stream.h"

namespace {

// These tests treat BaseStream::getUndecodedStream() as a black box and only
// verify observable behavior through the public interface.

class BaseStreamTest_127 : public ::testing::Test {};

TEST_F(BaseStreamTest_127, GetUndecodedStreamReturnsThis_127) {
  // Construct a BaseStream using only the public constructor signature.
  // (Assumes Object is default-constructible in this codebase, as is typical in Poppler.)
  Object dict;
  BaseStream s(std::move(dict), /*lengthA=*/0);

  Stream *undecoded = s.getUndecodedStream();

  ASSERT_NE(undecoded, nullptr);
  EXPECT_EQ(undecoded, static_cast<Stream *>(&s));
}

TEST_F(BaseStreamTest_127, GetUndecodedStreamIsStableAcrossCalls_127) {
  Object dict;
  BaseStream s(std::move(dict), /*lengthA=*/0);

  Stream *p1 = s.getUndecodedStream();
  Stream *p2 = s.getUndecodedStream();
  Stream *p3 = s.getUndecodedStream();

  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(BaseStreamTest_127, GetUndecodedStreamViaStreamPointerReturnsSameObject_127) {
  Object dict;
  BaseStream s(std::move(dict), /*lengthA=*/0);

  Stream *asStream = static_cast<Stream *>(&s);
  Stream *undecoded = asStream->getUndecodedStream();

  ASSERT_NE(undecoded, nullptr);
  EXPECT_EQ(undecoded, asStream);
}

} // namespace