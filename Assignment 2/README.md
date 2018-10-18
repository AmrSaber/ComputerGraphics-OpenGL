# Assignment 2
### Problem
Make a simulation of a scientific principle.  
This assignment was made in association with [Salma Sayed](https://github.com/SalmaSayed).

### Solution
We chose to simulate the "[Solids Of Revolution](https://en.wikipedia.org/wiki/Solid_of_revolution)" which refers to the surfaces that are formed from rotating mathematical functions about one of the Cartesian axes, check the link for more details.  

#### First Of All
We wanted to make the program __as general as possible__, so we implemented a simple expression parser, which takes a string consisting of mathematical expression and parses it into programmable object.  
The parser (in files Exp.h, Exp.cpp) accepts all kinds of polynomials with all their forms, using **^** for exponentiation, e.g. "`x`", "`x^2`", "`2x^4`" + "`2x + 5`", "`x^2 + 4x + 12`", etc. (spaces are totally ignored)  
It also accepts trig and heyper-polyic functions with the limitation that they can only have "x" as their parameter, but they can have coefficients and powers (for the function itself) no problem, e.g. "`sin(x)`", "`2 cos(x)`", "`3 tanh(x)^2`", "`5 acos(x)^2 + 12 x^2`", etc.  
We then used this expression parser to feed the functions into the plotter-part of the program which then plotted and revolved the equation about the desired axes (x or y).

### Second Of All
We plot the function provided by the parser and repeat it several times (about 3600) with different rotation each time to show the final __Solid__ shape.  
When the shape was plotted for the first time, we had a problem with showing that it's actually a 3D shape, so we put all sorts of lights (ambient, directional and specular) to show the depth and curvature of the shape. (this part is alot easier said than done, really!)  
Last but not least we added the functionality for the user to change the angle and the position of the camera with respect to the plot for a better viewing of the formed shape, the user can move up and down with `W` and `S`, they can also rotate the graph with `A` and `D`.

#### GIF Of The Program Execution
![Execution GIF](https://i.imgur.com/d62B4Mg.gif)

#### Note
We may return to this project later to add watching the solid form.
