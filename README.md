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

## Docker

There is a Dockerfile that creates a full install of all dependencies for a self-hosted runner. 
To install the self-hosted runner, a TOKEN parameter needs tobe supplied, which provides authentication.
Get the token, follow self-hosted runner instructions below.
```
./docker/docker_build <TOKEN> <REPO_TAG>
./docker/docker_build <TOKEN> github.actions.runner.ubuntu-22.04
```

## Go

Go development tutorial can be found [here](https://code.visualstudio.com/docs/languages/go)

## Buf and Connect

Follow these links to setup [Buf](https://buf.build/docs/installation) and [Connect-go](https://connectrpc.com/docs/go/getting-started/) to auto generate API code from .proto files.
To keep versions updated, install [go-mod-upgrade](https://github.com/oligot/go-mod-upgrade)

# Run

To execute this module in Linux, run:
```
python3 test_runner.py
```

# Programming Languages

Intermediate+ Level Skills
1. [C++](tests/cpp/README.md) 
2. [Python](tests/py/README.md)
3. [Go](tests/go/README.md)

# GitHub

The following is a list of GitHub workflows supported:

| Workflow                            | Description                                                                          |
|-------------------------------------|--------------------------------------------------------------------------------------|
|[build_libraries.yaml](\.github/workflows/build_libraries.yaml) | Installs dependencies, libraries, and uploads artifacts.|
|[build.yaml](\.github/workflows/build.yaml) | Installs dependencies, downloads artifacts, builds, and runs all tests.|

## Self-Hosted Runners

Add self-hosted runners by following this [link](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/adding-self-hosted-runners)

### Start Service on Boot

Configure the self-hosted runner application as a service to start on boot [here](https://docs.github.com/en/actions/hosting-your-own-runners/managing-self-hosted-runners/configuring-the-self-hosted-runner-application-as-a-service)\
`Note: Handle the User used to start the self-hosted runner applications. The user may be set in /etc/systemd/system/actions.runner.<githubuser>-<repo>.<host>.service`

To find the service name in the list of running services on Linux systems:
```
$ systemctl --type=service | grep actions.runner
actions.runner.<hostname>.service loaded active running GitHub Actions Runner (<hostname>)
```

### Non-systemd Boot Systems

If your system boots with init.d, perform the following steps to launch the actions runner as a service:
1. Copy [boot-script](scripts/init.d/boot-script) to init.d: 
```
sudo cp scripts/init.d/boot-script /etc/init.d
```
2. Update paths as necessary.
3. Copy [actions.runner.service.template](scripts/init.d/actions.runner.service.template) to init.d:
```
sudo cp scripts/init.d/actions.runner.service.template /etc/init.d
```
4. Make the script executable: 
```
sudo chmod +x /etc/init.d/boot-script
```
5. Update the rc.d system links (to start script on boot): 
```
sudo update-rc.d boot-script defaults
```
If the above fails, link it to the booter:
```
sudo ln -s /etc/init.d/boot-script /etc/rc2.d/S20boot-script
```
6. (Optional) Start the service: 
```
sudo service boot-script start
```
7. (Optional) Check service status
```
sudo service boot-script status
```
If all else fails, use manual mode to start the service:
``` 
./bin/runsvc.sh ./bin/actions.runner.service.template
```

