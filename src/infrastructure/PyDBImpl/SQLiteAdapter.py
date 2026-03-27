import sqlite3
from adapter.IDBAdapter import IDBAdapter

class SQLiteAdapter(IDBAdapter):
    def __init__(self, db_path: str):
        self.conn = sqlite3.connect(db_path)
        self.cursor = self.conn.cursor()

    def select(self, query: str) -> list[tuple]:
        self.cursor.execute(query)
        return self.cursor.fetchall()
    
    def is_exist(self, query: str) -> bool:
        self.cursor.execute(query)
        result = self.cursor.fetchone()
        return result is not None

    def close(self):
        self.conn.close()
