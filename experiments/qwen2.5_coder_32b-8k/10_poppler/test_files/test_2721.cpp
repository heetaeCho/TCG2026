#include <gtest/gtest.h>

#include <string>



// Assuming the function myStringReplace exists and is used internally by myXmlTokenReplace

extern std::string myStringReplace(const std::string& str, const std::string& from, const std::string& to);



// Mocking myStringReplace for verification purposes

class MockStringReplacer {

public:

    MOCK_CONST_METHOD3(myStringReplaceMock, std::string(const std::string&, const std::string&, const std::string&));

};



std::string myXmlTokenReplace(const char *inString) {

    static MockStringReplacer mock;

    std::string myString(inString);

    myString = mock.myStringReplaceMock(myString, "&", "&amp;");

    myString = mock.myStringReplaceMock(myString, "'", "&apos;");

    myString = mock.myStringReplaceMock(myString, "\"", "&quot;");

    myString = mock.myStringReplaceMock(myString, "<", "&lt;");

    myString = mock.myStringReplaceMock(myString, ">", "&gt;");

    return myString;

}



// Test fixture

class MyXmlTokenReplaceTest_2721 : public ::testing::Test {

protected:

    MockStringReplacer* mock;



    void SetUp() override {

        mock = new MockStringReplacer();

    }



    void TearDown() override {

        delete mock;

    }

};



TEST_F(MyXmlTokenReplaceTest_2721, NormalOperation_2721) {

    EXPECT_CALL(*mock, myStringReplaceMock("Hello & World", "&", "&amp;")).WillOnce(::testing::Return("Hello &amp; World"));

    EXPECT_CALL(*mock, myStringReplaceMock("Hello &amp; World", "'", "&apos;")).WillOnce(::testing::Return("Hello &amp; World"));

    EXPECT_CALL(*mock, myStringReplaceMock("Hello &amp; World", "\"", "&quot;")).WillOnce(::testing::Return("Hello &amp; World"));

    EXPECT_CALL(*mock, myStringReplaceMock("Hello &amp; World", "<", "&lt;")).WillOnce(::testing::Return("Hello &amp; World"));

    EXPECT_CALL(*mock, myStringReplaceMock("Hello &amp; World", ">", "&gt;")).WillOnce(::testing::Return("Hello &amp; World"));



    std::string result = myXmlTokenReplace("Hello & World");

    EXPECT_EQ(result, "Hello &amp; World");

}



TEST_F(MyXmlTokenReplaceTest_2721, BoundaryConditions_EmptyString_2721) {

    EXPECT_CALL(*mock, myStringReplaceMock("", "&", "&amp;")).WillOnce(::testing::Return(""));

    EXPECT_CALL(*mock, myStringReplaceMock("", "'", "&apos;")).WillOnce(::testing::Return(""));

    EXPECT_CALL(*mock, myStringReplaceMock("", "\"", "&quot;")).WillOnce(::testing::Return(""));

    EXPECT_CALL(*mock, myStringReplaceMock("", "<", "&lt;")).WillOnce(::testing::Return(""));

    EXPECT_CALL(*mock, myStringReplaceMock("", ">", "&gt;")).WillOnce(::testing::Return(""));



    std::string result = myXmlTokenReplace("");

    EXPECT_EQ(result, "");

}



TEST_F(MyXmlTokenReplaceTest_2721, BoundaryConditions_SingleCharacter_2721) {

    EXPECT_CALL(*mock, myStringReplaceMock("&", "&", "&amp;")).WillOnce(::testing::Return("&amp;"));

    EXPECT_CALL(*mock, myStringReplaceMock("&amp;", "'", "&apos;")).WillOnce(::testing::Return("&amp;"));

    EXPECT_CALL(*mock, myStringReplaceMock("&amp;", "\"", "&quot;")).WillOnce(::testing::Return("&amp;"));

    EXPECT_CALL(*mock, myStringReplaceMock("&amp;", "<", "&lt;")).WillOnce(::testing::Return("&amp;"));

    EXPECT_CALL(*mock, myStringReplaceMock("&amp;", ">", "&gt;")).WillOnce(::testing::Return("&amp;"));



    std::string result = myXmlTokenReplace("&");

    EXPECT_EQ(result, "&amp;");

}



TEST_F(MyXmlTokenReplaceTest_2721, ExceptionalCases_NoSpecialCharacters_2721) {

    EXPECT_CALL(*mock, myStringReplaceMock("NoSpecialChars", "&", "&amp;")).WillOnce(::testing::Return("NoSpecialChars"));

    EXPECT_CALL(*mock, myStringReplaceMock("NoSpecialChars", "'", "&apos;")).WillOnce(::testing::Return("NoSpecialChars"));

    EXPECT_CALL(*mock, myStringReplaceMock("NoSpecialChars", "\"", "&quot;")).WillOnce(::testing::Return("NoSpecialChars"));

    EXPECT_CALL(*mock, myStringReplaceMock("NoSpecialChars", "<", "&lt;")).WillOnce(::testing::Return("NoSpecialChars"));

    EXPECT_CALL(*mock, myStringReplaceMock("NoSpecialChars", ">", "&gt;")).WillOnce(::testing::Return("NoSpecialChars"));



    std::string result = myXmlTokenReplace("NoSpecialChars");

    EXPECT_EQ(result, "NoSpecialChars");

}



TEST_F(MyXmlTokenReplaceTest_2721, VerificationOfExternalInteractions_AllTokens_2721) {

    EXPECT_CALL(*mock, myStringReplaceMock("All & ' \" < > Tokens", "&", "&amp;")).WillOnce(::testing::Return("All &amp; ' \" < > Tokens"));

    EXPECT_CALL(*mock, myStringReplaceMock("All &amp; ' \" < > Tokens", "'", "&apos;")).WillOnce(::testing::Return("All &amp; &apos; \" < > Tokens"));

    EXPECT_CALL(*mock, myStringReplaceMock("All &amp; &apos; \" < > Tokens", "\"", "&quot;")).WillOnce(::testing::Return("All &amp; &apos; &quot; < > Tokens"));

    EXPECT_CALL(*mock, myStringReplaceMock("All &amp; &apos; &quot; < > Tokens", "<", "&lt;")).WillOnce(::testing::Return("All &amp; &apos; &quot; &lt; > Tokens"));

    EXPECT_CALL(*mock, myStringReplaceMock("All &amp; &apos; &quot; &lt; > Tokens", ">", "&gt;")).WillOnce(::testing::Return("All &amp; &apos; &quot; &lt; &gt; Tokens"));



    std::string result = myXmlTokenReplace("All & ' \" < > Tokens");

    EXPECT_EQ(result, "All &amp; &apos; &quot; &lt; &gt; Tokens");

}
