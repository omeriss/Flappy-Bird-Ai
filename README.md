# Flappy-Bird-Ai
flappy bird game with ai that learns how to play it in c++ and the simple grafics library sfml.
The neural network was written by me from scratch.

# The Neural Network
The convolutional neural net consists of 3 type of layers: Input, Hidden and output. 
The input layer for this nn is made out 5 neurons:
1. bird h
2. down pipe h
3. up pipe h
4. bird speed
5. bird dis to pipe
The output is 2 neurons. one for jump and one for not to jump.
The nn learn by mimicking evolution.
the nn starts with randon vals, after every gen I pick the best birds, combite them and tweak their val randomly.
In that way, only the bist birds every time survive and improve and that is how they learn.

# short video from the project



https://user-images.githubusercontent.com/94307825/146689617-75ab22ef-f80c-4e15-be9d-c3c40ce0d285.mp4

