#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "exiv2/error.hpp"
#include "tiffcomposite_int.hpp"
#include "tiffcomponent.hpp"
#include "tiffdirectory.hpp"

namespace Exiv2 {
namespace Internal {

// Mocking the TiffComponent::SharedPtr for testing purposes
class MockTiffComponent : public TiffComponent {
public:
    MOCK_METHOD0(get, std::shared_ptr<TiffComponent>());
};

} // namespace Internal
} // namespace Exiv2

// Test suite for TiffSubIfd class
class TiffSubIfdTest : public ::testing::Test {
protected:
    // Create a TiffSubIfd instance for testing
    Exiv2::Internal::TiffSubIfd subIfd_{0x0001, 0x0002, 0x0003};
};

// Test for normal operation of doAddChild
TEST_F(TiffSubIfdTest, DoAddChild_NormalOperation_328) {
    auto tiffComponent = std::make_shared<Exiv2::Internal::MockTiffComponent>();

    // Mocking the dynamic pointer cast to TiffDirectory
    auto tiffDirectory = std::make_shared<Exiv2::Internal::TiffDirectory>();
    EXPECT_CALL(*tiffComponent, get()).WillOnce(testing::Return(tiffDirectory));

    // Test the successful addition of a child
    EXPECT_NO_THROW({
        auto result = subIfd_.doAddChild(tiffComponent);
        // Check that the child is added
        ASSERT_EQ(result, tiffDirectory.get());
    });
}

// Test for failed dynamic_pointer_cast (invalid type)
TEST_F(TiffSubIfdTest, DoAddChild_FailedCast_329) {
    auto invalidTiffComponent = std::make_shared<Exiv2::Internal::MockTiffComponent>();

    // Mocking the dynamic pointer cast to fail
    EXPECT_CALL(*invalidTiffComponent, get()).WillOnce(testing::Return(nullptr));

    // Test the exception thrown when the cast fails
    EXPECT_THROW({
        subIfd_.doAddChild(invalidTiffComponent);
    }, Exiv2::Error);
}