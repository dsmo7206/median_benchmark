package main

import (
	"fmt"
	"math/rand"
	"os"
	"strconv"
	"time"
)

func quick_select(values []int, k int) int {
	if len(values) == 1 {
		return values[0]
	}

	pivot := values[0]

	lows := make([]int, 0, len(values) / 2)
	highs := make([]int, 0, len(values) / 2)
	pivots := make([]int, 0, 0)

	for _, value := range values {
		if value < pivot {
			lows = append(lows, value)
		} else if value > pivot {
			highs = append(highs, value)
		} else {
			pivots = append(pivots, value)
		}
	}

	if k < len(lows) {
		return quick_select(lows, k)
	} else if k < len(lows) + len(pivots) {
		return pivots[0]
	} else {
		return quick_select(highs, k - len(lows) - len(pivots))
	}
}

func quick_select_median(values []int) int {
	return quick_select(values, len(values) / 2)
}

func get_millis_between(start, end time.Time) int {
	return int(end.Sub(start) / time.Millisecond)
}

func main() {
	if len(os.Args) != 2 {
		fmt.Println("Need argument (integer > 0)")
		os.Exit(1)
	}

	size, err := strconv.Atoi(os.Args[1])
	if err != nil || size <= 0 {
		fmt.Println("Invalid argument (need integer > 0)")
		os.Exit(1)
	}

	gen_start := time.Now()
	values := make([]int, 0, size)
	for i := 0; i < size; i++ {
		values = append(values, rand.Intn(12345678))
	}
	gen_end := time.Now()

	find_start := time.Now()
	result := quick_select_median(values)
	find_end := time.Now()

	fmt.Printf("Result is: %d\n", result)
	fmt.Printf("Gen took : %dms\n", get_millis_between(gen_start, gen_end))
	fmt.Printf("Find took: %dms\n", get_millis_between(find_start, find_end))
}
