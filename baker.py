import argparse, os, sys

from typing import TextIO

def is_valid_src(src: str):
    return os.path.isfile(src) and src.endswith(".h")

def collect_includes(src: TextIO, tmpf: TextIO):
    for line in src:
        if not line.startswith("#include"):
            tmpf.write(line)
            continue

        yield line

def main(args: argparse.Namespace):
    tmpfnames = []
    includes = set()

    os.makedirs(os.path.dirname(args.out), exist_ok=True)

    for src in args.sources:
        print(f"Processing {src}...")
        
        if not is_valid_src(src):
            print(f"Invalid source given: {src}", file=sys.stderr)            
            exit(1)

        tmpf = src + ".tmp"
        tmpfnames.append(tmpf)

        with open(src, "r") as f, open(tmpf, "w") as tf:
            for include in collect_includes(f, tf):
                includes.add(include)

    with open(args.out, "w") as out:
        for include in includes:
            out.write(include)

        out.write('\n')

        for tmpf in tmpfnames:
            src = tmpf.rstrip(".tmp")

            with open(tmpf, "r") as tf:
                out.write('\n')
                out.write(f"/* {'-' * 25} {src} {'-' * 25} */\n")
                out.write(tf.read())

            os.remove(tmpf)

if __name__ == "__main__":
    p = argparse.ArgumentParser()

    p.add_argument("sources",       nargs='+',                       help="Source header files to concatenate")
    p.add_argument("-o", "--out",  metavar="FILE", default="out.h",  help="Destination file")

    args = p.parse_args()

    main(args)