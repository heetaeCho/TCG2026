// File: test_tiffreader_ctor_2202.cpp
// TEST_ID: 2202

#include <gtest/gtest.h>

#include <array>
#include <cstddef>
#include <cstdint>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace {

// A minimal concrete root component for wiring the TiffReader constructor.
// We do not rely on any internal behavior of TiffComponent; it is only used
// as a non-null pointer dependency.
class DummyRootComponent_2202 : public Exiv2::Internal::TiffComponent {
 public:
  DummyRootComponent_2202(uint16_t tag, Exiv2::Internal::IfdId group)
      : Exiv2::Internal::TiffComponent(tag, group) {}
  ~DummyRootComponent_2202() override = default;
};

class TiffReaderTest_2202 : public ::testing::Test {
 protected:
  // Ensure we always pass a valid pointer (even when size==0) to avoid UB.
  std::array<Exiv2::byte, 8> buf_{};

  DummyRootComponent_2202 root_{0x1234, static_cast<Exiv2::Internal::IfdId>(0)};

  // Helper: create a state with chosen byte order + base offset.
  Exiv2::Internal::TiffRwState MakeState(Exiv2::ByteOrder bo, std::size_t base) {
    return Exiv2::Internal::TiffRwState(bo, base);
  }
};

}  // namespace

TEST_F(TiffReaderTest_2202, ConstructorExposesOriginalStateViaAccessors_2202) {
  const auto state = MakeState(Exiv2::littleEndian, 0u);

  Exiv2::Internal::TiffReader reader(buf_.data(), buf_.size(), &root_, state);

  EXPECT_EQ(reader.byteOrder(), state.byteOrder());
  EXPECT_EQ(reader.baseOffset(), state.baseOffset());
}

TEST_F(TiffReaderTest_2202, ConstructorHandlesZeroSizeBuffer_2202) {
  const auto state = MakeState(Exiv2::bigEndian, 42u);

  Exiv2::Internal::TiffReader reader(buf_.data(), 0u, &root_, state);

  EXPECT_EQ(reader.byteOrder(), state.byteOrder());
  EXPECT_EQ(reader.baseOffset(), state.baseOffset());
}

TEST_F(TiffReaderTest_2202, SetMnStateSwitchesAccessorsToMakernoteState_2202) {
  const auto orig = MakeState(Exiv2::littleEndian, 10u);
  const auto mn = MakeState(Exiv2::bigEndian, 999u);

  Exiv2::Internal::TiffReader reader(buf_.data(), buf_.size(), &root_, orig);

  reader.setMnState(&mn);

  EXPECT_EQ(reader.byteOrder(), mn.byteOrder());
  EXPECT_EQ(reader.baseOffset(), mn.baseOffset());
}

TEST_F(TiffReaderTest_2202, SetOrigStateRestoresOriginalStateAfterMakernoteState_2202) {
  const auto orig = MakeState(Exiv2::bigEndian, 1u);
  const auto mn = MakeState(Exiv2::littleEndian, 777u);

  Exiv2::Internal::TiffReader reader(buf_.data(), buf_.size(), &root_, orig);

  reader.setMnState(&mn);
  ASSERT_EQ(reader.byteOrder(), mn.byteOrder());
  ASSERT_EQ(reader.baseOffset(), mn.baseOffset());

  reader.setOrigState();

  EXPECT_EQ(reader.byteOrder(), orig.byteOrder());
  EXPECT_EQ(reader.baseOffset(), orig.baseOffset());
}