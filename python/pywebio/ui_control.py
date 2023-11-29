import time
import json
import subprocess

# import time
# import sys
# import pywebio
# from pywebio.input import *
from pywebio.output import (
    put_html,
    use_scope,
    put_row,
    put_buttons,
    put_tabs,
    put_text,
    put_table,
)
from pywebio import config, start_server

from pywebio.input import radio

# from pywebio.input import radio
from pywebio.pin import pin, put_input
from pywebio.platform.adaptor.http import random_str
from pywebio.session import hold


def validate_name(name):
    # removing all spaces from the input name
    name = name.replace(" ", "")
    # performing validation checks
    # check 1 : Name must not be empty
    # check 2 : It should contain only alphabets [a-z] or [A-Z]
    if name == "" or not (name.isalpha()):
        return "Please enter a non empty name consisting of alphabets only"


def put_pin_value(t1, t2):
    with use_scope("text_output", clear=True):
        put_text("new UE config：")
        put_table(
            [
                ["from", "to"],
                [t1, t2],
            ]
        )


def start_constellation(index):
    if index < 4:
        # e, msg = subprocess.getstatusoutput(f'./non-high.sh {index + 1}')
        subprocess.Popen(["./non_high.sh", f"{index + 1}"])
        # if e != 0:
        #     print(f'错误码：{e}')
        #     put_text(f'出错了, {e}, 请检查日志, 可能是已经有一个启动的进程，导致端口被占用')
    elif index == 4:
        # e, msg = subprocess.getstatusoutput(f'./high.sh')
        subprocess.Popen(["./high.sh"])
        # if e != 0:
        #     print(f'错误码：{e} msg = {msg}')
        #     put_text(f'出错了, {e}, msg = {msg}, 请检查日志, 可能是已经有一个启动的进程，导致端口被占用')


def write_json_to_file(path, config):
    with open(path, "w") as f:
        json.dump(config, f, indent=2)


def get_json_from_file(path):
    with open(path) as f:
        return json.load(f)


def toggle_route():
    config_path = "./non_control/Service-Display/Cesium-display-New/public/config.json"
    with open(config_path) as f:
        config = json.load(f)

    config["show_route_event"] = not config["show_route_event"]

    write_json_to_file(config_path, config)


def toggle_image():
    config_path = "./non_control/Service-Display/Cesium-display-New/public/config.json"
    with open(config_path) as f:
        config = json.load(f)

    config["show_load_image"] = not config["show_load_image"]

    write_json_to_file(config_path, config)


def start_web_page():
    # subprocess.Popen(['node', './non_control/Service-Display/app.js'])
    subprocess.Popen(["./start_node.sh"])


def set_ue_config(from_id, to_id, ue_type, type_id):
    from_id = int(from_id)
    to_id = int(to_id)
    with use_scope("text_output", clear=False):
        put_text("new UE config：")
        put_table(
            [
                ["from", "to", "type", "type_id"],
                [from_id, to_id, ue_type, type_id],
            ]
        )
    ue_info = get_json_from_file("./ue_info.json")
    for info in ue_info["ueInfo"]:
        if to_id >= info["id"] >= from_id:
            info["type"] = type_id

    write_json_to_file("./new_ue_info.json", ue_info)
    print(from_id, to_id)


def put_row_from_to(names, placeholders, ue_type, type_id):
    put_row(
        [
            *[
                item
                for name, placeholder in zip(names, placeholders)
                for item in [put_input(name, placeholder=placeholder), None]
            ],
            put_buttons(
                [ue_type],
                lambda _: set_ue_config(
                    *(getattr(pin, name) for name in names), ue_type, type_id
                ),
            ),
        ],
        size="10% 10px 10% 10px",
    )


def set_incentive_source_config(**configs):
    # 同一个id的会直接覆盖之间的配置
    for key, value in configs.items():
        try:
            value = int(value)
        except Exception:
            raise ValueError("输入整数")

    configs = {key: int(value) for key, value in configs.items()}
    print(configs)
    incentive_source = get_json_from_file("./incentive_source.json")
    # print(incentive_source)

    for info in incentive_source["incentiveSource"]["userScene"]["info"]:
        print(info, "info")
        print(info["business"], "business", configs["id"], "id")
        if info["business"] == configs["id"]:
            print("find")
            info["srcUe"] = configs["srcUe"]
            info["dstUe"] = configs["dstUe"]
            info["type"] = configs["type"]

            info["startTime"] = configs["startTime"]
            info["endTime"] = configs["endTime"]
            business_type = configs["type"]
            simulationMessage_value = configs["simulationMessage"]
            if business_type == 1 or business_type == 2:
                info["simulationMessage"]["speedKbps"] = simulationMessage_value
            elif business_type == 22:
                info["simulationMessage"]["peerBusinessId"] = simulationMessage_value
            elif business_type == 23:
                info["simulationMessage"]["pps"] = simulationMessage_value
            else:
                raise ValueError("未知的业务类型")
            break

    write_json_to_file("./new_incentive_source.json", incentive_source)


def incentive_source_config(names, placeholders):
    put_row(
        [
            *[
                item
                for name, placeholder in zip(names, placeholders)
                for item in [put_input(name, placeholder=placeholder), None]
            ],
            put_buttons(
                ["+"],
                lambda _: set_incentive_source_config(
                    **{name: getattr(pin, name) for name in names}
                ),
            ),
        ],
        # size="10% 10px 10% 10px",
        size=" ".join([f"{len(name) * 1.2 + 3}% 10px " for name in names]),
    )

    # "business": 1,
    # "srcUe": 54,
    # "dstUe": 168,
    # "type": 1,
    # "indication": 1,
    # "prior": 2,
    # "guaranteedBandwidth": 100,
    # "startTime": simulationTime + 50 * 1000,
    # "endTime": simulationTime + 150 * 1000,
    # "simulationMessage": {"speedKbps": 9000},
    #


def main():
    put_html("<h1>UE and Incentive Source Config</h1>")
    put_html("<h2>UE config</h2>")
    id_header = random_str()
    put_row_from_to([f"{id_header}{i}" for i in range(2)], ["from", "to"], "宽演终端", 0)
    id_header = random_str()
    put_row_from_to([f"{id_header}{i}" for i in range(2)], ["from", "to"], "窄带话音终端", 2)
    id_header = random_str()
    put_row_from_to([f"{id_header}{i}" for i in range(2)], ["from", "to"], "窄带物联网终端", 3)
    id_header = random_str()
    put_row_from_to([f"{id_header}{i}" for i in range(2)], ["from", "to"], "地面", 4)

    put_html("<h2>Incentive Source Config</h2>")

    put_html("<h3>simulation message处： </h3>")
    put_html("<li>如果type==1 or 2, 输入speedKbps对应的数值</li>")
    put_html("<li>如果type==22, 输入peerBusinessId对应的数值</li>")
    put_html("<li>如果type==23, 输入pps对应的数值</li>")
    put_html("<hr>")

    needed_config = [
        "id",
        "srcUe",
        "dstUe",
        "type",
        # "indication",
        # "prior",
        # "guaranteedBandwidth",
        "startTime",
        "endTime",
        "simulationMessage",
    ]

    incentive_source_config(needed_config, needed_config)

    use_scope("text_output")
    hold()


if __name__ == "__main__":
    WEB_PORT = 23088
    config(title="配置界面")
    start_server(main, port=WEB_PORT, debug=True, cdn=False)
