#include <gtest/gtest.h>
#include "crwimage_int.hpp"

namespace Exiv2 { namespace Internal {

class CiffComponentTest : public ::testing::Test {
protected:
    CiffComponentTest() = default;
    ~CiffComponentTest() override = default;
};

TEST_F(CiffComponentTest, Tag_1759) {
    // TEST_ID: 1759
    // Test the behavior of the tag() function.
    
    // Arrange
    uint16_t tag = 42;
    uint16_t dir = 10;
    CiffComponent component(tag, dir);
    
    // Act
    uint16_t result = component.tag();
    
    // Assert
    EXPECT_EQ(result, tag);
}

TEST_F(CiffComponentTest, DefaultConstructor_1760) {
    // TEST_ID: 1760
    // Test the default constructor of CiffComponent.
    
    // Arrange & Act
    CiffComponent component;
    
    // Assert
    EXPECT_EQ(component.tag(), 0);
    EXPECT_EQ(component.dir(), 0);
}

TEST_F(CiffComponentTest, AddComponent_1761) {
    // TEST_ID: 1761
    // Test adding a component using the add method.
    
    // Arrange
    uint16_t tag = 100;
    uint16_t dir = 50;
    CiffComponent component(tag, dir);
    CiffComponent::UniquePtr ptr = std::make_unique<CiffComponent>(200, 150);
    
    // Act
    const CiffComponent::UniquePtr& result = component.add(std::move(ptr));
    
    // Assert
    EXPECT_NE(result, nullptr);
    EXPECT_EQ(result->tag(), 200);
    EXPECT_EQ(result->dir(), 150);
}

TEST_F(CiffComponentTest, RemoveComponent_1762) {
    // TEST_ID: 1762
    // Test removing a component using the remove method.
    
    // Arrange
    uint16_t tag = 300;
    uint16_t dir = 100;
    CiffComponent component(tag, dir);
    CiffComponent::UniquePtr ptr = std::make_unique<CiffComponent>(400, 250);
    component.add(std::move(ptr));
    
    // Act
    // The remove method doesn't return a value, so we check the component state.
    component.remove({}, 400);
    
    // Assert
    EXPECT_EQ(component.empty(), true);
}

TEST_F(CiffComponentTest, Write_1763) {
    // TEST_ID: 1763
    // Test the write method.
    
    // Arrange
    uint16_t tag = 500;
    uint16_t dir = 200;
    CiffComponent component(tag, dir);
    Blob blob;
    size_t offset = 0;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    
    // Act
    size_t writtenSize = component.write(blob, byteOrder, offset);
    
    // Assert
    EXPECT_GT(writtenSize, 0);
}

TEST_F(CiffComponentTest, Size_1764) {
    // TEST_ID: 1764
    // Test the size() function.
    
    // Arrange
    uint16_t tag = 600;
    uint16_t dir = 300;
    CiffComponent component(tag, dir);
    
    // Act
    size_t size = component.size();
    
    // Assert
    EXPECT_EQ(size, 0);  // Assuming size is initially 0
}

TEST_F(CiffComponentTest, SetValue_1765) {
    // TEST_ID: 1765
    // Test the setValue() method.
    
    // Arrange
    uint16_t tag = 700;
    uint16_t dir = 400;
    CiffComponent component(tag, dir);
    DataBuf buf;
    
    // Act
    component.setValue(std::move(buf));
    
    // Assert
    // No direct observable effect; we could verify side effects with a mock or further method checks
    EXPECT_TRUE(component.empty());
}

TEST_F(CiffComponentTest, Decode_1766) {
    // TEST_ID: 1766
    // Test the decode method.
    
    // Arrange
    uint16_t tag = 800;
    uint16_t dir = 500;
    CiffComponent component(tag, dir);
    Image image;
    ByteOrder byteOrder = ByteOrder::bigEndian;
    
    // Act
    component.decode(image, byteOrder);
    
    // Assert
    // No return value; potentially could verify internal changes through other mechanisms
}

TEST_F(CiffComponentTest, FindComponent_1767) {
    // TEST_ID: 1767
    // Test the findComponent method.
    
    // Arrange
    uint16_t tag = 900;
    uint16_t dir = 600;
    CiffComponent component(tag, dir);
    CiffComponent* found = nullptr;
    
    // Act
    found = component.findComponent(1000, 700);
    
    // Assert
    EXPECT_EQ(found, nullptr);  // Assuming no component with crwTagId 1000 and crwDir 700
}

} } // namespace Exiv2::Internal