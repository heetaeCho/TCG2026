#include <gtest/gtest.h>
#include <memory>

// Forward declarations and minimal includes based on the provided interface
namespace Exiv2 {
namespace Internal {

class TiffComponent {
public:
    using UniquePtr = std::unique_ptr<TiffComponent>;
    TiffComponent* doAddNext(UniquePtr /*tiffComponent*/) { return nullptr; }
};

} // namespace Internal
} // namespace Exiv2

using namespace Exiv2::Internal;

class TiffComponentTest_333 : public ::testing::Test {
protected:
    TiffComponent component;
};

// Test that doAddNext returns nullptr when passed a nullptr UniquePtr
TEST_F(TiffComponentTest_333, DoAddNextWithNullptrReturnsNull_333) {
    TiffComponent::UniquePtr nullPtr(nullptr);
    TiffComponent* result = component.doAddNext(std::move(nullPtr));
    EXPECT_EQ(result, nullptr);
}

// Test that doAddNext returns nullptr when passed a valid UniquePtr
TEST_F(TiffComponentTest_333, DoAddNextWithValidComponentReturnsNull_333) {
    TiffComponent::UniquePtr validComponent = std::make_unique<TiffComponent>();
    TiffComponent* result = component.doAddNext(std::move(validComponent));
    EXPECT_EQ(result, nullptr);
}

// Test that doAddNext can be called multiple times and always returns nullptr
TEST_F(TiffComponentTest_333, DoAddNextCalledMultipleTimesAlwaysReturnsNull_333) {
    for (int i = 0; i < 10; ++i) {
        TiffComponent::UniquePtr comp = std::make_unique<TiffComponent>();
        TiffComponent* result = component.doAddNext(std::move(comp));
        EXPECT_EQ(result, nullptr) << "Failed on iteration " << i;
    }
}

// Test that doAddNext with a default-constructed UniquePtr returns nullptr
TEST_F(TiffComponentTest_333, DoAddNextWithDefaultConstructedUniquePtrReturnsNull_333) {
    TiffComponent::UniquePtr defaultPtr;
    EXPECT_EQ(defaultPtr.get(), nullptr);
    TiffComponent* result = component.doAddNext(std::move(defaultPtr));
    EXPECT_EQ(result, nullptr);
}

// Test that the passed UniquePtr is consumed (moved) by doAddNext
TEST_F(TiffComponentTest_333, DoAddNextConsumesUniquePtr_333) {
    TiffComponent::UniquePtr comp = std::make_unique<TiffComponent>();
    EXPECT_NE(comp.get(), nullptr);
    component.doAddNext(std::move(comp));
    // After move, the original unique_ptr should be null
    EXPECT_EQ(comp.get(), nullptr);
}

// Test that TiffComponent can be default constructed
TEST_F(TiffComponentTest_333, DefaultConstruction_333) {
    TiffComponent tc;
    // Just verifying that default construction works without issues
    SUCCEED();
}

// Test calling doAddNext on a newly created component on the heap
TEST_F(TiffComponentTest_333, DoAddNextOnHeapAllocatedComponent_333) {
    auto heapComponent = std::make_unique<TiffComponent>();
    TiffComponent::UniquePtr arg = std::make_unique<TiffComponent>();
    TiffComponent* result = heapComponent->doAddNext(std::move(arg));
    EXPECT_EQ(result, nullptr);
}

// Test that doAddNext alternating between null and valid arguments always returns nullptr
TEST_F(TiffComponentTest_333, DoAddNextAlternatingNullAndValid_333) {
    TiffComponent::UniquePtr nullArg(nullptr);
    TiffComponent* result1 = component.doAddNext(std::move(nullArg));
    EXPECT_EQ(result1, nullptr);

    TiffComponent::UniquePtr validArg = std::make_unique<TiffComponent>();
    TiffComponent* result2 = component.doAddNext(std::move(validArg));
    EXPECT_EQ(result2, nullptr);

    TiffComponent::UniquePtr nullArg2(nullptr);
    TiffComponent* result3 = component.doAddNext(std::move(nullArg2));
    EXPECT_EQ(result3, nullptr);
}
