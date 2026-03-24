#!/bin/bash

IMAGE="rainfall.qcow2"
ISO="RainFall.iso"
ISO_URL="https://cdn.intra.42.fr/isos/RainFall.iso"
IMAGE_SIZE="2G"

if [ ! -f "$IMAGE" ]; then
    echo "[+] Création de l'image $IMAGE ($IMAGE_SIZE)"
    qemu-img create -f qcow2 "$IMAGE" "$IMAGE_SIZE"
else
    echo "[=] L'image $IMAGE existe déjà"
fi

if [ ! -f "$ISO" ]; then
    echo "[+] Téléchargement de $ISO"
    wget "$ISO_URL" -O "$ISO"
else
    echo "[=] L'ISO $ISO existe déjà"
fi

qemu-system-x86_64 \
    -m 1024 \
    -hda "$IMAGE" \
    -cdrom "$ISO" \
    -boot d \
    -enable-kvm \
    -net nic \
    -net user,hostfwd=tcp::4243-:4242 \
	-daemonize