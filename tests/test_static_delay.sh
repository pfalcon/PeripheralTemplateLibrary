#!/bin/sh
set -e

function test_case () {
    make -B TARGET=stm32 bin-stm32/$1.s
    python asm_pattern_match.py bin-stm32/$1.s $1.pattern
    echo "==="
}

test_case test_delay_single
test_case test_2_same_delays
test_case test_delay_in_loop
