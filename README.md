## Game Description

Developed a 3D OpenGL game featuring dynamic environments where players strategically engage and destroy enemy tanks. Implemented advanced shaders to enhance visual appeal, delivering stunning graphics and realistic lighting effects.
Expertly handled collision detection for seamless gameplay mechanics, ensuring precision in shooting interactions. Engineered randomized enemy tank movements, contributing to an immersive and challenging gaming experience

## Demo

<img src="[link_to_demo_image](https://drive.google.com/file/d/1CUunwLbtLbhHwHhcJ_2zq2pMMlELkiV6/view?usp=sharing)" alt="click">

<img src="https://github.com/OctavianMihaila/Tanks3D/blob/master/p3.png?raw=true" alt="Tank Warfare">

## Usage

1. Import the game into the [framework](https://ocw.cs.pub.ro/courses/egc/setup-framework) by following the provided setup instructions.

## Project Structure

The game is organized into three key components: engine models, services, and shaders.

### Engine Models

Houses the fundamental entities of the game, including tanks, shells, and barracks. Implements core functionalities and behaviors of these entities.

### Services

Manages various game services, such as movement and collision handling. Organizes and orchestrates the game's logic and interactions.

### Shaders

Contains graphical shaders responsible for rendering the 3D environment. Enhances visual elements and contributes to the overall immersive experience.

## Enemy Movement System

The enemy movement system is intricately designed using a state-based approach. The RandomMovementService determines the next movement state based on the current state, offering dynamic and unpredictable enemy behavior. States include forward movement, backward movement, in-place rotation, and following the player with turret rotation. This system injects variety into enemy actions, creating a challenging and engaging gameplay experience.

## Collision Handling

The collision handling system ensures realistic interactions between game entities.

### Tank-Tank Collision

Prevents tanks from overlapping by adjusting their positions based on their directions.

### Tank-Shell Collision

Deals damage to tanks when hit by enemy shells, enhancing combat dynamics.

### Tank-Barracks Collision

Halts tanks upon colliding with barracks, adding strategic elements to gameplay.

### Shell-Barracks Collision

Marks shells as collided when hitting barracks, affecting game dynamics.

### BoundingBox Intersect Functions

Implement collision detection logic for various entity combinations (tank-tank, tank-shell, tank-barracks, shell-barracks). Utilizes bounding box calculations for precise collision handling.
