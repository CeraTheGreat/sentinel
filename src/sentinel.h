#ifndef _SENTINEL_
#define _SENTINEL_

#include <stdbool.h>
#include <stdint.h>


/*
 *                                   Usage
 * =============================================================================
 *   sentinel [opts] <sentinel_script>
 *
 *                                 Arguments
 * =============================================================================
 *   -f <filename>  --  Specify the name of a text file as input. If none are 
 *                      selected, will instead read from stdin.
 *
 *   -o <filename>  --  Specify the name of an output file. Will create a new 
 *                      file if none exists and overwrite any which do. If none
 *                      specified, will instead write to stdout.
 *
 *   -i <script>    --  Provide script through opts rather than as an arg.
 *
 *   -c <sntl_file> --  Provide a .sntl file as a precompiled script.
 *
 *   -C <filename>  --  Output a compiled .sntl file from the provided script
 *                      for use later.
 *
 *   -w             --  Wrap newlines. Sentinel marching by default ends at 
 *                      newlines. Marching may optionally wrap around newlines 
 *                      with -w. If wrapping is enabled, things will only stop 
 *                      after the last code has finished executing.
 *
 *   -h             --  Display help message.
 *
 *
 *
 *                              Sentinel Codes
 * =============================================================================
 *   <, >         - direction state
 *   +, -         - read/skip state
 *   <<[n], >>[n] - jump forward or backwards by n within bounds
 *   :(c)         - move until we find character c (c required)
 *   .(c)[n]      - output character c (c required)
 *   ![n]         - 'backspace' n characters in output
 *   $            - move until reaching '\n' or '\0' (an 'end')
 *
 *   If [n] is excluded, it is presumed to be equal to 1
 *
 *   Example: 
 *   +>:x.,:z
 *	
 *     +  - read mode
 *     >  - move to the right
 *     :x - move to the right and read chars till we hit 'x'
 *     ., - write ',' to the output
 *     :z - move to the right and read chars till we hit 'z'
 *     done
 *
 *
 *   Example:
 *   +>: .,-:[>>3+$
 *     
 *     +   - read mode
 *     >   - move to the right
 *     :   - read to space character
 *     .,  - write ',' to the output
 *     -   - skip mode
 *     :[  - skip to '[' character
 *     >>3 - skip 3 to the right
 *     +   - read mode
 *     $   - read to an end
 *     done
 *
 *
 *                             Overview of Process
 * =============================================================================
 *   Parsing is slow and complicated. Therefore it is necesary to compile the
 *   codes beforehand. 
 *
 *
 *   0000 0000   0000 0000   0000 0000
 *   +--+ +--+   +-------+ - +-------+
 *   |    |      |
 *   |    |      +- arguments (n and/or c)
 *   |    |
 *   |    +- states (+ - < >)
 *   |
 *   +- actions (<< >> : . $ !) 
 *
 *   Actions:
 *     1000 - $
 *     0100 - :(c)
 *     0010 - .(c)
 *     0011 - .(c)[n]
 *     0001 - !
 *     1001 - ![n]
 *     1100 - <<
 *     1010 - <<[n]
 *     0110 - >>
 *     0101 - >>[n]
 *
 *   States:
 *     0001 - >
 *     0010 - <
 *     0100 = -
 *     1000 = +
 *     1001 = + and >
 *     1010 = + and <
 *     0101 = - and >
 *     0110 = - and <
 *
 *   Arguments:
 *     0, 1 or 2 bytes depending on what the needs are
 *
 *     0 - when no arguments are needed -- $ ! << >>
 *     1 when a single char is being passed -- :(c) .(c)
 *     2 when a char and int are being passed -- .(c)[n]
 *     2 when a single int is being passed -- ![n] <<[n] >>[n]
 *
 *
 *   Actions and States can be done in the same instruction.
 *   Multiple actions cannot be merged into one instruction.
 *   Conflicting states < and > or + and - cannot be merged either.
 *
 */


typedef struct _state {
	enum { SHORT_MODE, LONG_MODE } script_mode;
	enum { MV_POS, MV_NEG } move_dir;
	enum { READ, SKIP } read_mode;
} state_t;

void show_help();

void compile_script(uint8_t **dest, size_t *length, char *script);

#endif
