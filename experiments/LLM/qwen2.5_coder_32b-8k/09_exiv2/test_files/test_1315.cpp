#include <gtest/gtest.h>

#include <gmock/gmock.h>

#include <Exiv2/xmp.hpp>

#include <string>

#include <map>



using namespace testing;

using namespace Exiv2;



class XmpNsDumperTest : public Test {

protected:

    std::map<std::string, std::string> nsMap;

};



TEST_F(XmpNsDumperTest_1315, NormalNamespace_1315) {

    const char* buffer = "xmp: http://ns.adobe.com/xap/1.0/";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_EQ(nsMap[""], "http://ns.adobe.com/xap/1.0");

}



TEST_F(XmpNsDumperTest_1315, NormalUri_1315) {

    nsMap[""] = "xmp";

    const char* buffer = "xmp:Title Info";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_EQ(nsMap["xmp"], "Title Info");

}



TEST_F(XmpNsDumperTest_1315, EmptyBuffer_1315) {

    const char* buffer = "";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_TRUE(nsMap.empty());

}



TEST_F(XmpNsDumperTest_1315, NonAsciiBuffer_1315) {

    const char* buffer = "xmp:\x80Title Info";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_TRUE(nsMap.empty());

}



TEST_F(XmpNsDumperTest_1315, InvalidUriWithoutNamespace_1315) {

    const char* buffer = "http://example.com";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_TRUE(nsMap.empty());

}



TEST_F(XmpNsDumperTest_1315, TrailingColonNamespace_1315) {

    const char* buffer = "xmp:";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_TRUE(nsMap.empty());

}



TEST_F(XmpNsDumperTest_1315, NamespaceWithoutUri_1315) {

    const char* buffer = "xmp";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_TRUE(nsMap.empty());

}



TEST_F(XmpNsDumperTest_1315, UriWithExistingNamespace_1315) {

    nsMap[""] = "xmp";

    const char* buffer = "xmp:Title Info";

    XMP_StringLen bufferSize = strlen(buffer);

    EXPECT_EQ(nsDumper(&nsMap, buffer, bufferSize), 0);

    EXPECT_EQ(nsMap["xmp"], "Title Info");

}



TEST_F(XmpNsDumperTest_1315, MultipleNamespaces_1315) {

    const char* buffer1 = "dc: http://purl.org/dc/elements/1.1/";

    XMP_StringLen bufferSize1 = strlen(buffer1);

    EXPECT_EQ(nsDumper(&nsMap, buffer1, bufferSize1), 0);



    const char* buffer2 = "xmp: http://ns.adobe.com/xap/1.0/";

    XMP_StringLen bufferSize2 = strlen(buffer2);

    EXPECT_EQ(nsDumper(&nsMap, buffer2, bufferSize2), 0);



    EXPECT_EQ(nsMap[""], "http://ns.adobe.com/xap/1.0");

    EXPECT_EQ(nsMap["dc"], "http://purl.org/dc/elements/1.1");

}
