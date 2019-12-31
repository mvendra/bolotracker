#!/usr/bin/env python3

import sys
import os

def puaq():
    print("Usage: %s filename.sql" % os.path.basename(__file__))
    sys.exit(1)

def gen(fn, fo = None):

    if fo is None:
        fo = "./snippet.txt"

    if os.path.exists(fo):
        print("%s already exists. Will not overwrite." % fo)
        return

    contents = ""
    with open(fn) as f:
        contents = f.read()

    lines_generated = []
    contents_singlestr = contents.replace("\n", "")

    gen_line = ""
    for c in contents_singlestr:
        gen_line += c
        if c == ";":
            lines_generated.append(gen_line)
            gen_line = ""

    lines_gen_deco = []
    for i in lines_generated:
        lgd = "cmds.push_back(\"%s\");" % i
        lines_gen_deco.append(lgd)

    lines_full = []
    lines_full.append("void Database::bootstrap(){\n\n")
    lines_full.append("    std::vector<std::string> cmds;\n\n")
    for l in lines_gen_deco:
        lines_full.append("    %s\n" % l)

    lines_full.append("\n    for (auto i: cmds){\n")
    lines_full.append("        exec(i);\n")
    lines_full.append("    }\n\n}")

    with open(fo, "w+") as f:
        for w in lines_full:
            f.write(w)

if __name__ == "__main__":

    if len(sys.argv) < 2:
        puaq()

    fn = sys.argv[1]
    fo = None

    if len(sys.argv) > 2:
        fo = sys.argv[2]

    gen(fn, fo)

