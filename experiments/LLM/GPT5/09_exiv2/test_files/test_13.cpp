#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <vector>
#include <list>

// Mocked version of the ContainerStorage class for testing
namespace Exiv2 { namespace Internal {
    template <typename container>
    struct MockContainerStorage {
        public:
            container& data_;
            MockContainerStorage(container& data, size_t /* begin */, size_t end) : data_(data) {}
            const auto& unsafeAt(size_t index) const { return data_.at(index); }
            auto unsafeGetIteratorAt(size_t index) { 
                assert(index <= data_.size()); 
                auto it = data_.begin(); 
                std::advance(it, index); 
                return it; 
            }
    };
}}

using namespace Exiv2::Internal;

// TEST_ID 13: Test unsafeGetIteratorAt with valid index
TEST_F(ContainerStorageTest_13, GetIteratorAtValidIndex_13) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    MockContainerStorage<std::vector<int>> container(data, 0, 5);
    
    auto it = container.unsafeGetIteratorAt(2);
    
    ASSERT_EQ(*it, 3) << "Iterator at index 2 should point to 3";
}

// TEST_ID 14: Test unsafeGetIteratorAt with boundary index
TEST_F(ContainerStorageTest_14, GetIteratorAtBoundaryIndex_14) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    MockContainerStorage<std::vector<int>> container(data, 0, 5);
    
    auto it = container.unsafeGetIteratorAt(0);
    ASSERT_EQ(*it, 1) << "Iterator at index 0 should point to 1";

    it = container.unsafeGetIteratorAt(4);
    ASSERT_EQ(*it, 5) << "Iterator at index 4 should point to 5";
}

// TEST_ID 15: Test unsafeGetIteratorAt with out-of-bounds index
TEST_F(ContainerStorageTest_15, GetIteratorAtOutOfBoundsIndex_15) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    MockContainerStorage<std::vector<int>> container(data, 0, 5);
    
    // The assert inside the method should trigger if the index is out of bounds.
    EXPECT_DEATH(container.unsafeGetIteratorAt(6), ".*");
}

// TEST_ID 16: Test unsafeAt with valid index
TEST_F(ContainerStorageTest_16, GetElementAtValidIndex_16) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    MockContainerStorage<std::vector<int>> container(data, 0, 5);
    
    ASSERT_EQ(container.unsafeAt(3), 4) << "unsafeAt should return correct element at index 3";
}

// TEST_ID 17: Test unsafeAt with out-of-bounds index
TEST_F(ContainerStorageTest_17, GetElementAtOutOfBoundsIndex_17) {
    std::vector<int> data = {1, 2, 3, 4, 5};
    MockContainerStorage<std::vector<int>> container(data, 0, 5);
    
    // The assert inside the method should trigger if the index is out of bounds.
    EXPECT_DEATH(container.unsafeAt(6), ".*");
}

// TEST_ID 18: Test behavior of unsafeGetIteratorAt for empty container
TEST_F(ContainerStorageTest_18, GetIteratorAtEmptyContainer_18) {
    std::vector<int> data = {};
    MockContainerStorage<std::vector<int>> container(data, 0, 0);
    
    // The assert inside the method should trigger if the index is out of bounds.
    EXPECT_DEATH(container.unsafeGetIteratorAt(0), ".*");
}

// TEST_ID 19: Test iterator behavior with a list container
TEST_F(ContainerStorageTest_19, GetIteratorAtWithList_19) {
    std::list<int> data = {10, 20, 30, 40};
    MockContainerStorage<std::list<int>> container(data, 0, 4);
    
    auto it = container.unsafeGetIteratorAt(2);
    ASSERT_EQ(*it, 30) << "Iterator at index 2 should point to 30";
}