#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"  // Include the header for the CiffComponent class

namespace Exiv2 {
namespace Internal {

// Mock class for testing
class MockCiffComponent : public CiffComponent {
public:
    MockCiffComponent(uint16_t tag, uint16_t dir) : CiffComponent(tag, dir) {}

    MOCK_METHOD(const UniquePtr&, doAdd, (UniquePtr component), (override));
    MOCK_METHOD(const UniquePtr&, doAdd, (CrwDirs & crwDirs, uint16_t crwTagId), (override));
    MOCK_METHOD(void, doRemove, (CrwDirs & crwDirs, uint16_t crwTagId), (override));
    MOCK_METHOD(void, doRead, (const byte* pData, size_t size, uint32_t start, ByteOrder byteOrder), (override));
    MOCK_METHOD(size_t, doWrite, (Blob& blob, ByteOrder byteOrder, size_t offset), (override));
    MOCK_METHOD(void, doDecode, (Image& image, ByteOrder byteOrder), (override));
    MOCK_METHOD(void, doPrint, (std::ostream& os, ByteOrder byteOrder, const std::string& prefix), (override));
    MOCK_METHOD(bool, doEmpty, (), (override));
    MOCK_METHOD(CiffComponent*, doFindComponent, (uint16_t crwTagId, uint16_t crwDir), (override));
};

// Test for the default constructor
TEST_F(CiffComponentTest_1757, DefaultConstructor_1757) {
    CiffComponent component;
    EXPECT_EQ(component.dir(), 0);  // dir_ should default to 0
    EXPECT_EQ(component.tag(), 0);  // tag_ should default to 0
    EXPECT_EQ(component.size(), 0); // size_ should default to 0
    EXPECT_EQ(component.offset(), 0); // offset_ should default to 0
    EXPECT_EQ(component.pData(), nullptr); // pData_ should default to nullptr
}

// Test for the parameterized constructor
TEST_F(CiffComponentTest_1758, ParameterizedConstructor_1758) {
    uint16_t dir = 1;
    uint16_t tag = 10;
    CiffComponent component(tag, dir);
    EXPECT_EQ(component.dir(), dir);  // Check that dir is set correctly
    EXPECT_EQ(component.tag(), tag);  // Check that tag is set correctly
}

// Test for the setDir method
TEST_F(CiffComponentTest_1759, SetDir_1759) {
    CiffComponent component;
    uint16_t dir = 42;
    component.setDir(dir);
    EXPECT_EQ(component.dir(), dir);  // Verify the dir was set correctly
}

// Test for the add method (basic functionality)
TEST_F(CiffComponentTest_1760, AddComponent_1760) {
    CiffComponent component(1, 2);
    UniquePtr dummyComponent = std::make_unique<CiffComponent>(3, 4);
    EXPECT_CALL(component, doAdd(::testing::_)).Times(1);  // Verify the internal doAdd is called
    component.add(std::move(dummyComponent));
}

// Test for the remove method (basic functionality)
TEST_F(CiffComponentTest_1761, RemoveComponent_1761) {
    CiffComponent component(1, 2);
    CrwDirs crwDirs;
    uint16_t tagId = 100;
    EXPECT_CALL(component, doRemove(::testing::Ref(crwDirs), tagId)).Times(1); // Verify doRemove is called
    component.remove(crwDirs, tagId);
}

// Test for the read method (boundary condition: empty data)
TEST_F(CiffComponentTest_1762, ReadEmptyData_1762) {
    CiffComponent component(1, 2);
    const byte* pData = nullptr;
    size_t size = 0;
    uint32_t start = 0;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    EXPECT_CALL(component, doRead(pData, size, start, byteOrder)).Times(1); // Verify read function is invoked
    component.read(pData, size, start, byteOrder);
}

// Test for the write method (boundary condition: zero size)
TEST_F(CiffComponentTest_1763, WriteZeroSize_1763) {
    CiffComponent component(1, 2);
    Blob blob;
    ByteOrder byteOrder = ByteOrder::littleEndian;
    size_t offset = 0;
    EXPECT_CALL(component, doWrite(::testing::Ref(blob), byteOrder, offset)).Times(1); // Verify write is invoked
    size_t writtenSize = component.write(blob, byteOrder, offset);
    EXPECT_EQ(writtenSize, 0);  // Expect the write to handle zero-size gracefully
}

// Test for the empty method (boundary condition: empty component)
TEST_F(CiffComponentTest_1764, EmptyComponent_1764) {
    CiffComponent component;
    EXPECT_CALL(component, doEmpty()).Times(1); // Verify doEmpty is called
    EXPECT_TRUE(component.empty());  // Expect empty to return true for an empty component
}

// Test for exceptional case: calling findComponent with invalid tagId
TEST_F(CiffComponentTest_1765, FindComponentInvalid_1765) {
    CiffComponent component(1, 2);
    uint16_t crwTagId = 999;
    uint16_t crwDir = 0;
    EXPECT_CALL(component, doFindComponent(crwTagId, crwDir)).WillOnce(::testing::Return(nullptr));  // Expect null
    CiffComponent* found = component.findComponent(crwTagId, crwDir);
    EXPECT_EQ(found, nullptr);  // Expect nullptr as the component wasn't found
}

} // namespace Internal
} // namespace Exiv2