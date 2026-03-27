from domain.prompt_creator.reconstructor.plugins.renderers.IRenderer import IRenderer

class VariableRenderer(IRenderer):
    def __init__(self, db):
        self.db = db

    def render(self, row: tuple) -> str:
        NAME_IDX = 1
        TYPE_IDX = 2
        VALUE_IDX = 3
        NS_ID_IDX = -1

        _name = row[NAME_IDX]
        _type = row[TYPE_IDX]
        _value = row[VALUE_IDX]
        _namespace_id = row[NS_ID_IDX]

        NS_NAME_IDX = 1
        NS_FILE_ID_IDX = 2
        NS_PARENT_IDX = 3
        
        temp_namespace = []
        while _namespace_id != -1:
            ns_row = self._get_namespace(_namespace_id)
            temp_namespace.insert(0, ns_row[NS_NAME_IDX])
            _namespace_id = ns_row[NS_PARENT_IDX]
            
        lines = []
        lines.append(_type)
        lines.append("::".join(temp_namespace)+"::"+_name)
        lines.append("= " + _value)

        FILE_ID_IDX = -2
        file_id = row[FILE_ID_IDX]
        file_name = super().get_file_name(self.db, file_id)
        line = f"File name : {file_name}\n" + "```cpp\n"+ " ".join(lines) + "\n```\n"
        return line

    def _get_namespace(self, namespace_id):
        row = self.db.select(f"SELECT * FROM Namespace where namespace_id = '{namespace_id}'")
        return row[0]