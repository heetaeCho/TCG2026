#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "exiv2/exiv2.hpp"

// We need to include the necessary headers for the types used
// Attempt to include what's needed based on the interface
#include <memory>
#include <cstdint>

using namespace Exiv2::Internal;

// A concrete subclass for testing since TiffComponent has pure virtual or virtual methods
class TestTiffComponent : public TiffComponent {
public:
    using TiffComponent::TiffComponent;

    // Track calls to doAddNext
    TiffComponent* lastAddedNext_ = nullptr;

protected:
    TiffComponent* doAddNext(TiffComponent::UniquePtr tiffComponent) override {
        lastAddedNext_ = tiffComponent.get();
        // Store it to keep it alive
        nextComponents_.push_back(std::move(tiffComponent));
        return lastAddedNext_;
    }

    TiffComponent* doAddChild(TiffComponent::SharedPtr tiffComponent) override {
        auto* raw = tiffComponent.get();
        childComponents_.push_back(std::move(tiffComponent));
        return raw;
    }

    void doAccept(TiffVisitor& /*visitor*/) override {}

    size_t doWrite(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                   size_t /*valueIdx*/, size_t /*dataIdx*/, size_t& /*imageIdx*/) override {
        return 0;
    }

    size_t doWriteData(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/, size_t /*offset*/,
                       size_t /*dataIdx*/, size_t& /*imageIdx*/) const override {
        return 0;
    }

    size_t doWriteImage(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/) const override {
        return 0;
    }

    size_t doSize() const override { return 0; }
    size_t doCount() const override { return 0; }
    size_t doSizeData() const override { return 0; }
    size_t doSizeImage() const override { return 0; }

private:
    std::vector<TiffComponent::UniquePtr> nextComponents_;
    std::vector<TiffComponent::SharedPtr> childComponents_;
};

class TiffComponentTest_332 : public ::testing::Test {
protected:
    void SetUp() override {
    }
};

// Test constructor initializes tag and group correctly
TEST_F(TiffComponentTest_332, ConstructorSetsTagAndGroup_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0100);
    EXPECT_EQ(component.group(), Exiv2::Internal::IfdId::ifd0Id);
}

// Test tag() returns the tag set at construction
TEST_F(TiffComponentTest_332, TagReturnsConstructedTag_332) {
    TestTiffComponent component(0x0110, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0110);
}

// Test group() returns the group set at construction
TEST_F(TiffComponentTest_332, GroupReturnsConstructedGroup_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::exifId);
    EXPECT_EQ(component.group(), Exiv2::Internal::IfdId::exifId);
}

// Test that start() initially returns nullptr
TEST_F(TiffComponentTest_332, StartInitiallyNull_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_332, SetStartUpdatesStart_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    Exiv2::byte data[10] = {0};
    component.setStart(data);
    EXPECT_EQ(component.start(), data);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_332, SetStartWithNullptr_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    component.setStart(nullptr);
    EXPECT_EQ(component.start(), nullptr);
}

// Test addNext delegates to doAddNext and returns the added component
TEST_F(TiffComponentTest_332, AddNextDelegatesToDoAddNext_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    auto nextComponent = std::make_unique<TestTiffComponent>(0x0101, Exiv2::Internal::IfdId::ifd0Id);
    auto* rawPtr = nextComponent.get();

    TiffComponent* result = component.addNext(std::move(nextComponent));
    EXPECT_EQ(result, rawPtr);
    EXPECT_EQ(component.lastAddedNext_, rawPtr);
}

// Test addNext with nullptr unique_ptr
TEST_F(TiffComponentTest_332, AddNextWithNullptr_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    TiffComponent::UniquePtr nullComponent;

    TiffComponent* result = component.addNext(std::move(nullComponent));
    EXPECT_EQ(result, nullptr);
}

// Test tag boundary: tag value 0
TEST_F(TiffComponentTest_332, TagBoundaryZero_332) {
    TestTiffComponent component(0x0000, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0x0000);
}

// Test tag boundary: max uint16_t
TEST_F(TiffComponentTest_332, TagBoundaryMaxUint16_332) {
    TestTiffComponent component(0xFFFF, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.tag(), 0xFFFF);
}

// Test idx() default return value
TEST_F(TiffComponentTest_332, IdxDefaultValue_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    // Default idx() should return 0
    EXPECT_EQ(component.idx(), 0);
}

// Test count() returns value from doCount override
TEST_F(TiffComponentTest_332, CountReturnsDoCountValue_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.count(), 0u);
}

// Test size() returns value from doSize override
TEST_F(TiffComponentTest_332, SizeReturnsDoSizeValue_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.size(), 0u);
}

// Test sizeData() returns value from doSizeData override
TEST_F(TiffComponentTest_332, SizeDataReturnsDoSizeDataValue_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.sizeData(), 0u);
}

// Test sizeImage() returns value from doSizeImage override
TEST_F(TiffComponentTest_332, SizeImageReturnsDoSizeImageValue_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(component.sizeImage(), 0u);
}

// Test that multiple addNext calls work
TEST_F(TiffComponentTest_332, MultipleAddNextCalls_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);

    auto next1 = std::make_unique<TestTiffComponent>(0x0101, Exiv2::Internal::IfdId::ifd0Id);
    auto* rawPtr1 = next1.get();
    TiffComponent* result1 = component.addNext(std::move(next1));
    EXPECT_EQ(result1, rawPtr1);

    auto next2 = std::make_unique<TestTiffComponent>(0x0102, Exiv2::Internal::IfdId::ifd0Id);
    auto* rawPtr2 = next2.get();
    TiffComponent* result2 = component.addNext(std::move(next2));
    EXPECT_EQ(result2, rawPtr2);
}

// Test setStart can be changed
TEST_F(TiffComponentTest_332, SetStartCanBeChanged_332) {
    TestTiffComponent component(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    Exiv2::byte data1[10] = {0};
    Exiv2::byte data2[10] = {1};

    component.setStart(data1);
    EXPECT_EQ(component.start(), data1);

    component.setStart(data2);
    EXPECT_EQ(component.start(), data2);
}

// Test construction with different IfdId groups
TEST_F(TiffComponentTest_332, DifferentGroups_332) {
    TestTiffComponent comp1(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    TestTiffComponent comp2(0x0100, Exiv2::Internal::IfdId::exifId);
    TestTiffComponent comp3(0x0100, Exiv2::Internal::IfdId::gpsId);

    EXPECT_EQ(comp1.group(), Exiv2::Internal::IfdId::ifd0Id);
    EXPECT_EQ(comp2.group(), Exiv2::Internal::IfdId::exifId);
    EXPECT_EQ(comp3.group(), Exiv2::Internal::IfdId::gpsId);
}

// Test destruction (virtual destructor)
TEST_F(TiffComponentTest_332, VirtualDestructorWorks_332) {
    std::unique_ptr<TiffComponent> component =
        std::make_unique<TestTiffComponent>(0x0100, Exiv2::Internal::IfdId::ifd0Id);
    // Should not crash when destroying through base pointer
    EXPECT_NO_THROW(component.reset());
}
