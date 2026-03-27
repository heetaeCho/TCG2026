from domain.prompt_creator.reconstructor.plugins.renderers.IRenderer import IRenderer

class EnumRenderer(IRenderer):
    def __init__(self, db):
        self.db = db

    def render(self, row: tuple) -> str:
        NAME_IDX = 2
        QNAME_IDX = 3
        TAG_TYPE_IDX = 1
        BODY_IDX = 4

        name = row[NAME_IDX]
        qualified_name = row[QNAME_IDX]
        tag_type = row[TAG_TYPE_IDX] or "enum"
        body = row[BODY_IDX] or ""
        # print(row)

        ns_parts, enum_name = self._parse_qualified_name(qualified_name)

        body = body.replace('\n', " ").replace('\t', " ")
        lines = []

        for ns in ns_parts:
            lines.append(f"namespace {ns} {{")

        lines.append(f"{tag_type} {enum_name} {{ {body} }};")

        for ns in reversed(ns_parts):
            lines.append("}}")

        FILE_ID_IDX = -3
        file_id = row[FILE_ID_IDX]
        file_name = super().get_file_name(self.db, file_id)
        line = f"File name : {file_name}\n" + "```cpp\n"+ " ".join(lines) + "\n```\n"
        return line

    def _parse_qualified_name(self, qname: str) -> tuple[list[str], str]:
        parts = qname.split("::")
        if len(parts) <= 1:
            return [], qname
        return parts[:-1], parts[-1]
