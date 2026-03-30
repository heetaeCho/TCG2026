#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;



// Mock classes for dependencies

class MockBlob : public Blob {

public:

    MOCK_METHOD(size_t, size, (), (override));

    MOCK_METHOD(void, append, (const byte*, size_t), (override));

};



class MockCrwDirs : public CrwDirs {

public:

    MOCK_METHOD(bool, hasTag, (uint16_t), (const));

    MOCK_METHOD(void, addComponent, (UniquePtr, uint16_t), ());

    MOCK_METHOD(void, removeComponent, (uint16_t), ());

};



class MockImage : public Image {

public:

    MOCK_METHOD(void, readMetadata, (), (override));

    MOCK_METHOD(void, writeMetadata, (), (override));

};



class CiffComponentTest_1764 : public ::testing::Test {

protected:

    uint16_t tag = 0x0001;

    uint16_t dir = 0x0002;

    MockBlob mockBlob;

    MockCrwDirs mockCrwDirs;

    MockImage mockImage;

    CiffComponent component{tag, dir};

};



TEST_F(CiffComponentTest_1764, TypeIdReturnsCorrectValue_1764) {

    EXPECT_EQ(component.typeId(), CiffComponent::typeId(tag));

}



TEST_F(CiffComponentTest_1764, DataLocationReturnsCorrectValue_1764) {

    EXPECT_EQ(component.dataLocation(), CiffComponent::dataLocation(tag));

}



TEST_F(CiffComponentTest_1764, TagIdReturnsCorrectValue_1764) {

    EXPECT_EQ(component.tagId(), tag);

}



TEST_F(CiffComponentTest_1764, DirReturnsCorrectValue_1764) {

    EXPECT_EQ(component.dir(), dir);

}



TEST_F(CiffComponentTest_1764, AddComponentToDirsWorks_1764) {

    UniquePtr mockUniquePtr = std::make_unique<CiffComponent>();

    EXPECT_CALL(mockCrwDirs, addComponent(_, tag)).Times(1);

    component.add(mockCrwDirs, tag);

}



TEST_F(CiffComponentTest_1764, RemoveComponentFromDirsWorks_1764) {

    EXPECT_CALL(mockCrwDirs, removeComponent(tag)).Times(1);

    component.remove(mockCrwDirs, tag);

}



TEST_F(CiffComponentTest_1764, ReadMethodDoesNotThrow_1764) {

    byte data[] = {0x00};

    size_t size = sizeof(data);

    uint32_t start = 0;

    ByteOrder byteOrder = littleEndian;

    EXPECT_NO_THROW(component.read(data, size, start, byteOrder));

}



TEST_F(CiffComponentTest_1764, WriteMethodDoesNotThrow_1764) {

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;

    EXPECT_CALL(mockBlob, append(_, _)).Times(AtLeast(1));

    EXPECT_NO_THROW(component.write(mockBlob, byteOrder, offset));

}



TEST_F(CiffComponentTest_1764, WriteValueDataMethodDoesNotThrow_1764) {

    size_t offset = 0;

    EXPECT_CALL(mockBlob, append(_, _)).Times(AtLeast(1));

    EXPECT_NO_THROW(component.writeValueData(mockBlob, offset));

}



TEST_F(CiffComponentTest_1764, DecodeMethodDoesNotThrow_1764) {

    ByteOrder byteOrder = littleEndian;

    EXPECT_NO_THROW(component.decode(mockImage, byteOrder));

}



TEST_F(CiffComponentTest_1764, PrintMethodDoesNotThrow_1764) {

    std::ostringstream oss;

    ByteOrder byteOrder = littleEndian;

    std::string prefix = "";

    EXPECT_NO_THROW(component.print(oss, byteOrder, prefix));

}



TEST_F(CiffComponentTest_1764, WriteDirEntryMethodDoesNotThrow_1764) {

    ByteOrder byteOrder = littleEndian;

    EXPECT_CALL(mockBlob, append(_, _)).Times(AtLeast(1));

    EXPECT_NO_THROW(component.writeDirEntry(mockBlob, byteOrder));

}



TEST_F(CiffComponentTest_1764, FindComponentReturnsNullptrWhenNotFound_1764) {

    uint16_t crwTagId = 0x0003;

    uint16_t crwDir = 0x0004;

    EXPECT_CALL(mockCrwDirs, hasTag(crwTagId)).WillOnce(::testing::Return(false));

    EXPECT_EQ(component.findComponent(crwTagId, crwDir), nullptr);

}



TEST_F(CiffComponentTest_1764, EmptyMethodReturnsFalseInitially_1764) {

    EXPECT_FALSE(component.empty());

}
