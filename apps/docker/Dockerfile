# Define the OS version (must match the one used by AzerothCore)
ARG UBUNTU_VERSION=22.04 # lts
FROM ubuntu:$UBUNTU_VERSION

ENV DEBIAN_FRONTEND=noninteractive

# Install the python dependencies here.
# Since 'skeleton' and 'runtime' in the original Dockerfile inherit from this,
# these packages will exist in ALL stages.
RUN apt-get update && apt-get install -y --no-install-recommends \
    python3-dev libpython3-dev libboost-python-dev \
    && rm -rf /var/lib/apt/lists/*
