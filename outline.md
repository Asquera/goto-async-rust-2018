# Outline

## Overview

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
    