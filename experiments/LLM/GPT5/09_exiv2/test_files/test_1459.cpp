// =================================================================================================
// TEST_ID: 1459
// Unit tests for: Exiv2::Internal::FujiMnHeader::write(IoWrapper&, ByteOrder) const
// File under test: ./TestProjects/exiv2/src/makernote_int.cpp
// =================================================================================================

#include <gtest/gtest.h>

#include <type_traits>
#include <cstddef>

#include <exiv2/basicio.hpp>
#include <exiv2/types.hpp>
#include <exiv2/error.hpp>

// FujiMnHeader / IoWrapper are internal. In many Exiv2 setups, these live in src/*_int.hpp.
// Prefer the internal header if available; fall back to including the .cpp if that’s how the
// project exposes the symbol in this test harness.
#if __has_include("makernote_int.hpp")
#include "makernote_int.hpp"
#elif __has_include("../src/makernote_int.hpp")
#include "../src/makernote_int.hpp"
#elif __has_include("makernote_int.cpp")
#include "makernote_int.cpp"
#elif __has_include("../src/makernote_int.cpp")
#include "../src/makernote_int.cpp"
#else
#error "Cannot find makernote_int.hpp/cpp that defines Exiv2::Internal::FujiMnHeader / IoWrapper."
#endif

namespace {

using Exiv2::BasicIo;
using Exiv2::ByteOrder;

template <typename IoWrapperT>
IoWrapperT MakeIoWrapper(BasicIo& io)
{
    // IoWrapper constructor signatures vary across versions/builds. Try common forms.
    if constexpr (std::is_constructible_v<IoWrapperT, BasicIo&>) {
        return IoWrapperT(io);
    } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIo*>) {
        return IoWrapperT(&io);
    } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIo&, std::size_t>) {
        return IoWrapperT(io, 0U);
    } else if constexpr (std::is_constructible_v<IoWrapperT, BasicIo*, std::size_t>) {
        return IoWrapperT(&io, 0U);
    } else {
        static_assert(!sizeof(IoWrapperT), "Unsupported IoWrapper constructor for this build.");
    }
}

class ThrowingBasicIo final : public BasicIo {
public:
    // Make it obvious when the class is used: any write attempt fails.
    long write(const Exiv2::byte*, long) override
    {
        throw Exiv2::Error(Exiv2::kerErrorMessage, "ThrowingBasicIo: write failed");
    }

    // --- Required BasicIo interface (minimal, non-writing behavior) ---
    int open() override { return 0; }
    int close() override { return 0; }
    bool isopen() const override { return true; }

    long read(Exiv2::byte*, long) override { return 0; }
    int putb(Exiv2::byte) override { return 0; }
    int seek(long, Exiv2::BasicIo::Position) override { return 0; }
    long tell() const override { return 0; }
    long size() const override { return 0; }
    int error() const override { return 0; }
    bool eof() const override { return false; }
    std::string path() const override { return {}; }
    Exiv2::DataBuf read(long) override { return {}; }
    int mmap(bool) override { return 0; }
    Exiv2::byte* mmap() override { return nullptr; }
    void munmap() override {}
    bool isMalloced() const override { return false; }
    void populateFakeData() override {}
    BasicIo::AutoPtr temporary() const override { return BasicIo::AutoPtr(nullptr); }
    long transfer(BasicIo&) override { return 0; }
};

class FujiMnHeaderTest_1459 : public ::testing::Test {};

} // namespace

TEST_F(FujiMnHeaderTest_1459, WriteAppendsExactlyReturnedBytes_1459)
{
    Exiv2::MemIo mem;
    auto ioWrapper = MakeIoWrapper<Exiv2::Internal::IoWrapper>(mem);

    const Exiv2::Internal::FujiMnHeader header;

    const long before = mem.size();
    const std::size_t written = header.write(ioWrapper, Exiv2::littleEndian);
    const long after = mem.size();

    // Observable contract: write() returns a byte-count, and the underlying sink grows by that amount.
    ASSERT_GE(after, before);
    EXPECT_EQ(static_cast<long>(written), after - before);

    // Boundary-ish sanity: the call should be meaningful (non-zero write) for a "header write".
    // If an implementation legitimately writes 0, this expectation can be relaxed.
    EXPECT_GT(written, 0U);
}

TEST_F(FujiMnHeaderTest_1459, MultipleWritesAccumulateByReturnValue_1459)
{
    Exiv2::MemIo mem;
    auto ioWrapper = MakeIoWrapper<Exiv2::Internal::IoWrapper>(mem);

    const Exiv2::Internal::FujiMnHeader header;

    const long base = mem.size();
    const std::size_t w1 = header.write(ioWrapper, Exiv2::littleEndian);
    const long after1 = mem.size();
    const std::size_t w2 = header.write(ioWrapper, Exiv2::littleEndian);
    const long after2 = mem.size();

    EXPECT_EQ(static_cast<long>(w1), after1 - base);
    EXPECT_EQ(static_cast<long>(w2), after2 - after1);
    EXPECT_EQ(static_cast<long>(w1 + w2), after2 - base);
}

TEST_F(FujiMnHeaderTest_1459, DifferentByteOrdersDoNotChangeWrittenSize_1459)
{
    Exiv2::MemIo mem1;
    auto ioWrapper1 = MakeIoWrapper<Exiv2::Internal::IoWrapper>(mem1);

    Exiv2::MemIo mem2;
    auto ioWrapper2 = MakeIoWrapper<Exiv2::Internal::IoWrapper>(mem2);

    const Exiv2::Internal::FujiMnHeader header;

    const long b1 = mem1.size();
    const std::size_t wLE = header.write(ioWrapper1, Exiv2::littleEndian);
    const long a1 = mem1.size();

    const long b2 = mem2.size();
    const std::size_t wBE = header.write(ioWrapper2, Exiv2::bigEndian);
    const long a2 = mem2.size();

    EXPECT_EQ(static_cast<long>(wLE), a1 - b1);
    EXPECT_EQ(static_cast<long>(wBE), a2 - b2);

    // Observable behavior: return value is the count written; this should be consistent across orders
    // for a fixed header write (even if the content differs).
    EXPECT_EQ(wLE, wBE);
}

TEST_F(FujiMnHeaderTest_1459, WritePropagatesIoFailureAsException_1459)
{
    ThrowingBasicIo throwingIo;
    auto ioWrapper = MakeIoWrapper<Exiv2::Internal::IoWrapper>(throwingIo);

    const Exiv2::Internal::FujiMnHeader header;

    // If the underlying write fails, an exception is an observable error-path behavior.
    // (If your build uses a different failure signaling mechanism, adjust accordingly.)
    EXPECT_THROW(
        {
            (void)header.write(ioWrapper, Exiv2::littleEndian);
        },
        Exiv2::Error);
}