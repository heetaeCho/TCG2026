The TEST_ID is 867

--- PROMPT START ---

You are given a partial implementation of a C++ class.
This class is already implemented and used in the actual codebase.
Your task is to write unit tests for the given interface, using Google Test (and Google Mock if needed), while strictly following the constraints below.

[Constraints]
1. **Do NOT re-implement or infer the internal logic** of any function.  
   You must treat the implementation as a black box.
2. **Write tests only based on the provided interface** — that is, based on:
   - Function signatures
   - Observable behavior (e.g., return values, effects visible through public functions or callback invocations)
3. **You may use Google Mock**:
   - Only when mocking external collaborators (e.g., passed-in handlers, callbacks, or dependencies)
   - Not to simulate internal behavior of the class under test
4. **Do NOT access or rely on private/internal state**, such as internal buffers, counters, or helper function behavior.
5. Include test cases for:
   - Normal operation
   - Boundary conditions
   - Exceptional or error cases (if observable through the interface)
   - Verification of external interactions (e.g., mock handler calls and their parameters)
6. Each test case should clearly indicate what behavior is being tested, and should follow consistent naming conventions.

[Requirements]
1. add TEST_ID for every Test name
   e.g.) TEST_F(WriteBatchTest_85, PutIncreasesCount_85), where The TEST_ID is 85

[Partial Code]
File name : Catch2/src/catch2/reporters/catch_reporter_json.cpp
```cpp
namespace Catch { class JsonReporter { public: void testRunEnded(TestRunStats const& runStats) { assert( isInside( Writer::Array ) ); endArray(); { auto totals = m_objectWriters.top().write( "totals"_sr ).writeObject(); writeCounts( totals.write( "assertions"_sr ).writeObject(), runStats.totals.assertions ); writeCounts( totals.write( "test-cases"_sr ).writeObject(), runStats.totals.testCases ); } endObject(); } }; }
```

---
[Known or Inferred Dependencies (Optional)]
File name : Catch2/src/catch2/catch_totals.hpp
```cpp
namespace Catch { struct Totals { public Counts assertions; public Counts testCases; public const Totals operator- (const Totals & other); public  Totals & operator+= (const Totals & other); public const Totals delta (const Totals & prevTotals); public Totals Totals::operator - ( Totals const& other ) const; public Totals& Totals::operator += ( Totals const& other ); public Totals Totals::delta( Totals const& prevTotals ) const; }; }}
```

File name : Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp
```cpp
namespace Catch { struct TestRunStats { public TestRunInfo runInfo; public  TestRunStats (const TestRunInfo & _runInfo, const Totals & _totals, bool _aborting); public TestRunStats::TestRunStats( TestRunInfo const& _runInfo, Totals const& _totals, bool _aborting ) : runInfo( _runInfo ), totals( _totals ), aborting( _aborting ); }; }}
```

File name : Catch2/src/catch2/internal/catch_jsonwriter.hpp
```cpp
namespace Catch { class JsonValueWriter { private std::stringstream m_sstream; private std::uint64_t m_indent_level; public  JsonValueWriter (std::ostream & os); public  JsonValueWriter (std::ostream & os, std::uint64_t indent_level); public JsonValueWriter::JsonValueWriter( std::ostream& os ): JsonValueWriter; public JsonValueWriter::JsonValueWriter( std::ostream& os, std::uint64_t indent_level ): m_os; public  JsonObjectWriter writeObject (); public  JsonArrayWriter writeArray (); public  void write (StringRef value); public  void write (bool value); private  void writeImpl (StringRef value, bool quote); public template <typename T> void write( T const& value ) &&; private template <typename T, typename = typename std::enable_if_t< !std::is_convertible<T, StringRef>::value>> void writeImpl( T const& value, bool quote_value ); public JsonObjectWriter JsonValueWriter::writeObject() &&; public JsonArrayWriter JsonValueWriter::writeArray() &&; public void JsonValueWriter::write( Catch::StringRef value ) &&; public void JsonValueWriter::write( bool value ) &&; private void JsonValueWriter::writeImpl( Catch::StringRef value, bool quote ); }; }}
```

File name : Catch2/src/catch2/internal/catch_jsonwriter.hpp
```cpp
namespace Catch { class JsonObjectWriter { private bool m_should_comma= false; private bool m_active= true; public  JsonObjectWriter (std::ostream & os); public  JsonObjectWriter (std::ostream & os, std::uint64_t indent_level); public  JsonObjectWriter (JsonObjectWriter && source); public JsonObjectWriter::JsonObjectWriter( std::ostream& os ): JsonObjectWriter; public JsonObjectWriter::JsonObjectWriter( std::ostream& os, std::uint64_t indent_level ): m_os; public JsonObjectWriter::JsonObjectWriter( JsonObjectWriter&& source ) noexcept: m_os; public  void ~JsonObjectWriter (); public  JsonValueWriter write (StringRef key); public JsonObjectWriter& operator=( JsonObjectWriter&& source ) = delete; public JsonObjectWriter::~JsonObjectWriter(); public JsonValueWriter JsonObjectWriter::write( StringRef key ); }; }}
```

File name : Catch2/src/catch2/reporters/catch_reporter_json.hpp
```cpp
namespace Catch { class JsonReporter : public StreamingReporterBase { private Timer m_testCaseTimer; private std::stack<JsonObjectWriter> m_objectWriters= {}; private std::stack<JsonArrayWriter> m_arrayWriters= {}; private std::stack<Writer> m_writers= {}; private bool m_startedListing= false; public  JsonReporter (ReporterConfig && config); public JsonReporter::JsonReporter( ReporterConfig&& config ): StreamingReporterBase; public  void ~JsonReporter () override; public static std::string getDescription (); public  void testRunStarting (const TestRunInfo & runInfo) override; public  void testRunEnded (const TestRunStats & runStats) override; public  void testCaseStarting (const TestCaseInfo & tcInfo) override; public  void testCaseEnded (const TestCaseStats & tcStats) override; public  void testCasePartialStarting (const TestCaseInfo & tcInfo, uint64_t index) override; public  void testCasePartialEnded (const TestCaseStats & tcStats, uint64_t index) override; public  void sectionStarting (const SectionInfo & sectionInfo) override; public  void sectionEnded (const SectionStats & sectionStats) override; public  void assertionStarting (const AssertionInfo & assertionInfo) override; public  void assertionEnded (const AssertionStats & assertionStats) override; public  void benchmarkPreparing (StringRef name) override; public  void benchmarkStarting (const BenchmarkInfo & unnamed) override; public  void benchmarkEnded (const BenchmarkStats<> & unnamed) override; public  void benchmarkFailed (StringRef error) override; public  void listReporters (const std::vector<ReporterDescription> & descriptions) override; public  void listListeners (const std::vector<ListenerDescription> & descriptions) override; public  void listTests (const std::vector<TestCaseHandle> & tests) override; public  void listTags (const std::vector<TagInfo> & tags) override; private  JsonArrayWriter & startArray (); private  JsonArrayWriter & startArray (StringRef key); private  JsonObjectWriter & startObject (); private  JsonObjectWriter & startObject (StringRef key); private  void endObject (); private  void endArray (); private  bool isInside (Writer writer); private  void startListing (); private  void endListing (); public JsonReporter::~JsonReporter(); private JsonArrayWriter& JsonReporter::startArray(); private JsonArrayWriter& JsonReporter::startArray( StringRef key ); private JsonObjectWriter& JsonReporter::startObject(); private JsonObjectWriter& JsonReporter::startObject( StringRef key ); private void JsonReporter::endObject(); private void JsonReporter::endArray(); private bool JsonReporter::isInside( Writer writer ); private void JsonReporter::startListing(); private void JsonReporter::endListing(); public std::string JsonReporter::getDescription(); public void JsonReporter::testRunStarting( TestRunInfo const& runInfo ); public void JsonReporter::testRunEnded(TestRunStats const& runStats); public void JsonReporter::testCaseStarting( TestCaseInfo const& tcInfo ); public void JsonReporter::testCaseEnded( TestCaseStats const& tcStats ); public void JsonReporter::testCasePartialStarting( TestCaseInfo const& /*tcInfo*/, uint64_t index ); public void JsonReporter::testCasePartialEnded( TestCaseStats const& tcStats, uint64_t /*index*/ ); public void JsonReporter::sectionStarting( SectionInfo const& sectionInfo ); public void JsonReporter::sectionEnded( SectionStats const& /*sectionStats */); public void JsonReporter::assertionStarting( AssertionInfo const& /*assertionInfo*/ ); public void JsonReporter::assertionEnded( AssertionStats const& assertionStats ); public void JsonReporter::benchmarkPreparing( StringRef name ); public void JsonReporter::benchmarkStarting( BenchmarkInfo const& ); public void JsonReporter::benchmarkEnded( BenchmarkStats<> const& ); public void JsonReporter::benchmarkFailed( StringRef error ); public void JsonReporter::listReporters( std::vector<ReporterDescription> const& descriptions ); public void JsonReporter::listListeners( std::vector<ListenerDescription> const& descriptions ); public void JsonReporter::listTests( std::vector<TestCaseHandle> const& tests ); public void JsonReporter::listTags( std::vector<TagInfo> const& tags ); }; }}
```

File name : Catch2/src/catch2/reporters/catch_reporter_json.hpp
```cpp
namespace Catch { namespace JsonReporter { enum class Writer { Object = 0, Array = 1 }; }} }}
```


--- PROMPT END ---
