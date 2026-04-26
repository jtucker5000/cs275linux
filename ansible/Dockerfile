FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y openssh-server sudo python3 && \
    mkdir /var/run/sshd

# Create a demo user
RUN useradd -ms /bin/bash ansible && \
    echo 'ansible:password' | chpasswd && \
    adduser ansible sudo

# Allow password auth (simpler for demo)
RUN sed -i 's/#PasswordAuthentication yes/PasswordAuthentication yes/' /etc/ssh/sshd_config

EXPOSE 22

CMD ["/usr/sbin/sshd", "-D"]
