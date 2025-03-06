

#if not defined(_MISC_FUNCTIONS_)
    #define _MISC_FUNCTIONS_
    
    #include "../headers/included.h++"

    namespace misc_functions {


        /**
            @brief Get the current time on this local system
            @return A `std::string` of the current time (date and time) on the system.
        */
        const std::string get_current_time();


        /**
            @brief Get the terminal's (for UNIX or cmd/powershell on WIN) width.
            @returns An `int` representing the Command line's width.
        */
        int get_terminal_width();


        /**
            @brief Get the terminal's (for UNIX or cmd/powershell on WIN) height.
            @returns An `int` representing the Command line's height.
        */
        int get_terminal_height();


    }

#endif