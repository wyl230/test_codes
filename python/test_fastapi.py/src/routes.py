from fastapi import APIRouter

# import src.distribution.distribution_task_functions as func
from src.request_format import Test


router = APIRouter()


# *生成用户分布接口
# curl -X POST -H "Content-Type: application/json" -d '{ "config": [ { "totalNums": 300, "terminalType":"1", "locationType": "1", "modelType": "1", "model": "1", "longitude": 123.32, "latitude": 43.34, "range": 200 }, { "totalNums": 300, "terminalType":"1", "locationType": "1", "modelType": "1", "model": "1", "longitude": 123.32, "latitude": 43.34, "range": 200 } ] }' http://127.0.0.1:5001/terminal/generate


@router.post("/test")
def terminal_config(body: Test):
    return [1, 2]
