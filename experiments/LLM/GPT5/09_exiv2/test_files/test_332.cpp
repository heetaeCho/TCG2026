#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"  // Assuming the header is available in the project

namespace Exiv2 {
namespace Internal {

// Mock class for testing external dependencies
class MockTiffVisitor : public TiffVisitor {
public:
    MOCK_METHOD(void, visit, (TiffComponent& component), (override));
};

// Test fixture for TiffComponent
class TiffComponentTest_332 : public ::testing::Test {
protected:
    TiffComponentTest_332() : component(1, IfdId::TIFF_IFD0) {}

    TiffComponent component;  // Test instance of TiffComponent
};

// Test: addNext method adds a new component correctly
TEST_F(TiffComponentTest_332, AddNext_AddsComponentSuccessfully_332) {
    // Arrange
    auto newComponent = std::make_unique<TiffComponent>(2, IfdId::TIFF_IFD1);

    // Act
    TiffComponent* result = component.addNext(std::move(newComponent));

    // Assert
    ASSERT_EQ(result->tag(), 2);
    ASSERT_EQ(result->group(), IfdId::TIFF_IFD1);
}

// Test: addNext method handles null pointer scenario
TEST_F(TiffComponentTest_332, AddNext_NullPointer_332) {
    // Arrange
    std::unique_ptr<TiffComponent> nullComponent = nullptr;

    // Act & Assert
    ASSERT_THROW(component.addNext(std::move(nullComponent)), std::invalid_argument);
}

// Test: addChild method adds a child component successfully
TEST_F(TiffComponentTest_332, AddChild_AddsChildSuccessfully_332) {
    // Arrange
    auto childComponent = std::make_shared<TiffComponent>(3, IfdId::TIFF_IFD2);

    // Act
    TiffComponent* result = component.addChild(childComponent);

    // Assert
    ASSERT_EQ(result->tag(), 3);
    ASSERT_EQ(result->group(), IfdId::TIFF_IFD2);
}

// Test: addChild method handles null shared pointer scenario
TEST_F(TiffComponentTest_332, AddChild_NullSharedPointer_332) {
    // Arrange
    std::shared_ptr<TiffComponent> nullChild = nullptr;

    // Act & Assert
    ASSERT_THROW(component.addChild(nullChild), std::invalid_argument);
}

// Test: accept method correctly calls visit on a visitor
TEST_F(TiffComponentTest_332, Accept_CallsVisitorVisit_332) {
    // Arrange
    MockTiffVisitor mockVisitor;
    EXPECT_CALL(mockVisitor, visit(::testing::_)).Times(1);

    // Act
    component.accept(mockVisitor);
}

// Test: write method returns a non-zero size on successful write
TEST_F(TiffComponentTest_332, Write_ReturnsValidSize_332) {
    // Arrange
    IoWrapper mockIoWrapper;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    size_t offset = 0;
    size_t valueIdx = 0;
    size_t dataIdx = 0;
    size_t imageIdx = 0;

    // Act
    size_t writtenSize = component.write(mockIoWrapper, byteOrder, offset, valueIdx, dataIdx, imageIdx);

    // Assert
    ASSERT_GT(writtenSize, 0);
}

// Test: count method returns correct number of components
TEST_F(TiffComponentTest_332, Count_ReturnsCorrectCount_332) {
    // Arrange
    auto childComponent = std::make_shared<TiffComponent>(4, IfdId::TIFF_IFD3);
    component.addChild(childComponent);

    // Act
    size_t count = component.count();

    // Assert
    ASSERT_EQ(count, 1);  // There is 1 child component added
}

// Test: idx method returns a valid index
TEST_F(TiffComponentTest_332, Index_ReturnsValidIndex_332) {
    // Act
    int index = component.idx();

    // Assert
    ASSERT_GE(index, 0);  // Index should not be negative
}

// Test: clone method correctly clones the TiffComponent
TEST_F(TiffComponentTest_332, Clone_ReturnsClonedComponent_332) {
    // Act
    TiffComponent::UniquePtr clonedComponent = component.clone();

    // Assert
    ASSERT_NE(clonedComponent.get(), &component);  // Cloned component should be a different object
    ASSERT_EQ(clonedComponent->tag(), component.tag());
    ASSERT_EQ(clonedComponent->group(), component.group());
}

}  // namespace Internal
}  // namespace Exiv2