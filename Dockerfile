# Use the official Ubuntu 22.04 base image
FROM ubuntu:22.04

# Update package lists and install required tools
RUN apt-get update && \
    apt-get -y install tar curl vim gzip sudo cmake g++ git python3 python3-pip libgtest-dev && \
    apt-get clean && \
    rm -rf /var/lib/apt/lists/*

# Install Python packages using pip
RUN pip3 install cget

# Create a new user
ENV USER=peter
ENV HOME=/home/$USER

RUN useradd -m -s /bin/bash $USER && \
    # Add the user to the admin group (assuming 'sudo' is the admin group)
    usermod -aG sudo $USER && su - $USER && \
    # Change ownership of the working directory to the new user
    chown -R $USER:$USER $HOME

# Set a password for the user (replace 'password' with the actual password)
# RUN echo "${USER}:password" | chpasswd

# Set the working directory to $HOME
WORKDIR $HOME

# Switch to the non-root user for actions-runner installation
USER $USER

# Install additional dependencies using cget
RUN cget install https://github.com/nlohmann/json/archive/refs/tags/v3.11.3.tar.gz && \
   cget install https://github.com/boostorg/boost/releases/download/boost-1.84.0/boost-1.84.0.tar.gz

ARG TOKEN=""
# The token is supplied by GitHub when a new self-hosted runner is created. 
# Replace the token as required, otherwise build will fail authentication.
RUN mkdir actions-runner && cd actions-runner && \
    curl -o actions-runner-linux-x64-2.312.0.tar.gz -L https://github.com/actions/runner/releases/download/v2.312.0/actions-runner-linux-x64-2.312.0.tar.gz && \
    tar xzf ./actions-runner-linux-x64-2.312.0.tar.gz && \
    ./config.sh --url https://github.com/parandor/samples --token $TOKEN

COPY scripts/init.d/* /etc/init.d/

# Specify the default command to run on container start
CMD ["/bin/bash", "-c", "/etc/init.d/boot-script start"]
