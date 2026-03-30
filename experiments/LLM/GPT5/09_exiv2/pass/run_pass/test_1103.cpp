// SPDX-License-Identifier: GPL-2.0-or-later

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>

#include <cstddef>
#include <cstdint>
#include <string>
#include <utility>

namespace {

// Helper that compares the observable behavior of:
//   ImageFactory::getType(const byte*, size_t)
// vs
//   ImageFactory::getType(BasicIo&)
//
// Requirement: treat implementation as a black box; verify delegation via
// equivalence of observable outcomes (same return value or same exception kind).
struct GetTypeOutcome {
  bool threw = false;
  std::string exception_kind;  // "Exiv2::Error", "std::exception", "unknown"
  Exiv2::ImageType type = Exiv2::ImageType::none;

  static GetTypeOutcome FromData(Exiv2::ImageFactory& f, const Exiv2::byte* data, size_t size) {
    GetTypeOutcome o;
    try {
      o.type = f.getType(data, size);
    } catch (const Exiv2::Error&) {
      o.threw = true;
      o.exception_kind = "Exiv2::Error";
    } catch (const std::exception&) {
      o.threw = true;
      o.exception_kind = "std::exception";
    } catch (...) {
      o.threw = true;
      o.exception_kind = "unknown";
    }
    return o;
  }

  static GetTypeOutcome FromIo(Exiv2::ImageFactory& f, Exiv2::BasicIo& io) {
    GetTypeOutcome o;
    try {
      o.type = f.getType(io);
    } catch (const Exiv2::Error&) {
      o.threw = true;
      o.exception_kind = "Exiv2::Error";
    } catch (const std::exception&) {
      o.threw = true;
      o.exception_kind = "std::exception";
    } catch (...) {
      o.threw = true;
      o.exception_kind = "unknown";
    }
    return o;
  }
};

}  // namespace

class ImageFactoryGetTypeFromDataTest_1103 : public ::testing::Test {
 protected:
  Exiv2::ImageFactory factory_;
};

TEST_F(ImageFactoryGetTypeFromDataTest_1103, DelegatesToIoOverloadForTypicalBuffer_1103) {
  // A small, arbitrary buffer. We do NOT assume it corresponds to any format.
  const Exiv2::byte buf[] = {0x00, 0x11, 0x22, 0x33, 0x44, 0x55};

  Exiv2::MemIo mem(buf, sizeof(buf));

  const auto from_data = GetTypeOutcome::FromData(factory_, buf, sizeof(buf));
  const auto from_io = GetTypeOutcome::FromIo(factory_, mem);

  // Observable equivalence: both succeed with same ImageType, or both throw the same "kind".
  ASSERT_EQ(from_data.threw, from_io.threw);
  if (!from_data.threw) {
    EXPECT_EQ(from_data.type, from_io.type);
  } else {
    EXPECT_EQ(from_data.exception_kind, from_io.exception_kind);
  }
}

TEST_F(ImageFactoryGetTypeFromDataTest_1103, EmptyBufferBehavesSameAsMemIoOverload_1103) {
  // Boundary: empty input. Use nullptr with size 0 to avoid reading any memory.
  const Exiv2::byte* buf = nullptr;
  const size_t size = 0;

  Exiv2::MemIo mem(buf, size);

  const auto from_data = GetTypeOutcome::FromData(factory_, buf, size);
  const auto from_io = GetTypeOutcome::FromIo(factory_, mem);

  ASSERT_EQ(from_data.threw, from_io.threw);
  if (!from_data.threw) {
    EXPECT_EQ(from_data.type, from_io.type);
  } else {
    EXPECT_EQ(from_data.exception_kind, from_io.exception_kind);
  }
}

TEST_F(ImageFactoryGetTypeFromDataTest_1103, NonEmptyBufferBehavesSameAsMemIoOverload_1103) {
  // Boundary-ish: minimal non-empty input (size 1).
  const Exiv2::byte buf[] = {0xFF};

  Exiv2::MemIo mem(buf, sizeof(buf));

  const auto from_data = GetTypeOutcome::FromData(factory_, buf, sizeof(buf));
  const auto from_io = GetTypeOutcome::FromIo(factory_, mem);

  ASSERT_EQ(from_data.threw, from_io.threw);
  if (!from_data.threw) {
    EXPECT_EQ(from_data.type, from_io.type);
  } else {
    EXPECT_EQ(from_data.exception_kind, from_io.exception_kind);
  }
}

TEST_F(ImageFactoryGetTypeFromDataTest_1103, LargerArbitraryBufferBehavesSameAsMemIoOverload_1103) {
  // Another normal-operation case with a larger buffer; still no format assumptions.
  Exiv2::byte buf[256]{};
  for (size_t i = 0; i < sizeof(buf); ++i) {
    buf[i] = static_cast<Exiv2::byte>(i & 0xFF);
  }

  Exiv2::MemIo mem(buf, sizeof(buf));

  const auto from_data = GetTypeOutcome::FromData(factory_, buf, sizeof(buf));
  const auto from_io = GetTypeOutcome::FromIo(factory_, mem);

  ASSERT_EQ(from_data.threw, from_io.threw);
  if (!from_data.threw) {
    EXPECT_EQ(from_data.type, from_io.type);
  } else {
    EXPECT_EQ(from_data.exception_kind, from_io.exception_kind);
  }
}