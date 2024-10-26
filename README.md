# Requests

**A C++ version of the python requests library**

# To Build

****This will create an executable based off the requests_tests.c++ file****

To create the build for this `requests` library, create a buld directory if it doesn't already exist, and `cd` into it.
Then run the command:

    cmake .. to create the build.

Once that's complete, from within the `build` directory, run:

    make

This will create the `object` directory (if it doesn't already exist) and in it place
the executable that can be used to test out the library.

To run the executable, from the requests project directory (The level where the `CMakeLists.txt` file exists at),
run:

    ./objects/requests_tests [URL] where URL is any website whose html you want to retrieve.



# Current Issues

    * I have no idea if the code will work... My guess is it won't, but that's what tomorrow is for. :D


# Resolutions (in progress)

    * Currently the only url that seems to work is `example.com`. More debugging need to occur to find out why this keeps happening.
        * I got in contact with ([Lews Van Winkle](https://codeplea.com/about)) the author of a wonderful book on network programming in C ([Hands On Network Programming in C](https://handsonnetworkprogramming.com/)) and he explained the problem I was experiencing here. He then told me how I could find the solution. I got the architecture figured out and I coded most of it. I need to start testing it and debugging though.