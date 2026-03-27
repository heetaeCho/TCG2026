#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "crwimage_int.hpp"

namespace Exiv2 {
namespace Internal {

// Mocking necessary components
class MockCiffComponent : public CiffComponent {
public:
    MockCiffComponent(uint16_t tag, uint16_t dir) : CiffComponent(tag, dir) {}

    MOCK_METHOD(void, doRead, (const byte* pData, size_t size, uint32_t start, ByteOrder byteOrder), (override));
    MOCK_METHOD(size_t, doWrite, (Blob& blob, ByteOrder byteOrder, size_t offset), (override));
    MOCK_METHOD(void, doDecode, (Image& image, ByteOrder byteOrder), (override));
    MOCK_METHOD(void, doPrint, (std::ostream& os, ByteOrder byteOrder, const std::string& prefix), (override));
    MOCK_METHOD(bool, doEmpty, (), (override));
    MOCK_METHOD(CiffComponent*, doFindComponent, (uint16_t crwTagId, uint16_t crwDir), (override));
};

// Unit tests
TEST_F(CiffComponentTest_1772, ConstructorSetsDefaults_1772) {
    MockCiffComponent component(123, 456);
    EXPECT_EQ(component.dir(), 456);
    EXPECT_EQ(component.tag(), 123);
    EXPECT_EQ(component.size(), 0);
    EXPECT_EQ(component.offset(), 0);
    EXPECT_EQ(component.pData(), nullptr);
}

TEST_F(CiffComponentTest_1772, ReadInvokesDoRead_1772) {
    MockCiffComponent component(123, 456);
    byte data[] = {0x01, 0x02};
    EXPECT_CALL(component, doRead(data, sizeof(data), 10, ByteOrder::littleEndian))
        .Times(1);

    component.read(data, sizeof(data), 10, ByteOrder::littleEndian);
}

TEST_F(CiffComponentTest_1772, WriteInvokesDoWrite_1772) {
    MockCiffComponent component(123, 456);
    Blob blob;
    EXPECT_CALL(component, doWrite(blob, ByteOrder::bigEndian, 100))
        .Times(1)
        .WillOnce(testing::Return(200));

    size_t result = component.write(blob, ByteOrder::bigEndian, 100);
    EXPECT_EQ(result, 200);
}

TEST_F(CiffComponentTest_1772, DecodeInvokesDoDecode_1772) {
    MockCiffComponent component(123, 456);
    Image image;
    EXPECT_CALL(component, doDecode(image, ByteOrder::littleEndian))
        .Times(1);

    component.decode(image, ByteOrder::littleEndian);
}

TEST_F(CiffComponentTest_1772, PrintInvokesDoPrint_1772) {
    MockCiffComponent component(123, 456);
    std::ostringstream os;
    EXPECT_CALL(component, doPrint(testing::Ref(os), ByteOrder::bigEndian, testing::_))
        .Times(1);

    component.print(os, ByteOrder::bigEndian, "Prefix");
}

TEST_F(CiffComponentTest_1772, EmptyReturnsTrue_1772) {
    MockCiffComponent component(123, 456);
    EXPECT_CALL(component, doEmpty())
        .Times(1)
        .WillOnce(testing::Return(true));

    EXPECT_TRUE(component.empty());
}

TEST_F(CiffComponentTest_1772, FindComponentReturnsCorrectResult_1772) {
    MockCiffComponent component(123, 456);
    CiffComponent* foundComponent = new MockCiffComponent(789, 101);
    EXPECT_CALL(component, doFindComponent(789, 101))
        .Times(1)
        .WillOnce(testing::Return(foundComponent));

    CiffComponent* result = component.findComponent(789, 101);
    EXPECT_EQ(result, foundComponent);
}

} // namespace Internal
} // namespace Exiv2