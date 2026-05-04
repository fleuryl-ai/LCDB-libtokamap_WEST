from pathlib import Path
# from typing import Any, override
try:
    from typing import override
except ImportError:
    # Fallback for Python < 3.12
    def override(func):
        return func
import numpy as np
import json
import libtokamap
import argparse
# import matplotlib.pyplot as plt



def map(mapper: libtokamap.Mapper, experiment: str, mapping_path: str, shot: int):
    res = mapper.map(experiment, mapping_path, {'shot': shot})
    if res.dtype == 'S1':
        res = res.tobytes().decode()
    print(f"{mapping_path}: {res}")
    # plt.plot(res)
    # plt.show()
    return res


def map_all(mapper: libtokamap.Mapper, experiment: str, shot: int):
    map(mapper, experiment, "magnetics/ip[0]/data", shot)
    map(mapper, experiment, "magnetics/flux_loop[0]/flux/data", shot)
    map(mapper, experiment, "magnetics/flux_loop[1]/flux/data", shot)
    map(mapper, experiment, "magnetics/flux_loop[2]/flux/data", shot)


def main(args):
    parser = argparse.ArgumentParser()
    parser.add_argument('--shot', type=int, default=54178)
    args = parser.parse_args(args[1:])

    print("Calling LibTokaMap version:", libtokamap.__version__)
    print(f"With context = {vars(args)}")

    # config_path = Path(__file__).parent / "config.toml"
    config_path = "/ZONE_TRAVAIL/LF218007/libtokamap_west/libtokamap-west-datasource/config/config.toml";
    mapper = libtokamap.Mapper(str(config_path))

    experiment = "WEST"
    try:
        map_all(mapper, experiment, args.shot)
    except Exception as e:
        print(f"{e}")


if __name__ == "__main__":
    import sys
    main(sys.argv)
