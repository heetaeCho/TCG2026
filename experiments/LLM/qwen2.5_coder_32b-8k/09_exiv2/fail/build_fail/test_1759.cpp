#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "./TestProjects/exiv2/src/crwimage_int.hpp"



using namespace Exiv2::Internal;

using ::testing::_;

using ::testing::Return;



class CiffComponentTest_1759 : public ::testing::Test {

protected:

    CiffComponent component{0x0001, 0x0002};

};



TEST_F(CiffComponentTest_1759, TagReturnsCorrectValue_1759) {

    EXPECT_EQ(component.tag(), 0x0001);

}



TEST_F(CiffComponentTest_1759, DirReturnsDefaultValue_1759) {

    EXPECT_EQ(component.dir(), 0x0002);

}



TEST_F(CiffComponentTest_1759, SetDirChangesValue_1759) {

    component.setDir(0x0003);

    EXPECT_EQ(component.dir(), 0x0003);

}



TEST_F(CiffComponentTest_1759, TagIdReturnsCorrectValue_1759) {

    EXPECT_EQ(component.tagId(), 0x0001);

}



TEST_F(CiffComponentTest_1759, SizeAndOffsetReturnDefaultValue_1759) {

    EXPECT_EQ(component.size(), 0);

    EXPECT_EQ(component.offset(), 0);

}



TEST_F(CiffComponentTest_1759, EmptyReturnsTrueWhenNoData_1759) {

    EXPECT_TRUE(component.empty());

}



// Mocking Image and Blob for external interactions

class MockImage : public Image {

public:

    MOCK_METHOD(void, readMetadata, (ByteOrder byteOrder), (override));

};



class MockBlob : public Blob {

public:

    MOCK_METHOD(void, append, (const DataBuf& buf));

    MOCK_METHOD(size_t, size, (), (const, override));

};



TEST_F(CiffComponentTest_1759, ReadCallsDoRead_1759) {

    const byte testData[] = {0x00, 0x01};

    uint32_t start = 0;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(*this, doRead(testData, sizeof(testData), start, byteOrder));



    component.read(testData, sizeof(testData), start, byteOrder);

}



TEST_F(CiffComponentTest_1759, WriteCallsDoWrite_1759) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;

    size_t offset = 0;



    EXPECT_CALL(mockBlob, append(_));

    EXPECT_CALL(*this, doWrite(&mockBlob, byteOrder, offset));



    component.write(mockBlob, byteOrder, offset);

}



TEST_F(CiffComponentTest_1759, WriteValueDataCallsDoWrite_1759) {

    MockBlob mockBlob;

    size_t offset = 0;



    EXPECT_CALL(mockBlob, append(_));

    EXPECT_CALL(*this, doWrite(&mockBlob, littleEndian, offset));



    component.writeValueData(mockBlob, offset);

}



TEST_F(CiffComponentTest_1759, DecodeCallsDoDecode_1759) {

    MockImage mockImage;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(*this, doDecode(&mockImage, byteOrder));



    component.decode(mockImage, byteOrder);

}



TEST_F(CiffComponentTest_1759, PrintCallsDoPrint_1759) {

    std::ostringstream oss;

    ByteOrder byteOrder = littleEndian;

    std::string prefix = "test";



    EXPECT_CALL(*this, doPrint(&oss, byteOrder, prefix));



    component.print(oss, byteOrder, prefix);

}



TEST_F(CiffComponentTest_1759, WriteDirEntryCallsDoWrite_1759) {

    MockBlob mockBlob;

    ByteOrder byteOrder = littleEndian;



    EXPECT_CALL(*this, doWrite(&mockBlob, byteOrder));



    component.writeDirEntry(mockBlob, byteOrder);

}
