---
title: async in Rust 2018
subtitle: The future of futures
transition: fade
---

## `whoami(1)`

Katharina Fey ( `@spacekookie` )

* Active FOSS developer
* Avid tea drinker
* Hobbyist hardware maker 

---

I also make some attrocious puns

---

<img src="images/twitter_a.png" height=275px/>

<img src="images/twitter_b.png" height=250px/>

---

## `whoami(2)`

I do Rust things!

* Contributer of the CLI working group
* Member of the community team & `berlin.rs`
* Maintainer of several `use[ful|less]` libraries

---

## Concurrency is hard

---

<img src="images/concurrency.gif" width=650px>

---

Race conditions

**vs**

Inefficient scaling

---

### What thread owns data?

---

## Rust

---

> Rust is a systems programming language that runs blazingly fast, prevents segfaults, and guarantees thread safety. 

---

<img src="images/confused_travolta.gif" height=350px />

---

## Safety

---

Memory safety

<div class="fragment" data-fragment-index="3">
**and**

Thread safety
</div>

---

## Ownership

---

* Data is always owned
* Data can always be borrowed
* Strict rules around borrowing and owning

---

```rust
let mut f = File::open("foo.txt")?;

for _ in 0..3 {
    thread::spawn(move || {
        // ... read data from file or something ...

        drop(f); // close the file
    });
}

```

---

This would not compile!

---

```
error[E0382]: capture of moved value: `f` --> main.rs:13:14
   |
10 | thread::spawn(move || {
   |               ------- value moved (into closure) here
...
13 |     drop(f);
   |          ^ value captured here after move
   |
```

---

```rust
fn main() {
    let f = File::open("foo.txt")?;

    read_from_file(f);
    read_from_file(f);
}

fn read_from_file(f: File) { ... }
```

---

This will also not compile!

---

<img src="images/purity.png" width=800px>

---

**Rust breaks down these spectrums**

---

> No matter what kind of code you are writing now, Rust empowers you to reach farther, to program with confidence in a wider variety of domains than you did before.

<small>--- Rust book, foreword</small>

---

## Async

<div class="fragment" data-fragment-index="2">
What is that?
</div>

<div class="fragment" data-fragment-index="3">
What does it know?
</div>

<div class="fragment" data-fragment-index="4">
Does it know anything?
</div>

<div class="fragment" data-fragment-index="5">
Let's find out!
</div>

---

"Do this thing but don't make me wait"

---

Not just a new Thread

---

## Futures

---

![](images/back_to_the_future.gif)

---

No, not that type of Futures

---

**`Future` = calculation that hasn't happened yet**

> * Is *probably* gonna happen at some point
> * Just keep asking

---

**Event Loop = runtime for `Future`s**

* Keeps polling `Future` until it is ready
* Runs your code whenever it can be run

---

## Why?

---

![](images/apache-vs-nginx.png)

---

---

I'm here to show code and talk history

<div class="fragment" data-fragment-index="2">
and I'm ~~all~~ mostly out of code
</div>

---

![](images/back_to_the_future.gif)

---

## Late 2013

---

### `libgreen`

---

![](images/libgreen_add.png)

* Rust had green threading support
* Enabled non-blocking IO

---

Included a runtime in `stdlib`

* This came with a lot of problems

---

Rust wanted to go in a different direction

---

## Late 2014

---

**`libgreen` is dead, long live `libgreen`**

![](images/libgreen_remove.png)

---

Sorry, did I say ~~libgreen~~, I meant `mio.rs`

---

## `mio.rs`

<small>"Metal IO" 🤘</small>

---

* Light, non-blocking IO library
* Abstracts async over different platforms
* Eventually developed an ecosystem around it

---

<img src="images/hit-you-with-some-knowledge.gif" width=450px />

---

### Zero Cost Abstractions

---

**= no discernible* runtime overhead**

<br />

---

**= code that you can't write better by hand**

<div class="fragment" data-fragment-index="2">
Abstraction layers disappear at compile-time
</div>

---

## Mid 2016

---

<img src="images/futures-rs-logo.svg" />

---

* *zero cost abstraction* for futures
* Building async state-machines

---

### `tokio-core`

---

* Wraps around `mio.rs` and `futures.rs`
* Event reactor

---

## Fast foward to 2018

---

It's state machines all the way down

```rust
// ... define `stdin` and `stdout`
let reader = BufReader::new(stdin);
let buffer = Vec::new();

let fut = io::read_until(reader, b'\n', buffer)
      .and_then(move |(stdin, buffer)| {
          stdout.write_all(&buffer).map_err(|e| panic!(e))
      }).map_err(|e| panic!(e));

// Actually run _here_
tokio::run(fut);
```

---

**Reminder:** Futures are zero-cost-abstractions.

They disappear from the code at compile-time!

---

## `async` & `await`

---

Write code that looks synchronous but really isn't

```rust
async fn do_this_thing() { ... }

// ...

await!( do_this_thing() );
```

---

## How?!

---

### It's complicated!

<div class="fragment" data-fragment-index="3">
Clever people are working on it
</div>

<div class="fragment" data-fragment-index="4">
In Groups
</div>

<div class="fragment" data-fragment-index="5">
You might even call them "working groups"
</div>


---

## networking-WG

* Implements async/await features in compiler
* Provides library ecosystem

---

## Can I use this?

---

*kinda* 😅

---

### Roadmap

* `async`/`await` syntax in nightly compiler
* library ecosystem is still being polished

Expect more concrete progress early-2019

---

## You made it!

Follow me on twitter **`@spacekookie`**

Or: **`kookie@spacekookie.de`**

<br/>

#### Thanks to my employers

* I do *Rust* work at **Ferrous Systems**
* I do *Distributed Systems* at **Asquera**