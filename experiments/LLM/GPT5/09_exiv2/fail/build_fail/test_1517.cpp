// =================================================================================================
// Unit tests for: Exiv2::Internal::newFujiMn2 (makernote_int.cpp)
// TEST_ID: 1517
//
// Constraints honored:
// - Treat implementation as black box (no internal logic assumptions beyond observable interface).
// - Use only public/visible behavior from returned object.
// - No private state access.
// - No mocking internal behavior.
// =================================================================================================

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <type_traits>

#include "tiffcomposite_int.hpp"  // Exiv2::Internal::TiffIfdMakernote, IfdId (expected in Exiv2 internals)

namespace {

class FujiMn2FactoryTest_1517 : public ::testing::Test {};

TEST_F(FujiMn2FactoryTest_1517, ReturnsNonNullUniquePtr_1517) {
  // Normal operation: factory should return a valid object.
  auto mn = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0001),
                                       static_cast<Exiv2::Internal::IfdId>(0),
                                       static_cast<Exiv2::Internal::IfdId>(0));
  ASSERT_NE(mn, nullptr);
}

TEST_F(FujiMn2FactoryTest_1517, ReturnsDistinctObjectsOnEachCall_1517) {
  // Normal operation: repeated calls should yield distinct objects (no shared singleton).
  auto mn1 = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0001),
                                        static_cast<Exiv2::Internal::IfdId>(0),
                                        static_cast<Exiv2::Internal::IfdId>(0));
  auto mn2 = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0001),
                                        static_cast<Exiv2::Internal::IfdId>(0),
                                        static_cast<Exiv2::Internal::IfdId>(0));

  ASSERT_NE(mn1, nullptr);
  ASSERT_NE(mn2, nullptr);
  EXPECT_NE(mn1.get(), mn2.get());
}

TEST_F(FujiMn2FactoryTest_1517, AcceptsBoundaryTagValues_1517) {
  // Boundary conditions: tag is uint16_t; test min/max.
  auto mnMin = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0000),
                                          static_cast<Exiv2::Internal::IfdId>(0),
                                          static_cast<Exiv2::Internal::IfdId>(0));
  auto mnMax = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0xFFFF),
                                          static_cast<Exiv2::Internal::IfdId>(0),
                                          static_cast<Exiv2::Internal::IfdId>(0));

  EXPECT_NE(mnMin, nullptr);
  EXPECT_NE(mnMax, nullptr);
}

TEST_F(FujiMn2FactoryTest_1517, AcceptsVariousGroupValues_1517) {
  // Boundary-ish/robustness: IfdId is an enum-like type in Exiv2 internals.
  // We avoid assuming valid enumerators and only verify that creation doesn't throw
  // and produces a non-null object for several representative underlying values.
  using IfdIdT = Exiv2::Internal::IfdId;

  auto mn1 = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0100),
                                        static_cast<IfdIdT>(0),
                                        static_cast<IfdIdT>(1));
  auto mn2 = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0101),
                                        static_cast<IfdIdT>(-1),
                                        static_cast<IfdIdT>(2));
  auto mn3 = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0102),
                                        static_cast<IfdIdT>(12345),
                                        static_cast<IfdIdT>(-12345));

  EXPECT_NE(mn1, nullptr);
  EXPECT_NE(mn2, nullptr);
  EXPECT_NE(mn3, nullptr);
}

TEST_F(FujiMn2FactoryTest_1517, IsMovableUniquePtr_1517) {
  // Observable property: factory returns std::unique_ptr, it should be movable.
  auto mn = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x0002),
                                       static_cast<Exiv2::Internal::IfdId>(0),
                                       static_cast<Exiv2::Internal::IfdId>(0));
  ASSERT_NE(mn, nullptr);

  auto raw = mn.get();
  std::unique_ptr<Exiv2::Internal::TiffIfdMakernote> moved = std::move(mn);

  EXPECT_EQ(mn.get(), nullptr);
  ASSERT_NE(moved, nullptr);
  EXPECT_EQ(moved.get(), raw);
}

TEST_F(FujiMn2FactoryTest_1517, ConstructionDoesNotThrow_1517) {
  // Exceptional/error case (observable): ensure factory itself does not throw
  // for typical inputs. If it throws, that's observable via the interface.
  EXPECT_NO_THROW({
    auto mn = Exiv2::Internal::newFujiMn2(static_cast<uint16_t>(0x1234),
                                         static_cast<Exiv2::Internal::IfdId>(0),
                                         static_cast<Exiv2::Internal::IfdId>(0));
    ASSERT_NE(mn, nullptr);
  });
}

TEST_F(FujiMn2FactoryTest_1517, ReturnTypeIsUniquePtrOfExpectedPointee_1517) {
  // Compile-time contract check based strictly on the signature.
  using RetT = decltype(Exiv2::Internal::newFujiMn2(uint16_t{}, Exiv2::Internal::IfdId{}, Exiv2::Internal::IfdId{}));
  static_assert(std::is_same_v<RetT, std::unique_ptr<Exiv2::Internal::TiffIfdMakernote>>,
                "newFujiMn2 must return std::unique_ptr<TiffIfdMakernote>");
  SUCCEED();
}

}  // namespace