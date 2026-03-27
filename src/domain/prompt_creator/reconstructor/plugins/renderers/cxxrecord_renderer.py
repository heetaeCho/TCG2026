from domain.prompt_creator.reconstructor.plugins.renderers.IRenderer import IRenderer
import re

class CXXRecordRenderer(IRenderer):
    def __init__(self, db):
        self.db = db

    def render(self, row: tuple) -> str:
        NAME_IDX = 1
        QNAME_IDX = 2
        RECORD_TYPE_IDX = 3
        INHERITANCE_IDX = 4
        TEMPLATE_IDX = 5
        ACCESS_IDX = 6

        FILE_ID_IDX = -3
        NS_ID_IDX = -2
        CLS_ID_IDX = 0

        file_id = row[FILE_ID_IDX]
        ns_id = row[NS_ID_IDX]
        cls_id = row[CLS_ID_IDX]

        related_map = self._collect_related_rows(row)

        name = row[NAME_IDX]
        qualified_name = row[QNAME_IDX]
        record_type = row[RECORD_TYPE_IDX] or "class"
        inheritances = row[INHERITANCE_IDX]
        template = row[TEMPLATE_IDX]
        access = row[ACCESS_IDX]

        res_map = self._parse_qname(qualified_name)
        ns_parts = res_map["ns"]
        cls_parts = res_map["cls"]

        typedefs = self.get_typedef(file_id)
        macros = self.get_macro(file_id)

        lines = []
        for macro in macros:
            lines.append(macro[1])

        for ns in ns_parts:
            lines.append(f"namespace {ns} {{")
            for typedef in typedefs:
                if typedef[-1] == -1:
                    lines.append(typedef[1]+";")

        if template:
            lines.append(f"{template}")

        decl_line = ""
        for class_name in cls_parts:
            decl_line += f"{record_type} {class_name}"
            if inheritances:
                decl_line += f" : {inheritances}"
            decl_line += " {"
            for typedef in typedefs:
                if typedef[-1] != -1:
                    lines.append(typedef[1]+";")

        lines.append(decl_line)
        for field in related_map['fields']:
            lines.append(f'{field}')

        for cstr_decl in related_map['cstr_decls']:
            lines.append(f'{cstr_decl}')
        for cstr_def in related_map['cstr_defs']:
            cstr_def = ' '.join(([elem for elem in cstr_def.split('\n') if elem != '' and not elem.strip().startswith('//')]))
            cstr_def = ' '.join(cstr_def.replace('\n', " ").replace('\t', " ").split())
            lines.append(f'{cstr_def}')

        for func_decl in related_map['func_decls']:
            lines.append(f'{func_decl}')
        for func_def in related_map['func_defs']:
            func_def = ' '.join(([elem for elem in func_def.split('\n') if elem != '' and not elem.strip().startswith('//')]))
            func_def = ' '.join(func_def.replace('\n', " ").replace('\t', " ").split())
            lines.append(f'{func_def}')

        lines.append("};")

        for ns in reversed(ns_parts):
            lines.append("}}")

        file_name = super().get_file_name(self.db, file_id)
        line = f"File name : {file_name}\n" + "```cpp\n"+ " ".join(lines) + "\n```\n"

        return line
    
    def get_typedef(self, file_id):
        rows = self.db.select(f"SELECT * FROM Typedef where file_id = {file_id}")
        return rows

    def get_macro(self, file_id):
        def endswith_numeric_expression(line: str) -> bool:
            line = line.strip()

            # 빈 줄이나 세미콜론만 있는 경우 제외
            if not line or line.endswith(';') and len(line.strip(';')) == 0:
                return False

            # 괄호로 끝나는 경우: (...123)
            if line.endswith(')'):
                open_idx = line.rfind('(')
                if open_idx != -1:
                    inside = line[open_idx+1:-1].strip()

                    # 단순 숫자인지 확인
                    try:
                        if inside.startswith(('-0x', '0x', '-0X', '0X')):
                            int(inside, 16)
                            return True
                        float(inside)
                        return True
                    except ValueError:
                        return False

                # 괄호는 있는데 숫자 아님
                return False

            # 괄호로 끝나지 않고, 다른 토큰으로 끝나는 경우
            # 마지막 "단어"가 숫자면 OK
            tokens = line.split()
            if not tokens:
                return False

            last = tokens[-1]

            # 음수 처리
            is_negative = last.startswith('-')
            if is_negative:
                last = last[1:]

            try:
                if last.startswith(('0x', '0X')):
                    int(last, 16)
                    return True
                float(last)
                return True
            except ValueError:
                return False
        rows = self.db.select(f"SELECT * FROM Macro where file_id = {file_id}")
        res = []
        for row in rows:
            if endswith_numeric_expression(row[1]):
                res.append(row)
        return res

    def _parse_qname(self, qname):
        parts = qname.split("::")
        ns_query = "SELECT 1 FROM Namespace where name = '{}'"
        cls_query = "SELECT 1 FROM CXXRecord where name = '{}'"

        res_map = {"ns":[], "cls":[]}

        for name in parts:
            res = self.db.is_exist(ns_query.format(name))
            if res:
                res_map["ns"].append(name)
            else:
                res = self.db.is_exist(cls_query.format(name))
                if res:
                    res_map["cls"].append(name)
        return res_map

    def _collect_related_rows(self, row: tuple):
        # TODO: 실제 DB 쿼리 로직 구현
        cxxrecord_id = row[0]
        field_renderer = FieldRenderer()
        function_decl_renderer = FunctionDeclRenderer()
        constructor_decl_renderer = ConstructorDeclRenderer()
        constructor_def_renderer = ConstructorDefRenderer()
        function_def_renderer = FunctionDefRenderer()

        # print("\n=============================================================================")
        # print("===================== In CXXRecord For Field ======================")
        fields_1 = self.db.select(f"SELECT * FROM Field where cxxrecord_id = {cxxrecord_id}")
        fields_2 = self.db.select(f"SELECT * FROM Friend where cxxrecord_id = {cxxrecord_id}")

        # print("===================== In CXXRecord For Decal ======================")
        cstr_decls = self.db.select(f"SELECT * FROM ConstructorDeclaration where cxxrecord_id = {cxxrecord_id}")
        func_decls = self.db.select(f"SELECT * FROM FunctionDeclaration where cxxrecord_id = {cxxrecord_id}")
        # print("===================== In CXXRecord For Def ======================")
        cstr_defs = self.db.select(f"SELECT * FROM ConstructorDefinition where cxxrecord_id = {cxxrecord_id}")
        func_defs = self.db.select(f"SELECT * FROM FunctionDefinition where cxxrecord_id = {cxxrecord_id}")

        const_fields = []
        const_func_decls = []
        const_cstr_decls = []
        const_func_defs = []
        const_cstr_defs = []

        for field in fields_1:
            field = field_renderer.render(field, fields_2)
            const_fields.append(field)
        # print(func_decls)
        for func_decl in func_decls:
            func_decl = function_decl_renderer.render(func_decl)
            const_func_decls.append(func_decl)
        # print(cstr_decls)
        for cstr_decl in cstr_decls:
            cstr_decl = constructor_decl_renderer.render(cstr_decl)
            const_cstr_decls.append(cstr_decl.replace("\n", " "))

        for cstr_def in cstr_defs:
            cstr_def = constructor_def_renderer.render(cstr_def)
            const_cstr_defs.append(cstr_def.replace("\n", " "))
        
        for func_def in func_defs:
            func_def = function_def_renderer.render(func_def)
            const_func_defs.append(func_def)
        # print("\n==================== In CXXRecord For Field and Decal End ====================")
        # print("==============================================================================\n")
        return {
            'fields': const_fields,
            'func_decls': const_func_decls,
            'cstr_decls': const_cstr_decls,
            'func_defs': const_func_defs,
            'cstr_defs': const_cstr_defs
        }
        
class FieldRenderer(IRenderer):
    def render(self, row: tuple, rows) -> str: # rows = list(tuple) => friends
        FIELD_NAME_IDX = 1
        FIELD_TYPE_IDX = 2
        FIELD_VALUE_IDX = 3
        FIELD_IS_STATIC_IDX = 5
        FIELD_ACCESS_IDX = 6

        _name = row[FIELD_NAME_IDX]
        _type = row[FIELD_TYPE_IDX]
        _value = row[FIELD_VALUE_IDX]
        _access = row[FIELD_ACCESS_IDX]
        _static = row[FIELD_IS_STATIC_IDX]

        if _type == "class":
            FRIEND_CONTENT_IDX = 1
            for friend in rows:
                if friend[FRIEND_CONTENT_IDX].endswith(_name):
                    return friend[FRIEND_CONTENT_IDX]+";"

        line = ' '.join([_type, _name])
        if _static == 1:
            line = 'static' + ' ' + line
        if _value != '':
            line += f'= {_value}'
        line = _access + ' ' + line + ';'
        return line

class FunctionDeclRenderer(IRenderer):
    def render(self, row: tuple) -> str:
        FUNCTION_DECL_NAME_IDX = 1
        FUNCTION_DECL_ACCESS_IDX = 3
        FUNCTION_DECL_TEMPLATE_IDX = 4
        FUNCTION_DECL_RETURN_TYPE_IDX = 5
        FUNCTION_DECL_PARAMETERS_IDX = 6
        FUNCTION_DECL_IS_STATIC_IDX = 7
        FUNCTION_DECL_IS_VIRTUAL_IDX = 8
        FUNCTION_DECL_IS_OVERRIDE_IDX = 9
        FUNCTION_DECL_IS_FINAL_IDX = 10
        FUNCTION_DECL_IS_FRIEND_IDX = 11
        FUNCTION_DECL_IS_CONST_IDX = 12

        _name = row[FUNCTION_DECL_NAME_IDX]
        _access = row[FUNCTION_DECL_ACCESS_IDX]
        _template = row[FUNCTION_DECL_TEMPLATE_IDX]
        _return_type = row[FUNCTION_DECL_RETURN_TYPE_IDX]
        _prarameters = row[FUNCTION_DECL_PARAMETERS_IDX]
        _is_static = row[FUNCTION_DECL_IS_STATIC_IDX]
        _is_virtual = row[FUNCTION_DECL_IS_VIRTUAL_IDX]
        _is_override = row[FUNCTION_DECL_IS_OVERRIDE_IDX]
        _is_final = row[FUNCTION_DECL_IS_FINAL_IDX]
        _is_friend = row[FUNCTION_DECL_IS_FRIEND_IDX]
        _is_const = row[FUNCTION_DECL_IS_CONST_IDX]

        line = ''
        if _is_static == 1:
            line = 'static' + ' ' + line
        if _is_const == 1:
            line = 'const' + ' ' + line
        if _is_virtual == 1:
            line = 'virtual' + ' ' + line
        if _is_friend == 1:
            line = 'friend' + ' ' + line
        if _is_final == 1:
            line = 'final' + ' ' + line

        line = line.strip() + ' ' + _return_type + ' ' + _name + ' (' + _prarameters + ')'
        
        if _is_override == 1:
            line = line + ' ' + 'override'
        
        line = _access + ' ' + line
        if _template != '':
            line = _template + ' ' + line

        line += ';'
        return line

class ConstructorDeclRenderer(IRenderer):
    def render(self, row: tuple) -> str:
        CONSTRUCTOR_DECL_NAME_IDX = 1
        CONSTRUCTOR_DECL_ACCESS_IDX = 3
        CONSTRUCTOR_DECL_TEMPLATE_IDX = 4
        CONSTRUCTOR_DECL_PARAMETERS_IDX = 5
        CONSTRUCTOR_DECL_IS_CONST_IDX = 6
        CONSTRUCTOR_DECL_IS_EXPLICIT_IDX = 7
        CONSTRUCTOR_DECL_IS_DELETE_IDX = 8

        _name = row[CONSTRUCTOR_DECL_NAME_IDX]
        _access = row[CONSTRUCTOR_DECL_ACCESS_IDX]
        _template = row[CONSTRUCTOR_DECL_TEMPLATE_IDX]
        _parameters = row[CONSTRUCTOR_DECL_PARAMETERS_IDX]
        _is_const = row[CONSTRUCTOR_DECL_IS_CONST_IDX]
        _is_explicit = row[CONSTRUCTOR_DECL_IS_EXPLICIT_IDX]
        _is_delete = row[CONSTRUCTOR_DECL_IS_DELETE_IDX]

        line = ''
        if _is_const == 1:
            line = 'const' + ' ' + line
        if _is_explicit == 1:
            line = 'explicit' + ' ' + line

        line = line.strip() + ' ' + _name + ' (' + _parameters + ')'

        if _is_delete == 1:
            line = line + ' = ' + 'delete'

        line = _access + ' ' + line
        if _template != '' :
            line = _template + ' ' + line
        
        line += ';'
        return line
    
class FunctionDefRenderer(IRenderer):
    #['function_def_id', 'name', 'qualified_name', 'access', 'template', 'return_type', 'parameters', 'body', 'definition', 'file_id', 'namespace_id', 'cxxrecord_id']
    def render(self, row: tuple) -> str:
        FUNCTION_DEF_ACCESS_IDX = 3
        FUNCTION_DEF_TEMPLATE_IDX = 4
        FUNCTION_DEF_DEFINITION_IDX = 8

        _access = row[FUNCTION_DEF_ACCESS_IDX]
        _template = row[FUNCTION_DEF_TEMPLATE_IDX]
        _definition = row[FUNCTION_DEF_DEFINITION_IDX]
        
        line = ''
        line = _definition.split('{')[0].strip()

        line = _access.strip() + ' ' + line.strip()
        # if _template != '' :
        #     line = _template + ' ' + line
        
        line += ';'
        return line

class ConstructorDefRenderer(IRenderer):
    #['constructor_def_id', 'name', 'qualified_name', 'access', 'template', 'parameters', 'body', 'definition', 'file_id', 'namespace_id', 'cxxrecord_id']
    def render(self, row: tuple) -> str:
        CONSTRUCTOR_DEF_NAME_IDX = 1
        CONSTRUCTOR_DEF_ACCESS_IDX = 3
        CONSTRUCTOR_DEF_TEMPLATE_IDX = 4
        CONSTRUCTOR_DEF_PARAMETERS_IDX = 5
        CONSTRUCTOR_DEF_DEFINITION_IDX = 7

        _name = row[CONSTRUCTOR_DEF_NAME_IDX]
        _access = row[CONSTRUCTOR_DEF_ACCESS_IDX]
        _template = row[CONSTRUCTOR_DEF_TEMPLATE_IDX]
        _parameters = row[CONSTRUCTOR_DEF_PARAMETERS_IDX]
        _definition = row[CONSTRUCTOR_DEF_DEFINITION_IDX]

        line = ''
        line = _definition.split('{')[0].strip()

        line = _access + ' ' + line
        # if _template != '' :
        #     line = _template + ' ' + line
        
        line += ';'
        return line