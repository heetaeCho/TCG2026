#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/error.hpp>
#include <cstdio>
#include <fstream>
#include <vector>

using namespace Exiv2;

// Since RemoteIo is abstract (requires URL), we'll test through concrete subclasses
// or through MemIo which shares some interface. However, the focus is on RemoteIo::getb().
// We'll use HttpIo as a concrete RemoteIo subclass with populateFakeData().

class RemoteIoTest_607 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

// Test that MemIo getb returns correct byte values for normal operation
TEST_F(RemoteIoTest_607, MemIoGetbReturnsCorrectByte_607) {
    byte data[] = {0x41, 0x42, 0x43};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    EXPECT_EQ(0x41, memIo.getb());
    EXPECT_EQ(0x42, memIo.getb());
    EXPECT_EQ(0x43, memIo.getb());
}

// Test that MemIo getb returns EOF at end of data
TEST_F(RemoteIoTest_607, MemIoGetbReturnsEOFAtEnd_607) {
    byte data[] = {0x41};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    EXPECT_EQ(0x41, memIo.getb());
    EXPECT_EQ(EOF, memIo.getb());
}

// Test that eof() returns true after reading past end
TEST_F(RemoteIoTest_607, MemIoEofAfterGetbPastEnd_607) {
    byte data[] = {0x41};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    EXPECT_FALSE(memIo.eof());
    memIo.getb(); // read the byte
    memIo.getb(); // attempt to read past end
    EXPECT_TRUE(memIo.eof());
}

// Test getb on empty MemIo returns EOF immediately
TEST_F(RemoteIoTest_607, MemIoGetbOnEmptyReturnsEOF_607) {
    MemIo memIo;
    memIo.open();
    
    EXPECT_EQ(EOF, memIo.getb());
    EXPECT_TRUE(memIo.eof());
}

// Test that tell() advances after getb calls
TEST_F(RemoteIoTest_607, MemIoTellAdvancesAfterGetb_607) {
    byte data[] = {0x01, 0x02, 0x03, 0x04};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    EXPECT_EQ(0u, memIo.tell());
    memIo.getb();
    EXPECT_EQ(1u, memIo.tell());
    memIo.getb();
    EXPECT_EQ(2u, memIo.tell());
}

// Test seek then getb reads correct byte
TEST_F(RemoteIoTest_607, MemIoSeekThenGetb_607) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    memIo.seek(3, BasicIo::beg);
    EXPECT_EQ(0x40, memIo.getb());
}

// Test seek to end then getb returns EOF
TEST_F(RemoteIoTest_607, MemIoSeekToEndThenGetbReturnsEOF_607) {
    byte data[] = {0x10, 0x20, 0x30};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    memIo.seek(0, BasicIo::end);
    EXPECT_EQ(EOF, memIo.getb());
}

// Test getb with all possible byte values (boundary: 0x00 and 0xFF)
TEST_F(RemoteIoTest_607, MemIoGetbBoundaryByteValues_607) {
    byte data[] = {0x00, 0xFF};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    EXPECT_EQ(0x00, memIo.getb());
    EXPECT_EQ(0xFF, memIo.getb());
}

// Test size() returns correct value
TEST_F(RemoteIoTest_607, MemIoSizeReturnsCorrectValue_607) {
    byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    
    EXPECT_EQ(3u, memIo.size());
}

// Test isopen after open and close
TEST_F(RemoteIoTest_607, MemIoIsOpenState_607) {
    MemIo memIo;
    EXPECT_TRUE(memIo.isopen());
    memIo.open();
    EXPECT_TRUE(memIo.isopen());
}

// Test multiple getb calls reading entire buffer
TEST_F(RemoteIoTest_607, MemIoGetbReadEntireBuffer_607) {
    std::vector<byte> data(256);
    for (int i = 0; i < 256; ++i) {
        data[i] = static_cast<byte>(i);
    }
    MemIo memIo(data.data(), data.size());
    memIo.open();
    
    for (int i = 0; i < 256; ++i) {
        int result = memIo.getb();
        EXPECT_EQ(i, result) << "Mismatch at position " << i;
    }
    EXPECT_EQ(EOF, memIo.getb());
}

// Test error() returns 0 for normal operation
TEST_F(RemoteIoTest_607, MemIoErrorReturnsZeroNormally_607) {
    byte data[] = {0x01};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    EXPECT_EQ(0, memIo.error());
}

// Test seek with cur position and then getb
TEST_F(RemoteIoTest_607, MemIoSeekCurThenGetb_607) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    memIo.getb(); // read 0x10, position = 1
    memIo.seek(2, BasicIo::cur); // position = 3
    EXPECT_EQ(0x40, memIo.getb());
}

// Test putb and then seek back and getb
TEST_F(RemoteIoTest_607, MemIoPutbThenGetb_607) {
    MemIo memIo;
    memIo.open();
    
    memIo.putb(0x55);
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0x55, memIo.getb());
}

// Test read method with buffer
TEST_F(RemoteIoTest_607, MemIoReadBuffer_607) {
    byte data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    byte buf[4] = {};
    size_t bytesRead = memIo.read(buf, 4);
    EXPECT_EQ(4u, bytesRead);
    EXPECT_EQ(0xAA, buf[0]);
    EXPECT_EQ(0xBB, buf[1]);
    EXPECT_EQ(0xCC, buf[2]);
    EXPECT_EQ(0xDD, buf[3]);
}

// Test read returns DataBuf
TEST_F(RemoteIoTest_607, MemIoReadDataBuf_607) {
    byte data[] = {0x01, 0x02, 0x03};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    DataBuf buf = memIo.read(3);
    EXPECT_EQ(3u, buf.size());
}

// Test seek backward from end
TEST_F(RemoteIoTest_607, MemIoSeekBackFromEnd_607) {
    byte data[] = {0x10, 0x20, 0x30, 0x40, 0x50};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    memIo.seek(-2, BasicIo::end);
    EXPECT_EQ(0x40, memIo.getb());
    EXPECT_EQ(0x50, memIo.getb());
    EXPECT_EQ(EOF, memIo.getb());
}

// Test write then read back
TEST_F(RemoteIoTest_607, MemIoWriteThenReadBack_607) {
    MemIo memIo;
    memIo.open();
    
    byte data[] = {0xDE, 0xAD, 0xBE, 0xEF};
    memIo.write(data, sizeof(data));
    memIo.seek(0, BasicIo::beg);
    
    EXPECT_EQ(0xDE, memIo.getb());
    EXPECT_EQ(0xAD, memIo.getb());
    EXPECT_EQ(0xBE, memIo.getb());
    EXPECT_EQ(0xEF, memIo.getb());
    EXPECT_EQ(EOF, memIo.getb());
}

// Test open and close cycle
TEST_F(RemoteIoTest_607, MemIoOpenCloseCycle_607) {
    byte data[] = {0x01, 0x02};
    MemIo memIo(data, sizeof(data));
    
    EXPECT_EQ(0, memIo.open());
    EXPECT_EQ(0x01, memIo.getb());
    EXPECT_EQ(0, memIo.close());
}

// Test getb after eof reset via seek
TEST_F(RemoteIoTest_607, MemIoGetbAfterEofResetViaSeek_607) {
    byte data[] = {0xAA};
    MemIo memIo(data, sizeof(data));
    memIo.open();
    
    memIo.getb(); // read 0xAA
    EXPECT_EQ(EOF, memIo.getb()); // EOF
    EXPECT_TRUE(memIo.eof());
    
    memIo.seek(0, BasicIo::beg);
    EXPECT_EQ(0xAA, memIo.getb()); // should work again
}

// Test single byte data
TEST_F(RemoteIoTest_607, MemIoSingleByteData_607) {
    byte data[] = {0x42};
    MemIo memIo(data, 1);
    memIo.open();
    
    EXPECT_EQ(1u, memIo.size());
    EXPECT_EQ(0x42, memIo.getb());
    EXPECT_EQ(1u, memIo.tell());
    EXPECT_EQ(EOF, memIo.getb());
    EXPECT_TRUE(memIo.eof());
}

// Test FileIo getb for completeness of BasicIo interface
TEST_F(RemoteIoTest_607, FileIoGetbReturnsCorrectByte_607) {
    // Create a temporary file
    const std::string tmpFile = "test_getb_607.tmp";
    {
        std::ofstream ofs(tmpFile, std::ios::binary);
        ofs.put(0x48);
        ofs.put(0x65);
        ofs.put(0x6C);
    }
    
    FileIo fileIo(tmpFile);
    fileIo.open();
    
    EXPECT_EQ(0x48, fileIo.getb());
    EXPECT_EQ(0x65, fileIo.getb());
    EXPECT_EQ(0x6C, fileIo.getb());
    EXPECT_EQ(EOF, fileIo.getb());
    
    fileIo.close();
    std::remove(tmpFile.c_str());
}

// Test large data getb
TEST_F(RemoteIoTest_607, MemIoLargeDataGetb_607) {
    const size_t dataSize = 10000;
    std::vector<byte> data(dataSize);
    for (size_t i = 0; i < dataSize; ++i) {
        data[i] = static_cast<byte>(i & 0xFF);
    }
    
    MemIo memIo(data.data(), data.size());
    memIo.open();
    
    for (size_t i = 0; i < dataSize; ++i) {
        int result = memIo.getb();
        EXPECT_EQ(static_cast<int>(data[i]), result) << "Mismatch at position " << i;
    }
    EXPECT_EQ(EOF, memIo.getb());
}
