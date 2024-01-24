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

# Programming Languages

Intermediate+ Level Skills
1. [C++](tests/cpp/README.md) 
2. Python
3. Go


# GitHub

The following is a list of GitHub workflows supported:

| Workflow                            | Description                                                                          |
|-------------------------------------|--------------------------------------------------------------------------------------|
|[build.yaml](\.github/workflows/build.yaml) | Installs permissions, dependencies, builds, and runs all tests.|

## Self-Hosted Runners

1. Add self-hosted runners by following this [link](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/adding-self-hosted-runners)

2. Configure the self-hosted runner application as a service to start on boot [here](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/configuring-the-self-hosted-runner-application-as-a-service)\
`Note: handle the User used to start the self-hosted runner applications. The user may be set in /etc/systemd/system/actions.runner.<githubuser>-<repo>.<host>.service`

3. To find the service name in the list of running services on Linux systems you can use the systemctl command:
    ```
    $ systemctl --type=service | grep actions.runner
    ```
    `actions.runner.<hostname>.service loaded active running GitHub Actions Runner (<hostname>)`

