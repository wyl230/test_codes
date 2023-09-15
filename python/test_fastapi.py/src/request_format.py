from pydantic.main import BaseModel
from typing import List


class Test(BaseModel):
    A: int | None


class Empty(BaseModel):
    pass


class single_id(BaseModel):
    insId: int


class TerminalConfig(BaseModel):
    totalNums: int
    terminalType: str
    locationType: str
    modelType: str
    model: str
    longitude: float
    latitude: float
    height: float
    range: int
    traceType: str
    realStartTime: int
    simulationStartTime: int
    simulationStopTime: int
    timeStep: int


class TerminalsConfig(BaseModel):
    config: List[TerminalConfig]
