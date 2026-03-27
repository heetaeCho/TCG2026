#include <gtest/gtest.h>
#include "crwimage_int.hpp"  // Include the header for CiffComponent

namespace Exiv2 {
    namespace Internal {

        // Test Fixture for CiffComponent
        class CiffComponentTest : public ::testing::Test {
        protected:
            CiffComponentTest() : ciffComponent(1, 2) {}  // TEST_ID for constructor test is 1758

            CiffComponent ciffComponent;  // CiffComponent instance for testing
        };

        // Test normal operation of the dir() function
        TEST_F(CiffComponentTest, DirReturnsCorrectValue_1758) {
            EXPECT_EQ(ciffComponent.dir(), 2);  // Check if the default dir_ value is 2
        }

        // Test boundary condition for size
        TEST_F(CiffComponentTest, SizeZeroWhenInitialized_1759) {
            EXPECT_EQ(ciffComponent.size(), 0);  // Size should be 0 initially
        }

        // Test exceptional case: Test that dir_ value is set correctly
        TEST_F(CiffComponentTest, SetDirSetsCorrectValue_1760) {
            ciffComponent.setDir(100);
            EXPECT_EQ(ciffComponent.dir(), 100);  // Verify that the setDir function works correctly
        }

        // Test boundary condition for offset
        TEST_F(CiffComponentTest, OffsetZeroWhenInitialized_1761) {
            EXPECT_EQ(ciffComponent.offset(), 0);  // Offset should be 0 initially
        }

        // Test exceptional case: Test that size can be updated correctly
        TEST_F(CiffComponentTest, SetSizeUpdatesCorrectly_1762) {
            ciffComponent.setSize(256);
            EXPECT_EQ(ciffComponent.size(), 256);  // Verify that setSize updates size correctly
        }

        // Test exceptional case: Test that offset can be updated correctly
        TEST_F(CiffComponentTest, SetOffsetUpdatesCorrectly_1763) {
            ciffComponent.setOffset(128);
            EXPECT_EQ(ciffComponent.offset(), 128);  // Verify that setOffset updates offset correctly
        }

        // Test normal operation for add method with UniquePtr component
        TEST_F(CiffComponentTest, AddUniquePtrComponent_1764) {
            CiffComponent::UniquePtr component(new CiffComponent(1, 2));
            ciffComponent.add(std::move(component));  // Test adding a component
            EXPECT_EQ(ciffComponent.empty(), false);  // Verify the component was added
        }

        // Test exceptional case for empty function
        TEST_F(CiffComponentTest, EmptyReturnsCorrectValue_1765) {
            EXPECT_TRUE(ciffComponent.empty());  // Initially, it should be empty
            CiffComponent::UniquePtr component(new CiffComponent(1, 2));
            ciffComponent.add(std::move(component));  // Add component
            EXPECT_FALSE(ciffComponent.empty());  // After adding, it should no longer be empty
        }

        // Test the behavior of the findComponent function
        TEST_F(CiffComponentTest, FindComponentReturnsNullIfNotFound_1766) {
            EXPECT_EQ(ciffComponent.findComponent(10, 20), nullptr);  // Component with those ids should not exist
        }

        // Test the behavior of the findComponent function when component exists
        TEST_F(CiffComponentTest, FindComponentReturnsCorrectComponent_1767) {
            CiffComponent::UniquePtr component(new CiffComponent(10, 20));
            ciffComponent.add(std::move(component));  // Add component
            EXPECT_NE(ciffComponent.findComponent(10, 20), nullptr);  // Should return a non-null pointer
        }

        // Test writing data using the write function
        TEST_F(CiffComponentTest, WriteFunctionWritesData_1768) {
            Blob blob;
            size_t result = ciffComponent.write(blob, ByteOrder::littleEndian, 0);
            EXPECT_GT(result, 0);  // Verify that the write function writes data
        }

        // Test exceptional case: Check for a value that cannot be added
        TEST_F(CiffComponentTest, AddThrowsForInvalidComponent_1769) {
            CiffComponent::UniquePtr invalidComponent(nullptr);
            EXPECT_THROW(ciffComponent.add(std::move(invalidComponent)), std::invalid_argument);
        }

    }  // namespace Internal
}  // namespace Exiv2