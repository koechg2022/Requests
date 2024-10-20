# Requests

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

Currently the only url that seems to work is `example.com`. More debugging need to occur to find out why this keeps happening.