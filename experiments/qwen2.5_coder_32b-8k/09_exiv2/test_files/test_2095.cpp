#include <gtest/gtest.h>

#include <gmock/gmock.h>



// Mocking dependencies if needed

class MockExpatAdapter : public ExpatAdapter {

public:

    MOCK_METHOD(void, CharacterDataHandler, (void* userData, XMP_StringPtr cData, int len), (override));

};



TEST_F(ExpatAdapterTest_2095, NormalCharacterDataHandling_2095) {

    XMLParserAdapter parser;

    ExpatAdapter adapter(&parser);

    const char* data = "Sample text";

    int length = 11;



    EXPECT_NO_THROW(adapter.CharacterDataHandler(&adapter, data, length));



    // Verify that the character data is added to the parse stack

    ASSERT_EQ(parser.parseStack.back()->content.size(), 1);

    EXPECT_EQ(parser.parseStack.back()->content[0]->value, "Sample text");

}



TEST_F(ExpatAdapterTest_2095, EmptyCharacterDataHandling_2095) {

    XMLParserAdapter parser;

    ExpatAdapter adapter(&parser);

    const char* data = nullptr;

    int length = 0;



    EXPECT_NO_THROW(adapter.CharacterDataHandler(&adapter, data, length));



    // Verify that an empty string node is added to the parse stack

    ASSERT_EQ(parser.parseStack.back()->content.size(), 1);

    EXPECT_EQ(parser.parseStack.back()->content[0]->value, "");

}



TEST_F(ExpatAdapterTest_2095, ZeroLengthCharacterDataHandling_2095) {

    XMLParserAdapter parser;

    ExpatAdapter adapter(&parser);

    const char* data = "Sample text";

    int length = 0;



    EXPECT_NO_THROW(adapter.CharacterDataHandler(&adapter, data, length));



    // Verify that an empty string node is added to the parse stack

    ASSERT_EQ(parser.parseStack.back()->content.size(), 1);

    EXPECT_EQ(parser.parseStack.back()->content[0]->value, "");

}



TEST_F(ExpatAdapterTest_2095, NullCharacterDataHandling_2095) {

    XMLParserAdapter parser;

    ExpatAdapter adapter(&parser);

    const char* data = nullptr;

    int length = 11;



    EXPECT_NO_THROW(adapter.CharacterDataHandler(&adapter, data, length));



    // Verify that an empty string node is added to the parse stack

    ASSERT_EQ(parser.parseStack.back()->content.size(), 1);

    EXPECT_EQ(parser.parseStack.back()->content[0]->value, "");

}



TEST_F(ExpatAdapterTest_2095, LargeCharacterDataHandling_2095) {

    XMLParserAdapter parser;

    ExpatAdapter adapter(&adapter);

    const char* data = "A very long string that exceeds typical buffer sizes to test edge cases.";

    int length = 68;



    EXPECT_NO_THROW(adapter.CharacterDataHandler(&adapter, data, length));



    // Verify that the character data is added to the parse stack

    ASSERT_EQ(parser.parseStack.back()->content.size(), 1);

    EXPECT_EQ(parser.parseStack.back()->content[0]->value, "A very long string that exceeds typical buffer sizes to test edge cases.");

}
