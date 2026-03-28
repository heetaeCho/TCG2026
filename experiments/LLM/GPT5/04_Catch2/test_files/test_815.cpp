The TEST_ID is 815

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
File name : Catch2/src/catch2/reporters/catch_reporter_compact.cpp
```cpp
namespace Catch { class CompactReporter { public: void sectionEnded(SectionStats const& _sectionStats) { double dur = _sectionStats.durationInSeconds; if ( shouldShowDuration( *m_config, dur ) ) { m_stream << getFormattedDuration( dur ) << " s: " << _sectionStats.sectionInfo.name << '\n' << std::flush; } } }; }
```

---
[Known or Inferred Dependencies (Optional)]
File name : Catch2/src/catch2/catch_section_info.hpp
```cpp
namespace Catch { struct SectionInfo { public SectionInfo( SourceLineInfo const& _lineInfo, std::string _name, const char* const = nullptr ): name(CATCH_MOVE(_name)), lineInfo(_lineInfo); }; }}
```

File name : Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp
```cpp
namespace Catch { struct SectionStats { public bool missingAssertions; public  SectionStats (SectionInfo && _sectionInfo, const Counts & _assertions, double _durationInSeconds, bool _missingAssertions); public SectionStats::SectionStats( SectionInfo&& _sectionInfo, Counts const& _assertions, double _durationInSeconds, bool _missingAssertions ) : sectionInfo( CATCH_MOVE(_sectionInfo) ), assertions( _assertions ), durationInSeconds( _durationInSeconds ), missingAssertions( _missingAssertions ); }; }}
```

File name : Catch2/src/catch2/interfaces/catch_interfaces_reporter.hpp
```cpp
namespace Catch { class IEventListener { protected ReporterPreferences m_preferences; protected const IConfig * m_config; public IEventListener( IConfig const* config ): m_config( config ); public virtual void ~IEventListener (); public virtual void noMatchingTestCases (StringRef unmatchedSpec); public virtual void reportInvalidTestSpec (StringRef invalidArgument); public virtual void testRunStarting (const TestRunInfo & testRunInfo); public virtual void testCaseStarting (const TestCaseInfo & testInfo); public virtual void testCasePartialStarting (const TestCaseInfo & testInfo, uint64_t partNumber); public virtual void sectionStarting (const SectionInfo & sectionInfo); public virtual void benchmarkPreparing (StringRef benchmarkName); public virtual void benchmarkStarting (const BenchmarkInfo & benchmarkInfo); public virtual void benchmarkEnded (const BenchmarkStats<> & benchmarkStats); public virtual void benchmarkFailed (StringRef benchmarkName); public virtual void assertionStarting (const AssertionInfo & assertionInfo); public virtual void assertionEnded (const AssertionStats & assertionStats); public virtual void sectionEnded (const SectionStats & sectionStats); public virtual void testCasePartialEnded (const TestCaseStats & testCaseStats, uint64_t partNumber); public virtual void testCaseEnded (const TestCaseStats & testCaseStats); public virtual void testRunEnded (const TestRunStats & testRunStats); public virtual void skipTest (const TestCaseInfo & testInfo); public virtual void fatalErrorEncountered (StringRef error); public virtual void listReporters (const std::vector<ReporterDescription> & descriptions); public virtual void listListeners (const std::vector<ListenerDescription> & descriptions); public virtual void listTests (const std::vector<TestCaseHandle> & tests); public virtual void listTags (const std::vector<TagInfo> & tags); public ReporterPreferences const& getPreferences() const; public IEventListener::~IEventListener(); }; }}
```

File name : Catch2/src/catch2/reporters/catch_reporter_common_base.hpp
```cpp
namespace Catch { class ReporterBase : public IEventListener { protected Detail::unique_ptr<IStream> m_wrapped_stream; protected std::ostream & m_stream; protected Detail::unique_ptr<ColourImpl> m_colour; public  ReporterBase (ReporterConfig && config); public ReporterBase::ReporterBase( ReporterConfig&& config ): IEventListener( config.fullConfig() ), m_wrapped_stream( CATCH_MOVE(config).takeStream() ), m_stream( m_wrapped_stream->stream() ), m_colour( makeColourImpl( config.colourMode(), m_wrapped_stream.get() ) ), m_customOptions( config.customOptions() ); public  void ~ReporterBase () override; public  void listReporters (const std::vector<ReporterDescription> & descriptions) override; public  void listListeners (const std::vector<ListenerDescription> & descriptions) override; public  void listTests (const std::vector<TestCaseHandle> & tests) override; public  void listTags (const std::vector<TagInfo> & tags) override; public ReporterBase::~ReporterBase(); public void ReporterBase::listReporters( std::vector<ReporterDescription> const& descriptions ); public void ReporterBase::listListeners( std::vector<ListenerDescription> const& descriptions ); public void ReporterBase::listTests(std::vector<TestCaseHandle> const& tests); public void ReporterBase::listTags(std::vector<TagInfo> const& tags); }; }}
```

File name : Catch2/src/catch2/reporters/catch_reporter_compact.hpp
```cpp
namespace Catch { class CompactReporter : public StreamingReporterBase { public  void ~CompactReporter () override; public static std::string getDescription (); public  void noMatchingTestCases (StringRef unmatchedSpec) override; public  void testRunStarting (const TestRunInfo & _testInfo) override; public  void assertionEnded (const AssertionStats & _assertionStats) override; public  void sectionEnded (const SectionStats & _sectionStats) override; public  void testRunEnded (const TestRunStats & _testRunStats) override; public std::string CompactReporter::getDescription(); public void CompactReporter::noMatchingTestCases( StringRef unmatchedSpec ); public void CompactReporter::testRunStarting( TestRunInfo const& ); public void CompactReporter::assertionEnded( AssertionStats const& _assertionStats ); public void CompactReporter::sectionEnded(SectionStats const& _sectionStats); public void CompactReporter::testRunEnded( TestRunStats const& _testRunStats ); public CompactReporter::~CompactReporter(); }; }}
```


--- PROMPT END ---
