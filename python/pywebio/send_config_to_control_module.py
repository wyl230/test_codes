import time
import requests
import json
import sys
import random
from constell_options import constellation_types

from get_converted_json import get_converted_json
from get_ue_info import get_ue_info


def get_xw_time():
    xw_time_stamp = 1136044800
    return int(time.time()) - xw_time_stamp


url = f"http://{sys.argv[1]}:5002/networkProtocol/evaluate/sceneConfig"
nb_url = f"http://{sys.argv[1]}:5002/networkProtocol/evaluate/nbInterferenceConfig"


def get_payload(simulationId, simulationTime, constellation_type):
    payload = {
        "simulationId": simulationId,
        "sceneObjectId": "test sceneobjectid",
        "simulationStartTime": 0,
        "simulationEndTime": 1,
        "params": {
            "networkSystem": 0,
            **(constellation_types[constellation_type]),
            "gatewayStation": [
                {
                    "id": 1,
                    "latitude": 1,
                    "longitude": 2,
                    "beamCount": 3,
                    "bandwidth": 4,
                },
                {
                    "id": 2,
                    "latitude": 0,
                    "longitude": 0,
                    "beamCount": 4,
                    "bandwidth": 0,
                },
                {
                    "id": 3,
                    "latitude": 0,
                    "longitude": 0,
                    "beamCount": 4,
                    "bandwidth": 0,
                },
                {
                    "id": 4,
                    "latitude": 0,
                    "longitude": 0,
                    "beamCount": 6,
                    "bandwidth": 0,
                },
                {
                    "id": 5,
                    "latitude": 0,
                    "longitude": 0,
                    "beamCount": 8,
                    "bandwidth": 0,
                },
            ],
            "businessTerminal": {"terminalType": "string"},
            "sceneType": 0,
            "evaluateType": [0],
            "policyOptions": {
                "accessControlStrategy": {
                    "ueStarAccessPolicy": 0,
                    "sgnbAdmissionControlPolicy": 0,
                },
                "switchingPolicy": {
                    "ueStarSwitchingPolicy": 0,
                    "sgnbAdmissionControlPolicy": 0,
                },
                "feedBearerSelectionPolicy": {
                    "uplinkStarPolicy": 0,
                    "downlinkStationPolicy": 0,
                },
                "wirelessResourceSchedulingPolicy": {
                    "wirelessResourceAllocationPolicy": 0,
                    "beamHoppingPolicy": 0,
                },
                "interferenceAvoidancePolicy": 0,
                "routingPolicy": {
                    "centralizedConnectionlessRoutingPolicy": 0,
                    "distributedConnectionlessRoutingPolicy": 0,
                    "centralizedConnectionOrientedRoutingPolicy": 0,
                },
                "energyStrategy": 0,
            },
            **get_ue_info(),
            **get_converted_json(simulationTime),
            "backgroundStream": {
                "open": 0,
                "info": [
                    {
                        "srcSat": 0,
                        "dstSat": 0,
                        "level": 0,
                        "type": 0,
                        "startTime": 0,
                        "endTime": 0,
                    }
                ],
            },
            "backgroundLoad": [],
            "breakdownType": {"info": [{"nodeType": 0, "type": 0, "algorithm": 0}]},
            "breakdownFileConfig": "string",
        },
    }

    # 打印payload
    payload = json.dumps(payload, indent=4)
    print(payload)
    return payload


headers = {"Content-Type": "application/json"}


def send_http(simulationId, simulationTime, constellation_type):
    print(url)
    response = requests.request(
        "POST",
        url,
        headers=headers,
        data=get_payload(simulationId, simulationTime, constellation_type),
    )
    print(response.text)


def get_nb_interference_payload(simulationId, simulationTime, constellation_type):
    payload = {
        "simulationId": simulationId,
        "sceneObjectId": "test sceneobjectid",
        "params": {
            "networkSystem": 0,
            **(constellation_types[constellation_type]),
            "PMBCHFrame": {
                "frames": [
                    {"frameId": 1, "beamList": [1]},
                    {"frameId": 2, "beamList": [2]},
                    {"frameId": 3, "beamList": [3]},
                    {"frameId": 4, "beamList": [4]},
                    {"frameId": 5, "beamList": [5, 17, 30, 34, 38, 42]},
                    {"frameId": 6, "beamList": [6, 18, 29, 33, 37, 41]},
                    {"frameId": 7, "beamList": [7, 19, 32, 36, 40, 44]},
                    {"frameId": 8, "beamList": [8, 20, 31, 35, 39, 43]},
                    {"frameId": 9, "beamList": [9, 13, 22, 26, 46, 50]},
                    {"frameId": 10, "beamList": [10, 14, 21, 25, 45, 49]},
                    {"frameId": 11, "beamList": [11, 15, 24, 28, 48, 52]},
                    {"frameId": 12, "beamList": [12, 16, 23, 27, 47, 51]},
                    {"frameId": 13, "beamList": []},
                ],
                "framesAggregation": [
                    {"aggregationId": "G1", "frameList": [1, 2, 3, 4]},
                    {"aggregationId": "G2", "frameList": [5, 6, 7, 8]},
                    {"aggregationId": "G3", "frameList": [9, 10, 11, 12]},
                    {"aggregationId": "G4", "frameList": [13]},
                ],
            },
            "nbLatitudeCloseStrategy": [
                {
                    "needLatitudeClose": True,
                    "firstLatitude": 70,
                    "secondLatitude": 75,
                    "thirdLatitude": 80,
                    "orbitIdList": [1, 3, 5],
                },
                {
                    "needLatitudeClose": False,
                    "firstLatitude": 90,
                    "secondLatitude": 90,
                    "thirdLatitude": 90,
                    "orbitIdList": [2, 4, 6],
                },
            ],
            "nbFrameCloseStrategy": True,
            "nbOverlappingCloseStrategy": {
                "needOverlappingClose": True,
                "scatterNum": 9,
            },
            "nbInterferenceSatList": [
                {
                    "satId": "B0001_0001",
                    "frequencyPoint": 60.0,
                    "framesAggregationList": ["G3", "G2", "G1", "G4"],
                },
                {
                    "satId": "B0001_0002",
                    "frequencyPoint": 80.0,
                    "framesAggregationList": ["G2", "G1", "G3", "G4"],
                },
                {
                    "satId": "B0001_0003",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0004",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0005",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0006",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0007",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0008",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0009",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0001_0010",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0001",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0002",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0003",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0004",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0005",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0006",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0007",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0008",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0009",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0002_0010",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0001",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0002",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0003",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0004",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0005",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0006",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0007",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0008",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0009",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0003_0010",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0001",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0002",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0003",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0004",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0005",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0006",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0007",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0008",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0009",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0004_0010",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0001",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0002",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0003",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0004",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0005",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0006",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0007",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0008",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0009",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0005_0010",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0001",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0002",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0003",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0004",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0005",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0006",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0007",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0008",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0009",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
                {
                    "satId": "B0006_0010",
                    "frequencyPoint": 100.0,
                    "framesAggregationList": ["G1", "G2", "G3", "G4"],
                },
            ],
        },
    }

    # 打印payload
    payload = json.dumps(payload, indent=4)
    print(payload)
    return payload


def send_nb_interference_http(simulationId, simulationTime, constellation_type):
    print(nb_url)
    response = requests.request(
        "POST",
        nb_url,
        headers=headers,
        data=get_nb_interference_payload(
            simulationId, simulationTime, constellation_type
        ),
    )
    print("response", response.text)


if __name__ == "__main__":
    # print(get_payload())
    # send_http(str(time.time()), 1, "167")
    nb_url = f"http://{sys.argv[1]}:5003/networkProtocol/evaluate/nbInterferenceConfig"
    send_nb_interference_http(str(time.time()), 1, "168")
