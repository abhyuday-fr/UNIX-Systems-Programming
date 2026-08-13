# simple-shell
Step by step walkthrough
1. The parent process prints `$$` and waits for you to type. You type a command (for eg. `ls`) and hit Enter. The buffer now contains "ls\n".
2. `buf[strlen(buf) - 1] = '\0';`: The code strips the newline character so the buffer just contains "ls".
3. The parent forks itself
4. Parent's Path: The parent skips the if (pid == 0) block and hits waitpid. It goes to sleep, waiting for the child.
5. Child's Path: The child enters the if (pid == 0) block and calls execlp("ls", "ls", NULL).
6. The child's memory is overwritten by the /usr/bin/ls program. The ls program runs, prints the directory contents to the terminal, and exits.
7. The operating system sees the child die and wakes up the parent. waitpid finishes successfully
8. The parent reaches the end of the while loop, jumps back to the top, prints `$$` , and waits for your next command.

# simple-cat
Step by step walkthrough
1. You run the program, for example `./simple-cat < simple-cat.c`. Since `argc` and `argv` are unused, no arguments are parsed.
2. `while ((n = read(STDIN_FILENO, buf, BUFFSIZE)) > 0)`: The `read` syscall reads up to `BUFFSIZE` (32768) bytes from standard input into `buf` and stores the number of bytes read in `n`.
3. `if (write(STDOUT_FILENO, buf, n) != n)`: The `write` syscall copies those `n` bytes from `buf` to standard output. If it did not write all `n` bytes, an error is printed and the program exits.
4. The loop repeats: `read` then `write`, over and over, until `read` returns `0`, meaning end-of-file has been reached on standard input. Every byte of input has now been echoed to output.
5. `if (n < 0)`: If `read` ever returns `-1`, something went wrong reading the input, so "Unable to read" is printed and the program exits.
6. `return(EXIT_SUCCESS);`: All input was read and written successfully, so the program exits with a status of 0.

# simple-ls
Step by step walkthrough
1. You run the program with exactly one argument, the directory to list, for example `./simple-ls .`.
2. `if (argc != 2)`: If the argument count is not exactly 2 (program name + one directory name), a usage message is printed to stderr and the program exits.
3. `if ((dp = opendir(argv[1])) == NULL)`: The `opendir` call opens the directory named `argv[1]`. If it fails (for example, the directory does not exist or you lack permission), an error is printed and the program exits.
4. `while ((dirp = readdir(dp)) != NULL)`: The `readdir` call returns the next entry in the directory one at a time. Each entry's name is printed with `printf("%s\n", dirp->d_name)`.
5. When `readdir` returns `NULL`, all directory entries have been read and the loop ends.
6. `(void)closedir(dp)`: The directory stream is closed.
7. `return EXIT_SUCCESS;`: The program exits with a status of 0.

# welcome
Step by step walkthrough
1. `getlogin()` is called to obtain the username of the current user.
2. The returned name is formatted into the greeting with `printf("Welcome to CS631 Advanced Programming in the UNIX Environment, %s!\n", ...)` and printed to standard output.
3. `main` falls off the end without a `return` statement.
4. Note: this file intentionally contains various errors - there is no `return` statement (an exit status is never explicitly set), and the return value of `printf` is ignored.

