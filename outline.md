# Outline

## Overview

- Who am I?
- Writing concurrent applications is hard
    - Race conditions
    - General scaling
- Rust
    - Show that sentence
    - Confusion gif
    - Safety
        - Memory Safety
        - Thread Safety
    - It's all about empowering developers
- What is async development?
    - What are futures/ promises?
    - What is an event loop?
    - Show nginx vs apache memory usage
- "I'm here to show code and talk history, and I'm all out of code"
    - libgreen vs native-thread = common abstraction in libstd
        - this was not good -> libgreen gets removed
    - Rust _wants_ to do async IO though
    - `mio.rs` -> basic async primitives
    - quick interlude: "zero cost abstractions" - what is that?
    - `futures.rs` -> zero cost abstractions
    - `tokio` -> event loop on top of futures and mio
- So how do we go from here?
    - This is state machines all the way down
    - `async` & `await`
        - Write synchronous looking code, that gets turned into futures
    - This is complicated, and clever people are working on it
        - in groups
            - you might call them working groups
    - Network-WG for Rust 2018. Split into three:
        - Cross-framework collaboration on tools
    - `async`/`await` is unstable in `nightly` (needs a feature flag)


1. intro: writing concurrent applications is hard, rust is about empowering, so let's try to make a lang/libraries that helps you make apps that work and scale 2. the "i'm here to show code and talk history and i'm all out of code" part 2.1. libgreen = literally node.rs 2.2. runtime? lolnope! let's try to make this zero-cost over system apis: mio 2.3. now that we have low-level things, and inspired by other langs/platforms like JS and scala, people started working on abstracting over this (mention but don't explain futures and tokio) 3. how make this managable: it's state machines all the way down (<- event loops and stuff intro) 4. this is complicated. clever people are working on this. in groups. working groups, you might call them. 4.1. net-wg and pushing new tokio and futures versions etc 4.2. also language team to make async/await happen

- What is Rust?
    - Actually ask who doesn't know it at all
    - Highlight the buzzword sentence from the website
    - Talk about how that might be accurate, but that focussing on the methodology might be more important
    - Safety!
        - What does this mean?
        - Static analysis
        - Memory safety
        - Concurrency aware types
- What is async programming?
    - General concepts first: Future, Executor, event loops
    - Show example of async programming in some other language
- The beginnings
    - libgreen
    
- Enter: tokio `0.1`
    - Show small example
    - Show benefits and capabilities
    - Also show drawbacks
    - Not easy to wrap head around
- Network WG
    - Sidetrack: `async`/ `await`
    - Reasoning behind new core syntax elements
    - Talk about a common `Future` trait in core and std
    - Then intro `futures-rs`
        - How does this new syntax make things easier?
        - Show some cool things that are possible
        - What about static analysis?!
- Timeline
    - Early tokio
    - Current implementations
    - async await syntax slated for early 2019
    