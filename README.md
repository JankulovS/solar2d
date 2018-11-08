# Solar2D
Simulation of n-body physics in a 2D environment using RK4  
  
  ![Preview](https://thumbs.gfycat.com/ElaborateAthleticBilby-small.gif)

  
## Requirements
SFML library

Sprites (folder \data)

## Features
 - A few premade scenes that show off stable and unstable orbits
 - Dynamic body adding with precise speed vector using click-and-drag
 - Dynamic camera control, with zoom and translation
 - Adjustable timestep
 - Collisons that combine body mass and speed of both into a single body
 - Pausing of simulation.
 - Orbital lines for easier following of orbit changes from other bodies' gravitational interference

## Algorithm
Solar2D is a simulation of n-body physics (solar system style gravitational attractions) using the Runge-Kutta (RK4) algorithm. Calculating changes of positions (solving differential equations) using RK4 instead of the basic Euler method provides a much more precise calculation (taking gradients into account), and using sufficiently small timesteps provides maximum precision.  
  
RK4, unlike the Euler method, can have very long lasting stable configurations with minimal precision loss. Solving the problem using the Euler method will degrade the orbits and cause initially stable orbits to decay and eventually collapse. Even with higher precision from RK4, having a high timestep will still lower precision, so instead of increasing the timestep for faster time passing, it's better to compute two timesteps with a lower value than one with a higher. This assures no precision loss, but requires more computing power.
