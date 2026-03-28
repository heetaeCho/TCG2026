#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "crwimage_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class CiffComponentTest_1762 : public ::testing::Test {

protected:

    CiffComponent component;

};



TEST_F(CiffComponentTest_1762, DefaultConstructorInitializesNullPointerData_1762) {

    EXPECT_EQ(component.pData(), nullptr);

}



TEST_F(CiffComponentTest_1762, ParameterizedConstructorSetsTagAndDir_1762) {

    uint16_t tag = 0x1234;

    uint16_t dir = 0x5678;

    CiffComponent component(tag, dir);

    EXPECT_EQ(component.tag(), tag);

    EXPECT_EQ(component.dir(), dir);

}



TEST_F(CiffComponentTest_1762, SetDirUpdatesDirectoryValue_1762) {

    uint16_t newDir = 0x5678;

    component.setDir(newDir);

    EXPECT_EQ(component.dir(), newDir);

}



TEST_F(CiffComponentTest_1762, EmptyMethodReturnsTrueByDefault_1762) {

    EXPECT_TRUE(component.empty());

}



TEST_F(CiffComponentTest_1762, SetSizeUpdatesSizeValue_1762) {

    size_t newSize = 1024;

    component.setSize(newSize);

    EXPECT_EQ(component.size(), newSize);

}



TEST_F(CiffComponentTest_1762, SetOffsetUpdatesOffsetValue_1762) {

    size_t newOffset = 512;

    component.setOffset(newOffset);

    EXPECT_EQ(component.offset(), newOffset);

}



// Mock classes for testing external interactions

class MockImage : public Image {

public:

    MOCK_METHOD(void, readMetadata, (), (override));

};



class MockBlob : public Blob {

public:

    MOCK_METHOD(void, append, (const byte*, size_t), (override));

};



TEST_F(CiffComponentTest_1762, DecodeCallsDoDecode_1762) {

    MockImage mockImage;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockImage, readMetadata()).Times(1);

    // Since doDecode is protected and not virtual, we cannot directly verify its call.

    component.decode(mockImage, byteOrder);

}



TEST_F(CiffComponentTest_1762, WriteCallsDoWrite_1762) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;



    EXPECT_CALL(mockBlob, append(_, _)).Times(1);

    // Since doWrite is protected and not virtual, we cannot directly verify its call.

    component.write(mockBlob, byteOrder, offset);

}



TEST_F(CiffComponentTest_1762, WriteValueDataCallsDoWriteValueData_1762) {

    MockBlob mockBlob;

    size_t offset = 0;



    EXPECT_CALL(mockBlob, append(_, _)).Times(1);

    // Since writeValueData directly calls doWriteValueData, we can't verify doWriteValueData separately.

    component.writeValueData(mockBlob, offset);

}



TEST_F(CiffComponentTest_1762, FindComponentCallsDoFindComponent_1762) {

    uint16_t crwTagId = 0x9ABC;

    uint16_t crwDir = 0xCDEF;



    // Since doFindComponent is protected and not virtual, we cannot directly verify its call.

    component.findComponent(crwTagId, crwDir);

}



TEST_F(CiffComponentTest_1762, PrintCallsDoPrint_1762) {

    std::ostringstream os;

    ByteOrder byteOrder = littleEndian;

    std::string prefix = "prefix";



    // Since doPrint is protected and not virtual, we cannot directly verify its call.

    component.print(os, byteOrder, prefix);

}



TEST_F(CiffComponentTest_1762, WriteDirEntryCallsDoWriteDirEntry_1762) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(mockBlob, append(_, _)).Times(1);

    // Since writeDirEntry directly calls doWriteDirEntry, we can't verify doWriteDirEntry separately.

    component.writeDirEntry(mockBlob, byteOrder);

}



TEST_F(CiffComponentTest_1762, AddWithUniquePtrCallsDoAdd_1762) {

    std::unique_ptr<CiffComponent> uniqueComp = std::make_unique<CiffComponent>();

    CiffComponent::UniquePtr ptr(std::move(uniqueComp));



    // Since doAdd is protected and not virtual, we cannot directly verify its call.

    component.add(ptr);

}



TEST_F(CiffComponentTest_1762, AddWithCrwDirsCallsDoAdd_1762) {

    CrwDirs crwDirs;

    uint16_t crwTagId = 0x9ABC;



    // Since doAdd is protected and not virtual, we cannot directly verify its call.

    component.add(crwDirs, crwTagId);

}



TEST_F(CiffComponentTest_1762, RemoveCallsDoRemove_1762) {

    CrwDirs crwDirs;

    uint16_t crwTagId = 0x9ABC;



    // Since doRemove is protected and not virtual, we cannot directly verify its call.

    component.remove(crwDirs, crwTagId);

}
