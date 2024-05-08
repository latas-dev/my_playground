// thread:  sleep.
// time:    duration.
use std::{thread, time};

struct Philosopher {
    name: String,
    
}

impl Philosopher {
    fn new(name: &str) -> Philosopher {
        Philosopher {
            name: name.to_string(),
        }
    }

    fn eat(&self) {
        println!("{} is eating.", self.name);

        thread::sleep(time::Duration::from_millis(1000));

        println!("{} is done eating.", self.name);
    }

    #[allow(dead_code)]
    fn think(&self) {
        println!("{} is thinking.", self.name);

        thread::sleep(time::Duration::from_millis(1000));

        println!("{} is done thinking.", self.name);
    }
}

fn main() {
    let philosophers = vec![
        Philosopher::new("Judith Butler"),
        Philosopher::new("Gilles Deleuze"),
        Philosopher::new("Karl Marx"),
        Philosopher::new("Emma Goldman"),
        Philosopher::new("Michel Foucault"),
    ];

    for p in &philosophers {
        p.eat();
    }
}