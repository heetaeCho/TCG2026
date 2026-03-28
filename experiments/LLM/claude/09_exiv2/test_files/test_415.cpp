#include <gtest/gtest.h>
#include <memory>
#include <cstdint>

// Include necessary headers
#include "exiv2/tags.hpp"

// Forward declarations and includes for the internal types
namespace Exiv2 {
namespace Internal {

class TiffComponent {
public:
    using UniquePtr = std::unique_ptr<TiffComponent>;
    virtual ~TiffComponent() = default;
    virtual uint16_t tag() const = 0;
    virtual Exiv2::IfdId group() const = 0;
};

class TiffMnEntry : public TiffComponent {
public:
    TiffMnEntry(uint16_t tag, IfdId group, IfdId mnGroup);
    uint16_t tag() const override;
    IfdId group() const override;
    IfdId mnGroup() const;
private:
    uint16_t tag_;
    IfdId group_;
    IfdId mnGroup_;
};

TiffComponent::UniquePtr newTiffMnEntry(uint16_t tag, IfdId group);

} // namespace Internal
} // namespace Exiv2

// Since we need the actual implementation to link, and the partial code
// shows the factory function, we include the actual header if available.
// For testing purposes, we rely on the declared interface.

// If the above forward declarations cause issues, use the actual project headers:
// #include "tiffcomposite_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class NewTiffMnEntryTest_415 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
};

// Test that newTiffMnEntry returns a non-null unique pointer
TEST_F(NewTiffMnEntryTest_415, ReturnsNonNull_415) {
    auto result = newTiffMnEntry(0x0001, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
}

// Test that the returned component has the correct tag
TEST_F(NewTiffMnEntryTest_415, CorrectTag_415) {
    uint16_t expectedTag = 0x927C; // Common MakerNote tag
    auto result = newTiffMnEntry(expectedTag, IfdId::exifId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), expectedTag);
}

// Test that the returned component has the correct group
TEST_F(NewTiffMnEntryTest_415, CorrectGroup_415) {
    auto result = newTiffMnEntry(0x0001, IfdId::exifId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::exifId);
}

// Test with tag value of 0
TEST_F(NewTiffMnEntryTest_415, ZeroTag_415) {
    auto result = newTiffMnEntry(0x0000, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0000);
}

// Test with maximum tag value
TEST_F(NewTiffMnEntryTest_415, MaxTag_415) {
    auto result = newTiffMnEntry(0xFFFF, IfdId::ifd0Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0xFFFF);
}

// Test with ifdIdNotSet group
TEST_F(NewTiffMnEntryTest_415, IfdIdNotSetGroup_415) {
    auto result = newTiffMnEntry(0x0001, IfdId::ifdIdNotSet);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::ifdIdNotSet);
}

// Test with various IFD groups
TEST_F(NewTiffMnEntryTest_415, GpsGroup_415) {
    auto result = newTiffMnEntry(0x0001, IfdId::gpsId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::gpsId);
}

// Test with mnId group
TEST_F(NewTiffMnEntryTest_415, MnIdGroup_415) {
    auto result = newTiffMnEntry(0x0010, IfdId::mnId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::mnId);
}

// Test with canonId group
TEST_F(NewTiffMnEntryTest_415, CanonIdGroup_415) {
    auto result = newTiffMnEntry(0x0001, IfdId::canonId);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::canonId);
    EXPECT_EQ(result->tag(), 0x0001);
}

// Test with nikon3Id group
TEST_F(NewTiffMnEntryTest_415, Nikon3IdGroup_415) {
    auto result = newTiffMnEntry(0x0002, IfdId::nikon3Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->group(), IfdId::nikon3Id);
    EXPECT_EQ(result->tag(), 0x0002);
}

// Test that multiple calls create independent objects
TEST_F(NewTiffMnEntryTest_415, MultipleCallsCreateIndependentObjects_415) {
    auto result1 = newTiffMnEntry(0x0001, IfdId::ifd0Id);
    auto result2 = newTiffMnEntry(0x0002, IfdId::exifId);
    ASSERT_NE(result1, nullptr);
    ASSERT_NE(result2, nullptr);
    EXPECT_NE(result1.get(), result2.get());
    EXPECT_EQ(result1->tag(), 0x0001);
    EXPECT_EQ(result2->tag(), 0x0002);
    EXPECT_EQ(result1->group(), IfdId::ifd0Id);
    EXPECT_EQ(result2->group(), IfdId::exifId);
}

// Test with sony1Id group
TEST_F(NewTiffMnEntryTest_415, Sony1IdGroup_415) {
    auto result = newTiffMnEntry(0x1234, IfdId::sony1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x1234);
    EXPECT_EQ(result->group(), IfdId::sony1Id);
}

// Test with ifd1Id group
TEST_F(NewTiffMnEntryTest_415, Ifd1Group_415) {
    auto result = newTiffMnEntry(0x0100, IfdId::ifd1Id);
    ASSERT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 0x0100);
    EXPECT_EQ(result->group(), IfdId::ifd1Id);
}

// Test the TiffMnEntry has mnGroup set to mnId (if accessible through the interface)
TEST_F(NewTiffMnEntryTest_415, MnGroupIsMnId_415) {
    auto result = newTiffMnEntry(0x927C, IfdId::exifId);
    ASSERT_NE(result, nullptr);
    // Dynamic cast to TiffMnEntry to check mnGroup if the interface exposes it
    auto* mnEntry = dynamic_cast<TiffMnEntry*>(result.get());
    if (mnEntry != nullptr) {
        EXPECT_EQ(mnEntry->mnGroup(), IfdId::mnId);
    }
}
