#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <memory>
#include <cstring>

#include "exiv2/bmffimage.hpp"
#include "exiv2/basicio.hpp"
#include "exiv2/error.hpp"
#include "exiv2/xmp_exiv2.hpp"

using namespace Exiv2;

// Mock BasicIo for testing parseXmp
class MockBasicIo : public BasicIo {
public:
    MOCK_METHOD(int, open, (), (override));
    MOCK_METHOD(int, close, (), (override));
    MOCK_METHOD(size_t, write, (const byte* data, size_t wcount), (override));
    MOCK_METHOD(size_t, write, (BasicIo& src), (override));
    MOCK_METHOD(int, putb, (byte data), (override));
    MOCK_METHOD(DataBuf, read, (size_t rcount), (override));
    MOCK_METHOD(size_t, read, (byte* buf, size_t rcount), (override));
    MOCK_METHOD(int, getb, (), (override));
    MOCK_METHOD(void, transfer, (BasicIo& src), (override));
    MOCK_METHOD(int, seek, (int64_t offset, Position pos), (override));
    MOCK_METHOD(byte*, mmap, (bool isWriteable), (override));
    MOCK_METHOD(int, munmap, (), (override));
    MOCK_METHOD(size_t, tell, (), (const, override));
    MOCK_METHOD(size_t, size, (), (const, override));
    MOCK_METHOD(bool, isopen, (), (const, override));
    MOCK_METHOD(int, error, (), (const, override));
    MOCK_METHOD(bool, eof, (), (const, override));
    MOCK_METHOD(const std::string&, path, (), (const, override));
    MOCK_METHOD(void, populateFakeData, (), (override));

    std::string path_ = "mock";
};

class BmffImageParseXmpTest_1198 : public ::testing::Test {
protected:
    void SetUp() override {
        XmpParser::initialize();
    }

    void TearDown() override {
        XmpParser::terminate();
    }

    // Helper to create a BmffImage with a mock IO
    // We need to use a MemoryIo or work around the unique_ptr requirement
    // Since BmffImage takes ownership of io_, we'll use a real MemoryIo approach
};

// Test: start exceeds io size -> throws kerCorruptedMetadata
TEST_F(BmffImageParseXmpTest_1198, StartExceedsIoSize_1198) {
    const std::string xmpData = "<x:xmpmeta></x:xmpmeta>";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(xmpData.data()), xmpData.size());

    BmffImage img(std::move(memIo), false, 100);

    // start = size + 1, which exceeds io size
    EXPECT_THROW(img.parseXmp(1, xmpData.size() + 1), Error);
}

// Test: length exceeds available data from start -> throws kerCorruptedMetadata
TEST_F(BmffImageParseXmpTest_1198, LengthExceedsAvailableData_1198) {
    const std::string xmpData = "<x:xmpmeta></x:xmpmeta>";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(xmpData.data()), xmpData.size());

    BmffImage img(std::move(memIo), false, 100);

    // length = size + 1 starting from 0
    EXPECT_THROW(img.parseXmp(xmpData.size() + 1, 0), Error);
}

// Test: length + start overflow scenario
TEST_F(BmffImageParseXmpTest_1198, LengthPlusStartExceedsSize_1198) {
    const std::string xmpData = "0123456789";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(xmpData.data()), xmpData.size());

    BmffImage img(std::move(memIo), false, 100);

    // start=5, length=6 -> 5+6=11 > 10
    EXPECT_THROW(img.parseXmp(6, 5), Error);
}

// Test: Valid XMP data parsed successfully
TEST_F(BmffImageParseXmpTest_1198, ValidXmpDataParsedSuccessfully_1198) {
    const std::string xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''"
        " xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:description>"
        "<rdf:Alt><rdf:li xml:lang='x-default'>Test</rdf:li></rdf:Alt>"
        "</dc:description>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(xmpData.data()), xmpData.size());

    BmffImage img(std::move(memIo), false, 100);

    EXPECT_NO_THROW(img.parseXmp(xmpData.size(), 0));

    // Check that XMP data was populated
    const XmpData& xmp = img.xmpData();
    EXPECT_FALSE(xmp.empty());
}

// Test: Zero length XMP data (empty)
TEST_F(BmffImageParseXmpTest_1198, ZeroLengthXmpData_1198) {
    const std::string data = "some data";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(data.data()), data.size());

    BmffImage img(std::move(memIo), false, 100);

    // length=0, start=0 -> should read 0 bytes, empty xmp
    EXPECT_NO_THROW(img.parseXmp(0, 0));
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: start equals io size with length 0
TEST_F(BmffImageParseXmpTest_1198, StartEqualsIoSizeWithZeroLength_1198) {
    const std::string data = "abcdef";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(data.data()), data.size());

    BmffImage img(std::move(memIo), false, 100);

    // start = size, length = 0 -> should be valid (start <= size, length <= size - start = 0)
    EXPECT_NO_THROW(img.parseXmp(0, data.size()));
}

// Test: Parse XMP from middle of data
TEST_F(BmffImageParseXmpTest_1198, ParseXmpFromMiddleOfData_1198) {
    // Prefix some garbage, then XMP data
    const std::string prefix = "GARBAGE_PREFIX";
    const std::string xmpData =
        "<?xpacket begin='' id='W5M0MpCehiHzreSzNTczkc9d'?>"
        "<x:xmpmeta xmlns:x='adobe:ns:meta/'>"
        "<rdf:RDF xmlns:rdf='http://www.w3.org/1999/02/22-rdf-syntax-ns#'>"
        "<rdf:Description rdf:about=''"
        " xmlns:dc='http://purl.org/dc/elements/1.1/'>"
        "<dc:creator><rdf:Seq><rdf:li>Author</rdf:li></rdf:Seq></dc:creator>"
        "</rdf:Description>"
        "</rdf:RDF>"
        "</x:xmpmeta>"
        "<?xpacket end='w'?>";

    std::string combined = prefix + xmpData;
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(combined.data()), combined.size());

    BmffImage img(std::move(memIo), false, 100);

    EXPECT_NO_THROW(img.parseXmp(xmpData.size(), prefix.size()));
    EXPECT_FALSE(img.xmpData().empty());
}

// Test: start equals io size but length > 0 -> should throw
TEST_F(BmffImageParseXmpTest_1198, StartEqualsIoSizeWithNonZeroLength_1198) {
    const std::string data = "abcdef";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(data.data()), data.size());

    BmffImage img(std::move(memIo), false, 100);

    // start = size, length = 1 -> length > size - start = 0
    EXPECT_THROW(img.parseXmp(1, data.size()), Error);
}

// Test: Exact boundary - read exactly all data from start to end
TEST_F(BmffImageParseXmpTest_1198, ExactBoundaryReadAllData_1198) {
    const std::string data = "<x:xmpmeta xmlns:x='adobe:ns:meta/'/>";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(data.data()), data.size());

    BmffImage img(std::move(memIo), false, 100);

    // length = size, start = 0 -> exactly fits
    EXPECT_NO_THROW(img.parseXmp(data.size(), 0));
}

// Test: Empty IO with start=0 length=0
TEST_F(BmffImageParseXmpTest_1198, EmptyIoZeroStartZeroLength_1198) {
    auto memIo = std::make_unique<MemoryIo>();

    BmffImage img(std::move(memIo), false, 100);

    EXPECT_NO_THROW(img.parseXmp(0, 0));
    EXPECT_TRUE(img.xmpData().empty());
}

// Test: Empty IO with start > 0 -> should throw
TEST_F(BmffImageParseXmpTest_1198, EmptyIoNonZeroStart_1198) {
    auto memIo = std::make_unique<MemoryIo>();

    BmffImage img(std::move(memIo), false, 100);

    EXPECT_THROW(img.parseXmp(0, 1), Error);
}

// Test: Empty IO with length > 0 and start=0 -> should throw
TEST_F(BmffImageParseXmpTest_1198, EmptyIoNonZeroLength_1198) {
    auto memIo = std::make_unique<MemoryIo>();

    BmffImage img(std::move(memIo), false, 100);

    EXPECT_THROW(img.parseXmp(1, 0), Error);
}

// Test: Invalid/garbage XMP content should throw
TEST_F(BmffImageParseXmpTest_1198, InvalidXmpContentHandled_1198) {
    // Non-XML garbage that XmpParser::decode might handle gracefully
    // or might throw - depends on implementation
    const std::string data = "this is not valid xmp at all!!!!";
    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(data.data()), data.size());

    BmffImage img(std::move(memIo), false, 100);

    // The function catches exceptions from XmpParser::decode and rethrows as kerFailedToReadImageData
    // However, XmpParser::decode might not throw for arbitrary strings, it might just return an error code
    // This test just verifies no crash occurs
    try {
        img.parseXmp(data.size(), 0);
    } catch (const Error&) {
        // Expected if XmpParser::decode throws
    }
}

// Test: Partial read from data with non-zero start
TEST_F(BmffImageParseXmpTest_1198, PartialReadWithNonZeroStart_1198) {
    // Put some padding then empty XMP
    std::string padding(10, 'X');
    std::string xmp = "<x:xmpmeta xmlns:x='adobe:ns:meta/'/>";
    std::string combined = padding + xmp;

    auto memIo = std::make_unique<MemoryIo>(
        reinterpret_cast<const byte*>(combined.data()), combined.size());

    BmffImage img(std::move(memIo), false, 100);

    EXPECT_NO_THROW(img.parseXmp(xmp.size(), padding.size()));
}
