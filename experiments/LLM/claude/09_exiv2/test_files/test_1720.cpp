#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <exiv2/basicio.hpp>
#include <exiv2/xmpsidecar.hpp>
#include <cstring>

using namespace Exiv2;
using ::testing::_;
using ::testing::Return;
using ::testing::Invoke;
using ::testing::AtLeast;

// We'll use MemIo for testing since it's a concrete BasicIo implementation
class IsXmpTypeTest_1720 : public ::testing::Test {
protected:
    void SetUp() override {}
    void TearDown() override {}
    
    // Helper to create MemIo with given content
    std::unique_ptr<MemIo> createMemIo(const std::string& content) {
        auto io = std::make_unique<MemIo>();
        if (!content.empty()) {
            io->write(reinterpret_cast<const byte*>(content.data()), content.size());
            io->seek(0, BasicIo::beg);
        }
        return io;
    }
    
    std::unique_ptr<MemIo> createMemIo(const byte* data, size_t size) {
        auto io = std::make_unique<MemIo>();
        if (size > 0) {
            io->write(data, size);
            io->seek(0, BasicIo::beg);
        }
        return io;
    }
};

// The xmlHeader used internally:
// "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
// xmlHdrCnt = 54

// Test: Empty file returns false
TEST_F(IsXmpTypeTest_1720, EmptyFileReturnsFalse_1720) {
    auto io = createMemIo("");
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: Just the xmlHeader (the xpacket header) exactly should return true
// because iIo.read reads xmlHdrCnt+1 bytes, and if eof and matches xmlHeader, returns true
TEST_F(IsXmpTypeTest_1720, ExactXmlHeaderReturnsTrue_1720) {
    std::string xmlHeader = "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n";
    auto io = createMemIo(xmlHeader);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: Valid xpacket declaration at start
TEST_F(IsXmpTypeTest_1720, ValidXpacketAtStartReturnsTrue_1720) {
    std::string content = "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n"
                          "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
                          "some xmp content here padding padding padding";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: Valid x:xmpmeta element at start without xpacket
TEST_F(IsXmpTypeTest_1720, XmpmmetaElementReturnsTrue_1720) {
    // Need enough data (at least 80 bytes after reading past xmlHdrCnt+1)
    std::string content = "<x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
                          "some xmp content here with enough padding to fill buffer completely yes";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: XML declaration followed by xpacket
TEST_F(IsXmpTypeTest_1720, XmlDeclFollowedByXpacketReturnsTrue_1720) {
    std::string content = "<?xml version=\"1.0\"?><?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: XML declaration followed by x:xmpmeta
TEST_F(IsXmpTypeTest_1720, XmlDeclFollowedByXmpmmetaReturnsTrue_1720) {
    std::string content = "<?xml version=\"1.0\"?><x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
                          "padding padding padding padding padding";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: BOM followed by xpacket
TEST_F(IsXmpTypeTest_1720, BomFollowedByXpacketReturnsTrue_1720) {
    std::string bom = "\xef\xbb\xbf";
    std::string content = bom + "<?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding padding";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: BOM followed by xml declaration and xmpmeta
TEST_F(IsXmpTypeTest_1720, BomFollowedByXmlDeclAndXmpmmetaReturnsTrue_1720) {
    std::string bom = "\xef\xbb\xbf";
    std::string content = bom + "<?xml version=\"1.0\"?><x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
                          "pad pad pad pad pad";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: Random/non-XMP content returns false
TEST_F(IsXmpTypeTest_1720, RandomContentReturnsFalse_1720) {
    std::string content = "This is just some random text that is definitely not XMP."
                          " More text to ensure we have enough bytes to read.";
    auto io = createMemIo(content);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: HTML content returns false
TEST_F(IsXmpTypeTest_1720, HtmlContentReturnsFalse_1720) {
    std::string content = "<html><head><title>Test</title></head><body>Hello</body></html>"
                          " extra padding to fill up the buffer requirement.";
    auto io = createMemIo(content);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: advance=false should restore position on success
TEST_F(IsXmpTypeTest_1720, AdvanceFalseRestoresPositionOnFailure_1720) {
    std::string content = "This is not XMP content and should fail the test easily."
                          " Additional padding to make sure buffer is full enough.";
    auto io = createMemIo(content);
    size_t posBefore = io->tell();
    bool result = isXmpType(*io, false);
    EXPECT_FALSE(result);
    // Position should be restored on failure
    EXPECT_EQ(io->tell(), posBefore);
}

// Test: advance=true with valid content should advance position
TEST_F(IsXmpTypeTest_1720, AdvanceTrueAdvancesPositionOnSuccess_1720) {
    std::string content = "<?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding padding padding padding";
    auto io = createMemIo(content);
    size_t posBefore = io->tell();
    bool result = isXmpType(*io, true);
    EXPECT_TRUE(result);
    // Position should have advanced
    EXPECT_NE(io->tell(), posBefore);
}

// Test: advance=false with valid content should restore position (with BOM adjustment)
TEST_F(IsXmpTypeTest_1720, AdvanceFalseRestoresPositionOnSuccessWithoutBom_1720) {
    std::string content = "<?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding padding padding padding";
    auto io = createMemIo(content);
    bool result = isXmpType(*io, false);
    EXPECT_TRUE(result);
    // When advance=false and rc=true, seek is NOT called, so position stays advanced
    // Actually re-reading the code: "if (!advance || !rc)" means if advance is false, it seeks back
    EXPECT_EQ(io->tell(), static_cast<size_t>(0));
}

// Test: Very short file (less than xmlHdrCnt bytes) that doesn't match
TEST_F(IsXmpTypeTest_1720, ShortNonMatchingFileReturnsFalse_1720) {
    std::string content = "short";
    auto io = createMemIo(content);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: File that is exactly the xml declaration only
TEST_F(IsXmpTypeTest_1720, XmlDeclarationOnlyReturnsFalse_1720) {
    // "<?xml version=\"1.0\"?>" alone, not followed by xpacket or x:xmpmeta
    // Need enough data for the full 80-byte read though
    std::string content = "<?xml version=\"1.0\"?><sometag>not xmp content here at all. more padding needed!!";
    auto io = createMemIo(content);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: File with xml declaration followed by something other than xpacket/xmpmeta
TEST_F(IsXmpTypeTest_1720, XmlDeclFollowedByOtherTagReturnsFalse_1720) {
    std::string content = "<?xml version=\"1.0\"?><root><child>data</child></root>"
                          "extra padding to ensure full buffer read is possible!";
    auto io = createMemIo(content);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: xpacket with BOM prefix and advance=true
TEST_F(IsXmpTypeTest_1720, BomXpacketAdvanceTrueReturnsTrue_1720) {
    std::string bom = "\xef\xbb\xbf";
    std::string content = bom + "<?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding padding padding";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, true));
}

// Test: Binary garbage returns false
TEST_F(IsXmpTypeTest_1720, BinaryGarbageReturnsFalse_1720) {
    byte data[100];
    for (int i = 0; i < 100; i++) {
        data[i] = static_cast<byte>(i + 128);  // High bytes
    }
    auto io = createMemIo(data, 100);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: Null bytes at start returns false
TEST_F(IsXmpTypeTest_1720, NullBytesReturnsFalse_1720) {
    byte data[100] = {};
    memset(data, 0, 100);
    auto io = createMemIo(data, 100);
    EXPECT_FALSE(isXmpType(*io, false));
}

// Test: xmpmeta with BOM and XML declaration
TEST_F(IsXmpTypeTest_1720, BomXmlDeclXmpmmetaReturnsTrue_1720) {
    std::string bom = "\xef\xbb\xbf";
    std::string content = bom + "<?xml version=\"1.0\"?><x:xmpmeta xmlns:x=\"adobe:ns:meta/\">"
                          "pad";
    // Ensure enough length
    while (content.size() < 120) content += " ";
    auto io = createMemIo(content);
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: Calling isXmpType multiple times on the same IO with advance=false
TEST_F(IsXmpTypeTest_1720, MultipleCallsWithAdvanceFalse_1720) {
    std::string content = "<?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding padding padding padding";
    auto io = createMemIo(content);
    
    EXPECT_TRUE(isXmpType(*io, false));
    // Should be able to call again since position was restored
    EXPECT_TRUE(isXmpType(*io, false));
}

// Test: File with just the partial xmlHeader (less than xmlHdrCnt)
TEST_F(IsXmpTypeTest_1720, PartialXmlHeaderReturnsFalse_1720) {
    std::string content = "<?xpacket begin=\"\xef\xbb\xbf\" id=";  // Truncated
    auto io = createMemIo(content);
    // This is shorter than xmlHdrCnt (54), so read will hit EOF
    // But the first 10 chars "<?xpacket " don't match xmlHeader fully at xmlHdrCnt length
    bool result = isXmpType(*io, false);
    // The file starts with "<?xpacket" which is the xmlHeader prefix, 
    // but it's short. The eof check with strncmp to xmlHeader won't match the full header.
    EXPECT_FALSE(result);
}

// Test: Exactly xmlHdrCnt bytes of the xpacket header (triggers EOF path with match)
TEST_F(IsXmpTypeTest_1720, ExactXmlHdrCntBytesReturnsTrue_1720) {
    // The xmlHeader is 54 chars. We need exactly xmlHdrCnt bytes that match.
    std::string xmlHeader = "<?xpacket begin=\"\xef\xbb\xbf\" id=\"W5M0MpCehiHzreSzNTczkc9d\"?>\n";
    // xmlHdrCnt = 54
    // The function reads xmlHdrCnt+1 = 55 bytes. If we provide exactly 54 bytes, 
    // the read of 55 bytes will hit EOF with 54 bytes read.
    std::string content = xmlHeader.substr(0, 54);
    auto io = createMemIo(content);
    bool result = isXmpType(*io, false);
    EXPECT_TRUE(result);
}

// Test: Content starting with spaces (not matching anything)
TEST_F(IsXmpTypeTest_1720, LeadingSpacesReturnsFalse_1720) {
    std::string content = "   <?xpacket begin=\"\" id=\"test\"?>"
                          "padding padding padding padding padding padding padding";
    auto io = createMemIo(content);
    EXPECT_FALSE(isXmpType(*io, false));
}
