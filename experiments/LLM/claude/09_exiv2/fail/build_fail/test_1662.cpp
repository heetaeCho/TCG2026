#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "exiv2/exiv2.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "tiffimage_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;
using ::testing::NiceMock;

namespace {

// A concrete TiffEntry for testing purposes
class TestTiffEntry : public TiffEntry {
public:
    TestTiffEntry(uint16_t tag, IfdId group)
        : TiffEntry(tag, group) {}
};

// Helper to create a FindDecoderFct that returns nullptr (no decoder found)
DecoderFct nullDecoderFct(const std::string&, uint16_t, IfdId) {
    return nullptr;
}

// Track whether a custom decoder was called
static bool g_customDecoderCalled = false;
static const TiffEntryBase* g_lastDecodedObject = nullptr;

// A custom decoder function that records it was called
void customDecoderForTest(TiffDecoder& /*decoder*/, const TiffEntryBase* object) {
    g_customDecoderCalled = true;
    g_lastDecodedObject = object;
}

// FindDecoderFct that returns our custom decoder
DecoderFct findCustomDecoder(const std::string&, uint16_t, IfdId) {
    return &customDecoderForTest;
}

// FindDecoderFct that returns custom decoder only for a specific tag
DecoderFct findConditionalDecoder(const std::string&, uint16_t tag, IfdId) {
    if (tag == 0x0100) {
        return &customDecoderForTest;
    }
    return nullptr;
}

class TiffDecoderTest_1662 : public ::testing::Test {
protected:
    void SetUp() override {
        g_customDecoderCalled = false;
        g_lastDecodedObject = nullptr;
    }

    void TearDown() override {
        g_customDecoderCalled = false;
        g_lastDecodedObject = nullptr;
    }

    ExifData exifData_;
    IptcData iptcData_;
    XmpData xmpData_;
};

// Test: decodeTiffEntry with null pValue returns early without calling decoder
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryNullValueReturnsEarly_1662) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    // entry has no value set, so pValue() should be nullptr

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findCustomDecoder);
    decoder.decodeTiffEntry(&entry);

    EXPECT_FALSE(g_customDecoderCalled);
}

// Test: decodeTiffEntry with valid pValue and decoder found invokes decoder
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryWithValueInvokesDecoder_1662) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);
    
    // Set a value on the entry so pValue() is not null
    auto value = std::make_unique<Exiv2::UShortValue>();
    value->value_.push_back(42);
    entry.setValue(std::move(value));

    ASSERT_NE(entry.pValue(), nullptr);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findCustomDecoder);
    decoder.decodeTiffEntry(&entry);

    EXPECT_TRUE(g_customDecoderCalled);
    EXPECT_EQ(g_lastDecodedObject, &entry);
}

// Test: decodeTiffEntry with valid pValue but no decoder found (findDecoderFct returns nullptr)
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryNoDecoderFound_1662) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);

    auto value = std::make_unique<Exiv2::UShortValue>();
    value->value_.push_back(1);
    entry.setValue(std::move(value));

    ASSERT_NE(entry.pValue(), nullptr);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullDecoderFct);
    decoder.decodeTiffEntry(&entry);

    EXPECT_FALSE(g_customDecoderCalled);
}

// Test: decodeTiffEntry with conditional decoder - matching tag
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryConditionalDecoderMatchingTag_1662) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);  // tag 0x0100 matches

    auto value = std::make_unique<Exiv2::UShortValue>();
    value->value_.push_back(100);
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findConditionalDecoder);
    decoder.decodeTiffEntry(&entry);

    EXPECT_TRUE(g_customDecoderCalled);
    EXPECT_EQ(g_lastDecodedObject, &entry);
}

// Test: decodeTiffEntry with conditional decoder - non-matching tag
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryConditionalDecoderNonMatchingTag_1662) {
    TiffEntry entry(0x0200, IfdId::ifd0Id);  // tag 0x0200 does not match

    auto value = std::make_unique<Exiv2::UShortValue>();
    value->value_.push_back(200);
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findConditionalDecoder);
    decoder.decodeTiffEntry(&entry);

    EXPECT_FALSE(g_customDecoderCalled);
}

// Test: decodeTiffEntry passes correct object to decoder
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryPassesCorrectObject_1662) {
    TiffEntry entry1(0x0100, IfdId::ifd0Id);
    TiffEntry entry2(0x0101, IfdId::ifd0Id);

    auto value1 = std::make_unique<Exiv2::UShortValue>();
    value1->value_.push_back(1);
    entry1.setValue(std::move(value1));

    auto value2 = std::make_unique<Exiv2::UShortValue>();
    value2->value_.push_back(2);
    entry2.setValue(std::move(value2));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findCustomDecoder);

    decoder.decodeTiffEntry(&entry1);
    EXPECT_TRUE(g_customDecoderCalled);
    EXPECT_EQ(g_lastDecodedObject, &entry1);

    g_customDecoderCalled = false;
    g_lastDecodedObject = nullptr;

    decoder.decodeTiffEntry(&entry2);
    EXPECT_TRUE(g_customDecoderCalled);
    EXPECT_EQ(g_lastDecodedObject, &entry2);
}

// Test: decodeTiffEntry with different groups
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryDifferentGroup_1662) {
    TiffEntry entry(0x0100, IfdId::exifId);

    auto value = std::make_unique<Exiv2::UShortValue>();
    value->value_.push_back(50);
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findCustomDecoder);
    decoder.decodeTiffEntry(&entry);

    EXPECT_TRUE(g_customDecoderCalled);
}

// Test: Multiple sequential calls to decodeTiffEntry
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryMultipleCalls_1662) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);

    auto value = std::make_unique<Exiv2::UShortValue>();
    value->value_.push_back(10);
    entry.setValue(std::move(value));

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, findCustomDecoder);

    // First call
    decoder.decodeTiffEntry(&entry);
    EXPECT_TRUE(g_customDecoderCalled);

    // Reset and call again
    g_customDecoderCalled = false;
    decoder.decodeTiffEntry(&entry);
    EXPECT_TRUE(g_customDecoderCalled);
}

// Test: Entry with value set then decoder returning null - no crash
TEST_F(TiffDecoderTest_1662, DecodeTiffEntryWithValueButNullDecoder_1662) {
    TiffEntry entry(0x0100, IfdId::ifd0Id);

    auto value = std::make_unique<Exiv2::AsciiValue>();
    value->read("TestString");
    entry.setValue(std::move(value));

    ASSERT_NE(entry.pValue(), nullptr);

    TiffDecoder decoder(exifData_, iptcData_, xmpData_, nullptr, nullDecoderFct);
    
    // Should not crash or throw
    EXPECT_NO_THROW(decoder.decodeTiffEntry(&entry));
    EXPECT_FALSE(g_customDecoderCalled);
}

}  // namespace
