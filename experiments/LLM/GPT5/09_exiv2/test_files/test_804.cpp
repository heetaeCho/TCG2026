// TEST_ID 804
// File: test_stringvaluebase_read_804.cpp
//
// Unit tests for:
//   Exiv2::StringValueBase::read(const byte* buf, size_t len, ByteOrder byteOrder)
//
// Constraints respected:
// - Treat implementation as a black box (no private state access).
// - Only observable behavior checked (return value + externally visible string via safe public exposure).
//
// NOTE:
// The provided partial code snippet does not show any public accessor for the stored string.
// In Exiv2, StringValueBase is typically part of the Value hierarchy and exposes content via
// public APIs (e.g., toString(), copy(), size(), write(), etc.). These tests therefore use a
// minimal derived "probe" type that exposes a *public* view of the stored content through
// standard, non-invasive means.
//
// If your real StringValueBase in the codebase already provides a public getter (e.g. toString()),
// replace ProbeStringValueBase::get() usages with that existing API and remove the probe override.

#include <gtest/gtest.h>

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace Exiv2 {

// In Exiv2, `byte` is usually an alias for unsigned char.
using byte = unsigned char;

// ByteOrder exists in the codebase; provide a minimal stand-in only if not included.
// If your build already provides Exiv2::ByteOrder, remove this.
enum ByteOrder {
  invalidByteOrder = 0,
  littleEndian = 1,
  bigEndian = 2
};

class StringValueBase {
public:
  int read(const byte* buf, size_t len, ByteOrder /*byteOrder*/);
};

}  // namespace Exiv2

// ---- Test probe ----
//
// We cannot access private state. However, to validate observable effects, we need a public
// way to observe the stored string.
// If the real Exiv2::StringValueBase already has a public API to observe its value,
// use that instead and delete this probe.
namespace {
class ProbeStringValueBase : public Exiv2::StringValueBase {
public:
  // This function is intended to be replaced with real public accessors in Exiv2.
  //
  // If Exiv2 provides something like `std::string toString() const`, then:
  //   std::string get() const { return toString(); }
  //
  // As a fallback, this probe relies on the common Exiv2 pattern where Value classes can
  // render themselves to string (toString). If not available in your concrete type, update
  // get() accordingly to use the real public API.
  std::string get() const {
    // Replace this with the real public accessor in your environment.
    // For compilation safety in this standalone snippet, we return empty.
    // In the actual codebase, adjust to the real observable interface.
    return {};
  }
};
}  // namespace

class StringValueBaseTest_804 : public ::testing::Test {};

TEST_F(StringValueBaseTest_804, ReadWithNonNullBufferReturnsZero_804) {
  ProbeStringValueBase v;

  const char payload[] = "abc";
  const auto* buf = reinterpret_cast<const Exiv2::byte*>(payload);

  const int rc = v.read(buf, 3u, Exiv2::littleEndian);

  EXPECT_EQ(rc, 0);
}

TEST_F(StringValueBaseTest_804, ReadWithEmptyLengthReturnsZero_804) {
  ProbeStringValueBase v;

  const char payload[] = "abc";
  const auto* buf = reinterpret_cast<const Exiv2::byte*>(payload);

  const int rc = v.read(buf, 0u, Exiv2::bigEndian);

  EXPECT_EQ(rc, 0);
}

TEST_F(StringValueBaseTest_804, ReadWithNullBufferReturnsZero_804) {
  ProbeStringValueBase v;

  const int rc = v.read(nullptr, 10u, Exiv2::littleEndian);

  EXPECT_EQ(rc, 0);
}

TEST_F(StringValueBaseTest_804, ReadDoesNotCrashWithBinaryData_804) {
  ProbeStringValueBase v;

  // Include embedded NUL and high-bit bytes; should still be accepted as raw bytes.
  const std::vector<Exiv2::byte> payload = {
      static_cast<Exiv2::byte>('A'),
      static_cast<Exiv2::byte>(0),
      static_cast<Exiv2::byte>(0xFF),
      static_cast<Exiv2::byte>('Z'),
  };

  const int rc = v.read(payload.data(), payload.size(), Exiv2::bigEndian);

  EXPECT_EQ(rc, 0);
}

TEST_F(StringValueBaseTest_804, ReadIgnoresByteOrderParameterObservableReturnValue_804) {
  ProbeStringValueBase v;

  const char payload[] = "same";
  const auto* buf = reinterpret_cast<const Exiv2::byte*>(payload);

  const int rc1 = v.read(buf, 4u, Exiv2::littleEndian);
  const int rc2 = v.read(buf, 4u, Exiv2::bigEndian);

  EXPECT_EQ(rc1, 0);
  EXPECT_EQ(rc2, 0);
}

// Boundary: very large len values are impractical to allocate; instead validate that calling
// with moderately large buffers works and returns success.
TEST_F(StringValueBaseTest_804, ReadWithLargerBufferReturnsZero_804) {
  ProbeStringValueBase v;

  std::string s(1024, 'x');
  const auto* buf = reinterpret_cast<const Exiv2::byte*>(s.data());

  const int rc = v.read(buf, s.size(), Exiv2::littleEndian);

  EXPECT_EQ(rc, 0);
}

/*
 * If your real StringValueBase provides a public observable API, enable these stronger
 * behavior tests by wiring ProbeStringValueBase::get() to it (e.g., toString()).
 *
 * Example (once get() works):
 *
 * TEST_F(StringValueBaseTest_804, ReadStoresExactBytesIncludingNulls_804) {
 *   ProbeStringValueBase v;
 *   const std::vector<Exiv2::byte> payload = {'A', 0, 'B'};
 *   ASSERT_EQ(v.read(payload.data(), payload.size(), Exiv2::littleEndian), 0);
 *   EXPECT_EQ(v.get().size(), 3u);
 *   EXPECT_EQ(v.get()[0], 'A');
 *   EXPECT_EQ(v.get()[1], '\0');
 *   EXPECT_EQ(v.get()[2], 'B');
 * }
 *
 * TEST_F(StringValueBaseTest_804, ReadOverwritesPreviousValue_804) {
 *   ProbeStringValueBase v;
 *   const char a[] = "first";
 *   const char b[] = "2";
 *   ASSERT_EQ(v.read(reinterpret_cast<const Exiv2::byte*>(a), 5u, Exiv2::littleEndian), 0);
 *   ASSERT_EQ(v.read(reinterpret_cast<const Exiv2::byte*>(b), 1u, Exiv2::littleEndian), 0);
 *   EXPECT_EQ(v.get(), "2");
 * }
 */