def get_members(obj, ignored_members):
    return [
        member
        for member in dir(obj)
        if not member.startswith("__")
        and not member.endswith("__")
        and "_" not in member
        and member
        not in (
            ["Config", "construct", "copy", "dict", "json", "schema", "validate"]
            + ignored_members
        )
    ]


def camel_to_snake(camel_case):
    fk = {
        # "info": "breakdown_type_info",  # WARN: delete this later
    }

    if camel_case in fk:
        return fk[camel_case]

    result = [camel_case[0].lower()]

    for char in camel_case[1:]:
        if char.isupper():
            result.extend(["_", char.lower()])
        else:
            result.append(char)

    return "".join(result)
