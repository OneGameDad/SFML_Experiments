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

### HUD Component System
The HUD Component is the base class for a simple HUD/UI system. It does not have the functionality of Imgui or other full sytems. But it provides a level of abstraction and control.

#### Player Health Bar
This is a HUD element that scales to the player's size, and always follows their position. It should also reduce in length to show how much health a player has remaining (needs further testing). This will be easily replicable for enemies and other characters.

#### TextBox
This is a HUD element that does what it says in the box. Dad jokes aside. It's a replicable and controllable means of putting text on screen.

##### WeaponTextBox
This is a Textbox designed to be used in place of Particle and/or Sound Effects for prototyping purposes. Currently it can be seen on the Player, and appears near the Weapon when it is active. It is meant to simulate particle and sound effects, but is quicker and easier to implement.

#### StoryletBox
This is another textbox but with the ability to be updated so the text may be changed. It can be placed and have various attributes set. One is currently visible in Game. The logic for changing what text is within the Game.cpp file.

### StoryletReader
Storylets are small atomic stories, for the purposes of demonstrating my narrative design and programming skills I made a simple system for storytelling, tutorials and other text.

StoryletReader is a singleton that automatically loads a file called storylets.txt (found in the assets folder) via the ResourceManager system provided by Supercell. Each line is a single storylet, which are stored in a map. The key is the first part of the line, with the value delimited by "\t". These can be set in TextBoxes by calling the StoryletReader.

### Projectile System
This is a the basics of a repeatable system for projectiles. It utilizes AProjectile for the projectile class and ProjectileManager, the class BoundingBox was also created to set a limit for how far the projectiles would travel.

#### AProjectile
This is derived from the Rectangle Class provided by Supercell, as such uses the same method for collision detection for both the BoundingBox and the Vampire. Currently the projectiles travel in a straight line, but would be easy enough to modify with gravity and other variables.

#### ProjectileManager
This is a manager that utlizes a vector for the pool. Upon initialization it constructs all of the objects within it. It is also used for spawning them and cleaning them up. I chose to pool rather than construct and deconstruct objects because it's standard practice in game development, and just smart in terms of system calls and optimizations.

#### BoundingBox
A simple derived class from the Rectangle Class provided by Supercell, it is meant to set limits for objects that check collisions.

## Roadmap

- [x] 1) Get to grip with the basics
- [x] 2) CMake Compiles
- [x] 3) Create Screenshake
- [x] 4) Create GameState Class
- [X] 5) Create Animation system - expand the current PropertyAnimator class
- [X] 6) Create a particle system & pooling system
- ~~[] 7) Improved Input system - current means isn't scalable:~~ Now using Supercell InputHandler
- ~~[] 8) Create an audio system~~
- [X] 9) UI
- ~~[X] 10) Update Game to use ALevels~~
- [X] 11) Storylet system (This is just to indulge my interests)
- [X] 12) Projectile system - Moving objects that can collidge and damage other objects
- [] 13) Map system - Terrain and the ability to move from one screen to another
- [X] 14) Reorganize Repo - Cleaned things up for ease of use and visibility

## Removed Features
These features have been removed for one reason or another

### Particle System
A particle system using sf::VertexArray and sf::Quad to draw particles. This was created using Chat-GPT to help me with the calculations. As a result I wasn't happy with it. And decided to no longer use it. It can still be found in some folders from earlier branches, but is no longer in use in later branches.

### Level System
ALevel is copy of the Game class provided by Supercell. It is meant to be a micromanager of entities in a single level or scene of a game. I abstracted it out so that I wouldn't have to write everything into a single Game class. Ultimately this was removed because it was more cumbersome than it was worth for a prototype.

## Author and acknowledgement
I'm [Gregory Pellechi](https://github.com/OneGameDad), an experienced Narrative Designer and writer who has been learning to program in C & C++ at Hive Helsinki. I couldn't have done this without my mentor Aki.