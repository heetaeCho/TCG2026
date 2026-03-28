// Object_isStream_unittest.cpp
// Unit tests for poppler::Object::isStream()
// TEST_ID = 81

#include <gtest/gtest.h>

#include "poppler/Object.h"

namespace {

class ObjectIsStreamTest_81 : public ::testing::Test {
protected:
  // Keep empty; tests are pure black-box via public API.
};

TEST_F(ObjectIsStreamTest_81, DefaultConstructedIsNotStream_81) {
  Object obj;
  EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectIsStreamTest_81, BoolConstructedIsNotStream_81) {
  Object objTrue(true);
  Object objFalse(false);
  EXPECT_FALSE(objTrue.isStream());
  EXPECT_FALSE(objFalse.isStream());
}

TEST_F(ObjectIsStreamTest_81, IntConstructedIsNotStream_81) {
  Object obj0(0);
  Object objPos(123);
  Object objNeg(-456);
  EXPECT_FALSE(obj0.isStream());
  EXPECT_FALSE(objPos.isStream());
  EXPECT_FALSE(objNeg.isStream());
}

TEST_F(ObjectIsStreamTest_81, RealConstructedIsNotStream_81) {
  Object obj0(0.0);
  Object objPi(3.14159);
  Object objNeg(-2.5);
  EXPECT_FALSE(obj0.isStream());
  EXPECT_FALSE(objPi.isStream());
  EXPECT_FALSE(objNeg.isStream());
}

TEST_F(ObjectIsStreamTest_81, Int64ConstructedIsNotStream_81) {
  Object obj0(static_cast<long long>(0));
  Object objBig(static_cast<long long>(1) << 40);
  Object objNeg(static_cast<long long>(-1) * (static_cast<long long>(1) << 40));
  EXPECT_FALSE(obj0.isStream());
  EXPECT_FALSE(objBig.isStream());
  EXPECT_FALSE(objNeg.isStream());
}

TEST_F(ObjectIsStreamTest_81, StaticNullIsNotStream_81) {
  Object obj = Object::null();
  EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectIsStreamTest_81, StaticEofIsNotStream_81) {
  Object obj = Object::eof();
  EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectIsStreamTest_81, StaticErrorIsNotStream_81) {
  Object obj = Object::error();
  EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectIsStreamTest_81, SetToNullMakesNotStream_81) {
  // Boundary/transition: ensure calling setToNull results in a non-stream object.
  Object obj(true);
  obj.setToNull();
  EXPECT_FALSE(obj.isStream());
}

TEST_F(ObjectIsStreamTest_81, MoveConstructedPreservesIsStreamResult_81) {
  // Black-box move semantics: moved-to should report the same isStream as source did pre-move.
  Object src(123);  // Known non-stream
  const bool expected = src.isStream();

  Object moved(std::move(src));
  EXPECT_EQ(moved.isStream(), expected);
}

TEST_F(ObjectIsStreamTest_81, MoveAssignedPreservesIsStreamResult_81) {
  Object src(3.14); // Known non-stream
  const bool expected = src.isStream();

  Object dst;
  dst = std::move(src);
  EXPECT_EQ(dst.isStream(), expected);
}

TEST_F(ObjectIsStreamTest_81, CopyIsNotStreamForNonStreamSource_81) {
  // copy() is part of the public interface; verify it doesn't turn a non-stream into a stream.
  Object obj(7);
  Object copied = obj.copy();
  EXPECT_FALSE(obj.isStream());
  EXPECT_FALSE(copied.isStream());
}

TEST_F(ObjectIsStreamTest_81, DeepCopyIsNotStreamForNonStreamSource_81) {
  // deepCopy() should also preserve "not a stream" for a non-stream source.
  Object obj(std::string{"hello"});
  Object copied = obj.deepCopy();
  EXPECT_FALSE(obj.isStream());
  EXPECT_FALSE(copied.isStream());
}

} // namespace