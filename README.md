# SFML_Experiments
My learning experiments with SFML, C++ and CMake

## Description
These are a series of tools I'm creating in an effort to learn SFML, improve at C++, create a small game engine, program for video games, and prepare for the Supercell Internship Challenge Day at Hive Helsinki.

## Current Working Features
These features are now based on core provided by Supercell for the Supercell Internship Challenge Days. Integration with them has been key to understanding the architecture they use. All of the tools now integrate with it, but ultimately need some tuning.

### GameTime
GameTime is a singleton class, which can return Delta Time & Current Time, as well as Unscaled versions of Delta Time and Current Time.

### GameState
GameState is singleton class, used to track any shared data that other classes needed. It currently isn't used for anything.

### PropertyAnimator
PropertyAnimator uses PerlinNoiseGenerator to provide animation timing.

### PerlinNoiseGenerator
PerlinNoiseGenerator is a singleton class, used to generate Perlin noise from a bitmap image.

### Googly Eye
A simple test animation to replicate a googly eye, by replacing the texture of a sprite.

### Particle System
A particle system using sf::VertexArray and sf::Quad to draw particles. Abstracted it to create a fire effect. It needs some refinement and the current textures are too large. But it can have multiple emitters which can follow a target. The fire effect proves it can be do multiple types of effects. This was created using Chat-GPT to help me with the calculations.

### HUD Component System
The HUD Component is the base class for a simple HUD/UI system. It does not have the functionality of Imgui or other full sytems. But it provides a level of abstraction and control.

#### Player Health Bar
This is a HUD element that scales to the player's size, and always follows their position. It should also reduce in length to show how much health a player has remaining (needs further testing). This will be easily replicable for enemies and other characters.

### Level System
ALevel is copy of the Game class provided by Supercell. It is meant to be a micromanager of entities in a single level or scene of a game. I abstracted it out so that I wouldn't have to write everything into a single Game class. But can how have the Game class load a particular Level Class and thus only the relevant textures, classes, etc. For use, Game just needs to be updated to load it. This is forthcoming

## Roadmap

- [x] 1) Get to grip with the basics
- [x] 2) CMake Compiles
- [x] 3) Create Screenshake
- [x] 4) Create GameState Class
- [X] 5) Create Animation system - expand the current PropertyAnimator class
- [X] 6) Create a particle system & pooling system
- ~~[] 7) Improved Input system - current means isn't scalable~~
- ~~[] 8) Create an audio system~~
- [X] 9) UI
- [] 10) Update Game to use ALevels
- [] 11) Storylet system (This is just to indulge my interests)

## Author and acknowledgement
I'm [Gregory Pellechi](https://github.com/OneGameDad), an experienced Narrative Designer and writer who has been learning to program in C & C++ at Hive Helsinki. I couldn't have done this without my mentor Aki.