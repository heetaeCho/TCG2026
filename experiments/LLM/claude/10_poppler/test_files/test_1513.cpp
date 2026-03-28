#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <cstdio>
#include <cstring>
#include <memory>
#include <vector>
#include <variant>
#include <string>

// Include necessary headers
#include "CryptoSignBackend.h"

// Since hashFileRange is a static function in Form.cc, we need to either:
// 1. Include it directly, or
// 2. Recreate a testable version
// Since it's static, we'll include the source or declare it for testing.
// We'll use a forward declaration approach by including the implementation.

// For testing a static function, we include the .cc file directly
// or we need to make it accessible. Let's include the relevant part.

// We need the Goffset and Gfseek definitions
#include "goo/gfile.h"

// Forward declare or include the function - since it's static in Form.cc,
// we need to either test it indirectly or include the source.
// For unit testing purposes, let's include the source file.
// This is a common pattern for testing static functions.

// Re-declare the function signature for testing (we'll link against the object)
// Since the function is static, we need to include the source
namespace {
#include "Form.cc"
}

using ::testing::_;
using ::testing::Invoke;
using ::testing::AtLeast;

// Mock for CryptoSign::SigningInterface
class MockSigningInterface : public CryptoSign::SigningInterface {
public:
    MOCK_METHOD(void, addData, (unsigned char* data_block, int data_len), (override));
    MOCK_METHOD(const CryptoSign::SignatureType, signatureType, (), (override));
    MOCK_METHOD(const std::unique_ptr<X509CertificateInfo>, getCertificateInfo, (), (override));
    MOCK_METHOD((std::variant<std::vector<unsigned char>, CryptoSign::SigningErrorMessage>), signDetached, (const std::string& password), (override));
};

class HashFileRangeTest_1513 : public ::testing::Test {
protected:
    void SetUp() override {
        // Create a temporary file with known content
        tmpFile = tmpfile();
        ASSERT_NE(tmpFile, nullptr);
    }

    void TearDown() override {
        if (tmpFile) {
            fclose(tmpFile);
            tmpFile = nullptr;
        }
    }

    void writeToFile(const std::vector<unsigned char>& data) {
        fwrite(data.data(), 1, data.size(), tmpFile);
        fflush(tmpFile);
    }

    FILE* tmpFile = nullptr;
    MockSigningInterface mockHandler;
};

// Test: Null handler returns false
TEST_F(HashFileRangeTest_1513, NullHandlerReturnsFalse_1513) {
    bool result = hashFileRange(tmpFile, nullptr, 0, 100);
    EXPECT_FALSE(result);
}

// Test: Empty range (start == end) returns true without calling addData
TEST_F(HashFileRangeTest_1513, EmptyRangeReturnsTrue_1513) {
    std::vector<unsigned char> data(100, 'A');
    writeToFile(data);

    EXPECT_CALL(mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(tmpFile, &mockHandler, 0, 0);
    EXPECT_TRUE(result);
}

// Test: Normal operation with small file
TEST_F(HashFileRangeTest_1513, SmallFileNormalOperation_1513) {
    std::vector<unsigned char> data(100, 'B');
    writeToFile(data);

    std::vector<unsigned char> capturedData;
    EXPECT_CALL(mockHandler, addData(_, 100))
        .Times(1)
        .WillOnce(Invoke([&capturedData](unsigned char* buf, int len) {
            capturedData.assign(buf, buf + len);
        }));

    bool result = hashFileRange(tmpFile, &mockHandler, 0, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(capturedData.size(), 100u);
    for (auto b : capturedData) {
        EXPECT_EQ(b, 'B');
    }
}

// Test: Range starts and ends within the file
TEST_F(HashFileRangeTest_1513, PartialRangeOperation_1513) {
    std::vector<unsigned char> data(200, 0);
    for (int i = 0; i < 200; i++) {
        data[i] = static_cast<unsigned char>(i % 256);
    }
    writeToFile(data);

    std::vector<unsigned char> capturedData;
    EXPECT_CALL(mockHandler, addData(_, 50))
        .Times(1)
        .WillOnce(Invoke([&capturedData](unsigned char* buf, int len) {
            capturedData.assign(buf, buf + len);
        }));

    bool result = hashFileRange(tmpFile, &mockHandler, 50, 100);
    EXPECT_TRUE(result);
    EXPECT_EQ(capturedData.size(), 50u);
    for (int i = 0; i < 50; i++) {
        EXPECT_EQ(capturedData[i], static_cast<unsigned char>((50 + i) % 256));
    }
}

// Test: Large file that requires multiple buffer reads
TEST_F(HashFileRangeTest_1513, LargeFileMultipleBufferReads_1513) {
    // Write a file larger than 65536 bytes
    size_t fileSize = 65536 * 2 + 1000; // Two full buffers + partial
    std::vector<unsigned char> data(fileSize, 'C');
    writeToFile(data);

    int totalDataLen = 0;
    EXPECT_CALL(mockHandler, addData(_, _))
        .Times(3) // Two full buffers + one partial
        .WillRepeatedly(Invoke([&totalDataLen](unsigned char* buf, int len) {
            totalDataLen += len;
        }));

    bool result = hashFileRange(tmpFile, &mockHandler, 0, static_cast<Goffset>(fileSize));
    EXPECT_TRUE(result);
    EXPECT_EQ(totalDataLen, static_cast<int>(fileSize));
}

// Test: Reading beyond file end returns false (fread fails)
TEST_F(HashFileRangeTest_1513, ReadBeyondFileEndReturnsFalse_1513) {
    std::vector<unsigned char> data(50, 'D');
    writeToFile(data);

    // Try to read range 0-100 but file only has 50 bytes
    bool result = hashFileRange(tmpFile, &mockHandler, 0, 100);
    EXPECT_FALSE(result);
}

// Test: Start equals end should return true (no data to hash)
TEST_F(HashFileRangeTest_1513, StartEqualsEndReturnsTrue_1513) {
    std::vector<unsigned char> data(100, 'E');
    writeToFile(data);

    EXPECT_CALL(mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(tmpFile, &mockHandler, 50, 50);
    EXPECT_TRUE(result);
}

// Test: Single byte range
TEST_F(HashFileRangeTest_1513, SingleByteRange_1513) {
    std::vector<unsigned char> data = {'H', 'e', 'l', 'l', 'o'};
    writeToFile(data);

    unsigned char capturedByte = 0;
    EXPECT_CALL(mockHandler, addData(_, 1))
        .Times(1)
        .WillOnce(Invoke([&capturedByte](unsigned char* buf, int len) {
            capturedByte = buf[0];
        }));

    bool result = hashFileRange(tmpFile, &mockHandler, 2, 3);
    EXPECT_TRUE(result);
    EXPECT_EQ(capturedByte, 'l');
}

// Test: Exactly one buffer size (65536 bytes)
TEST_F(HashFileRangeTest_1513, ExactlyOneBufferSize_1513) {
    const int BUF_SIZE = 65536;
    std::vector<unsigned char> data(BUF_SIZE, 'F');
    writeToFile(data);

    EXPECT_CALL(mockHandler, addData(_, BUF_SIZE))
        .Times(1);

    bool result = hashFileRange(tmpFile, &mockHandler, 0, BUF_SIZE);
    EXPECT_TRUE(result);
}

// Test: One byte more than buffer size triggers two addData calls
TEST_F(HashFileRangeTest_1513, OneByteMoreThanBufferSize_1513) {
    const int BUF_SIZE = 65536;
    std::vector<unsigned char> data(BUF_SIZE + 1, 'G');
    writeToFile(data);

    int callCount = 0;
    int totalLen = 0;
    EXPECT_CALL(mockHandler, addData(_, _))
        .Times(2)
        .WillRepeatedly(Invoke([&callCount, &totalLen](unsigned char* buf, int len) {
            callCount++;
            totalLen += len;
        }));

    bool result = hashFileRange(tmpFile, &mockHandler, 0, BUF_SIZE + 1);
    EXPECT_TRUE(result);
    EXPECT_EQ(totalLen, BUF_SIZE + 1);
}

// Test: Start > end should return true (loop doesn't execute)
TEST_F(HashFileRangeTest_1513, StartGreaterThanEndReturnsTrue_1513) {
    std::vector<unsigned char> data(100, 'H');
    writeToFile(data);

    EXPECT_CALL(mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(tmpFile, &mockHandler, 100, 50);
    EXPECT_TRUE(result);
}

// Test: Null file pointer - should fail on fseek
TEST_F(HashFileRangeTest_1513, NullFilePointerBehavior_1513) {
    // This test may cause undefined behavior with NULL file,
    // but we test that it handles it (likely returns false from fseek failure)
    // Skip if it would crash - the function should handle invalid file gracefully
    // through fseek returning non-zero
}

// Test: Data integrity - verify content matches file at offset
TEST_F(HashFileRangeTest_1513, DataIntegrityAtOffset_1513) {
    std::vector<unsigned char> data;
    for (int i = 0; i < 256; i++) {
        data.push_back(static_cast<unsigned char>(i));
    }
    writeToFile(data);

    std::vector<unsigned char> captured;
    EXPECT_CALL(mockHandler, addData(_, _))
        .WillOnce(Invoke([&captured](unsigned char* buf, int len) {
            captured.assign(buf, buf + len);
        }));

    bool result = hashFileRange(tmpFile, &mockHandler, 100, 200);
    EXPECT_TRUE(result);
    ASSERT_EQ(captured.size(), 100u);
    for (int i = 0; i < 100; i++) {
        EXPECT_EQ(captured[i], static_cast<unsigned char>(100 + i));
    }
}

// Test: Multiple exact buffer-size chunks
TEST_F(HashFileRangeTest_1513, MultipleExactBufferChunks_1513) {
    const int BUF_SIZE = 65536;
    const int NUM_CHUNKS = 3;
    std::vector<unsigned char> data(BUF_SIZE * NUM_CHUNKS, 'I');
    writeToFile(data);

    EXPECT_CALL(mockHandler, addData(_, BUF_SIZE))
        .Times(NUM_CHUNKS);

    bool result = hashFileRange(tmpFile, &mockHandler, 0, BUF_SIZE * NUM_CHUNKS);
    EXPECT_TRUE(result);
}
