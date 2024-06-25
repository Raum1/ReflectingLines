# RAYCASTING 2D simulation
I made all of this due to my boredom during the xmas holidays, doesn't have to be something special however i decided it won't be redundant to upload here. The project is about 2d simulation of raycasting that i made using c++ sfml library (mainly for graphic part). Dragging mouse we move the rays source and in main.cpp line 33 (rays lines(pos, 256, raysColor);) we can change the number of rays. Here's what each file responds for:

## wall.h and wall.cpp
This is a class of wall, i don't see anything special here it just creates a segment between 2 points and contains beginning pos, ending pos and static list of all instances and method to return it (i will explain further why it's needed)

## rays.h and rays.cpp
The heart of project, basically all of logic is written there. Here's the purpose of each variable and method:
**sf::VertexArray raysSource** - the very lines to draw them later
**sf::Color color** - the color of rays
**rays(sf::Vector2f pos, int numOfRays, sf::Color color)** - constructor which creates beams that are looking in all directions. Basically it asigns pos to the initial position of all rays and builds from it straight line from the center to far far away right. After that we divide TAU (2pi) by numOfRays to get an angle between each beam. Then, using formula x' = x*cos(θ)-y*sin(θ); y' = x*sin(θ)+y*cos(θ) we calculate the next end position of the line. The magnitude of this vector is either big number (when there is no obstacle ahead) or distance between the initial position and the closest hit point that lines on the segment. That's why we use methods float get_distance(sf::Vector2f pos1, sf::Vector2f pos2), and bool is_on_segment(sf::Vector2f& beg, sf::Vector2f& end, sf::Vector2f& point). The calc_hit method is the heart of collision logic, basically it converts solves for slope (m) and intercept (b) of the wall and line and then solves for x,y of hit point (it's basic math that i think don't have to explain). After that we check whether is that point within wall and rays segment and if so it returns the point, otherwise we get some point very far away. The closest_hit method checks for all the walls (and that's why static std::vector<wall*> objList is needed) and returns the closest point

## How to run with VS Code (LINUX)
**Install the files** and run *raytracing2D* with command ./raytracing (if you are in the folder of the project)

### To compile
**Make sure** SFML is installed (preferably 2.6.1, i did on this version). Copy path to the include folder of SFML "includePath" in *c_cpp_properties.json*. To compile with g++ you need to run this command
''' g++ -o raytracing2D main.cpp wall.cpp rays.cpp rando.cpp -lsfml-graphics -lsfml-window -lsfml-system '''
It will create and replace a new raytracing2D.o file 

##

Next in the project i plan to create lines reflection and maybe some interface to change the properties of rays during the work of program   
