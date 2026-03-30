#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"  // Include the header for CiffComponent

using namespace Exiv2::Internal;

class CiffComponentTest : public ::testing::Test {
protected:
    CiffComponent component;

    CiffComponentTest() : component(1234, 5678) {}  // Example tag and dir
};

TEST_F(CiffComponentTest, DefaultConstructor_1760) {
    // Test for the default constructor
    CiffComponent defaultComponent;
    EXPECT_EQ(defaultComponent.size(), 0);
    EXPECT_EQ(defaultComponent.offset(), 0);
    EXPECT_EQ(defaultComponent.pData(), nullptr);
}

TEST_F(CiffComponentTest, SizeMethod_1761) {
    // Test the size method
    EXPECT_EQ(component.size(), 0);  // Initially, size is 0
}

TEST_F(CiffComponentTest, SetSize_1762) {
    // Test setSize method
    component.setSize(100);
    EXPECT_EQ(component.size(), 100);
}

TEST_F(CiffComponentTest, SetOffset_1763) {
    // Test setOffset method
    component.setOffset(200);
    EXPECT_EQ(component.offset(), 200);
}

TEST_F(CiffComponentTest, AddComponent_1764) {
    // Test the add method
    CiffComponent::UniquePtr newComponent = std::make_unique<CiffComponent>(5678, 1234);
    auto result = component.add(std::move(newComponent));
    EXPECT_EQ(result->size(), 0);  // Newly added component has a default size of 0
}

TEST_F(CiffComponentTest, FindComponent_1765) {
    // Test the findComponent method
    CiffComponent::UniquePtr newComponent = std::make_unique<CiffComponent>(5678, 1234);
    component.add(std::move(newComponent));
    auto foundComponent = component.findComponent(5678, 1234);
    EXPECT_NE(foundComponent, nullptr);  // Component should be found
}

TEST_F(CiffComponentTest, RemoveComponent_1766) {
    // Test the remove method
    CiffComponent::UniquePtr newComponent = std::make_unique<CiffComponent>(5678, 1234);
    component.add(std::move(newComponent));
    component.remove(5678, 1234);
    auto foundComponent = component.findComponent(5678, 1234);
    EXPECT_EQ(foundComponent, nullptr);  // Component should be removed
}

TEST_F(CiffComponentTest, EmptyComponent_1767) {
    // Test the empty method
    EXPECT_TRUE(component.empty());  // Initially, the component is empty
    component.setSize(10);  // Set a size to make it non-empty
    EXPECT_FALSE(component.empty());  // Now it is not empty
}

TEST_F(CiffComponentTest, WriteMethod_1768) {
    // Test the write method (simulated since it interacts with Blob)
    Blob blob;
    size_t writtenSize = component.write(blob, ByteOrder::bigEndian, 0);
    EXPECT_GT(writtenSize, 0);  // Ensure some data is written
}

TEST_F(CiffComponentTest, PrintMethod_1769) {
    // Test the print method (mocking the output stream)
    testing::internal::CaptureStdout();
    component.print(std::cout, ByteOrder::bigEndian, "Prefix_");
    std::string output = testing::internal::GetCapturedStdout();
    EXPECT_THAT(output, ::testing::HasSubstr("Prefix_"));
}