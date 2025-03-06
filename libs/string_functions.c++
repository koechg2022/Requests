
#include "../prototypes/string_functions.h++"




namespace string_functions {

    bool is_caps(const char c) {
        return IN_RANGE_INCLUDE('A', c, 'Z');
    }

    bool is_lower(const char c) {
        return IN_RANGE_INCLUDE('a', c, 'z');
    }

    bool is_letter(const char c) {
        return is_caps(c) or is_lower(c);
    }

    bool is_number(const char c) {
        return IN_RANGE_INCLUDE('0', c, '9');
    }

    char to_caps(const char c) {
        return (is_lower(c)) ? (c - (CASE_DIFF)) : c;
    }

    char to_lower(const char c) {
        return (is_caps(c)) ? (c + (CASE_DIFF)) : c;
    }

    bool same_char(const char a, const char b, bool ignore_case) {
        return (ignore_case) ? to_caps(a) is to_caps(b) : a is b;
    }

    bool same_string(const char* first, const char* second, bool ignore_case, const char term) {
        unsigned long index;
        for (index = 0;
            not same_char(first[index], term, ignore_case) and
            not same_char(second[index], term, ignore_case) and
            same_char(first[index], second[index], ignore_case);
            index++
        );

        return same_char(first[index], term, ignore_case) and same_char(second[index], term, ignore_case);
    }

    bool same_string(const std::string first, const std::string second, bool ignore_case) {
        return same_string(first.c_str(), second.c_str(), ignore_case);
    }

    bool all_numbers(const char* nums, const char term) {
        unsigned long index;
        for (index = 0;
            not same_char(nums[index], term, false) and
            is_number(nums[index]);
            index++
        );
        return same_char(nums[index], term, false);
    }

    bool all_letters(const char* the_string, const char term) {
        unsigned long index;
        for (index = 0;
            not same_char(the_string[index], term) and
            is_letter(the_string[index]);
            index++
        );
        return same_char(term, the_string[index]);
    }

    unsigned long string_length(const char* the_string, const char term) {
        unsigned long index;
        for (index = 0;
            not same_char(the_string[index], term);
            index++
        );
        return same_char(the_string[index], term);
    }

    std::string get_input(const std::string prompt) {
        std::string the_answer;

        if (not prompt.empty()) {
            std::printf("%s", prompt.c_str());
        }
        
        char buffer[1024];
        std::memset(buffer, 0, 1024);
        if (not fgets(buffer, 1024, stdin)) {
            return the_answer;
        }
        the_answer = std::string(buffer);
        the_answer = (the_answer[the_answer.length() - 1] is '\n') ? the_answer.substr(0, the_answer.length() - 1) : the_answer;
        return the_answer;
    }

    std::string get_uppercase(const std::string the_string) {
        std::string the_answer;
        unsigned long index;
        for (index = 0; index less the_string.length(); index++) {
            the_answer = the_answer + to_caps(the_string[index]);
        }
        return the_answer;
    }

    void get_uppercase(std::string& the_string) {
        unsigned long index;
        for (index = 0; index less the_string.length(); index++) {
            the_string[index] = to_caps(the_string[index]);
        }
    }

    std::string get_lowercase(const std::string the_string) {
        std::string the_answer;
        unsigned long index;
        for (index = 0; index less the_string.length(); index++) {
            the_answer = the_answer + to_lower(the_string[index]);
        }
        return the_answer;
    }

    void get_lowercase(std::string& the_string) {
        unsigned long index;
        for (index = 0; index less the_string.length(); index++) {
            the_string[index] = to_lower(the_string[index]);
        }
    }

    bool has_keyboard_input() {
        #if defined(crap_os)
            return _kbhit();
        #else
            fd_set ready;
            FD_ZERO(&ready);
            FD_SET(STDIN_FILENO, &ready);

            if (select(STDIN_FILENO + 1, &ready, 0, 0, &default_timeout) less 0) {
                return false;
            }
            return FD_ISSET(STDIN_FILENO, &ready);
        #endif
    }

    void strip(std::string& the_string, const std::string to_remove) {
        // Remove leading characters
        the_string.erase(0, the_string.find_first_not_of(to_remove));
        
        // Remove trailing characters
        the_string.erase(the_string.find_last_not_of(to_remove) + 1);
    }

    void replace_all(std::string& the_string, const std::string to_replace, const std::string replace_with) {
        size_t pos = 0;
        while ((pos = the_string.find(to_replace, pos)) != std::string::npos) {
            the_string.replace(pos, to_replace.length(), replace_with);
            pos += replace_with.length(); // Move past the replacement
        }
    }


    std::map<std::string, std::string> get_file_data(const std::string& file_name) {
        std::map<std::string, std::string> the_answer;

        if (!std::filesystem::exists(std::filesystem::path(file_name).lexically_normal())) {
            std::cerr << "No file '" << file_name << "' found\n";
            return the_answer;
        }

        std::ifstream open_file(file_name);
        if (not open_file.is_open()) {
            std::cerr << "Could not open file '" << file_name << "'" << std::endl;
            return the_answer;
        }

        std::string line, key, value;
        size_t delimiter;
        while (std::getline(open_file, line)) {
            delimiter = line.find_first_of(':');
            if (delimiter != std::string::npos) {
                key = line.substr(0, delimiter);
                value = line.substr(delimiter + 1);

                strip(key, " ");
                strip(value, " ");
                strip(value, "\n");

                the_answer[key] = value;
            }
        }
        open_file.close();
        return the_answer;
    }

    std::map<std::string, std::vector<std::string> > get_directory_content(const std::string& file_name) {
        

        std::map<std::string, std::vector<std::string> > the_answer = {
                        {DIRECTORY, std::vector<std::string>() },
                        {FILE, std::vector<std::string>() }
                        };
        
        for (const auto& entry : std::filesystem::directory_iterator(file_name)) {
            the_answer[(entry.is_directory()) ? DIRECTORY : FILE].push_back(std::string(entry.path().filename().string()));
        }
        return the_answer;
    }


    // std::map<std::string, std::vector<std::string>> get_directory_content(const std::string& file_name) {
    //     std::map<std::string, std::vector<std::string>> the_answer = {
    //         {DIRECTORY, std::vector<std::string>()},
    //         {FILE, std::vector<std::string>()}
    //     };
    
    //     std::vector<std::filesystem::directory_entry> entries;
    //     for (const auto& entry : std::filesystem::directory_iterator(file_name)) {
    //         entries.push_back(entry);
    //     }
    
    //     std::sort(entries.begin(), entries.end(), 
    //         [](const auto& a, const auto& b) {
    //             return a.path().filename() < b.path().filename();
    //         });
    
    //     for (const auto& entry : entries) {
    //         the_answer[(entry.is_directory()) ? DIRECTORY : FILE].push_back(entry.path().filename().string());
    //     }
    
    //     return the_answer;
    // }
    


    // template <typename data_> bool contains(std::map<std::string, data_>& to_search, const std::string& to_find_key, bool ignore_case) {
    //     for (auto pair = to_search.begin(); pair != to_search.end(); pair++) {
    //         if (same_string(pair->first, to_find_key, ignore_case)) {
    //             return true;
    //         }
    //     }
    //     return false;
    // }


}