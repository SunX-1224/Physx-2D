# Physx-2D

Physx2D is a in-development early stage physics and rendering engine for mainly 2D graphics. It is now programmed for supporting windows and linux only.

# Rendering 
Inside this different options related to 2D rendering is implemented, which are listed as below,
* Normal Renderer
     > For rendering a single 2D-model/objects
* Instanced Renderer
     > For faster rendering of multiple similiar models/objects
* Framebuffer
     > For post-processing of the render
* Textures
     > For adding textures to objects
* Shaders
     > For shading the model/objects

A lot of optimization have been done in the rendering aspect of the engine to finally reduce the rendering time of thousands of objects to less than 0.1ms in release mode. Another plus side is that there are few default renderers implemented inside the engine for more reliability. Also default shader is also embedded directly inside the renderer. Some special shaders are also pre-written for better experience. 

# Utilities
Besides, there are som,e utility objects that can be used for multiple purposes.
* General Buffers
     > Buffers for storing data for being processed by GPU
* Compute Shaders (newly added)
     > Perform any processing/calculation on GPU in parallel
* QuadTree
     > QuadTree can be used for space partitioning in 2D-Space. It is also used by this engine for collision detection optimization.

# 2D Physics

Although a "proper physics handling system" is still far off from where the it is, a base for handling very minimalistic 2d physics is implemented till now which includes basic rigidbody physics, collision detection and proper dynamics of elastic and inelastic collisions. Algorithms used are implemented in raw way without not much optimization, but works for now.

QuadTree is used for handling on-screen collisions of object, when no clustering of thousands of objects is present, this can handle many colliding objects over 5 thousand. Framerate will drop if thousands of objects are clustered in one place. No substeps for collision optimization is implemented and no separate thread for handling physics is implemented till now. A generalized collision detected and resolution method used now is now in 'average' state. Type of collision detection used now is discrete. This part of engine works well for over 2 thousands collider components with the numbers being dependent on component type.

There are 4 types of colliders that can be used now,
* CircleColliders
* BoxCollider2D
* AABB
* Bounding Circle

Among them, last 2 colliders are static (and implemented only to make it easy to setup a physics simulation where objects won't fly off screen. On a single screen, AABB and BoundingCircles should not overlap with any of each other due to what they are made for.

# Math
Mathematical part of the engine includes some features like : 
* 2-Component vector
* 3-Component vector
* 4-Component vector
* 3x3 matrix
* Pseudo Random Number generator
     > As a function for short term random numbers and as an object for auto-seed update which is proved to best for procedural generations.
* Projection matrices and view matrices
* center-rect

# Entity Component System
A Physx-2D world handles objects according to their components (data oriented design) rather than inherited properties (object oriented design). This enables an object to have any combination of properties. Components currently available are :
* Transform
* Tag
* RendererComponent
* Collider : 
    * BoxCollider2D
    * CircleCollider
    * AABB
    * Bounding Circle
     {An object can have only one type of collider at a time}
* RigidBody2D
* ScriptComponent

This game engine as of now does not have an integrated editor. So, setup has to be done through code.

# Logging system
A simple yet effective logging system is implemented which is made to display the logged data in the debug mode. This will strip off the logging code in any other mode which makes the engine event faster in other mode and useful is debug mode.

* LOG_INFO logs the informations in green color
* LOG_WARN logs the informations in yellow color
* LOG_ERROR logs the informations in red color

> Also, ASSERTIONS are available in any mode as long as enabled.

> Also DEBUG_ONLY_EXPRESSIONS are also implemented which allows for debug mode to be effective in doing many things (e.g. performance evaluation and comparision).

> All these features are automatically enabled in respective build mode. These features can be enabled manually by defining some constants in any mode.

# SandBox
Time to time, some interesting simulations are added here. This is a general playground for anyone using it. With compute shaders added now, multiple processings for simulations can be now performed in parallel in GPU. Some simulations added till now are : 

* Autonomous agents :
   * Boids

* Ray tracing : *Incomplete*

* Cellular Automata :
   * Conway's game of life
   * Evan's larger than life
   * wolfram cellular automata rules simulations
   * Belousov-Zhabotinsky reaction
   * Another Reaction-Diffusion simulation that does something weird and spectacular

* Multi-Neighbour Cellular Automata:
   * Mitosis
   * Bacteria
   * Worms
   * Circles (But actually resembles a forest fire through a bug.... kept the bug because it looks cool)

* Wave Function Collapse Algorithm :
  * Some idea of quantum mechanics implemented in this engine to do some procedural generation of complex things from simple things
  * *Incomplete* (Backtracking not implemented but still works fine)

# Others
A project environment setup system is implemented using premake. Build system for windows is up and working, for Linux it is under testing as of now.

There are many things I did not explained about the engine here. Take a look at code or contact me if you want to understand it.

*Future plans for the project (large or small) are inside .todo file. Take a look if you want*

Anyone is free to contribute to some bug-fixing, feature-adding, suggestions, etc. Enjoy !!!!!!!!!!
