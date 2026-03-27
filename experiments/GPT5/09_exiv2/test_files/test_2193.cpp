// TEST_ID 2193
// Unit tests for Exiv2::Internal::SamsungMnHeader
//
// Constraints respected:
// - Treat implementation as a black box
// - Use only public interface / observable behavior
// - No private-state access

#include <gtest/gtest.h>

#include <limits>
#include <memory>
#include <type_traits>

// Exiv2 public/internal headers (paths may vary by project setup)
#include "makernote_int.hpp"
#include "basicio.hpp"

namespace {

// Helper: attempt to construct an Exiv2::Internal::IoWrapper in a way that compiles
// across Exiv2 versions/build variants, using if constexpr to avoid instantiating
// non-existent constructors.
template <typename IoWrapperT, typename BasicIoT>
std::unique_ptr<IoWrapperT> TryMakeIoWrapper(BasicIoT& bio) {
  // Common-ish constructor candidates across Exiv2 internal code.
  if constexpr (std::is_constructible_v<IoWrapperT, BasicIoT&>) {
    return std::make_unique<IoWrapperT>(bio);
  } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIoT&, Exiv2::ByteOrder>) {
    return std::make_unique<IoWrapperT>(bio, Exiv2::littleEndian);
  } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIoT&, bool>) {
    return std::make_unique<IoWrapperT>(bio, false);
  } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIoT&, std::size_t>) {
    return std::make_unique<IoWrapperT>(bio, static_cast<std::size_t>(0));
  } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIoT&, std::size_t, Exiv2::ByteOrder>) {
    return std::make_unique<IoWrapperT>(bio, static_cast<std::size_t>(0), Exiv2::littleEndian);
  } else {
    return nullptr;
  }
}

class SamsungMnHeaderTest_2193 : public ::testing::Test {};

}  // namespace

TEST_F(SamsungMnHeaderTest_2193, DefaultConstruct_DoesNotThrow_2193) {
  EXPECT_NO_THROW({
    Exiv2::Internal::SamsungMnHeader h;
    (void)h;
  });
}

TEST_F(SamsungMnHeaderTest_2193, Read_WithNullAndZeroSize_IsCallable_2193) {
  Exiv2::Internal::SamsungMnHeader h;

  // Constructor already calls read(nullptr, 0, invalidByteOrder) in provided snippet.
  // Here we only verify the method is callable and returns a boolean.
  bool result = false;
  EXPECT_NO_THROW({ result = h.read(nullptr, 0, Exiv2::invalidByteOrder); });
  (void)result;  // Do not assert semantics; treat as black box.
}

TEST_F(SamsungMnHeaderTest_2193, Size_IsStableAcrossCalls_2193) {
  Exiv2::Internal::SamsungMnHeader h;

  const std::size_t s1 = h.size();
  const std::size_t s2 = h.size();

  // Observable property: repeated calls should be consistent.
  EXPECT_EQ(s1, s2);
}

TEST_F(SamsungMnHeaderTest_2193, BaseOffset_BoundaryInputs_AreCallableAndStable_2193) {
  Exiv2::Internal::SamsungMnHeader h;

  const std::size_t inputs[] = {
      static_cast<std::size_t>(0),
      static_cast<std::size_t>(1),
      std::numeric_limits<std::size_t>::max(),
  };

  for (std::size_t mnOffset : inputs) {
    std::size_t b1 = 0, b2 = 0;
    EXPECT_NO_THROW({ b1 = h.baseOffset(mnOffset); });
    EXPECT_NO_THROW({ b2 = h.baseOffset(mnOffset); });
    EXPECT_EQ(b1, b2) << "baseOffset should be stable for mnOffset=" << mnOffset;
  }
}

TEST_F(SamsungMnHeaderTest_2193, ByteOrder_SetAndGet_RoundTrips_2193) {
  Exiv2::Internal::SamsungMnHeader h;

  // MnHeader exposes setByteOrder / byteOrder. This is observable state via the interface.
  h.setByteOrder(Exiv2::littleEndian);
  EXPECT_EQ(h.byteOrder(), Exiv2::littleEndian);

  h.setByteOrder(Exiv2::bigEndian);
  EXPECT_EQ(h.byteOrder(), Exiv2::bigEndian);

  h.setByteOrder(Exiv2::invalidByteOrder);
  EXPECT_EQ(h.byteOrder(), Exiv2::invalidByteOrder);
}

TEST_F(SamsungMnHeaderTest_2193, IfdOffset_IsCallableAndStable_2193) {
  Exiv2::Internal::SamsungMnHeader h;

  std::size_t o1 = 0, o2 = 0;
  EXPECT_NO_THROW({ o1 = h.ifdOffset(); });
  EXPECT_NO_THROW({ o2 = h.ifdOffset(); });

  EXPECT_EQ(o1, o2);
}

TEST_F(SamsungMnHeaderTest_2193, Write_CanBeInvokedWhenIoWrapperIsConstructible_2193) {
  Exiv2::Internal::SamsungMnHeader h;

  // Use Exiv2 memory IO as the backing store (public API).
  Exiv2::MemIo memIo;

  using IoWrapperT = Exiv2::Internal::IoWrapper;
  auto ioWrapper = TryMakeIoWrapper<IoWrapperT>(memIo);
  if (!ioWrapper) {
    GTEST_SKIP() << "IoWrapper is not constructible with known constructor patterns in this build.";
  }

  std::size_t written1 = 0, written2 = 0;
  EXPECT_NO_THROW({ written1 = h.write(*ioWrapper, Exiv2::invalidByteOrder); });
  EXPECT_NO_THROW({ written2 = h.write(*ioWrapper, Exiv2::invalidByteOrder); });

  // Only assert stability for identical inputs; do not infer actual write semantics.
  EXPECT_EQ(written1, written2);
}