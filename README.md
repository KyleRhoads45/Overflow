# Overflow
I built a data-oriented game engine using C++ and made an example platformer game for testing purposes.

![OverflowGameplay](https://user-images.githubusercontent.com/52022661/211657669-d7cda915-9ac5-409e-90dd-4fce8ed49573.gif)

### Features
* Sprite sheet animations with animation controllers
* Batch Renderer
* Entity Component System
* AABB Collision Detection and Reconciliation
* Circle Collision Detection
* Level Editor
* Level Serialization

### Rendering
Rendering for the game is hardware accelerated using OpenGL. In addition sprites are dynamically batched, resulting in fewer draw calls to improve GPU utilization.

### Physics
The game features two main types of collision detection, axis aligned bounding box (AABB) and circle collision detection. AABB is used for collision detection and reconciliation between the player and the level. Circle collision detection is used to detect when the player enters a sawblade or reaches the end of the level. Both types of collision detections use sweeps to ensure the player doesn't tunnel through objects when moving fast or if the game experiences frame drops.

![OverflowPhysics](https://user-images.githubusercontent.com/52022661/211658031-075b87a5-7ff2-4e34-9f0b-3703778f8723.gif)

### Level Editor
In order to make levels quickly I created an editor which allows the picking and placing of tiles into the level. When placing tiles you can specify their Z coordinate to make the player appear in front of or behind the tile. Tiles can also be overwritten with other tiles or erased entirely. Additionally, levels can also be created, saved, loaded, and deleted through the editor. Levels are saved into a text file that contain all the entities within that level and their positions.  

![OverflowEditor](https://user-images.githubusercontent.com/52022661/211658082-843de8c9-e6ae-4552-8c31-6a43d0748650.gif)

### Libraries
* [glfw3](https://github.com/glfw/glfw) - Used for window creation and input.
* [glad](https://github.com/Dav1dde/glad) - Used to load modern OpenGL functions.
* [glm](https://github.com/g-truc/glm) - OpenGL mathematics.
* [entt](https://github.com/skypjack/entt) - Entity component system.
* [stb_image](https://github.com/nothings/stb/blob/master/stb_image.h) - Used to load images.
* [Dear ImGui](https://github.com/ocornut/imgui) - Used for the level editor GUI

### About
This game was my senior project at CSU Chico and was intended to explore how game engines work.

![OverflowPoster](https://user-images.githubusercontent.com/52022661/211072131-e2b6691c-75e7-4e9d-adf2-45580cd26380.png)
