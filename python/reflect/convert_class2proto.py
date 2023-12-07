# TODO: handle list
import simulation_proto.simulation_pb2 as simulation_pb2
import traceback
from loguru import logger
from typing import List
from .utils import get_members, camel_to_snake
from src.request_format import (
    narrowBandAccessPolicyConfig,
    wideBandEvolutionAccessPolicyConfig,
    policyOptionsConfig,
    breakdownType,
    breakdownTypeInfo,
)


def get_narrow_band_access_policy(narrow_band_access_policy_config):
    narrow_band_access_policy = simulation_pb2.NarrowBandAccessPolicy()
    narrow_band_access_policy.ue_star_access_policy = (
        narrow_band_access_policy_config.ueStarAccessPolicy
    )
    narrow_band_access_policy.ue_star_switching_policy = (
        narrow_band_access_policy_config.ueStarSwitchingPolicy
    )
    narrow_band_access_policy.wireless_resource_allocation_policy = (
        narrow_band_access_policy_config.wirelessResourceAllocationPolicy
    )
    return narrow_band_access_policy


def basic_convert(config, member_top):
    # narrow_band_access_policy = simulation_pb2.NarrowBandAccessPolicy()
    member_top = member_top[0].upper() + member_top[1:]
    # print(member_top)
    result = getattr(simulation_pb2, member_top)()
    for member in get_members(config):
        setattr(
            result,
            camel_to_snake(member),
            getattr(config, member),
        )
    return result


def basic_test():
    narrow_band_access_policy_config = narrowBandAccessPolicyConfig(
        ueStarAccessPolicy=1,
        ueStarSwitchingPolicy=1,
        wirelessResourceAllocationPolicy=1,
    )

    narrow_band_access_policy = simulation_pb2.NarrowBandAccessPolicy()
    for member in get_members(narrow_band_access_policy_config):
        print("mem: ", member)
        v = getattr(narrow_band_access_policy_config, member)
        print("value in http", v)
        setattr(
            narrow_band_access_policy,
            camel_to_snake(member),
            getattr(narrow_band_access_policy_config, member),
        )
        value = getattr(narrow_band_access_policy, camel_to_snake(member))
        print(f"{member}: {value}")

    print("-------------")

    v = getattr(narrow_band_access_policy, "CopyFrom")
    print(v)


def complex_convert(config, member_top, ignored_members=None):
    if ignored_members is None:
        ignored_members = []
    member_top = member_top[0].upper() + member_top[1:]
    print("member_top", member_top)
    result = getattr(simulation_pb2, member_top)()

    for member in get_members(config, ignored_members):
        # print("mem: ", member)
        v = getattr(config, member)
        # print("value in http", v, "type is : ", type(v))
        print(type(v))
        try:
            match v:
                case int() | str() | float() | bool():
                    # print("set basic type  : ", member)
                    setattr(
                        result,
                        camel_to_snake(member),
                        getattr(config, member),
                    )
                case None:
                    pass
                    # print('dont have', member)
                # case list():
                #     print("set list type: ", member)
                #     print("config", config)
                #     # 遍历v
                #
                #     m = getattr(result, camel_to_snake(member))
                #     for inner_config in v:
                #         im = getattr(result, camel_to_snake(member))
                #         getattr(im, "CopyFrom")(
                #             complex_convert(getattr(inner_config, member), member)
                #         )
                #
                #         getattr(m, "append")(im)
                #
                #     # m = getattr(result, camel_to_snake(member))
                #     # for member, inner_config in zip(
                #     #     get_members(config, ignored_members), getattr(config, member)
                #     # ):
                #     #     print("vc", member, inner_config)
                #     #     print("tt", type(member), type(inner_config))
                #     #     getattr(m, "append")(
                #     #         complex_convert(getattr(inner_config, member), member)
                #     #     )
                case _:
                    # print("set complex type: ", member)
                    m = getattr(result, camel_to_snake(member))
                    getattr(m, "CopyFrom")(
                        complex_convert(getattr(config, member), member)
                    )
        except Exception as e:
            traceback.print_exc()

        # value = getattr(policy_options, camel_to_snake(member))
        # print(f"{member}: {value}")

    return result
    # print("-------------")
    #
    # v = getattr(policy_options, "CopyFrom")
    # print(v)


def test_complex():
    policy_options_config = policyOptionsConfig(
        wideBandEvolutionAccessPolicy=wideBandEvolutionAccessPolicyConfig(
            ueStarAccessPolicy=1,
            randomBeamScanPolicy=1,
            ueStarSwitchingPolicy=1,
            wirelessResourceAllocationPolicy=1,
        ),
        narrowBandAccessPolicy=narrowBandAccessPolicyConfig(
            ueStarAccessPolicy=1,
            ueStarSwitchingPolicy=1,
            wirelessResourceAllocationPolicy=1,
        ),
        sgnbAccessAdmissionControlPolicy=1,
        interferenceAvoidancePolicy=1,
        uplinkStarPolicy=1,
        downlinkStationPolicy=1,
        centralizedConnectionlessRoutingPolicy=1,
        distributedConnectionlessRoutingPolicy=1,
        centralizedConnectionOrientedRoutingPolicy=1,
        energyPolicyEnable=1,
    )

    complex_convert(policy_options_config, "policyOptions")


def test():
    breakdown_type = breakdownType(
        info=[
            breakdownTypeInfo(
                nodeType=1,
                nodeId=2,
                malfunctionType=1,
                malfunctionPart=1,
                malfunctionStartTime=1,
                malfunctionEndTime=1,
            )
        ]
    )

    complex_convert(breakdown_type, "BreakDownType")
