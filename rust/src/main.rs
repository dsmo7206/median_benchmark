extern crate rand;

use rand::distributions::{Distribution, Uniform};
use std::cmp::Ordering;
use std::env;
use std::process;
use std::time::SystemTime;

fn get_size(s: &str) -> usize {
    let result = s.parse::<usize>().unwrap();
    if result <= 0 {
        println!("Invalid argument (need integer > 0)");
        process::exit(1);
    }
    result
}

fn quick_select(values: &[usize], k: usize) -> usize {
    if values.len() == 1 {
        return values[0];
    }

    let pivot = values[0];

    let mut lows : Vec<usize> = Vec::with_capacity(values.len() / 2);
    let mut highs : Vec<usize> = Vec::with_capacity(values.len() / 2);
    let mut pivots : Vec<usize> = Vec::new();

    for &value in values.iter() {
        match value.cmp(&pivot) {
            Ordering::Less => lows.push(value),
            Ordering::Greater => highs.push(value),
            _ => pivots.push(value)
        }
    }

    if k < lows.len() {
        return quick_select(lows.as_slice(), k);
    }
    else if k < lows.len() + pivots.len() {
        return pivots[0]
    }

    quick_select(highs.as_slice(), k - lows.len() - pivots.len())
}

fn quick_select_median(values: &[usize]) -> usize {
    quick_select(values, values.len() / 2)
}

fn get_millis_between(start: SystemTime, end: SystemTime) -> u64 {
    let duration = end.duration_since(start).expect("SystemTime::duration_since failed");
    let nanos = duration.subsec_nanos() as u64;
    (1000*1000*1000 * duration.as_secs() + nanos) / (1000 * 1000)
}

fn main() {
    let args : Vec<String> = env::args().collect();

    if args.len() != 2 {
        println!("Need argument (integer > 0)");
        process::exit(1);
    }

    let size = get_size(&args[1]);

    let gen_start = SystemTime::now();

    let range = Uniform::new(0, 12345678);
    let mut rng = rand::thread_rng();

    let mut values : Vec<usize> = Vec::new();

    for _ in 0..size {
        values.push(range.sample(&mut rng));
    }

    let gen_end = SystemTime::now();

    let find_start = SystemTime::now();
    let result = quick_select_median(values.as_slice());
    let find_end = SystemTime::now();

    println!("Result is: {}", result);
    println!("Gen took : {}ms", get_millis_between(gen_start, gen_end));
    println!("Find took: {}ms", get_millis_between(find_start, find_end));
}
