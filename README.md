# snake

A simple implementation of snake to further test my pixel rendering engine [Pixul](https://www.github.com/connormdoane/Pixul/)

# Running
The included makefile has a gcc command to compile, but if you wish to compile with your own command ensure you include the -lSDL flag since Pixul uses SDL2 to render the image.

During gameplay, use the WASD keys to move the snake, and Q to quit. The spacebar pauses play, and pressing N while paused iterates play by one frame at a time.
