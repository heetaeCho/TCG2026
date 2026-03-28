#include <gtest/gtest.h>
#include <sstream>
#include <string>

#include <exiv2/exiv2.hpp>

class XmpdatumWriteTest_1299 : public ::testing::Test {
protected:
    void SetUp() override {
        Exiv2::XmpParser::initialize();
    }

    void TearDown() override {
        Exiv2::XmpParser::terminate();
    }
};

TEST_F(XmpdatumWriteTest_1299, WriteReturnsOutputStream_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test Title";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    std::ostream& result = it->write(os, nullptr);

    // write should return the same stream reference
    EXPECT_EQ(&result, &os);
}

TEST_F(XmpdatumWriteTest_1299, WriteStringValue_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Hello World";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    it->write(os, nullptr);

    std::string output = os.str();
    // The output should contain the value we set
    EXPECT_FALSE(output.empty());
    EXPECT_NE(output.find("Hello World"), std::string::npos);
}

TEST_F(XmpdatumWriteTest_1299, WriteWithNullExifData_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.description"] = "A description";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    // Should not crash with nullptr ExifData
    EXPECT_NO_THROW(it->write(os, nullptr));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(XmpdatumWriteTest_1299, WriteWithExifDataPointer_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.creator"] = "Test Author";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.creator"));
    ASSERT_NE(it, xmpData.end());

    Exiv2::ExifData exifData;
    std::ostringstream os;
    EXPECT_NO_THROW(it->write(os, &exifData));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(XmpdatumWriteTest_1299, WriteEmptyStringValue_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    EXPECT_NO_THROW(it->write(os, nullptr));
}

TEST_F(XmpdatumWriteTest_1299, WriteMultipleTimes_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Title1";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    it->write(os, nullptr);
    std::string first = os.str();

    std::ostringstream os2;
    it->write(os2, nullptr);
    std::string second = os2.str();

    // Writing the same datum twice should produce the same output
    EXPECT_EQ(first, second);
}

TEST_F(XmpdatumWriteTest_1299, WriteDifferentXmpProperties_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "My Title";
    xmpData["Xmp.dc.subject"] = "Subject1";

    auto itTitle = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    auto itSubject = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.subject"));
    ASSERT_NE(itTitle, xmpData.end());
    ASSERT_NE(itSubject, xmpData.end());

    std::ostringstream osTitle, osSubject;
    itTitle->write(osTitle, nullptr);
    itSubject->write(osSubject, nullptr);

    EXPECT_NE(osTitle.str(), osSubject.str());
}

TEST_F(XmpdatumWriteTest_1299, WriteUnicodeValue_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "日本語テスト";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    EXPECT_NO_THROW(it->write(os, nullptr));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(XmpdatumWriteTest_1299, WriteLongStringValue_1299) {
    Exiv2::XmpData xmpData;
    std::string longStr(10000, 'A');
    xmpData["Xmp.dc.description"] = longStr;

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.description"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    EXPECT_NO_THROW(it->write(os, nullptr));
    EXPECT_FALSE(os.str().empty());
}

TEST_F(XmpdatumWriteTest_1299, WriteSpecialCharacters_1299) {
    Exiv2::XmpData xmpData;
    xmpData["Xmp.dc.title"] = "Test <>&\"' special chars";

    auto it = xmpData.findKey(Exiv2::XmpKey("Xmp.dc.title"));
    ASSERT_NE(it, xmpData.end());

    std::ostringstream os;
    EXPECT_NO_THROW(it->write(os, nullptr));
    EXPECT_FALSE(os.str().empty());
}
