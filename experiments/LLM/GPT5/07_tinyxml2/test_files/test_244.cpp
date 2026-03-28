// TEST_ID: 244
#include <climits>
#include <string>

#include "gtest/gtest.h"
#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementQueryIntTextTest_244 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }

    void SetText(const char* text) {
        ASSERT_NE(elem_, nullptr);
        elem_->DeleteChildren();
        elem_->SetText(text);
    }

    void MakeFirstChildElementNotText() {
        ASSERT_NE(elem_, nullptr);
        elem_->DeleteChildren();
        elem_->InsertNewChildElement("child"); // first child is an element, not a text node
    }

    void MakeNoChildren() {
        ASSERT_NE(elem_, nullptr);
        elem_->DeleteChildren();
    }
};

TEST_F(XMLElementQueryIntTextTest_244, ReturnsSuccessAndParsesZero_244) {
    SetText("0");
    int v = 12345;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, 0);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsSuccessAndParsesNegativeNumber_244) {
    SetText("-7");
    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, -7);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsSuccessAndParsesIntMax_244) {
    const std::string s = std::to_string(INT_MAX);
    SetText(s.c_str());

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, INT_MAX);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsSuccessAndParsesIntMin_244) {
    const std::string s = std::to_string(INT_MIN);
    SetText(s.c_str());

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_EQ(v, INT_MIN);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsCanNotConvertTextForNonNumeric_244) {
    SetText("not_an_int");

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsCanNotConvertTextForEmptyString_244) {
    SetText("");

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsNoTextNodeWhenNoChildren_244) {
    MakeNoChildren();

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsNoTextNodeWhenFirstChildIsNotText_244) {
    MakeFirstChildElementNotText();

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_NO_TEXT_NODE);
}

TEST_F(XMLElementQueryIntTextTest_244, ReturnsCanNotConvertTextForMixedNumericAndLetters_244) {
    SetText("123abc");

    int v = 0;
    const XMLError err = elem_->QueryIntText(&v);

    EXPECT_EQ(err, XML_CAN_NOT_CONVERT_TEXT);
}
