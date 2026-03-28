#include <gtest/gtest.h>
#include <gmock/gmock.h>

// Include necessary headers for XMP SDK
#define TXMP_STRING_TYPE std::string
#include <string>

// Forward declarations and includes needed for the XMP SDK
#include "XMP.incl_cpp"
#include "XMP.hpp"

// Test fixture for WXMPMeta tests
class WXMPMetaTest_1989 : public ::testing::Test {
protected:
    static void SetUpTestSuite() {
        // Initialize XMP SDK once for all tests
        SXMPMeta::Initialize();
    }

    static void TearDownTestSuite() {
        SXMPMeta::Terminate();
    }

    void SetUp() override {
        meta_ = SXMPMeta();
    }

    void TearDown() override {
    }

    SXMPMeta meta_;
};

// Test: Default construction creates a valid object
TEST_F(WXMPMetaTest_1989, DefaultConstruction_1989) {
    SXMPMeta meta;
    // Should be able to get object name without crashing
    std::string name;
    meta.GetObjectName(&name);
    EXPECT_TRUE(name.empty());
}

// Test: SetProperty and GetProperty basic round-trip
TEST_F(WXMPMetaTest_1989, SetAndGetProperty_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "TestProp", "TestValue", 0);

    std::string value;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty(ns, "TestProp", &value, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ("TestValue", value);
}

// Test: GetProperty returns false for non-existent property
TEST_F(WXMPMetaTest_1989, GetPropertyNonExistent_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    std::string value;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty(ns, "NonExistent", &value, &opts);

    EXPECT_FALSE(found);
}

// Test: DoesPropertyExist for existing and non-existing properties
TEST_F(WXMPMetaTest_1989, DoesPropertyExist_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    EXPECT_FALSE(meta_.DoesPropertyExist(ns, "Prop1"));

    meta_.SetProperty(ns, "Prop1", "Value1", 0);
    EXPECT_TRUE(meta_.DoesPropertyExist(ns, "Prop1"));
}

// Test: DeleteProperty removes property
TEST_F(WXMPMetaTest_1989, DeleteProperty_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "ToDelete", "Value", 0);
    EXPECT_TRUE(meta_.DoesPropertyExist(ns, "ToDelete"));

    meta_.DeleteProperty(ns, "ToDelete");
    EXPECT_FALSE(meta_.DoesPropertyExist(ns, "ToDelete"));
}

// Test: SetProperty_Bool and GetProperty_Bool round-trip
TEST_F(WXMPMetaTest_1989, SetAndGetPropertyBool_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty_Bool(ns, "BoolProp", true, 0);

    bool boolVal = false;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty_Bool(ns, "BoolProp", &boolVal, &opts);

    EXPECT_TRUE(found);
    EXPECT_TRUE(boolVal);
}

// Test: SetProperty_Int and GetProperty_Int round-trip
TEST_F(WXMPMetaTest_1989, SetAndGetPropertyInt_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty_Int(ns, "IntProp", 42, 0);

    XMP_Int32 intVal = 0;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty_Int(ns, "IntProp", &intVal, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ(42, intVal);
}

// Test: SetProperty_Int64 and GetProperty_Int64 round-trip
TEST_F(WXMPMetaTest_1989, SetAndGetPropertyInt64_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    XMP_Int64 bigVal = 9876543210LL;
    meta_.SetProperty_Int64(ns, "Int64Prop", bigVal, 0);

    XMP_Int64 resultVal = 0;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty_Int64(ns, "Int64Prop", &resultVal, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ(bigVal, resultVal);
}

// Test: SetProperty_Float and GetProperty_Float round-trip
TEST_F(WXMPMetaTest_1989, SetAndGetPropertyFloat_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty_Float(ns, "FloatProp", 3.14, 0);

    double floatVal = 0.0;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty_Float(ns, "FloatProp", &floatVal, &opts);

    EXPECT_TRUE(found);
    EXPECT_NEAR(3.14, floatVal, 0.001);
}

// Test: AppendArrayItem and GetArrayItem
TEST_F(WXMPMetaTest_1989, AppendAndGetArrayItem_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.AppendArrayItem(ns, "ArrayProp", kXMP_PropValueIsArray, "Item1", 0);
    meta_.AppendArrayItem(ns, "ArrayProp", kXMP_PropValueIsArray, "Item2", 0);

    std::string value;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetArrayItem(ns, "ArrayProp", 1, &value, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ("Item1", value);

    found = meta_.GetArrayItem(ns, "ArrayProp", 2, &value, &opts);
    EXPECT_TRUE(found);
    EXPECT_EQ("Item2", value);
}

// Test: CountArrayItems
TEST_F(WXMPMetaTest_1989, CountArrayItems_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.AppendArrayItem(ns, "CountArray", kXMP_PropValueIsArray, "A", 0);
    meta_.AppendArrayItem(ns, "CountArray", kXMP_PropValueIsArray, "B", 0);
    meta_.AppendArrayItem(ns, "CountArray", kXMP_PropValueIsArray, "C", 0);

    XMP_Index count = meta_.CountArrayItems(ns, "CountArray");
    EXPECT_EQ(3, count);
}

// Test: CountArrayItems returns 0 for non-existent array
TEST_F(WXMPMetaTest_1989, CountArrayItemsNonExistent_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    XMP_Index count = meta_.CountArrayItems(ns, "NoSuchArray");
    EXPECT_EQ(0, count);
}

// Test: DeleteArrayItem
TEST_F(WXMPMetaTest_1989, DeleteArrayItem_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.AppendArrayItem(ns, "DelArray", kXMP_PropValueIsArray, "X", 0);
    meta_.AppendArrayItem(ns, "DelArray", kXMP_PropValueIsArray, "Y", 0);
    EXPECT_EQ(2, meta_.CountArrayItems(ns, "DelArray"));

    meta_.DeleteArrayItem(ns, "DelArray", 1);
    EXPECT_EQ(1, meta_.CountArrayItems(ns, "DelArray"));
}

// Test: SetStructField and GetStructField
TEST_F(WXMPMetaTest_1989, SetAndGetStructField_1989) {
    const char* ns = "http://test.ns/";
    const char* fieldNS = "http://field.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    SXMPMeta::RegisterNamespace(fieldNS, "field", nullptr);

    meta_.SetStructField(ns, "StructProp", fieldNS, "FieldName", "FieldValue", 0);

    std::string value;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetStructField(ns, "StructProp", fieldNS, "FieldName", &value, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ("FieldValue", value);
}

// Test: DoesStructFieldExist
TEST_F(WXMPMetaTest_1989, DoesStructFieldExist_1989) {
    const char* ns = "http://test.ns/";
    const char* fieldNS = "http://field.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    SXMPMeta::RegisterNamespace(fieldNS, "field", nullptr);

    EXPECT_FALSE(meta_.DoesStructFieldExist(ns, "StructProp", fieldNS, "FieldName"));

    meta_.SetStructField(ns, "StructProp", fieldNS, "FieldName", "Val", 0);
    EXPECT_TRUE(meta_.DoesStructFieldExist(ns, "StructProp", fieldNS, "FieldName"));
}

// Test: DeleteStructField
TEST_F(WXMPMetaTest_1989, DeleteStructField_1989) {
    const char* ns = "http://test.ns/";
    const char* fieldNS = "http://field.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    SXMPMeta::RegisterNamespace(fieldNS, "field", nullptr);

    meta_.SetStructField(ns, "StructProp", fieldNS, "FieldName", "Val", 0);
    EXPECT_TRUE(meta_.DoesStructFieldExist(ns, "StructProp", fieldNS, "FieldName"));

    meta_.DeleteStructField(ns, "StructProp", fieldNS, "FieldName");
    EXPECT_FALSE(meta_.DoesStructFieldExist(ns, "StructProp", fieldNS, "FieldName"));
}

// Test: SetQualifier and GetQualifier
TEST_F(WXMPMetaTest_1989, SetAndGetQualifier_1989) {
    const char* ns = "http://test.ns/";
    const char* qualNS = "http://qual.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    SXMPMeta::RegisterNamespace(qualNS, "qual", nullptr);

    meta_.SetProperty(ns, "QualProp", "PropValue", 0);
    meta_.SetQualifier(ns, "QualProp", qualNS, "QualName", "QualValue", 0);

    std::string value;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetQualifier(ns, "QualProp", qualNS, "QualName", &value, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ("QualValue", value);
}

// Test: DoesQualifierExist
TEST_F(WXMPMetaTest_1989, DoesQualifierExist_1989) {
    const char* ns = "http://test.ns/";
    const char* qualNS = "http://qual.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    SXMPMeta::RegisterNamespace(qualNS, "qual", nullptr);

    meta_.SetProperty(ns, "QualProp2", "PropValue", 0);
    EXPECT_FALSE(meta_.DoesQualifierExist(ns, "QualProp2", qualNS, "QualName"));

    meta_.SetQualifier(ns, "QualProp2", qualNS, "QualName", "QualValue", 0);
    EXPECT_TRUE(meta_.DoesQualifierExist(ns, "QualProp2", qualNS, "QualName"));
}

// Test: SetObjectName and GetObjectName
TEST_F(WXMPMetaTest_1989, SetAndGetObjectName_1989) {
    meta_.SetObjectName("MyXMPObject");

    std::string name;
    meta_.GetObjectName(&name);

    EXPECT_EQ("MyXMPObject", name);
}

// Test: SetObjectName with empty string
TEST_F(WXMPMetaTest_1989, SetObjectNameEmpty_1989) {
    meta_.SetObjectName("SomeName");
    meta_.SetObjectName("");

    std::string name;
    meta_.GetObjectName(&name);

    EXPECT_EQ("", name);
}

// Test: Erase clears all properties
TEST_F(WXMPMetaTest_1989, EraseClearsProperties_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "Prop1", "Val1", 0);
    meta_.SetProperty(ns, "Prop2", "Val2", 0);
    EXPECT_TRUE(meta_.DoesPropertyExist(ns, "Prop1"));

    meta_.Erase();

    EXPECT_FALSE(meta_.DoesPropertyExist(ns, "Prop1"));
    EXPECT_FALSE(meta_.DoesPropertyExist(ns, "Prop2"));
}

// Test: Clone produces independent copy
TEST_F(WXMPMetaTest_1989, CloneProducesIndependentCopy_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "CloneProp", "CloneValue", 0);

    SXMPMeta cloned(meta_);

    std::string value;
    bool found = cloned.GetProperty(ns, "CloneProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ("CloneValue", value);

    // Modify original; clone should be unaffected
    meta_.SetProperty(ns, "CloneProp", "ModifiedValue", 0);

    found = cloned.GetProperty(ns, "CloneProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ("CloneValue", value);
}

// Test: SerializeToBuffer produces non-empty RDF output
TEST_F(WXMPMetaTest_1989, SerializeToBuffer_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "SerProp", "SerValue", 0);

    std::string rdfString;
    meta_.SerializeToBuffer(&rdfString, 0, 0, "", "", 0);

    EXPECT_FALSE(rdfString.empty());
    // The serialization should contain RDF
    EXPECT_NE(std::string::npos, rdfString.find("rdf"));
}

// Test: ParseFromBuffer populates meta
TEST_F(WXMPMetaTest_1989, ParseFromBuffer_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    // First serialize some data
    SXMPMeta source;
    source.SetProperty(ns, "ParseProp", "ParseValue", 0);

    std::string rdfString;
    source.SerializeToBuffer(&rdfString, 0, 0, "", "", 0);

    // Now parse into a new meta
    SXMPMeta target;
    target.ParseFromBuffer(rdfString.c_str(), static_cast<XMP_StringLen>(rdfString.size()), 0);

    std::string value;
    bool found = target.GetProperty(ns, "ParseProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ("ParseValue", value);
}

// Test: SetLocalizedText and GetLocalizedText
TEST_F(WXMPMetaTest_1989, SetAndGetLocalizedText_1989) {
    const char* ns = kXMP_NS_DC;

    meta_.SetLocalizedText(ns, "title", "", "en-US", "English Title", 0);

    std::string actualLang;
    std::string itemValue;
    XMP_OptionBits opts = 0;
    bool found = meta_.GetLocalizedText(ns, "title", "", "en-US", &actualLang, &itemValue, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ("English Title", itemValue);
}

// Test: GetLocalizedText with non-matching language
TEST_F(WXMPMetaTest_1989, GetLocalizedTextNonMatchingLang_1989) {
    const char* ns = kXMP_NS_DC;

    meta_.SetLocalizedText(ns, "description", "", "fr-FR", "Description Francaise", 0);

    std::string actualLang;
    std::string itemValue;
    XMP_OptionBits opts = 0;
    // Try to get with a different specific language
    bool found = meta_.GetLocalizedText(ns, "description", "", "de-DE", &actualLang, &itemValue, &opts);

    // Behavior may vary — the SDK might return the x-default or fail
    // We just check it doesn't crash and returns a consistent result
    if (found) {
        EXPECT_FALSE(itemValue.empty());
    }
}

// Test: RegisterNamespace and GetNamespacePrefix
TEST_F(WXMPMetaTest_1989, RegisterAndGetNamespacePrefix_1989) {
    const char* ns = "http://unique.test.ns/1989/";
    SXMPMeta::RegisterNamespace(ns, "unique1989", nullptr);

    std::string prefix;
    bool found = SXMPMeta::GetNamespacePrefix(ns, &prefix);

    EXPECT_TRUE(found);
    EXPECT_FALSE(prefix.empty());
}

// Test: GetNamespaceURI for registered namespace
TEST_F(WXMPMetaTest_1989, GetNamespaceURI_1989) {
    const char* ns = "http://unique.test.ns/uri1989/";
    SXMPMeta::RegisterNamespace(ns, "uri1989", nullptr);

    std::string prefix;
    SXMPMeta::GetNamespacePrefix(ns, &prefix);

    std::string uri;
    bool found = SXMPMeta::GetNamespaceURI(prefix.c_str(), &uri);

    EXPECT_TRUE(found);
    EXPECT_EQ(ns, uri);
}

// Test: GetNamespacePrefix for unregistered namespace
TEST_F(WXMPMetaTest_1989, GetNamespacePrefixUnregistered_1989) {
    std::string prefix;
    bool found = SXMPMeta::GetNamespacePrefix("http://totally.unknown.ns/", &prefix);
    EXPECT_FALSE(found);
}

// Test: GetVersionInfo returns non-null info
TEST_F(WXMPMetaTest_1989, GetVersionInfo_1989) {
    XMP_VersionInfo info;
    memset(&info, 0, sizeof(info));
    SXMPMeta::GetVersionInfo(&info);

    // Version info should have some data
    EXPECT_GT(info.major, 0);
}

// Test: SetProperty_Date and GetProperty_Date round-trip
TEST_F(WXMPMetaTest_1989, SetAndGetPropertyDate_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    XMP_DateTime dateVal;
    memset(&dateVal, 0, sizeof(dateVal));
    dateVal.year = 2023;
    dateVal.month = 6;
    dateVal.day = 15;
    dateVal.hour = 10;
    dateVal.minute = 30;
    dateVal.second = 0;
    dateVal.nanoSecond = 0;
    dateVal.tzSign = 0;
    dateVal.tzHour = 0;
    dateVal.tzMinute = 0;

    meta_.SetProperty_Date(ns, "DateProp", dateVal, 0);

    XMP_DateTime resultDate;
    memset(&resultDate, 0, sizeof(resultDate));
    XMP_OptionBits opts = 0;
    bool found = meta_.GetProperty_Date(ns, "DateProp", &resultDate, &opts);

    EXPECT_TRUE(found);
    EXPECT_EQ(2023, resultDate.year);
    EXPECT_EQ(6, resultDate.month);
    EXPECT_EQ(15, resultDate.day);
}

// Test: SetArrayItem replaces existing item
TEST_F(WXMPMetaTest_1989, SetArrayItemReplacesExisting_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.AppendArrayItem(ns, "ReplaceArray", kXMP_PropValueIsArray, "Original", 0);

    std::string value;
    meta_.GetArrayItem(ns, "ReplaceArray", 1, &value, nullptr);
    EXPECT_EQ("Original", value);

    meta_.SetArrayItem(ns, "ReplaceArray", 1, "Replaced", 0);

    meta_.GetArrayItem(ns, "ReplaceArray", 1, &value, nullptr);
    EXPECT_EQ("Replaced", value);
}

// Test: DoesArrayItemExist
TEST_F(WXMPMetaTest_1989, DoesArrayItemExist_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.AppendArrayItem(ns, "ExistArray", kXMP_PropValueIsArray, "Item", 0);

    EXPECT_TRUE(meta_.DoesArrayItemExist(ns, "ExistArray", 1));
    EXPECT_FALSE(meta_.DoesArrayItemExist(ns, "ExistArray", 2));
}

// Test: Sort does not lose properties
TEST_F(WXMPMetaTest_1989, SortDoesNotLoseProperties_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "Zebra", "Z", 0);
    meta_.SetProperty(ns, "Alpha", "A", 0);
    meta_.SetProperty(ns, "Middle", "M", 0);

    meta_.Sort();

    EXPECT_TRUE(meta_.DoesPropertyExist(ns, "Zebra"));
    EXPECT_TRUE(meta_.DoesPropertyExist(ns, "Alpha"));
    EXPECT_TRUE(meta_.DoesPropertyExist(ns, "Middle"));
}

// Test: Overwrite property value
TEST_F(WXMPMetaTest_1989, OverwritePropertyValue_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "OverProp", "First", 0);
    meta_.SetProperty(ns, "OverProp", "Second", 0);

    std::string value;
    meta_.GetProperty(ns, "OverProp", &value, nullptr);
    EXPECT_EQ("Second", value);
}

// Test: Multiple namespaces in same meta
TEST_F(WXMPMetaTest_1989, MultipleNamespaces_1989) {
    const char* ns1 = "http://test.ns/one/";
    const char* ns2 = "http://test.ns/two/";
    SXMPMeta::RegisterNamespace(ns1, "one", nullptr);
    SXMPMeta::RegisterNamespace(ns2, "two", nullptr);

    meta_.SetProperty(ns1, "PropA", "ValueA", 0);
    meta_.SetProperty(ns2, "PropB", "ValueB", 0);

    std::string valA, valB;
    EXPECT_TRUE(meta_.GetProperty(ns1, "PropA", &valA, nullptr));
    EXPECT_TRUE(meta_.GetProperty(ns2, "PropB", &valB, nullptr));
    EXPECT_EQ("ValueA", valA);
    EXPECT_EQ("ValueB", valB);

    // Cross-namespace should not find
    EXPECT_FALSE(meta_.DoesPropertyExist(ns1, "PropB"));
    EXPECT_FALSE(meta_.DoesPropertyExist(ns2, "PropA"));
}

// Test: Empty property value
TEST_F(WXMPMetaTest_1989, EmptyPropertyValue_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "EmptyProp", "", 0);

    std::string value;
    bool found = meta_.GetProperty(ns, "EmptyProp", &value, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ("", value);
}

// Test: SetProperty_Bool false and retrieve
TEST_F(WXMPMetaTest_1989, SetPropertyBoolFalse_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty_Bool(ns, "FalseProp", false, 0);

    bool boolVal = true;
    bool found = meta_.GetProperty_Bool(ns, "FalseProp", &boolVal, nullptr);
    EXPECT_TRUE(found);
    EXPECT_FALSE(boolVal);
}

// Test: Negative integer property
TEST_F(WXMPMetaTest_1989, SetPropertyIntNegative_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty_Int(ns, "NegInt", -100, 0);

    XMP_Int32 intVal = 0;
    bool found = meta_.GetProperty_Int(ns, "NegInt", &intVal, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(-100, intVal);
}

// Test: Zero integer property
TEST_F(WXMPMetaTest_1989, SetPropertyIntZero_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty_Int(ns, "ZeroInt", 0, 0);

    XMP_Int32 intVal = 99;
    bool found = meta_.GetProperty_Int(ns, "ZeroInt", &intVal, nullptr);
    EXPECT_TRUE(found);
    EXPECT_EQ(0, intVal);
}

// Test: DumpObject callback
static XMP_Status TestDumpCallback(void* refCon, XMP_StringPtr buffer, XMP_StringLen bufferSize) {
    std::string* output = static_cast<std::string*>(refCon);
    output->append(buffer, bufferSize);
    return 0;
}

TEST_F(WXMPMetaTest_1989, DumpObject_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.SetProperty(ns, "DumpProp", "DumpValue", 0);

    std::string dumpOutput;
    XMP_Status status = meta_.DumpObject(TestDumpCallback, &dumpOutput);

    EXPECT_EQ(0, status);
    EXPECT_FALSE(dumpOutput.empty());
}

// Test: Ordered array
TEST_F(WXMPMetaTest_1989, OrderedArray_1989) {
    const char* ns = "http://test.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);

    meta_.AppendArrayItem(ns, "OrdArray", kXMP_PropArrayIsOrdered, "First", 0);
    meta_.AppendArrayItem(ns, "OrdArray", kXMP_PropArrayIsOrdered, "Second", 0);
    meta_.AppendArrayItem(ns, "OrdArray", kXMP_PropArrayIsOrdered, "Third", 0);

    EXPECT_EQ(3, meta_.CountArrayItems(ns, "OrdArray"));

    std::string val;
    meta_.GetArrayItem(ns, "OrdArray", 1, &val, nullptr);
    EXPECT_EQ("First", val);
    meta_.GetArrayItem(ns, "OrdArray", 3, &val, nullptr);
    EXPECT_EQ("Third", val);
}

// Test: DeleteQualifier
TEST_F(WXMPMetaTest_1989, DeleteQualifier_1989) {
    const char* ns = "http://test.ns/";
    const char* qualNS = "http://qual.ns/";
    SXMPMeta::RegisterNamespace(ns, "test", nullptr);
    SXMPMeta::RegisterNamespace(qualNS, "qual", nullptr);

    meta_.SetProperty(ns, "QualDelProp", "PropValue", 0);
    meta_.SetQualifier(ns, "QualDelProp", qualNS, "QualDel", "QualValue", 0);
    EXPECT_TRUE(meta_.DoesQualifierExist(ns, "QualDelProp", qualNS, "QualDel"));

    meta_.DeleteQualifier(ns, "QualDelProp", qualNS, "QualDel");
    EXPECT_FALSE(meta_.DoesQualifierExist(ns, "QualDelProp", qualNS, "QualDel"));
}
