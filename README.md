# MiniShell

MiniShell is a minimal shell implementation developed as part of the Ecole 42 project. It supports pipes, heredoc, built-in commands, variable expansion, and wildcard handling. This project demonstrates advanced process control, file descriptor management, and signal handling in C.

## Features
- **Pipe and Heredoc Support:** Seamlessly connect processes and handle input redirections with heredoc.
- **Wildcard Expansion:** Flexible command matching with wildcard handling.
- **Builtin and Binary Execution:** Execute core shell builtins as well as external commands.
- **Robust Error Management:** Comprehensive error handling and precise exit status reporting.

## Project Structure
```
├── .gitignore
├── Makefile
├── minishell                # Compiled binary
├── .vscode
│   ├── launch.json
│   └── settings.json
├── include
│   └── minishell.h         # Main header file defining macros, enums, and prototypes
└── src
    └── exec
        └── pipe_heredoc.c  # Implements pipe setup, heredoc redirection, and command execution
```

## Build Instructions

Compile the project with:
```bash
make
```

## Usage

Launch MiniShell using:
```bash
./minishell
```

Once started, the shell will accept standard UNIX commands, handle piping, redirection, and built-in commands.

## Testing

For testing and debugging, use the provided Makefile targets and the integrated terminal in your IDE. Visual Studio Code users can utilize the `.vscode/launch.json` configuration for debugging support.

## Contributing

Contributions are welcome. Please fork the repository, create your feature branches, and open a pull request with your improvements. Adhere to the project's coding conventions and include clear documentation for any changes.

## License

This project is a part of the Ecole 42 curriculum and is provided for educational purposes.
  
---

Happy coding!