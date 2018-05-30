#!/usr/bin/env python3

import sys
import time
import random


def quickselect_median(values):
    return quickselect(values, len(values) // 2)


def quickselect(values, k):
    if len(values) == 1:
        return values[0]

    pivot = values[0]

    lows, highs, pivots = [], [], []
    for el in values:
        if el < pivot: lows.append(el)
        elif el > pivot: highs.append(el)
        else: pivots.append(el)

    if k < len(lows):
        return quickselect(lows, k)
    elif k < len(lows) + len(pivots):
        return pivots[0]
    else:
        return quickselect(highs, k - len(lows) - len(pivots))


class Timer:
    def __enter__(self):
        self.start = time.time()
        return self
    def __exit__(self, *exc_info):
        self.end = time.time()
    def get_millis(self):
        return int((self.end - self.start) * 1000)


def main():
    if len(sys.argv) != 2:
        print('Need argument (integer > 0)')
        sys.exit(1)

    try:
        size = int(sys.argv[1])
        if size <= 0:
            raise ValueError()
    except:
        print('Invalid argument (need integer > 0)')
        sys.exit(1)

    with Timer() as gen_timer:
        values = [random.randrange(0, 12345678) for _ in range(size)]

    with Timer() as find_timer:
        result = quickselect_median(values)

    print('Result is: %s' % result)
    print('Gen took : %sms' % gen_timer.get_millis())
    print('Find took: %sms' % find_timer.get_millis())


if __name__ == '__main__':
    main()
