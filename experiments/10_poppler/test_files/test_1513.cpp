#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "CryptoSignBackend.h"



using namespace ::testing;

namespace CryptoSign {

    class MockSigningInterface : public SigningInterface {

    public:

        MOCK_METHOD(void, addData, (unsigned char *data_block, int data_len), (override));

        MOCK_METHOD(const SignatureType, signatureType, (), (const, override));

        MOCK_METHOD(const std::unique_ptr<X509CertificateInfo>, getCertificateInfo, (), (const, override));

        MOCK_METHOD(std::variant<std::vector<unsigned char>, SigningErrorMessage>, signDetached, (const std::string &password), (override));

    };

}



class HashFileRangeTest_1513 : public ::testing::Test {

protected:

    FILE* tempFile;

    CryptoSign::MockSigningInterface* mockHandler;



    void SetUp() override {

        tempFile = tmpfile();

        ASSERT_NE(tempFile, nullptr);

        mockHandler = new CryptoSign::MockSigningInterface();

    }



    void TearDown() override {

        fclose(tempFile);

        delete mockHandler;

    }

};



TEST_F(HashFileRangeTest_1513, HashingEmptyFileReturnsTrue_1513) {

    EXPECT_CALL(*mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(tempFile, mockHandler, 0, 0);

    EXPECT_TRUE(result);

}



TEST_F(HashFileRangeTest_1513, HashingNonEmptyFileCallsAddDataOnce_1513) {

    unsigned char data[] = "Hello";

    fwrite(data, sizeof(unsigned char), sizeof(data), tempFile);

    rewind(tempFile);



    EXPECT_CALL(*mockHandler, addData(_, sizeof(data))).Times(1);

    bool result = hashFileRange(tempFile, mockHandler, 0, sizeof(data));

    EXPECT_TRUE(result);

}



TEST_F(HashFileRangeTest_1513, HashingLargeFileCallsAddDataMultipleTimes_1513) {

    const int largeFileSize = 2 * 65536 + 1;

    unsigned char* data = new unsigned char[largeFileSize];

    memset(data, 'A', largeFileSize);

    fwrite(data, sizeof(unsigned char), largeFileSize, tempFile);

    rewind(tempFile);



    EXPECT_CALL(*mockHandler, addData(_, 65536)).Times(2);

    EXPECT_CALL(*mockHandler, addData(_, 1)).Times(1);

    bool result = hashFileRange(tempFile, mockHandler, 0, largeFileSize);

    EXPECT_TRUE(result);

    delete[] data;

}



TEST_F(HashFileRangeTest_1513, HashingWithNullHandlerReturnsFalse_1513) {

    EXPECT_CALL(*mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(tempFile, nullptr, 0, 65536);

    EXPECT_FALSE(result);

}



TEST_F(HashFileRangeTest_1513, HashingWithSeekFailureReturnsFalse_1513) {

    unsigned char data[] = "Hello";

    fwrite(data, sizeof(unsigned char), sizeof(data), tempFile);

    rewind(tempFile);



    EXPECT_CALL(*mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(reinterpret_cast<FILE*>(-1), mockHandler, 0, sizeof(data));

    EXPECT_FALSE(result);

}



TEST_F(HashFileRangeTest_1513, HashingWithFreadFailureReturnsFalse_1513) {

    unsigned char data[] = "Hello";

    fwrite(data, sizeof(unsigned char), sizeof(data), tempFile);

    rewind(tempFile);



    EXPECT_CALL(*mockHandler, addData(_, _)).Times(0);

    bool result = hashFileRange(tempFile, mockHandler, 0, sizeof(data) + 1);

    EXPECT_FALSE(result);

}
