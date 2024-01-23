# Samples
Language samples.

# Purpose
The purpose of this module is to showcase intermediate and advanced concepts of the language. \
This is not a complete or whole set and is not meant as a finished library nor production ready. \
This is meant for learnings and tutorials that can be successfully compiled and executed. \
Purpose of which is to use as a collection of code snippets that cover a broad list of categories.

# Installation

To configure VS Code with GCC, GDB, and WSL, follow this [link](https://code.visualstudio.com/docs/cpp/config-wsl)

To install dependencies, run:
```
./install.sh
```

# Run

To execute this module in Linux, run:
```
python3 test_runner.py
```

# C++ Intermediate+ Level Skills

| Category                            | Skills                                                                               |
|-------------------------------------|--------------------------------------------------------------------------------------|
| **Language Features**               | [Smart Pointers](tests/cpp/smart_pointers.cpp) \| [Templates](tests/cpp/templates.cpp) \| [Lambda Expressions](tests/cpp/lambdas.cpp) \| [Function Pointers](tests/cpp/function_pointers.cpp) \| [RAII](tests/cpp/RAII.cpp) |
| **Memory Management**               | [Memory Allocation Strategies](tests/cpp/memory_allocation.cpp) \| [Custom Allocators](tests/cpp/custom_allocators.cpp) \| [Memory Leaks Detection](tests/cpp/memory_leak_detection.cpp) \| [Debugging](tests/cpp/debugging.cpp) |
| **Concurrency and Parallelism**     | [std::thread](tests/cpp/thread.cpp) \| [std::mutex](tests/cpp/mutex.cpp) \| [std::condition_variable](tests/cpp/condition_variable.cpp) \| Parallel Algorithms \| Atomic Types  |
| **STL Mastery**                     | Advanced Usage of Containers (std::vector, std::map, etc.), Iterators, Algorithms    |
| **Object-Oriented Design Patterns** | Factory, Observer, Strategy, Command, Decorator                                      |
| **Advanced Templates**              | SFINAE (Substitution Failure Is Not An Error), Template Metaprogramming              |
| **File I/O**                        | std::ifstream, std::ofstream, [Serialization](tests/cpp/serialization.cpp), Binary File Handling                   |
| **Network Programming**             | Socket Programming, Networking Libraries (Boost.Asio), REST APIs                      |
| **Build Systems**                   | CMake, Make, Understanding of Build Tools and Dependency Management                 |
| **Debugging Proficiency**           | GDB, Valgrind, AddressSanitizer, Profiling Tools                                     |
| **Testing Frameworks**               | Google Test, Catch2, Unit Testing, Test-Driven Development (TDD)                      |
| **Version Control**                 | Git, Branching Strategies, Conflict Resolution, Code Review                          |
| **Code Documentation**              | Doxygen, Javadoc, Writing Self-Documenting Code                                       |
| **Cross-Platform Development**       | Platform Abstraction, Handling Platform-Specific Code, Build Configurations        |
| **Performance Optimization**        | Profiling, Cache Optimization, SIMD, Memory Layout, Compiler Flags                    |
| **Security Best Practices**         | Buffer Overflow Prevention, Secure Coding Standards, Code Audits                      |
| **Continuous Integration**          | Github CI, Jenkins, Travis CI, GitLab CI, Automating Build and Test Pipelines         |
| **Agile and Scrum Methodologies**   | Sprint Planning, Daily Stand-ups, Sprint Review, Retrospective                        |
| **Communication Skills**            | Effectively Communicating Technical Concepts, Team Collaboration                       |
| **Mentoring and Leadership**        | Guiding Junior Developers, Code Reviews, Knowledge Sharing, Technical Leadership    |

# GitHub

The following is a list of GitHub workflows supported:

| Workflow                            | Description                                                                          |
|-------------------------------------|--------------------------------------------------------------------------------------|
|[build.yaml](\.github/workflows/build.yaml) | Installs permissions, dependencies, builds, and runs all tests.|

## Self-Hosted Runners

1. Add self-hosted runners by following this [link](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/adding-self-hosted-runners)

2. Configure the self-hosted runner application as a service to start on boot [here](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/configuring-the-self-hosted-runner-application-as-a-service)

3. To find the service name in the list of running services on Linux systems you can use the systemctl command:
    ```
    $ systemctl --type=service | grep actions.runner
    ```
    `actions.runner.<hostname>.service loaded active running GitHub Actions Runner (<hostname>)`

