import re


def convert_file(file_name):
    content = []
    with open(file_name) as f:
        content = f.readlines()

    with open("get_converted_json.py", "w") as f:
        f.write("def get_converted_json(SimulationTime):\n")
        f.write("  return")
        for con in content:
            if "Time" in con:
                numbers = re.findall(r"\d+", con)

                f.write(
                    "  "
                    + con.replace(numbers[0], f"{numbers[0]} * 1000 + SimulationTime")
                )
            else:
                f.write("  " + con)


if __name__ == "__main__":
    convert_file("./new_incentive_source.json")
