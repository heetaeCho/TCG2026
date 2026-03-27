#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"

namespace Exiv2 {
namespace Internal {

class CiffComponentTest : public ::testing::Test {
protected:
    // Test Fixture
    CiffComponentTest() : component(0, 0) {}

    CiffComponent component;
};

// Test for the empty() method (Normal operation)
TEST_F(CiffComponentTest, Empty_1794) {
    EXPECT_TRUE(component.empty());
}

// Test for the empty() method (Boundary condition: empty state)
TEST_F(CiffComponentTest, NotEmpty_1795) {
    // Simulate the component being not empty by mocking the doEmpty method
    EXPECT_CALL(component, doEmpty())
        .WillOnce(testing::Return(false));
    
    EXPECT_FALSE(component.empty());
}

// Test for the add() method (Normal operation)
TEST_F(CiffComponentTest, AddComponent_1796) {
    // Create a mock component to add
    UniquePtr mockComponent = std::make_unique<CiffComponent>(0, 0);
    EXPECT_CALL(component, doAdd(testing::_))
        .WillOnce(testing::ReturnRef(mockComponent));

    EXPECT_EQ(&component.add(std::move(mockComponent)), &mockComponent);
}

// Test for the add() method with CrwDirs (Boundary condition)
TEST_F(CiffComponentTest, AddComponentCrwDirs_1797) {
    CrwDirs crwDirs;
    uint16_t crwTagId = 1234;
    
    // Expect the add to be called with crwDirs and crwTagId
    EXPECT_CALL(component, doAdd(testing::_, crwTagId))
        .WillOnce(testing::ReturnRef(component));
    
    component.add(crwDirs, crwTagId);
}

// Test for the findComponent() method (Normal operation)
TEST_F(CiffComponentTest, FindComponent_1798) {
    uint16_t crwTagId = 1234;
    uint16_t crwDir = 5678;
    
    EXPECT_CALL(component, doFindComponent(crwTagId, crwDir))
        .WillOnce(testing::Return(&component));

    EXPECT_EQ(component.findComponent(crwTagId, crwDir), &component);
}

// Test for the write() method (Normal operation)
TEST_F(CiffComponentTest, Write_1799) {
    Blob blob;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    size_t offset = 0;
    
    EXPECT_CALL(component, doWrite(testing::_, byteOrder, offset))
        .WillOnce(testing::Return(1024));

    EXPECT_EQ(component.write(blob, byteOrder, offset), 1024);
}

// Test for the write() method with an exceptional case (Boundary condition: zero offset)
TEST_F(CiffComponentTest, WriteZeroOffset_1800) {
    Blob blob;
    ByteOrder byteOrder = ByteOrder::bigEndian;
    size_t offset = 0;

    EXPECT_CALL(component, doWrite(testing::_, byteOrder, offset))
        .WillOnce(testing::Return(0)); // Zero offset case

    EXPECT_EQ(component.write(blob, byteOrder, offset), 0);
}

// Test for the remove() method (Normal operation)
TEST_F(CiffComponentTest, Remove_1801) {
    CrwDirs crwDirs;
    uint16_t crwTagId = 1234;

    EXPECT_CALL(component, doRemove(testing::_, crwTagId))
        .Times(1);

    component.remove(crwDirs, crwTagId);
}

// Test for the decode() method (Normal operation)
TEST_F(CiffComponentTest, Decode_1802) {
    Image image;
    ByteOrder byteOrder = ByteOrder::littleEndian;

    EXPECT_CALL(component, doDecode(image, byteOrder))
        .Times(1);

    component.decode(image, byteOrder);
}

}  // namespace Internal
}  // namespace Exiv2