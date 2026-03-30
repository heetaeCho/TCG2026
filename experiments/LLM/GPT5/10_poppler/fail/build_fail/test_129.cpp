// -*- mode: c++; tab-width: 2; indent-tabs-mode: nil; c-basic-offset: 2 -*-
// The TEST_ID is 129
//
// Unit tests for BaseStream::getDictObject()
// File: ./TestProjects/poppler/poppler/Stream.h

#include <gtest/gtest.h>

#include "Stream.h"

// These tests treat BaseStream as a black box and verify only observable behavior
// through the public interface: getDictObject().

namespace {

// NOTE: We intentionally avoid assuming anything about Object's internal structure.
// We only check pointer identity/stability and non-nullness as observable behavior.

class BaseStreamGetDictObjectTest_129 : public ::testing::Test {};

}  // namespace

TEST_F(BaseStreamGetDictObjectTest_129, ReturnsNonNullPointer_129) {
  Object dict;
  BaseStream s(std::move(dict), /*lengthA=*/0);

  Object* p = s.getDictObject();
  ASSERT_NE(p, nullptr);
}

TEST_F(BaseStreamGetDictObjectTest_129, ReturnsStablePointerAcrossCalls_129) {
  Object dict;
  BaseStream s(std::move(dict), /*lengthA=*/0);

  Object* p1 = s.getDictObject();
  Object* p2 = s.getDictObject();
  Object* p3 = s.getDictObject();

  ASSERT_NE(p1, nullptr);
  EXPECT_EQ(p1, p2);
  EXPECT_EQ(p2, p3);
}

TEST_F(BaseStreamGetDictObjectTest_129, DifferentInstancesReturnDifferentAddresses_129) {
  Object dict1;
  Object dict2;

  BaseStream s1(std::move(dict1), /*lengthA=*/0);
  BaseStream s2(std::move(dict2), /*lengthA=*/0);

  Object* p1 = s1.getDictObject();
  Object* p2 = s2.getDictObject();

  ASSERT_NE(p1, nullptr);
  ASSERT_NE(p2, nullptr);

  // Each instance should expose its own dict object.
  EXPECT_NE(p1, p2);
}

TEST_F(BaseStreamGetDictObjectTest_129, PointerRemainsValidAfterOtherCalls_129) {
  Object dict;
  BaseStream s(std::move(dict), /*lengthA=*/0);

  Object* p_before = s.getDictObject();
  ASSERT_NE(p_before, nullptr);

  // Call other public APIs (without asserting on their effects),
  // then verify getDictObject still returns the same address.
  // This remains black-box: we only assert stability of the exposed pointer.
  (void)s.getBaseStream();
  (void)s.getUndecodedStream();
  (void)s.getDict();
  (void)s.isBinary(/*last=*/true);
  (void)s.isBinary(/*last=*/false);
  (void)s.getLength();

  Object* p_after = s.getDictObject();
  EXPECT_EQ(p_before, p_after);
}