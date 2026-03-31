#include <gtest/gtest.h>
#include <memory>

#include "tiffcomposite_int.hpp"
#include "types.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;

class TiffMnEntryTest_329 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that addChild returns nullptr when mn_ is not set (freshly constructed TiffMnEntry)
TEST_F(TiffMnEntryTest_329, AddChildReturnsNullWhenMnNotSet_329) {
    // Construct a TiffMnEntry with some tag, group, and mnGroup
    // When mn_ is not initialized, doAddChild should return nullptr
    TiffMnEntry entry(0x0001, IfdId::ifd0Id, IfdId::canonId);

    // Create a shared_ptr to a TiffComponent to pass as child
    auto child = std::make_shared<TiffEntry>(0x0002, IfdId::ifd0Id);
    TiffComponent::SharedPtr sharedChild = child;

    TiffComponent* result = entry.addChild(std::move(sharedChild));

    EXPECT_EQ(result, nullptr);
}

// Test that addChild with nullptr shared_ptr returns nullptr when mn_ is not set
TEST_F(TiffMnEntryTest_329, AddChildWithNullSharedPtrReturnsNull_329) {
    TiffMnEntry entry(0x0001, IfdId::ifd0Id, IfdId::canonId);

    TiffComponent::SharedPtr nullChild;

    TiffComponent* result = entry.addChild(std::move(nullChild));

    EXPECT_EQ(result, nullptr);
}

// Test basic construction of TiffMnEntry
TEST_F(TiffMnEntryTest_329, ConstructorSetsTagAndGroup_329) {
    const uint16_t testTag = 0x927c;  // MakerNote tag
    const IfdId testGroup = IfdId::ifd0Id;
    const IfdId testMnGroup = IfdId::canonId;

    TiffMnEntry entry(testTag, testGroup, testMnGroup);

    EXPECT_EQ(entry.tag(), testTag);
    EXPECT_EQ(entry.group(), testGroup);
}

// Test that multiple addChild calls all return nullptr when mn_ is not set
TEST_F(TiffMnEntryTest_329, MultipleAddChildCallsReturnNull_329) {
    TiffMnEntry entry(0x927c, IfdId::ifd0Id, IfdId::nikonId);

    for (int i = 0; i < 5; ++i) {
        auto child = std::make_shared<TiffEntry>(static_cast<uint16_t>(i), IfdId::ifd0Id);
        TiffComponent* result = entry.addChild(std::move(child));
        EXPECT_EQ(result, nullptr) << "addChild should return nullptr on call " << i;
    }
}

// Test destruction doesn't crash when mn_ is not set
TEST_F(TiffMnEntryTest_329, DestructorSafeWhenMnNotSet_329) {
    auto entry = std::make_unique<TiffMnEntry>(0x0001, IfdId::ifd0Id, IfdId::canonId);
    // Just verify no crash on destruction
    EXPECT_NO_THROW(entry.reset());
}

// Test with different IfdId combinations
TEST_F(TiffMnEntryTest_329, DifferentGroupCombinations_329) {
    TiffMnEntry entry1(0x0001, IfdId::exifId, IfdId::canonId);
    EXPECT_EQ(entry1.group(), IfdId::exifId);

    auto child = std::make_shared<TiffEntry>(0x0010, IfdId::exifId);
    TiffComponent* result = entry1.addChild(std::move(child));
    EXPECT_EQ(result, nullptr);
}

// Test count and size when mn_ is not set
TEST_F(TiffMnEntryTest_329, CountAndSizeWhenMnNotSet_329) {
    TiffMnEntry entry(0x927c, IfdId::ifd0Id, IfdId::canonId);

    // These should return some default value without crashing
    EXPECT_NO_THROW(entry.count());
    EXPECT_NO_THROW(entry.size());
}
