// SPDX-License-Identifier: GPL-2.0-or-later
// File: test_psdimage_newPsdInstance_1188.cpp

#include <gtest/gtest.h>

#include <cstdint>
#include <memory>
#include <vector>

#include <exiv2/basicio.hpp>
#include <exiv2/image.hpp>
#include <exiv2/psdimage.hpp>

namespace {

// Build a minimal (but structurally plausible) PSD byte stream.
// This is intentionally tiny: 1x1, 1 channel, 8-bit, RGB mode, no optional sections, raw image data.
std::vector<Exiv2::byte> makeMinimalPsd1x1()
{
    std::vector<Exiv2::byte> b;

    auto pushU16BE = [&](uint16_t v) {
        b.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
        b.push_back(static_cast<Exiv2::byte>(v & 0xFF));
    };
    auto pushU32BE = [&](uint32_t v) {
        b.push_back(static_cast<Exiv2::byte>((v >> 24) & 0xFF));
        b.push_back(static_cast<Exiv2::byte>((v >> 16) & 0xFF));
        b.push_back(static_cast<Exiv2::byte>((v >> 8) & 0xFF));
        b.push_back(static_cast<Exiv2::byte>(v & 0xFF));
    };

    // Signature "8BPS"
    b.push_back(static_cast<Exiv2::byte>('8'));
    b.push_back(static_cast<Exiv2::byte>('B'));
    b.push_back(static_cast<Exiv2::byte>('P'));
    b.push_back(static_cast<Exiv2::byte>('S'));

    // Version = 1
    pushU16BE(1);

    // Reserved (6 bytes) = 0
    for (int i = 0; i < 6; ++i) b.push_back(0);

    // Channels = 1
    pushU16BE(1);

    // Height = 1, Width = 1
    pushU32BE(1);
    pushU32BE(1);

    // Depth = 8
    pushU16BE(8);

    // Color mode = 3 (RGB)
    pushU16BE(3);

    // Color mode data section length = 0
    pushU32BE(0);

    // Image resources section length = 0
    pushU32BE(0);

    // Layer and mask info section length = 0
    pushU32BE(0);

    // Image data:
    // Compression = 0 (raw)
    pushU16BE(0);

    // Raw pixel data: channels * height * width bytes = 1
    b.push_back(0x00);

    return b;
}

std::vector<Exiv2::byte> makeInvalidSignaturePsdLike()
{
    auto b = makeMinimalPsd1x1();
    // Break the signature.
    b[0] = static_cast<Exiv2::byte>('X');
    return b;
}

} // namespace

class PsdInstanceTest_1188 : public ::testing::Test {
protected:
    static Exiv2::BasicIo::UniquePtr makeMemIo(const std::vector<Exiv2::byte>& bytes)
    {
        // MemIo is part of Exiv2's public BasicIo implementations.
        // Use the buffer constructor so the image can read from it.
        return std::make_unique<Exiv2::MemIo>(bytes.data(), static_cast<long>(bytes.size()));
    }
};

TEST_F(PsdInstanceTest_1188, ReturnsNonNullForMinimalValidPsd_1188)
{
    const auto psd = makeMinimalPsd1x1();
    auto io = makeMemIo(psd);

    Exiv2::Image::UniquePtr img = Exiv2::newPsdInstance(std::move(io), /*create=*/false);

    ASSERT_NE(img, nullptr);
}

TEST_F(PsdInstanceTest_1188, ReturnsNullptrForEmptyData_1188)
{
    const std::vector<Exiv2::byte> empty;
    auto io = makeMemIo(empty);

    Exiv2::Image::UniquePtr img = Exiv2::newPsdInstance(std::move(io), /*create=*/false);

    ASSERT_EQ(img, nullptr);
}

TEST_F(PsdInstanceTest_1188, ReturnsNullptrForInvalidSignature_1188)
{
    const auto bad = makeInvalidSignaturePsdLike();
    auto io = makeMemIo(bad);

    Exiv2::Image::UniquePtr img = Exiv2::newPsdInstance(std::move(io), /*create=*/false);

    ASSERT_EQ(img, nullptr);
}

TEST_F(PsdInstanceTest_1188, CreateFlagDoesNotChangeOutcomeForSameInput_1188)
{
    const auto psd = makeMinimalPsd1x1();

    auto io1 = makeMemIo(psd);
    auto io2 = makeMemIo(psd);

    Exiv2::Image::UniquePtr imgCreateFalse = Exiv2::newPsdInstance(std::move(io1), /*create=*/false);
    Exiv2::Image::UniquePtr imgCreateTrue  = Exiv2::newPsdInstance(std::move(io2), /*create=*/true);

    // Observable contract from the snippet: the flag is unused (commented /*create*/).
    ASSERT_NE(imgCreateFalse, nullptr);
    ASSERT_NE(imgCreateTrue, nullptr);
}

TEST_F(PsdInstanceTest_1188, ReturnsNullptrForTruncatedHeader_1188)
{
    // Provide fewer bytes than required to even hold a PSD signature + version.
    const std::vector<Exiv2::byte> truncated = {
        static_cast<Exiv2::byte>('8'),
        static_cast<Exiv2::byte>('B'),
        static_cast<Exiv2::byte>('P')
    };
    auto io = makeMemIo(truncated);

    Exiv2::Image::UniquePtr img = Exiv2::newPsdInstance(std::move(io), /*create=*/false);

    ASSERT_EQ(img, nullptr);
}