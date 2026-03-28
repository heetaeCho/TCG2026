#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "xmp.hpp"
#include "value.hpp"
#include "xmp_exiv2.hpp"

namespace Exiv2 {

class MockValue : public Value {
public:
    MOCK_METHOD(int, count, (), (const, override));
};

// Test fixture class
class XmpdatumTest : public ::testing::Test {
protected:
    XmpdatumTest() = default;
    ~XmpdatumTest() override = default;

    // Helper function to create an Xmpdatum object with a mock value
    Xmpdatum createXmpdatumWithMockValue(size_t count) {
        auto mockValue = std::make_unique<MockValue>(TypeId::kInt); // Example with TypeId::kInt
        EXPECT_CALL(*mockValue, count()).WillOnce(testing::Return(count));
        return Xmpdatum(XmpKey("mockKey"), mockValue.get());
    }
};

// Normal operation: when count is non-zero
TEST_F(XmpdatumTest, CountNonZero_1289) {
    // Setup
    Xmpdatum xmpdatum = createXmpdatumWithMockValue(5);

    // Execute and Verify
    EXPECT_EQ(xmpdatum.count(), 5);
}

// Boundary condition: when count is zero
TEST_F(XmpdatumTest, CountZero_1290) {
    // Setup
    Xmpdatum xmpdatum = createXmpdatumWithMockValue(0);

    // Execute and Verify
    EXPECT_EQ(xmpdatum.count(), 0);
}

// Exceptional case: when value is null (p_->value_ is nullptr)
TEST_F(XmpdatumTest, CountWithNullValue_1291) {
    // Create Xmpdatum with a null value
    Xmpdatum xmpdatum(XmpKey("mockKey"), nullptr);

    // Execute and Verify
    EXPECT_EQ(xmpdatum.count(), 0);
}

}  // namespace Exiv2