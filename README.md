# C-Shell

## Nutshell - Linux shell in C

## Introduction

This is an implementation of a Linux shell written in C language.


#### To run the shell :
- Run the command `make`.
- Run `./a.out` to get a prompt as 

```

<USER@Hostname:~> for your PC.
```


### Commands

1. cd
- Changes directory to the directory specified, throws an error if the directory does not exist.
- Handles flags `[~]`, `[-]`.
- Works same as the Ubuntu shell.
- Implemented in builtin.c


2. pwd
- Displays the name of the working directory.
- Works same as the Ubuntu shell.
- Implemented in builtin.c

3. echo [arguments]
    
- Displays whatever is specified in[arguments]. 
- Accounts for double quotes as well.
- Works same as the Ubuntu shell.
- Supports multi commands in a single line i.e.
 ```
 echo hi; echo hello
     will show output as :
hi
hello
```
- Implemented in builtin.c

4. quit
- Exits the shell.

5. history
-  It displays the last few commands.
- history [num] displays the specified `num` commands.
- Implemented in history.c

6. pinfo `[pid]`
- Displays deatisl about the process such as status, memory, executable path and pid id.
- Implemented in pinfo.c

7. fg <jobNumber>
    
- Brings a running or a stopped background job with given job number to foreground.
- Implemented in user_defined.c

8.   bg <jobNumber>
- Changes a stopped background job to a running background job.
- Implemented in user_defined.c
9. jobs
- This command prints a list of all currently running background processes along with their job number.
- Works for `jobs -r` and `jobs -s` as well.
- Implemented in user_defined.c

10. sig [jobnumber] [signalnumber]
- Takes the job number and send the assigned signal to that process.
- Gives error when proper input is not given.
- Implemented in user_defined.c

11. ls
- Lists all the files and directories in a specified directory.
- ls -l, ls-a, ls -al, ls -la, ls -l -a works.
- ls .., ls . and ls also works.
- Works same as the Ubuntu shell.
- Implemented in ls.c

12.  Input-Output Redirection & Piping

    - Handles `<`, `>`, `>>`, and `|` operators appropriately, wherever they are in the command
    - Throws error if syntax is incorrect.
    - Implemented in pipe.c

13. `​CTRL-Z`

- Changes the status of currently running job to stop, and pushes it to the background.
- Implemented in runcommands.c

14. `CTRL-C`
- Interrupting the foreground process using SIGINT signal.
- Implemented in runcommands.c

15. `CTRL-D`
- Exists the shell.
- Implemented in runcommands.c

16. overkill
- Kills all background process at once.
- Implemented in user_defined.c

###### history.txt Must exist before compilation


