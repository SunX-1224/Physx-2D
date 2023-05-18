# Physx-2D

Physx2D is a in-development early stage physics and rendering engine for mainly 2D graphics. It is developed only for windows 64 bit OS only. Very few things are implemented until now relating to rendering and physics.

# Rendering 
Inside this different options related to 2D rendering is implemented, which are listed as below,
* Normal Renderer
* Instanced Renderer
* Framebuffer
* Textures
* Shaders

Not everything is very flexible and can be implemented in any form, but development and optimizations are going on.

# 2D Physics

Although a "proper physics handling system" is still far off from where the it is, a base for handling very minimalistic 2d physics is implemented till now which includes basic rigidbody physics, collision detection and proper dynamics of elastic and inelastic collisions. Algorithms used are implemented in raw way without not much optimization, but works for now.

QuadTree is used for handling on-screen collisions of object, when no clustering of thousands of objects is present, this can handle many colliding objects over 5 thousand. Framerate will drop is thousands of objects are clustered in one place. No substeps for collision optimization is implemented and no separate thread for handling physics is implemented till now.

On the bright side, there are 4 types of colliders that can be used,
* CircleColliders
* BoxCollider2D
* AABB
* Bounding Circle

Among them, last 2 colliders are static (and implemented only to make it easy to setup a physics simulation where objects won't fly off screen. On a single screen, AABB and BoundingCircles should not overlap with any of each other due to what they are made for.

# Math
A basic math setup for some structures like vec2, vec4 and mat3, (only those required by program are implemented, others : TODO) is there when needed.

Currently there is no GUI layer implemented, so everything has to be done in code.

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
