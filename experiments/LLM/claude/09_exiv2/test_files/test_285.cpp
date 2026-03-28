#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"
#include "types.hpp"

#include <memory>

using namespace Exiv2;
using namespace Exiv2::Internal;

// Concrete subclass for testing since TiffComponent has pure virtual methods
class TestTiffComponent : public TiffComponent {
public:
    TestTiffComponent(uint16_t tag, IfdId group) : TiffComponent(tag, group) {}

protected:
    TiffComponent* doClone() const override {
        return new TestTiffComponent(tag(), group());
    }

    TiffComponent* doAddPath(uint16_t /*tag*/, TiffPath& /*tiffPath*/,
                              TiffComponent* /*pRoot*/,
                              TiffComponent::UniquePtr /*object*/) override {
        return nullptr;
    }

    TiffComponent* doAddChild(TiffComponent::SharedPtr /*tiffComponent*/) override {
        return nullptr;
    }

    TiffComponent* doAddNext(TiffComponent::UniquePtr /*tiffComponent*/) override {
        return nullptr;
    }

    void doAccept(TiffVisitor& /*visitor*/) override {}

    size_t doWrite(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/,
                   size_t /*offset*/, size_t /*valueIdx*/,
                   size_t /*dataIdx*/, size_t& /*imageIdx*/) override {
        return 0;
    }

    size_t doWriteData(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/,
                       size_t /*offset*/, size_t /*dataIdx*/,
                       size_t& /*imageIdx*/) const override {
        return 0;
    }

    size_t doWriteImage(IoWrapper& /*ioWrapper*/, ByteOrder /*byteOrder*/) const override {
        return 0;
    }

    size_t doSize() const override {
        return 0;
    }

    size_t doCount() const override {
        return 0;
    }

    size_t doSizeData() const override {
        return 0;
    }

    size_t doSizeImage() const override {
        return 0;
    }
};

class TiffComponentTest_285 : public ::testing::Test {
protected:
    void SetUp() override {
        component_ = std::make_unique<TestTiffComponent>(0x0100, IfdId::ifd0Id);
    }

    std::unique_ptr<TestTiffComponent> component_;
};

// Test constructor sets tag correctly
TEST_F(TiffComponentTest_285, ConstructorSetsTag_285) {
    TestTiffComponent comp(0x0110, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0x0110);
}

// Test constructor sets group correctly
TEST_F(TiffComponentTest_285, ConstructorSetsGroup_285) {
    TestTiffComponent comp(0x0100, IfdId::ifd1Id);
    EXPECT_EQ(comp.group(), IfdId::ifd1Id);
}

// Test tag() returns correct tag value
TEST_F(TiffComponentTest_285, TagReturnsCorrectValue_285) {
    EXPECT_EQ(component_->tag(), 0x0100);
}

// Test group() returns correct group value
TEST_F(TiffComponentTest_285, GroupReturnsCorrectValue_285) {
    EXPECT_EQ(component_->group(), IfdId::ifd0Id);
}

// Test start() returns nullptr initially
TEST_F(TiffComponentTest_285, StartReturnsNullInitially_285) {
    EXPECT_EQ(component_->start(), nullptr);
}

// Test setStart and start
TEST_F(TiffComponentTest_285, SetStartAndRetrieve_285) {
    byte data[] = {0x01, 0x02, 0x03};
    component_->setStart(data);
    EXPECT_EQ(component_->start(), data);
}

// Test clone creates a copy with same tag
TEST_F(TiffComponentTest_285, ClonePreservesTag_285) {
    auto cloned = component_->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tag(), component_->tag());
}

// Test clone creates a copy with same group
TEST_F(TiffComponentTest_285, ClonePreservesGroup_285) {
    auto cloned = component_->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->group(), component_->group());
}

// Test clone returns a distinct object
TEST_F(TiffComponentTest_285, CloneReturnsDistinctObject_285) {
    auto cloned = component_->clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_NE(cloned.get(), component_.get());
}

// Test idx() returns default value
TEST_F(TiffComponentTest_285, IdxReturnsDefaultValue_285) {
    int idx = component_->idx();
    EXPECT_EQ(idx, 0);
}

// Test count() via doCount
TEST_F(TiffComponentTest_285, CountReturnsZero_285) {
    EXPECT_EQ(component_->count(), 0u);
}

// Test size() via doSize
TEST_F(TiffComponentTest_285, SizeReturnsZero_285) {
    EXPECT_EQ(component_->size(), 0u);
}

// Test sizeData() via doSizeData
TEST_F(TiffComponentTest_285, SizeDataReturnsZero_285) {
    EXPECT_EQ(component_->sizeData(), 0u);
}

// Test sizeImage() via doSizeImage
TEST_F(TiffComponentTest_285, SizeImageReturnsZero_285) {
    EXPECT_EQ(component_->sizeImage(), 0u);
}

// Test addPath returns nullptr for base implementation
TEST_F(TiffComponentTest_285, AddPathReturnsNull_285) {
    TiffPath tiffPath;
    auto obj = std::make_unique<TestTiffComponent>(0x0101, IfdId::ifd0Id);
    TiffComponent* result = component_->addPath(0x0101, tiffPath, component_.get(), std::move(obj));
    EXPECT_EQ(result, nullptr);
}

// Test addChild returns nullptr for base implementation
TEST_F(TiffComponentTest_285, AddChildReturnsNull_285) {
    auto child = std::make_shared<TestTiffComponent>(0x0102, IfdId::ifd0Id);
    TiffComponent* result = component_->addChild(child);
    EXPECT_EQ(result, nullptr);
}

// Test addNext returns nullptr for base implementation
TEST_F(TiffComponentTest_285, AddNextReturnsNull_285) {
    auto next = std::make_unique<TestTiffComponent>(0x0103, IfdId::ifd0Id);
    TiffComponent* result = component_->addNext(std::move(next));
    EXPECT_EQ(result, nullptr);
}

// Test with different tag values
TEST_F(TiffComponentTest_285, DifferentTagValues_285) {
    TestTiffComponent comp1(0x0000, IfdId::ifd0Id);
    EXPECT_EQ(comp1.tag(), 0x0000);

    TestTiffComponent comp2(0xFFFF, IfdId::ifd0Id);
    EXPECT_EQ(comp2.tag(), 0xFFFF);
}

// Test with different group values
TEST_F(TiffComponentTest_285, DifferentGroupValues_285) {
    TestTiffComponent comp1(0x0100, IfdId::exifId);
    EXPECT_EQ(comp1.group(), IfdId::exifId);

    TestTiffComponent comp2(0x0100, IfdId::gpsId);
    EXPECT_EQ(comp2.group(), IfdId::gpsId);
}

// Test setStart with nullptr
TEST_F(TiffComponentTest_285, SetStartWithNull_285) {
    component_->setStart(nullptr);
    EXPECT_EQ(component_->start(), nullptr);
}

// Test setStart can be updated
TEST_F(TiffComponentTest_285, SetStartCanBeUpdated_285) {
    byte data1[] = {0x01};
    byte data2[] = {0x02};
    component_->setStart(data1);
    EXPECT_EQ(component_->start(), data1);
    component_->setStart(data2);
    EXPECT_EQ(component_->start(), data2);
}

// Test clone of component with setStart - note clone doesn't necessarily copy pStart_
TEST_F(TiffComponentTest_285, CloneCreatesNewObject_285) {
    TestTiffComponent comp(0x0200, IfdId::ifd1Id);
    auto cloned = comp.clone();
    ASSERT_NE(cloned, nullptr);
    EXPECT_EQ(cloned->tag(), 0x0200);
    EXPECT_EQ(cloned->group(), IfdId::ifd1Id);
}

// Test boundary tag value 0
TEST_F(TiffComponentTest_285, BoundaryTagZero_285) {
    TestTiffComponent comp(0, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), 0);
}

// Test boundary tag value max uint16
TEST_F(TiffComponentTest_285, BoundaryTagMaxUint16_285) {
    TestTiffComponent comp(UINT16_MAX, IfdId::ifd0Id);
    EXPECT_EQ(comp.tag(), UINT16_MAX);
}
