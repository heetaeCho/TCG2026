// TEST_ID: 241
#include <gtest/gtest.h>

#include "tinyxml2.h"

using namespace tinyxml2;

class XMLElementBoolSetTextTest_241 : public ::testing::Test {
protected:
    XMLDocument doc_;
    XMLElement* elem_ = nullptr;

    void SetUp() override {
        elem_ = doc_.NewElement("root");
        ASSERT_NE(elem_, nullptr);
        doc_.InsertEndChild(elem_);
    }

    static std::string BoolToExpectedString(bool v) {
        char buf[200] = {};
        XMLUtil::ToStr(v, buf, sizeof(buf));
        return std::string(buf);
    }
};

TEST_F(XMLElementBoolSetTextTest_241, SetTextTrueMatchesXMLUtilToStr_241) {
    elem_->SetText(true);

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, BoolToExpectedString(true).c_str());
}

TEST_F(XMLElementBoolSetTextTest_241, SetTextFalseMatchesXMLUtilToStr_241) {
    elem_->SetText(false);

    const char* text = elem_->GetText();
    ASSERT_NE(text, nullptr);
    EXPECT_STREQ(text, BoolToExpectedString(false).c_str());
}

TEST_F(XMLElementBoolSetTextTest_241, SetTextOverwritesPreviousValue_241) {
    elem_->SetText(true);
    ASSERT_NE(elem_->GetText(), nullptr);
    EXPECT_STREQ(elem_->GetText(), BoolToExpectedString(true).c_str());

    elem_->SetText(false);
    ASSERT_NE(elem_->GetText(), nullptr);
    EXPECT_STREQ(elem_->GetText(), BoolToExpectedString(false).c_str());
}

TEST_F(XMLElementBoolSetTextTest_241, QueryBoolTextReflectsSetTextTrue_241) {
    elem_->SetText(true);

    bool out = false;
    const XMLError err = elem_->QueryBoolText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_TRUE(out);
}

TEST_F(XMLElementBoolSetTextTest_241, QueryBoolTextReflectsSetTextFalse_241) {
    elem_->SetText(false);

    bool out = true;
    const XMLError err = elem_->QueryBoolText(&out);
    EXPECT_EQ(err, XML_SUCCESS);
    EXPECT_FALSE(out);
}

TEST_F(XMLElementBoolSetTextTest_241, BoolTextReturnsValueAfterSetText_241) {
    elem_->SetText(true);
    EXPECT_TRUE(elem_->BoolText(false));   // default should be ignored when text is present

    elem_->SetText(false);
    EXPECT_FALSE(elem_->BoolText(true));   // default should be ignored when text is present
}

TEST_F(XMLElementBoolSetTextTest_241, QueryBoolTextWithNullOutParamReportsError_241) {
    elem_->SetText(true);

    // Observable error behavior through return code.
    const XMLError err = elem_->QueryBoolText(nullptr);
    EXPECT_NE(err, XML_SUCCESS);
}

TEST_F(XMLElementBoolSetTextTest_241, SetBoolSerializationAffectsSetTextOutput_241) {
    // This exercises an observable external interaction: SetText(bool) uses XMLUtil::ToStr(bool).
    // NOTE: XMLUtil::SetBoolSerialization is global; we reset to common defaults at the end.
    XMLUtil::SetBoolSerialization("YES", "NO");
    elem_->SetText(true);
    ASSERT_NE(elem_->GetText(), nullptr);
    EXPECT_STREQ(elem_->GetText(), "YES");

    elem_->SetText(false);
    ASSERT_NE(elem_->GetText(), nullptr);
    EXPECT_STREQ(elem_->GetText(), "NO");

    // Best-effort reset for test isolation.
    XMLUtil::SetBoolSerialization("true", "false");
}
