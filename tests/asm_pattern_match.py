#!/usr/bin/env python
import sys
import re


lines = []

asm_fname = sys.argv[1]
pat_fname = sys.argv[2]

with open(asm_fname) as f:
    in_func = False
    for l in f:
        l = l.strip()
        if not l:
            continue
        if l == ".cfi_endproc":
            in_func = False
        if in_func:
            if re.match(r".L\d+:", l):
                pass
            elif l[0] in ["@", "."]:
                continue
#            print l
            lines.append(l)
        elif "%function" in l:
            in_func = True

pattern = [l.rstrip() for l in open(pat_fname).readlines()]
captures = {}
for l in lines[1:]:
    l = re.sub(r"[\t ]", " ", l)
    p = ""
    if pattern:
        p = pattern.pop(0)
#    print l, "|", p
    m = re.match(p, l)
    c = m.groupdict()
    for k, v in c.iteritems():
        if k in captures and captures[k] != v:
            print "FAIL:", asm_fname
            sys.exit(1)
    captures.update(c)

# Differently named capture regs should represent different underlying regs
if len(set(captures.values())) != len(captures):
    print "FAIL:", asm_fname
    sys.exit(1)

print "OK:", asm_fname
