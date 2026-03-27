#include <gtest/gtest.h>

#include "poppler/StructElement.h"

#include "poppler/Object.h"

#include <cstdio>

#include <memory>



using namespace std;



class MockObject : public Object {

public:

    MOCK_METHOD(void, print, (FILE * f), (const override));

};



class MockAttribute : public Attribute {

public:

    MockAttribute(Type type, Object* value) : Attribute(type, value) {}

    MOCK_METHOD(const char*, getTypeName, (), (const override));

    MOCK_METHOD(const char*, getOwnerName, (), (const override));

    MOCK_METHOD(const Object*, getValue, (), (const override));

    MOCK_METHOD(const char*, getName, (), (const override));

    MOCK_METHOD(unsigned int, getRevision, (), (const override));

    MOCK_METHOD(bool, isHidden, (), (const override));

    MOCK_METHOD(const char*, getFormattedValue, (), (const override));

};



class PrintAttributeTest : public ::testing::Test {

protected:

    MockObject mockObject;

    MockAttribute mockAttribute;



    void SetUp() override {

        EXPECT_CALL(mockObject, print(testing::_)).WillOnce([](FILE *f) { fprintf(f, "mocked_value"); });

        EXPECT_CALL(mockAttribute, getTypeName()).WillRepeatedly(testing::Return("MockType"));

        EXPECT_CALL(mockAttribute, getName()).WillRepeatedly(testing::Return("MockName"));

        EXPECT_CALL(mockAttribute, getValue()).WillRepeatedly(testing::Return(&mockObject));

    }

};



TEST_F(PrintAttributeTest, NormalOperation_2668) {

    testing::internal::CaptureStdout();

    printAttribute(&mockAttribute, 0);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " /MockType (MockName) mocked_value\n");

}



TEST_F(PrintAttributeTest, NoFormattedValue_2668) {

    EXPECT_CALL(mockAttribute, getFormattedValue()).WillOnce(testing::Return(nullptr));

    testing::internal::CaptureStdout();

    printAttribute(&mockAttribute, 0);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " /MockType (MockName) mocked_value\n");

}



TEST_F(PrintAttributeTest, WithFormattedValue_2668) {

    GooString formattedValue("formatted_mocked_value");

    EXPECT_CALL(mockAttribute, getFormattedValue()).WillOnce(testing::Return(formattedValue.getCString()));

    testing::internal::CaptureStdout();

    printAttribute(&mockAttribute, 0);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " /MockType (MockName) mocked_value \"formatted_mocked_value\"\n");

}



TEST_F(PrintAttributeTest, HiddenAttribute_2668) {

    EXPECT_CALL(mockAttribute, isHidden()).WillOnce(testing::Return(true));

    testing::internal::CaptureStdout();

    printAttribute(&mockAttribute, 0);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, " /MockType (MockName) mocked_value [hidden]\n");

}



TEST_F(PrintAttributeTest, Indentation_2668) {

    testing::internal::CaptureStdout();

    printAttribute(&mockAttribute, 4);

    string output = testing::internal::GetCapturedStdout();

    EXPECT_EQ(output, "    /MockType (MockName) mocked_value\n");

}
