// SPDX-License-Identifier: GPL-2.0-or-later
//
// File: test_memio_reserve_575.cpp
//
// Tests for Exiv2::MemIo behavior that (indirectly) exercises MemIo::Impl::reserve()
// from ./TestProjects/exiv2/src/basicio.cpp, treating implementation as a black box.

#include <gtest/gtest.h>

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <vector>

#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"

#if defined(__unix__) || defined(__APPLE__)
#include <atomic>
#include <dlfcn.h>
#endif

namespace {

using Exiv2::byte;

static std::vector<byte> MakePattern(std::size_t n, byte seed = 0x10) {
  std::vector<byte> v(n);
  for (std::size_t i = 0; i < n; ++i) v[i] = static_cast<byte>(seed + (i % 251));
  return v;
}

#if defined(__unix__) || defined(__APPLE__)
// --- malloc/realloc interposition to simulate allocation failures (exceptional cases) ---
// This is intentionally limited and guarded so tests can skip if RTLD_NEXT isn't available.

static std::atomic<bool> g_fail_next_malloc{false};
static std::atomic<bool> g_fail_next_realloc{false};

using MallocFn = void* (*)(std::size_t);
using ReallocFn = void* (*)(void*, std::size_t);

static MallocFn RealMalloc() {
  static MallocFn fn = reinterpret_cast<MallocFn>(dlsym(RTLD_NEXT, "malloc"));
  return fn;
}

static ReallocFn RealRealloc() {
  static ReallocFn fn = reinterpret_cast<ReallocFn>(dlsym(RTLD_NEXT, "realloc"));
  return fn;
}

extern "C" void* malloc(std::size_t size) {
  if (g_fail_next_malloc.exchange(false)) return nullptr;
  auto fn = RealMalloc();
  return fn ? fn(size) : nullptr;
}

extern "C" void* realloc(void* ptr, std::size_t size) {
  if (g_fail_next_realloc.exchange(false)) return nullptr;
  auto fn = RealRealloc();
  return fn ? fn(ptr, size) : nullptr;
}

static bool HasInterpositionSupport() {
  return RealMalloc() != nullptr && RealRealloc() != nullptr;
}
#endif

}  // namespace

// -------------------- Normal + boundary behavior --------------------

TEST(MemIoReserveTest_575, WriteSmallBufferUpdatesSizeAndPreservesData_575) {
  Exiv2::MemIo io;

  const auto payload = MakePattern(128, 0x22);
  ASSERT_EQ(128U, payload.size());

  // Write should report number of bytes written.
  const long wrote = io.write(payload.data(), static_cast<long>(payload.size()));
  EXPECT_EQ(static_cast<long>(payload.size()), wrote);

  // Size should reflect bytes written.
  EXPECT_EQ(static_cast<long>(payload.size()), io.size());

  // Read back from the beginning and compare.
  ASSERT_EQ(0L, io.seek(0, Exiv2::BasicIo::beg));
  std::vector<byte> out(payload.size());
  const long read = io.read(out.data(), static_cast<long>(out.size()));
  EXPECT_EQ(static_cast<long>(out.size()), read);
  EXPECT_EQ(payload, out);
}

TEST(MemIoReserveTest_575, ZeroLengthWriteIsNoOpAndDoesNotThrow_575) {
  Exiv2::MemIo io;

  const auto beforeSize = io.size();
  const byte dummy = 0xAB;

  // Many IO APIs allow (ptr,0) as a no-op; verify observable behavior only:
  // - must not throw
  // - must not increase size
  EXPECT_NO_THROW({
    const long wrote = io.write(&dummy, 0L);
    EXPECT_EQ(0L, wrote);
  });

  EXPECT_EQ(beforeSize, io.size());
}

TEST(MemIoReserveTest_575, LargeWriteGrowsStorageAndDataRoundTrips_575) {
  Exiv2::MemIo io;

  // Larger than 32 KiB to ensure growth behavior is exercised.
  const std::size_t n = 40U * 1024U;
  const auto payload = MakePattern(n, 0x33);

  const long wrote = io.write(payload.data(), static_cast<long>(payload.size()));
  EXPECT_EQ(static_cast<long>(payload.size()), wrote);
  EXPECT_EQ(static_cast<long>(payload.size()), io.size());

  ASSERT_EQ(0L, io.seek(0, Exiv2::BasicIo::beg));
  std::vector<byte> out(payload.size());
  const long read = io.read(out.data(), static_cast<long>(out.size()));
  EXPECT_EQ(static_cast<long>(out.size()), read);
  EXPECT_EQ(payload, out);
}

TEST(MemIoReserveTest_575, GrowthPreservesExistingPrefixAcrossMultipleWrites_575) {
  Exiv2::MemIo io;

  const auto first = MakePattern(8U * 1024U, 0x40);
  const auto second = MakePattern(48U * 1024U, 0x55);  // triggers growth beyond the first write

  ASSERT_EQ(static_cast<long>(first.size()),
            io.write(first.data(), static_cast<long>(first.size())));
  ASSERT_EQ(static_cast<long>(first.size()), io.size());

  ASSERT_EQ(static_cast<long>(second.size()),
            io.write(second.data(), static_cast<long>(second.size())));
  ASSERT_EQ(static_cast<long>(first.size() + second.size()), io.size());

  // Read back everything; ensure prefix equals `first` and suffix equals `second`.
  ASSERT_EQ(0L, io.seek(0, Exiv2::BasicIo::beg));
  std::vector<byte> all(static_cast<std::size_t>(io.size()));
  ASSERT_EQ(io.size(), io.read(all.data(), static_cast<long>(all.size())));

  ASSERT_GE(all.size(), first.size() + second.size());
  EXPECT_TRUE(std::equal(first.begin(), first.end(), all.begin()));
  EXPECT_TRUE(std::equal(second.begin(), second.end(), all.begin() + first.size()));
}

// -------------------- Exceptional / error behavior (observable) --------------------

#if defined(__unix__) || defined(__APPLE__)

TEST(MemIoReserveTest_575, MallocFailureOnFirstGrowthThrowsKerMallocFailed_575) {
  if (!HasInterpositionSupport()) GTEST_SKIP() << "malloc/realloc interposition not available";

  // Construct from an existing buffer so the first reserve path does a malloc+memcpy
  // (i.e., it starts as "not malloced" storage).
  const auto initial = MakePattern(1024U, 0x60);
  Exiv2::MemIo io(initial.data(), static_cast<long>(initial.size()));

  // Force the next malloc to fail.
  g_fail_next_malloc.store(true);

  const auto extra = MakePattern(2048U, 0x61);
  try {
    (void)io.write(extra.data(), static_cast<long>(extra.size()));
    FAIL() << "Expected Exiv2::Error due to forced malloc failure";
  } catch (const Exiv2::Error& e) {
    // Verify observable error code when available.
    EXPECT_EQ(Exiv2::ErrorCode::kerMallocFailed, e.code());
  }
}

TEST(MemIoReserveTest_575, ReallocFailureDuringGrowthThrowsKerMallocFailed_575) {
  if (!HasInterpositionSupport()) GTEST_SKIP() << "malloc/realloc interposition not available";

  Exiv2::MemIo io;

  // First, write enough to allocate initial internal storage.
  const auto first = MakePattern(64U * 1024U, 0x70);
  ASSERT_EQ(static_cast<long>(first.size()),
            io.write(first.data(), static_cast<long>(first.size())));
  ASSERT_EQ(static_cast<long>(first.size()), io.size());

  // Now force realloc failure on the next growth attempt.
  g_fail_next_realloc.store(true);

  // Write more to trigger growth. The exact threshold is an implementation detail;
  // we only require that a growth attempt results in a kerMallocFailed error when realloc fails.
  const auto second = MakePattern(2U * 1024U * 1024U, 0x71);  // large write increases chance of growth
  try {
    (void)io.write(second.data(), static_cast<long>(second.size()));
    FAIL() << "Expected Exiv2::Error due to forced realloc failure";
  } catch (const Exiv2::Error& e) {
    EXPECT_EQ(Exiv2::ErrorCode::kerMallocFailed, e.code());
  }
}

#else

TEST(MemIoReserveTest_575, AllocationFailureTestsSkippedOnNonPosix_575) {
  GTEST_SKIP() << "malloc/realloc interposition is implemented only for POSIX platforms in this test";
}

#endif