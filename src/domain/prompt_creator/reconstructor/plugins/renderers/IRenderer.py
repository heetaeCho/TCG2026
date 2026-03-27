from abc import ABC, abstractmethod

class IRenderer(ABC):
    @abstractmethod
    def render(self, row: tuple) -> str:
        pass

    def get_file_name(self, db, file_id):
        query = f"SELECT name FROM FILE where file_id = {file_id}"
        file_name = db.select(query)
        file_name = file_name[0][0]

        if 'include/' in file_name:
            file_name = file_name.split('include/')[-1]
        else:
            file_name = file_name.split('leveldb/')[-1]
        return file_name

