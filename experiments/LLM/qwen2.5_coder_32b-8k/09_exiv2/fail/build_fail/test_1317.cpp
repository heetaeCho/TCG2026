

### Test Cases



#### 1. Basic Property Parsing

```cpp

TEST(XmpParserTest, BasicPropertyParsing) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:dc="http://purl.org/dc/elements/1.1/"

                    dc:title="Sample Image Title" />

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    EXPECT_EQ(xmpData["Xmp.dc.title"].toString(), "Sample Image Title");

}

```



#### 2. Parsing Array Property

```cpp

TEST(XmpParserTest, ParsingArrayProperty) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:dc="http://purl.org/dc/elements/1.1/"

                    dc:creator="Author 1"

                    dc:creator="Author 2" />

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    std::vector<std::string> creators = xmpData["Xmp.dc.creator"].toString().split("\n");

    EXPECT_EQ(creators.size(), 2);

    EXPECT_EQ(creators[0], "Author 1");

    EXPECT_EQ(creators[1], "Author 2");

}

```



#### 3. Parsing Struct Property

```cpp

TEST(XmpParserTest, ParsingStructProperty) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:exif="http://ns.adobe.com/exif/1.0/"

                    exif:DateTimeOriginal="2021-01-01T12:34:56Z" />

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    EXPECT_EQ(xmpData["Xmp.exif.DateTimeOriginal"].toString(), "2021-01-01T12:34:56Z");

}

```



#### 4. Parsing Qualified Property

```cpp

TEST(XmpParserTest, ParsingQualifiedProperty) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:dc="http://purl.org/dc/elements/1.1/"

                    dc:title>

                        <rdf:Alt>

                            <rdf:li xml:lang="x-default">Default Title</rdf:li>

                            <rdf:li xml:lang="en">English Title</rdf:li>

                        </rdf:Alt>

                    </dc:title>

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    EXPECT_EQ(xmpData["Xmp.dc.title"].toString(), "Default Title");

}

```



#### 5. Parsing Lang Alt Property

```cpp

TEST(XmpParserTest, ParsingLangAltProperty) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:dc="http://purl.org/dc/elements/1.1/"

                    dc:title>

                        <rdf:Alt>

                            <rdf:li xml:lang="x-default">Default Title</rdf:li>

                            <rdf:li xml:lang="en">English Title</rdf:li>

                            <rdf:li xml:lang="fr">Titre Français</rdf:li>

                        </rdf:Alt>

                    </dc:title>

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    EXPECT_EQ(xmpData["Xmp.dc.title"].toString(), "Default Title");

}

```



#### 6. Error Handling for Invalid XML

```cpp

TEST(XmpParserTest, ErrorHandlingForInvalidXML) {

    const std::string invalidXmlPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:dc="http://purl.org/dc/elements/1.1/"

                    dc:title="Sample Image Title"

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_NE(parser.decode(invalidXmlPacket), 0);

}

```



#### 7. Parsing Nested Struct Property

```cpp

TEST(XmpParserTest, ParsingNestedStructProperty) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:exif="http://ns.adobe.com/exif/1.0/"

                    exif:GPSInfo>

                        <rdf:Bag>

                            <rdf:li>

                                <rdf:Seq>

                                    <rdf:li>37.7749</rdf:li>

                                    <rdf:li>-122.4194</rdf:li>

                                </rdf:Seq>

                            </rdf:li>

                        </rdf:Bag>

                    </exif:GPSInfo>

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    // Assuming that the GPS coordinates are stored in a specific format

    std::string gpsInfo = xmpData["Xmp.exif.GPSInfo"].toString();

    EXPECT_TRUE(gpsInfo.find("37.7749") != std::string::npos);

    EXPECT_TRUE(gpsInfo.find("-122.4194") != std::string::npos);

}

```



#### 8. Parsing Alias Property

```cpp

TEST(XmpParserTest, ParsingAliasProperty) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:photoshop="http://ns.adobe.com/photoshop/1.0/"

                    photoshop:Credit="Photographer Name" />

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    // Assuming that the Credit is an alias for Creator

    EXPECT_EQ(xmpData["Xmp.photoshop.Credit"].toString(), "Photographer Name");

}

```



#### 9. Parsing Namespace URI and Prefix

```cpp

TEST(XmpParserTest, ParsingNamespaceURIAndPrefix) {

    const std::string xmpPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about=""

                    xmlns:dc="http://purl.org/dc/elements/1.1/"

                    dc:title="Sample Image Title" />

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(xmpPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    EXPECT_TRUE(parser.namespaceExists("dc", "http://purl.org/dc/elements/1.1/"));

}

```



#### 10. Parsing Empty XMP Packet

```cpp

TEST(XmpParserTest, ParsingEmptyXmpPacket) {

    const std::string emptyXmlPacket = R"(<x:xmpmeta xmlns:x="adobe:ns:meta/" x:xmptk="XMP Core 5.4.0">

            <rdf:RDF xmlns:rdf="http://www.w3.org/1999/02/22-rdf-syntax-ns#">

                <rdf:Description rdf:about="" />

            </rdf:RDF>

        </x:xmpmeta>)";



    XmpParser parser;

    EXPECT_EQ(parser.decode(emptyXmlPacket), 0);



    Exiv2::XmpData xmpData = parser.xmpData();

    EXPECT_TRUE(xmpData.empty());

}
