import json


def get_ue_info():
    with open("new_ue_info.json", "r") as f:
        return json.load(f)
