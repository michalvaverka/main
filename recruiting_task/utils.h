/**
    @filename:  utils.h
    @author:    Michal Vaverka

    @description:
                File containing only macros for errors to keep the code clean.

    @projectdescription: 
                The task was to write a code, which would extract certain data from a file and write them in a specific
                format to another file.

                This task was given to me as a recruiting task when I was applying for a job in METEL s.r.o.

    @predisclaimer:
                Disclaimer and rules on usage are listed in order to avoid plagiarization in academic institutions.
    
    @disclaimer:
        !!! READ !!!
                Any part of this code can be used IF AND ONLY IF all of the following conditions hold:
                    1) The whole header of this file (from the @filename to the end of the @disclaimer section) must be pasted
                            directly above where the borrowed snippet/whole code is used,
                    2) The project borrowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/

#ifndef UTILS_H
#define UTILS_H

//Error return values macros
#define PARAM_ERROR 1
#define FILE_ERROR 2
#define MEM_ALLOC_ERROR 3
#define DATA_FAULT 4

#define NO_DATA -1

#endif
