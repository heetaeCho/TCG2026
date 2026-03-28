#include <gtest/gtest.h>
#include "tiffcomposite_int.hpp"  // Include the header file for TiffComponent

namespace Exiv2 { namespace Internal {

// Test Fixture for TiffComponent
class TiffComponentTest : public ::testing::Test {
protected:
    uint16_t tag = 123;
    IfdId group = 0;
    TiffComponent tiffComponent{tag, group};
};

// Normal operation: Test for the tag() method
TEST_F(TiffComponentTest, Tag_ReturnsCorrectTag_229) {
    EXPECT_EQ(tiffComponent.tag(), tag);
}

// Normal operation: Test for the group() method
TEST_F(TiffComponentTest, Group_ReturnsCorrectGroup_230) {
    EXPECT_EQ(tiffComponent.group(), group);
}

// Boundary condition: Test for the idx() method
TEST_F(TiffComponentTest, Idx_ReturnsValidIdx_231) {
    EXPECT_GE(tiffComponent.idx(), 0); // idx should not be negative
}

// Normal operation: Test for the count() method
TEST_F(TiffComponentTest, Count_ReturnsPositiveValue_232) {
    EXPECT_GT(tiffComponent.count(), 0); // count should return a positive value
}

// Exceptional case: Test if addChild() adds a valid child component
TEST_F(TiffComponentTest, AddChild_AddsValidChild_233) {
    auto child = std::make_shared<TiffComponent>(100, 0);
    TiffComponent* result = tiffComponent.addChild(child);

    EXPECT_NE(result, nullptr); // Ensure the child is added successfully
}

// Boundary condition: Test for the size() method when no components are added
TEST_F(TiffComponentTest, Size_ZeroWhenNoChildren_234) {
    EXPECT_EQ(tiffComponent.size(), 0); // Size should be zero if no components are added
}

// Exceptional case: Test for the clone() method
TEST_F(TiffComponentTest, Clone_ReturnsValidClone_235) {
    const auto clone = tiffComponent.clone();
    EXPECT_NE(clone, nullptr);  // Ensure that the clone is not null
}

// Normal operation: Test for addNext() method
TEST_F(TiffComponentTest, AddNext_AddsNextComponent_236) {
    auto next = std::make_unique<TiffComponent>(200, 1);
    TiffComponent* result = tiffComponent.addNext(std::move(next));

    EXPECT_NE(result, nullptr); // Ensure the next component is added successfully
}

// Boundary condition: Test for writeData() method with edge case
TEST_F(TiffComponentTest, WriteData_EdgeCase_237) {
    IoWrapper ioWrapper;
    size_t imageIdx = 0;
    size_t result = tiffComponent.writeData(ioWrapper, ByteOrder::LittleEndian, 0, 0, imageIdx);

    EXPECT_GT(result, 0);  // Ensure writeData returns a positive size
}

// Exceptional case: Test for writeImage() method when data is not present
TEST_F(TiffComponentTest, WriteImage_NoData_238) {
    IoWrapper ioWrapper;
    size_t result = tiffComponent.writeImage(ioWrapper, ByteOrder::LittleEndian);

    EXPECT_EQ(result, 0);  // If no data is present, it should return 0
}

// Test the destructor behavior by ensuring no memory leaks
TEST_F(TiffComponentTest, Destructor_CleansUpMemory_239) {
    TiffComponent* temp = new TiffComponent(tag, group);
    delete temp;  // Ensure that the destructor is called without memory leaks
}

} } // namespace Exiv2::Internal