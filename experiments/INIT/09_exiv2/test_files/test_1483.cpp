// =================================================================================================
//  Unit tests for Exiv2::Internal::PentaxDngMnHeader::write
//  File: makernote_int.cpp (class is implemented in the production codebase)
// =================================================================================================

#include <gtest/gtest.h>

#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>

// The header that declares Exiv2::Internal::PentaxDngMnHeader / IoWrapper in the real codebase.
// Depending on your Exiv2 tree, one of these will exist. Keep the first that compiles.
#if __has_include("makernote_int.hpp")
#  include "makernote_int.hpp"
#elif __has_include("makernote_int.hpp")
#  include "makernote_int.hpp"
#elif __has_include("tiffimage_int.hpp")
#  include "tiffimage_int.hpp"
#else
#  include "makernote_int.hpp"
#endif

#include <type_traits>
#include <utility>

namespace {

// ---- Detection helpers to adapt to IoWrapper API without re-implementing logic ----

template <typename...>
using void_t = void;

template <typename T, typename = void>
struct has_setTarget_basicio_ptr : std::false_type {};
template <typename T>
struct has_setTarget_basicio_ptr<
    T, void_t<decltype(std::declval<T&>().setTarget(static_cast<Exiv2::BasicIo*>(nullptr)))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_setTarget_basicio_ref : std::false_type {};
template <typename T>
struct has_setTarget_basicio_ref<
    T, void_t<decltype(std::declval<T&>().setTarget(std::declval<Exiv2::BasicIo&>()))>>
    : std::true_type {};

template <typename T, typename = void>
struct has_setByteOrder : std::false_type {};
template <typename T>
struct has_setByteOrder<T, void_t<decltype(std::declval<T&>().setByteOrder(Exiv2::littleEndian))>>
    : std::true_type {};

template <typename IoWrapperT>
IoWrapperT MakeIoWrapper(Exiv2::BasicIo& io, Exiv2::ByteOrder bo) {
  // Try common patterns in Exiv2 internals: default-construct + setTarget, or direct construction.
  if constexpr (std::is_default_constructible<IoWrapperT>::value) {
    IoWrapperT w{};
    if constexpr (has_setTarget_basicio_ptr<IoWrapperT>::value) {
      w.setTarget(&io);
    } else if constexpr (has_setTarget_basicio_ref<IoWrapperT>::value) {
      w.setTarget(io);
    } else {
      // If we can't set the target, fall back to other constructors below.
      // (Return after trying constructors.)
      (void)w;
      goto try_constructors;
    }

    if constexpr (has_setByteOrder<IoWrapperT>::value) {
      w.setByteOrder(bo);
    }
    return w;
  }

try_constructors:
  if constexpr (std::is_constructible<IoWrapperT, Exiv2::BasicIo&, Exiv2::ByteOrder>::value) {
    return IoWrapperT(io, bo);
  } else if constexpr (std::is_constructible<IoWrapperT, Exiv2::BasicIo*, Exiv2::ByteOrder>::value) {
    return IoWrapperT(&io, bo);
  } else if constexpr (std::is_constructible<IoWrapperT, Exiv2::BasicIo&>::value) {
    return IoWrapperT(io);
  } else if constexpr (std::is_constructible<IoWrapperT, Exiv2::BasicIo*>::value) {
    return IoWrapperT(&io);
  } else {
    // If none match, this test translation unit cannot create an IoWrapper for the local Exiv2 tree.
    // Fail fast with a clear message.
    static_assert(std::is_constructible<IoWrapperT, Exiv2::BasicIo&>::value ||
                      std::is_constructible<IoWrapperT, Exiv2::BasicIo*>::value ||
                      std::is_constructible<IoWrapperT, Exiv2::BasicIo&, Exiv2::ByteOrder>::value ||
                      std::is_constructible<IoWrapperT, Exiv2::BasicIo*, Exiv2::ByteOrder>::value ||
                      std::is_default_constructible<IoWrapperT>::value,
                  "Unable to construct IoWrapper in this Exiv2 configuration.");
    return IoWrapperT(io);  // Unreachable if static_assert triggers.
  }
}

}  // namespace

// -------------------------------------------------------------------------------------------------
// Fixture
// -------------------------------------------------------------------------------------------------
class PentaxDngMnHeaderWriteTest_1483 : public ::testing::Test {
 protected:
  using Header = Exiv2::Internal::PentaxDngMnHeader;
  using IoWrapper = Exiv2::Internal::IoWrapper;

  Header header_;
};

// -------------------------------------------------------------------------------------------------
// Tests (TEST_ID = 1483)
// -------------------------------------------------------------------------------------------------

TEST_F(PentaxDngMnHeaderWriteTest_1483, WriteToEmptyMemIoReturnsNonZeroAndMatchesBytesAppended_1483) {
  Exiv2::MemIo mem;
  const auto beforeSize = mem.size();

  auto wrapper = MakeIoWrapper<IoWrapper>(mem, Exiv2::littleEndian);

  const size_t written = header_.write(wrapper, Exiv2::littleEndian);

  EXPECT_GT(written, 0u);
  EXPECT_EQ(mem.size(), beforeSize + written);
}

TEST_F(PentaxDngMnHeaderWriteTest_1483, WriteTwiceAppendsTwiceTheReturnedByteCount_1483) {
  Exiv2::MemIo mem;
  auto wrapper = MakeIoWrapper<IoWrapper>(mem, Exiv2::littleEndian);

  const auto beforeSize = mem.size();
  const size_t w1 = header_.write(wrapper, Exiv2::littleEndian);
  const auto midSize = mem.size();
  const size_t w2 = header_.write(wrapper, Exiv2::littleEndian);
  const auto afterSize = mem.size();

  EXPECT_GT(w1, 0u);
  EXPECT_GT(w2, 0u);

  // Observable behavior: each call reports how many bytes it wrote and the underlying IO grows by that.
  EXPECT_EQ(midSize, beforeSize + w1);
  EXPECT_EQ(afterSize, midSize + w2);
}

TEST_F(PentaxDngMnHeaderWriteTest_1483, WriteIsStableAcrossByteOrderParameterForReturnValue_1483) {
  // The interface takes a ByteOrder; we only assert what is observable:
  // return value is consistent for the same object and does not depend on external IO state.
  Exiv2::MemIo mem1;
  Exiv2::MemIo mem2;

  auto wLittle = MakeIoWrapper<IoWrapper>(mem1, Exiv2::littleEndian);
  auto wBig = MakeIoWrapper<IoWrapper>(mem2, Exiv2::bigEndian);

  const size_t nLittle = header_.write(wLittle, Exiv2::littleEndian);
  const size_t nBig = header_.write(wBig, Exiv2::bigEndian);

  EXPECT_GT(nLittle, 0u);
  EXPECT_GT(nBig, 0u);
  EXPECT_EQ(nLittle, nBig);

  EXPECT_EQ(mem1.size(), nLittle);
  EXPECT_EQ(mem2.size(), nBig);
}

TEST_F(PentaxDngMnHeaderWriteTest_1483, WriteOnUninitializedWrapperDoesNotCrashAndIsExceptionSafe_1483) {
  // Exceptional / error case (observable): the call may throw if wrapper is not properly configured.
  // We don't assume the specific failure mode; we only verify it is exception-safe (no UB in test)
  // and, if it succeeds, it returns a non-zero byte count.
  using IoWrapper = Exiv2::Internal::IoWrapper;

  if constexpr (std::is_default_constructible<IoWrapper>::value) {
    IoWrapper wrapper{};

    try {
      const size_t n = header_.write(wrapper, Exiv2::littleEndian);
      EXPECT_GT(n, 0u);
    } catch (...) {
      SUCCEED();
    }
  } else {
    GTEST_SKIP() << "IoWrapper is not default-constructible in this Exiv2 configuration.";
  }
}