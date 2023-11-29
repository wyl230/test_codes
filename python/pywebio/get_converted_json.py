def get_converted_json(SimulationTime):
  return  {
    "incentiveSource": {
      "userScene": {
        "ueNum": 0,
        "info": [
          {
            "business": 1,
            "srcUe": 12,
            "dstUe": 12,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 12 * 1000 + SimulationTime,
            "endTime": 12 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 12
            }
          },
          {
            "business": 2,
            "srcUe": 1,
            "dstUe": 205,
            "type": 2,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 300 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 800000
            }
          },
          {
            "business": 3,
            "srcUe": 96,
            "dstUe": 89,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 170 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 9000
            }
          },
          {
            "business": 4,
            "srcUe": 100,
            "dstUe": 101,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 170 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 9000
            }
          },
          {
            "business": 5,
            "srcUe": 10,
            "dstUe": 20,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 120 * 1000 + SimulationTime,
            "endTime": 180 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 9000
            }
          },
          {
            "business": 6,
            "srcUe": 99,
            "dstUe": 90,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 170 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 9000
            }
          },
          {
            "business": 7,
            "srcUe": 70,
            "dstUe": 81,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 170 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 9000
            }
          },
          {
            "business": 8,
            "srcUe": 82,
            "dstUe": 83,
            "type": 22,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 80 * 1000 + SimulationTime,
            "simulationMessage": {
              "telephoneNumber": "83",
              "peerBusinessId": 9000
            }
          },
          {
            "business": 9,
            "srcUe": 4,
            "dstUe": 5,
            "type": 23,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 80 * 1000 + SimulationTime,
            "simulationMessage": {
              "pps": 5
            }
          },
          {
            "business": 10,
            "srcUe": 2,
            "dstUe": 6,
            "type": 1,
            "indication": 1,
            "prior": 2,
            "guaranteedBandwidth": 100,
            "startTime": 50 * 1000 + SimulationTime,
            "endTime": 170 * 1000 + SimulationTime,
            "simulationMessage": {
              "speedKbps": 9000
            }
          }
        ]
      }
    }
  }