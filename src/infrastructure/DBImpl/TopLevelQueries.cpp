#include "TopLevelQueries.hpp"

namespace NewTCG::infrastructure::DBImpl {
    std::map<std::string, const char*> queries = {
        {"File", 
        "CREATE TABLE IF NOT EXISTS File ("
        "file_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL UNIQUE);"},

        {"Namespace",
        "CREATE TABLE IF NOT EXISTS Namespace ("
        "namespace_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "parent_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (parent_id) REFERENCES Namespace(namespace_id));"},

        {"CXXRecord", 
        "CREATE TABLE IF NOT EXISTS CXXRecord ("
        "cxxrecord_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "record_type TEXT NOT NULL, "
        "inheritances TEXT, "
        "template TEXT, " 
        "access TEXT, " 
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "parent_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (parent_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"ConstructorDeclaration",
        "CREATE TABLE IF NOT EXISTS ConstructorDeclaration ("
        "constructor_decl_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "access TEXT, "
        "template TEXT, " 
        "parameters TEXT, "
        "is_const BOOLEAN NOT NULL, "
        "is_explicit BOOLEAN NOT NULL, "
        "is_delete BOOLEAN NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"ConstructorDefinition", 
        "CREATE TABLE IF NOT EXISTS ConstructorDefinition ("
        "constructor_def_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "access TEXT, "
        "template TEXT, " 
        "parameters TEXT, "
        "body TEXT NOT NULL, "
        "definition TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(File_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"FunctionDeclaration", 
        "CREATE TABLE IF NOT EXISTS FunctionDeclaration ("
        "function_decl_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "access TEXT, "
        "template TEXT, " 
        "return_type TEXT NOT NULL, "
        "parameters TEXT, "
        "is_static BOOLEAN NOT NULL, "
        "is_virtual BOOLEAN NOT NULL, "
        "is_override BOOLEAN NOT NULL, "
        "is_final BOOLEAN NOT NULL, "
        "is_friend BOOLEAN NOT NULL, "
        "is_const BOOLEAN NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"FunctionDefinition", 
        "CREATE TABLE IF NOT EXISTS FunctionDefinition ("
        "function_def_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "access TEXT, "
        "template TEXT, " 
        "return_type TEXT NOT NULL, "
        "parameters TEXT, "
        "body TEXT, "
        "definition TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Enum",
        "CREATE TABLE IF NOT EXISTS Enum ("
        "enum_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "type TEXT NOT NULL, "
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "variables TEXT, "
        "access TEXT, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Record",
        "CREATE TABLE IF NOT EXISTS Record ("
        "record_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "type TEXT NOT NULL, "   // struct or union
        "name TEXT NOT NULL, "
        "qualified_name TEXT NOT NULL, "
        "variables TEXT, "
        "access TEXT, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Field",
        "CREATE TABLE IF NOT EXISTS Field ("
        "field_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "value TEXT, "
        "is_const BOOLEAN NOT NULL, "
        "is_static BOOLEAN NOT NULL, "
        "access TEXT, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Variable", 
        "CREATE TABLE IF NOT EXISTS Variable ("
        "variable_id INTEGER PRIMARY KEY AUTOINCREMENT, "
        "name TEXT NOT NULL, "
        "type TEXT NOT NULL, "
        "value TEXT, "
        "is_const BOOLEAN NOT NULL, "
        "is_static BOOLEAN NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES FileInfo(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES NamespaceInfo(namespace_id));"},

        {"Typedef",
        "CREATE TABLE IF NOT EXISTS Typedef ("
        "typedef_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"NamespaceAlias",
        "CREATE TABLE IF NOT EXISTS NamespaceAlias ("
        "namespace_alias_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"TypeAlias",
        "CREATE TABLE IF NOT EXISTS TypeAlias ("
        "type_alias_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Friend",
        "CREATE TABLE IF NOT EXISTS Friend ("
        "friend_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"UsingDirective",
        "CREATE TABLE IF NOT EXISTS UsingDirective ("
        "using_directive_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Using",
        "CREATE TABLE IF NOT EXISTS UsingDecl ("
        "using_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"Macro",
        "CREATE TABLE IF NOT EXISTS Macro ("
        "macro_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "content TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "namespace_id INTEGER, "
        "cxxrecord_id INTEGER, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "FOREIGN KEY (namespace_id) REFERENCES Namespace(namespace_id), "
        "FOREIGN KEY (cxxrecord_id) REFERENCES CXXRecord(cxxrecord_id));"},

        {"FunctionCallTrace",
        "CREATE TABLE IF NOT EXISTS FunctionCallTrace ("
        "function_call_trace_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "caller_id INTEGER NOT NULL, "
        "caller_type TEXT NOT NULL, "
        "callee_id INTEGER NOT NULL, "
        "callee_type TEXT NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "UNIQUE (caller_id, caller_type, callee_id, callee_type));"},

        {"VarTrace",
        "CREATE TABLE IF NOT EXISTS VarTrace ("
        "var_trace_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "caller_id INTEGER NOT NULL, "
        "caller_type TEXT NOT NULL, "
        "var_id INTEGER NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "UNIQUE (caller_id, caller_type, var_id));"},

        {"EnumTrace",
        "CREATE TABLE IF NOT EXISTS EnumTrace ("
        "enum_trace_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "caller_id INTEGER NOT NULL, "
        "caller_type TEXT NOT NULL, "
        "enum_id INTEGER NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "UNIQUE (caller_id, caller_type, enum_id));"},

        {"RecordTrace",
        "CREATE TABLE IF NOT EXISTS RecordTrace ("
        "record_trace_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "caller_id INTEGER NOT NULL, "
        "caller_type TEXT NOT NULL, "
        "record_id INTEGER NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "UNIQUE (caller_id, caller_type, record_id));"},

        {"CXXRecordTrace",
        "CREATE TABLE IF NOT EXISTS CXXRecordTrace ("
        "cxxrecord_trace_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "caller_id INTEGER NOT NULL, "
        "caller_type TEXT NOT NULL, "
        "cxxrecord_id INTEGER NOT NULL, "
        "file_id INTEGER NOT NULL, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "UNIQUE (caller_id, caller_type, cxxrecord_id));"},

        {"HeaderTrace",
        "CREATE TABLE IF NOT EXISTS HeaderTrace ("
        "header_trace_id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "file_id INTEGER NOT NULL, "
        "headers TEXT, "
        "FOREIGN KEY (file_id) REFERENCES File(file_id), "
        "UNIQUE (file_id, headers));"}
    };
}
