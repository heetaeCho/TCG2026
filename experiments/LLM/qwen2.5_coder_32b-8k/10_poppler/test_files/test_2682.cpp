#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include "TestProjects/poppler/utils/pdfsig.cc"

#include "TestProjects/poppler/Form.h"



using namespace testing;



class FormFieldSignatureMock : public FormFieldSignature {

public:

    MOCK_CONST_METHOD0(getSignature, const std::vector<unsigned char>&());

};



TEST(dumpSignatureTest_2682, EmptySignature_ReturnsFalse_2682) {

    FormFieldSignatureMock formFieldSignature;

    EXPECT_CALL(formFieldSignature, getSignature()).WillOnce(Return(std::vector<unsigned char>()));

    

    bool result = dumpSignature(1, &formFieldSignature, "testfile");

    

    EXPECT_FALSE(result);

}



TEST(dumpSignatureTest_2682, NonEmptySignature_ReturnsTrueAndWritesToFile_2682) {

    std::vector<unsigned char> signatureData = {0x01, 0x02, 0x03};

    FormFieldSignatureMock formFieldSignature;

    EXPECT_CALL(formFieldSignature, getSignature()).WillRepeatedly(ReturnRef(signatureData));

    

    bool result = dumpSignature(1, &formFieldSignature, "testfile");

    

    EXPECT_TRUE(result);

    // Verify that the file was created and contains the correct data

    std::ifstream infile("testfile1.sig", std::ios::binary | std::ios::ate);

    ASSERT_TRUE(infile.is_open());

    size_t fileSize = infile.tellg();

    infile.seekg(0, std::ios::beg);

    std::vector<unsigned char> fileData(fileSize);

    infile.read(reinterpret_cast<char*>(fileData.data()), fileSize);

    

    EXPECT_EQ(fileData, signatureData);

}



TEST(dumpSignatureTest_2682, FilenameWithExtension_CorrectPathGenerated_2682) {

    std::vector<unsigned char> signatureData = {0x01, 0x02, 0x03};

    FormFieldSignatureMock formFieldSignature;

    EXPECT_CALL(formFieldSignature, getSignature()).WillRepeatedly(ReturnRef(signatureData));

    

    bool result = dumpSignature(1, &formFieldSignature, "testfile.pdf");

    

    EXPECT_TRUE(result);

    // Verify that the file was created with the correct name

    std::ifstream infile("testfile1.sig", std::ios::binary | std::ios::ate);

    ASSERT_TRUE(infile.is_open());

}



TEST(dumpSignatureTest_2682, BoundaryCondition_SignatureNumberZero_ReturnsFalseAndDoesNotWriteToFile_2682) {

    FormFieldSignatureMock formFieldSignature;

    EXPECT_CALL(formFieldSignature, getSignature()).WillOnce(Return(std::vector<unsigned char>({0x01})));

    

    bool result = dumpSignature(0, &formFieldSignature, "testfile");

    

    EXPECT_FALSE(result);

    // Verify that the file was not created

    std::ifstream infile("testfile0.sig", std::ios::binary | std::ios::ate);

    ASSERT_FALSE(infile.is_open());

}



TEST(dumpSignatureTest_2682, BoundaryCondition_SignatureNumberNegative_ReturnsFalseAndDoesNotWriteToFile_2682) {

    FormFieldSignatureMock formFieldSignature;

    EXPECT_CALL(formFieldSignature, getSignature()).WillOnce(Return(std::vector<unsigned char>({0x01})));

    

    bool result = dumpSignature(-1, &formFieldSignature, "testfile");

    

    EXPECT_FALSE(result);

    // Verify that the file was not created

    std::ifstream infile("testfile-1.sig", std::ios::binary | std::ios::ate);

    ASSERT_FALSE(infile.is_open());

}
