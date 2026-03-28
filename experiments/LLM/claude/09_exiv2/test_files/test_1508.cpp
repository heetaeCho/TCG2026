#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdint>
#include <cstring>
#include <vector>

// We need to include the relevant headers from exiv2
#include "makernote_int.hpp"
#include "types.hpp"

// Since we need IoWrapper for testing, we need to include or mock it
// IoWrapper wraps a BasicIo and writes data to it
#include "image_int.hpp"

using namespace Exiv2;
using namespace Exiv2::Internal;
using ::testing::_;
using ::testing::Return;

// Helper: create a MemIo-based IoWrapper for testing write operations
class Casio2MnHeaderTest_1508 : public ::testing::Test {
protected:
    void SetUp() override {
    }

    void TearDown() override {
    }
};

TEST_F(Casio2MnHeaderTest_1508, DefaultConstruction_1508) {
    // Test that a Casio2MnHeader can be default constructed
    Casio2MnHeader header;
    // If we get here without exception, construction succeeded
    SUCCEED();
}

TEST_F(Casio2MnHeaderTest_1508, SizeOfSignatureIsPositive_1508) {
    Casio2MnHeader header;
    EXPECT_GT(Casio2MnHeader::sizeOfSignature(), 0u);
}

TEST_F(Casio2MnHeaderTest_1508, WriteReturnsSignatureSize_1508) {
    Casio2MnHeader header;

    // Create a memory-based IO to capture writes
    auto memIo = std::make_unique<Exiv2::MemIo>();
    memIo->open();

    // IoWrapper needs a BasicIo reference, a byte array pointer, and a size
    // We'll construct it minimally
    IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);

    ByteOrder byteOrder = littleEndian;
    size_t bytesWritten = header.write(ioWrapper, byteOrder);

    EXPECT_EQ(bytesWritten, Casio2MnHeader::sizeOfSignature());
}

TEST_F(Casio2MnHeaderTest_1508, WriteWithBigEndian_1508) {
    Casio2MnHeader header;

    auto memIo = std::make_unique<Exiv2::MemIo>();
    memIo->open();

    IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);

    ByteOrder byteOrder = bigEndian;
    size_t bytesWritten = header.write(ioWrapper, byteOrder);

    EXPECT_EQ(bytesWritten, Casio2MnHeader::sizeOfSignature());
}

TEST_F(Casio2MnHeaderTest_1508, WriteWithLittleEndian_1508) {
    Casio2MnHeader header;

    auto memIo = std::make_unique<Exiv2::MemIo>();
    memIo->open();

    IoWrapper ioWrapper(*memIo, nullptr, 0, nullptr);

    ByteOrder byteOrder = littleEndian;
    size_t bytesWritten = header.write(ioWrapper, byteOrder);

    EXPECT_EQ(bytesWritten, Casio2MnHeader::sizeOfSignature());
}

TEST_F(Casio2MnHeaderTest_1508, WriteActuallyWritesData_1508) {
    Casio2MnHeader header;

    Exiv2::MemIo memIo;
    memIo.open();

    IoWrapper ioWrapper(memIo, nullptr, 0, nullptr);

    ByteOrder byteOrder = littleEndian;
    size_t bytesWritten = header.write(ioWrapper, byteOrder);

    // Verify that data was actually written to the IO
    EXPECT_EQ(memIo.size(), bytesWritten);
    EXPECT_GT(memIo.size(), 0u);
}

TEST_F(Casio2MnHeaderTest_1508, WriteConsistentAcrossCalls_1508) {
    Casio2MnHeader header;

    // First write
    Exiv2::MemIo memIo1;
    memIo1.open();
    IoWrapper ioWrapper1(memIo1, nullptr, 0, nullptr);
    size_t bytesWritten1 = header.write(ioWrapper1, littleEndian);

    // Second write
    Exiv2::MemIo memIo2;
    memIo2.open();
    IoWrapper ioWrapper2(memIo2, nullptr, 0, nullptr);
    size_t bytesWritten2 = header.write(ioWrapper2, littleEndian);

    // Both writes should produce the same result
    EXPECT_EQ(bytesWritten1, bytesWritten2);
    EXPECT_EQ(memIo1.size(), memIo2.size());

    // Compare the actual bytes written
    memIo1.seek(0, BasicIo::beg);
    memIo2.seek(0, BasicIo::beg);

    std::vector<uint8_t> buf1(memIo1.size());
    std::vector<uint8_t> buf2(memIo2.size());

    memIo1.read(buf1.data(), buf1.size());
    memIo2.read(buf2.data(), buf2.size());

    EXPECT_EQ(buf1, buf2);
}

TEST_F(Casio2MnHeaderTest_1508, ByteOrderDoesNotAffectSignature_1508) {
    // The write method ignores ByteOrder for the signature
    Casio2MnHeader header;

    Exiv2::MemIo memIoLE;
    memIoLE.open();
    IoWrapper ioWrapperLE(memIoLE, nullptr, 0, nullptr);
    size_t bytesLE = header.write(ioWrapperLE, littleEndian);

    Exiv2::MemIo memIoBE;
    memIoBE.open();
    IoWrapper ioWrapperBE(memIoBE, nullptr, 0, nullptr);
    size_t bytesBE = header.write(ioWrapperBE, bigEndian);

    // Both should write the same number of bytes
    EXPECT_EQ(bytesLE, bytesBE);

    // Both should write the same content (signature doesn't depend on byte order)
    memIoLE.seek(0, BasicIo::beg);
    memIoBE.seek(0, BasicIo::beg);

    std::vector<uint8_t> bufLE(memIoLE.size());
    std::vector<uint8_t> bufBE(memIoBE.size());

    memIoLE.read(bufLE.data(), bufLE.size());
    memIoBE.read(bufBE.data(), bufBE.size());

    EXPECT_EQ(bufLE, bufBE);
}
