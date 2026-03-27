from abc import ABC, abstractmethod

class IDBAdapter(ABC):
    @abstractmethod
    def select(self, query: str) -> list[tuple]:
        pass
