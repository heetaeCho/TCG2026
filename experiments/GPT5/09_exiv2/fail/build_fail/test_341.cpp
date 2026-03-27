#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "tiffcomposite_int.hpp"
#include "tiffvisitor_int.hpp"

namespace Exiv2 {
namespace Internal {

class TiffVisitorMock : public TiffVisitor {
public:
    MOCK_METHOD(void, visitSizeEntry, (TiffSizeEntry* object), (override));
};

// Test Fixture for TiffSizeEntry
class TiffSizeEntryTest : public ::testing::Test {
protected:
    uint16_t tag = 10;
    IfdId group = 1;
    uint16_t dtTag = 20;
    IfdId dtGroup = 2;

    TiffSizeEntry sizeEntry;

    TiffSizeEntryTest() : sizeEntry(tag, group, dtTag, dtGroup) {}
};

// Test normal operation: verify doAccept calls visitSizeEntry on the visitor
TEST_F(TiffSizeEntryTest, DoAcceptCallsVisitSizeEntry) {
    TiffVisitorMock mockVisitor;

    EXPECT_CALL(mockVisitor, visitSizeEntry(&sizeEntry))
        .Times(1);

    sizeEntry.doAccept(mockVisitor);
}

// Test boundary conditions: initializing with minimum and maximum values
TEST_F(TiffSizeEntryTest, ConstructorMinMaxValues) {
    uint16_t minTag = 0;
    uint16_t maxTag = 65535;
    IfdId minGroup = 0;
    IfdId maxGroup = 65535;

    TiffSizeEntry minEntry(minTag, minGroup, minTag, minGroup);
    TiffSizeEntry maxEntry(maxTag, maxGroup, maxTag, maxGroup);

    ASSERT_EQ(minEntry.dtTag(), minTag);
    ASSERT_EQ(minEntry.dtGroup(), minGroup);
    ASSERT_EQ(maxEntry.dtTag(), maxTag);
    ASSERT_EQ(maxEntry.dtGroup(), maxGroup);
}

// Test boundary condition: handling zero dtTag and dtGroup values
TEST_F(TiffSizeEntryTest, ConstructorZeroValues) {
    uint16_t zeroTag = 0;
    IfdId zeroGroup = 0;

    TiffSizeEntry zeroEntry(zeroTag, zeroGroup, zeroTag, zeroGroup);

    ASSERT_EQ(zeroEntry.dtTag(), zeroTag);
    ASSERT_EQ(zeroEntry.dtGroup(), zeroGroup);
}

// Test exceptional case: invalid values for dtTag and dtGroup
// (assuming exceptions are thrown or return values change based on invalid input)
// Note: This is a placeholder for actual exception handling if applicable.
TEST_F(TiffSizeEntryTest, ConstructorThrowsOnInvalidValues) {
    uint16_t invalidTag = 70000; // Exceeds uint16_t max
    IfdId invalidGroup = 70000;  // Exceeds IfdId max

    EXPECT_THROW({
        TiffSizeEntry invalidEntry(invalidTag, invalidGroup, invalidTag, invalidGroup);
    }, std::out_of_range);
}

}  // namespace Internal
}  // namespace Exiv2