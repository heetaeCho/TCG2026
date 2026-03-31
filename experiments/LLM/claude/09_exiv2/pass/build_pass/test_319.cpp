#include <gtest/gtest.h>
#include <cstdint>
#include <vector>

// Forward declarations and minimal type definitions needed for testing
namespace Exiv2 {
namespace Internal {

// Minimal TiffPath definition for testing purposes
class TiffPath {
public:
    TiffPath() = default;
};

class TiffComponent {
public:
    using UniquePtr = std::unique_ptr<TiffComponent>;

    TiffComponent() = default;
    virtual ~TiffComponent() = default;

    TiffComponent* doAddPath(uint16_t tag, TiffPath& tiffPath, TiffComponent* pRoot, TiffComponent::UniquePtr object) {
        return this;
    }
};

}  // namespace Internal
}  // namespace Exiv2

using namespace Exiv2::Internal;

class TiffComponentTest_319 : public ::testing::Test {
protected:
    void SetUp() override {
        component_ = std::make_unique<TiffComponent>();
    }

    std::unique_ptr<TiffComponent> component_;
};

// Test that doAddPath returns 'this' pointer (the component itself)
TEST_F(TiffComponentTest_319, DoAddPathReturnsThis_319) {
    TiffPath path;
    TiffComponent* root = component_.get();
    TiffComponent::UniquePtr object = nullptr;

    TiffComponent* result = component_->doAddPath(0, path, root, std::move(object));

    EXPECT_EQ(result, component_.get());
}

// Test with tag value of 0
TEST_F(TiffComponentTest_319, DoAddPathWithZeroTag_319) {
    TiffPath path;
    TiffComponent::UniquePtr object = nullptr;

    TiffComponent* result = component_->doAddPath(0, path, nullptr, std::move(object));

    EXPECT_EQ(result, component_.get());
}

// Test with maximum uint16_t tag value
TEST_F(TiffComponentTest_319, DoAddPathWithMaxTag_319) {
    TiffPath path;
    TiffComponent::UniquePtr object = nullptr;

    TiffComponent* result = component_->doAddPath(UINT16_MAX, path, nullptr, std::move(object));

    EXPECT_EQ(result, component_.get());
}

// Test with nullptr root
TEST_F(TiffComponentTest_319, DoAddPathWithNullRoot_319) {
    TiffPath path;
    TiffComponent::UniquePtr object = nullptr;

    TiffComponent* result = component_->doAddPath(100, path, nullptr, std::move(object));

    EXPECT_EQ(result, component_.get());
}

// Test with a non-null object UniquePtr
TEST_F(TiffComponentTest_319, DoAddPathWithNonNullObject_319) {
    TiffPath path;
    TiffComponent::UniquePtr object = std::make_unique<TiffComponent>();

    TiffComponent* result = component_->doAddPath(42, path, component_.get(), std::move(object));

    EXPECT_EQ(result, component_.get());
}

// Test with a different root pointer
TEST_F(TiffComponentTest_319, DoAddPathWithDifferentRoot_319) {
    TiffPath path;
    TiffComponent otherComponent;
    TiffComponent::UniquePtr object = nullptr;

    TiffComponent* result = component_->doAddPath(1, path, &otherComponent, std::move(object));

    EXPECT_EQ(result, component_.get());
    EXPECT_NE(result, &otherComponent);
}

// Test multiple calls return the same pointer
TEST_F(TiffComponentTest_319, DoAddPathMultipleCallsReturnSame_319) {
    TiffPath path;

    TiffComponent* result1 = component_->doAddPath(1, path, nullptr, nullptr);
    TiffComponent* result2 = component_->doAddPath(2, path, nullptr, nullptr);
    TiffComponent* result3 = component_->doAddPath(UINT16_MAX, path, component_.get(), nullptr);

    EXPECT_EQ(result1, component_.get());
    EXPECT_EQ(result2, component_.get());
    EXPECT_EQ(result3, component_.get());
    EXPECT_EQ(result1, result2);
    EXPECT_EQ(result2, result3);
}

// Test that the returned pointer is not null
TEST_F(TiffComponentTest_319, DoAddPathReturnsNonNull_319) {
    TiffPath path;

    TiffComponent* result = component_->doAddPath(0, path, nullptr, nullptr);

    EXPECT_NE(result, nullptr);
}

// Test with various boundary tag values
TEST_F(TiffComponentTest_319, DoAddPathBoundaryTagValues_319) {
    TiffPath path;

    EXPECT_EQ(component_->doAddPath(0, path, nullptr, nullptr), component_.get());
    EXPECT_EQ(component_->doAddPath(1, path, nullptr, nullptr), component_.get());
    EXPECT_EQ(component_->doAddPath(255, path, nullptr, nullptr), component_.get());
    EXPECT_EQ(component_->doAddPath(256, path, nullptr, nullptr), component_.get());
    EXPECT_EQ(component_->doAddPath(32767, path, nullptr, nullptr), component_.get());
    EXPECT_EQ(component_->doAddPath(65534, path, nullptr, nullptr), component_.get());
    EXPECT_EQ(component_->doAddPath(65535, path, nullptr, nullptr), component_.get());
}

// Test that root being same as component still returns this
TEST_F(TiffComponentTest_319, DoAddPathRootIsSelf_319) {
    TiffPath path;

    TiffComponent* result = component_->doAddPath(10, path, component_.get(), nullptr);

    EXPECT_EQ(result, component_.get());
}
