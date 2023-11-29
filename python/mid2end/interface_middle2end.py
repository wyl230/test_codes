import json


def mid2end(middle_interface):
    return {
        "nbLatitudeCloseStrategy": {
            "needLatitudeClose": True,
            "nbLatitudeCloseList": [
                {
                    "orbitIdList": data["orbitIdList"],
                    "nbLatitudeCloseFrameList": [
                        {
                            "startLatitude": data["firstLatitude"],
                            "endLatitue": 90,
                            "BeamList": [1, 2, 3, 4],
                        },
                        {
                            "startLatitude": data["secondLatitude"],
                            "endLatitue": 90,
                            "BeamList": [5, 6, 7, 8],
                        },
                        {
                            "startLatitude": data["thirdLatitude"],
                            "endLatitue": 90,
                            "BeamList": [10, 11, 12, 13],
                        },
                    ],
                }
                for data in middle_interface["nbLatitudeCloseStrategy"]
            ],
        }
    }


middle_interface = {
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
            "firstLatitude": 70,
            "secondLatitude": 75,
            "thirdLatitude": 80,
            "orbitIdList": [2, 4, 6],
        },
    ],
}

end_interface = {
    "nbLatitudeCloseStrategy": {
        "needLatitudeClose": True,
        "nbLatitudeCloseList": [
            {
                "orbitIdList": [1, 3, 5],
                "nbLatitudeCloseFrameList": [
                    {
                        "startLatitude": 70,
                        "endLatitue": 90,
                        "BeamList": [1, 2, 3, 4],
                    },
                    {
                        "startLatitude": 75,
                        "endLatitue": 90,
                        "BeamList": [5, 6, 7, 8],
                    },
                    {
                        "startLatitude": 80,
                        "endLatitue": 90,
                        "BeamList": [10, 11, 12, 13],
                    },
                ],
            },
            {
                "orbitIdList": [2, 4, 6],
                "nbLatitudeCloseFrameList": [
                    {
                        "startLatitude": 70,
                        "endLatitue": 90,
                        "BeamList": [1, 2, 3, 4],
                    },
                    {
                        "startLatitude": 75,
                        "endLatitue": 90,
                        "BeamList": [5, 6, 7, 8],
                    },
                    {
                        "startLatitude": 80,
                        "endLatitue": 90,
                        "BeamList": [10, 11, 12, 13],
                    },
                ],
            },
        ],
    }
}

my_end = mid2end(middle_interface)
print(my_end)
print("------------")
print(end_interface)
if my_end == end_interface:
    print("pass")
else:
    print("fail")
