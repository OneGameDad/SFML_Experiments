# SFML_Experiments
My learning experiments with SFML, C++ and CMake

## Description
These are a series of tools I'm creating in an effort to learn SFML, improve at C++, create a small game engine, program for video games, and prepare for the Supercell Internship Challenge Day at Hive Helsinki.

## Current Working Features
### GameTime
GameTime is a singleton class, which can return Delta Time & Current Time, as well as Unscaled versions of Delta Time and Current Time.

### GameState
GameState is singleton class, used to track any shared data that other classes needed.

### PropertyAnimator
PropertyAnimator uses PerlinNoiseGenerator to provide animation timing.

### PerlinNoiseGenerator
PerlinNoiseGenerator is a singleton class, used to generate Perlin noise from a bitmap image.

### Googly Eye
A simple test animation to replicate a googly eye, by replacing the texture of a sprite.

### Particle System
A particle system using sf::VertexArray and sf::Quad to draw particles. Abstracted it to create a fire effect. It needs some refinement and the current textures are too large. But it can have multiple emitters which can follow a target. The fire effect proves it can be do multiple types of effects. This was created using Chat-GPT to help me with the calculations.

## Roadmap

- [x] 1) Get to grip with the basics
- [x] 2) CMake Compiles
- [x] 3) Create Screenshake
- [x] 4) Create GameState Class
- [X] 5) Create Animation system - expand the current PropertyAnimator class
- [X] 6) Create a particle system & pooling system
- ~~[] 7) Improved Input system - current means isn't scalable~~
- ~~[] 8) Create an audio system~~
- [] 9) UI
- [] 10) Storylet system (This is just to indulge my interests)

## Author and acknowledgement
I'm [Gregory Pellechi](https://github.com/OneGameDad), an experienced Narrative Designer and writer who has been learning to program in C & C++ at Hive Helsinki. I couldn't have done this without my mentor Aki.