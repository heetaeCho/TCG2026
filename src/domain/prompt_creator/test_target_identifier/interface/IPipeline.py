# domain/pipeline.py
from abc import ABC, abstractmethod

class IPipeline(ABC):
    @abstractmethod
    def identify(self, input_type, input_data):
        pass
