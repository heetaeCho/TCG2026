# domain/pipeline.py
from abc import ABC, abstractmethod

class IPipeline(ABC):
    @abstractmethod
    def construct(self, input_data):
        pass
