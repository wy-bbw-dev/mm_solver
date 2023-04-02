FROM archlinux:latest as builder
RUN pacman -Syyu --noconfirm \
    && pacman -S --noconfirm base-devel \
    && pacman -S --noconfirm python python-pip \
    && pip install --upgrade pip \
    && pip install conan gcovr \
    && pacman -S --noconfirm cmake ninja \
    && pacman -S --noconfirm qt6-base qt6-webengine \
    && pacman -S --noconfirm openssh \
    && pacman -S --noconfirm unzip \
    && rm -rf `pip cache dir` \
    && rm -rf /var/cache/pacman/pkg/*
RUN pacman -S --noconfirm wget curl
WORKDIR /app
