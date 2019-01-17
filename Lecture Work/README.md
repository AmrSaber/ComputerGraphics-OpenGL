# Lecture Work
These 2 scripts are the implementation of requested lecture assignments and I decided to implement them instead of doing the work manually.

Note that those are the only 2 assignments written in python.

I made the code as readable as possible so anyone can understand it easily later (actually I used to memorize the algorithms from the code not from the lectures).

Dependencies (stated at the end of each problem) can be installed from the terminal (Windows or Ubuntu) using the following command:  
`pip3 install [library_name]`  
if you don't have pip installed, Google is your friend.

## Assignment 1
### Problem
We were requested to calculate the integer points along the path of a straight line and a circle using Bresenham's line algorithm and its extension for curves.

### Solution
I wrote a script that would run and take input from the terminal.  
The script has several commands and you can use it from the terminal as ..  
`python3 LinesAndCircles.py [command]`  
and instead of `[command]` you type your command which is one of the following:

```
-h, --help            show this help message and exit
-tl                   Test Line: Draw sample test line
-tc                   Test Circle: Draw sample test circle
-v                    Verbos: Print generated points
-nd                   No Draw: Don't draw the points
--line int int int int
                    Accepts 4 integers (x, y) of start and (x, y) of end
                    respectivly
--circle int int int  Accepts 3 integers (x, y) of center and radius of the
                    circle respectivly
```
Also the code is pretty much straight forward, you can open the script and see how the algorithms work for your self.

### Test Line/Circle Images
![Test Line image](https://i.imgur.com/30sHqY6.png)

![Test Circle image](https://i.imgur.com/cFgZR2H.png)

### Dependencies
- Python3 (make sure it's 3 not 2)
- matplotlib

## Assignment 2
### Problem
We were asked to show the transformation matrix after some transformations are applied then the show the final result after applying those transformations to a certain point.

### Solution
This time no fancy terminal-commands stuff, this time you open the script and write the transformations you want and see the result when you run the script.

### Dependencies
- Python3 (Again make sure you don't use python2)
- numpy
