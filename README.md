# Generator

A Lincoln Programming Club challenge project for "Generation". Collaboration with @rwilliase

Generates an island using a wandering simulated "turtle", and fills with colors and biomes with OpenSimplex noise.

Click to regenerate the island. Runs very slowly, as performance was not a priority on this project. It iterates through each pixel and resamples the noise class, which is not ours, and which the algorithm is certainly not optimized for.
If you would like to speed up the program, you can turn off the regeneration of the noise function with the REDOMAPS directive.

![image](https://i.imgur.com/NlegGfX.png)

Features that could be added in the future:
* Elevation and better stepping of biome graphics
* More biomes
* Recursive details in the island shape
* Transposition of the application of the algorithm to severely decrease time complexity of regenerating noise & island
* A better shader function
* More realistic-colored water
* More configuration options
* General code cleanup
