#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mock class for TiffVisitor (to verify external interactions)
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visit, (TiffComponent& component), (override));
};

// Unit tests for TiffComponent class
class TiffComponentTest : public ::testing::Test {
protected:
    TiffComponentTest() : component(100, IfdId::ExifIFD) {}

    TiffComponent component;
};

// Test for addChild() method
TEST_F(TiffComponentTest, AddChild_325) {
    TiffComponent::SharedPtr childComponent = std::make_shared<TiffComponent>(101, IfdId::ExifIFD);
    TiffComponent* addedChild = component.addChild(childComponent);

    // Verify that addChild correctly delegates to doAddChild (black box test)
    EXPECT_EQ(addedChild->tag(), 101);  // Should have the correct tag
    EXPECT_EQ(addedChild->group(), IfdId::ExifIFD);  // Should have the correct group
}

// Test for addNext() method
TEST_F(TiffComponentTest, AddNext_326) {
    TiffComponent::UniquePtr nextComponent = std::make_unique<TiffComponent>(102, IfdId::ExifIFD);
    TiffComponent* addedNext = component.addNext(std::move(nextComponent));

    // Verify that addNext correctly delegates to doAddNext (black box test)
    EXPECT_EQ(addedNext->tag(), 102);  // Should have the correct tag
    EXPECT_EQ(addedNext->group(), IfdId::ExifIFD);  // Should have the correct group
}

// Test for accept() method with MockTiffVisitor
TEST_F(TiffComponentTest, Accept_Visit_327) {
    MockTiffVisitor visitor;
    EXPECT_CALL(visitor, visit(testing::_)).Times(1);

    // Verifying that accept() correctly interacts with the visitor
    component.accept(visitor);
}

// Test for count() method
TEST_F(TiffComponentTest, Count_328) {
    EXPECT_EQ(component.count(), 0);  // Assuming that the count starts at 0 for an empty component
}

// Test for size() method
TEST_F(TiffComponentTest, Size_329) {
    EXPECT_EQ(component.size(), 0);  // Assuming that the size starts at 0 for an empty component
}

// Test for sizeData() method
TEST_F(TiffComponentTest, SizeData_330) {
    EXPECT_EQ(component.sizeData(), 0);  // Assuming that the data size starts at 0 for an empty component
}

// Test for sizeImage() method
TEST_F(TiffComponentTest, SizeImage_331) {
    EXPECT_EQ(component.sizeImage(), 0);  // Assuming that the image size starts at 0 for an empty component
}

// Test for write() method
TEST_F(TiffComponentTest, Write_332) {
    IoWrapper ioWrapper;
    size_t imageIdx = 0;
    size_t writtenBytes = component.write(ioWrapper, ByteOrder::LittleEndian, 0, 0, 0, imageIdx);

    EXPECT_GT(writtenBytes, 0);  // Verifying that write() writes some bytes
}

// Test for clone() method
TEST_F(TiffComponentTest, Clone_333) {
    TiffComponent::UniquePtr clonedComponent = component.clone();

    EXPECT_NE(&component, clonedComponent.get());  // Ensure that the clone is a different object
    EXPECT_EQ(component.tag(), clonedComponent->tag());  // Should have the same tag
    EXPECT_EQ(component.group(), clonedComponent->group());  // Should have the same group
}

}  // namespace Internal
}  // namespace Exiv2