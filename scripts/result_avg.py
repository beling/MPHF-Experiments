#!/bin/env python3
from collections import defaultdict, namedtuple
from pathlib import Path
from decimal import Decimal
import sys

to_sum = ('queryTimeMilliseconds', 'numQueries', 'numQueriesTotal')
to_avg = ('bitsPerElement',)
to_avg_round = ('constructionTimeMilliseconds',)

class Value:
    def __init__(self):
        self.sum = defaultdict(Decimal)
        self.count = 0

results = defaultdict(Value)
  
def add_results_from(file):
    for l in file:
        if not l.startswith('RESULT'): continue
        key = ''
        values = {}
        for kv in l.strip().split()[1:]:
            k, v = kv.split('=')
            if k in to_sum or k in to_avg or k in to_avg_round:
                values[k] = Decimal(v)
            else:
                if k: key += ' '
                key += kv
        res_val = results[key]
        res_val.count += 1
        for k, v in values.items():
            res_val.sum[k] += v
        
for dir in sys.argv[1:] if len(sys.argv) > 1 else ('.',):
    p = Path(dir)
    if p.is_file():
        with open(p) as f: add_results_from(f)
    elif p.is_dir():
        for filename in p.rglob('*.txt'):
            with open(filename) as f: add_results_from(f)
    else:
        print(f"Cannot find file or directory '{dir}'.", file=sys.stdout)

for key, value in results.items():
    print('RESULT', key, end='')
    for k, v in value.sum.items():
        print(f' {k}=', end='')
        if k in to_sum: print(v, end='')
        elif k in to_avg: print(v / value.count, end='')
        else: print(round(v / value.count), end='')
    print()