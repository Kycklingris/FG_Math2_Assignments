# Gameplay mathematics
This ended up being very rushed due to reasons.
 - Relative Context is created in ContextComponent and used in AssignmentPlayer for a shitty "backstab", that checks if the player is behind and intersecting
 - Intersection is used in the above mentioned context.
 - Interpolation and noise is defindedin EasingFunctions and used in AssignmentPlayer, interpolation for acceleration (didn't wanna spend time on keeping velocity so no deceleration) and one dimensional noise is used for shaking the camera on landing.
 - Collision is probably the worst one, only collision between a sphere collider and AABB exists, and it seemed annoying to do any sweeping or keeping track of previous positions to stop with the colliders touching, so instead, I kind of, maybe, only use the distance between the nearest point on the aabb and the sphere edge, obviously this wouldn't work for most use cases, and as such is only used for collisions from caused by gravity as I can just offset the player in the up direction based on the distance. Guessing it might not fully fit the requirements of the assignment, but... Am lazy.