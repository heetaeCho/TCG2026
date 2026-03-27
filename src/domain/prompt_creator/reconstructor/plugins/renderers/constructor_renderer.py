from domain.prompt_creator.reconstructor.plugins.renderers.IRenderer import IRenderer

class ConstructorRenderer(IRenderer):
    def __init__(self, db):
        self.db = db

    def render(self, row: tuple, is_target=False) -> str:
        NAME_IDX = 1
        PARAMS_IDX = 5
        BODY_IDX = 6
        DEF_IDX = 7
        QNAME_IDX = 2
        FILE_ID_IDX = -3

        name = row[NAME_IDX]
        parameters = row[PARAMS_IDX] or ""
        body = row[BODY_IDX] or "{}"
        definition = row[DEF_IDX]
        qualified_name = row[QNAME_IDX]
        file_id = row[FILE_ID_IDX]

        # ns_parts, class_name, ctor_name = self._parse_qualified_name(qualified_name)
        name_map = self._parse_qname(qualified_name)
        ns_parts = name_map["ns"]
        class_parts = name_map["cls"]
        ctor_name = name_map["func"][0]
        file_name = super().get_file_name(self.db, file_id)

        # body = body.replace('\n', " ").replace('\t', " ")
        definition = ' '.join(([elem for elem in definition.split('\n') if elem != '' and not elem.strip().startswith('//')]))
        definition = ' '.join(definition.replace('\n', " ").replace('\t', " ").split())
        if class_parts:
            definition = definition.replace("{}::{}".format("::".join(class_parts), ctor_name), "{}".format(ctor_name))

        typedefs = self.get_typedef(file_id)
        macros = self.get_macro(file_id)

        lines = []
        if not (file_name.endswith(".h") or file_name.endswith(".hpp")):
            for macro in macros:
                lines.append("#define {}".format(' '.join(macro[1].split())))
            for typedef in typedefs:
                lines.append(typedef[1])

        TEMPLATE_IDX = 4
        template = row[TEMPLATE_IDX]

        for ns in ns_parts:
            lines.append(f"namespace {ns} {{")

        for cls in class_parts:
            if cls.startswith("struct_"):
                lines.append(cls.replace("_", " "))
            else:
                lines.append(f"class {cls} {{")
        lines.append("public:")
        # lines.append(f"{template}")
        # lines.append(f"{ctor_name}({parameters}) {body}")
        lines.append(f"{definition}")
        lines.append("};")

        for ns in reversed(ns_parts):
            lines.append("}}")

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
        cls_query = "SELECT * FROM CXXRecord where name = '{}'"

        res_map = {"ns":[], "cls":[], "func":[]}
        res_map["func"].append(parts[-1])

        for name in parts[:-1]:
            res = self.db.is_exist(ns_query.format(name))
            if res:
                res_map["ns"].append(name)
            elif self.db.is_exist(cls_query.format(name)):
                res = self.db.select(cls_query.format(name))[0]
                if res:
                    RECORD_TYPE_IDX = 3
                    if res[RECORD_TYPE_IDX] == 'class':
                        res_map["cls"].append(name)
                    else:
                        res_map["cls"].append("struct_" + name)
        return res_map