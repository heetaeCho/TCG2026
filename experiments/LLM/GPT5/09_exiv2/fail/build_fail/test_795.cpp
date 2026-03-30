// TEST_ID 795
// Unit tests for Exiv2::DataValue::copy (black-box via public interface)

#include <gtest/gtest.h>

#include <algorithm>
#include <array>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <memory>
#include <optional>
#include <type_traits>
#include <vector>

#if __has_include(<exiv2/value.hpp>)
#include <exiv2/value.hpp>
#elif __has_include("value.hpp")
#include "value.hpp"
#else
#error "Cannot find Exiv2 value.hpp (expected <exiv2/value.hpp> or \"value.hpp\")"
#endif

#if __has_include(<exiv2/types.hpp>)
#include <exiv2/types.hpp>
#elif __has_include("types.hpp")
#include "types.hpp"
#endif

namespace {

using Exiv2::byte;

template <typename T>
concept HasDefaultCtor = std::is_default_constructible_v<T>;

template <typename T>
concept HasReadLong = requires(T& v, const byte* p, long n, Exiv2::ByteOrder bo) {
  { v.read(p, n, bo) };
};

template <typename T>
concept HasReadSizeT = requires(T& v, const byte* p, std::size_t n, Exiv2::ByteOrder bo) {
  { v.read(p, n, bo) };
};

template <typename T>
concept CtorFromPtrSizeT = std::is_constructible_v<T, const byte*, std::size_t>;

template <typename T>
concept CtorFromPtrLong = std::is_constructible_v<T, const byte*, long>;

template <typename T>
concept CtorFromVectorByte = std::is_constructible_v<T, std::vector<byte>>;

template <typename T>
concept CtorFromVectorU8 = std::is_constructible_v<T, std::vector<uint8_t>>;

template <typename T>
std::unique_ptr<T> MakeDataValueWithBytes(const std::vector<byte>& bytes, Exiv2::ByteOrder bo) {
  if constexpr (HasDefaultCtor<T> && HasReadLong<T>) {
    auto v = std::make_unique<T>();
    // Use the public API only; do not assume any internal behavior beyond observability.
    v->read(bytes.data(), static_cast<long>(bytes.size()), bo);
    return v;
  } else if constexpr (HasDefaultCtor<T> && HasReadSizeT<T>) {
    auto v = std::make_unique<T>();
    v->read(bytes.data(), bytes.size(), bo);
    return v;
  } else if constexpr (CtorFromPtrSizeT<T>) {
    return std::make_unique<T>(bytes.data(), bytes.size());
  } else if constexpr (CtorFromPtrLong<T>) {
    return std::make_unique<T>(bytes.data(), static_cast<long>(bytes.size()));
  } else if constexpr (CtorFromVectorByte<T>) {
    return std::make_unique<T>(bytes);
  } else if constexpr (CtorFromVectorU8<T>) {
    std::vector<uint8_t> u8(bytes.begin(), bytes.end());
    return std::make_unique<T>(u8);
  } else {
    return nullptr;
  }
}

static Exiv2::ByteOrder AnyByteOrderA() {
#ifdef EXV_BYTE_ORDER // (not a real macro; keep conservative)
  return Exiv2::littleEndian;
#else
  // Exiv2 commonly defines these; if not, this still compiles only if ByteOrder exists.
  return Exiv2::littleEndian;
#endif
}

static Exiv2::ByteOrder AnyByteOrderB() {
  return Exiv2::bigEndian;
}

class DataValueTest_795 : public ::testing::Test {};

}  // namespace

TEST_F(DataValueTest_795, CopyOnDefaultConstructedWritesZero_795) {
  // If DataValue isn't default-constructible in this build, we can't observe this behavior.
  if constexpr (!std::is_default_constructible_v<Exiv2::DataValue>) {
    GTEST_SKIP() << "Exiv2::DataValue is not default-constructible in this build.";
  } else {
    Exiv2::DataValue v;

    std::array<byte, 8> out{};
    std::fill(out.begin(), out.end(), static_cast<byte>(0xAA));

    const auto written = v.copy(out.data(), AnyByteOrderA());

    EXPECT_EQ(written, 0u);

    // No bytes should have been overwritten if nothing was copied.
    EXPECT_TRUE(std::all_of(out.begin(), out.end(),
                            [](byte b) { return b == static_cast<byte>(0xAA); }));
  }
}

TEST_F(DataValueTest_795, CopyCopiesAllBytesAndReturnsCount_795) {
  const std::vector<byte> input{0x00, 0x01, 0x7F, 0x80, 0xFE, 0xFF};
  auto v = MakeDataValueWithBytes<Exiv2::DataValue>(input, AnyByteOrderA());
  if (!v) {
    GTEST_SKIP() << "No public way found to construct/populate Exiv2::DataValue in this build.";
  }

  std::vector<byte> out(input.size(), static_cast<byte>(0xAA));
  const auto written = v->copy(out.data(), AnyByteOrderA());

  EXPECT_EQ(written, input.size());
  EXPECT_EQ(out, input);
}

TEST_F(DataValueTest_795, CopyDoesNotClobberBytesBeyondReturnedCount_795) {
  const std::vector<byte> input{0x10, 0x20, 0x30, 0x40};
  auto v = MakeDataValueWithBytes<Exiv2::DataValue>(input, AnyByteOrderA());
  if (!v) {
    GTEST_SKIP() << "No public way found to construct/populate Exiv2::DataValue in this build.";
  }

  std::vector<byte> out(input.size() + 5, static_cast<byte>(0xAA));
  const auto written = v->copy(out.data(), AnyByteOrderA());

  ASSERT_EQ(written, input.size());

  // First N bytes match.
  EXPECT_TRUE(std::equal(input.begin(), input.end(), out.begin()));

  // Remaining bytes unchanged.
  EXPECT_TRUE(std::all_of(out.begin() + static_cast<std::ptrdiff_t>(input.size()), out.end(),
                          [](byte b) { return b == static_cast<byte>(0xAA); }));
}

TEST_F(DataValueTest_795, CopyResultIndependentOfByteOrderParameter_795) {
  const std::vector<byte> input{0xDE, 0xAD, 0xBE, 0xEF, 0x11};
  auto v = MakeDataValueWithBytes<Exiv2::DataValue>(input, AnyByteOrderA());
  if (!v) {
    GTEST_SKIP() << "No public way found to construct/populate Exiv2::DataValue in this build.";
  }

  std::vector<byte> outA(input.size(), static_cast<byte>(0xAA));
  std::vector<byte> outB(input.size(), static_cast<byte>(0xAA));

  const auto writtenA = v->copy(outA.data(), AnyByteOrderA());
  const auto writtenB = v->copy(outB.data(), AnyByteOrderB());

  EXPECT_EQ(writtenA, input.size());
  EXPECT_EQ(writtenB, input.size());
  EXPECT_EQ(outA, input);
  EXPECT_EQ(outB, input);
}

TEST_F(DataValueTest_795, CopyWithNonTrivialSizePayload_795) {
  // Boundary-ish: larger payload (still small enough for unit test)
  std::vector<byte> input(1024);
  for (std::size_t i = 0; i < input.size(); ++i) {
    input[i] = static_cast<byte>(i & 0xFF);
  }

  auto v = MakeDataValueWithBytes<Exiv2::DataValue>(input, AnyByteOrderA());
  if (!v) {
    GTEST_SKIP() << "No public way found to construct/populate Exiv2::DataValue in this build.";
  }

  std::vector<byte> out(input.size(), static_cast<byte>(0xAA));
  const auto written = v->copy(out.data(), AnyByteOrderA());

  EXPECT_EQ(written, input.size());
  EXPECT_EQ(out, input);
}