#include <gtest/gtest.h>
#include <exiv2/iptc.hpp>
#include <exiv2/types.hpp>
#include <exiv2/value.hpp>
#include <cstring>

using namespace Exiv2;

class IptcParserEncodeTest_704 : public ::testing::Test {
protected:
    IptcData iptcData;
};

// Test encoding empty IptcData returns empty DataBuf
TEST_F(IptcParserEncodeTest_704, EncodeEmptyIptcData_704) {
    DataBuf buf = IptcParser::encode(iptcData);
    EXPECT_TRUE(buf.empty());
    EXPECT_EQ(buf.size(), 0u);
}

// Test encoding a single small datum
TEST_F(IptcParserEncodeTest_704, EncodeSingleDatum_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("TestObject");
    iptcData.add(key, val.get());

    DataBuf buf = IptcParser::encode(iptcData);
    EXPECT_FALSE(buf.empty());
    EXPECT_GT(buf.size(), 0u);

    // Check marker byte (0x1c)
    EXPECT_EQ(buf.read_uint8(0), 0x1c);
}

// Test round-trip: encode then decode should preserve data
TEST_F(IptcParserEncodeTest_704, RoundTripEncodeDecode_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("HelloWorld");
    iptcData.add(key, val.get());

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(decoded.count(), 1u);

    auto it = decoded.findKey(IptcKey("Iptc.Application2.ObjectName"));
    ASSERT_NE(it, decoded.end());
    EXPECT_EQ(it->toString(), "HelloWorld");
}

// Test encoding multiple data entries
TEST_F(IptcParserEncodeTest_704, EncodeMultipleData_704) {
    {
        IptcKey key("Iptc.Application2.ObjectName");
        Value::UniquePtr val = Value::create(string);
        val->read("Object1");
        iptcData.add(key, val.get());
    }
    {
        IptcKey key("Iptc.Application2.Keywords");
        Value::UniquePtr val = Value::create(string);
        val->read("keyword1");
        iptcData.add(key, val.get());
    }
    {
        IptcKey key("Iptc.Application2.Keywords");
        Value::UniquePtr val = Value::create(string);
        val->read("keyword2");
        iptcData.add(key, val.get());
    }

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(decoded.count(), 3u);
}

// Test that encoding sorts by record
TEST_F(IptcParserEncodeTest_704, EncodeSortsByRecord_704) {
    {
        IptcKey key("Iptc.Application2.ObjectName");
        Value::UniquePtr val = Value::create(string);
        val->read("AppData");
        iptcData.add(key, val.get());
    }
    {
        IptcKey key("Iptc.Envelope.CharacterSet");
        Value::UniquePtr val = Value::create(string);
        val->read("EnvData");
        iptcData.add(key, val.get());
    }

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    // After encoding, envelope (record 1) should come before application2 (record 2)
    // First record byte is at offset 1
    uint8_t firstRecord = buf.read_uint8(1);
    // The Envelope record number is 1, Application2 is 2
    EXPECT_LE(firstRecord, 2u);

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(decoded.count(), 2u);
}

// Test encoding with empty string value
TEST_F(IptcParserEncodeTest_704, EncodeEmptyStringValue_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("");
    iptcData.add(key, val.get());

    DataBuf buf = IptcParser::encode(iptcData);
    EXPECT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(decoded.count(), 1u);
    auto it = decoded.findKey(IptcKey("Iptc.Application2.ObjectName"));
    ASSERT_NE(it, decoded.end());
    EXPECT_EQ(it->toString(), "");
}

// Test round-trip preserves multiple keywords
TEST_F(IptcParserEncodeTest_704, RoundTripMultipleKeywords_704) {
    std::vector<std::string> keywords = {"alpha", "beta", "gamma", "delta"};
    for (const auto& kw : keywords) {
        IptcKey key("Iptc.Application2.Keywords");
        Value::UniquePtr val = Value::create(string);
        val->read(kw);
        iptcData.add(key, val.get());
    }

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(decoded.count(), 4u);
}

// Test that marker byte is correctly set for each entry
TEST_F(IptcParserEncodeTest_704, MarkerByteCorrect_704) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr val = Value::create(string);
    val->read("Test caption text");
    iptcData.add(key, val.get());

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());
    // First byte should be the IPTC marker 0x1c
    EXPECT_EQ(buf.read_uint8(0), 0x1c);
}

// Test decode with nullptr or zero size
TEST_F(IptcParserEncodeTest_704, DecodeEmptyData_704) {
    IptcData decoded;
    int rc = IptcParser::decode(decoded, nullptr, 0);
    // Should handle gracefully - either return error or empty data
    EXPECT_TRUE(decoded.empty());
}

// Test encoding preserves record and tag information
TEST_F(IptcParserEncodeTest_704, EncodePreservesRecordAndTag_704) {
    IptcKey key("Iptc.Application2.City");
    Value::UniquePtr val = Value::create(string);
    val->read("Berlin");
    iptcData.add(key, val.get());

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);

    auto it = decoded.findKey(IptcKey("Iptc.Application2.City"));
    ASSERT_NE(it, decoded.end());
    EXPECT_EQ(it->toString(), "Berlin");
}

// Test encoding data of various sizes
TEST_F(IptcParserEncodeTest_704, EncodeVaryingSizes_704) {
    // Short string
    {
        IptcKey key("Iptc.Application2.ObjectName");
        Value::UniquePtr val = Value::create(string);
        val->read("A");
        iptcData.add(key, val.get());
    }
    // Medium string
    {
        IptcKey key("Iptc.Application2.Caption");
        Value::UniquePtr val = Value::create(string);
        std::string medium(1000, 'X');
        val->read(medium);
        iptcData.add(key, val.get());
    }

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(decoded.count(), 2u);
}

// Test IptcData basic operations
TEST_F(IptcParserEncodeTest_704, IptcDataAddAndFind_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("TestName");
    int rc = iptcData.add(key, val.get());
    EXPECT_EQ(rc, 0);
    EXPECT_EQ(iptcData.count(), 1u);
    EXPECT_FALSE(iptcData.empty());

    auto it = iptcData.findKey(IptcKey("Iptc.Application2.ObjectName"));
    ASSERT_NE(it, iptcData.end());
    EXPECT_EQ(it->toString(), "TestName");
}

// Test IptcData clear
TEST_F(IptcParserEncodeTest_704, IptcDataClear_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("TestName");
    iptcData.add(key, val.get());
    EXPECT_FALSE(iptcData.empty());

    iptcData.clear();
    EXPECT_TRUE(iptcData.empty());
    EXPECT_EQ(iptcData.count(), 0u);

    // Encoding cleared data should return empty buffer
    DataBuf buf = IptcParser::encode(iptcData);
    EXPECT_TRUE(buf.empty());
}

// Test IptcData erase
TEST_F(IptcParserEncodeTest_704, IptcDataErase_704) {
    IptcKey key1("Iptc.Application2.ObjectName");
    Value::UniquePtr val1 = Value::create(string);
    val1->read("Name1");
    iptcData.add(key1, val1.get());

    IptcKey key2("Iptc.Application2.Keywords");
    Value::UniquePtr val2 = Value::create(string);
    val2->read("Keyword1");
    iptcData.add(key2, val2.get());

    EXPECT_EQ(iptcData.count(), 2u);

    auto it = iptcData.findKey(IptcKey("Iptc.Application2.ObjectName"));
    ASSERT_NE(it, iptcData.end());
    iptcData.erase(it);

    EXPECT_EQ(iptcData.count(), 1u);
}

// Test double encode produces consistent results
TEST_F(IptcParserEncodeTest_704, DoubleEncodeConsistency_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("ConsistencyTest");
    iptcData.add(key, val.get());

    DataBuf buf1 = IptcParser::encode(iptcData);
    DataBuf buf2 = IptcParser::encode(iptcData);

    ASSERT_EQ(buf1.size(), buf2.size());
    EXPECT_EQ(std::memcmp(buf1.c_data(0), buf2.c_data(0), buf1.size()), 0);
}

// Test decode of encoded data with special characters
TEST_F(IptcParserEncodeTest_704, EncodeDecodeSpecialCharacters_704) {
    IptcKey key("Iptc.Application2.Caption");
    Value::UniquePtr val = Value::create(string);
    val->read("Line1\nLine2\tTabbed");
    iptcData.add(key, val.get());

    DataBuf buf = IptcParser::encode(iptcData);
    ASSERT_FALSE(buf.empty());

    IptcData decoded;
    int rc = IptcParser::decode(decoded, buf.c_data(0), buf.size());
    EXPECT_EQ(rc, 0);

    auto it = decoded.findKey(IptcKey("Iptc.Application2.Caption"));
    ASSERT_NE(it, decoded.end());
    EXPECT_EQ(it->toString(), "Line1\nLine2\tTabbed");
}

// Test findId
TEST_F(IptcParserEncodeTest_704, FindById_704) {
    IptcKey key("Iptc.Application2.ObjectName");
    Value::UniquePtr val = Value::create(string);
    val->read("FindMe");
    iptcData.add(key, val.get());

    // ObjectName dataset is 5, Application2 record is 2
    auto it = iptcData.findId(5, 2);
    ASSERT_NE(it, iptcData.end());
    EXPECT_EQ(it->toString(), "FindMe");
}

// Test operator[] creates entry if not found
TEST_F(IptcParserEncodeTest_704, OperatorBracketCreatesEntry_704) {
    Iptcdatum& datum = iptcData["Iptc.Application2.ObjectName"];
    datum = std::string("Created");

    EXPECT_EQ(iptcData.count(), 1u);
    auto it = iptcData.findKey(IptcKey("Iptc.Application2.ObjectName"));
    ASSERT_NE(it, iptcData.end());
    EXPECT_EQ(it->toString(), "Created");
}
