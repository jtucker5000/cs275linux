FROM ubuntu:22.04

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update && \
    apt-get install -y \
      openssh-server \
      sudo \
      curl \
      gnupg \
      ca-certificates && \
    mkdir /var/run/sshd

# Create user
RUN useradd -ms /bin/bash demo && \
    echo 'demo:password' | chpasswd && \
    adduser demo sudo && \
    echo 'demo ALL=(ALL) NOPASSWD:ALL' >> /etc/sudoers

# Install Puppet agent
RUN curl -LO https://apt.puppet.com/puppet7-release-jammy.deb && \
    dpkg -i puppet7-release-jammy.deb && \
    apt-get update && \
    apt-get install -y puppet-agent

# Enable SSH password auth
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config

EXPOSE 22

CMD ["bash", "-c", "/usr/sbin/sshd & while true; do /opt/puppetlabs/bin/puppet agent -t --server puppet; sleep 30; done"]



