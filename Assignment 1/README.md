# Assignment 1
### Problem
draw as much as you can from (5-gon, 6-gon, 7-gon, ..., 10-gon)

### Solution
Instead of hard-coding the verices of each polygon, I made a generic function that takes certain "information" about the polygon and draws it.  

These pieces "information" are:  
- The number of sides of the polygon  
- The radius of the inner circle of the polygon (the circle that touches all of its sides from the inside)  
- The (x, y) of the center of the inner circle  

Based on those pieces of information, the function returns the vertices of the polygon and it's based on some simple math as follows:  

Consider a polygon with n sides ...  
1) Divide each polygon to rectangles with their head at the center of the polygon (as shown in image below).  
2) Consider the top rectangle, calculate (x, y) for its right vertix (which is also a verix of the polygon), it will be (l * tan(a/2), l)  
   where a = 360/n and l = the radius of the inner circle.  
3) Rotate the coordinates of that point clock-wise for (n-1) times to get all the vertices of the polygon  
   points rotaion about the origin with angle a is done through the equations:  
   x' = x cos(a) + y sin(a), y' = y cos(a) - x sin(a)  
4) Translate every point with the value of the origin of the inner center given before and you get the polygon where you want it.  

#### Screen shot of sliced polygons:  
![sliced images here](https://imgur.com/mD3245V)

#### Screen shot of the final result:
![final polygons here](https://imgur.com/x2A47Mj)

