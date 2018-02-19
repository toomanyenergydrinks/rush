# RuSH: Ray's Unremarkable SHell

This is intended as a learning experiment, I'm going to try and leave as many comments as possible so other people can understand it. Initial material is from the following article, the rest were based on assignments I found across the net relating to OS courses about writing shells.

# Features:
* Built-in functions (currently help, cd and exit)
* Displays current working directory
* Can launch programs
 
# Proposed Additions
* Adding command history
* Integrating a Ruby interpreter
* Adding unit test coverage (CMocka already set up)

# Proposed Additions from CS Course Questions
## Cornell CS414
* ~~The prompt you print should indicate the current working directory. For example:  The directory: /usr/foo/bar%~~
* It may also indicate other things like machine name or username or any other information you would like. Try getcwd(char * buf, size_t size) .
* You should be able to redirect STDIN and STDOUT for the new processes by using < and >. For example, foo < infile > outfile would create a new process to run foo and assign STDIN for the new process to infile and STDOUT for the new process to outfile. In many real shells it gets much more complicated than this (e.g. >> to append, > to overwrite, >& redirect STDERR and STDOUT, etc.)! 
* You should be able to place commands in the background with an & at the end of the command line. You do not need to support moving processes between the foreground and the background (ex. bg and fg). You also do not need to support putting built-in commands in the background.
* You should maintain a history of commands previously issued. The number of previous commands recorded can be a compile time constant of at least 10. This is a FIFO list, you should start numbering them with 1 and then when you exhaust your buffer you should discard the lowest number *BUT* keep incrementing the number of the next item. For example, if storing 10 commands, when the 11th is issued, you would be recording commands 2 through 11.
* A built-in command is one for which no new process is created but instead the functionality is build directly into the shell itself. You should support the following built-in commands: jobs, cd, history, exit and kill. jobs provide a numbered list of processes currently executing in the background. Try waitpid with WNOHANG option to check without blocking. You can either check when jobs called or each time through the main while loop. cd should change the working directory. history should print the list of previously executed commands. The list of commands should include be numbered such that the numbers can be used with ! to indicate a command to repeat. exit should terminate your shell process, kill %num should terminate the process numbered, num in the list of background processes returned by jobs (by sending it a SIGKILL signal).
* If the user chooses to exit while there are background processes, notify the user that these background processes exist, do not exit and return to the command prompt. The user must kill the background processes before exiting.
* You may assume that each item in the command string is seperated on either side by at least on space (e.g. prog > outfile rather than prog>outfile).
