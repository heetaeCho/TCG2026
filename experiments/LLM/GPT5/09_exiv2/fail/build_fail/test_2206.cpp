// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_xmp_automutex_2206.cpp

#include <gtest/gtest.h>

#include <type_traits>
#include <utility>

// The class under test lives here.
#include "xmpsdk/src/XMPCore_Impl.hpp"

namespace {

class XMPAutoMutexTest_2206 : public ::testing::Test {};

TEST_F(XMPAutoMutexTest_2206, TypeTraits_DefaultConstructibleAndDestructible_2206) {
  static_assert(std::is_default_constructible<XMP_AutoMutex>::value,
                "XMP_AutoMutex should be default constructible.");
  static_assert(std::is_destructible<XMP_AutoMutex>::value,
                "XMP_AutoMutex should be destructible.");
  SUCCEED();
}

TEST_F(XMPAutoMutexTest_2206, ConstructAndDestroy_DoesNotThrow_2206) {
  EXPECT_NO_THROW({
    XMP_AutoMutex lock;
    (void)lock;
  });
}

TEST_F(XMPAutoMutexTest_2206, NestedScopes_MultipleInstances_DoNotThrow_2206) {
  EXPECT_NO_THROW({
    XMP_AutoMutex lock1;
    (void)lock1;
    {
      XMP_AutoMutex lock2;
      (void)lock2;
    }
    {
      XMP_AutoMutex lock3;
      (void)lock3;
    }
  });
}

TEST_F(XMPAutoMutexTest_2206, KeepLock_IsCallable_2206) {
  XMP_AutoMutex lock;
  EXPECT_NO_THROW({ lock.KeepLock(); });
}

TEST_F(XMPAutoMutexTest_2206, KeepLock_CalledMultipleTimes_DoesNotThrow_2206) {
  XMP_AutoMutex lock;
  EXPECT_NO_THROW({
    lock.KeepLock();
    lock.KeepLock();
    lock.KeepLock();
  });
}

TEST_F(XMPAutoMutexTest_2206, CanBeAllocatedAndDeleted_DoesNotThrow_2206) {
  EXPECT_NO_THROW({
    auto* p = new XMP_AutoMutex();
    delete p;
  });
}

}  // namespace